#include <beep.h>
#include <log.h>

static int fd;
static int ret;

static int isBeeping = 0;

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

void destroyBeep()
{
	close(fd);
}

void beepStop()
{
	ret = ioctl(fd, 1, 1);
	if (ret < 0)
	{
		debug("ioctl failed", ERROR);
		return;
	}
	debug("Beep Off", INFO);
}

void beepStart(int delay)
{
	ret = ioctl(fd, 0, 1);
	if (ret < 0)
	{
		debug("ioctl failed", ERROR);
		return;
	}
	debug("Beep On", INFO);
	usleep(delay);
	beepStop();
}
