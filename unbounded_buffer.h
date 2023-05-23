#ifndef UNBOUNDED_BUFFER_H
#define UNBOUNDED_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef int v4si __attribute__((vector_size(16)));

typedef struct Node
{
    v4si data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    int count;
} Unbounded_Buffer;

Unbounded_Buffer *create_Unbounded_Buffer();
void destroy_Unbounded_Buffer(Unbounded_Buffer *buffer);
void insert_Unbounded_Buffer(Unbounded_Buffer *buffer, v4si s);
v4si removeItem_Unbounded_Buffer(Unbounded_Buffer *buffer);
bool isBufferEmpty_Unbounded_Buffer(const Unbounded_Buffer *buffer);

Unbounded_Buffer *create_Unbounded_Buffer()
{
    Unbounded_Buffer *buffer = (Unbounded_Buffer *)malloc(sizeof(Unbounded_Buffer));
    buffer->head = NULL;
    buffer->tail = NULL;
    buffer->count = 0;
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
}

v4si removeItem_Unbounded_Buffer(Unbounded_Buffer *buffer)
{
    if (buffer->head == NULL)
    {
        // todo to fix;
        v4si returnValue = {-1, -1, -1, -1};
        return returnValue;
    }

    Node *temp = buffer->head;
    v4si data = temp->data;

    buffer->head = buffer->head->next;
    buffer->count--;

    free(temp);
    return data;
}

bool isBufferEmpty_Unbounded_Buffer(const Unbounded_Buffer *buffer)
{
    return buffer->head == NULL;
}

v4si top_Unbounded_Buffer(const Unbounded_Buffer *buffer)
{
    Node *temp = buffer->head;
    v4si data = temp->data;
    return data;
}

#endif /* UNBOUNDED_BUFFER_H */
