#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <unistd.h>

bool auth(char* login, int serial) {
    login[strcspn(login, "\n")] = '\0';
    int login_length = strnlen(login, 32);
    if (login_length <= 5) return 1;

    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
        puts("\x1B[32m.---------------------------.");
        puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1B[32m'---------------------------'");
        return 1;
    } else {
        int target = (login[3] ^ 4919) + 6221293;
        for (int i = 0; i < login_length; ++i) {
            if (login[i] <= 31) return 1;
            target += (target ^ (unsigned int)login[i]) % 1337;
        }
        return serial != target;
    }
}

int main() {
    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");

    char login[32];
    fgets(login, 32, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");

    int serial;
    scanf("%d", &serial);

    if (auth(login, serial)) return 1;

    puts("Authenticated!");
    system("/bin/sh");
    return 0;
}
