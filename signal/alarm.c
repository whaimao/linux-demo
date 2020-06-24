/*
* by wanghaimao  2020.6.24
* 第 11 章，进程与信号
* 实验：模拟一个闹钟
*/
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;
// 模拟一个闹钟
void ding(int sig)
{
	alarm_fired = 1;
}

// 告诉子进程在等待5s 后发生一个SIGALRM信号给他的父进程
int main()
{
	pid_t pid;
	printf("alarm application starting!\n");

	pid = fork();
	switch(pid){
	case -1:
		/* Failure */
		perror("fork failed");
		exit(0);
	case 0:
		/* child */
		sleep(5);
		kill(getppid(), SIGALRM);
		exit(0);
	}
	// 父进程通过一个signal 调用安排好捕获SIGALRM信号的工作，然后等待它的到来。
	/* if we get here we are the parent process */
	(void) signal(SIGALRM, ding);
	/* pause 把程序的执行挂起，直到有一个信号出现为止，之后恢复执行*/
	pause();
	if(alarm_fired)
		printf("Ding!\n");
	printf("done\n");
	exit(0);
	
}
