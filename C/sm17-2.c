#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int mysys(char *str) {
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    }
    if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } 
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return 128 + WTERMSIG(status);
}
/*
int main(int argc, char *argv[]) {
    waitpid(pid_t pid, int *status, 0);
    if (WIFEXITED(status)) {
         WEXITSTATUS(status);
    }
    return 128 + WTERMSIG(status);
    return 0;
}
*/
