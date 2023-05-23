#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "bounded_buffer.h"
#include "unbounded_buffer.h"
#include "producer.h"

typedef struct
{
    Unbounded_Buffer *ubb_S;
    Unbounded_Buffer *ubb_N;
    Unbounded_Buffer *ubb_W;
    Bounded_Buffer **bb_list;
    int bb_list_size;
} Dispatcher;

Dispatcher *createDispatcher(Producer **producers, int producersNum)
{
    Dispatcher *dispatcher = (Dispatcher *)malloc(sizeof(Dispatcher));
    dispatcher->ubb_S = create_Unbounded_Buffer();
    dispatcher->ubb_N = create_Unbounded_Buffer();
    dispatcher->ubb_W = create_Unbounded_Buffer();
    dispatcher->bb_list_size = producersNum;
    dispatcher->bb_list = (Bounded_Buffer **)malloc(sizeof(Bounded_Buffer *) * producersNum);
    for (int i = 0; i < producersNum; i++)
    {
        dispatcher->bb_list[i] = create_Bounded_Buffer(producers[i]->queueSize);
    }
    return dispatcher;
};

void destroyDispatcher(Dispatcher *dispatcher)
{
    destroy_Unbounded_Buffer(dispatcher->ubb_S);
    destroy_Unbounded_Buffer(dispatcher->ubb_N);
    destroy_Unbounded_Buffer(dispatcher->ubb_W);
    free(dispatcher);
}

#endif /* DISPATCHER_H */
