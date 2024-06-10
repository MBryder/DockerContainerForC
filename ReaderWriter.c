// Read læser count og writer prøver at adde 1 til counter writer på ikke skrive men en reader læser 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int counter = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int reader = 0;

void *readerfunc(void* arg) {
    pthread_mutex_lock(&lock);
    reader++;
    printf("%d\n", counter);
    reader--;
    if(reader == 0){
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

void *writerfunc(void* arg) {
    pthread_mutex_lock(&lock);
    if (reader > 0)
    {
        while (reader != 0) {
            pthread_cond_wait(&cond, &lock);
        }
    }
    counter++;
    printf("Writer +1\n");

    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}


int main(){
    pthread_t r1;
    pthread_t r2;
    pthread_t w;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    while(1)
    {
    pthread_create(&w, NULL, writerfunc, (void *) NULL);
    pthread_create(&r1, NULL, readerfunc, (void *) NULL);
    pthread_create(&r2, NULL, readerfunc, (void *) NULL);
    
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w, NULL);
    sleep(1);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    pthread_exit(NULL);
    return 0;
}