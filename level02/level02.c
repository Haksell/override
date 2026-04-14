#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char password[100];  // [rsp+10h] [rbp-110h] BYREF
    char ptr[48];  // [rsp+80h] [rbp-A0h] BYREF
    char username[100];  // [rsp+B0h] [rbp-70h] BYREF

    memset(username, 0, sizeof(username));
    memset(ptr, 0, 41);
    memset(password, 0, sizeof(password));

    FILE* stream = fopen("/home/users/level03/.pass", "r");
    if (!stream) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    int bytes_read = fread(ptr, 1, 41, stream);
    ptr[strcspn(ptr, "\n")] = '\0';
    if (bytes_read != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }
    fclose(stream);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("--[ Password: ");
    fgets(password, 100, stdin);
    password[strcspn(password, "\n")] = '\0';

    puts("*****************************************");
    if (strncmp(ptr, password, 41)) {
        printf(username);
        puts(" does not have access!");
        exit(1);
    }
    printf("Greetings, %s!\n", username);
    system("/bin/sh");
    return 0;
}
