#ifndef RUNNABLE_H
#define RUNNABLE_H

typedef struct
{
    void *(*run)(void *arg);
} Runnable;

#endif /* RUNNABLE_H */