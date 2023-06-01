#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
#include "bounded_buffer.h"
#include "producer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define DONE -99
typedef struct
{
    void *(*run)(void *arg);
    Bounded_Buffer *buffer; // owner
} Screen_Manager;

Screen_Manager *createScreenManager(int bufferSize);
void destroyScreenManager(Screen_Manager *screenManager);
void *run_Screen_Manager(void *arg);
void start_Screen_Managar(Screen_Manager *screenManager);

#endif /* SCREEN_MANAGER_H */