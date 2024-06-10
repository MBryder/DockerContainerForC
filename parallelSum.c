// 2 threads deler et array op og finder gennemsnittet
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2
#define ARRAY_SIZE 10

float first = 0;
float sec = 0;

void *sum1(void *array) {
    float *arr = (float *)array;
    int i = 0;
    while(i < ARRAY_SIZE/2){
        first += arr[i];
        printf("from 1: %.2f\n",arr[i]);
        i++;
    }
    first = first/(ARRAY_SIZE/2);
    printf("averge from lower: %.2f\n", first);
}

void *sum2(void *array) {
    float *arr = (float *)array;
    int i = ARRAY_SIZE-1;
    while(i >= ARRAY_SIZE/2){
        sec += arr[i];
        printf("from 2: %.2f\n",arr[i]);
        i--;
    }
    sec = sec/(ARRAY_SIZE/2);
    printf("averge from higher: %.2f\n", sec);
}

int main() {
    pthread_t t[NUM_THREADS];
    float array[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10};

    pthread_create(&t[0], NULL, sum1, (void *)array);
    pthread_create(&t[1], NULL, sum2, (void *)array);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);


    printf("%.2f\n", (float)((first+sec)/2));

    pthread_exit(NULL);
}