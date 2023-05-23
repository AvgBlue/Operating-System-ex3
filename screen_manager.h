#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
#include "bounded_buffer.h"

typedef struct
{
    Bounded_Buffer *buffer;
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

#endif /* SCREEN_MANAGER_H */