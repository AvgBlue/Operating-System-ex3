#ifndef UNBOUNDED_BUFFER_H
#define UNBOUNDED_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>

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

#endif /* UNBOUNDED_BUFFER_H */
