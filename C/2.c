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
    pid_t pid = fork();
    if (!pid) {
        int file1 = open(argv[2], O_RDONLY, 0);
        if (file1 < 0) {
            return 42;
        }
        int file2 = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660);
        if (file2 < 0) {
            return 42;
        }
        int file3 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (file3 < 0) {
            return 42;
        }
        dup2(file1, 0);
        dup2(file2, 1);
        dup2(file3, 2);
        close(file1);
        close(file2);
        close(file3);
        execlp(argv[1], argv[1], NULL);
        exit(42);
    }
    waitpid(pid, &status, 0);
    printf("%d\n", status);
    return 0;
}
