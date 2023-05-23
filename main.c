#include <stdio.h>
#include <stdlib.h>
#include "producer.h"

int linesCount(char *filename)
{
    FILE *fileptr;
    int count_lines = 0;
    char chr;
    fileptr = fopen(filename, "r");
    if (fileptr == NULL)
    {
        printf("Failed to open the file.\n");
        exit(1);
    }

    while ((chr = fgetc(fileptr)) != EOF)
    {
        if (chr == '\n')
        {
            count_lines++;
        }
    }
    fclose(fileptr);
    return count_lines;
}

void readData(char *filename, Producer **producers, int num_producers, int *co_editor_queue_size)
{
    FILE *fileptr;
    fileptr = fopen(filename, "r");
    if (fileptr == NULL)
    {
        printf("Failed to open the file.\n");
        exit(1);
    }

    for (int i = 0; i < num_producers; i++)
    {
        int producerId, productsNum, queueSize;
        fscanf(fileptr, "%d", &producerId);
        fscanf(fileptr, "%d", &productsNum);
        fscanf(fileptr, "%d", &queueSize);
        producers[i] = createProduct(producerId, productsNum, queueSize);
    }

    fscanf(fileptr, "%d", co_editor_queue_size);

    fclose(fileptr);
}

int main()
{
    char *filename = "conf.txt";
    int num_producers = linesCount(filename) / 4;
    Producer **producers = malloc(num_producers * sizeof(Producer *));
    int co_editor_queue_size = 0;

    readData(filename, producers, num_producers, &co_editor_queue_size);

    // Access the data in the producers array and co-editor queue size as needed
    for (int i = 0; i < num_producers; i++)
    {
        printf("Producer ID: %d\n", producers[i]->id);
        printf("Number of Products: %d\n", producers[i]->numProducts);
        printf("Queue Size: %d\n\n", producers[i]->queueSize);
    }
    printf("Co-Editor Queue Size: %d\n", co_editor_queue_size);

    // Free memory for producers and their buffers
    for (int i = 0; i < num_producers; i++)
    {
        free(producers[i]->buffer);
        free(producers[i]);
    }
    free(producers);

    return 0;
}
