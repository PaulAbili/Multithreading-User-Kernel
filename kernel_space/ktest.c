#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <linux/kernel.h>
#include <sys/syscall.h>
#include <pthread.h>


#define __NR_add_task 548
#define __NR_schedule_tasks 549
#define __NR_acquire_resources 550
#define __NR_release_resources 551
#define __NR_destroy_scheduler 552
#define __NR_print_queues 553

void* add(){
        long val = syscall(__NR_add_task);
        return 0;
}

void* run(){
        //int* ptr = malloc(sizeof(int) * 2);
	//int result = syscall(__NR_acquire_resources, ptr);
        //if(result != -1 && result != 3){
        //        syscall(__NR_release_resources, ptr[0], ptr[1]);
        //}
        //free(ptr);
        return 0;
}

int main(){
	long scheduler = syscall(__NR_schedule_tasks);
	pthread_t pthread[5];
	pthread_t cthread[5];
	int i;
	int* p;
	int* c;
	for(i = 0; i < 5; i++){
		pthread_create(&pthread[i], NULL, &add, NULL);
	}
	for(i = 0; i < 5; i++){
		pthread_join(pthread[i], (void**) &p);
	}
	long print1 = syscall(__NR_print_queues);
	for(i = 0; i < 5; i++){
		pthread_create(&cthread[i], NULL, &run, NULL);
	}
	for(i = 0; i < 5; i++){
		pthread_join(cthread[i], (void**) &c);
	}
	long print2 = syscall(__NR_print_queues);
	long destory = syscall(__NR_destroy_scheduler);
	free(p);
	free(c);
	return 0;
}

