#ifndef __LINKLIST_H__
#define __LINKLIST_H__
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
typedef struct LinklistCell{
    void* value;
    struct LinklistCell* next;
    struct LinklistCell* prev;
}linklistcell;

typedef struct{
    size_t length;
    int type;
    int elemSize;
    linklistcell* firstCell;
    linklistcell* lastCell;
    void (*dealloc)(void*);
    void (*print)(void*);
}linklist;

linklist* initList(int eleSize, void (*dealloc)(void*));
linklist* intlinklist();
linklist* doublelinklist();
linklist* floatlinklist();
linklist* charlinklist();
linklist* longlinklist();
linklist* stringlinklist();

void appendToList(void* value, linklist* list);
void appendToListAtIndex(void* value,size_t index,linklist* list);

int popListFront(void* value,linklist* list);
int popList(void* value,linklist* list);
int popFromListAtIndex(void* value,size_t index,linklist* list);

int getListValueAtIndex(void* value,size_t index,linklist* list);

void freeList(linklist* list);

bool listEmpty(linklist* list);

void printList(linklist* list);

void freeStringList(void* val);

void setListDealloc(void (*dealloc)(void*),linklist *list);
void setListPrint(void (*print)(void*),linklist *list);


#ifdef __cplusplus
};
#endif

#endif