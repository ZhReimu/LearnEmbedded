#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <linux/fb.h>

#define LCD_DEVICE "/dev/fb0"

//显示fb的位域
void show_fb_bitfield(struct fb_bitfield color)
{
	//显示位域的偏移量
	printf("offset = %d\n", color.offset);
	//位域的长度
	printf("length = %d\n", color.length);
}

int main()
{
	//1.打开屏幕驱动
	int lcdfd = open(LCD_DEVICE, O_RDWR);
	if (lcdfd == -1)
	{
		perror("/dev/fb0 open failed\n");

		return -1;
	}
	printf("open lcd OK\n");

	//获取显存的信息
	struct fb_fix_screeninfo myfix;

	//获取设备文件参数
	ioctl(lcdfd, FBIOGET_FSCREENINFO, &myfix);

	printf("myfix.smem_start = %ld\n", myfix.smem_start);

	printf("myfix.smem_len   = %ld\n", myfix.smem_len);

	//获取屏幕信息
	struct fb_var_screeninfo myvar;

	ioctl(lcdfd, FBIOGET_VSCREENINFO, &myvar);

	printf("myvar.xres = %d\n", myvar.xres);

	printf("myvar.yres = %d\n", myvar.yres);

	printf("myvar.xres_virtual = %d\n", myvar.xres_virtual);

	printf("myvar.yres_virtual = %d\n", myvar.yres_virtual);

	printf("myvar.xoffset = %d\n", myvar.xoffset);

	printf("myvar.yoffset = %d\n", myvar.yoffset);

	printf("myvar.bits_per_pixel = %d\n", myvar.bits_per_pixel);

	printf("red:\n");
	show_fb_bitfield(myvar.red);

	printf("green:\n");
	show_fb_bitfield(myvar.green);

	printf("blue:\n");
	show_fb_bitfield(myvar.blue);

	printf("transp:\n");
	show_fb_bitfield(myvar.transp);

	close(lcdfd);

	return 0;
}
