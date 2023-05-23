#ifndef UNBOUNDED_BUFFER_H
#define UNBOUNDED_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *data;
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
void insert_Unbounded_Buffer(Unbounded_Buffer *buffer, const char *s);
char *removeItem_Unbounded_Buffer(Unbounded_Buffer *buffer);
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

void insert_Unbounded_Buffer(Unbounded_Buffer *buffer, char *s)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = s;
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

char *removeItem_Unbounded_Buffer(Unbounded_Buffer *buffer)
{
    if (buffer->head == NULL)
    {
        return NULL;
    }

    Node *temp = buffer->head;
    char *data = temp->data;

    buffer->head = buffer->head->next;
    buffer->count--;

    free(temp);
    return data;
}

bool isBufferEmpty_Unbounded_Buffer(const Unbounded_Buffer *buffer)
{
    return buffer->head == NULL;
}

#endif /* UNBOUNDED_BUFFER_H */
