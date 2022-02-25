#include <myHeader.h>

/**
 * @brief 上一页 按钮区域
 * 
 */
Rect btPrev;
/**
 * @brief 下一页 按钮区域
 * 
 */
Rect btNext;
/**
 * @brief 暂停播放 按钮区域
 * 
 */
Rect btPause;
/**
 * @brief 相册图片 数组
 * 
 */
const char *pics[] = {
	"/mnt/udisk/2/bmp2/01.bmp",
	"/mnt/udisk/2/bmp2/02.bmp",
	"/mnt/udisk/2/bmp2/03.bmp",
	"/mnt/udisk/2/bmp2/04.bmp",
	"/mnt/udisk/2/bmp2/05.bmp",
	"/mnt/udisk/2/bmp2/06.bmp",
	"/mnt/udisk/2/bmp2/07.bmp",
	"/mnt/udisk/2/bmp2/08.bmp",
	"/mnt/udisk/2/bmp2/09.bmp",
};
/**
 * @brief 自动播放时的 相册图片 数组
 * 
 */
const char *picsPlaying[] = {
	"/mnt/udisk/2/bmp1/01.bmp",
	"/mnt/udisk/2/bmp1/02.bmp",
	"/mnt/udisk/2/bmp1/03.bmp",
	"/mnt/udisk/2/bmp1/04.bmp",
	"/mnt/udisk/2/bmp1/05.bmp",
	"/mnt/udisk/2/bmp1/06.bmp",
	"/mnt/udisk/2/bmp1/07.bmp",
	"/mnt/udisk/2/bmp1/08.bmp",
	"/mnt/udisk/2/bmp1/09.bmp",
};
/**
 * @brief 进度条 图片
 * 
 */
const char *pb = "/mnt/udisk/2/tiger.bmp";
/**
 * @brief 开机动画 数组
 * 
 */
const char *videos[] = {
	"/mnt/udisk/1/001.bmp",
	"/mnt/udisk/1/002.bmp",
	"/mnt/udisk/1/003.bmp",
	"/mnt/udisk/1/004.bmp",
	"/mnt/udisk/1/005.bmp",
	"/mnt/udisk/1/006.bmp",
	"/mnt/udisk/1/007.bmp",
	"/mnt/udisk/1/008.bmp",
	"/mnt/udisk/1/009.bmp",
	"/mnt/udisk/1/010.bmp",
	"/mnt/udisk/1/011.bmp",
	"/mnt/udisk/1/012.bmp",
	"/mnt/udisk/1/013.bmp",
	"/mnt/udisk/1/014.bmp",
	"/mnt/udisk/1/015.bmp",
	"/mnt/udisk/1/016.bmp",
	"/mnt/udisk/1/017.bmp",
	"/mnt/udisk/1/018.bmp",
	"/mnt/udisk/1/019.bmp",
	"/mnt/udisk/1/020.bmp",
	"/mnt/udisk/1/021.bmp",
	"/mnt/udisk/1/022.bmp",
	"/mnt/udisk/1/023.bmp",
	"/mnt/udisk/1/024.bmp",
	"/mnt/udisk/1/025.bmp",
	"/mnt/udisk/1/026.bmp",
	"/mnt/udisk/1/027.bmp",
	"/mnt/udisk/1/028.bmp",
	"/mnt/udisk/1/029.bmp",
	"/mnt/udisk/1/030.bmp",
	"/mnt/udisk/1/031.bmp",
	"/mnt/udisk/1/032.bmp",
	"/mnt/udisk/1/033.bmp",
	"/mnt/udisk/1/034.bmp",
	"/mnt/udisk/1/035.bmp",
	"/mnt/udisk/1/036.bmp",
	"/mnt/udisk/1/037.bmp",
	"/mnt/udisk/1/038.bmp",
	"/mnt/udisk/1/039.bmp",
	"/mnt/udisk/1/040.bmp",
	"/mnt/udisk/1/041.bmp",
	"/mnt/udisk/1/042.bmp",
	"/mnt/udisk/1/043.bmp",
	"/mnt/udisk/1/044.bmp",
	"/mnt/udisk/1/045.bmp",
	"/mnt/udisk/1/046.bmp",
	"/mnt/udisk/1/047.bmp",
	"/mnt/udisk/1/048.bmp",
	"/mnt/udisk/1/049.bmp",
	"/mnt/udisk/1/050.bmp",
	"/mnt/udisk/1/051.bmp",
	"/mnt/udisk/1/052.bmp",
	"/mnt/udisk/1/053.bmp",
	"/mnt/udisk/1/054.bmp",
	"/mnt/udisk/1/055.bmp",
	"/mnt/udisk/1/056.bmp",
	"/mnt/udisk/1/057.bmp",
	"/mnt/udisk/1/058.bmp",
	"/mnt/udisk/1/059.bmp",
	"/mnt/udisk/1/060.bmp",
	"/mnt/udisk/1/061.bmp",
	"/mnt/udisk/1/062.bmp",
	"/mnt/udisk/1/063.bmp",
	"/mnt/udisk/1/064.bmp",
	"/mnt/udisk/1/065.bmp",
	"/mnt/udisk/1/066.bmp",
	"/mnt/udisk/1/067.bmp",
	"/mnt/udisk/1/068.bmp",
	"/mnt/udisk/1/069.bmp",
	"/mnt/udisk/1/070.bmp",
	"/mnt/udisk/1/071.bmp",
	"/mnt/udisk/1/072.bmp",
	"/mnt/udisk/1/073.bmp",
	"/mnt/udisk/1/074.bmp",
	"/mnt/udisk/1/075.bmp",
	"/mnt/udisk/1/076.bmp",
	"/mnt/udisk/1/077.bmp",
	"/mnt/udisk/1/078.bmp",
	"/mnt/udisk/1/079.bmp",
	"/mnt/udisk/1/080.bmp",
	"/mnt/udisk/1/081.bmp",
	"/mnt/udisk/1/082.bmp",
	"/mnt/udisk/1/083.bmp",
	"/mnt/udisk/1/084.bmp",
	"/mnt/udisk/1/085.bmp",
	"/mnt/udisk/1/086.bmp",
	"/mnt/udisk/1/087.bmp",
	"/mnt/udisk/1/088.bmp",
	"/mnt/udisk/1/089.bmp",
	"/mnt/udisk/1/090.bmp",
	"/mnt/udisk/1/091.bmp",
	"/mnt/udisk/1/092.bmp",
	"/mnt/udisk/1/093.bmp",
	"/mnt/udisk/1/094.bmp",
	"/mnt/udisk/1/095.bmp",
	"/mnt/udisk/1/096.bmp",
	"/mnt/udisk/1/097.bmp",
	"/mnt/udisk/1/098.bmp",
	"/mnt/udisk/1/099.bmp",
	"/mnt/udisk/1/100.bmp",
	"/mnt/udisk/1/101.bmp",
	"/mnt/udisk/1/102.bmp",
	"/mnt/udisk/1/103.bmp",
	"/mnt/udisk/1/104.bmp",
	"/mnt/udisk/1/105.bmp",
	"/mnt/udisk/1/106.bmp",
	"/mnt/udisk/1/107.bmp",
	"/mnt/udisk/1/108.bmp",
	"/mnt/udisk/1/109.bmp",
	"/mnt/udisk/1/110.bmp",
	"/mnt/udisk/1/111.bmp",
	"/mnt/udisk/1/112.bmp",
	"/mnt/udisk/1/113.bmp",
	"/mnt/udisk/1/114.bmp",
	"/mnt/udisk/1/115.bmp",
	"/mnt/udisk/1/116.bmp",
	"/mnt/udisk/1/117.bmp",
	"/mnt/udisk/1/118.bmp",
	"/mnt/udisk/1/119.bmp",
	"/mnt/udisk/1/120.bmp",
	"/mnt/udisk/1/121.bmp",
	"/mnt/udisk/1/122.bmp",
	"/mnt/udisk/1/123.bmp",
	"/mnt/udisk/1/124.bmp",
	"/mnt/udisk/1/125.bmp",
	"/mnt/udisk/1/126.bmp",
	"/mnt/udisk/1/127.bmp",
	"/mnt/udisk/1/128.bmp",
	"/mnt/udisk/1/129.bmp",
	"/mnt/udisk/1/130.bmp",
	"/mnt/udisk/1/131.bmp",
	"/mnt/udisk/1/132.bmp",
	"/mnt/udisk/1/133.bmp",
	"/mnt/udisk/1/134.bmp",
	"/mnt/udisk/1/135.bmp",
	"/mnt/udisk/1/136.bmp",
	"/mnt/udisk/1/137.bmp",
	"/mnt/udisk/1/138.bmp",
	"/mnt/udisk/1/139.bmp",
	"/mnt/udisk/1/140.bmp",
	"/mnt/udisk/1/141.bmp",
	"/mnt/udisk/1/142.bmp",
	"/mnt/udisk/1/143.bmp",
	"/mnt/udisk/1/144.bmp",
	"/mnt/udisk/1/145.bmp",
	"/mnt/udisk/1/146.bmp",
	"/mnt/udisk/1/147.bmp",
	"/mnt/udisk/1/148.bmp",
	"/mnt/udisk/1/149.bmp",
	"/mnt/udisk/1/150.bmp",
	"/mnt/udisk/1/151.bmp",
	"/mnt/udisk/1/152.bmp",
	"/mnt/udisk/1/153.bmp",
	"/mnt/udisk/1/154.bmp",
	"/mnt/udisk/1/155.bmp",
	"/mnt/udisk/1/156.bmp",
	"/mnt/udisk/1/157.bmp",
	"/mnt/udisk/1/158.bmp",
	"/mnt/udisk/1/159.bmp",
	"/mnt/udisk/1/160.bmp",
	"/mnt/udisk/1/161.bmp",
	"/mnt/udisk/1/162.bmp",
	"/mnt/udisk/1/163.bmp",
	"/mnt/udisk/1/164.bmp",
	"/mnt/udisk/1/165.bmp",
	"/mnt/udisk/1/166.bmp",
	"/mnt/udisk/1/167.bmp",
	"/mnt/udisk/1/168.bmp",
	"/mnt/udisk/1/169.bmp",
	"/mnt/udisk/1/170.bmp",
	"/mnt/udisk/1/171.bmp",
	"/mnt/udisk/1/172.bmp",
	"/mnt/udisk/1/173.bmp",
	"/mnt/udisk/1/174.bmp",
	"/mnt/udisk/1/175.bmp",
	"/mnt/udisk/1/176.bmp",
	"/mnt/udisk/1/177.bmp",
	"/mnt/udisk/1/178.bmp",
	"/mnt/udisk/1/179.bmp",
	"/mnt/udisk/1/180.bmp",
	"/mnt/udisk/1/181.bmp",
	"/mnt/udisk/1/182.bmp",
	"/mnt/udisk/1/183.bmp",
	"/mnt/udisk/1/184.bmp",
	"/mnt/udisk/1/185.bmp",
	"/mnt/udisk/1/186.bmp",
	"/mnt/udisk/1/187.bmp",
	"/mnt/udisk/1/188.bmp",
	"/mnt/udisk/1/189.bmp",
	"/mnt/udisk/1/190.bmp",
	"/mnt/udisk/1/191.bmp",
	"/mnt/udisk/1/192.bmp",
	"/mnt/udisk/1/193.bmp",
	"/mnt/udisk/1/194.bmp",
	"/mnt/udisk/1/195.bmp",
	"/mnt/udisk/1/196.bmp",
	"/mnt/udisk/1/197.bmp",
	"/mnt/udisk/1/198.bmp",
	"/mnt/udisk/1/199.bmp",
	"/mnt/udisk/1/200.bmp",
	"/mnt/udisk/1/201.bmp",
	"/mnt/udisk/1/202.bmp",
	"/mnt/udisk/1/203.bmp",
	"/mnt/udisk/1/204.bmp",
	"/mnt/udisk/1/205.bmp",
	"/mnt/udisk/1/206.bmp",
	"/mnt/udisk/1/207.bmp",
	"/mnt/udisk/1/208.bmp",
	"/mnt/udisk/1/209.bmp",
	"/mnt/udisk/1/210.bmp",
	"/mnt/udisk/1/211.bmp",
	"/mnt/udisk/1/212.bmp",
	"/mnt/udisk/1/213.bmp",
	"/mnt/udisk/1/214.bmp",
	"/mnt/udisk/1/215.bmp",
	"/mnt/udisk/1/216.bmp",
	"/mnt/udisk/1/217.bmp",
	"/mnt/udisk/1/218.bmp",
	"/mnt/udisk/1/219.bmp",
	"/mnt/udisk/1/220.bmp",
	"/mnt/udisk/1/221.bmp",
	"/mnt/udisk/1/222.bmp",
	"/mnt/udisk/1/223.bmp",
	"/mnt/udisk/1/224.bmp",
	"/mnt/udisk/1/225.bmp",
	"/mnt/udisk/1/226.bmp",
	"/mnt/udisk/1/227.bmp",
	"/mnt/udisk/1/228.bmp",
	"/mnt/udisk/1/229.bmp",
	"/mnt/udisk/1/230.bmp",
	"/mnt/udisk/1/231.bmp",
	"/mnt/udisk/1/232.bmp",
	"/mnt/udisk/1/233.bmp",
	"/mnt/udisk/1/234.bmp",
	"/mnt/udisk/1/235.bmp",
	"/mnt/udisk/1/236.bmp",
	"/mnt/udisk/1/237.bmp",
	"/mnt/udisk/1/238.bmp",
	"/mnt/udisk/1/239.bmp",
	"/mnt/udisk/1/240.bmp",
	"/mnt/udisk/1/241.bmp",
	"/mnt/udisk/1/242.bmp",
	"/mnt/udisk/1/243.bmp",
	"/mnt/udisk/1/244.bmp",
	"/mnt/udisk/1/245.bmp",
	"/mnt/udisk/1/246.bmp",
	"/mnt/udisk/1/247.bmp",
	"/mnt/udisk/1/248.bmp",
	"/mnt/udisk/1/249.bmp",
	"/mnt/udisk/1/250.bmp",
	"/mnt/udisk/1/251.bmp",
	"/mnt/udisk/1/252.bmp",
	"/mnt/udisk/1/253.bmp",
	"/mnt/udisk/1/254.bmp",
	"/mnt/udisk/1/255.bmp",
	"/mnt/udisk/1/256.bmp",
	"/mnt/udisk/1/257.bmp",
	"/mnt/udisk/1/258.bmp",
	"/mnt/udisk/1/259.bmp",
	"/mnt/udisk/1/260.bmp",
	"/mnt/udisk/1/261.bmp",
	"/mnt/udisk/1/262.bmp",
	"/mnt/udisk/1/263.bmp",
	"/mnt/udisk/1/264.bmp",
	"/mnt/udisk/1/265.bmp",
	"/mnt/udisk/1/266.bmp",
	"/mnt/udisk/1/267.bmp",
	"/mnt/udisk/1/268.bmp",
	"/mnt/udisk/1/269.bmp",
	"/mnt/udisk/1/270.bmp",
	"/mnt/udisk/1/271.bmp",
	"/mnt/udisk/1/272.bmp",
	"/mnt/udisk/1/273.bmp",
	"/mnt/udisk/1/274.bmp",
	"/mnt/udisk/1/275.bmp",
	"/mnt/udisk/1/276.bmp",
	"/mnt/udisk/1/277.bmp",
	"/mnt/udisk/1/278.bmp",
	"/mnt/udisk/1/279.bmp",
	"/mnt/udisk/1/280.bmp",
	"/mnt/udisk/1/281.bmp",
	"/mnt/udisk/1/282.bmp",
	"/mnt/udisk/1/283.bmp",
	"/mnt/udisk/1/284.bmp",
	"/mnt/udisk/1/285.bmp",
	"/mnt/udisk/1/286.bmp",
	"/mnt/udisk/1/287.bmp",
	"/mnt/udisk/1/288.bmp",
	"/mnt/udisk/1/289.bmp",
	"/mnt/udisk/1/290.bmp",
	"/mnt/udisk/1/291.bmp",
	"/mnt/udisk/1/292.bmp",
	"/mnt/udisk/1/293.bmp",
	"/mnt/udisk/1/294.bmp",
	"/mnt/udisk/1/295.bmp",
	"/mnt/udisk/1/296.bmp",
	"/mnt/udisk/1/297.bmp",
	"/mnt/udisk/1/298.bmp",
	"/mnt/udisk/1/299.bmp",
	"/mnt/udisk/1/300.bmp",
	"/mnt/udisk/1/301.bmp",
	"/mnt/udisk/1/302.bmp",
	"/mnt/udisk/1/303.bmp",
	"/mnt/udisk/1/304.bmp",
	"/mnt/udisk/1/305.bmp",
	"/mnt/udisk/1/306.bmp",
	"/mnt/udisk/1/307.bmp",
	"/mnt/udisk/1/308.bmp",
	"/mnt/udisk/1/309.bmp",
	"/mnt/udisk/1/310.bmp",
	"/mnt/udisk/1/311.bmp",
	"/mnt/udisk/1/312.bmp",
	"/mnt/udisk/1/313.bmp",
	"/mnt/udisk/1/314.bmp",
	"/mnt/udisk/1/315.bmp",
	"/mnt/udisk/1/316.bmp",
	"/mnt/udisk/1/317.bmp",
	"/mnt/udisk/1/318.bmp",
	"/mnt/udisk/1/319.bmp",
	"/mnt/udisk/1/320.bmp",
	"/mnt/udisk/1/321.bmp",
	"/mnt/udisk/1/322.bmp",
	"/mnt/udisk/1/323.bmp",
	"/mnt/udisk/1/324.bmp",
	"/mnt/udisk/1/325.bmp",
	"/mnt/udisk/1/326.bmp",
	"/mnt/udisk/1/327.bmp",
	"/mnt/udisk/1/328.bmp",
	"/mnt/udisk/1/329.bmp",
	"/mnt/udisk/1/330.bmp",
	"/mnt/udisk/1/331.bmp",
	"/mnt/udisk/1/332.bmp",
	"/mnt/udisk/1/333.bmp",
	"/mnt/udisk/1/334.bmp",
	"/mnt/udisk/1/335.bmp",
	"/mnt/udisk/1/336.bmp",
	"/mnt/udisk/1/337.bmp",
	"/mnt/udisk/1/338.bmp",
	"/mnt/udisk/1/339.bmp",
	"/mnt/udisk/1/340.bmp",
	"/mnt/udisk/1/341.bmp",
	"/mnt/udisk/1/342.bmp",
	"/mnt/udisk/1/343.bmp",
	"/mnt/udisk/1/344.bmp",
	"/mnt/udisk/1/345.bmp",
	"/mnt/udisk/1/346.bmp",
	"/mnt/udisk/1/347.bmp",
	"/mnt/udisk/1/348.bmp",
	"/mnt/udisk/1/349.bmp",
	"/mnt/udisk/1/350.bmp",
	"/mnt/udisk/1/351.bmp",
	"/mnt/udisk/1/352.bmp",
};

/**
 * @brief 是否正在播放 标志位
 * 
 */
static char isPlaying = 0;
static char canTap = 1;
/**
 * @brief 自动播放线程函数
 * 
 * @param arg 线程函数参数
 * @return void* 永远返回 NULL
 */
void *autoPlayThread(void *arg)
{
	int *x = arg;
	if (*x == 0)
	{
		*x = 1;
	}

	debugD("AutoPlay Thread idx is %d", *x, INFO);
	while (isPlaying)
	{
		canTap = 0;
		debugD("AutoPlay Thread Change Pic To %d", *x, INFO);
		showBMP(picsPlaying[*x], 0, 0, 0);
		if (*x == 8)
		{
			*x = 0;
		}
		sleep(1);
		canTap = 1;
		*x = *x + 1;
	}
	return NULL;
}
/**
 * @brief 启动自动播放线程
 * 
 * @param i 当前播放图片的 id
 */
void startAutoPlayThread(int *i)
{
	pthread_t th;
	int ret;
	int *thread_ret = NULL;
	ret = pthread_create(&th, NULL, autoPlayThread, i);
	if (ret != 0)
	{
		debug("Create thread error!", ERROR);
		return;
	}
	debug("AutoPlay Thread Started Successful", DEBUG);
}
/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
	static int i = 0;
	debug2D("Touch Thread Callback OnClick in Main : %d, %d", x, y, DEBUG);
	// 如果点击了 上一页 按钮, 并且没有启用 自动播放
	if (inArea2(btPrev, x, y) && !isPlaying && canTap)
	{
		if (i++ == 8)
		{
			i = 0;
		}
		debugD("Touch Thread Callback Next -> Change Pic To %d", i, INFO);
		showBMP(pics[i], 0, 0, 0);
	}
	// 如果点击了 下一页 按钮, 并且没有启用 自动播放
	else if (inArea2(btNext, x, y) && !isPlaying && canTap)
	{
		if (i-- == 0)
		{
			i = 8;
		}
		debugD("Prev -> Change Pic To %d", i, INFO);
		showBMP(pics[i], 0, 0, 0);
	}
	// 如果点击了 暂停/继续 按钮, 并且启用了 自动播放
	else if (inArea2(btPause, x, y))
	{
		// 如果没在自动播放, 那就开启自动播放
		if (!isPlaying)
		{
			if (canTap)
			{
				isPlaying = 1;
				debug("AutoPlay Start", INFO);
				startAutoPlayThread(&i);
			}
			else
			{
				debug("Filtered", INFO);
			}
			return;
		}
		// 如果正在自动播放, 那就暂停播放
		else if (isPlaying)
		{
			isPlaying = 0;
			debug("AutoPlay Paused", INFO);
			showBMP(pics[i], 0, 0, 0);
		}
	}
	else
	{
		debug("Not Hit", INFO);
	}
}
/**
 * @brief 初始化 点击区域 矩阵
 * 
 */
void initRect()
{
	btPrev.startX = 0;
	btPrev.startY = 512;
	btPrev.endX = 102;
	btPrev.endY = 614;

	btNext.startX = 102;
	btNext.startY = 512;
	btNext.endX = 204;
	btNext.endY = 614;

	btPause.startX = 960;
	btPause.startY = 0;
	btPause.endX = 1024;
	btPause.endY = 64;
}
/**
 * @brief 播放开机动画
 * 
 */
void playVideo()
{
	debug("Playing Video", INFO);
	int idx = 0;
	float pid = 1;
	for (idx = 0; idx < 352; idx++)
	{
		showBMP(videos[idx], 0, 0, 0);
		pid += 2.3;
		showBMP(pb, (int)pid, 440, 1);
		usleep(100000 / 60);
	}
	debug("Video End", INFO);
}
int main()
{
	initRect();
	playVideo();
	showBMP(pics[0], 0, 0, 0);
	startTouchThread(onClick);
	return 0;
}