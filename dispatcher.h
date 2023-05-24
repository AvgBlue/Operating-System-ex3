#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <stdio.h>
#include "bounded_buffer.h"
#include "unbounded_buffer.h"
#include "producer.h"

typedef struct
{
    Unbounded_Buffer *ubb_S;  // owenr
    Unbounded_Buffer *ubb_N;  // owenr
    Unbounded_Buffer *ubb_W;  // owner
    Bounded_Buffer **bb_list; // lender
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
        dispatcher->bb_list[i] = producers[i]->buffer;
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

void start_Dispatcher(Dispatcher *dispatcher)
{
    int doneNum = 0;
    while (doneNum != dispatcher->bb_list_size)
    {
        for (int i = 0; i < dispatcher->bb_list_size; i++)
        {
            // the buffer is empty and the producer is not done
            if (isBufferEmpty(dispatcher->bb_list[i]))
            {
                continue;
            }
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
            case 0:
                insert_Unbounded_Buffer(dispatcher->ubb_S, popValue);
                break;
            case 1:
                insert_Unbounded_Buffer(dispatcher->ubb_W, popValue);
                break;
            case 2:
                insert_Unbounded_Buffer(dispatcher->ubb_N, popValue);
                break;
            default:
                break;
            }
            v4si done = {-99, -99, -99, -99};
            insert_Unbounded_Buffer(dispatcher->ubb_S, done);
            insert_Unbounded_Buffer(dispatcher->ubb_W, done);
            insert_Unbounded_Buffer(dispatcher->ubb_N, done);
        }
    }
}

#endif /* DISPATCHER_H */
