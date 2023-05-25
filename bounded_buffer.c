#include "bounded_buffer.h"

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