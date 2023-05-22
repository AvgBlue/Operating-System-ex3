
#include "bounded_buffer.h"
#include <stdio.h>

int main()
{
    // Create a bounded buffer with a capacity of 5
    Bounded_Buffer *buffer = createBuffer(5);

    // Insert items into the buffer
    insert(buffer, "Item 1");
    insert(buffer, "Item 2");
    insert(buffer, "Item 3");
    insert(buffer, "Item 4");
    insert(buffer, "Item 5");
    insert(buffer, "Item 6");

    // Remove and print items from the buffer
    printf("Removed item: %s\n", removeItem(buffer));
    printf("Removed item: %s\n", removeItem(buffer));

    // Insert more items
    insert(buffer, "Item 7");
    insert(buffer, "Item 8");
    insert(buffer, "Item 9"); // Won't be inserted since the buffer is full

    // Remove and print remaining items
    printf("Removed item: %s\n", removeItem(buffer));
    printf("Removed item: %s\n", removeItem(buffer));
    printf("Removed item: %s\n", removeItem(buffer));
    printf("Removed item: %s\n", removeItem(buffer));
    printf("Removed item: %s\n", removeItem(buffer));
    printf("Removed item: %s\n", removeItem(buffer));

    // Destroy the buffer
    destroyBuffer(buffer);

    return 0;
}