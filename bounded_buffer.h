#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#define ERROR_VALUE -1
typedef int v4si __attribute__((vector_size(16)));

typedef struct
{
    v4si *buffer;       // Buffer array
    int capacity;       // Maximum capacity of the buffer
    int front;          // Index of the front item
    int rear;           // Index of the rear item
    int count;          // Current number of items in the buffer
    sem_t empty;        // Semaphore to track available empty slots
    sem_t full;         // Semaphore to track occupied slots
    sem_t bufferAccess; // Semaphore to control buffer access
} Bounded_Buffer;

// Function prototypes
Bounded_Buffer *create_Bounded_Buffer(int size);
void destroy_Bounded_Buffer(Bounded_Buffer *buffer);
void insert_Bounded_Buffer(Bounded_Buffer *buffer, v4si v);
v4si removeItem_Bounded_Buffer(Bounded_Buffer *buffer);
bool isBufferEmpty(const Bounded_Buffer *buffer);

Bounded_Buffer *create_Bounded_Buffer(int size)
{
    Bounded_Buffer *buffer = (Bounded_Buffer *)malloc(sizeof(Bounded_Buffer));
    buffer->buffer = (v4si *)malloc(sizeof(v4si) * size);
    buffer->capacity = size;
    buffer->front = 0;
    buffer->rear = -1;
    buffer->count = 0;
    sem_init(&(buffer->empty), 0, size);     // Initialize empty slots to capacity
    sem_init(&(buffer->full), 0, 0);         // Initialize occupied slots to 0
    sem_init(&(buffer->bufferAccess), 0, 1); // Initialize buffer access semaphore
    return buffer;
}

bool isBufferFull(const Bounded_Buffer *buffer)
{
    return buffer->count == buffer->capacity;
}

bool isBufferEmpty(const Bounded_Buffer *buffer)
{
    return buffer->count == 0;
}

void destroy_Bounded_Buffer(Bounded_Buffer *buffer)
{
    free(buffer->buffer);
    free(buffer);
}

void insert_Bounded_Buffer(Bounded_Buffer *buffer, v4si v)
{
    sem_wait(&(buffer->empty));
    sem_wait(&(buffer->bufferAccess));

    buffer->rear = (buffer->rear + 1) % buffer->capacity;
    buffer->buffer[buffer->rear] = v;
    buffer->count++;

    sem_post(&(buffer->bufferAccess));
    sem_post(&(buffer->full));
}

v4si removeItem_Bounded_Buffer(Bounded_Buffer *buffer)
{
    if (sem_trywait(&(buffer->full)) != 0)
    {
        v4si returnValue = {ERROR_VALUE, ERROR_VALUE, ERROR_VALUE, ERROR_VALUE};
        return returnValue;
    }

    sem_wait(&(buffer->bufferAccess));

    v4si item = buffer->buffer[buffer->front];
    buffer->front = (buffer->front + 1) % buffer->capacity;
    buffer->count--;

    sem_post(&(buffer->bufferAccess));
    sem_post(&(buffer->empty));

    return item;
}

v4si top_Bounded_Buffer(const Bounded_Buffer *buffer)
{
    return buffer->buffer[buffer->front];
}

void print_Bounded_Buffer(const Bounded_Buffer *buffer)
{
    printf("Buffer elements: ");

    if (isBufferEmpty(buffer))
    {
        printf("Empty");
    }
    else
    {
        int current = buffer->front;
        int count = buffer->count;

        while (count > 0)
        {
            v4si data = buffer->buffer[current];
            printf("(%d, %d, %d, %d) ", data[0], data[1], data[2], data[3]);

            current = (current + 1) % buffer->capacity;
            count--;
        }
    }

    printf("\n");
}

#endif /* BOUNDED_BUFFER_H */
