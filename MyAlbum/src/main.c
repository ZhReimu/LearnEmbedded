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
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
    debug2D("Main Handler %d, %d", x, y, INFO);
    passwdHandler(x, y);
    homeHandler(x, y);
    videoPlayerHandler(x, y);
    musicPlayerHandler(x, y);
    albumHandler(x, y);
}
/**
 * @brief 项目入口
 * 
 * @return int 
 */
int main()
{
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
