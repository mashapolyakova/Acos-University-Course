#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
int ** matrix;
int rows, cols;
void * foo(void *p) {
    int iter_count, row, col, incr;
    scanf("%d %d %d %d", &iter_count, &row, &col, &incr);
    if (row == -1) {
	for (int j = 0; j < iter_count; ++j) {
            for (int i = 0; i < rows; ++i) {
	        matrix[i][col]  += incr;
	    }
	}
    }
    else {
        for (int j = 0; j < iter_count; ++j) {
            for (int i = 0; i < cols; ++i) {
                matrix[row][i]  += incr;
            }
        }

    }
    return NULL;

}
int main() {
    int rows, cols, thrs;
    scanf("%d %d %d", &rows, &cols, &thrs);
    matrix = calloc(cols*rows, sizeof(int));
    pthread_t * buf = calloc(thrs, sizeof(pthread_t));
    for (int i = 0; i < thrs; ++i) {
        pthread_create(&buf[i], NULL, foo, NULL);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
	    printf("%d ", matrix[i][j]);
	}
	printf("\n");
    }
    free(buf);
    return 0;
}
