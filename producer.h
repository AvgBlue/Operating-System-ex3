#ifndef PRODUCER_H
#define PRODUCER_H

#include "bounded_buffer.h"
#include <time.h>

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
    producer->buffer = create_Bounded_Buffer(size);
    return producer;
}

void destroyProducer(Producer *producer)
{
    destroy_Bounded_Buffer(producer->buffer);
    free(producer);
}

void initializeRandomNumberGenerator()
{
    // Initialize random number generator with current time as seed
    srandom(time(NULL));
}

int getRandomNumber(int min, int max)
{
    // Generate random number within the specified range
    int randomNumber = (random() % (max - min + 1)) + min;
    return randomNumber;
}


void startProducer(Producer *producer)
{
    // num is 1
    int S_num = 0;
    // num is 2
    int W_num = 0;
    // num is 3
    int N_num = 0;

    for (int i = 0; i < producer->numProducts; i++)
    {
        int randomNum = getRandomNumber(1, 3);
        v4si product;
        switch (randomNum)
        {
        case 1:
            product = (v4si){producer->id,randomNum,S_num++,0};
            break;
        case 2:
            product = (v4si){producer->id,randomNum,W_num++,0};
            break;
        case 3:
            product = (v4si){producer->id,randomNum,N_num++,0};
            break;
        default:
            break;
        };
        insert_Bounded_Buffer(producer->buffer, product);
    }
    //todo to fix
    v4si Done = {-99,-99,-99,-99};
    insert_Bounded_Buffer(producer->buffer, Done);
}

#endif /* PRODUCER_H */