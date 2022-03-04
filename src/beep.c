#include <beep.h>
#include <log.h>
/**
 * @brief 蜂鸣器 驱动文件描述符
 * 
 */
static int fd;
/**
 * @brief 初始化 蜂鸣器
 * 
 */
void initBeep()
{
	//1.打开蜂鸣器驱动
	fd = open("/dev/beep", O_RDWR);
	//打开设备，成功返回0
	if (fd < 0)
	{
		exit(-1);
	}
}
/**
 * @brief 销毁 蜂鸣器
 * 
 */
void destroyBeep()
{
	close(fd);
}
/**
 * @brief 停止 蜂鸣器
 * 
 */
void beepStop()
{
	int ret = ioctl(fd, 1, 1);
	if (ret < 0)
	{
		debug("ioctl failed", ERROR);
		return;
	}
	debug("Beep Off", INFO);
}
/**
 * @brief 启动蜂鸣器
 * 
 * @param delay 延时 delay 秒后 关闭蜂鸣器
 */
void beepStart(int delay)
{
	int ret = ioctl(fd, 0, 1);
	if (ret < 0)
	{
		debug("ioctl failed", ERROR);
		return;
	}
	debug("Beep On", INFO);
	usleep(delay);
	beepStop();
}
