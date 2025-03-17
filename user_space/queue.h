#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include "structures.h"


void initQueue(queue_t* q, int size);
void destoryQueue(queue_t* q);
bool isEmpty(queue_t* q);
bool isFull(queue_t* q);
bool enqueue(queue_t* q, task_t value);
bool dequeue(queue_t* q);
task_t top(queue_t* q);
void print(queue_t* q);
int find(queue_t* q, int value);

#endif
