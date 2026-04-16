#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void log_wrapper(FILE* log_file, const char* s1, const char* s2) {
    char dest[256];

    strcpy(dest, s1);
    snprintf(&dest[strlen(dest)], 254 - strlen(dest), s2);
    dest[strcspn(dest, "\n")] = '\0';
    fprintf(log_file, "LOG: %s\n", dest);
}

int main(int argc, const char** argv) {
    if (argc != 2) printf("Usage: %s filename\n", *argv);

    FILE* log_file = fopen("./backups/.log", "w");
    if (!log_file) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(EXIT_FAILURE);
    }
    log_wrapper(log_file, "Starting back up: ", argv[1]);

    FILE* arg_file = fopen(argv[1], "r");
    if (!arg_file) {
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
        char buf = fgetc(arg_file);
        if (buf == EOF) break;
        write(fd, &buf, 1);
    }

    log_wrapper(log_file, "Finished back up ", argv[1]);
    fclose(arg_file);
    close(fd);
    return EXIT_SUCCESS;
}
