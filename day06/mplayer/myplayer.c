#include <myHeader.h>

/**
 * @brief 暂停, 继续 按钮
 * 
 */
Rect btPlayAndPause;
/**
 * @brief 快进 按钮
 * 
 */
Rect btFastForward;
/**
 * @brief 快退 按钮
 * 
 */
Rect btBack;
/**
 * @brief 首页 按钮
 * 
 */
Rect btHome;
/**
 * @brief 播放状态 枚举
 * 
 */
enum SATTUS
{
	/**
	 * @brief 暂停中
	 * 
	 */
	PAUSED,
	/**
	 * @brief 播放中
	 * 
	 */
	STARTED,
	/**
	 * @brief 停止中
	 * 
	 */
	STOPED,
};
/**
 * @brief 当前播放状态
 * 
 */
static int playStatus = STOPED;
/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
	static int i = 0;
	debug2D("Touch Thread Callback OnClick in Main : %d, %d", x, y, INFO);
	if (inArea2(btPlayAndPause, x, y))
	{
		if (playStatus == STOPED)
		{
			debug("Play", INFO);
			playStatus = STARTED;
			showBMP("/mnt/udisk/2/video-ui-start.bmp", 0, 0, 0);
			system("mplayer -slave -quiet -input  file=/pipe -zoom -x 800 -y 430 -nosound /mnt/udisk/dream.avi &");
		}
		else if (playStatus == STARTED)
		{
			showBMP("/mnt/udisk/2/video-ui-stop.bmp", 0, 0, 0);
			playStatus = PAUSED;
			system("echo pause >> /pipe");
			debug("Paused", INFO);
		}
		else if (playStatus == PAUSED)
		{
			playStatus = STARTED;
			showBMP("/mnt/udisk/2/video-ui-start.bmp", 0, 0, 0);
			system("echo pause >> /pipe");
			debug("Resume", INFO);
		}
	}
	else if (inArea2(btFastForward, x, y))
	{
		if (playStatus)
		{
			system("echo seek +5 >> /pipe");
			debug("FastForward", INFO);
		}
	}
	else if (inArea2(btBack, x, y))
	{
		if (playStatus)
		{
			system("echo seek -5 >> /pipe");
			debug("Back", INFO);
		}
	}
	else if (inArea2(btHome, x, y))
	{
		// fixme: 主页 点击卡死
		if (playStatus == STARTED || playStatus == PAUSED)
		{
			playStatus = STOPED;
			system("killall -kill mplayer");
			showBMP("/mnt/udisk/2/video-ui-stop.bmp", 0, 0, 0);
			debug("Home", INFO);
		}
	}
	else
	{
		debug("Not Hit", INFO);
	}
}
void init()
{
	btPlayAndPause.startX = 342;
	btPlayAndPause.startY = 550;
	btPlayAndPause.endX = 684;
	btPlayAndPause.endY = 614;

	btFastForward.startX = 684;
	btFastForward.startY = 550;
	btFastForward.endX = 960;
	btFastForward.endY = 614;

	btBack.startX = 0;
	btBack.startY = 550;
	btBack.endX = 341;
	btBack.endY = 614;

	btHome.startX = 960;
	btHome.startY = 563;
	btHome.endX = 1024;
	btHome.endY = 614;
}

int main()
{
	init();
	// system("mplayer -slave -quiet -input  file=/pipe  -geometry  0:0 -zoom -x 800 -y 480  dream.avi &");
	// system("echo pause >> /pipe");
	system("rm /pipe");
	system("mkfifo /pipe");
	system("chmod 777 /pipe");
	showBMP("/mnt/udisk/2/video-ui-stop.bmp", 0, 0, 0);
	startTouchThread(onClick);
	return 0;
}
