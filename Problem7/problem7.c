#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 10

void *f(void* idx) {
    
    // Casting to long and dereferencing
    int id = *(int*)idx;
    printf("%d ", id);
}

int main() {
    
    //void *status;
    
    //Array of threads.
    pthread_t threads[NUM_THREADS];
    
    //Array of arguments
    int arguments[NUM_THREADS];
    
    // Creating NUM_THREADS threads.
    for (int i = 0; i < NUM_THREADS; i++) {
        arguments[i] = i;
        int return_value_thread_create = pthread_create(&threads[i], NULL, f, &arguments[i]);
        if (return_value_thread_create) {
            printf("Error creating thread!");
            exit(-1);
        }
    }
    
    // Waiting all threads to finish
    for(int i = 0; i < NUM_THREADS; i++) {
        int return_value_thread_join = pthread_join(threads[i], NULL);
        if (return_value_thread_join) {
            printf("Error joining thread %d", i);
            exit(-1);
        }
    }

    printf("\n");
}