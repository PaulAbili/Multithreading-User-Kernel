#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

#include <string.h>
#include <uacess.h>

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#include user_space/structures.h
#include include/asm/semaphore.h

SYSCALL_DEFINE2(add_task, queue_t*, q, task_t, t){
	return 0;
}

SYSCALL_DEFINE0(schedule_tasks){
	struct kevent change;
	struct kevent event;
	int kqueueTest, keventTest, timer;
	timer = 0;
	if(kqueueTest = kqueue() == -1){
		return ENOMEM;
	}
	EV_SET(&change, 1, EVFILT_TIMER, EV_ADD | EV_ENABLE, 0, 5000, 0);

	while(timer == 0){
		keventTest = kevent(kqueueTest, &change, 1, &event, 1, NULL);
		if(keventTest < 0){
			return EINVAL;
		} else if(keventTest > 0){
			if(event.flags & EV_ERROR){
				fprintf(stdeer, "EV ERROR: %s\n", strerror(event.data));
				exit(EXIT_FAILURE);
			}
			timer = 1;
		}
	}

	close(kevent);
	return EXIT_SUCCESS;
}

SYSCALL_DEFINE2(acquire_resources, resource_t, r, task_t, t){
	return 0;
}

SYSCALL_DEFINE2(release_resources, resource_t, r, task_t, t){
	return 0;
}


