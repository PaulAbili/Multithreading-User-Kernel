#include "kscheduler.h"

int createResources(resource_queue_t* resources){
	int i;
	for(i = 0; i < 5; i++){
		resources->resources[i].rid = i;
		sema_init(&(resources->resources[i].semaphore), get_random_int() % 3 + 1);
	}
	return 0;
}


void createTask(queue_t* high, queue_t* mid, queue_t* low){
	task_t task;
	int num1, num2;
	task.taskID = get_random_int();
	task.priority = get_random_int() % 3 + 1;
	task.duration = get_random_int() % 6 + 1;
	num1 = get_random_int() % 5;
	num2 = get_random_int() % 5;
	if(num1 == num2){
		num2 = (num2 + 1) % 5;
	}
	task.resources[0] = num1;
	task.resources[1] = num2;
	if(task.priority == 1){
		mutex_lock(&(low->mutex));
		enqueue(&(*low), task);
		mutex_unlock(&(low->mutex));
	} else if(task.priority == 2){
		mutex_lock(&(mid->mutex));
		enqueue(&(*mid), task);
		mutex_unlock(&(mid->mutex));
	} else {
		mutex_lock(&(high->mutex));
		enqueue(&(*high), task);
		mutex_unlock(&(high->mutex));
	}
}

task_t getTask(queue_t* high, queue_t* mid, queue_t* low){
	task_t task;
	if(!isEmpty(&(*high))){
		//do stuff at the highest priority
		mutex_lock(&(high->mutex));
		task = high->queue[0];
		dequeue(&(*high));
		mutex_unlock(&(high->mutex));
	} else if(!isEmpty(&(*mid))){
		// do stuff at middle priority
		mutex_lock(&(mid->mutex));
		task = mid->queue[0];
		dequeue(&(*mid));
		mutex_lock(&(mid->mutex));
	} else if(!isEmpty(&(*low))){
		// do stuff at low priority
		mutex_lock(&(low->mutex));
		task = low->queue[0];
		dequeue(&(*low));
		mutex_unlock(&(low->mutex));
	}
	return task;
}

task_t getWaiting(queue_t* waiting){
	task_t task;
        if(!isEmpty(&(*waiting))){
                //dequeue waiting
                mutex_lock(&(waiting->mutex));
		task = waiting->queue[0];
                mutex_lock(&(waiting->mutex));
                dequeue(&(*waiting));
                mutex_unlock(&(waiting->mutex));
        }
        return task;
}

void executeTask(resource_queue_t* resources, queue_t* completed, task_t task){
        msleep(task.duration);
        up(&(resources->resources[task.resources[0]].semaphore));
        up(&(resources->resources[task.resources[1]].semaphore));
	mutex_lock(&(completed->mutex));
	enqueue(&(*completed), task);
	mutex_unlock(&(completed->mutex));
}

void addToWait(queue_t* waiting, task_t task){
	mutex_lock(&(waiting->mutex));
	enqueue(&(*waiting), task);
	mutex_unlock(&(waiting->mutex));
}

void deallocate(resource_queue_t* resources, queue_t* high, queue_t* mid, queue_t* low, queue_t* waiting, queue_t* completed){
	destroyQueue(high);
	destroyQueue(mid);
	destroyQueue(low);
	destroyQueue(waiting);
	destroyQueue(completed);
}




