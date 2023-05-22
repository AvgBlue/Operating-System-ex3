#ifndef PRODUCER_H
#define PRODUCER_H

#include "bounded_buffer.h"

typedef struct
{
    int numProducts;
    int queueSize;
    Bounded_Buffer *buffer;
} Product;

Product *createProduct(int size)
{
    Product *product = (Product *)malloc(sizeof(Product));
    product->numProducts = 0;
    product->queueSize = size;
    product->buffer = createBuffer(size);
    return product;
}

#endif /* PRODUCER_H */