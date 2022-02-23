#include "myHeader.h"

/**
 * @brief 业务逻辑函数
 * 
 * @param lcdfd 要操作的 驱动文件 的 文件描述符
 * @param buff 要操作的缓冲区指针
 */
void doAction(int lcdfd, char *buff)
{
	//把bmp图片24位颜色数据读取出来
	char BMP_24bit[BMP_SIZE] = {};
	if (readBMP("1.bmp", BMP_24bit) < 0)
	{
		return;
	}
	int x, y;
	for (y = 0; y < 480; y++)
	{
		for (x = 0; x < 800; x++)
		{
			setBMPColor(buff, BMP_24bit, x, y);
		}
	}
}

int main()
{
	int lcdfd = -1;
	char *buff = NULL;

	if ((lcdfd = openLCD(&buff)) < 0)
	{
		return -1;
	}

	doAction(lcdfd, buff);
	//关闭驱动文件描述符
	munmap(buff, BUFF_SIZE);
	//关闭驱动文件描述符
	close(lcdfd);
	return 0;
}