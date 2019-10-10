#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    int N, A_0, D, K, m;
    N = atoi(argv[1]);
    A_0 = atoi(argv[3]);
    D = atoi(argv[4]);
    K = atoi(argv[5]);
    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0660);
    close(fd);
    for (int i = 0; i < N; ++i) {
        if (!fork()) {
            fd = open(argv[2], O_WRONLY, 0660);
            m = A_0 + i * D;
            for (int j = 0; j < K; ++j) {
                lseek(fd, (i + j * N) *sizeof(int), SEEK_SET);
                write(fd, &m, sizeof(int));
                m += N * D;
            }
            close(fd);
            return 0;
        } else {
            wait(NULL);
        }
    }
    return 0;
}
