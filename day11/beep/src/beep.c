#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* pthread 头文件 */
#include <pthread.h>

static int fd;
static int ret;

int isBeeping = 0;

void initBeep()
{
	//1.打开蜂鸣器驱动
	fd = open("/dev/beep", O_RDWR);
	//打开设备，成功返回0
	if (fd < 0)
	{
		exit(-1);
	}
}

void *beepThread(void *args)
{
	while (isBeeping)
	{
		printf("==============buzeer On ================\n");
		ret = ioctl(fd, 1, 1);
		//BUZZER ON
		if (ret < 0)
		{
			perror("ioctl failed");
			return NULL;
		}
		sleep(2);
		printf("==============buzeer Off ================\n");
		ret = ioctl(fd, 0, 1);
		if (ret < 0)
		{
			perror("ioctl failed");
			return NULL;
		}
		sleep(2);
	}
}

static void onDestroyed()
{
	close(fd);
}

void startBeepThread()
{
	pthread_t th;
	int ret;
	int *thread_ret = NULL;
	ret = pthread_create(&th, NULL, beepThread, NULL);
	if (ret != 0)
	{
		return;
	}
	// 阻塞线程, 使 main 函数不会退出
	pthread_join(th, (void **)&thread_ret);
}

int main(void)
{
	startBeepThread();
	sleep(2);
	isBeeping = 0;
	return 0;
}
