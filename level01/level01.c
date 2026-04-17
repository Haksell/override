#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_user_name[100];

bool verify_user_name() {
    puts("verifying username....\n");
    return memcmp(a_user_name, "dat_wil", 7) != 0;
}

bool verify_user_pass(const void* password) {
    return memcmp(password, "admin", 5) != 0;
}

int main() {
    char password[64];
    memset(password, 0, sizeof(password));
    bool check = false;

    puts("********* ADMIN LOGIN PROMPT *********");

    printf("Enter Username: ");
    fgets(a_user_name, 256, stdin);
    check = verify_user_name();
    if (check) {
        puts("nope, incorrect username...\n");
        return EXIT_FAILURE;
    }

    puts("Enter Password: ");
    fgets(password, 100, stdin);
    check = verify_user_pass(password);
    if (check || !check) {  // hard to avoid tbh
        puts("nope, incorrect password...\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
