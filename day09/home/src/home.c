#include <home.h>

Rect btThumAlbum;
Rect btAlbum;
Rect btThumVideoPlayer;
Rect btVideoPlayer;
Rect btThumMusicPlayer;
Rect btMusicPlayer;
Rect btLockScreen;

const char *home = "/mnt/udisk/ProjectAlbum/home.bmp";
void homeHandler(int x, int y)
{
}

void initHome()
{
    btThumAlbum.startX = 64;
    btThumAlbum.startY = 156;
    btThumAlbum.endX = 320;
    btThumAlbum.endY = 216;

    btAlbum.startX = 198;
    btAlbum.startY = 505;
    btAlbum.endX = 262;
    btAlbum.endY = 569;

    btThumVideoPlayer.startX = 385;
    btThumVideoPlayer.startY = 156;
    btThumVideoPlayer.endX = 641;
    btThumVideoPlayer.endY = 216;

    btVideoPlayer.startX = 480;
    btVideoPlayer.startY = 505;
    btVideoPlayer.endX = 544;
    btVideoPlayer.endY = 569;

    btThumMusicPlayer.startX = 704;
    btThumMusicPlayer.startY = 156;
    btThumMusicPlayer.endX = 960;
    btThumMusicPlayer.endY = 216;

    btMusicPlayer.startX = 761;
    btMusicPlayer.startY = 505;
    btMusicPlayer.endX = 825;
    btMusicPlayer.endY = 569;

    btLockScreen.startX = 972;
    btLockScreen.startY = 569;
    btLockScreen.endX = 1024;
    btLockScreen.endY = 614;

    showBMPOO(home);
}