#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sched.h>

// Measuring the cost of a system call

int main() {

    cpu_set_t my_set; // Define your cpu_set bit mask.
    CPU_ZERO(&my_set); // Initialize it all to 0, i.e. no CPUs selected.
    CPU_SET(7, &my_set); // set the bit that represents core 7.
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set); // Set affinity of tihs process to the defined mask, i.e. only 7.

    int p1[2];
    if (pipe(p1 == -1)) {return 1;} // Error

    int pid = fork();
    if (pid == -1) {return 1;}

    if (pid == 0) {
        // Child process
        int x;
        if (read(p1[0], &x, sizeof(x)) == -1) {return 1;}
        printf("Received %d\n", x);
        x*= 4;
        if (write(p1[1], &x, sizeof(x)) == -1) {return 1;}
        printf("Wrote %d\n", x);
    } else {

    }
    return 0;
}