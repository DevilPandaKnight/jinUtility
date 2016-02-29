#include "JObject.h"
static const int JObjectSize = sizeof(JObject);

JObject* initJObject(){
    JObject *obj = cnew(JObject);
    if (obj==NULL) {
        printf("malloc JObject failed, no enough memory.\n");
        return NULL;
    }
    obj->className = "JObject";
    obj->parentClass = NULL;
    obj->childClass = NULL;
    obj->objectSize = JObjectSize;
    obj->dealloc = free;
    obj->parentPointer = NULL;
    obj->childPointer=NULL;
    obj->superClassIsJObject = false;
    obj->selfPointer = NULL;
    obj->print = NULL;
    return obj;
}

#define getJObject(obj) JObject* object;memcpy(&object, obj, sizeof(JObject*));

bool isKindOfObject(char* class, void* obj){
    getJObject(obj)
    void* temp;
    while (object->parentPointer != NULL) {
        if (strcmp(object->className, class)==0) {
            return true;
        }
        temp = object->parentPointer;
        if (object->superClassIsJObject == false) {
            memcpy(&object, temp, sizeof(JObject*));
        }
        else{
            object = temp;
        }
    }
    return (strcmp(object->className, class)==0);
}

bool isObject(char* class,void* obj){
    getJObject(obj)
    return (strcmp(object->className, class)==0);
}

void* getParentObject(char* className, void* obj){
    getJObject(obj)
    void* temp;
    while (object->parentPointer != NULL) {
        if (strcmp(object->className, className)==0) {
            return object->selfPointer;
        }
        temp = object->parentPointer;
        if (!object->superClassIsJObject) {
            memcpy(&object, temp, sizeof(JObject*));
        }
        else{
            JObject* j = (JObject*)temp;
            return (strcmp(j->className, className)==0)? j:NULL;
        }
    }
    return NULL;
}

void deleteJinObject(void* obj){
    getJObject(obj)
    object->dealloc(obj);
}

void printJinObject(void* obj){
    getJObject(obj)
    object->print(obj);
}

#undef getJObject