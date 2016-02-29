#ifndef __MEMORY_H__
#define __MEMORY_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "../utility.h"

typedef struct{
    void *value;
    size_t capacity;
    size_t length;
}memory;

memory* initMemory();
memory* initMemoryWithCapacity(size_t capacity);
memory* initMemoryWithMemory(memory* m);
memory* initMemoryWithFilledBytes(unsigned char value,size_t numberOfBytes);
memory* initMemoryWithArray(void* array,size_t numberOfBytes);
size_t freeMemory(memory* m,void* getMemoryContent);

int writeToMemory(void* array,size_t numberOfBytes, memory* m);
int writeToMemoryWithPattern(void* array,size_t numberOfBytes,size_t times,memory* m);
int insertToMemoryAtOffset(void* array,size_t numberOfBytes,size_t offSet,memory* m);
int insertToMemoryAtOffsetWithPattern(void* array,size_t numberOfBytes,size_t times,size_t offSet,memory* m);

void* copyMemory(memory* m);
void* copyMemoryBytesAtOffset(size_t offSet,size_t numberOfBytes,memory* m);

int setMemoryBytes(unsigned char value,size_t numberOfBytes,memory* m);
int setMemoryBytesAtOffset(unsigned char value,size_t numberOfBytes,size_t offset,memory* m);
int replaceMemoryAtOffsetWithArray(void* array,size_t numberOfBytes,size_t offset,memory* m);
int replaceByteAtOffset(unsigned char value,size_t offset,memory* m);

unsigned char firstMemoryByte(memory* m);
unsigned char lastMemoryByte(memory* m);
unsigned char memoryByteAtOffset(size_t offset,memory* m);

int removeMemoryBytes(size_t numberOfBytes,void* getRemovedMemory,memory* m);
int removeFromMemoryAtOffset(size_t offSet,size_t numberOfBytes,void* getRemovedMemory,memory* m);
int clearMemory(memory* m);

void* memsetPattern(void* array,size_t numberOfBytes,size_t times);

#ifdef __cplusplus
};
#endif

#endif