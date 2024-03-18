#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 10

pthread_mutex_t lock;

void *f(void* idx) {

    pthread_mutex_lock(&lock);
    
    // Casting to int* and dereferencing
    int id = *((int*)idx);

    // Increment index
    id++;

    // Sleep in callback
    sleep(1);
    
    printf("Thread %d started\n", id);
    
    pthread_mutex_unlock(&lock);
}

int main() {
    
    //void *status;
    
    //Array of threads.
    pthread_t threads[NUM_THREADS];
    
    //Array of arguments
    int arguments[NUM_THREADS];
    
    // For 08 first observation
    int increment = 0;
    
    // Initialising mutex
    if (pthread_mutex_init(&lock, NULL)) {
        printf("Error initialising mutex");
        return 1;
    }
    
    // Create 10 threads and give increasing indexes as arguments
    for (int i = 0; i < NUM_THREADS; i++) {
        arguments[i] = i;
        pthread_mutex_lock(&lock);
        int return_value_thread_create = pthread_create(&threads[i], NULL, f, &arguments[i]);
        if (return_value_thread_create) {
            printf("Error creating thread!");
            exit(-1);
        }
        pthread_mutex_unlock(&lock);
    }
    
    // Joining the threads.
    for (int i = 0; i < NUM_THREADS; i++) {
        int return_value_thread_join = pthread_join(threads[i], NULL);
        if (return_value_thread_join) {
            printf("Error joining thread %d", i);
            exit(-1);
        }
    }
    
    if (pthread_mutex_destroy(&lock)) {
        printf("Error destroying mutex");
        exit(-1);
    }
    return 0;
} 