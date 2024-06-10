
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t readers_cond;
int counter = 0;
int active_readers = 0;

void* writer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait until there are no active readers
        while (active_readers > 0) {
            pthread_cond_wait(&readers_cond, &mutex);
        }

        // Increment the counter
        counter++;
        printf("Writer: Counter incremented to %d\n", counter);

        pthread_mutex_unlock(&mutex);

        // Break the loop after incrementing the counter
    }

    pthread_exit(NULL);
}

void* reader(void* arg) {
    while (1)
    {pthread_mutex_lock(&mutex);
    active_readers++;
    pthread_mutex_unlock(&mutex);

    // Read the counter
    printf("Reader: Counter value is %d\n", counter);

    pthread_mutex_lock(&mutex);
    active_readers--;

    // Signal the writer if no more active readers
    if (active_readers == 0) {
        pthread_cond_signal(&readers_cond);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);}
}

int main() {
    pthread_t writer_thread, reader_thread1, reader_thread2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&readers_cond, NULL);

    // Create writer thread
    pthread_create(&writer_thread, NULL, writer, NULL);

    // Create reader threads
    pthread_create(&reader_thread1, NULL, reader, NULL);
    pthread_create(&reader_thread2, NULL, reader, NULL);

    // Wait for threads to finish
    pthread_join(writer_thread, NULL);
    pthread_join(reader_thread1, NULL);
    pthread_join(reader_thread2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&readers_cond);

    return 0;
}
