#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **buffer;    // Buffer array
    int capacity;     // Maximum capacity of the buffer
    int front;        // Index of the front item
    int rear;         // Index of the rear item
    int count;        // Current number of items in the buffer
} Bounded_Buffer;

// Function prototypes
Bounded_Buffer* createBuffer(int size);
void destroyBuffer(Bounded_Buffer *buffer);
void insert(Bounded_Buffer *buffer, const char *s);
char* removeItem(Bounded_Buffer *buffer);


Bounded_Buffer *createBuffer(int size)
{
    Bounded_Buffer *buffer = (Bounded_Buffer *)malloc(sizeof(Bounded_Buffer));
    buffer->buffer = (char **)malloc(sizeof(char *) * size);
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

void destroyBuffer(Bounded_Buffer *buffer)
{
    free(buffer->buffer);
    free(buffer);
}

void insert(Bounded_Buffer *buffer, const char *s)
{
    if (isBufferFull(buffer))
    {
        // Buffer is full, cannot insert
        return;
    }

    int length = strlen(s) + 1; // Include null terminator
    char *item = (char *)malloc(sizeof(char) * length);
    strcpy(item, s);

    buffer->rear = (buffer->rear + 1) % buffer->capacity;
    buffer->buffer[buffer->rear] = item;
    buffer->count++;
}

char *removeItem(Bounded_Buffer *buffer)
{
    if (isBufferEmpty(buffer))
    {
        // Buffer is empty, nothing to remove
        return NULL;
    }

    char *item = buffer->buffer[buffer->front];
    buffer->front = (buffer->front + 1) % buffer->capacity;
    buffer->count--;

    return item;
}

#endif  /* BOUNDED_BUFFER_H */
