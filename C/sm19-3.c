#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
volatile int has_arrived;
volatile int second_count;
volatile int should_terminate;
void handler(int signal_id) {
    if (signal_id == SIGUSR1) {
        has_arrived = 1;
    } else if (signal_id == SIGUSR2) {
        second_count += 1;
    } else if (signal_id == SIGTERM) {
        should_terminate = 1;
    }
}
int main() {
    sigset_t block, unblock;
    sigemptyset(&block);
    sigemptyset(&unblock);
    sigaddset(&block, SIGUSR1);
    sigaddset(&block, SIGUSR2);
    sigaddset(&block, SIGTERM);
    sigprocmask(SIG_BLOCK, &block, &unblock);
    struct sigaction sa = {};
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    printf("%d", getpid());
    fflush(stdout); 
    int count = 0;
    while(1) {
        sigsuspend(&unblock);
        if (should_terminate) {
            exit(0);
        }
        if (has_arrived) {
            printf("%d %d\n", count++, second_count);
            fflush(stdout);
            has_arrived = 0;
        }
    }
} 



