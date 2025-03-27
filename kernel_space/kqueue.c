#include "kqueue.h"
#include <linux/slab.h> //kmalloc
#include <stdlib.h> // allowed
#include <stdio.h> // allowed
#include <linux/errno.h> //

void initQueue(queue_t* q, int size){
	q->queue = kmalloc(sizeof(task_t) * size, GFP_KERNEL);
	q->capacity = size;
	q->currentSize = 0;
}

void destroyQueue(queue_t* q){
	kfree(q->queue);
}

int isEmpty(queue_t* q){
	if(q->currentSize == 0){
		return 1;
	}
	return 0;
}

int isFull(queue_t* q){
	if(q->currentSize >= q->capacity){
		return 1;
	}
	return 0;
}

int enqueue(queue_t* q, task_t value){
	if(isFull(q)){
		return 1;
	}
	q->queue[q->currentSize] = value;
	q->currentSize++;
	return 0;
}

int dequeue(queue_t* q){
	if(isEmpty(q)){
		return 0;
	}
	for(int i = 0; i < q->currentSize - 1; i++){
		q->queue[i] = q->queue[i+1];
	}
	q->currentSize--;
	return 1;
}

task_t top(queue_t* q){
	if(isEmpty(q)){
		task_t emptyTask;
		emptyTask.taskID = -1;
		return emptyTask;
	}
	return q->queue[0];
}

void printQueue(queue_t* q){
	if(isEmpty(q)){
         // do nothing
        } else {
		int i;
		for(i = 0; i < q->currentSize - 1; i++){
			printk("%d, ", q->queue[i].taskID);
		}
		printk("%d\n", q->queue[q->currentSize -1].taskID);
	}
}

int find(queue_t* q, int id){
	if(isEmpty(q)){
                return -1;
        }
	int i;
	for(i = 0; q->currentSize; i++){
		if(q->queue[i].taskID == id){
			return i;
		}
	}
	return -2;
}
