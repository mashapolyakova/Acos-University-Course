#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stddef.h>

int main(void) {
    time_t t = time(NULL);
    int days;
    while (scanf("%d", &days) == 1) {
        long long dd = (long long) days * (60 * 60 * 24);
        long long cur = t + dd;
        if (cur >= INT_MIN && cur <= INT_MAX && (time_t)dd == dd && (time_t)cur == cur) {
            time_t c = cur;
            struct tm  *p = localtime(&c);
            printf("%04d-%02d-%02d\n", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday);
        } else {
            printf("OVERFLOW\n");
        }
    }
    return 0;
}
