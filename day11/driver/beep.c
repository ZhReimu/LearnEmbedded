#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ioctl.h>
#include <types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	int ret;
	//1.打开蜂鸣器驱动
	fd = open("/dev/beep",O_RDWR);
	//打开设备，成功返回0
	if(fd < -)
	{
		perror("open beep failed");
		
		return -1;
	}
	while(1)
	{
		printf("==============buzeer On ================\n");
		ret = ioctl(fd,1,1);
		
		//BUZZER ON
		if(ret < 0)
		{
			perror("ioctl failed");
			return -1;
		}
		
		sleep(2);
		
		printf("==============buzeer Off ================\n");
		
		ret = ioctl(fd,0,1);
		
		if(ret < 0)
		{
			perror("ioctl failed");
			
			return -1;
		}
		
		sleep(2);
		
		
		
	}
	close(fd);
	return 0;
}

