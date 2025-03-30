#ifndef KSTRUCTURES_H_
#define KSTRUCTURES_H_

#include <linux/mutex.h>
#include <linux/semaphore.h>

#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

typedef struct task_t{
        int taskID;
        int priority;
        int duration;
        int resources[2];
} task_t;

typedef struct queue_t{
        task_t* queue;
        int capacity;
        int currentSize;
	struct mutex mutex;
}queue_t;

typedef struct resource_t{
        int rid; // id
        struct semaphore semaphore;
} resource_t;

typedef struct resource_queue_t{
        resource_t resources[10];
} resource_queue_t;

#endif
