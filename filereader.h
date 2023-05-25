#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <stdlib.h>
#include "producer.h"

int linesCount(char *filename);
void readData(char *filename, Producer **producers, int num_producers, int *co_editor_queue_size);

#endif // FILE_READER_H
