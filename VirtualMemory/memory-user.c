#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int mb = atoi(argv[1]);
    double time = atof(argv[2]);
    
    int size = (mb * 1024 * 1024) / sizeof(int);
    int *arr = malloc(size * sizeof(int));
    int item;

    // Touch all memory (initialize)
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    
    clock_t begin = clock();

    while (((double) (clock() - begin) / CLOCKS_PER_SEC) < time) {
        for (int i = 0; i < size; i++) {
            item = arr[i];
        }
    }
    return 0;
}