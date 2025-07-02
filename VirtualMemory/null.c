#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /*
    int x = 5;
    int* p = &x;
    p = NULL;
    int a = *p;
    */

    int* x = malloc(sizeof(int)*100);
    x[100] = 0;
    
    return 0;
}