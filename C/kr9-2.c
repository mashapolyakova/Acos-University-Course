#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>

double func0(double x)
{
    return (x + 1.0) * 1.00001;
}

double func1(double x)
{
    return sin(x);
}

double func2(double x)
{
    return pow(fabs(x), 1.0001);
}

double func3(double x)
{
    return sqrt(fabs(x) + 1);
}
void *func(void *arg)
{
    int serial = (int) (intptr_t) arg;
    pthread_join(ids2[serial], NULL);
    
        pthread_join(ids[2], NULL);
    return NULL;
}

int main() {
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids2[i], NULL, func2, NULL);
    }
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids[i], NULL, func, (void*) (intptr_t) i);
    }

}
