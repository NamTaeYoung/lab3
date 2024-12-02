#include <stdio.h>
#include <unistd.h>

int main() {
    const char *file_name = "test_dir/example.txt";

    if (unlink(file_name) == 0) {
        printf("File '%s' deleted successfully.\n", file_name);
    } else {
        perror("Failed to delete file");
    }

    return 0;
}