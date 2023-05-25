#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "unbounded_buffer.h"
#include "producer.h"
#include <pthread.h>

typedef struct
{
    void *(*run)(void *arg);
    Unbounded_Buffer *ubb_S;  // owenr
    Unbounded_Buffer *ubb_N;  // owenr
    Unbounded_Buffer *ubb_W;  // owner
    Bounded_Buffer **bb_list; // lender
    int bb_list_size;
} Dispatcher;

Dispatcher *createDispatcher(Producer **producers, int producersNum);
void destroyDispatcher(Dispatcher *dispatcher);
void *run_Dispatcher(void *arg);

#endif /* DISPATCHER_H */
