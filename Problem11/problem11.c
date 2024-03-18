#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "problem11.h"

int queue_pop(QUEUE *queue) {

    pthread_mutex_lock(&queue->lock_queue);

    // Wait while the queue is empty and engine is not yet stopped.
    while (0 == queue->array_size && 0 == queue->exit_flag) {
        pthread_cond_wait(&queue->not_empty, &queue->lock_queue);
    }
    
    // If the engine is stopped return sentinel value -1.
    if (1 == queue->exit_flag) {
        pthread_mutex_unlock(&queue->lock_queue);
        return -1;
    }

    int data_to_pop = queue->array[queue->front]; 

    // Calculate the front of the circular array.
    queue->front = (queue->front + 1) % QUEUE_SIZE;  
    queue->array_size--;

    // Signal waiting producer thread that the queue is not full.
    pthread_cond_signal(&queue->not_full);
    
    pthread_mutex_unlock(&queue->lock_queue);

    return data_to_pop;
}

void queue_push(QUEUE *queue, int data_to_push) {

    pthread_mutex_lock(&queue->lock_queue);

    // Waiting while the queue is full.
    while (QUEUE_SIZE == queue->array_size) {
        pthread_cond_wait(&queue->not_full, &queue->lock_queue);
    }

    queue->array[queue->rear] = data_to_push;

    // Calculate rear of the circular array.
    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    
    queue->array_size++;

    // Signal waiting consumer thread that queue is not empty.
    pthread_cond_signal(&queue->not_empty);
    
    pthread_mutex_unlock(&queue->lock_queue);
}

// Initialization of the queue
void initialize_queue(QUEUE *queue) {
    queue->array_size = 0;
    queue->front = 0;
    queue->rear = 0;
    queue->exit_flag = 0;
    pthread_mutex_init(&queue->lock_queue, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    pthread_cond_init(&queue->not_full, NULL);
}


// Initialization of the engine
void *initialize_engine() {
    ENGINE_DATA *engine = (ENGINE_DATA*)malloc(sizeof(ENGINE_DATA));
    if (NULL == engine) {
        printf("Error allocating memory in initialize_engine");
        exit(EXIT_FAILURE);
    }

    initialize_queue(&engine->my_queue);
    return engine;
}


// Creating consumer thread
int start_engine(void *engine) {
    ENGINE_DATA *data = (ENGINE_DATA*)engine;

    int rc = pthread_create(&data->consumer_thread, NULL, consumer, data);
    if (rc != 0) {
        printf("Error creating consumer thread!\n");
        exit(EXIT_FAILURE);
    }

    printf("Consumer created!\n");

    return rc;
}

// Helper function for the consumer thread
int on_consume(void *engine) {
    ENGINE_DATA *data = (ENGINE_DATA*)engine;

    while (!data->my_queue.exit_flag) {

        int pop_value = queue_pop(&data->my_queue);

        // If the sentinel value was returned.
        if (pop_value == -1) {
            printf("Finished consuming\n");
            break;
        }

        printf("Consumer thread consumed value: %d\n", pop_value);
    }
}

void *consumer(void *consumer) {

    on_consume(consumer);    

    return NULL;
}

// Function for stopping the engine
void stop_engine(void *engine) {

    ENGINE_DATA *data = (ENGINE_DATA*)engine;
    pthread_mutex_lock(&data->my_queue.lock_queue);

    // Signaling to stop the engine.
    data->my_queue.exit_flag = 1;
    pthread_cond_signal(&data->my_queue.not_empty);

    pthread_mutex_unlock(&data->my_queue.lock_queue);

    pthread_join(data->consumer_thread, NULL);
}

// Destroying the engine
void destroy_engine(void *engine) {
    ENGINE_DATA *data = (ENGINE_DATA*)engine;
    pthread_mutex_destroy(&data->my_queue.lock_queue);
    pthread_cond_destroy(&data->my_queue.not_empty);
    pthread_cond_destroy(&data->my_queue.not_full);
    free(data);
}

// Helper function for the producer thread
int produce(void *data, int index) {

    ENGINE_DATA *engine = (ENGINE_DATA*)data;

    printf("Thread %d produced value: %d\n", pthread_self(), index);
    queue_push(&engine->my_queue, index);

}

void *producer(void *arg) {

    ENGINE_DATA *engine = (ENGINE_DATA*)arg;

    // Generating a new seed based on epoch time XOR with thread ID.
    unsigned int seed = (unsigned int)time(NULL);
    seed ^= pthread_self();
    srand(seed);

    while (!engine->my_queue.exit_flag) {

        int index = (rand() % 100) + 1;

        produce(engine, index);

        // Sleep for 0.5 seconds.
        usleep(500000); 
        //sleep(0.5); // !! Doesn't work?!?
    }

    return NULL;
}

// Function for printing the queue
void print_queue(QUEUE *queue) {

    if (queue->array_size == 0) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");

    for (int i = 0; i < queue->array_size; i++) {
        printf("%d ", queue->array[i]);
    }

    printf("\n");
}

int main() {

    ENGINE_DATA* engine = initialize_engine();

    start_engine(engine);

    pthread_t threads[NUM_THREADS];

    // Creating producer threads.
    for (int i = 0; i < NUM_THREADS; i++) {
        int rc = pthread_create(&threads[i], NULL, producer, engine);
        if (rc != 0) {
            printf("Error creating consumer thread!\n");
            exit(EXIT_FAILURE);
        }   
    }

    // Sleep to let the threads process for SECONDS_TO_PROCESS seconds.
    sleep(SECONDS_TO_PROCESS);

    stop_engine(engine);

    destroy_engine(engine);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    print_queue(&engine->my_queue); 

    return 0;
}