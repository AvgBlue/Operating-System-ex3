// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// typedef int v4si __attribute__((vector_size(16)));

// void printVector(v4si a)
// {
//     printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);
// }

// int main()
// {
//     v4si a = {1, 2, 3, 4};
//     printVector(a);

//     v4si arr[3] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
//     printVector(arr[0]);
//     v4si b = arr[1];
//     printVector(b + a);
//     if (a[0] == arr[0][0] && a[1] == arr[0][1] && a[2] == arr[0][2] && a[3] == arr[0][3])
//     {
//         printf("a==arr[0]\n");
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>

// char *formatString(int i, const char *type, int j)
// {
//     int bufferSize = snprintf(NULL, 0, "producer %d %s %d", i, type, j) + 1;
//     char *result = (char *)malloc(bufferSize * sizeof(char));

//     if (result != NULL)
//     {
//         snprintf(result, bufferSize, "producer %d %s %d", i, type, j);
//     }

//     return result;
// }

#include <stdio.h>
#include "bounded_buffer.h"

int main()
{
    // Create a bounded buffer of size 5
    Bounded_Buffer *buffer = create_Bounded_Buffer(5);

    // Insert some elements into the buffer
    v4si v1 = {1, 2, 3, 4};
    insert_Bounded_Buffer(buffer, v1);

    v4si v2 = {5, 6, 7, 8};
    insert_Bounded_Buffer(buffer, v2);

    v4si v3 = {9, 10, 11, 12};
    insert_Bounded_Buffer(buffer, v3);

    // Remove an element from the buffer
    v4si removed_item = removeItem_Bounded_Buffer(buffer);
    printf("Removed item: {%d, %d, %d, %d}\n",
           removed_item[0], removed_item[1], removed_item[2], removed_item[3]);
    removed_item = removeItem_Bounded_Buffer(buffer);
    printf("Removed item: {%d, %d, %d, %d}\n",
           removed_item[0], removed_item[1], removed_item[2], removed_item[3]);
    removed_item = removeItem_Bounded_Buffer(buffer);
    printf("Removed item: {%d, %d, %d, %d}\n",
           removed_item[0], removed_item[1], removed_item[2], removed_item[3]);
    removed_item = removeItem_Bounded_Buffer(buffer);
    printf("Removed item: {%d, %d, %d, %d}\n",
           removed_item[0], removed_item[1], removed_item[2], removed_item[3]);
    // Insert another element
    v4si v4 = {13, 14, 15, 16};
    insert_Bounded_Buffer(buffer, v4);

    // Check if the buffer is empty or full
    printf("Buffer empty? %s\n", isBufferEmpty(buffer) ? "Yes" : "No");
    printf("Buffer full? %s\n", isBufferFull(buffer) ? "Yes" : "No");

    // Destroy the buffer
    destroy_Bounded_Buffer(buffer);

    return 0;
}
