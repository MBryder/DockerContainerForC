// Alle threads skriver hello world men lige threads skal køre før ulige
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define NUM_THREADS 4
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t even = PTHREAD_COND_INITIALIZER;
int EVEN_COUNT = 0;
int DONE_EVEN = 0; 

void *printHello(void *id) {
    long tId = (long)id;
    
    pthread_mutex_lock(&lock);
    if ((tId % 2) != 0) {
        while(!DONE_EVEN)
        pthread_cond_wait(&even, &lock); // sætter threaden på pause
    }
    else {
        EVEN_COUNT++;
        if (EVEN_COUNT == NUM_THREADS / 2) { // ser om halvdelen af vores Threads har væreet talt
            DONE_EVEN = 1;
            pthread_cond_broadcast(&even); // Wake up all waiting odd threads
        }
    }
    printf("Hello World form Thread %d\n", tId);
    pthread_mutex_unlock(&lock);
}

int main(){
    pthread_t t[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    for (long i = 1; i <= NUM_THREADS; i++)
    {

        pthread_create(&t[i-1], NULL, printHello, (void *)i);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(t[i], NULL);
    }

    pthread_exit(NULL);
    return 0;
}