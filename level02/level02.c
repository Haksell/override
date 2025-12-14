#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char password[96];  // [rsp+10h] [rbp-110h] BYREF
    int v5;  // [rsp+70h] [rbp-B0h]
    char content[48];  // [rsp+80h] [rbp-A0h] BYREF
    char username[96];  // [rsp+B0h] [rbp-70h] BYREF
    int v8;  // [rsp+110h] [rbp-10h]
    int v9;  // [rsp+114h] [rbp-Ch]
    FILE* stream;  // [rsp+118h] [rbp-8h]

    memset(username, 0, sizeof(username));
    v8 = 0;
    memset(content, 0, 41);
    memset(password, 0, sizeof(password));
    v5 = 0;
    stream = 0;
    v9 = 0;
    stream = fopen("/home/users/level03/.pass", "r");
    if (!stream) {
        fwrite("ERROR: failed to open password file\n", 1, 40, stderr);
        exit(1);
    }
    v9 = fread(content, 1, 41, stream);
    content[strcspn(content, "\n")] = 0;
    if (v9 != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 40, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 40, stderr);
        exit(1);
    }
    fclose(stream);
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    printf("--[ Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = 0;
    printf("--[ Password: ");
    fgets(password, 100, stdin);
    password[strcspn(password, "\n")] = 0;
    puts("*****************************************");
    if (strncmp(content, password, 41)) {
        printf(username);
        puts(" does not have access!");
        exit(1);
    }
    printf("Greetings, %s!\n", username);
    system("/bin/sh");
    return 0;
}
