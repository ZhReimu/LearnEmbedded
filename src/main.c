#include <passwd.h>
#include <album.h>
#include <home.h>
#include <videoPlayer.h>
#include <musicPlayer.h>
#include <global.h>
#include <beep.h>

/**
 * @brief 项目全局变量, 当前模块
 * 
 */
int CURRENT_MODULE = PASSWORD;
/**
 * @brief 版本号
 * 
 */
static const char *VERSION = "1.2";
/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
    debug2D("Main Handler %d, %d", x, y, INFO);
    if (passwdHandler(x, y))
    {
        return;
    }
    if (homeHandler(x, y))
    {
        return;
    }
    if (videoPlayerHandler(x, y))
    {
        return;
    }
    if (musicPlayerHandler(x, y))
    {
        return;
    }
    albumHandler(x, y);
}
/**
 * @brief 项目入口
 * 
 * @return int 
 */
int main()
{
    debugS("WELCOME TO MY ALBUM V %s", VERSION, WARN);
    playVideo();
    initPasswd();
    initHome();
    initVideoPlayer();
    initMusicPlayer();
    initAlbum();
    initBeep();

    showLockScreen();
    startTouchThread(onClick);
    return 0;
}
