/*
* by wanghaimao 2020.6.24
* POSIX 线程
* 实验：一个简单的线程程序
*
*
*
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void *thread_function(void *arg);

char message[] = "Hello World";
int main()
{
	int res;
	pthread_t a_thread;
	void *thread_result;
	res = pthread_create(&a_thread, NULL, thread_function, (void*)message);
	if(res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Watting for thread to finish...\n");
	// 等价于进程用来收集子进程信息的wait函数
	res = pthread_join(a_thread, &thread_result);
	if(res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined, it returned %s\n",(char*)thread_result);
	printf("Message is now %s\n", message);
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
	printf("thread_function is running, Argument was %s\n", (char*)arg);
	sleep(3);
	strcpy(message, "Bye!");
	pthread_exit("Thanke for you the CPU time");
}
