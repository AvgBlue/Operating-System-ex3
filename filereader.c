#include "filereader.h"

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