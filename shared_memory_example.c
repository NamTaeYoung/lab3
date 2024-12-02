#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024 // 공유 메모리 크기

int main() {
    // 공유 메모리 키 생성
    key_t key = ftok("shmfile", 65);

    // 공유 메모리 생성 및 ID 반환
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) { // 자식 프로세스
        // 공유 메모리 연결
        char *shared_memory = (char *)shmat(shmid, NULL, 0);
        printf("Child: Reading from shared memory: %s\n", shared_memory);
        shmdt(shared_memory); // 공유 메모리 분리
    } else if (pid > 0) { // 부모 프로세스
        // 공유 메모리 연결
        char *shared_memory = (char *)shmat(shmid, NULL, 0);
        const char *message = "Hello from Parent Process!";
        strncpy(shared_memory, message, SHM_SIZE);
        printf("Parent: Written to shared memory: %s\n", message);
        shmdt(shared_memory); // 공유 메모리 분리

        wait(NULL); // 자식 프로세스 종료 대기

        // 공유 메모리 삭제
        shmctl(shmid, IPC_RMID, NULL);
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}