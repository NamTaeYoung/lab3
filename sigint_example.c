#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// SIGINT 핸들러 함수
void handle_sigint(int sig) {
    printf("\nCaught SIGINT (Ctrl+C). Use 'kill -9' to terminate.\n");
}

int main() {
    // SIGINT 핸들러 등록
    signal(SIGINT, handle_sigint);

    printf("Press Ctrl+C to trigger SIGINT. Running indefinitely...\n");

    while (1) {
        sleep(1); // 무한 루프 (프로그램 계속 실행)
    }

    return 0;
}