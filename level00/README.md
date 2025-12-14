## level00

After port-forwarding the guest port 4242 to 24242 on the host, and logging in with `ssh`, we are greeted by this screen:

```console
ssh level00@localhost -p 24242
           ____                  ____  _     __   
          / __ \_   _____  _____/ __ \(_)___/ /__ 
         / / / / | / / _ \/ ___/ /_/ / / __  / _ \
        / /_/ /| |/ /  __/ /  / _, _/ / /_/ /  __/
        \____/ |___/\___/_/  /_/ |_/_/\__,_/\___/ 
                                          
                       Good luck & Have fun

   To start, ssh with level00/level00 on 10.0.2.15:4242
level00@localhost's password: 

RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   /home/users/level00/level00
```

The only difference with rainfall (the previous project), is the presence of `Partial RELRO` (rainfall had `No RELRO`).

> Partial RELRO is the default setting in GCC, and nearly all binaries you will see have at least partial RELRO.
> From an attackers point-of-view, partial RELRO makes almost no difference, other than it forces the GOT to come before the BSS in memory, eliminating the risk of a buffer overflows on a global variable overwriting GOT entries.
> -- https://ctf101.org/binary-exploitation/relocation-read-only/

There is an executable file with the setuid bit on. It means that if we manage to execute a shell or any other command from within it, it will be executed with the permissions of `level01`, allowing us to escalate privileges.

```console
level00@OverRide:~$ ls -Ahl
total 13K
-rw-r--r--  1 level01 level01  220 Sep 10  2016 .bash_logout
lrwxrwxrwx  1 root    root       7 Sep 13  2016 .bash_profile -> .bashrc
-rw-r--r--  1 level00 level00 3.5K Sep 10  2016 .bashrc
-rw-r--r--  1 level01 level01  675 Sep 10  2016 .profile
-rwsr-s---+ 1 level01 users   7.2K Sep 10  2016 level00
```

The executable itself, decompiled with Hex-Rays, simply checks if we enter the correct password.

```c
int main() {
    int password;

    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &password);
    if (password == 5276) {
        puts("\nAuthenticated!");
        system("/bin/sh");
        return 0;
    } else {
        puts("\nInvalid Password!");
        return 1;
    }
}
```

```console
level00@OverRide:~$ ./level00 
***********************************
*            -Level00 -           *
***********************************
Password:123

Invalid Password!
level00@OverRide:~$ ./level00 
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```