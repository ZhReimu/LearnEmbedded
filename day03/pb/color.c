#include "myHeader.h"

/**
 * @brief 业务逻辑函数
 * 
 * @param lcdfd 要操作的 驱动文件 的 文件描述符
 */
void doAction(int lcdfd)
{
	char *buff = mmap(NULL, BUFF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lcdfd, 0);
	cls(buff, GREEN);
	puts("Clear Screen OK!");
	int x, y;
	for (x = 100; x < 720; x++)
	{
		for (y = 420; y < 470; y++)
		{
			setColor(buff, x, y, RED);
			usleep(1000);
		}
	}
	write(lcdfd, buff, BUFF_SIZE);
	puts("ALL Done!");
}

int main()
{
	//打开lcd屏幕驱动文件
	int lcdfd = open(LCD_DEVICE, O_RDWR);
	if (lcdfd < 0)
	{
		printf("open lcdfd failed\n");
		return 0;
	}
	printf("open lcdfd OK\n");

	doAction(lcdfd);

	//关闭驱动文件描述符
	close(lcdfd);

	return 0;
}