#include "myHeader.h"


int main()
{
	//打开lcd屏幕驱动文件
	int lcdfd = open(LCD_DEVICE,O_RDWR);
	if(lcdfd < 0)
	{
		printf("open lcdfd failed\n");
		return 0;
	}
	printf("open lcdfd OK\n");

	char buff[BUFF_SIZE] = {0};
	
	// write(lcdfd,buff,BUFF_SIZE);
	puts("Clear Buff OK!");
	int x, y;
	
	for(x=50;x<400;x++)
	{
		for(y=100;y<250;y++)
		{
			setColor(buff, x, y, BLUE);
		}
	}
	
	for(y=100;y<250;y++)
	{
		for(x=50;x<400;x++)
		{
			setColor(buff, x, y, BLUE);
		}
	}
	
	for(y=150;y<250;y++)
	{
		for(x=50;x<400;x++)
		{
			setColor(buff, x, y, GREEN);
		}
	}
	
	for(y=200;y<250;y++)
	{
		for(x=50;x<400;x++)
		{
			setColor(buff, x, y, RED);
		}
	}
	
	write(lcdfd,buff,BUFF_SIZE);
	puts("ALL Done!");
	//关闭驱动文件描述符
	close(lcdfd);
	
	return 0;
}