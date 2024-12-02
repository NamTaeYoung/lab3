#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // SIGQUIT 무시 설정
    signal(SIGQUIT, SIG_IGN);

    printf("SIGQUIT (Ctrl+\\) is ignored. Press Ctrl+\\ to test.\n");
    printf("Press Ctrl+C to terminate.\n");

    while (1) {
        sleep(1); // 무한 루프
    }

    return 0;
}