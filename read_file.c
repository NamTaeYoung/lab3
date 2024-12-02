#include <stdio.h>

int main() {
    const char *file_name = "test_dir/example.txt";

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char line[256];
    printf("Contents of '%s':\n", file_name);
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}