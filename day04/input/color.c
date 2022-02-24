#include <myHeader.h>

Rect preview;

void onClick(int x, int y)
{
	debug2D("OnClick in Main : %d, %d\n", x, y, INFO);
	if (inArea2(preview, x, y))
	{
		debug("Change Pic", INFO);
		showBMP("./pic2/02.bmp", 0, 0);
	}
	else
	{
		debug("Not Hit", INFO);
		showBMP("./pic2/01.bmp", 0, 0);
	}
}
int main()
{
	preview.startX = 0;
	preview.startY = 500;

	preview.endX = 100;
	preview.endY = 614;

	showBMP("./pic2/01.bmp", 0, 0);
	startTouchThread(onClick);
	return 0;
}