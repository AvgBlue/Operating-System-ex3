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

int readData(char *filename, Producer **producers, int num_producers, int *co_editor_queue_size)
{
    FILE *fileptr;
    fileptr = fopen(filename, "r");
    if (fileptr == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    int result; // Variable to store the return value of fscanf

    for (int i = 0; i < num_producers; i++)
    {
        int producerId, productsNum, queueSize;
        result = fscanf(fileptr, "%d", &producerId);
        if (result != 1)
        {
            printf("Failed to read producerId from file.\n");
            fclose(fileptr);
            return 1;
        }

        result = fscanf(fileptr, "%d", &productsNum);
        if (result != 1)
        {
            printf("Failed to read productsNum from file.\n");
            fclose(fileptr);
            return 1;
        }

        result = fscanf(fileptr, "%d", &queueSize);
        if (result != 1)
        {
            printf("Failed to read queueSize from file.\n");
            fclose(fileptr);
            return 1;
        }

        producers[i] = createProduct(producerId - 1, productsNum, queueSize);
        if (producers[i] == NULL)
        {
            printf("malloc failed\n");
            // free distroy everything that was make before go back from i to 0 and free everything
            for (int j = i; j >= 0; j--)
            {
                destroyProducer(producers[j]);
            }
            fclose(fileptr);
            return 1;
        }
    }

    result = fscanf(fileptr, "%d", co_editor_queue_size);
    if (result != 1)
    {
        printf("Failed to read co_editor_queue_size from file.\n");
        fclose(fileptr);
        return 1;
    }
    fclose(fileptr);
    return 0;
}
