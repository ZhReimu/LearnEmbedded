#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
  
#define TEST_MAGIC 'x'                           //�������

 //����LED��ħ����
#define LED1 _IO(TEST_MAGIC, 0)              
#define LED2 _IO(TEST_MAGIC, 1)
#define LED3 _IO(TEST_MAGIC, 2)
#define LED4 _IO(TEST_MAGIC, 3) 

#define LED_ON  	0	//����
#define LED_OFF		1   //����

int main(void)
{
	int val;
	//1.�򿪵�����
	int led_fd = open("/dev/Led");
	if(led_fd == -1)
	{
		perror("can not open /dev/LED");
		return 0;
	}

	ioctl(led_fd,LED1,LED_OFF);
	ioctl(led_fd,LED2,LED_OFF);
	ioctl(led_fd,LED3,LED_OFF);
	ioctl(led_fd,LED4,LED_OFF);
		
	
	while(1)
	{		
		ioctl(led_fd,LED1,LED_ON);
		sleep(1);
		
		ioctl(led_fd,LED1,LED_OFF);
		
		sleep(1);
	}
	
	close(led_fd);
	
	return 0;
}





