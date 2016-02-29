#ifndef __JOBJECT_H__
#define __JOBJECT_H__
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../utility.h"
typedef struct JObject{
    size_t objectSize;
    char* className;
    char* parentClass;
    char* childClass;
    void* parentPointer;
    void* childPointer;
    void* selfPointer;
    bool superClassIsJObject;
    void (*dealloc)();
    void (*print)();
}JObject;


JObject* initJObject();
bool isKindOfObject(char* obj_class, void* obj);
bool isObject(char* obj_class,void* obj);
void* getParentObject(char* className, void* obj);
void deleteJinObject(void* obj);
void printJinObject(void* obj);

#ifdef __cplusplus
};
#endif

#endif