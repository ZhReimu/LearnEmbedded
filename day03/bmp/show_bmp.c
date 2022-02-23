#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdlib.h>

#include <linux/fb.h>

#include "bmphead.h"

#define LCD_DEV "/dev/fb0"

struct lcd_info
{
	int fd;		  //屏幕文件描述符
	int width;	  //屏幕宽度
	int high;	  //屏幕高度
	int bits_per; //屏幕像素位数
};

//映射内存首地址
static int *lcdmem = NULL;

//初始化函数
//lcd屏幕初始化
static int lcd_init(struct lcd_info *lcdinfo)
{
	//1.打开lcd屏幕
	lcdinfo->fd = open(LCD_DEV, O_RDWR);
	if (lcdinfo->fd == -1)
	{
		perror("open lcd failed");
		return -1;
	}
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
	if (lcdmem == MAP_FAILED)
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
	if (fp == NULL)
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
	if (bmpbuf == NULL)
	{
		perror("malloc bmpbuf failed");
		exit(-1);
	}
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
	if (bmpARGB == NULL)
	{
		perror("malloc bmpARGB failed");
		exit(-1);
	}
	printf("malloc bmpARGB OK\n");
	for (i = 0; i < bmp_width * bmp_high; i++)
	{
		bmpARGB[i] = bmpbuf[3 * i + 2] << 16 | bmpbuf[3 * i + 1] << 8 | bmpbuf[3 * i];
	}
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

int main()
{
	//创建一个屏幕信息结构体子针
	struct lcd_info *lcdinfo = malloc(sizeof(struct lcd_info));
	if (lcdinfo == NULL)
	{
		perror("malloc struct lcd_info failed");
		return -1;
	}

	lcd_init(lcdinfo);

	show_bmp("1.bmp", 0, 0, lcdinfo);

	lcd_exit(lcdinfo);

	return 0;
}