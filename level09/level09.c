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

void set_msg(char* a1) {
    char s[1024];

    memset(s, 0, sizeof(s));
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(s, 1024, stdin);
    strncpy(a1, s, *(int*)(a1 + 180));
}

int set_username(char* a1) {
    char s[140];

    memset(s, 0, 128);
    puts(">: Enter your username");
    printf(">>: ");
    fgets(s, 128, stdin);
    for (int i = 0; i <= 40 && s[i]; ++i) *(char*)(a1 + i + 140) = s[i];
    return printf(">: Welcome, %s", (const char*)(a1 + 140));
}

int handle_msg() {
    char v1[140];  // [rsp+0h] [rbp-C0h] BYREF
    uint64_t v2;  // [rsp+8Ch] [rbp-34h]
    uint64_t v3;  // [rsp+94h] [rbp-2Ch]
    uint64_t v4;  // [rsp+9Ch] [rbp-24h]
    uint64_t v5;  // [rsp+A4h] [rbp-1Ch]
    uint64_t v6;  // [rsp+ACh] [rbp-14h]
    int v7;  // [rsp+B4h] [rbp-Ch]

    v2 = 0;
    v3 = 0;
    v4 = 0;
    v5 = 0;
    v6 = 0;
    v7 = 140;
    set_username(v1);
    set_msg(v1);
    return puts(">: Msg sent!");
}

int main() {
    puts(
        "--------------------------------------------\n"
        "|   ~Welcome to l33t-m$n ~    v1337        |\n"
        "--------------------------------------------");
    handle_msg();
    return 0;
}
