#ifndef _BMPHEAD_H_
#define _BMPHEAD_H_

#include <stdio.h>
#include <stdint.h>

// uint32_t ---->unsigned int
// uint16_t ---->unsigned short

struct bmphead
{
	char bfType[2];			  //文件标志，BMP图片固定位"BM"
	uint32_t bfSIZE;		  //位图大小，以字节为单位
	uint16_t bfReserved1;	  //保留字，必须为0
	uint16_t bfReserved2;	  //保留字，必须为0
	uint32_t bf0ffBits;		  //文件开始到位图数据开始之间的偏移量
	uint32_t biSize;		  //图像描述信息块大小，常为 28H
	uint32_t Width;			  //图像宽度
	uint32_t Height;		  //图像高度
	uint16_t biPlanes;		  //图像的plane总数(恒为1)
	uint16_t biBitCount;	  //记录颜色的位数取值
	uint32_t biCompression;	  //数据压缩方式
	uint32_t biSizeImage;	  //图像区数据的大小，必须是4的倍数
	uint32_t biXPelsPerMeter; //水平每米多少像素
	uint32_t biYPelsPerMeter; //垂直每米多少像素
	uint32_t biClrUsed;		  //此图像所用颜色数
	uint32_t biClrImportant;  //重要颜色数，不用的话固定为0
} __attribute__((packed));	  //表示不让结构体对齐

//;
//__attribute__((aligned(4)));----强制结构体4字节对齐

#endif
