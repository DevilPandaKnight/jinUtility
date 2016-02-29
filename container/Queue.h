#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../dataType.h"
#include "../utility.h"

typedef struct QueueCell{
    void* value;
    struct QueueCell* next;
}queueCell;

typedef struct{
    size_t length;
    int type;
    int elemSize;
    queueCell* firstCell;
    queueCell* lastCell;
    void (*dealloc)(void*);
    void (*print)(void*);
}queue;

queue* initQueue(int eleSize, void (*dealloc)(void*));
queue* intQueue();
queue* doubleQueue();
queue* floatQueue();
queue* charQueue();
queue* longQueue();
queue* stringQueue();

void pushQueue(void * val,queue *q);
size_t dequeue(void* val, queue *q);

void freeQueue(queue *q);

bool queueEmpty(queue *q);

void printQueue(queue* q);

void freeStringInQueue(void* val);

void setQueueDealloc(void (*dealloc)(void*),queue *q);

void setQueuePrint(void (*print)(void*),queue *q);


#ifdef __cplusplus
};
#endif

#endif