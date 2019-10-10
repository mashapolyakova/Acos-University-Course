#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
void handler(int s) {
    exit(0);
}

int main() {
    signal(SIGALRM, handler);
    time_t seconds;
    int n_sec;
    scanf("%ld %d", &seconds, &n_sec);
    struct timeval sig = {};
    struct timeval current = {};
    sig.tv_sec = seconds;
    sig.tv_usec = n_sec/1000;
    gettimeofday(&current, NULL);
    /*printf("%ld\n", current.tv_sec);*/
    if (sig.tv_sec < current.tv_sec) {
        return 0;
    }
    if (sig.tv_sec == current.tv_sec && sig.tv_usec <= current.tv_usec) {
        return 0;
    }
    struct itimerval to = {};
    to.it_value.tv_sec = sig.tv_sec - current.tv_sec;
    to.it_value.tv_usec = sig.tv_usec - current.tv_usec;
    if (to.it_value.tv_usec < 0) {
        to.it_value.tv_sec -= 1;
        to.it_value.tv_usec += 1000000;
    }
    setitimer(ITIMER_REAL, &to, NULL);
    pause();
    return 0;
}
