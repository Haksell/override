#include <stdio.h>
#include <string.h>

char a_user_name[100];

int verify_user_name() {
    puts("verifying username....\n");
    return memcmp(a_user_name, "dat_wil", 7) != 0;
}

int verify_user_pass(const void* pass) { return memcmp(pass, "admin", 5) != 0; }

int main() {
    char s[64];
    int correct;

    memset(s, 0, sizeof(s));
    correct = 0;
    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, 256, stdin);
    correct = verify_user_name();
    if (correct) {
        puts("nope, incorrect username...\n");
    } else {
        puts("Enter Password: ");
        fgets(s, 100, stdin);
        correct = verify_user_pass(s);
        puts("nope, incorrect password...\n");
    }
    return 1;
}
