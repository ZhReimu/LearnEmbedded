#ifndef _MYHEADER_H_
#define _MYHEADER_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
/* 调用 open 函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* 调用 write close 函数的头文件 */
#include <unistd.h>
/* 调用 mmap 的头文件 */
#include <sys/mman.h>

#include "bmphead.h"

#define LCD_DEVICE "/dev/fb0" //---驱动工程师确定	应用开发工程师不管这些的
/**
 * @brief 像素个数
 * 
 */
#define BUFF_SIZE 800 * 480 * 4
/**
 * @brief BMP 文件大小 ( 字节 )
 * 
 */
#define BMP_SIZE 800 * 480 * 3

/**
 * @brief 颜色枚举
 * 
 */
enum COLOR
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	PINK,
	SAKURA,
	ORANGE,
	CYAN
};
/**
 * @brief 设置某个像素的颜色
 * 
 * @param buff 要设置颜色的缓冲区指针
 * @param x 要设置颜色的像素坐标的 x 坐标
 * @param y 要设置颜色的像素坐标的 y 坐标
 * @param c 要设置的颜色
 * @see COLOR
 */
void setColor(char *buff, int x, int y, int c);
/**
 * @brief 将 BMP 图片指定像素颜色设置到缓冲区
 * 
 * @param buff 要设置颜色的缓冲区指针
 * @param bmpBuff 要获取颜色的 BMP 文件缓冲区指针
 * @param x 要获取 && 设置 颜色的像素的 x 坐标
 * @param y 要获取 && 设置 颜色的像素的 y 坐标
 */
void setBMPColor(char *buff, char *bmpBuff, int x, int y);
/**
 * @brief 读取 BMP 文件
 * 
 * @param fileName 要读取的文件名
 * @param bmp 存放结果的指针
 * @return int 读取的结果
 */
int readBMP(const char *fileName, char *bmp);
/**
 * @brief 打开 LCD 屏幕驱动文件
 * 
 * @param buff 屏幕缓冲区
 * @return int 操作结果, 正常返回 fd, 否则返回 -1
 */
int openLCD(char **buff);
/**
 * @brief 清屏
 * 
 * @param buff 要清屏的缓冲区指针
 * @param c 要设置的颜色
 * @see COLOR
 */
void cls(char *buff, int c);
/**
 * @brief 获取随机颜色
 * 
 * @return int 随机颜色 RED, GREEN, BLUE
 */
int radColor();
#endif