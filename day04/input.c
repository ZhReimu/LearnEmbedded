#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


/*调用 open 函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*调用 write close 函数的头文件 */
#include <unistd.h>

#include <sys/mman.h>

#include <linux/input.h>
#include <stdbool.h>
#include <pthread.h>

#define LCD_DEVICE	"/dev/fb0"	//---驱动工程师确定	应用开发工程师不管这些的

#define EVENT_DEVICE "/dev/input/event0"

int get_xy(int input_fd,int *x,int *y)
{
	bool xflag = false;
	bool yflag = false;
	

	
	//2.新建一个输入子系统模型的结构体
	struct input_event ts;
	bzero(&ts,sizeof(ts));
	
	//3.循环从驱动中去读取触摸数据，放到输入子系统模型里面
	//检测是否有触摸发生，如果没有触摸，代码会默认为阻塞状态
	while(1)
	{
		//读取触摸操作信息
		read(input_fd,&ts,sizeof(ts));
		
		//4.分析输入子系统模型存放的数据，就可以得到触摸坐标等信息
		if(ts.type == EV_ABS)
		{
			if(ts.code == ABS_X)
			{
				*x = ts.value;
				
				xflag = true;
			}
			if(ts.code == ABS_Y)
			{
				*y = ts.value;
				
				yflag = true;
			}
		}
		
		if(xflag == true && yflag == true )
		{
			break;
		}
		
	}
	
	printf("<x = %d, y = %d>\n",*x,*y);
	
}


int main()
{
	
	//1.打开触摸屏的驱动文件
	int input_fd = open(EVENT_DEVICE,O_RDWR);
	if(input_fd == -1)
	{
		printf("open EVENT_DEVICE failed\n");
		return -1;
	}
	printf("open EVENT_DEVICE OK\n");
	
	int x,y;
	while(1)
	{
		get_xy(input_fd,&x,&y);
	}
	
	
}