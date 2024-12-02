#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // 새로운 프로세스 생성

    if (pid == 0) { // 자식 프로세스
        printf("Hello from Child Process! PID: %d\n", getpid());
    } else if (pid > 0) { // 부모 프로세스
        printf("Hello from Parent Process! PID: %d, Child PID: %d\n", getpid(), pid);
    } else { // 오류 처리
        perror("Failed to fork");
    }

    return 0;
}