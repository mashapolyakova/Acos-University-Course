#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        char *path = argv[i];
        int fd = open(path, O_RDONLY, 0);
        if (fd < 0) {
            printf("%d\n", -1);
            continue;
        }
        struct stat stb;
        fstat(fd, &stb);
        if (stb.st_size == 0) {
            printf("%d\n", 0);
            close(fd);
            continue;
        }
        void *ptr = mmap(NULL, stb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (ptr == MAP_FAILED){
            printf("%d\n", -1);
            close(fd);
            continue;
        }
        size_t sz = stb.st_size;
        close(fd);
        long long ans = 0;
        char *eptr = (char *) ((char *) ptr + sz);
        char *cptr = (char *) ptr;

        for (; cptr < eptr; ++cptr) {
            if (*cptr == '\n') {
            ++ans;
            }
        }
        --eptr;
        if (*eptr != '\n') {
            ans += 1;
        }
        printf("%lld\n", ans);
        munmap(ptr, stb.st_size);
    }
    return 0;
}
