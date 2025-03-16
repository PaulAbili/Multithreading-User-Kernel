#include "queue.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
void initQueue(queue_t* q, int size){
	q->queue = malloc(sizeof(int) * size);
	q->capacity = size;
	q->currentSize = 0;
}

void destoryQueue(queue_t* q){
	free(q->queue);
}

bool isEmpty(queue_t* q){
	if(q->currentSize == 0){
		return true;
	}
	return false;
}

bool isFull(queue_t* q){
	if(q->currentSize >= q->capacity){
		return true;
	}
	return false;
}

bool enqueue(queue_t* q, int value){
	if(isFull(q)){
		return false;
	}
	q->queue[q->currentSize] = value;
	q->currentSize++;
	return true;
}

bool dequeue(queue_t* q){
	if(isEmpty(q)){
		return false;
	}
	for(int i = 0; i < q->currentSize - 1; i++){
		q->queue[i] = q->queue[i+1];
	}
	q-> currentSize--;
	return true;
}

int top(queue_t* q){
	if(isEmpty(q)){
		return -1;
	}
	return q->queue[0];
}

void print(queue_t* q){
	if(isEmpty(q)){
         // do nothing 
        } else {
		for(int i = 0; i < q -> currentSize; i++){
			printf("%d, ", q->queue[i]);
		}
		printf("\n");
	}
}

int find(queue_t* q, int value){
	if(isEmpty(q)){
                return -1; 
        }
	for(int i = 0; q -> currentSize; i++){
		if(q->queue[i] == value){
			return i;
		}
	}
	return -2;
}
