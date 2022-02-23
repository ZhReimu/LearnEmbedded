#include <stdio.h>
#include <strings.h>

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
#define BUFF_SIZE 800*480*4

//int x = 400;
//int y = 200;
//int width = 100;
//int height = 100;
//int endX = x + width;
//int endY = y + height;
int pow2(int x){
	return x*x;
}
int isInArea(int px, int py){
	int x = 600, y = 250;
	if(pow2(px-x) + pow2(py-y) <= pow2(100)){
		return 1;
	}
	return 0;
}

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
	
	// char buff[BUFF_SIZE] = {0};
	// write(lcdfd,buff,BUFF_SIZE);
	char* buff = mmap(NULL, BUFF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lcdfd, 0);
	puts("Clear Buff OK!");
	int x, y;
	for(y=100;y<150;y++)
	{
		for(x=100;x<150;x++)
		{
			buff[0+4*x+800*4*y] = 0;
			buff[1+4*x+800*4*y] = 255;
			buff[2+4*x+800*4*y] = 0;
			buff[3+4*x+800*4*y] = 0;
		}
	}
	// write(lcdfd,buff,BUFF_SIZE);
	puts("Square OK!");
	//bzero(buff, BUFF_SIZE);
	for(x = 200; x<300;x++ ){
		for(y = 200; y<=x;y++ ){
			buff[0+4*x+800*4*y] = 0;
			buff[1+4*x+800*4*y] = 0;
			buff[2+4*x+800*4*y] = 255;
			buff[3+4*x+800*4*y] = 0;
		}
	}
	
		for(x = 500; x<700;x++ ){
		for(y = 150; y<350;y++ ){
			if(isInArea(x, y)){
				buff[0+4*x+800*4*y] = 255;
				buff[1+4*x+800*4*y] = 0xCC;
				buff[2+4*x+800*4*y] = 0x66;
				buff[3+4*x+800*4*y] = 0;
			}
		}
	}
	
	write(lcdfd,buff,BUFF_SIZE);
	puts("Trangle OK!");
	//关闭驱动文件描述符
	close(lcdfd);
	
	return 0;
}