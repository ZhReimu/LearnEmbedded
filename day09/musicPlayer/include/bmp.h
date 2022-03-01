#ifndef _BMPHEAD_H_
#define _BMPHEAD_H_

#include <log.h>
#include <stdio.h>
#include <stdint.h>
/* 调用 open 函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* 调用 write close 函数的头文件 */
#include <unistd.h>
/* 获取屏幕信息的头文件 */
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <stdlib.h>
/* 调用 mmap 的头文件 */
#include <sys/mman.h>

// uint32_t ---->unsigned int
// uint16_t ---->unsigned short

struct bmphead
{
    char bfType[2];           //文件标志，BMP图片固定位"BM"
    uint32_t bfSIZE;          //位图大小，以字节为单位
    uint16_t bfReserved1;     //保留字，必须为0
    uint16_t bfReserved2;     //保留字，必须为0
    uint32_t bf0ffBits;       //文件开始到位图数据开始之间的偏移量
    uint32_t biSize;          //图像描述信息块大小，常为 28H
    uint32_t Width;           //图像宽度
    uint32_t Height;          //图像高度
    uint16_t biPlanes;        //图像的plane总数(恒为1)
    uint16_t biBitCount;      //记录颜色的位数取值
    uint32_t biCompression;   //数据压缩方式
    uint32_t biSizeImage;     //图像区数据的大小，必须是4的倍数
    uint32_t biXPelsPerMeter; //水平每米多少像素
    uint32_t biYPelsPerMeter; //垂直每米多少像素
    uint32_t biClrUsed;       //此图像所用颜色数
    uint32_t biClrImportant;  //重要颜色数，不用的话固定为0
} __attribute__((packed));    //表示不让结构体对齐

//;
//__attribute__((aligned(4)));----强制结构体4字节对齐

/**
 * @brief LCD 信息结构体
 * 
 */
struct lcd_info
{
    /**
	 * @brief 屏幕文件描述符
	 * 
	 */
    int fd;
    /**
	 * @brief 屏幕宽度
	 * 
	 */
    int width;
    /**
	 * @brief 屏幕高度
	 * 
	 */
    int high;
    /**
	 * @brief 屏幕像素位数
	 * 
	 */
    int bits_per;
};

/**
 * @brief lcd 设备驱动文件路径
 * 
 */
#define LCD_DEVICE "/dev/fb0"

/**
 * @brief 在指定位置显示一个 bmp 图片
 * 
 * @param fileName 要显示的 bmp 文件路径
 * @param x 显示坐标 x
 * @param y 显示坐标 y
 * @param isTransport 是否透明
 */
void showBMP(const char *fileName, int x, int y, int isTransport);
/**
 * @brief 在 0,0 的位置 显示一个 非透明的图片
 * 
 * @param fileName 图片文件名
 */
void showBMPOO(const char *fileName);
#endif
