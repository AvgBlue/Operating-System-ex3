#include "unbounded_buffer.h"

Unbounded_Buffer *create_Unbounded_Buffer()
{
    Unbounded_Buffer *buffer = (Unbounded_Buffer *)malloc(sizeof(Unbounded_Buffer));
    if (buffer == NULL)
    {
        return NULL;
    }
    buffer->head = NULL;
    buffer->tail = NULL;
    buffer->count = 0;
    sem_init(&(buffer->mutex), 0, 1);
    sem_init(&(buffer->full), 0, 0);
    return buffer;
}

void destroy_Unbounded_Buffer(Unbounded_Buffer *buffer)
{
    while (buffer->head != NULL)
    {
        Node *temp = buffer->head;
        buffer->head = buffer->head->next;
        free(temp);
    }
    free(buffer);
}

void insert_Unbounded_Buffer(Unbounded_Buffer *buffer, v4si v)
{
    sem_wait(&(buffer->mutex));
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = NULL;

    if (buffer->head == NULL)
    {
        buffer->head = newNode;
        buffer->tail = newNode;
    }
    else
    {
        buffer->tail->next = newNode;
        buffer->tail = newNode;
    }

    buffer->count++;
    sem_post(&(buffer->mutex));
    sem_post(&(buffer->full));
}

v4si removeItem_Unbounded_Buffer(Unbounded_Buffer *buffer)
{
    if (sem_trywait(&(buffer->full)) != 0)
    {
        v4si returnValue = {ERROR_VALUE, ERROR_VALUE, ERROR_VALUE, ERROR_VALUE};
        return returnValue;
    }
    sem_wait(&(buffer->mutex));
    Node *temp = buffer->head;
    v4si data = temp->data;

    buffer->head = buffer->head->next;
    buffer->count--;

    free(temp);
    sem_post(&(buffer->mutex));
    return data;
}