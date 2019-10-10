#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
int main() {
    int n;
    int status;
    int q = 1;
    while(scanf("%d", &n) == 1) {
        /*printf("it is a %d process\n", q);*/
        pid_t pid = fork();
        q += 1;
        /*if (q > 5) {
            pid = -1;
        }*/
        if (pid > 0) {
           /* q += 1;*/
           /* printf("it is a %d process\n", q);*/
            wait(&status);
            if (WEXITSTATUS(status) != 0) {
                /*printf("it is a %d process\n", q);*/
                if (q > 2) {
                    return 1;
                } else {
                    return 0;
                }
            }
           /* printf("it is a %d process\n", q);*/
            printf("%d\n", n);
            return 0;
        } else if (pid == -1) {
            printf("%d\n", -1);
            exit(1);
        }
    }
    /*printf("it is a final %d process\n", q);*/
    return 0;
}
