#include <stdio.h>
#include <strings.h>
/* 调用 open 函数的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* 调用 write close 函数的头文件 */
#include <unistd.h>
/* 调用 mmap 的头文件 */
#include <sys/mman.h>

#define LCD_DEVICE	"/dev/fb0"	//---驱动工程师确定	应用开发工程师不管这些的
#define BUFF_SIZE 800 * 480 * 4

enum COLOR{
	RED, GREEN, BLUE
};

void setColor(char* buff, int x, int y, int c);