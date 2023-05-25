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

#endif /* CO_EDITOR_H */