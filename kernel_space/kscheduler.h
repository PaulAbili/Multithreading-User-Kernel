#ifndef KSCHEDULER_H_
#define KSCHEDULER_H_
#include "kqueue.c"
#include <linux/random.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/ctype.h>



int createResources(resource_queue_t* resources);
void createTask(queue_t* high, queue_t* mid, queue_t* low);
task_t getTask(queue_t* high, queue_t* mid, queue_t* low);
task_t getWaiting(queue_t* waiting);
void executeTask(resource_queue_t* resources, queue_t* completed, task_t task);
void addToWait(queue_t* waiting, task_t task);
void deallocate(resource_queue_t* resources, queue_t* high, queue_t* mid, queue_t* low, queue_t* waiting, queue_t* completed);
#endif
