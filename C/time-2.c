#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stddef.h>

int main(int argc, char *argv[]) {
    //int stat(char *pathname, struct stat *st)
    //int fstat() // catalogs
    //int lstat() // links
    // struct stat { mode_t st_mode;} ISREG
    // lstat -> num
    long long answer = 0;
    for (int i = 1; i < argc; ++i) {
        struct stat lst;
        int tmp2 = lstat(argv[i], &lst);
        if (tmp2 >= 0 && S_ISREG(lst.st_mode) && lst.st_nlink == 1) {
            answer += lst.st_size;
        }
    }
    printf("%lld\n", answer);
    return 0;
}
