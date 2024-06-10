//t0 printer alle positive tal og t1 printer aller negative tal

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *fT0(void *array) {
    int *arr = (int *)array;
    for(int i = 0; i < 10; i++){
        if (arr[i] >= 0){
            printf("t0 prints: %d\n", arr[i]);
        }
    }
}

void *fT1(void *array) {
    int *arr = (int *)array;
    for(int i = 0; i < 10; i++){
        if (arr[i] < 0){
            printf("t1 prints: %d\n", arr[i]);
        }
    }
}

int main(){
    pthread_t t0;
    pthread_t t1;

    int array[] = {-5,43,-666,4,556,8,9564,-13,-523,5};

    
    pthread_create(&t1, NULL, fT1, (void *) array);
    pthread_create(&t0, NULL, fT0, (void *) array);
    

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    pthread_exit(NULL);
    return 0;
}