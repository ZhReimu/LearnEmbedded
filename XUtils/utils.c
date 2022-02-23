#include "myHeader.h"

/**
 * @brief 为指定的像素点设置颜色
 * 
 * @param buff 屏幕缓冲区
 * @param start 像素点所在位置
 * @param r R
 * @param g G
 * @param b B
 */
void setColor2(char *buff, int start, int r, int g, int b)
{
	buff[0 + start] = b; // B
	buff[1 + start] = g; // G
	buff[2 + start] = r; // R
	buff[3 + start] = 0; // A
}
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
	switch (c)
	{
	case RED:
		setColor2(buff, start, 0xFF, 0, 0);
		break;
	case GREEN:
		setColor2(buff, start, 0, 0xFF, 0);
		break;
	case BLUE:
		setColor2(buff, start, 0, 0, 0xFF);
		break;
	case PINK:
		setColor2(buff, start, 0xEF, 0x5B, 0x9C);
		break;
	case SAKURA:
		setColor2(buff, start, 0xFE, 0xEE, 0xED);
		break;
	case ORANGE:
		setColor2(buff, start, 0xFA, 0xA7, 0x55);
		break;
	case CYAN:
		setColor2(buff, start, 0, 0x9A, 0xD6);
		break;
	case BLACK:
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
	if (BMP_fd < 0 && DEBUG)
	{
		printf("Open Bmp Failed\n");
		return -1;
	}
	if (DEBUG)
		printf("Open Bmp OK\n");

	//偏移54个字节头信息
	lseek(BMP_fd, 54, SEEK_SET);

	int read_ret = read(BMP_fd, bmp, BMP_SIZE);
	if (read_ret < 0 && DEBUG)
	{
		printf("Read Bmp Failed\n");
		return -1;
	}
	if (DEBUG)
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
	if (lcdfd < 0 && DEBUG)
	{
		printf("Open LCD_FD Failed\n");
		return -1;
	}
	if (DEBUG)
		printf("Open LCD_FD OK\n");

	*buff = mmap(NULL, BUFF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lcdfd, 0);
	cls(*buff, GREEN);
	if (DEBUG)
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
/**
 * @brief 生成随机范围的随机数
 * 
 * @param min 最小值 ( 包括 )
 * @param max 最大值 ( 包括 )
 * @return int 返回 [min, max] 范围的值
 */
int rad(int min, int max)
{
	srand((unsigned int)time(NULL));
	return rand() % (max - min + 1) + min;
}
/**
 * @brief 生成随机颜色的枚举
 * 
 * @return int 在 COLOR 枚举里定义的 随机颜色
 */
int radColor()
{
	return rad(0, 7);
}

//映射内存首地址
static int *lcdmem = NULL;

//初始化函数
//lcd屏幕初始化
static int lcd_init(struct lcd_info *lcdinfo)
{
	//1.打开lcd屏幕
	lcdinfo->fd = open(LCD_DEVICE, O_RDWR);
	if (lcdinfo->fd == -1 && DEBUG)
	{
		perror("open lcd failed");
		return -1;
	}
	if (DEBUG)
		printf("open lcd OK\n");

	//获取lcd屏幕信息
	struct fb_var_screeninfo lcdvar;

	ioctl(lcdinfo->fd, FBIOGET_VSCREENINFO, &lcdvar);

	printf("lcd屏幕宽度=%d\n", lcdvar.xres);
	printf("lcd屏幕高度=%d\n", lcdvar.yres);
	printf("lcd屏幕位数=%d\n", lcdvar.bits_per_pixel);

	lcdinfo->width = lcdvar.xres;
	lcdinfo->high = lcdvar.yres;
	lcdinfo->bits_per = lcdvar.bits_per_pixel;

	//申请内存映射
	lcdmem = mmap(
		NULL,
		lcdinfo->width * lcdinfo->high * lcdinfo->bits_per / 8,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		lcdinfo->fd,
		0);
	if (lcdmem == MAP_FAILED && DEBUG)
	{
		perror("mmap lcd failed");
		return -1;
	}
}

//功能函数
void show_bmp(char *pathname, int x_begin, int y_begin, struct lcd_info *lcdinfo)
{
	int bmp_width;
	int bmp_high;
	int bmp_bit;

	FILE *fp = fopen(pathname, "r");
	if (fp == NULL && DEBUG)
	{
		perror("fopen bmp failed");
		return;
	}

	//读取头文件信息
	struct bmphead bmphead_buf;
	fread(&bmphead_buf, 54, 1, fp);

	printf("图片的宽度:%d\n", bmphead_buf.Width);
	printf("图片的高度:%d\n", bmphead_buf.Height);
	printf("图片的位数:%d\n", bmphead_buf.biBitCount);

	bmp_width = bmphead_buf.Width;
	bmp_high = bmphead_buf.Height;
	bmp_bit = bmphead_buf.biBitCount;

	//设置bmp图片颜色的缓冲区
	char *bmpbuf = malloc(bmp_width * bmp_high * bmp_bit / 8);
	if (bmpbuf == NULL && DEBUG)
	{
		perror("malloc bmpbuf failed");
		exit(-1);
	}
	if (DEBUG)
		printf("malloc bmpbuf OK\n");
	//先计算是否有4字节补齐，如果有，求出补齐了多少个字节
	int add_size = (4 - (bmp_width * bmp_bit / 8) % 4) % 4;

	//每次读取一行数据的时候就要偏移add_size个字节，循环次数，就是图片的高度
	int i;
	for (i = 0; i < bmp_high; i++)
	{
		//每次读取的时候，保存到bmpbuf缓冲区的位置应该进行偏移
		fread(bmpbuf + (bmp_width * bmp_bit / 8) * i, bmp_width * bmp_bit / 8, 1, fp);
		fseek(fp, add_size, SEEK_CUR);
	}

	//以字节对齐的方式，将RGB颜色换成ARGB的颜色数据
	int *bmpARGB = malloc(bmp_high * bmp_width * 4);
	if (bmpARGB == NULL && DEBUG)
	{
		perror("malloc bmpARGB failed");
		exit(-1);
	}
	if (DEBUG)
		printf("malloc bmpARGB OK\n");
	for (i = 0; i < bmp_width * bmp_high; i++)
	{
		bmpARGB[i] = bmpbuf[3 * i + 2] << 16 | bmpbuf[3 * i + 1] << 8 | bmpbuf[3 * i];
	}
	if (DEBUG)
		printf(" << OK\n");
	int x, y;
	for (x = 0; x + x_begin < lcdinfo->width && x < bmp_width; x++)
	{
		for (y = 0; y + y_begin < lcdinfo->high && y < bmp_high; y++)
		{
			//对于x=0和y=0的坐标而言，lcd屏幕已经偏移了
			int lcd_offset = x + x_begin + lcdinfo->width * (y + y_begin);
			int bmp_offset = x + bmp_width * (bmp_high - y - 1);

			*(lcdmem + lcd_offset) = bmpARGB[bmp_offset];
		}
	}

	free(bmpbuf);
	free(bmpARGB);

	fclose(fp);
}

//销毁函数
static void lcd_exit(struct lcd_info *lcdinfo)
{
	//释放了映射内存
	munmap(lcdmem, lcdinfo->width * lcdinfo->high * lcdinfo->bits_per / 8);

	//关闭屏幕
	close(lcdinfo->fd);

	//释放lcd结构体的堆空间
	free(lcdinfo);
}
/**
 * @brief 在指定位置显示一个 bmp 图片
 * 
 * @param fileName 要显示的 bmp 文件路径
 * @param x 显示坐标 x
 * @param y 显示坐标 y
 */
void showBMP(char *fileName, int x, int y)
{
	// 创建一个屏幕信息结构体指针
	static struct lcd_info *lcdinfo;
	lcdinfo = malloc(sizeof(struct lcd_info));
	if (lcdinfo == NULL && DEBUG)
	{
		perror("malloc struct lcd_info failed");
		return;
	}
	if (lcdmem == NULL)
	{
		lcd_init(lcdinfo);
	}
	show_bmp(fileName, x, y, lcdinfo);
	lcd_exit(lcdinfo);
}