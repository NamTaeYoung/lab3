#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Parent process will execute `ls` command.\n");

    // execvp를 사용해 ls 명령 실행
    char *args[] = {"ls", "-l", NULL};
    execvp(args[0], args);

    // exec 호출 이후 실행되지 않음 (오류 발생 시만 실행됨)
    perror("exec failed");
    return 1;
}