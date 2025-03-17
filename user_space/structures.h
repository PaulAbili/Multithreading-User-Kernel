#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#include <pthread.h>
#include <semaphore.h>


typedef struct task_Structure{
        int taskID;
        int priority;
        int duration;
        int* resources;
} task_t;

typedef struct queue_Structure{
        task_t* queue;
        int capacity;
        int currentSize;
}queue_t;

typedef struct resource{
        int rid; // id
        sem_t* semaphore;
        struct resource* next;
} resource_t;

typedef struct resource_queue{
        resource_t* resources;
} resource_queue_t;

#endif
