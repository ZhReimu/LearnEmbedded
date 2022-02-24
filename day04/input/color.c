#include <myHeader.h>

void onClick(int x, int y)
{
	printf("OnClick in Main : %d, %d\n", x, y);
	if (inArea(0, 0, 100, 100, x, y))
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
	showBMP("./01.bmp", 0, 0);
	startTouchThread(onClick);
	return 0;
}