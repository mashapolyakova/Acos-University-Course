#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0600);
    unsigned val;
    unsigned char buf[4];

    while(scanf("%u", &val)==1) {
        buf[0] = val >> 24;
        buf[1] = val >> 16;
        buf[2] = val >> 8;
        buf[3] = val;
        write(fd, buf, sizeof(buf));
    }
    close(fd);
    return 0;
}
