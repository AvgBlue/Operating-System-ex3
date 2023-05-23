#ifndef CO_EDITOR_H
#define CO_EDITOR_H
#include "bounded_buffer.h"
#include "unbounded_buffer.h"

typedef struct
{
    Bounded_Buffer *bb;
    Unbounded_Buffer *ub;
} Co_Editor;

Co_Editor *createCoEditor(Bounded_Buffer *b, Unbounded_Buffer *u)
{
    Co_Editor *coEditor = (Co_Editor *)malloc(sizeof(Co_Editor));
    coEditor->bb = b;
    coEditor->ub = u;
    return coEditor;
}

#endif /* CO_EDITOR_H */