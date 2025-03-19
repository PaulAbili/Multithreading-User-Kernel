#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void initQueue(queue_t* q, int size){
	q->queue = malloc(sizeof(task_t) * size);
	q->capacity = size;
	q->currentSize = 0;
}

void destroyQueue(queue_t* q){
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

bool enqueue(queue_t* q, task_t value){
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
	free(q->queue[0].resources);
	for(int i = 0; i < q->currentSize - 1; i++){
		q->queue[i] = q->queue[i+1];
	}
	q->currentSize--;
	return true;
}

task_t top(queue_t* q){
	if(isEmpty(q)){
		task_t emptyTask;
		emptyTask.taskID = -1;
		return emptyTask;
	}
	return q->queue[0];
}

void print(queue_t* q){
	if(isEmpty(q)){
         // do nothing 
        } else {
		for(int i = 0; i < q->currentSize; i++){
			printf("%d, ", q->queue[i].taskID);
		}
		printf("\n");
	}
}

int find(queue_t* q, int id){
	if(isEmpty(q)){
                return -1; 
        }
	for(int i = 0; q->currentSize; i++){
		if(q->queue[i].taskID == id){
			return i;
		}
	}
	return -2;
}
