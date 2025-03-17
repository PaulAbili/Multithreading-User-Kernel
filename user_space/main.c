#include "scheduler.c"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>


int main(int argc, char** argv){
	setupQueues();
	return 0;
}
