#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// SIGUSR1 핸들러
void handle_sigusr1(int sig) {
    printf("Received SIGUSR1\n");
}

// SIGUSR2 핸들러
void handle_sigusr2(int sig) {
    printf("Received SIGUSR2\n");
}

int main() {
    // SIGUSR1 및 SIGUSR2 핸들러 등록
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);

    printf("Send SIGUSR1 or SIGUSR2 to this process (PID: %d).\n", getpid());

    while (1) {
        sleep(1); // 무한 루프
    }

    return 0;
}