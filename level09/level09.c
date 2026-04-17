#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void secret_backdoor() {
    char s[128];
    fgets(s, 128, stdin);
    system(s);
}

void set_username(char* buf) {
    char username[140];

    memset(username, 0, 128);
    puts(">: Enter your username");
    printf(">>: ");
    fgets(username, 128, stdin);
    // BUG FOUND!!!
    // It should be < 40 and will allow us to overwrite the strncpy argument
    for (int i = 0; i <= 40 && username[i]; ++i) buf[i + 140] = username[i];
    printf(">: Welcome, %s", buf + 140);
}

void set_msg(char* buf) {
    char s[1024];

    memset(s, 0, sizeof(s));
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(s, 1024, stdin);
    strncpy(buf, s, *(int*)(buf + 180));
}

void handle_msg() {
    char buf[140];
    uint64_t v2 = 0, v3 = 0, v4 = 0, v5 = 0, v6 = 0;
    int v7 = 140;

    set_username(buf);
    set_msg(buf);
    puts(">: Msg sent!");
}

int main() {
    puts(
        "--------------------------------------------\n"
        "|   ~Welcome to l33t-m$n ~    v1337        |\n"
        "--------------------------------------------");
    handle_msg();
    return 0;
}
