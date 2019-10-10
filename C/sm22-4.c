#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
int n;
int pipes[n];

void * foo(void *p) {
    int number = (int)(intptr_t)p;
    int k;
    while (read(pipes[number], &k, 4) == 1)
        long long value;
        if (scanf("%lld", &value) == 1) {
            printf("%d %lld", number, value);
	    int flag = 1;
	    write(pipes[buf[value%n]], &flag, 4);
	} else {
	    for (int i = 0; i < n; ++i) {
	        if (i != number) {
		   int pthread_join(buf[i], NULL);
		}
	    }
	    return NULL;
	}
    }
    return NULL;
}
int main(int argc, char *argv[]) {
    sscanf(argv[1], "%d", &n);
    int fd[2][n];
    for (int i = 0; i < n; ++i) {
       pipes[i] = pipe(fd[i]);
    }
    pthread_t * buf = calloc(n, sizeof(pthread_t));
    for (int i = 0; i < n; ++i) {
        pthread_create(&buf[i], NULL, foo, (void *)(intptr_t) i);
    }
    write(pipes[buf[0]], &flag, 4);
    return 0;
}
