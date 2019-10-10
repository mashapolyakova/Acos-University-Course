#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    int fd[2];
    if (pipe(fd) < 0) {
        _exit(1);
    }
    if (!fork()) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        if (!fork()) {
            execlp(argv[1], argv[1], NULL);
            _exit(0);
        }
        if (!fork()) {
            execlp(argv[2], argv[2], NULL);
            _exit(0);
        }
    }
    if (!fork()) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        int out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(out, 1);
        execlp(argv[3], argv[3], NULL);
        close(out);
        _exit(0);
    } else {
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
