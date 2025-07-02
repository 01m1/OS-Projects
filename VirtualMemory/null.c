#include <stdio.h>

int main(int argc, char *argv[]) {
    int x = 5;
    int* p = &x;
    p = NULL;
    int a = *p;

    return 0;
}