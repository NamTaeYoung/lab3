#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHM_SIZE 1024 // 공유 메모리 크기

int main() {
    // 공유 메모리 및 세마포어 초기화
    key_t key = ftok("shmfile", 65); // 공유 메모리 키 생성
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // 공유 메모리 생성
    char *shared_memory = (char *)shmat(shmid, NULL, 0); // 공유 메모리 연결

    // 세마포어 생성 (읽기 세마포어, 쓰기 세마포어)
    sem_t *sem_read = sem_open("/sem_read", O_CREAT, 0644, 0);
    sem_t *sem_write = sem_open("/sem_write", O_CREAT, 0644, 1);

    if (fork() == 0) { // 자식 프로세스: 파일 쓰기
        FILE *dest_file = fopen("destination.txt", "w");
        if (dest_file == NULL) {
            perror("Error opening destination file");
            exit(1);
        }

        while (1) {
            // 읽기 세마포어 대기
            sem_wait(sem_read);

            // 공유 메모리에서 데이터 읽기
            if (strcmp(shared_memory, "EOF") == 0) {
                break; // EOF 도달 시 종료
            }

            fprintf(dest_file, "%s", shared_memory); // 파일에 쓰기

            // 쓰기 세마포어 신호
            sem_post(sem_write);
        }

        fclose(dest_file);
        shmdt(shared_memory); // 공유 메모리 분리
        exit(0);
    } else { // 부모 프로세스: 파일 읽기
        FILE *source_file = fopen("source.txt", "r");
        if (source_file == NULL) {
            perror("Error opening source file");
            exit(1);
        }

        while (1) {
            // 쓰기 세마포어 대기
            sem_wait(sem_write);

            // 파일에서 데이터 읽기
            if (fgets(shared_memory, SHM_SIZE, source_file) == NULL) {
                strcpy(shared_memory, "EOF"); // EOF 표시
                sem_post(sem_read);
                break;
            }

            // 읽기 세마포어 신호
            sem_post(sem_read);
        }

        fclose(source_file);
        wait(NULL); // 자식 프로세스 종료 대기
        shmdt(shared_memory); // 공유 메모리 분리
        shmctl(shmid, IPC_RMID, NULL); // 공유 메모리 제거
        sem_unlink("/sem_read"); // 세마포어 제거
        sem_unlink("/sem_write");
        sem_close(sem_read);
        sem_close(sem_write);
    }

    return 0;
}