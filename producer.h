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

char *formatString(int i, const char *type, int j)
{
    int bufferSize = snprintf(NULL, 0, "producer %d %s %d", i, type, j) + 1;
    char *result = (char *)malloc(bufferSize * sizeof(char));

    if (result != NULL)
    {
        snprintf(result, bufferSize, "producer %d %s %d", i, type, j);
    }

    return result;
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
        char *product;
        switch (randomNum)
        {
        case 1:
            product = formatString(producer->id, "SPORTS", S_num++);
            break;
        case 2:
            product = formatString(producer->id, "WEATHER", W_num++);
            break;
        case 3:
            product = formatString(producer->id, "NEWS", N_num++);
            break;
        default:
            break;
        };
        insert_Bounded_Buffer(producer->buffer, product);
    }
    char *Done = (char *)malloc(sizeof(char) * 6);
    strcpy(Done, "Done");
    insert_Bounded_Buffer(producer->buffer, Done);
}

#endif /* PRODUCER_H */