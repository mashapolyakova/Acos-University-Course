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
    pthread_mutex_t *mutexes;
    double *acc;
};

void * foo(void * ptr) {
    struct Item *item = (struct Item *) ptr;
    for (int i = 0; i < item->iters; ++i) {
        if ((item->first) > (item->second)) {
            pthread_mutex_lock(&item->mutexes[item->second]);
            pthread_mutex_lock(&item->mutexes[item->first]);
            *((item->acc)+(item->second)) += item->change2;
            *((item->acc)+(item->first)) += item->change1;
            pthread_mutex_unlock(&item->mutexes[item->first]);
            pthread_mutex_unlock(&item->mutexes[item->second]);
        } else {
            pthread_mutex_lock(&item->mutexes[item->first]);
            pthread_mutex_lock(&item->mutexes[item->second]);
            *((item->acc)+(item->first)) += item->change1;
            *((item->acc)+(item->second)) += item->change2;
            pthread_mutex_unlock(&item->mutexes[item->second]);
            pthread_mutex_unlock(&item->mutexes[item->first]);
        }
    }
    return NULL;
}
int main(int argc, char *argv[]) {
    unsigned int acc_count, thr_count;
    scanf("%u", &acc_count);
    scanf("%u", &thr_count);
    double *accs = calloc(acc_count, sizeof(double));
    pthread_t *buf = calloc(thr_count, sizeof(pthread_t));
    pthread_mutex_t *block = calloc(acc_count, sizeof(pthread_mutex_t));
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);
    struct Item *items = calloc(thr_count, sizeof(struct Item));
    for (int i = 0; i < thr_count; ++i) {
        scanf("%u %u %lf %u %lf", &(items[i].iters), &(items[i].first), 
                        &(items[i].change1), &(items[i].second), &(items[i].change2));
	
        items[i].acc = accs;
        items[i].mutexes = block;
        pthread_create(&buf[i], &attr, foo, (void *) &items[i]);
    }
    for (int i = 0; i < thr_count; ++i) {
        pthread_join(buf[i], NULL);
    }
    for (int i = 0; i < acc_count; ++i) {
        printf("%.10g\n", accs[i]);
    }
    pthread_attr_destroy(&attr);
    free(accs);
    free(block);
    free(buf);
    free(items);
    return 0;
}

