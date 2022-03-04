#ifndef _BEEP_H
#define _BEEP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* pthread 头文件 */
#include <pthread.h>

/**
 * @brief 初始化 蜂鸣器
 * 
 */
void initBeep();
/**
 * @brief 启动蜂鸣器
 * 
 * @param delay 延时 delay 秒后 关闭蜂鸣器
 */
void beepStart(int delay);
/**
 * @brief 销毁 蜂鸣器
 * 
 */
void destroyBeep();

#endif