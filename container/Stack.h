#ifndef __STACK_H__
#define __STACK_H__
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../dataType.h"
#include "../utility.h"

typedef struct{
    size_t length;
    size_t capacity;
    int type;
    int elemSize;
    void* value;
    void (*dealloc)(void*);
    void (*print)(void*);
}stack;

stack* initStack(int eleSize,void(*dealloc)(void*));
stack* intStack();
stack* doubleStack();
stack* floatStack();
stack* charStack();
stack* longStack();
stack* stringStack();

void pushStack(void * val,stack *s);
void pushStackAtIndex(void* val,size_t index, stack* s);

void popStack(void* val, stack *s);
void popStackAtIndex(void *val,size_t index,stack *s);

void getStackValueAtIndex(void* val, size_t index,stack *s);

void freeStack(stack *s);

bool stackEmpty(stack *s);

void printStack(stack* s);

void freeStringInStack(void* val);

void setStackDealloc(void (*dealloc)(void*),stack *s);

void setStackPrint(void (*print)(void*),stack *s);

#ifdef __cplusplus
};
#endif

#endif