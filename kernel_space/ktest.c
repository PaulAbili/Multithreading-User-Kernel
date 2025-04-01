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
	syscall(__NR_add_task);
        return 0;
}

void* run(){
      	int* ptr = malloc(sizeof(int) * 2);
	printf("Pre \n");
	int result = syscall(__NR_acquire_resources, ptr);
	printf("Post %d", result);
	if(result != -1 && result != 3){
	        syscall(__NR_release_resources, ptr[0], ptr[1]);
        }
        free(ptr);
	printf("Exiting\n");
        return 0;
}
void producer(){
	pthread_t pthread[5];
	int* p;
        for(int i = 0; i < 5; i++){
                pthread_create(&pthread[i], NULL, &add, NULL);
        }
        for(int i = 0; i < 5; i++){
		 pthread_join(pthread[i], (void**) &p);
        }
	free(p);
}
void consumer(){
	pthread_t cthread[5];
	int* c;
        for(int i = 0; i < 5; i++){
                pthread_create(&cthread[i], NULL, &run, NULL);
        }
        for(int i = 0; i < 5; i++){
                pthread_join(cthread[i], (void**) &c);
		printf("%d ", i);
        }
	free(c);
}

int main(){
	syscall(__NR_schedule_tasks);
	producer();
	syscall(__NR_print_queues);
	consumer();
	syscall(__NR_print_queues);
	syscall(__NR_destroy_scheduler);
	return 0;
}

