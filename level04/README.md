## level04

The ISO is 64-bit but the files are ELF 32-bit. Important for the disassembly here!

```console
level04@OverRide:~$ uname -a
Linux OverRide 3.13.0-95-generic #142~precise1-Ubuntu SMP Fri Aug 12 18:20:15 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux
level04@OverRide:~$ file level04 
level04: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x7386c3c1bbd3e4d8fc85f88744379783bf327fd7, not stripped
```