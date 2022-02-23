#include "myHeader.h"

/**
 * @brief 业务逻辑函数
 * 
 * @param lcdfd 要操作的 驱动文件 的 文件描述符
 * @param buff 要操作的缓冲区指针
 */
void doAction(int lcdfd, char *buff)
{
	char path[] = "./1.bmp";
	showBMP(path, 0, 0);
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