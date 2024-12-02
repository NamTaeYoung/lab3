#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Custom system 함수 구현
int my_system(const char *command) {
    if (command == NULL) {
        return -1; // 명령어가 NULL이면 실패
    }

    pid_t pid = fork(); // 자식 프로세스 생성
    if (pid == 0) { // 자식 프로세스
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        perror("execl failed");
        exit(1);
    } else if (pid > 0) { // 부모 프로세스
        int status;
        waitpid(pid, &status, 0); // 자식 프로세스 종료 대기
        return WEXITSTATUS(status);
    } else {
        perror("fork failed");
        return -1; // fork 실패 시
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // 명령어 조합
    char command[1024] = {0};
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        if (i < argc - 1) {
            strcat(command, " "); // 명령어 사이 공백 추가
        }
    }

    printf("Executing command: %s\n", command);

    // Custom my_system 함수 호출
    int result = my_system(command);

    printf("Command exited with status: %d\n", result);
    return 0;
}