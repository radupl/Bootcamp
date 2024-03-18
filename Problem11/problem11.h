#include <stdbool.h>

#define QUEUE_SIZE 5

#define NUM_THREADS 10

#define SECONDS_TO_PROCESS 2

typedef struct QUEUE {
    int array[QUEUE_SIZE];
    int array_size;
    int front;
    int rear;
    int exit_flag;
    pthread_mutex_t lock_queue;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
}QUEUE;

typedef struct ENGINE_DATA {
    QUEUE my_queue;
    pthread_t consumer_thread;
    int tid_counter;
}ENGINE_DATA;


extern void queue_push(QUEUE *queue, int data_to_push);

extern int queue_pop(QUEUE *queue);

extern int start_engine(void *engine);

extern void stop_engine(void *engine);

extern int produce(void *engine, int index);

extern void *producer(void *arg);

extern int on_consume(void *engine);

extern void *consumer(void *arg);

extern void print_queue(QUEUE *queue);

extern void destroy_engine(void *engine);
