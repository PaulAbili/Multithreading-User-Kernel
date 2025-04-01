#include "kscheduler.c"

static queue_t high, mid, low, waiting, completed;
static resource_queue_t resources;


SYSCALL_DEFINE0(schedule_tasks){
	initQueue(&high, 30);
	initQueue(&mid, 30);
	initQueue(&low, 30);
	initQueue(&waiting, 30);
	initQueue(&completed, 30);
	createResources(&resources);
	return 0;
}

SYSCALL_DEFINE0(add_task){
	createTask(&high, &mid, &low);
	return 0;
}

SYSCALL_DEFINE1(acquire_resources, int __user*, ptr){
	int val;
	task_t task;
	struct semaphore sem;
	struct semaphore sem2;
	int result;
	int result2;
	if(isEmpty(&high) == 1 && isEmpty(&mid) == 1 && isEmpty(&low) == 1 && isEmpty(&waiting) == 1){
		// do nothing
		return 3; // nothing happened
	} else if(isEmpty(&waiting) == 0){
		task = getWaiting(&waiting);
		val = 2;
	} else if(isEmpty(&high) == 0 || isEmpty(&mid) == 0 || isEmpty(&low) == 0){
		task = getTask(&high, &mid, &low);
		val = 1;
	}

	sem = resources.resources[task.resources[0]].semaphore;
	sem2 = resources.resources[task.resources[1]].semaphore;
	result = down_trylock(&sem);
	result2 = down_trylock(&sem2);
	ptr[0] = task.resources[0];
	ptr[1] = task.resources[1];
	if(result == 0 && result2 == 0){
		executeTask(&resources, &completed, task);
		return val;
	} else if(result == 0){
		up(&sem2);
	} else if(result2 == 0){
		up(&sem);
	}
	if(val == 1){
		addToWait(&waiting, task);
	} else if(val == 2){
		val = 1;
		if(isEmpty(&high) == 0 || isEmpty(&mid) == 0 || isEmpty(&low) == 0){
			task = getTask(&high, &mid, &low);
		}
		sem = resources.resources[task.resources[0]].semaphore;
		sem2 = resources.resources[task.resources[1]].semaphore;
		result = down_trylock(&sem);
		result2 = down_trylock(&sem2);
		ptr[0] = task.resources[0];
		ptr[1] = task.resources[1];
		if(result == 0 && result2 == 0){
			executeTask(&resources, &completed, task);
			return val;
		} else if(result == 0){
			up(&sem2);
		} else if(result2 == 0){
			up(&sem);
		}
	}
	addToWait(&waiting, task);
	return -1; // failed
}

SYSCALL_DEFINE2(release_resources, int, i, int, j){
 	struct semaphore sem = resources.resources[i].semaphore;
        struct semaphore sem2 = resources.resources[j].semaphore;
	up(&sem2);
	up(&sem);
	return 0;
}

SYSCALL_DEFINE0(destroy_scheduler){
	deallocate(&resources, &high, &mid, &low, &waiting, &completed);
	return 0;
}

SYSCALL_DEFINE0(print_queues){
	printk("High Queue:\n");
	printQueue(&high);
	printk("Mid Queue:\n");
	printQueue(&mid);
	printk("Low Queue:\n");
	printQueue(&low);
	printk("Waiting Queue:\n");
	printQueue(&waiting);
	printk("Completed Queue:\n");
	printQueue(&completed);
	return 0;
}
