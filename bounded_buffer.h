#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_VALUE -1
typedef int v4si __attribute__((vector_size(16)));

typedef struct
{
    v4si *buffer; // Buffer array
    int capacity; // Maximum capacity of the buffer
    int front;    // Index of the front item
    int rear;     // Index of the rear item
    int count;    // Current number of items in the buffer
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
    if (isBufferFull(buffer))
    {
        // Buffer is full, cannot insert
        return;
    }
    buffer->rear = (buffer->rear + 1) % buffer->capacity;
    buffer->buffer[buffer->rear] = v;
    buffer->count = buffer->count + 1;
}

v4si removeItem_Bounded_Buffer(Bounded_Buffer *buffer)
{

    if (isBufferEmpty(buffer))
    {
        // Buffer is empty, nothing to remove
        v4si returnValue = {ERROR_VALUE, ERROR_VALUE, ERROR_VALUE, ERROR_VALUE};
        return returnValue;
    }

    v4si item = buffer->buffer[buffer->front];
    buffer->front = (buffer->front + 1) % buffer->capacity;
    buffer->count--;

    return item;
}

v4si top_Bounded_Buffer(const Bounded_Buffer *buffer)
{
    return buffer->buffer[buffer->front];
}

#endif /* BOUNDED_BUFFER_H */
