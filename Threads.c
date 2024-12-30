#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 3

typedef struct {
    int start;
    int end;
} ThreadData;

// Function executed by each thread
void *print_and_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg; // Retrieve the thread data
    int start = data->start;
    int end = data->end;
    int sum = 0;

    for (int i = start; i <= end; i++) {
        printf("Thread printing: %d\n", i);
        sum += i;
    }

    printf("Thread sum from %d to %d: %d\n", start, end, sum);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS]; // Array to hold thread IDs
    ThreadData thread_data[NUM_THREADS]; // Array to hold thread-specific data

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * 10 + 1; // Start number for the thread
        thread_data[i].end = (i + 1) * 10; // End number for the thread

        int result = pthread_create(&threads[i], NULL, print_and_sum, &thread_data[i]);
        if (result != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All threads have finished execution.\n");
    return 0;
}
