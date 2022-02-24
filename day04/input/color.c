#include <myHeader.h>

void onClick(int x, int y)
{
	printf("OnClick in Main : %d, %d\n", x, y);
}
int main()
{
	startTouchThread(onClick);
	return 0;
}