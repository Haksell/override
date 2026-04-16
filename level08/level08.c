#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void log_wrapper(FILE* a1, const char* a2, const char* a3) {
    char dest[264];

    strcpy(dest, a2);
    snprintf(&dest[strlen(dest)], 254 - strlen(dest), a3);
    dest[strcspn(dest, "\n")] = 0;
    fprintf(a1, "LOG: %s\n", dest);
}

int main(int argc, const char** argv) {
    if (argc != 2) printf("Usage: %s filename\n", *argv);

    FILE* log_file = fopen("./backups/.log", "w");
    if (!log_file) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(EXIT_FAILURE);
    }
    log_wrapper(log_file, "Starting back up: ", argv[1]);

    FILE* stream = fopen(argv[1], "r");
    if (!stream) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char dest[100];
    strcpy(dest, "./backups/");
    strncat(dest, argv[1], 99 - strlen(dest));

    // int fd = open(dest, 193, 432);
    int fd = open(dest, O_WRONLY | O_CREAT | O_EXCL, 0660);
    if (fd < 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (true) {
        char buf = fgetc(stream);
        if (buf == EOF) break;
        write(fd, &buf, 1);
    }

    log_wrapper(log_file, "Finished back up ", argv[1]);
    fclose(stream);
    close(fd);
    return EXIT_SUCCESS;
}
