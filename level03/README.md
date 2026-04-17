## level03

The program asks the user for a decimal password, executes some operations on it, and checks if the output is equal to `Congratulations!`.

First, a subtraction is done on our input. There might be tricks to make `rand()` somewhat deterministic by manipulating the system time, but we'll try using `key` in the correct range first.

```c
test(input, 322424845);

void test(int input, int given) {
    int key = given - input;

    // actually a long unoptimized switch case in assembly
    if (1 <= key && key <= 9 || 16 <= key && key <= 21) {
        decrypt(key);
    } else {
        decrypt(rand());
    }
}
```

Then, the program xors 17 bytes with the key, and checks if the result is equal to `Congratulations!`

```c
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
```

XOR is a self-inverse function, so by checking the XOR between the random bytes and the expected result, we can find the correct key.

```python
>>> ord('C') ^ ord('Q')
18
>>> ord('o') ^ ord('}')
18
>>> ...
```

Luckily, 18 is in the valid range from the `test` function, so we can simply give `322424845 - 18 = 322424827` as the password.

```
Password:level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
