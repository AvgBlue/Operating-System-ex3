#include "bounded_buffer.h"

Bounded_Buffer *create_Bounded_Buffer(int size)
{
    Bounded_Buffer *buffer = (Bounded_Buffer *)malloc(sizeof(Bounded_Buffer));
    if (buffer == NULL)
    {
        return NULL;
    }
    buffer->buffer = (v4si *)malloc(sizeof(v4si) * size);
    if (buffer->buffer == NULL)
    {
        free(buffer);
        return NULL;
    }
    buffer->capacity = size;
    buffer->front = 0;
    buffer->rear = -1;
    buffer->count = 0;
    sem_init(&(buffer->empty), 0, size);     // Initialize empty slots to capacity
    sem_init(&(buffer->full), 0, 0);         // Initialize occupied slots to 0
    sem_init(&(buffer->bufferAccess), 0, 1); // Initialize buffer access semaphore
    return buffer;
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