#include <utils.h>

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
 * @return int 读取的结果, -1 为失败, 成功返回读取字节数
 */
int readBMP(const char *fileName, char *bmp)
{
	//打开图片
	int BMP_fd = open(fileName, O_RDONLY);
	if (BMP_fd < 0)
	{
		debug("Open Bmp Failed", ERROR);
		return -1;
	}
	debug("Open Bmp OK", DEBUG);

	// 偏移54个字节头信息, 只针对 24 位 或 32 位 位图格式
	// 否则还需处理 调色板 偏移
	lseek(BMP_fd, 54, SEEK_SET);

	int read_ret = read(BMP_fd, bmp, BMP_SIZE);
	if (read_ret < 0)
	{
		debug("Read Bmp Failed", ERROR);
		return -1;
	}
	debugS("Read Bmp %s OK", fileName, DEBUG);
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
	int lcdfd = open(LCD_DEVICE, O_RDONLY);
	if (lcdfd < 0)
	{
		debug("Open LCD_FD Failed", ERROR);
		return -1;
	}
	debug("Open LCD_FD OK", DEBUG);

	*buff = mmap(NULL, BUFF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lcdfd, 0);
	cls(*buff, GREEN);
	debug("Clear Screen OK!", DEBUG);
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

void get_xy(int input_fd, int *x, int *y)
{
	bool xflag = false;
	bool yflag = false;

	//2.新建一个输入子系统模型的结构体
	struct input_event ts;
	bzero(&ts, sizeof(ts));

	while (1)
	{
		read(input_fd, &ts, sizeof(ts));
		if (ts.type == EV_ABS)
		{
			if (ts.code == ABS_X)
			{
				*x = ts.value;
			}
			if (ts.code == ABS_Y)
			{
				*y = ts.value;
			}
		}
		if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0)
		{
			break;
		}
	}

	debug2D("<x = %d, y = %d>\n", *x, *y, DEBUG);
}
/**
 * @brief 获取当前点击屏幕的 x,y 值
 * 
 * @param x 当前点击的 x 坐标
 * @param y 当前点击的 y 坐标
 * @param onClick 回调函数, 点击屏幕时调用
 */
void getXY(int *x, int *y, void (*onClick)(int, int))
{
	//1.打开触摸屏的驱动文件
	static int input_fd = -1;
	if (input_fd == -1)
	{
		input_fd = open(EVENT_DEVICE, O_RDONLY);
		if (input_fd == -1)
		{
			debug("open EVENT_DEVICE failed", ERROR);
			return;
		}
		debug("open EVENT_DEVICE OK", DEBUG);
	}
	while (1)
	{
		get_xy(input_fd, x, y);
		(*onClick)(*x, *y);
	}
}
/**
 * @brief 从 int* [] 中获取指定下标的 指针
 * 
 * @param arg 要取下标的 int 指针数组
 * @param idx 下标
 * @return int* 取出的 int*
 */
int *getIntP(int *arg[], int idx)
{
	return arg[idx];
}
/**
 * @brief 从 thread 的 arg 中 获取 onClock 函数指针
 * 
 * @param arg thread 的参数
 * @return void* onClick 的函数指针
 */
void *getOnClick(void *arg[])
{
	return arg[2];
}

void *thread(void *arg)
{
	int *x = getIntP(arg, 0);
	int *y = getIntP(arg, 1);
	getXY(x, y, getOnClick(arg));
	return NULL;
}
/**
 * @brief 启动点击事件线程
 * 
 * @param onClick 回调函数, 参数为 当前屏幕点击的坐标
 */
void startTouchThread(void (*onClick)(int x, int y))
{
	pthread_t th;
	int ret;
	int x = 0;
	int y = 0;
	void *arg[3] = {&x, &y, onClick};
	int *thread_ret = NULL;
	ret = pthread_create(&th, NULL, thread, &arg);
	if (ret != 0)
	{
		debug("Create thread error!", ERROR);
		return;
	}
	debug("Touch Thread Started Successful", DEBUG);
	// 阻塞线程, 使 main 函数不会退出
	pthread_join(th, (void **)&thread_ret);
}
/**
 * @brief 判断点击位置是否在指定矩形范围内
 * 
 * @param startX 矩形左上角 x 坐标
 * @param startY 矩形左上角 x 坐标
 * @param endX 矩形右下角 x 坐标
 * @param endY 矩形右下角 y 坐标
 * @param x 点击的 x 坐标
 * @param y 点击 的 y坐标
 * @return true 点击位置在 rect 内
 * @return false 点击位置不在 rect 内
 */
bool inArea(int startX, int startY, int endX, int endY, int x, int y)
{
	if ((x >= startX && x <= endX && y >= startY && y <= endY) == 1)
	{
		return true;
	}
	return false;
}
/**
 * @brief 判断点击位置是否在指定矩形范围内
 * 
 * @param rect Rect 类型的 矩形区域变量
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 * @see inArea
 * @return true 点击位置在 rect 内
 * @return false 点击位置不在 rect 内
 */
bool inArea2(Rect rect, int x, int y)
{
	if (inArea(rect.startX, rect.startY, rect.endX, rect.endY, x, y) == 1)
	{
		return true;
	}
	return false;
}
/**
 * @brief 连接字符串
 * 
 * @param dst 结果数组
 * @param arg_cnt 参数个数
 * @param ... 要拼接的字符串
 */
void stringCat(char *dst, int arg_cnt, ...)
{
	va_list p_args;
	va_start(p_args, arg_cnt);
	int idx;
	char *val;
	for (idx = 1; idx <= arg_cnt; ++idx)
	{
		val = va_arg(p_args, char *);
		strcat(dst, val);
	}
	va_end(p_args);
}
/**
 * @brief 判断两个字符串是否相等
 * 
 * @param arg1 字符串 1
 * @param arg2 字符串 2
 * @return true 相等就返回 true
 * @return false 不等就返回 false
 */
bool stringCmp(const char *arg1, const char *arg2)
{
	if (strcmp(arg1, arg2) == 0)
	{
		return true;
	}
	return false;
}
/**
 * @brief 初始化 /pipe 文件
 * 
 */
void initPipe()
{
	system("rm /pipe");
	system("mkfifo /pipe");
	system("chmod 777 /pipe");
}