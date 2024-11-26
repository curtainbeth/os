#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Global variable to store the sum
int sum = 0;

// Thread function to compute the sum of numbers
void *runner(void *param) {
    int i, upper;

    // Convert the input parameter to an integer
    upper = atoi((char *)param);
    sum = 0;

    // Calculate the sum of integers from 1 to 'upper'
    for (i = 1; i <= upper; i++) {
        sum += i;
    }

    // Exit the thread
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t tid;           // Thread identifier
    pthread_attr_t attr;     // Thread attributes

    // Check if the correct number of arguments is provided
    if (argc != 2) {
        printf("Usage: %s <positive integer>\n", argv[0]);
        return 1;
    }

    // Validate that the input is a positive integer
    int upper = atoi(argv[1]);
    if (upper <= 0) {
        printf("ERROR! Please provide a positive integer.\n");
        return 1;
    }

    // Initialize thread attributes
    pthread_attr_init(&attr);

    // Create the thread, passing the upper limit as an argument
    if (pthread_create(&tid, &attr, runner, argv[1]) != 0) {
        printf("ERROR! Failed to create thread.\n");
        return 1;
    }

    // Wait for the thread to finish execution
    if (pthread_join(tid, NULL) != 0) {
        printf("ERROR! Failed to join thread.\n");
        return 1;
    }

    // Print the result
    printf("Sum: %d\n", sum);

    return 0;
}
