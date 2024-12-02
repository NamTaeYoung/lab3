#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t sigset;

    // SIGINT를 차단
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    printf("SIGINT (Ctrl+C) is blocked for 10 seconds.\n");

    sleep(10); // SIGINT 차단 유지

    // SIGINT 차단 해제
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    printf("SIGINT is now unblocked. Press Ctrl+C to terminate.\n");

    while (1) {
        sleep(1); // 무한 루프
    }

    return 0;
}