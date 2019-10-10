#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int status = 0;
    int fd[2];
    int file1 = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0660);
    if (pipe(fd) < 0) {
        _exit(1);
    }
    if (!fork()) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        pid_t pid2 = fork();
        if (!pid2) {
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
        waitpid(pid2, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status)) {
            _exit(1);
        }
        if (!fork()) {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
    }
    if (!fork()) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        dup2(file1, 1);
        close(file1);
        if (fork()) {
        execlp(argv[3], argv[3], NULL);
        return 42;
        }
    if (!fork()) {
        execlp(argv[4], argv[4], NULL);
        return 42;
        }
    }
    close(fd[0]);
    close(fd[1]);
    close(file1);
    wait(NULL);
    wait(NULL);
    return 0;   
}

