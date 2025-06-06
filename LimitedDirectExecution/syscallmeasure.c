#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

// Measuring the time to run a system call

int main() {
    struct timeval current_time;
    struct timeval next_time;
    gettimeofday(&current_time, NULL);
    read(0, NULL, 0);
    gettimeofday(&next_time, NULL);
    printf("Took %ld microseconds\n", next_time.tv_usec-current_time.tv_usec);

    return 0;
}