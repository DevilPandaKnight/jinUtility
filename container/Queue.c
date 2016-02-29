#include "Queue.h"

queue* initQueue(int eleSize, void (*dealloc)(void*)){
	queue* q = cnew(queue);
	cRaise(q==NULL,"memory allocation failed.");
	q->length = 0;
    q->type = -1;
    q->elemSize = eleSize;
    q->firstCell = NULL;
    q->lastCell = NULL;
    q->dealloc = dealloc;
    q->print = NULL;
    return q;
}

#define allocQueue(t) initQueue(sizeof(t),NULL);

queue* intQueue(){
	queue* q = allocQueue(int);
	q->type = intType;
	return q;
}

queue* doubleQueue(){
	queue* q = allocQueue(double);
	q->type = doubleType;
	return q;
}
queue* floatQueue(){
	queue* q = allocQueue(float);
	q->type = floatType;
	return q;
}

queue* charQueue(){
	queue* q = allocQueue(char);
	q->type = charType;
	return q;
}

queue* longQueue(){
	queue* q = allocQueue(long);
	q->type = longType;
	return q;
}

queue* stringQueue(){
	queue* q = initQueue(sizeof(char*),freeStringInQueue);
	q->type = stringType;
	return q;
}

void pushQueue(void * val,queue *q){
	queueCell* cell = cnew(queueCell);
	assert(cell!=NULL);
	cell->value = malloc(q->elemSize);
	assert(cell->value!=NULL);
	memcpy(cell->value,val,q->elemSize);
	cell->next = NULL;
	if (q->lastCell) {
		q->lastCell->next = cell;
	}
	q->lastCell = cell;
	if (!q->firstCell) {
		q->firstCell = cell;
	}
	q->length++;
}


size_t dequeue(void* val, queue *q){
	cRaise(q->length==0, "empty queue.");
	if (q->firstCell == q->lastCell) {
		q->lastCell = NULL;
	}
	queueCell* cell = q->firstCell;
	q->firstCell = cell->next;
	memcpy(val, cell->value, q->elemSize);
	free(cell->value);
	free(cell);
	q->length--;
	return 1;
}

void freeQueue(queue *q){
	queueCell* cell = q->firstCell;
	queueCell* temp = NULL;
	if (q->dealloc) {
		while (cell) {
			temp = cell;
			cell = temp->next;
			q->dealloc(temp->value);
			free(temp->value);
			free(temp);
		}
	}
	else {
		while (cell) {
			temp = cell;
			cell = temp->next;
			free(temp->value);
			free(temp);
		}
	}
	free(q);
}

bool queueEmpty(queue *q){
	return q->length == 0;
}

void printQueue(queue* q){
	if (q->length == 0) {
		printf("empty queue.\n");
		return;
	}
	queueCell* cell = q->firstCell;
	if (!q->print) {
		while (cell) {
			printArray(cell->value, 1, q->type);
			cell = cell->next;
		}
	}
	else {
		while (cell) {
			q->print(cell->value);
			cell = cell->next;
		}
	}
}

void freeStringInQueue(void* val){
	free(*(char**)val);
}

void setQueueDealloc(void (*dealloc)(void*),queue *q){
	q->dealloc = dealloc;
}

void setQueuePrint(void (*print)(void*),queue *q){
	q->print = print;
}


