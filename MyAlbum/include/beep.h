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

void initBeep();
void beepStart(int delay);
void destroyBeep();

#endif