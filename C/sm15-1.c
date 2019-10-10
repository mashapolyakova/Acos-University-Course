#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const char *path = argv[1];

    int fd = open(path, O_RDONLY, 0);
    if (fd < 0) abort();

    struct stat stb;
    fstat(fd, &stb);

    if (!S_ISREG(stb.st_mode)) abort();
    if (stb.st_size == 0) {
        return 0;
    }

    // size_t != off_t
    size_t sz = stb.st_size;
    if (sz != stb.st_size) abort();

    void *ptr = mmap(NULL, stb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (ptr == MAP_FAILED) abort();

    close(fd);
    double *eptr = (double *) ((char *) ptr + sz);
    double *cptr = (double *) ptr;
    double ans = 0;

    
    for (; cptr < eptr; ++cptr) {
        ans += *cptr;
    }
    sz /= sizeof(double);
    ans /= sz;
    munmap(ptr, stb.st_size);
    printf("%a\n", ans);
}
