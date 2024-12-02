#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// 디렉토리 및 파일 나열 함수
void list_dir(const char *dir_name) {
    struct dirent *entry;
    DIR *dp = opendir(dir_name); // 디렉토리 열기

    if (dp == NULL) {
        perror("Failed to open directory");
        return;
    }

    printf("Directory: %s\n", dir_name);

    // 디렉토리 내 파일 및 디렉토리 나열
    while ((entry = readdir(dp)) != NULL) {
        // 현재 디렉토리 (.)와 부모 디렉토리 (..)는 제외
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printf("%s\n", entry->d_name);

        // 하위 디렉토리를 재귀적으로 방문
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            list_dir(path); // 재귀 호출
        }
    }

    closedir(dp); // 디렉토리 닫기
}
int main(int argc, char *argv[]) {
    // 디렉토리 경로 확인
    const char *start_dir = (argc > 1) ? argv[1] : ".";

    // 디렉토리 나열 함수 호출
    list_dir(start_dir);

    return 0;
}
