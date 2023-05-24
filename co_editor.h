#ifndef CO_EDITOR_H
#define CO_EDITOR_H
#include "bounded_buffer.h"
#include "unbounded_buffer.h"
#include <pthread.h>

typedef struct
{
    void *(*run)(void *arg);
    Bounded_Buffer *bbOut;  // lender
    Unbounded_Buffer *ubIn; // lender
} Co_Editor;

Co_Editor *createCoEditor(Bounded_Buffer *b, Unbounded_Buffer *u);
void destroyCoEditor(Co_Editor *coEditor);
void *run_Co_Editor(void *arg);

Co_Editor *createCoEditor(Bounded_Buffer *b, Unbounded_Buffer *u)
{
    Co_Editor *coEditor = (Co_Editor *)malloc(sizeof(Co_Editor));
    coEditor->run = run_Co_Editor;
    coEditor->bbOut = b;
    coEditor->ubIn = u;
    return coEditor;
}

void destroyCoEditor(Co_Editor *coEditor)
{
    free(coEditor);
}

void start_Co_Editor(Co_Editor *coEditor)
{
    while (true)
    {
        v4si popValue = removeItem_Unbounded_Buffer(coEditor->ubIn);

        insert_Bounded_Buffer(coEditor->bbOut, popValue);
        if (popValue[0] == -99 && popValue[1] == -99 && popValue[2] == -99 && popValue[3] == -99)
        {
            break;
        }
    }
}

void *run_Co_Editor(void *arg)
{
    Co_Editor *coEditor = (Co_Editor *)arg;
    start_Co_Editor(coEditor);
    pthread_exit(NULL);
}

#endif /* CO_EDITOR_H */