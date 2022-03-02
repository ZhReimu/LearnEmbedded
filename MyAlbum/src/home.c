#include <home.h>
#include <album.h>

Rect btThumAlbum;
Rect btAlbum;
Rect btThumVideoPlayer;
Rect btVideoPlayer;
Rect btThumMusicPlayer;
Rect btMusicPlayer;
Rect btLockScreen;

void homeHandler(int x, int y)
{
    if (CURRENT_MODULE != HOME)
    {
        return;
    }
    debug2D("HomeHandler %d, %d", x, y, INFO);
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
        debug("Hit btThumVideoPlayer", INFO);
    }
    else if (inArea2(btVideoPlayer, x, y))
    {
        debug("Hit btVideoPlayer", INFO);
    }
    else if (inArea2(btThumMusicPlayer, x, y))
    {
        debug("Hit btThumMusicPlayer", INFO);
    }
    else if (inArea2(btMusicPlayer, x, y))
    {
        debug("Hit btMusicPlayer", INFO);
    }
    else if (inArea2(btLockScreen, x, y))
    {
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