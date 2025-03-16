#include "queue.c"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>


int main(int argc, char** argv){
	queue_t queue;
	initQueue(&queue, 10);
	for(int i = 0; i < 10; i++){
		enqueue(&queue, i);
	}

	print(&queue);
	for(int i = 0; i < 3; i++){
		dequeue(&queue);
	}

	print(&queue);
	destoryQueue(&queue);
	return 0;
}
