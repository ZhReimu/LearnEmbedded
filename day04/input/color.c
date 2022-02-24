#include <myHeader.h>

Rect rect;

void onClick(int x, int y)
{
	printf("OnClick in Main : %d, %d\n", x, y);
	if (inArea2(rect, x, y))
	{
		puts("Change Pic");
		showBMP("./1/001.bmp", 0, 0);
	}
	else
	{
		puts("Not Hit");
		showBMP("./01.bmp", 0, 0);
	}
}
int main()
{
	rect.startX = 0;
	rect.startY = 0;
	rect.endX = 100;
	rect.endY = 100;

	showBMP("./01.bmp", 0, 0);
	startTouchThread(onClick);
	return 0;
}