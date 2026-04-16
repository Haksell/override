#include <stdint.h>
#include <stdio.h>
#include <string.h>

int clear_stdin() {
    int result;  // eax

    do result = getchar();
    while (result != '\n' && result != -1);
    return result;
}

int get_unum() {
    uint32_t v1[3];  // [esp+1Ch] [ebp-Ch] BYREF

    v1[0] = 0;
    fflush(stdout);
    scanf("%u", v1);
    clear_stdin();
    return v1[0];
}

int store_number(int a1) {
    unsigned int unum;  // [esp+18h] [ebp-10h]
    unsigned int idx;  // [esp+1Ch] [ebp-Ch]

    printf(" Number: ");
    unum = get_unum();
    printf(" Index: ");
    idx = get_unum();
    if (idx == 3 * (idx / 3) || (unum >> 18) == 183) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    } else {
        *(_DWORD*)(a1 + 4 * idx) = unum;
        return 0;
    }
}

int read_number(int a1) {
    printf(" Index: ");
    int idx = get_unum();
    printf(" Number at data[%u] is %u\n", idx, *(_DWORD*)(a1 + 4 * idx));
    return 0;
}

//----- (08048723) --------------------------------------------------------
int main(int argc, const char** argv, const char** envp) {
    _BYTE v6[400];  // [esp+24h] [ebp-1B8h] BYREF
    int number;  // [esp+1B4h] [ebp-28h]
    char s[4];  // [esp+1B8h] [ebp-24h] BYREF
    int v9;  // [esp+1BCh] [ebp-20h]
    int v10;  // [esp+1C0h] [ebp-1Ch]
    int v11;  // [esp+1C4h] [ebp-18h]
    int v12;  // [esp+1C8h] [ebp-14h]
    unsigned int v13;  // [esp+1CCh] [ebp-10h]

    v13 = __readgsdword(0x14u);
    number = 0;
    *(_DWORD*)s = 0;
    v9 = 0;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    memset(v6, 0, sizeof(v6));
    while (*argv) {
        memset((void*)*argv, 0, strlen(*argv));
        ++argv;
    }
    while (*envp) {
        memset((void*)*envp, 0, strlen(*envp));
        ++envp;
    }
    puts(
        "----------------------------------------------------\n"
        "  Welcome to wil's crappy number storage service!   \n"
        "----------------------------------------------------\n"
        " Commands:                                          \n"
        "    store - store a number into the data storage    \n"
        "    read  - read a number from the data storage     \n"
        "    quit  - exit the program                        \n"
        "----------------------------------------------------\n"
        "   wil has reserved some storage :>                 \n"
        "----------------------------------------------------\n");
    while (1) {
        printf("Input command: ");
        number = 1;
        fgets(s, 20, stdin);
        s[strlen(s) - 1] = 0;
        if (!memcmp(s, "store", 5u)) {
            number = store_number((int)v6);
            goto LABEL_13;
        }
        if (!memcmp(s, "read", 4u)) {
            number = read_number((int)v6);
            goto LABEL_13;
        }
        if (!memcmp(s, "quit", 4u)) return 0;
    LABEL_13:
        if (number)
            printf(" Failed to do %s command\n", s);
        else
            printf(" Completed %s command successfully\n", s);
        *(_DWORD*)s = 0;
        v9 = 0;
        v10 = 0;
        v11 = 0;
        v12 = 0;
    }
}
