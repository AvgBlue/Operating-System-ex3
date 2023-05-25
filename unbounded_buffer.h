#ifndef UNBOUNDED_BUFFER_H
#define UNBOUNDED_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int v4si __attribute__((vector_size(16)));
#define ERROR_VALUE -1

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
    sem_t mutex;
    sem_t full;
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

// void insert_Unbounded_Buffer(Unbounded_Buffer *buffer, v4si v)
// {
//     Node *newNode = (Node *)malloc(sizeof(Node));
//     newNode->data = v;
//     newNode->next = NULL;

//     if (buffer->head == NULL)
//     {
//         buffer->head = newNode;
//         buffer->tail = newNode;
//     }
//     else
//     {
//         buffer->tail->next = newNode;
//         buffer->tail = newNode;
//     }

//     buffer->count++;
// }

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

// v4si removeItem_Unbounded_Buffer(Unbounded_Buffer *buffer)
// {
//     if (buffer->head == NULL)
//     {
//         // todo to fix;
//         v4si returnValue = {-1, -1, -1, -1};
//         return returnValue;
//     }

//     Node *temp = buffer->head;
//     v4si data = temp->data;

//     buffer->head = buffer->head->next;
//     buffer->count--;

//     free(temp);
//     return data;
// }

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

void print_Unbounded_Buffer(const Unbounded_Buffer *buffer)
{
    printf("Buffer elements: ");

    if (isBufferEmpty_Unbounded_Buffer(buffer))
    {
        printf("Empty");
    }
    else
    {
        Node *current = buffer->head;

        while (current != NULL)
        {
            v4si data = current->data;
            printf("(%d, %d, %d, %d) ", data[0], data[1], data[2], data[3]);
            current = current->next;
        }
    }

    printf("\n");
}

#endif /* UNBOUNDED_BUFFER_H */
