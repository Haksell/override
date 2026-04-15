#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void decrypt(int key) {
    char buf[17];  // = "Q}|u`sfg~sf{}|a3"
    // Encoded data written as raw bytes from the assembly
    *(int*)(buf + 0x0) = 0x757c7d51;  // Q}|u
    *(int*)(buf + 0x4) = 0x67667360;  // `sfg
    *(int*)(buf + 0x8) = 0x7b66737e;  // ~sf{
    *(int*)(buf + 0xc) = 0x33617c7d;  // }|a3
    buf[16] = '\0';

    size_t len = strlen(buf);
    for (size_t i = 0; i < 16; i++) buf[i] ^= key;

    if (!strcmp(buf, "Congratulations!")) {
        system("/bin/sh");
    } else {
        puts("\nInvalid Password");
    }
}

void test(int a1, int a2) {
    int diff = a2 - a1;

    // actually a long unoptimized switch case in assembly
    if (1 <= diff && diff <= 9 || 16 <= diff && diff <= 21) {
        decrypt(diff);
    } else {
        decrypt(rand());
    }
}

int main() {
    srand(time(NULL));
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");
    int input;
    scanf("%d", &input);
    test(input, 0x1337d00d);  // 322424845
    return 0;
}
