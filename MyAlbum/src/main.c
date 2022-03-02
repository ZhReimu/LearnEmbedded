#include <passwd.h>
#include <album.h>
#include <home.h>
#include <videoPlayer.h>
#include <musicPlayer.h>

/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
    debug("OnClick In Main Before Password Handler", INFO);
    passwdHandler(x, y);

    debug("OnClick In Main After Password Handler", INFO);
    homeHandler(x, y);

    debug("OnClick In Main After Home Handler", INFO);
    videoPlayerHandler(x, y);

    debug("OnClick In Main After VideoPlayer Handler", INFO);
    musicPlayerHandler(x, y);

    debug("OnClick In Main After MusicPlayer Handler", INFO);
    albumHandler(x, y);

    debug("OnClick In Main After Album Handler", INFO);
}

int main()
{
    // TODO 还原开机动画 playVideo();
    initPasswd();
    initHome();
    initVideoPlayer();
    initMusicPlayer();
    initAlbum();

    showLockScreen();
    startTouchThread(onClick);
    return 0;
}
