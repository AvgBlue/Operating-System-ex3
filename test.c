#include <stdio.h>
#include "unbounded_buffer.h"

int main()
{
    Unbounded_Buffer *buffer = create_Unbounded_Buffer();

    insert_Unbounded_Buffer(buffer, "Item 1");
    insert_Unbounded_Buffer(buffer, "Item 2");
    insert_Unbounded_Buffer(buffer, "Item 3");
    insert_Unbounded_Buffer(buffer, "Item 4");
    insert_Unbounded_Buffer(buffer, "Item 5");
    insert_Unbounded_Buffer(buffer, "Item 6");
    insert_Unbounded_Buffer(buffer, "Item 7");
    insert_Unbounded_Buffer(buffer, "Item 8");
    insert_Unbounded_Buffer(buffer, "Item 9");

    printf("Buffer is empty: %s\n", isBufferEmpty_Unbounded_Buffer(buffer) ? "true" : "false");

    while (!isBufferEmpty_Unbounded_Buffer(buffer))
    {
        char *item = removeItem_Unbounded_Buffer(buffer);
        printf("Removed item: %s\n", item);
        free(item);
    }

    printf("Buffer is empty: %s\n", isBufferEmpty_Unbounded_Buffer(buffer) ? "true" : "false");

    destroy_Unbounded_Buffer(buffer);

    return 0;
}
