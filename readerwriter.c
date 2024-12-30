#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int data = 0;
int reader_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    pthread_mutex_lock(&read_mutex);
    reader_count++;
    if (reader_count == 1) {
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&read_mutex);

    printf("Reader %d is reading data: %d\n", reader_id, data);
    usleep(rand() % 1000);

    pthread_mutex_lock(&read_mutex);
    reader_count--;
    if (reader_count == 0) {
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_unlock(&read_mutex);
    return NULL;
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    pthread_mutex_lock(&mutex);
    data++;
    printf("Writer %d is writing data: %d\n", writer_id, data);
    usleep(rand() % 1000);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    int num_readers, num_writers;

    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);

    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    printf("Enter the initial value of data: ");
    scanf("%d", &data);

    pthread_t readers[num_readers];
    pthread_t writers[num_writers];
    int reader_ids[num_readers];
    int writer_ids[num_writers];

    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("Failed to create reader thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("Failed to create writer thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    printf("Main thread: All threads have finished execution.\n");
    return 0;
}
