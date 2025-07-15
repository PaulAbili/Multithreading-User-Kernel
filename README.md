# Task Scheduler with Priority and Resource Constraints

### Contact
**Author:** Paul Abili <br>
**Campus ID:** QD36016 <br>
**Email:** pabili1@umbc.edu <br>

### Overview

<p>The goal of this project is to simulate a task scheduler using sleep & msleep to simulate task execution in user space and kernel space code respectively.</p>

<p>Speaking of which, the project is split into two main sections, the user space section and & the kernel section, which individually attempt the aforementioned task scheduler.</p>

<p>In my implementation, the kernel_space code is NOT an exact logic copy of the user space code. This is due to the way I implemented the user space code, where I included pthreads inside of the project, rather than using them in the tester, and the way coded in locking.</p>

<p>Due to all of that, I needed to slightly change the logic of the kernel code although they largely perform the same. 
Each task has 2 resources and there are 5 resources inside of the task scheduler. Additionally, I don’t have a separate directories for the tests, they exist within their respective space folders, user space and kernel space.</p>

### Installation and Setup
#### Libraries used:
##### User space:

#include <stdlib.h> <br>
#include <stdio.h> <br>
#include <errno.h> <br>
#include <stdbool.h> <br>
#include <linux/kernel.h> <br>
#include <sys/syscall.h> <br>
#include <string.h> <br>
#include <unistd.h> <br>
#include <sys/wait.h> <br>
#include <ctype.h> <br>
#include <pthread.h> <br>
#include <semaphore.h> <br>

In Tester: N/A

##### Kernel space:

#include <linux/random.h> <br>
#include <linux/delay.h> <br>
#include <linux/string.h> <br>
#include <linux/unistd.h> <br>
#include <linux/ctype.h> <br>
#include <linux/mutex.h> <br>
#include <linux/semaphore.h> <br>
#include <linux/wait.h> <br>
#include <linux/slab.h> <br>
#include <linux/uaccess.h> <br>
#include <linux/printk.h> <br>
#include <linux/sched.h> <br>
#include <linux/kernel.h> <br>
#include <linux/syscalls.h> <br>
#include <linux/errno.h> <br>

##### In tester:

#include <stdio.h> <br>
#include <stdlib.h> <br>
#include <unistd.h> <br>
#include <sys/syscall.h> <br>
#include <pthread.h> <br>
#include <errno.h> <br>
#include <string.h> <br>

### Build and Compile
#### Build & run this program with: 
##### User Space tester: 

Build & Run:  make run
##### Kernel Space tester: 

Build: gcc [ktest.c](kernel_space/ktest.c) -g -o -pthread ktest
Run: ./ktest

#### User Space: [scheduler.c](user_space/scheduler.c) [utest.c](user_space/utest.c)
#### Kernel Space: [ktest.c](kernel_space/ktest.c)
 
### Testing

<p>I simply tested to see if the tasks were created after running the producer thread, tested to see if the tasks were put into different queues & I tested to see if the tasks were all placed into the completed queue at the end of execution</p>

### Troubleshooting

<p> Most issues stemmed from not understanding the process of converting from user_space to kernel </p>
<p> Additionally I experienced issues with finding information on kernel files. </p>

### References
#### External Sources

Sources mainly focused on kernel code implmentation <br>
https://yarchive.net/comp/linux/semaphores.html <br>
https://docs.kernel.org/locking/locktypes.html#semaphore <br>
https://kau-boys.com/3052/web-development/repair-a-broken-git-repository-file-system <br>
https://elixir.bootlin.com/linux/2.2.17pre16/source/include/linux/delay.h <br>
https://man7.org/linux/man-pages/man3/pthread_create.3.html <br>
https://docs.huihoo.com/doxygen/linux/kernel/3.7/linux_2random_8h.html#a1aaff17c5fc417e8e98fc4b5263ba5f3 <br>
https://elixir.bootlin.com/linux/v4.3/ident/get_random_bytes <br>
https://litux.nl/mirror/kerneldevelopment/0672327201/ch11lev1sec4.html <br>
https://stackoverflow.com/questions/13291353/iso-c90-forbids-mixed-declarations-and-code-in-c <br>
https://embetronicx.com/tutorials/linux/device-drivers/linux-device-drivers-tutorial-kernel-thread/#kthread_create <br>
https://man.netbsd.org/kqueue.2 <br>
https://forums.freebsd.org/threads/using-kqueue-in-event-driven-multithread-application.68376/ <br>
https://wiki.netbsd.org/tutorials/kqueue_tutorial/ <br>

