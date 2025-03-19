#include "scheduler.h"

queue_t high, mid, low;
queue_t waiting, complete;
resource_queue_t resources;

void setupProgram(){
	setupQueues();
        //Create Resource Queues
	createResources();
        //Create Tasks
        createTask();  //producer
        //Execute Tasks
        executeTask(); // consumer
        //Deallocate Memory
        deallocate(); // should deallocate tasks in queues
}

void setupQueues(){ //Only function called in main
        initQueue(&high, 30); //should this be 30?
        initQueue(&mid, 30);
        initQueue(&low, 30);
	initQueue(&waiting, 30);
	initQueue(&complete, 30);
}

int createResources(){
	for(int i = 0; i < 5; i++){
		resources.resources[i].rid = i;
		if(sem_init(&(resources.resources[i].semaphore), 0, rand() % 3 + 1) != 0){
			return ENOSYS;
		}
	}
	return 0;
}


void createTask(){
	task_t task;
	task.taskID = rand();
	task.priority = rand() % 3 + 1;
	task.duration = rand() % 6 + 1;
	int num1, num2;
	num1 = rand() % 5 + 1;
	num2 = rand() % 5 + 1;
	if(num1 == num2){
		num2 = (num2 + 1) % 5 + 1;
	}
	task.resources[0] = num1;
	task.resources[1] = num2;
	if(task.priority == 1){
		enqueue(&low, task);
	} else if(task.priority == 2){
		enqueue(&mid, task);
	} else {
		enqueue(&high, task);
	}
}

void executeTask(){
	if(!isEmpty(&high)){
		//do stuff at the highest priority
	} else if(!isEmpty(&mid)){
		// do stuff at middle priority
	} else if(!isEmpty(&low)){
		// do stuff at low priority
	}
}

void deallocate(){
	for(int i = 0; i < 5; i++){
		sem_destroy(&(resources.resources[i]).semaphore);
	}
	destroyQueue(&high);
	destroyQueue(&mid);
	destroyQueue(&low);
	destroyQueue(&waiting);
	destroyQueue(&complete);
}
