#include <stdio.h>
#include <dirent.h>

int main() {
    const char *dir_name = ".";
    struct dirent *entry;
    DIR *dp = opendir(dir_name);

    if (dp == NULL) {
        perror("Failed to open directory");
        return 1;
    }

    printf("Files and directories in '%s':\n", dir_name);
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
    return 0;
}