#include "screen_manager.h"

Screen_Manager *createScreenManager(int bufferSize)
{
    Screen_Manager *screenManager = (Screen_Manager *)malloc(sizeof(Screen_Manager));
    if (screenManager == NULL)
    {
        return NULL;
    }
    screenManager->run = run_Screen_Manager;
    screenManager->buffer = create_Bounded_Buffer(bufferSize);
    if (screenManager->buffer == NULL)
    {
        free(screenManager);
        return NULL;
    }
    return screenManager;
}

void destroyScreenManager(Screen_Manager *screenManager)
{
    destroy_Bounded_Buffer(screenManager->buffer);
    free(screenManager);
}

void start_Screen_Managar(Screen_Manager *screenManager)
{
    int counter = 0;
    while (counter != 3)
    {
        v4si popValue = removeItem_Bounded_Buffer(screenManager->buffer);
        if (popValue[0] == DONE && popValue[1] == DONE && popValue[2] == DONE && popValue[3] == DONE)
        {
            counter++;
            continue;
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
    printf("DONE\n");
}

void *run_Screen_Manager(void *arg)
{
    Screen_Manager *screenManager = (Screen_Manager *)arg;
    start_Screen_Managar(screenManager);
    pthread_exit(NULL);
}