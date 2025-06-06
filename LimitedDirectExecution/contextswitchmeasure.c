#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

// Measuring the cost of a system call

int main() {

    cpu_set_t my_set; // Define your cpu_set bit mask.
    CPU_ZERO(&my_set); // Initialize it all to 0, i.e. no CPUs selected.
    CPU_SET(7, &my_set); // set the bit that represents core 7.
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set); // Set affinity of tihs process to the defined mask, i.e. only 7.

    int p1[2]; // Child to parent
    int p2[2]; // Parent to child

    if (pipe(p1) < 0) {return 1;} // Error
    if (pipe(p2) < 0) {return 1;} // Error

    int pid = fork();
    if (pid == -1) {return 1;}
    if (pid == 0) {
        // Child process
        close(p1[0]);
        close(p2[1]);

        int x;

        if (read(p2[0], &x, sizeof(x)) == -1) {return 1;}
 
        printf("Child Received %d\n", x);
        x*= 4;
        if (write(p1[1], &x, sizeof(x)) == -1) {return 1;}
        printf("Child Wrote %d\n", x);
        int core = sched_getcpu();
        printf("Child Running on CPU %d\n", core);

        close(p1[1]);
        close(p2[0]);
    } else {
        
        // Parent process
        close(p1[1]);
        close(p2[0]);

        srand(time(NULL));
        int y = rand() % 10;
        if (write(p2[1], &y, sizeof(y)) == -1) {return 1;}
        printf("Parent Wrote %d\n", y);
        if (read(p1[0], &y, sizeof(y)) == -1) {return 1;}
        printf("Parent Result is %d\n", y);
        int core = sched_getcpu();
        printf("Parent Running on CPU %d\n", core);

        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
    close(p1[0]);
    close(p1[1]);
    return 0;
}