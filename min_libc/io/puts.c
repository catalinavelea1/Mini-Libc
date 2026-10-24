#include <unistd.h>
#include <string.h>
#include <stdio.h>

int puts(const char *string) {
    int length = 0;

    while (string[length] != '\0') {
        length++;
    }

    ssize_t bytes_written = write(1, string, length);

    if (bytes_written == -1) {
        return EOF; // Indicates an error
    }

    if (write(1, "\n", 1) == -1) {
        return EOF; // Indicates an error
    }

    return 1; // Indicates success
}
