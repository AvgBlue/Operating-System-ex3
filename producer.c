#include "producer.h"
#include <time.h>

Producer *createProduct(int producerId, int productsNum, int size)
{
    Producer *producer = (Producer *)malloc(sizeof(Producer));
    if (producer == NULL)
    {
        return NULL;
    }
    producer->run = run_Producer;
    producer->id = producerId;
    producer->numProducts = productsNum;
    producer->queueSize = size;
    producer->buffer = create_Bounded_Buffer(size);
    if (producer->buffer == NULL)
    {
        free(producer);
        return NULL;
    }
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

void start_Producer(Producer *producer)
{
    initializeRandomNumberGenerator();
    int S_num = 0;
    int W_num = 0;
    int N_num = 0;

    for (int i = 0; i < producer->numProducts; i++)
    {
        int randomNum = getRandomNumber(1, 3);
        v4si product;
        switch (randomNum)
        {
        case SPORTS:
            product = (v4si){producer->id, randomNum, S_num++, 0};
            break;
        case WEATHER:
            product = (v4si){producer->id, randomNum, W_num++, 0};
            break;
        case NEWS:
            product = (v4si){producer->id, randomNum, N_num++, 0};
            break;
        default:
            break;
        };
        insert_Bounded_Buffer(producer->buffer, product);
    }
    // todo to fix
    v4si done = {DONE, DONE, DONE, DONE};
    insert_Bounded_Buffer(producer->buffer, done);
}

void *run_Producer(void *arg)
{
    Producer *producer = (Producer *)arg;
    start_Producer(producer);
    pthread_exit(NULL);
}