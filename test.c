#include <stdio.h>
#include "unbounded_buffer.h"

int main()
{
    Unbounded_Buffer *buffer = createBuffer();

    insert(buffer, "Item 1");
    insert(buffer, "Item 2");
    insert(buffer, "Item 3");
    insert(buffer, "Item 4");
    insert(buffer, "Item 5");
    insert(buffer, "Item 6");
    insert(buffer, "Item 7");
    insert(buffer, "Item 8");
    insert(buffer, "Item 9");

    printf("Buffer is empty: %s\n", isBufferEmpty(buffer) ? "true" : "false");

    while (!isBufferEmpty(buffer))
    {
        char *item = removeItem(buffer);
        printf("Removed item: %s\n", item);
        free(item);
    }

    printf("Buffer is empty: %s\n", isBufferEmpty(buffer) ? "true" : "false");

    destroyBuffer(buffer);

    return 0;
}
