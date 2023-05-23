#ifndef PRODUCER_H
#define PRODUCER_H

#include "bounded_buffer.h"

typedef struct
{
    int id;
    int numProducts;
    int queueSize;
    Bounded_Buffer *buffer;
} Producer;

Producer *createProduct(int producerId, int productsNum, int size)
{
    Producer *producer = (Producer *)malloc(sizeof(Producer));
    producer->id = producerId;
    producer->numProducts = productsNum;
    producer->queueSize = size;
    producer->buffer = createBuffer(size);
    return producer;
}

#endif /* PRODUCER_H */