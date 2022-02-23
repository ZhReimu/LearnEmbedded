#include "myHeader.h"

/**
 * @brief 设置某个像素的颜色
 * 
 * @param buff 要设置颜色的缓冲区指针
 * @param x 要设置颜色的像素坐标的 x
 * @param y 要设置颜色的像素坐标的 y
 * @param c 要设置的颜色
 * @see COLOR
 */
void setColor(char *buff, int x, int y, int c)
{
	int start = 0 + 4 * x + 800 * 4 * y;

	buff[0 + start] = 0;
	buff[1 + start] = 0;
	buff[2 + start] = 0;
	buff[3 + start] = 0;

	switch (c)
	{
	case RED:
		buff[2 + start] = 0xFF;
		break;
	case GREEN:
		buff[1 + start] = 0xFF;
		break;
	case BLUE:
		buff[0 + start] = 0xFF;
		break;
	}
}
/**
 * @brief 将 BMP 图片指定像素颜色设置到缓冲区
 * 
 * @param buff 要设置颜色的缓冲区指针
 * @param bmpBuff 要获取颜色的 BMP 文件缓冲区指针
 * @param x 要获取 && 设置 颜色的像素的 x 坐标
 * @param y 要获取 && 设置 颜色的像素的 y 坐标
 */
void setBMPColor(char *buff, char *bmpBuff, int x, int y)
{
	int start = 0 + 4 * x + 800 * 4 * y;
	int bStart = 0 + 3 * x + 800 * 3 * y;
	buff[0 + start] = bmpBuff[0 + bStart];
	buff[1 + start] = bmpBuff[1 + bStart];
	buff[2 + start] = bmpBuff[2 + bStart];
	buff[3 + start] = 0;
}
/**
 * @brief 读取 BMP 文件
 * 
 * @param fileName 要读取的文件名
 * @param bmp 存放结果的指针
 * @return int 读取的结果
 */
int readBMP(const char *fileName, char *bmp)
{
	//打开图片
	int BMP_fd = open(fileName, O_RDWR);
	if (BMP_fd < 0)
	{
		printf("Open Bmp Failed\n");
		return -1;
	}
	printf("Open Bmp OK\n");

	//偏移54个字节头信息
	lseek(BMP_fd, 54, SEEK_SET);

	int read_ret = read(BMP_fd, bmp, BMP_SIZE);
	if (read_ret < 0)
	{
		printf("Read Bmp Failed\n");
		return -1;
	}
	printf("Read Bmp OK\n");
	close(BMP_fd);
	return read_ret;
}
/**
 * @brief 打开 LCD 屏幕驱动文件
 * 
 * @param buff 屏幕缓冲区
 * @return int 操作结果, 正常返回 fd, 否则返回 -1
 */
int openLCD(char **buff)
{
	//打开lcd屏幕驱动文件
	int lcdfd = open(LCD_DEVICE, O_RDWR);
	if (lcdfd < 0)
	{
		printf("Open LCD_FD Failed\n");
		return -1;
	}
	printf("Open LCD_FD OK\n");

	*buff = mmap(NULL, BUFF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lcdfd, 0);
	cls(*buff, GREEN);

	puts("Clear Screen OK!");
	return lcdfd;
}
/**
 * @brief 清屏
 * 
 * @param buff 要清屏的缓冲区指针
 * @param c 要设置的颜色
 * @see COLOR
 */
void cls(char *buff, int c)
{
	int x, y;
	for (x = 0; x < 800; x++)
	{
		for (y = 0; y < 480; y++)
		{
			setColor(buff, x, y, c);
		}
	}
}