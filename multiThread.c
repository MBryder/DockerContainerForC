#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 10
#define MAX_RANDOM 10

pthread_mutex_t lock;
int winningThread = 0;
int secretNumber;

// Function for threads to guess the number
void *guessNumber(void *threadid) {
    long tId = (long)threadid; // Cast threadid to long for thread identification
    int guess = 0;

    while (!winningThread) { // Continue guessing while no thread has won yet
        sleep(1);  // Each thread pauses for a second to simulate time taken to "think" about the guess

        // Generate a guess within the range 1 to MAX_RANDOM
        guess = rand() % MAX_RANDOM + 1;  // rand() % MAX_RANDOM generates a number between 0 and 99, so +1 makes it 1 to 100
        printf("Thread %ld guesses %d\n", tId, guess);

        pthread_mutex_lock(&lock); // Lock the mutex to update the winningThread variable safely
        if (guess == secretNumber && !winningThread) { // Check if the guess is correct and no thread has won yet
            winningThread = tId;  // Set the winning thread ID
            printf("Thread %ld guessed the correct number %d!\n", tId, guess);
        }
        else if (guess == secretNumber){
            printf("Thread %ld also guessed the correct number %d!\n", tId, guess);
        }
        pthread_mutex_unlock(&lock); // Unlock the mutex to allow other threads to guess

        if (winningThread) break; // If a winning thread is set, exit the loop
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS]; // Array to hold thread IDs
    srand(time(NULL)); // Seed the random number generator
    secretNumber = rand() % MAX_RANDOM + 1;  // Choose the secret number at random between 1 and 100

    printf("Secret Number is: %d\n", secretNumber);

    pthread_mutex_init(&lock, NULL); // Initialize the mutex

    for (long t = 1; t <= NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        int rc = pthread_create(&threads[t-1], NULL, guessNumber, (void *)t); // Create each thread
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1); // Exit if thread creation fails
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Wait for all threads to complete
    }

    printf("Game Over: Thread %d wins by guessing the secret number %d!\n", winningThread, secretNumber);
    pthread_mutex_destroy(&lock); // Clean up the mutex
    pthread_exit(NULL); // Exit the pthread library cleanly
}
