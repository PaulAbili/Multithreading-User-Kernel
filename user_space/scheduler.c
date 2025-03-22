#include "scheduler.h"
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_add_task 548
#define __NR_schedule_tasks 549
#define __NR_acquire_resources 550
#define __NR_release_resources 551

queue_t high, mid, low;
queue_t waiting, complete;
resource_queue_t resources;

//long sys_add_test(queue_t* q, task_t t){
//	return syscall(__NR_add_task);
//}

//long sys_scheduele_task(void){
//	return syscall(__NR_schedule_tasks);
//}

//	return syscall(__NR_acquire_resources);
//}

//long sys_release_resources(resource_t r[2], task_t t){
//	return syscall(__NR_release_resources);
//}

void setupProgram(){
	setupQueues();
        //Create Resource Queues
	createResources();
	//Create Threads
	createProducerThread();
	createConsumerThread();
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


void* createTask(){
	task_t task;
	task.taskID = rand();
	task.priority = rand() % 3 + 1;
	task.duration = rand() % 6 + 1;
	int num1, num2;
	num1 = rand() % 5;
	num2 = rand() % 5;
	if(num1 == num2){
		num2 = (num2 + 1) % 5;
	}
	task.resources[0] = num1;
	task.resources[1] = num2;
	if(task.priority == 1){
		//sys_add_task(&low, task);
		enqueue(&low, task);
	} else if(task.priority == 2){
		//sys_add_task(&mid, task);
		enqueue(&mid, task);
	} else {
		//sys_add_task(&high, task);
		enqueue(&high, task);
	}
	return 0;
}

void* executeTask(){
	task_t task;
	if(!isEmpty(&high)){
		//do stuff at the highest priority
		task = high.queue[0];
		dequeue(&high);
	} else if(!isEmpty(&mid)){
		// do stuff at middle priority
		task = mid.queue[0];
		dequeue(&mid);
	} else if(!isEmpty(&low)){
		// do stuff at low priority
		task = low.queue[0];
		dequeue(&low);
	} else {
		return 0; // returns bc nothing is in the queues 
	}
	//sys_acquire_resources(current.queue[0].resources,current.queue[0]);
	//sys_release_resources(current.queue[0].resources,current.queue[0]);

	sem_t sem = resources.resources[task.resources[0]].semaphore;
	sem_t sem2 = resources.resources[task.resources[1]].semaphore;

	int result = sem_trywait(&sem);
	int result2 = sem_trywait(&sem2);
	if(result == 0 && result2 == 0){
		//success
		//sleep post sem dequeue and add to completed
		sleep(task.duration);
		sem_post(&sem2);
		sem_post(&sem);
		enqueue(&complete, task);
	} else if(result == 0){
		sem_post(&sem);
	} else if(result2 == 0){
		sem_post(&sem2);
	}
	if(result != 0 && result2 != 0){
		//dequeue from current
		//add to waiting queue
		//use regular wait
		enqueue(&waiting, task);
		sem_wait(&sem);
		sem_wait(&sem2);
		sleep(task.duration);
	        sem_post(&sem2);
	        sem_post(&sem);
	        dequeue(&waiting);
	        enqueue(&complete, task);
	}
	return 0;
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

void createProducerThread(){
	int* p;
	pthread_t proThreads[3];
        for(int i = 0; i < 3; i++){
                pthread_create(&proThreads[i], NULL, &createTask, NULL);
        }
        for(int i = 0; i < 3; i++){
                pthread_join(proThreads[i], (void**) &p);
        }
	sleep(10);
	for(int i = 0; i < 3; i++){
                pthread_create(&proThreads[i], NULL, &createTask, NULL);
        }
        for(int i = 0; i < 3; i++){
                pthread_join(proThreads[i], (void**) &p);
      	 }
	free(p);
}

void createConsumerThread(){
	int* c;
	pthread_t conThreads[3];
        for(int i = 0; i < 3; i++){
                pthread_create(&conThreads[i], NULL, &executeTask, NULL);
        }
        for(int i = 0; i < 3; i++){
               pthread_join(conThreads[i], (void**) &c);
		sleep(1);
        }
	sleep(1);
	for(int i = 0; i < 3; i++){
                pthread_create(&conThreads[i], NULL, &executeTask, NULL);
        }
        for(int i = 0; i < 3; i++){
                pthread_join(conThreads[i], (void**) &c);
		sleep(1);
 	       }
	free(c);
}
