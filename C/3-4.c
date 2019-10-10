#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
struct Item 
{
    unsigned int iters;
    unsigned int first;
    unsigned int second;
    double change1;
    double change2;
    pthread_mutex_t *firstm;
    pthread_mutex_t *secondm;
    double *acc;
};

void * foo(void * ptr) {
    struct Item *item = (struct Item *) ptr;
    for (int i = 0; i < item->iters; ++i) {
        if ((item->first) > (item->second)) {
            pthread_mutex_lock(item->secondm);
            pthread_mutex_lock(item->firstm);
            *((item->acc)+(item->second)) += item->change2;
            *((item->acc)+(item->first)) += item->change1;
            pthread_mutex_unlock(item->firstm);
            pthread_mutex_unlock(item->secondm);
        } else {
            pthread_mutex_lock(item->firstm);
            pthread_mutex_lock(item->secondm);
            *((item->acc)+(item->first)) += item->change1;
            *((item->acc)+(item->second)) += item->change2;
            pthread_mutex_unlock(item->secondm);
            pthread_mutex_unlock(item->firstm);
        }
    }
    return NULL;
}
int main(int argc, char *argv[]) {
    unsigned int acc_count, thr_count;
    scanf("%u", &acc_count);
    scanf("%u", &thr_count);
    double accs[acc_count];
    pthread_t buf[thr_count];
    pthread_mutex_t *block;
    block = (pthread_mutex_t *)calloc(acc_count, sizeof(pthread_mutex_t));
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);
    for (int i = 0; i < thr_count; ++i) {
        struct Item *item = calloc(1 ,sizeof(item));
        scanf("%u %u %lf %u %lf", &(item->iters), &(item->first), 
                        &(item->change1), &(item->second), &(item->change2));
        item->acc = accs;
        item->firstm = block + item->first;
        item->secondm = block + item->second;
        pthread_create(&buf[i], &attr, foo, (void *) &item);
    }
    for (int i = 0; i < thr_count; ++i) {
        pthread_join(buf[i], NULL);
    }
    for (int i = 0; i < acc_count; ++i) {
        printf("%lf\n", accs[i]);
    }
    pthread_attr_destroy(&attr);
    free(block);
    free(&buf);
    return 0;
}
