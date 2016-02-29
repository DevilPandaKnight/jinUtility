#include "LinkList.h"

linklist* initList(int eleSize, void (*dealloc)(void*)){
    linklist* temp = cnew(linklist);
    assert(temp!=NULL);
    temp->length = 0;
    temp->type = nullType;
    temp->elemSize = eleSize;
    temp->firstCell = NULL;
    temp->lastCell = NULL;
    temp->dealloc = dealloc;
    temp->print = NULL;
    return temp;
}


#define initWithType(t) initList(sizeof(t), NULL);

linklist* intlinklist(){
    linklist* l = initWithType(int);
    l->type = intType;
    return l;
}

linklist* doublelinklist(){
    linklist* l = initWithType(double);
    l->type = doubleType;
    return l;
}

linklist* floatlinklist(){
    linklist* l = initWithType(float);
    l->type = floatType;
    return l;
}

linklist* charlinklist(){
    linklist* l = initWithType(char);
    l->type = charType;
    return l;
}

linklist* longlinklist(){
    linklist* l = initWithType(int);
    l->type = intType;
    return l;
}
linklist* stringlinklist(){
    linklist* l = initList(sizeof(char*), freeStringList);
    l->type = stringType;
    return l;
}


void freeStringList(void* val){
    free(*((char**)val));
}

void appendToList(void* value, linklist* list){
    linklistcell* temp = cnew(linklistcell);
    assert(temp!=NULL);
    temp->value = malloc(list->elemSize);
    assert(temp->value!=NULL);
    memcpy(temp->value, value, list->elemSize);
    temp->next = NULL;
    if (list->lastCell) {
        list->lastCell->next = temp;
        temp->prev = list->lastCell;
    }
    list->lastCell = temp;
    
    if (!list->firstCell) {
        list->firstCell = temp;
        temp->prev = NULL;
    }
    list->length++;
}

#define checkIndex if (index > list->length) {printf("index out of range.\n");return;}
linklistcell* getCellAtIndex(size_t index,linklist* list){
    if (index >= list->length) {
        return NULL;
    }
    size_t mid = list->length / 2;
    linklistcell* cell;
    if (index <= mid) {
        cell = list->firstCell;
        for (size_t i = 0; i<index; i++) {
            cell = cell->next;
        }
    }
    else {
        cell = list->lastCell;
        for (size_t i = list->length - 1;i>index;i--) {
            cell = cell->prev;
        }
    }
    return cell;
}


void appendToListAtIndex(void* value,size_t index,linklist* list){
    if (index == list->length) {
        appendToList(value, list);
        return;
    }
    linklistcell* indexCell;
    if((indexCell = getCellAtIndex(index, list)) == NULL){printf("index out of range.\n");return;}
    linklistcell* temp = cnew(linklistcell);
    assert(temp!=NULL);
    temp->value = malloc(list->elemSize);
    assert(temp->value!=NULL);
    memcpy(temp->value, value, list->elemSize);
    
    temp->next = indexCell;
    temp->prev = indexCell->prev;
    
    if (indexCell->prev) {
        indexCell->prev->next = temp;
    }
    else{
        list->firstCell = temp;
    }
    indexCell->prev = temp;
    list->length++;
}

int popListFront(void* value,linklist* list){
    cRaise(list->length == 0, "empty list.");
    if (list->firstCell == list->lastCell) {
        list->lastCell = NULL;
    }
    linklistcell* cell = list->firstCell;
    list->firstCell = cell->next;
    if (cell->next) {
        cell->next->prev = NULL;
    }
    memcpy(value, cell->value, list->elemSize);
    free(cell->value);
    free(cell);
    list->length--;
    return 1;
}

int popList(void* value,linklist* list){
    cRaise(list->length==0, "empty list.");
    if (list->firstCell == list->lastCell) {
        list->firstCell = NULL;
    }
    linklistcell* cell = list->lastCell;
    list->lastCell = cell->prev;
    if (cell->prev) {
        cell->prev->next = NULL;
    }
    memcpy(value, cell->value, list->elemSize);
    free(cell->value);
    free(cell);
    list->length--;
    return 1;
}

int popFromListAtIndex(void* value,size_t index,linklist* list){
    linklistcell* indexCell = getCellAtIndex(index, list);
    if (indexCell==NULL) {printf("index out of range.\n");return 0;}
    
    if (indexCell->next) {
        indexCell->next->prev = indexCell->prev;
    }
    
    if (indexCell->prev) {
        indexCell->prev->next = indexCell->next;
    }
    
    if (indexCell == list->firstCell) {
        list->firstCell = indexCell->next;
    }
    
    if (indexCell == list->lastCell) {
        list->lastCell = indexCell->prev;
    }
    
    memcpy(value, indexCell->value, list->elemSize);
    free(indexCell->value);
    free(indexCell);
    list->length--;
    return 1;
}

int getListValueAtIndex(void* value,size_t index,linklist* list){
    linklistcell* indexCell = getCellAtIndex(index, list);
    if (indexCell==NULL) {printf("index out of range.\n");return 0;}
    memcpy(value, indexCell->value, list->elemSize);
    return 1;
}

void freeList(linklist* list){
    linklistcell* cell = list->firstCell;
    linklistcell* temp;
    if (list->dealloc) {
        while (cell) {
            temp = cell;
            cell = temp->next;
            list->dealloc(temp->value);
            free(temp->value);
            free(temp);
        }
    }
    else{
        while (cell) {
            temp = cell;
            cell = temp->next;
            free(temp->value);
            free(temp);
        }
    }
    free(list);
}

bool listEmpty(linklist* list){
    return list->length == 0;
}


void printList(linklist* list){
    if (list->length == 0) {
        printf("empty list.\n");
        return;
    }
    linklistcell* cell = list->firstCell;
    if (list->print) {
        while (cell) {
            list->print(cell->value);
            cell = cell->next;
        }
    }
    else{
        while (cell) {
            printArray(cell->value, 1, list->type);
            cell = cell->next;
        }
    }
}

void setListDealloc(void (*dealloc)(void*),linklist *list){
    list->dealloc = dealloc;
}

void setListPrint(void (*print)(void*),linklist *list){
    list->print = print;
}

