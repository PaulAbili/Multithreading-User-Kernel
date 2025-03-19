#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "queue.c"

void setupProgram();
void setupQueues();
int createResources();
void createTask();
void executeTask();
void deallocate();

#endif
