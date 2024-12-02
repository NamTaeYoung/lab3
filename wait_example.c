#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // 자식 프로세스
        printf("Child Process: Doing some work...\n");
        sleep(2); // 작업 시뮬레이션
        printf("Child Process: Done.\n");
        return 42; // 종료 코드
    } else if (pid > 0) { // 부모 프로세스
        int status;
        printf("Parent Process: Waiting for child to finish...\n");
        wait(&status); // 자식 프로세스 종료 대기
        printf("Parent Process: Child finished with status: %d\n", WEXITSTATUS(status));
    } else {
        perror("fork failed");
    }

    return 0;
}