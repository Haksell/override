#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[100];
    memset(username, 0, sizeof(username));
    char password[48];
    memset(password, 0, 41);
    char pass_guess[100];
    memset(pass_guess, 0, sizeof(pass_guess));

    FILE* pass_file = fopen("/home/users/level03/.pass", "r");
    if (!pass_file) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(EXIT_FAILURE);
    }

    int read_size = fread(password, 1, 41, pass_file);
    password[strcspn(password, "\n")] = 0;
    if (read_size != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(EXIT_FAILURE);
    }
    fclose(pass_file);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    printf("--[ Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = 0;
    printf("--[ Password: ");
    fgets(pass_guess, 100, stdin);
    pass_guess[strcspn(pass_guess, "\n")] = 0;
    puts("*****************************************");
    if (strncmp(password, pass_guess, 41)) {
        printf(username);
        puts(" does not have access!");
        exit(EXIT_FAILURE);
    }
    printf("Greetings, %s!\n", username);
    system("/bin/sh");
    return EXIT_SUCCESS;
}
