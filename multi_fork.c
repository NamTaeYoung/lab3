#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == 0) { // 자식 프로세스
            printf("Child %d: PID = %d\n", i + 1, getpid());
            return 0;
        }
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL); // 모든 자식 프로세스 종료 대기
    }

    printf("All children have finished.\n");
    return 0;
}