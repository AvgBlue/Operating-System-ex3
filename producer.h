#ifndef PRODUCER_H
#define PRODUCER_H

#include "bounded_buffer.h"
#include <pthread.h>

#define SPORTS 1
#define WEATHER 2
#define NEWS 3
#define DONE -99

typedef struct
{
    void *(*run)(void *arg);
    int id;
    int numProducts;
    int queueSize;
    Bounded_Buffer *buffer; // owner
} Producer;

Producer *createProduct(int producerId, int productsNum, int size);
void destroyProducer(Producer *producer);
void *run_Producer(void *arg);

#endif /* PRODUCER_H */