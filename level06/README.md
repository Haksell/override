## level06

This is a basic reverse engineering challenge. The executable has some fluff but the core of it is quite simple.

The user needs to provide a login of at least 6 characters. The program then creates a deterministic target, and checks if it corresponds to the user input.

```c
bool auth(char* login, int serial) {
    login[strcspn(login, "\n")] = '\0';
    int login_length = strnlen(login, 32);
    if (login_length <= 5) return false;

    int target = (login[3] ^ 4919) + 6221293;
    for (int i = 0; i < login_length; ++i) {
        if (login[i] <= 31) return false;
        target += (target ^ login[i]) % 1337;
    }
    return serial != target;
}

int main() {
    char login[32];
    fgets(login, 32, stdin);
    
    int serial;
    scanf("%d", &serial);

    if (auth(login, serial)) return 1;

    puts("Authenticated!");
    system("/bin/sh");
    return 0;
}
```

We wrote a small Python script that does the same operation and prints the output.

```py
import sys


assert len(sys.argv) == 2
login = sys.argv[1]
assert len(login) >= 6
serial = (ord(login[3]) ^ 4919) + 6221293
for c in map(ord, login):
    serial += (serial ^ c) % 1337
print(serial)
```

We can then simply enter the same password and serial in the program.

```console
$ python level06.py axel42  
6232880
$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: axel42 
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6232880
Authenticated!
$ whoami 
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```