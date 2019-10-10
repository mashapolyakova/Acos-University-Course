#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>



int main(int argc, char *argv[]) {
    int fd1[2];
    int fd2[2]; 
    double beg;
    double dx;
    int n;
    sscanf(argv[1], "%lf", &beg);
    sscanf(argv[2], "%d", &n);
    sscanf(argv[3], "%lf", &dx);
    if (pipe(fd1) < 0) {
        _exit(1);
    }
    if (pipe(fd2) < 0) {
        _exit(1);
    }
    if (!fork()) {
        if (!fork()) {
            double k = beg;
            double m;
            for(int i = 0; i < (n + 1); ++i) {
                //printf("son1 i = %d\n", i);
                m = sin(k);
                write(fd1[1], &m, 8);
                fflush(NULL);
                k += dx;
            }
            double sum1 = 0;
            double cur;
            int j = -1;
            while (j < n) {
                //printf("son1 j = %d\n", j);
                read(fd2[0], &cur, 8);
                sum1 += cur * cur;
                ++j;
            }
            printf("1 %.10g\n", sum1);
            fflush(NULL);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            close(fd2[0]);
            //printf("grson1\n");
            return 0;
        }
        wait(NULL);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);
        close(fd2[0]);
        //printf("son1\n");
        return 0;
    }
    if (!fork()) {
        if (!fork()) {
            double k = beg;
            double sum2 = 0;
            double cur;
            int j = -1;
            while (j < n) {
                //printf("son 2 j = %d\n", j);
                read(fd1[0], &cur, 8);
                sum2 += fabs(cur);
                ++j;
            }
            double m;
            for(int i = 0; i < (n + 1); ++i) {
                //printf("son 2 i = %d\n", i);
                m = cos(k);
                write(fd2[1], &m, 8);
                fflush(NULL);
                k += dx;
            }
            printf("2 %.10g\n", sum2);
            fflush(NULL);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            close(fd2[0]);
            //printf("grson2");
            return 0;
        }
        wait(NULL);
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);
        close(fd2[0]);
        //printf("son2\n");
        return 0;
    }
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[1]);
    close(fd2[0]);
    wait(NULL);
    wait(NULL);
    //printf("batya\n");
    printf("0 0\n");
    fflush(NULL);
    return 0;
}
