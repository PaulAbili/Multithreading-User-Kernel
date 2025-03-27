#ifndef KSCHEDULER_H_
#define KSCHEDULER_H_
#include "kqueue.c"
#include <linux/string.h>
#include <linux/unistd.h>
#include <sys/wait.h>
#include <linux/ctype.h>

void setupPthreadedProgram();
void setupQueues();
int createResources();
void* createTask();
void* executeTask();
void deallocate();
void createProducerThread();
void createConsumerThread();

#endif
