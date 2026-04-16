## level05

This is a small program that reads user input and writes it back in lowercase.

```
(gdb) info function exit
All functions matching regular expression "exit":
[...]
0x08048370  exit
0x08048370  exit@plt
0xf7e5eb70  exit
[...]
(gdb) disas 0x08048370
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:     jmp    DWORD PTR ds:0x80497e0
   0x08048376 <+6>:     push   0x18
   0x0804837b <+11>:    jmp    0x8048330
End of assembler dump.
```

exit@got : 0x080497e0

Very similar to level5 of rainfall hmmmmmm.