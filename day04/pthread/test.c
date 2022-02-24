#include <stdio.h>  
#include <pthread.h> 

int *getIntP(int *arg[], int idx){
	return arg[idx];
}

void *thread(void *arg)
{
	int* x = getIntP(arg, 0);
	int* y = getIntP(arg, 1);
	printf("This is a thread and arg = %d, %d.\n", *x,*y);
	*x = 1234;
	*y = 5678;
	return NULL;
}

void startTouchThread(){
	pthread_t th;
	int ret;
	int x = 12;
	int y = 34;
	int *arg[2] = {&x, &y};
	
	int *thread_ret = NULL;
	ret = pthread_create(&th, NULL, thread, &arg);
	if (ret != 0)
	{
		printf("Create thread error!\n");
		return;
	}
	printf("This is the main process.\n");
	pthread_join(th, (void **)&thread_ret);
	printf("This is a arg = %d, %d.\n", x,y);
}
int main(int argc, char *argv[])
{
	startTouchThread();
	return 0;
}
