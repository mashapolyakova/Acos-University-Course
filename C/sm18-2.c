#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
    int fd[2];

    if (pipe(fd) < 0) {
        _exit(1);
    }

    if (!fork()) {
        close(fd[1]);
        if (!fork()) {
            long long sum = 0;
            int cur;
            while (read(fd[0], &cur, 4)) {
                sum += cur;
            }
            printf("%lld\n", sum);
            close(fd[0]);
            exit(0);
        }
        
        close(fd[0]);
        wait(NULL);
        exit(0);
    }

    close(fd[0]);
    int k;
    while (scanf("%d", &k) == 1) {
        write(fd[1], &k, 4);
    }
    close(fd[1]);
    wait(NULL);

    return 0;
}
