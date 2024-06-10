// Alle threads skriver hello world men lige threads skal køre før ulige
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int even_count = 0; // Counter for even threads
int done_evens = 0; // Indicator for completion of even threads

void *printHello(void *id) {
    long tId = (long)id;

    pthread_mutex_lock(&lock);
    if (tId % 2 == 0) { // Even threads
        printf("Hello world from %ld\n", tId);
        even_count++;
        if (even_count == NUM_THREADS / 2) {
            done_evens = 1;
            pthread_cond_broadcast(&cond); // Wake up all waiting odd threads
        }
    } else { // Odd threads
        while (!done_evens) {
            pthread_cond_wait(&cond, &lock);
        }
        printf("Hello world from %ld\n", tId);
    }
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    pthread_t t[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    for (long i = 1; i <= NUM_THREADS; i++) {
        pthread_create(&t[i-1], NULL, printHello, (void *)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(t[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    pthread_exit(NULL);
    return 0;
}
