#include <videoPlayer.h>
/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
    playerHandler(x, y);
}

int main()
{
    init();
    startTouchThread(onClick);
    return 0;
}
