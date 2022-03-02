#include <passwd.h>
#include <album.h>
#include <home.h>

/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
    debug("OnClick In Main Before Password", INFO);
    passwdHandler(x, y);
    debug("OnClick In Main After Password", INFO);
    homeHandler(x, y);
    debug("OnClick In Main After Home", INFO);
}

int main()
{
    // TODO 还原开机动画 playVideo();
    initPasswd();
    initHome();
    startTouchThread(onClick);
    return 0;
}