#include <fcntl.h>
#include <linux/prctl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

// Constants valid for x86 only
#define ORIG_EAX 44
#define SYS_EXECVE 11

int main() {
    char buffer[128];

    __pid_t pid = fork();
    memset(buffer, 0, sizeof(buffer));

    if (pid == 0) {
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(buffer);
    } else {
        do {
            int wstatus = 0;
            wait(&wstatus);
            if (WIFEXITED(wstatus) || WIFSIGNALED(wstatus)) {
                puts("child is exiting...");
                return 0;
            }
        } while (ptrace(PTRACE_PEEKUSER, pid, ORIG_EAX, 0) != SYS_EXECVE);
        puts("no exec() for you");
        kill(pid, SIGKILL);
    }

    return 0;
}
