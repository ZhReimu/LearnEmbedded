#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <string.h>
#include <strings.h>
/*调用 open 函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*调用 write close 函数的头文件 */
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <stdbool.h>

int ts_x, ts_y; //触摸坐标

//定义的线程的任务函数	用于触摸
void *fun(void *arg)
{
	//1.打开触摸屏驱动文件
	int ts_fd = open("/dev/input/event0", O_RDWR);
	if (ts_fd < 0)
	{
		printf("open ts_fd failed\n");
		exit(-1);
	}
	printf("open ts_fd OK\n");

	//2.读取触摸操作数据放到输入子系统中
	struct input_event ts;
	while (1)
	{
		while (1)
		{
			read(ts_fd, &ts, sizeof(ts));
			if (ts.type == EV_ABS)
			{
				if (ts.code == ABS_X)
				{
					ts_x = ts.value;
				}
				if (ts.code == ABS_Y)
				{
					ts_y = ts.value;
				}
			}
			if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0)
			{
				break;
			}
		}

		printf("x = %d\ny = %d\n", ts_x, ts_y);
	}
}

int main()
{
	//1.先给线程取名字
	pthread_t ts;
	//2.创建线程
	pthread_create(&ts, NULL, &fun, NULL);

	int movie_flag = 0;

	system("rm /pipe");

	system("mkfifo /pipe");

	system("chmod 777 /pipe");

	while (1)
	{
		//播放区域
		if (0 < ts_x && ts_x <= 200 && 0 < ts_y && ts_y <= 200 && movie_flag == 0)
		{
			ts_x = 0;
			ts_y = 0;

			system("mplayer -slave -quiet -input  file=/pipe  -geometry  0:0 -zoom -x 800 -y 480  dream.avi &");
			movie_flag = 1;
		}
		//暂停
		else if (200 < ts_x && ts_x <= 400 && 0 < ts_y && ts_y <= 200 && movie_flag == 1)
		{
			ts_x = 0;
			ts_y = 0;

			system("echo pause >> /pipe");
		}
		//继续
		/* if()
		{
			ts_x = 0;
			ts_y = 0;
			
			system("echo pause >> /pipe");
			
		} */
		//快进10

		//快退10
	}

	return 0;
}
