#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 10

pthread_cond_t cond;

pthread_mutex_t lock;

void *thread(void *arg) {
    
    int *process_done = (int*)arg;
    
    pthread_mutex_lock(&lock);
    
    printf("Waiting...\n");
    
    // Simulating processing
    while (!(*process_done)) {
        pthread_cond_wait(&cond, &lock);
        printf("Processing\n");
        sleep(1);
    }
    
    printf("Finished waiting\n");
    pthread_mutex_unlock(&lock);
}

int main() {
    
    int process_done = 0;

    pthread_t threads[NUM_THREADS];
    int rc; // For thread creation result.
    
    if (pthread_mutex_init(&lock, NULL)) {
        printf("Error initialising mutex");
        exit(-1);
    }
    
    // Creating NUM_THREADS threads.
    for (int i = 0; i < NUM_THREADS; i++) {
        rc = pthread_create(&threads[i], NULL, thread, &process_done);
        if (rc) {
            printf("Error creating thread %d", i);
            exit(-1);
        }
    }
    
    sleep(3); // to modify to 5
    
    process_done = 1;
    
    // Signaling all threads to finish processing
    if (pthread_cond_broadcast(&cond)) {
        printf("Error signaling threads");
        exit(-1);
    }
    
    // Waiting all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
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