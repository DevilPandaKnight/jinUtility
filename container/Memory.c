#include "Memory.h"

#define memoryCheck(ptr) cRaise(ptr==NULL,"memory allocation failed.");
bool expend(memory* m){
	void* temp = realloc(m->value,m->capacity);
	memoryCheck(temp);
	m->value = temp;
	return true;
}

memory* initMemory(){
	return initMemoryWithCapacity(0);
}

memory* initMemoryWithMemory(memory* m){
	cRaise(m==NULL, "NULL memory.");
	memory* temp = initMemoryWithCapacity(m->capacity);
	temp->length = m->length;
	memcpy(temp->value, m->value, m->length);
	return temp;
}

memory* initMemoryWithArray(void* array,size_t numberOfBytes){
	cRaise(array==NULL,"NULL array");
	cRaise((long)numberOfBytes < 0 ,"Cannot write negative bytes.");
	memory* temp = initMemoryWithCapacity(numberOfBytes);
	memcpy(temp->value, array, numberOfBytes);
	temp->length = numberOfBytes;
	return temp;
}

memory* initMemoryWithFilledBytes(unsigned char value,size_t numberOfBytes){
	cRaise((long)numberOfBytes<0, "number of bytes cannot less than 0.");
	memory* temp = initMemoryWithCapacity(numberOfBytes);
	memset(temp->value, value, numberOfBytes);
	temp->length = numberOfBytes;
	return temp;
}

memory* initMemoryWithCapacity(size_t capacity){
	cRaise((long)capacity < 0 ,"capacity cannot be less than 0.");
	memory* temp = cnew(memory);
	memoryCheck(temp);
	temp->capacity = capacity;
	temp->length = 0;
	if (capacity==0){temp->value = NULL;}
	else{
		temp->value = malloc(capacity);
		memoryCheck(temp->value);
	}
	return temp;
}

size_t freeMemory(memory* m,void* getMemoryContent){
	size_t len = m->length;
	if (getMemoryContent && len != 0) {
		memcpy(getMemoryContent,&m->value, sizeof(void*));
	}
	else {
		free(m->value);
	}
	free(m);
	return len;
}



int writeToMemory(void* array,size_t numberOfBytes, memory* m){
	cRaise(array==NULL,"NULL array");
	cRaise((long)numberOfBytes < 0 ,"Cannot write negative bytes.");
	cRaise(m==NULL,"NULL memory.");
	if (m->length+numberOfBytes > m->capacity){m->capacity = m->capacity*2+numberOfBytes;expend(m);}
	memcpy((char*)m->value+m->length,array,numberOfBytes);
	m->length += numberOfBytes;
	return numberOfBytes;
}



int insertToMemoryAtOffset(void* array,size_t numberOfBytes,size_t offSet,memory* m){
	cRaise(((long)numberOfBytes<0 || (long)offSet <0),"negative offset or bytes.");
	cRaise((long)offSet>m->length,"offSet out of range.");
	cRaise(array==NULL,"NULL array.");
	cRaise(m==NULL,"NULL memory.");
	if (m->length+numberOfBytes > m->capacity){m->capacity = m->capacity*2+numberOfBytes;expend(m);}
	char* offsetPos = (char*)m->value+offSet;
	char* shift = (char*)offsetPos+numberOfBytes;
	memmove(shift,offsetPos,m->length-offSet);
	memcpy(offsetPos,array,numberOfBytes);
	m->length += numberOfBytes;
	return numberOfBytes;
}


int clearMemory(memory* m){
	cRaise(m==NULL, "NULL memory.");
	int temp = m->length;
	m->length = 0;
	return temp;
}
int removeFromMemoryAtOffset(size_t offSet,size_t numberOfBytes,void* getRemovedMemory,memory* m){
	cRaise(((long)numberOfBytes<0 || (long)offSet <0),"negative offset or bytes.");
	cRaise(offSet+numberOfBytes>m->length,"offSet out of range.");
	char* offSetPos = (char*)m->value+offSet;
	char* shift = offSetPos+numberOfBytes;
	if (getRemovedMemory != NULL) {
		memcpy(getRemovedMemory, offSetPos, numberOfBytes);
	}
	memmove(offSetPos, shift, m->length-offSet-numberOfBytes);
	m->length -= numberOfBytes;
	return numberOfBytes;
}

int removeMemoryBytes(size_t numberOfBytes,void* getRemovedMemory,memory* m){
	cRaise((long)numberOfBytes<0, "negative bytes.");
	cRaise(numberOfBytes>m->length, "memory length less than number of bytes.");
	if (getRemovedMemory!=NULL) {
		char* pos = (char*)m->value+m->length-numberOfBytes;
		memcpy(getRemovedMemory, pos, numberOfBytes);
	}
	m->length-=numberOfBytes;
	return numberOfBytes;
}

void* copyMemoryBytesAtOffset(size_t offSet,size_t numberOfBytes,memory* m){
	cRaise(((long)numberOfBytes<0 || (long)offSet <0),"negative offset or bytes.");
	cRaise(offSet+numberOfBytes>m->length,"offSet out of range.");
	char* pos = (char*)m->value+offSet;
	void* temp = malloc(numberOfBytes);
	memoryCheck(temp);
	memcpy(temp, pos, numberOfBytes);
	return temp;
}

void* copyMemory(memory* m){
	cRaise(m==NULL || m->length == 0,"empty(null) memory.");
	void *temp = malloc(m->length);
	memoryCheck(temp);
	memcpy(temp, m->value, m->length);
	return temp;
}


int setMemoryBytes(unsigned char value,size_t numberOfBytes,memory* m){
	cRaise((long)numberOfBytes<0 || numberOfBytes >m->capacity, "number of bytes cannot be negative or greater than capacity of the memory.");
	memset(m->value, value, numberOfBytes);
	return numberOfBytes;
}
int setMemoryBytesAtOffset(unsigned char value,size_t numberOfBytes,size_t offset,memory* m){
	cRaise(offset+numberOfBytes>m->capacity,"offSet out of range.");
	cRaise(((long)numberOfBytes<0 || (long)offset <0),"negative offset or bytes.");
	char* offsetPos = (char*)m->value + offset;
	memset(offsetPos, value, numberOfBytes);
	return numberOfBytes;
}

unsigned char firstMemoryByte(memory* m){
	cRaise(m->length==0, "empty memory.");
	unsigned char c;
	memcpy(&c, m->value, 1);
	return c;
}
unsigned char lastMemoryByte(memory* m){
	cRaise(m->length==0, "empty memory.");
	unsigned char c;
	memcpy(&c, (char*)m->value+m->length-1, 1);
	return c;
}

unsigned char memoryByteAtOffset(size_t offset,memory* m){
	cRaise(offset>m->length-1 || (long)offset<0,"offSet out of range.");
	unsigned char c;
	char* pos = (char*)m->value+offset;
	memcpy(&c, pos, 1);
	return c;
}

void* memsetPattern(void* array,size_t numberOfBytes,size_t times){
	cRaise(array==NULL, "array cannot be null.");
	cRaise((long)numberOfBytes<0 || (long)times<0, "number of bytes or times cannot less than 0.");
	size_t totalBytes = numberOfBytes*times;
	char* temp = (char*)malloc(totalBytes);
	memoryCheck(temp);
	for (int i = 0;i<times;i++) {
		memcpy(temp+(i*numberOfBytes), array, numberOfBytes);
	}
	return temp;
}

int writeToMemoryWithPattern(void* array,size_t numberOfBytes,size_t times,memory* m){
	void* temp = memsetPattern(array, numberOfBytes, times);
	int totalBytes = writeToMemory(temp, numberOfBytes*times, m);
	free(temp);
	return totalBytes;
}
int insertToMemoryAtOffsetWithPattern(void* array,size_t numberOfBytes,size_t times,size_t offSet,memory* m){
	void* temp = memsetPattern(array, numberOfBytes, times);
	int totalBytes = insertToMemoryAtOffset(temp, numberOfBytes*times, offSet, m);
	free(temp);
	return totalBytes;
}

int replaceMemoryAtOffsetWithArray(void* array,size_t numberOfBytes,size_t offset,memory* m){
	cRaise(((long)numberOfBytes<0 || (long)offset <0),"negative offset or bytes.");
	cRaise(offset+numberOfBytes>m->length,"offSet out of range.");
	cRaise(array==NULL,"NULL array.");
	cRaise(m==NULL,"NULL memory.");
	char* pos = (char*)m->value+offset;
	memcpy(pos, array, numberOfBytes);
	return numberOfBytes;
}
int replaceByteAtOffset(unsigned char value,size_t offset,memory* m){
	cRaise(offset>m->length-1 || (long)offset<0,"offSet out of range.");
	memcpy((char*)m->value+offset, &value, 1);
	return 1;
}

#undef memoryCheck


