#include<stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
void foo(int) {
    if (flag == 5) {
        exit(0);
    }
    printf("%d\n", flag++);
    fflush(stdout);
}
volatile int flag = 0;
int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = foo;
    sigaction(SIGINT, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while(1) {
        pause();
    }
}
