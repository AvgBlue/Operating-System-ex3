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

#endif /* BOUNDED_BUFFER_H */
