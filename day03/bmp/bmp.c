#include <stdio.h>

/*调用 open 函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*调用 write close 函数的头文件 */
#include <unistd.h>

#include <sys/mman.h>

#define LCD_DEVICE "/dev/fb0" //---驱动工程师确定	应用开发工程师不管这些的

#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF

/*
1.打开LCD驱动
2.打开图片，读取颜色数据
3.申请虚拟共享内存
4.24位bmp图片转换成32位的LCD数据
5.转换后的数据放到共享内存
6.关闭驱动和图片，释放内存
*/

int main()
{
	//打开lcd屏幕驱动文件
	int LCD_fd = open(LCD_DEVICE, O_RDWR);
	if (LCD_fd < 0)
	{
		printf("open lcdfd failed\n");
		return 0;
	}
	printf("open lcdfd OK\n");

	//打开图片
	int BMP_fd = open("1.bmp", O_RDWR);
	if (BMP_fd < 0)
	{
		printf("open bmp failed\n");
		return -1;
	}
	printf("open bmp OK\n");

	//申请虚拟共享内存
	char *share_addr = NULL;

	share_addr = mmap(NULL,					  //由系统分配
					  800 * 480 * 4,		  //,申请的空间大小
					  PROT_READ | PROT_WRITE, //内存空间的使用权限
					  MAP_SHARED,			  //内存的使用性质
					  LCD_fd,
					  0);

	//把bmp图片24位颜色数据读取出来
	char BMP_24bit[800 * 480 * 3] = {};

	//偏移54个字节头信息
	lseek(BMP_fd, 54, SEEK_SET);

	int read_ret = read(BMP_fd, BMP_24bit, 800 * 480 * 3);
	if (read_ret < 0)
	{
		printf("read bmp failed\n");
		return -1;
	}
	printf("read bmp OK\n");

	int x, y;
	for (y = 0; y < 480; y++)
	{
		for (x = 0; x < 800; x++)
		{
			share_addr[0 + 4 * x + 4 * 800 * y] = BMP_24bit[0 + 3 * x + 800 * 3 * y];
			share_addr[1 + 4 * x + 4 * 800 * y] = BMP_24bit[1 + 3 * x + 800 * 3 * y];
			share_addr[2 + 4 * x + 4 * 800 * y] = BMP_24bit[2 + 3 * x + 800 * 3 * y];
			share_addr[3 + 4 * x + 4 * 800 * y] = 0;
		}
	}

	//关闭驱动文件描述符
	munmap(share_addr, 800 * 480 * 4);
	close(BMP_fd);
	close(LCD_fd);

	return 0;
}