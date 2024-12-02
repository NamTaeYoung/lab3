#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *dir_name = "test_dir";
    const char *file_name = "test_dir/example.txt";

    if (mkdir(dir_name, 0777) == 0) {
        printf("Directory '%s' created successfully.\n", dir_name);
    } else {
        perror("Failed to create directory");
    }

    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return 1;
    }

    fprintf(file, "This is a test file inside '%s'.\n", dir_name);
    fclose(file);
    printf("File '%s' created successfully.\n", file_name);

    return 0;
}