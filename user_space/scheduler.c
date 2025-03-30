#include "scheduler.h"
#include <linux/kernel.h>
#include <sys/syscall.h>

queue_t high, mid, low;
queue_t waiting, complete;
resource_queue_t resources;

void setupPthreadedProgram(){
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
		pthread_mutex_lock(&(low.mutex));
		enqueue(&low, task);
		pthread_mutex_unlock(&(low.mutex));
	} else if(task.priority == 2){
		pthread_mutex_unlock(&(mid.mutex));
		enqueue(&mid, task);
		pthread_mutex_unlock(&(mid.mutex));
	} else {
		pthread_mutex_lock(&(high.mutex));
		enqueue(&high, task);
		pthread_mutex_unlock(&(high.mutex));
	}
	return 0;
}

void* executeTask(){
	task_t task;
	if(!isEmpty(&high)){
		//do stuff at the highest priority
		task = high.queue[0];
		pthread_mutex_lock(&(high.mutex));
		dequeue(&high);
		pthread_mutex_unlock(&(high.mutex));
	} else if(!isEmpty(&mid)){
		// do stuff at middle priority
		task = mid.queue[0];
		pthread_mutex_lock(&(mid.mutex));
		dequeue(&mid);
		pthread_mutex_unlock(&(mid.mutex));
	} else if(!isEmpty(&low)){
		// do stuff at low priority
		task = low.queue[0];
		pthread_mutex_lock(&(low.mutex));
		dequeue(&low);
		pthread_mutex_unlock(&(low.mutex));
	}

	sem_t sem = resources.resources[task.resources[0]].semaphore;
	sem_t sem2 = resources.resources[task.resources[1]].semaphore;

	int result = sem_trywait(&sem);
	int result2 = sem_trywait(&sem2);
	if(result == 0 && result2 == 0){
		//success
		//sleep post and add to complete
		sleep(task.duration);
		sem_post(&sem2);
		sem_post(&sem);
		pthread_mutex_lock(&(complete.mutex));
		enqueue(&complete, task);
		pthread_mutex_unlock(&(complete.mutex));
	} else if(result == 0){ // if only resource 1 is available, releases it
		sem_post(&sem);
	} else if(result2 == 0){ // if only resource 2 is available
		sem_post(&sem2);
	}
	if(result != 0 && result2 != 0){ // if both resources are not available, adds to waiting queue
		pthread_mutex_lock(&(waiting.mutex));
		enqueue(&waiting, task);
		pthread_mutex_unlock(&(waiting.mutex));
	}
	if(!isEmpty(&waiting)){
		task = top(&waiting);
		sem = resources.resources[task.resources[0]].semaphore;
		sem2 = resources.resources[task.resources[1]].semaphore;
		result = sem_trywait(&sem);
        	result2 = sem_trywait(&sem2);
		if(result == 0 && result2 == 0){
			sem_post(&sem);
			sem_post(&sem2);
			pthread_mutex_lock(&(waiting.mutex));
			dequeue(&waiting);
			pthread_mutex_unlock(&(waiting.mutex));
			        if(task.priority == 1){
         			       	pthread_mutex_lock(&(low.mutex));
			               	enqueue(&low, task);
					pthread_mutex_unlock(&(low.mutex));
        			} else if(task.priority == 2){
        			        pthread_mutex_unlock(&(mid.mutex));
               				enqueue(&mid, task);
                			pthread_mutex_unlock(&(mid.mutex));
       				} else {
        			        pthread_mutex_lock(&(high.mutex));
        			        enqueue(&high, task);
                			pthread_mutex_unlock(&(high.mutex));
        			}

		int* p;
		pthread_t thread;
		pthread_create(&thread, NULL, &executeTask, NULL);
		pthread_join(thread, (void**) &p);
		free(p);
		} else if(result == 0){
			sem_post(&sem);
		} else if(result2 == 0){
			sem_post(&sem2);
		}
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


// pthread creation methods
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
