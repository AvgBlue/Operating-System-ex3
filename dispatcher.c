#include "dispatcher.h"

Dispatcher *createDispatcher(Producer **producers, int producersNum)
{
    Dispatcher *dispatcher = (Dispatcher *)malloc(sizeof(Dispatcher));
    if (dispatcher == NULL)
    {
        return NULL;
    }
    dispatcher->run = run_Dispatcher;
    dispatcher->ubb_S = create_Unbounded_Buffer();
    if (dispatcher->ubb_S == NULL)
    {
        goto ubb_S_fail;
    }
    dispatcher->ubb_N = create_Unbounded_Buffer();
    if (dispatcher->ubb_N == NULL)
    {
        goto ubb_N_fail;
    }
    dispatcher->ubb_W = create_Unbounded_Buffer();
    if (dispatcher->ubb_N == NULL)
    {
        goto ubb_W_fail;
    }
    dispatcher->bb_list_size = producersNum;
    dispatcher->bb_list = (Bounded_Buffer **)malloc(sizeof(Bounded_Buffer *) * producersNum);
    if (dispatcher->bb_list == NULL)
    {
        goto bb_list_fail;
    }
    for (int i = 0; i < producersNum; i++)
    {
        dispatcher->bb_list[i] = producers[i]->buffer;
    }
    return dispatcher;
bb_list_fail:
    destroy_Unbounded_Buffer(dispatcher->ubb_W);
ubb_W_fail:
    destroy_Unbounded_Buffer(dispatcher->ubb_N);
ubb_N_fail:
    destroy_Unbounded_Buffer(dispatcher->ubb_S);
ubb_S_fail:
    free(dispatcher);
    return NULL;
};

void destroyDispatcher(Dispatcher *dispatcher)
{
    destroy_Unbounded_Buffer(dispatcher->ubb_S);
    destroy_Unbounded_Buffer(dispatcher->ubb_N);
    destroy_Unbounded_Buffer(dispatcher->ubb_W);
    free(dispatcher);
}

void start_Dispatcher(Dispatcher *dispatcher)
{
    int doneNum = 0;
    while (doneNum != dispatcher->bb_list_size)
    {
        for (int i = 0; i < dispatcher->bb_list_size; i++)
        {
            // check if the producer is done
            v4si popValue = removeItem_Bounded_Buffer(dispatcher->bb_list[i]);
            if (popValue[0] == -99 && popValue[1] == -99 && popValue[2] == -99 && popValue[3] == -99)
            {
                doneNum++;
                continue;
            }
            // we send to the unbounded buffers
            switch (popValue[1])
            {
            case SPORTS:
                insert_Unbounded_Buffer(dispatcher->ubb_S, popValue);
                break;
            case WEATHER:
                insert_Unbounded_Buffer(dispatcher->ubb_W, popValue);
                break;
            case NEWS:
                insert_Unbounded_Buffer(dispatcher->ubb_N, popValue);
                break;
            default:
                break;
            }
        }
    }
    v4si done = {-99, -99, -99, -99};
    insert_Unbounded_Buffer(dispatcher->ubb_S, done);
    insert_Unbounded_Buffer(dispatcher->ubb_W, done);
    insert_Unbounded_Buffer(dispatcher->ubb_N, done);
}

void *run_Dispatcher(void *arg)
{
    Dispatcher *dispatcher = (Dispatcher *)arg;
    start_Dispatcher(dispatcher);
    pthread_exit(NULL);
}