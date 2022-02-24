#include <myHeader.h>

Rect prev, next;

void getPath(char *path, int firstZero, int id)
{
	if (id < 10)
	{
		path[firstZero + 1] = id + '0';
	}
	else if (id < 100)
	{
		path[firstZero] = id / 10 + '0';
		path[firstZero + 1] = id % 10 + '0';
	}
}
void onClick(int x, int y)
{
	static int i = 1;
	char path[] = "./pic2/01.bmp";
	getPath(path, 7, i);
	debug2D("OnClick in Main : %d, %d\n", x, y, INFO);
	if (inArea2(prev, x, y))
	{
		if (i++ == 9)
		{
			i = 1;
		}
		getPath(path, 7, i);
		debugS("Change Pic To %s", path, INFO);
	}
	else if (inArea2(next, x, y))
	{
		if (i-- == 1)
		{
			i = 9;
		}
		getPath(path, 7, i);
		debugS("Change Pic To %s", path, INFO);
	}
	else
	{
		debug("Not Hit", INFO);
	}
	showBMP(path, 0, 0);
}
int main()
{
	prev.startX = 0;
	prev.startY = 512;

	prev.endX = 102;
	prev.endY = 614;

	next.startX = 102;
	next.startY = 512;

	next.endX = 204;
	next.endY = 614;

	showBMP("./pic2/01.bmp", 0, 0);
	startTouchThread(onClick);
	return 0;
}