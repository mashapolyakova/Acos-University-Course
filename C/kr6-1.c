#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <stddef.h>

int main(int argc, char *argv[]) {
    int year, month;
    sscanf(argv[1], "%d", &year);
    sscanf(argv[2], "%d", &month);
    struct tm *p;
    p = malloc(sizeof(*p));
    p->tm_year = year - 1900;
    p->tm_mon = month - 1;
    p->tm_min = 0;
    p->tm_sec = 0;
    p->tm_hour = 0;
    p->tm_mday = 1;
    p->tm_isdst = -1;
    mktime(p);
    int hours = 0;
    while(p->tm_mon == month - 1) {
        if (p->tm_wday < 5 && p->tm_wday != 0) {
        hours += 8;
        } else if (p->tm_wday == 5) {
            hours += 6;
        }
        p->tm_mday += 1;
        mktime(p);
    }
    printf("%d\n", hours);
    return 0;
}

