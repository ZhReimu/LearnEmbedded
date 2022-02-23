#include <stdio.h>

/*调用 open 函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*调用 write close 函数的头文件 */
#include <unistd.h>

#define LCD_DEVICE	"/dev/fb0"	//---驱动工程师确定	应用开发工程师不管这些的

#define RED		0x00FF0000
#define GREEN	0x0000FF00
#define BLUE	0x000000FF

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
	
	//让lcd屏幕显示绿色----向lcd屏幕中写入绿色
	
	int i;
	int color1 = GREEN;
	int color2 = RED;
	int color3 = BLUE;
	
	for(i=0;i<800*480;i++)
	{
		
		write(lcdfd,&color1,4);
	}
	
	
	
	
	//关闭驱动文件描述符
	close(lcdfd);
	
	return 0;
}