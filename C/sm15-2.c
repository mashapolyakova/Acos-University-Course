#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
/*Использован код задачи с семинара группы 172-18*/
int main(int argc, char *argv[]) {
    if (argc < 4) {
        abort();
    }
    int rows, cols;
    sscanf(argv[2], "%d", &rows);
    sscanf(argv[3], "%d", &cols);
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0660);
    if (fd < 0) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    size_t sz = rows * cols * sizeof(int);
    if (ftruncate(fd, sz) < 0) {
        fprintf(stderr, "Error\n");
        close(fd);
        return 1;
    }
    int *arr = mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if (arr == MAP_FAILED) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    int  dif_rows = 0, dif_col = 1, i = 0, j = 0, cur = 0;
    while (i < rows && j < cols && arr[i * cols + j] == 0) {
        arr[i * cols + j] = ++cur;
        if (i + dif_rows < 0 ||
            i + dif_rows >= rows ||
            j + dif_col < 0 ||
            j + dif_col >= cols ||
            arr[(i + dif_rows) * cols + j + dif_col] != 0) {
            int ndif_rows = dif_col;
            int ndif_col = -dif_rows;
            dif_rows = ndif_rows;
            dif_col = ndif_col;
        }
        i += dif_rows;
        j += dif_col;
    }
    munmap(arr, sz);
}
