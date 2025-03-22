#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "queue.c"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>



void setupProgram();
void setupQueues();
int createResources();
void* createTask();
void* executeTask();
void deallocate();
void createProducerThread();
void createConsumerThread();

#endif
