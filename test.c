#include <stdio.h>
#include "producer.h"

int main()
{
    // Create a producer with id 1, producing 5 products, and a queue size of 10
    Producer *producer = createProduct(1, 5, 10);

    // Initialize the random number generator
    initializeRandomNumberGenerator();

    // Start the producer
    startProducer(producer);

    // Retrieve and print the items from the buffer
    while (!isBufferEmpty(producer->buffer))
    {
        v4si item = removeItem_Bounded_Buffer(producer->buffer);
        printf("Item: %d %d %d %d\n", item[0], item[1], item[2], item[3]);
    }

    // Destroy the producer
    destroyProducer(producer);

    return 0;
}
