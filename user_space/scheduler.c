#include "scheduler.h"
#include <semaphore.h>

queue_t high, mid, low;
queue_t waiting, complete;
resource_queue_t resources;

void setupQueues(){
        initQueue(&high, 30); //should this be 30?
        initQueue(&mid, 30);
        initQueue(&low, 30);
	initQueue(&waiting, 30);
	initQueue(&complete, 30);
	//Create Resource Queues
	createResources();
	//Create Tasks
	//createTasks();
	//Execute Tasks
	executeTasks();
	//Deallocate Memory
	deallocate(); // should deallocate tasks in queues
}

void createResources(){
	resource_t rArray[5];
	for(int i = 0; i < 5; i++){
		rArray[i].rid = i;
		sem_init((rArray->semaphore), 0, rand() % 3 + 1);
		if(i != 0){
			rArray[i].next = &rArray[i-1];
		}
	}
	resources.resources = &rArray[0];
}


void createTasks(){
	task_t task;
	task.taskID = rand();
	task.priority = rand() % 3 + 1;
	task.duration = rand() % 6 + 1;
	task.resources = malloc(sizeof(int) * 2);
	task.resources[0] = 1;
	task.resources[1] = 2;
	if(task.priority == 1){
		enqueue(&low, task); // currently only for ints fix it :)
	} else if(task.priority == 2){
		enqueue(&mid, task);
	} else {
		enqueue(&high, task);
	}
}

void executeTasks(){
	if(!isEmpty(&high)){
		//do stuff at the highest priority
	} else if(!isEmpty(&mid)){
		// do stuff at middle priority
	} else if(isEmpty(&low)){
		// do stuff at low priority
	}
}

void deallocate(){
	resource_t current;
	for(int i = 0; i < 5; i++){
		current = resources.resources;
		sem_destory(current->semaphore);
		current = current.next;
}
