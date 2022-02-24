#include <myHeader.h>

/**
 * @brief 上一页 按钮区域
 * 
 */
Rect prev;
/**
 * @brief 下一页 按钮区域
 * 
 */
Rect next;
/**
 * @brief 相册图片路径
 * 
 */
const char *pics[] = {
	"./pic2/01.bmp",
	"./pic2/02.bmp",
	"./pic2/03.bmp",
	"./pic2/04.bmp",
	"./pic2/05.bmp",
	"./pic2/06.bmp",
	"./pic2/07.bmp",
	"./pic2/08.bmp",
	"./pic2/09.bmp",
};
/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
	static int i = 0;
	debug2D("OnClick in Main : %d, %d", x, y, INFO);

	if (inArea2(prev, x, y))
	{
		if (i++ == 8)
		{
			i = 0;
		}
		debugD("Prev -> Change Pic To %d", i, INFO);
	}
	else if (inArea2(next, x, y))
	{
		if (i-- == 0)
		{
			i = 8;
		}
		debugD("Next -> Change Pic To %d", i, INFO);
	}
	else
	{
		debug("Not Hit", INFO);
	}
	showBMP(pics[i], 0, 0);
}
/**
 * @brief 初始化 点击区域 矩阵
 * 
 */
void init()
{
	prev.startX = 0;
	prev.startY = 512;
	prev.endX = 102;
	prev.endY = 614;

	next.startX = 102;
	next.startY = 512;
	next.endX = 204;
	next.endY = 614;
}

int main()
{
	init();
	showBMP("./pic2/01.bmp", 0, 0);
	startTouchThread(onClick);
	return 0;
}