#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
#include "bounded_buffer.h"
#include "producer.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    Bounded_Buffer *buffer; // owner
} Screen_Manager;

Screen_Manager *createScreenManager(int bufferSize)
{
    Screen_Manager *screenManager = (Screen_Manager *)malloc(sizeof(Screen_Manager));
    screenManager->buffer = create_Bounded_Buffer(bufferSize);
    return screenManager;
}

void destroyScreenManager(Screen_Manager *screenManager)
{
    destroy_Bounded_Buffer(screenManager->buffer);
    free(screenManager);
}

void start_Screen_Managar(Screen_Manager *screenManager)
{
    while (true)
    {
        v4si popValue = removeItem_Bounded_Buffer(screenManager->buffer);
        if (popValue[0] == -99 && popValue[1] == -99 && popValue[2] == -99 && popValue[3] == -99)
        {
            printf("DONE\n");
            break;
        }
        switch (popValue[1])
        {
        case SPORTS:
            printf("Producer %d  SPORTS  %d\n", popValue[0], popValue[2]);
            break;
        case WEATHER:
            printf("Producer %d  WEATHER  %d\n", popValue[0], popValue[2]);
            break;
        case NEWS:
            printf("Producer %d  NEWS  %d\n", popValue[0], popValue[2]);
            break;
        default:
            break;
        }
    }
}

#endif /* SCREEN_MANAGER_H */