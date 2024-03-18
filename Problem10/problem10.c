#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *array;
    int rear;
    int front;
    int size;
} Queue;

// Queue initialiser
void Queue_init(Queue *queue) {
    queue->array = NULL;
    queue->rear = -1;
    queue->front = -1;
    queue->size = 0;
}

// Queue deinitialisation
void Queue_deinit(Queue *queue) {
    free(queue->array);
    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
}

// Pushing an element to the queue.
void Queue_push(Queue *queue, int data) {
    
    int *new_array = (int*)realloc(queue->array, (queue->size + 1) * sizeof(int));
    
    // If the queue is empty
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->rear = queue->size;
    queue->array = new_array;
    queue->array[queue->rear] = data;
    queue->size++;
}

// Popping an element from the queue.
int Queue_pop(Queue *queue) {
    
    // If the queue is empty
    if (queue->size == 0) {
        printf("Queue is already empty!\n");
        return 0;
    }
    
    // Data to pop is the first element of the queue
    int data_to_pop = queue->array[0];
    
    // If the queue has only one element
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
        queue->size = 0;
        return data_to_pop;
    }
    
    // Shifting all elements to the left to overwrite the first one
    for (int i = 0; i < queue->size; i++) {
        queue->array[i] = queue->array[i + 1];
    }
    queue->size--;
    //queue->rear--; // Redundant(?)
    
    int *new_array = (int*)realloc(queue->array, (queue->size) * sizeof(int));
    queue->array = new_array;
    //queue->front++;
    return data_to_pop;
    
}

void Queue_print(Queue *queue) {
    printf("Queue: ");
    for (int i = 0; i < queue->size; i++)
        printf("%d ", queue->array[i]);
    printf("\n");
}

int main() {
    srand(time(NULL));
    Queue my_queue;
    Queue_init(&my_queue);
    
    // Populating queue with random numbers from 1 to 100.
    for (int i = 0; i < 10; i++) {
        Queue_push(&my_queue, rand() % 100 + 1);
    }
    Queue_print(&my_queue);
    
    // Popping all elements + 1 and printing one by one.
    for (int i = 0; i <= 10; i++) {
        printf("Popped: %d\n", Queue_pop(&my_queue));
        Queue_print(&my_queue);
    }
    
    Queue_push(&my_queue, 10);
    Queue_print(&my_queue);
    
    Queue_deinit(&my_queue);
    
}