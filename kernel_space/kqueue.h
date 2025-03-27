#ifndef KQUEUE_H_
#define KQUEUE_H_

#include "kstructures.h"


void initQueue(queue_t* q, int size);
void destroyQueue(queue_t* q);
int isEmpty(queue_t* q);
int isFull(queue_t* q);
int enqueue(queue_t* q, task_t value);
int dequeue(queue_t* q);
task_t top(queue_t* q);
void printQueue(queue_t* q);
int find(queue_t* q, int value);

#endif
