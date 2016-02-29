#include "Stack.h"

stack* initStack(int eleSize,void(*dealloc)(void*)){
    stack *s = cnew(stack);
    assert(s!=NULL);
    s->length=0;
    s->capacity=1;
    s->dealloc=dealloc;
    s->elemSize=eleSize;
    s->type=-1;
    s->value=malloc(eleSize);
    s->print = NULL;
    return s;
}

stack* intStack(){
    stack *s = initStack(sizeof(int), NULL);
    s->type=intType;
    return s;
}

stack* doubleStack(){
    stack* s = initStack(sizeof(double), NULL);
    s->type=doubleType;
    return s;
}

stack* floatStack(){
    stack *s = initStack(sizeof(float), NULL);
    s->type = doubleType;
    return s;
}
stack* charStack(){
    stack *s = initStack(sizeof(char), NULL);
    s->type = charType;
    return s;
}

stack* longStack(){
    stack *s = initStack(sizeof(long), NULL);
    s->type = longType;
    return s;
}

stack* stringStack(){
    stack *s = initStack(sizeof(char*), freeStringInStack);
    s->type = stringType;
    return s;
}

static void expendeStack(stack *s){
    s->capacity *= 2;
    void* temp = realloc(s->value, s->capacity*s->elemSize);
    if (temp==NULL) {
        printf("ask too large memory, killed stack to save memory.\n");
        freeStack(s);
    }
    s->value = temp;
}

void pushStack(void * val,stack *s){
    assert(s!=NULL);
    if (s->length == s->capacity) {
        expendeStack(s);
    }
    void *ptr = (char*)s->value+s->length*s->elemSize;
    memcpy(ptr, val, s->elemSize);
    s->length++;
}

void popStack(void* val, stack *s){
    popStackAtIndex(val, s->length-1, s);
}


void pushStackAtIndex(void* val,size_t index, stack* s){
    assert(s!=NULL);
    if (index > s->length) {
        pushStack(val, s);
        return;
    }
    if (s->length == s->capacity) {
        expendeStack(s);
    }
    memmove((char*)s->value+(index+1)*s->elemSize, (char*)s->value+index*s->elemSize, (s->length-index)*s->elemSize);
    memcpy((char*)s->value+index*s->elemSize, val, s->elemSize);
    s->length++;
}

void popStackAtIndex(void *val,size_t index,stack *s){
    assert(s!=NULL);
    if (index >= s->length) {
        printf("index out of range\n");
        return;
    }
    void* temp = (char*)s->value+index*s->elemSize;
    if (val == NULL) {
        if (s->dealloc != NULL) {
            s->dealloc(temp);
        }
    }
    else {
        memcpy(val,temp , s->elemSize);
    }
    memmove((char*)s->value+index*s->elemSize, (char*)s->value+(index+1)*s->elemSize, (s->length-(index+1))*s->elemSize);
    s->length--;
}

void getStackValueAtIndex(void* val, size_t index,stack *s){
    assert(s!=NULL);
    if (index >= s->length) {
        printf("index out of range\n");
        return;
    }
    memcpy(val, (char*)s->value + index*s->elemSize, s->elemSize);
}


void freeStack(stack *s){
    if (s->dealloc!=NULL) {
        for (int i =0; i<s->length; i++) {
            s->dealloc((char*)s->value+i*s->elemSize);
        }
    }
    free(s->value);
    free(s);
}

bool stackEmpty(stack *s){
    return (s->length>0) ? false : true;
}



void printStack(stack* s){
    if (s->length == 0) {
        printf("empty stack.\n");
        return;
    }
    if (s->type <0 && s->print == NULL) {
        printf("does not know how to print this stack.\n");
        return;
    }
    if (s->print != NULL) {
        for (int i = 0; i<s->length; i++) {
            s->print((char*)s->value+i*s->elemSize);
        }
        return;
    }
    printArray(s->value, s->length, s->type);
}

void setStackPrint(void (*print)(void*),stack *s){
    s->print = print;
}

void setStackDealloc(void (*dealloc)(void*),stack *s){
    s->dealloc = dealloc;
}

void freeStringInStack(void* val){
    free(*(char**)val);
}


