#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buffer[128];
    const char *message = "Hello from Parent Process!";

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) { // 자식 프로세스
        close(pipefd[1]); // 쓰기 종료
        read(pipefd[0], buffer, sizeof(buffer)); // 파이프에서 데이터 읽기
        printf("Child Process Received: %s\n", buffer);
        close(pipefd[0]);
    } else if (pid > 0) { // 부모 프로세스
        close(pipefd[0]); // 읽기 종료
        write(pipefd[1], message, strlen(message) + 1); // 파이프에 데이터 쓰기
        close(pipefd[1]);
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}