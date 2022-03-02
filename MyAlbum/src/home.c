#include <passwd.h>
#include <album.h>
#include <home.h>
#include <videoPlayer.h>
#include <musicPlayer.h>

Rect btThumAlbum;
Rect btAlbum;
Rect btThumVideoPlayer;
Rect btVideoPlayer;
Rect btThumMusicPlayer;
Rect btMusicPlayer;
Rect btLockScreen;

/**
 * @brief Home 模块主要逻辑
 * 
 * @param x 点击的坐标的 x
 * @param y 点击的坐标的 y
 */
void homeHandler(int x, int y)
{
    // 如果 当前展示的模块不是 HOME, 那就不管
    if (CURRENT_MODULE != HOME)
    {
        return;
    }
    debug2D("HomeHandler %d, %d", x, y, INFO);
    // 如果 点击了 缩略图的 相册 按钮
    if (inArea2(btThumAlbum, x, y))
    {
        showAlbum();
        debug("Hit btThumAlbum", INFO);
    }
    else if (inArea2(btAlbum, x, y))
    {
        showAlbum();
        debug("Hit btAlbum", INFO);
    }
    else if (inArea2(btThumVideoPlayer, x, y))
    {
        showVideoPlayer();
        debug("Hit btThumVideoPlayer", INFO);
    }
    else if (inArea2(btVideoPlayer, x, y))
    {
        showVideoPlayer();
        debug("Hit btVideoPlayer", INFO);
    }
    else if (inArea2(btThumMusicPlayer, x, y))
    {
        showMusicPlayer();
        debug("Hit btThumMusicPlayer", INFO);
    }
    else if (inArea2(btMusicPlayer, x, y))
    {
        showMusicPlayer();
        debug("Hit btMusicPlayer", INFO);
    }
    else if (inArea2(btLockScreen, x, y))
    {
        showLockScreen();
        debug("Hit btLockScreen", INFO);
    }
    else
    {
        debug("Not Hit", INFO);
    }
}

void initHome()
{
    btThumAlbum.startX = 64;
    btThumAlbum.startY = 156;
    btThumAlbum.endX = 320;
    btThumAlbum.endY = 307;

    btAlbum.startX = 198;
    btAlbum.startY = 505;
    btAlbum.endX = 262;
    btAlbum.endY = 569;

    btThumVideoPlayer.startX = 385;
    btThumVideoPlayer.startY = 156;
    btThumVideoPlayer.endX = 641;
    btThumVideoPlayer.endY = 307;

    btVideoPlayer.startX = 480;
    btVideoPlayer.startY = 505;
    btVideoPlayer.endX = 544;
    btVideoPlayer.endY = 569;

    btThumMusicPlayer.startX = 704;
    btThumMusicPlayer.startY = 156;
    btThumMusicPlayer.endX = 960;
    btThumMusicPlayer.endY = 307;

    btMusicPlayer.startX = 761;
    btMusicPlayer.startY = 505;
    btMusicPlayer.endX = 825;
    btMusicPlayer.endY = 569;

    btLockScreen.startX = 972;
    btLockScreen.startY = 569;
    btLockScreen.endX = 1024;
    btLockScreen.endY = 614;
}

/**
 * @brief 显示 Home 模块
 * 
 */
void showHome()
{
    CURRENT_MODULE = HOME;
    showBMPOO(home);
}