#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // 자식 프로세스
        printf("Child process running (PID: %d).\n", getpid());
        while (1) sleep(1); // 무한 루프
    } else if (pid > 0) { // 부모 프로세스
        sleep(2); // 2초 대기
        printf("Parent sending SIGTERM to child process (PID: %d).\n", pid);
        kill(pid, SIGTERM); // 자식 프로세스에 SIGTERM 전송
    } else {
        perror("fork failed");
    }

    return 0;
}