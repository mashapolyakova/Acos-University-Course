#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int invoke(const char *cmd) {
    if (!fork()) {
        execlp(cmd, cmd, NULL);
        _exit(1);
    }
    int status = 0;
    wait(&status);
    return WIFEXITED(status) && (WEXITSTATUS(status) == 0);
}

int main(int argc, char *argv[]) {
    return !((invoke(argv[1]) || invoke(argv[2])) && invoke(argv[3]));
}
