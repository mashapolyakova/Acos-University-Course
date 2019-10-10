#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (fork()) {
        int fd = open(argv[2], O_RDONLY, 0);
        dup2(fd, 0);
        close(fd);
        fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd, 1);
        close(fd);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    wait(NULL);
    return 0;
}
