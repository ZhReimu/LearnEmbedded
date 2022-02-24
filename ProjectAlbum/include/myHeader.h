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
/* 获取屏幕信息的头文件 */
#include <linux/fb.h>
#include <sys/ioctl.h>
/* 按键事件头文件 */
#include <linux/input.h>
#include <stdbool.h>
#include <pthread.h>

#include "bmphead.h"

#define LCD_DEVICE "/dev/fb0" //---驱动工程师确定	应用开发工程师不管这些的

#define EVENT_DEVICE "/dev/input/event0" // 触摸设备

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
 * @brief 日志等级枚举
 * 
 */
enum LOG
{
	DEBUG,
	INFO,
	WARN,
	ERROR
};

/**
 * @brief 当前日志等级
 * 
 */
#define LOG_LEVEL INFO

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
 * @brief LCD 信息结构体
 * 
 */
struct lcd_info
{
	int fd;		  //屏幕文件描述符
	int width;	  //屏幕宽度
	int high;	  //屏幕高度
	int bits_per; //屏幕像素位数
};
/**
 * @brief 矩形 结构体
 * 
 */
typedef struct rect
{
	int startX;
	int startY;
	int endX;
	int endY;
} Rect;

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
/**
 * @brief 在指定位置显示一个 bmp 图片
 * 
 * @param fileName 要显示的 bmp 文件路径
 * @param x 显示坐标 x
 * @param y 显示坐标 y
 */
void showBMP(const char *fileName, int x, int y);
/**
 * @brief 获取当前点击屏幕的 x,y 值
 * 
 * @param x 当前点击的 x 坐标
 * @param y 当前点击的 y 坐标
 * @param onClick 回调函数, 点击屏幕时调用
 */
void getXY(int *x, int *y, void (*onClick)(int x, int y));
/**
 * @brief 启动点击事件线程
*/
void startTouchThread();
/**
 * @brief 判断点击位置是否在指定矩形范围内
 * 
 * @param startX 矩形左上角 x 坐标
 * @param startY 矩形左上角 x 坐标
 * @param endX 矩形右下角 x 坐标
 * @param endY 矩形右下角 y 坐标
 * @param x 点击的 x 坐标
 * @param y 点击 的 y坐标
 * @return int 如果是, 返回 1 否则 返回 0
 */
int inArea(int startX, int startY, int endX, int endY, int x, int y);
/**
 * @brief 判断点击位置是否在指定矩形范围内
 * 
 * @param rect Rect 类型的 矩形区域变量
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 * @see inArea
 * @return int 如果是, 返回 1 否则 返回 0
 */
int inArea2(Rect rect, int x, int y);
void debug(const char *msg, int logType);
void debugD(const char *format, int arg, int logType);
void debugS(const char *format, const char *args, int logType);
void debug2D(const char *format, int arg, int arg2, int logType);
#endif