#include <home.h>

Rect btThumAlbum;
Rect btAlbum;
Rect btThumVideoPlayer;
Rect btVideoPlayer;
Rect btThumMusicPlayer;
Rect btMusicPlayer;

const char *home = "/mnt/udisk/ProjectAlbum/home.bmp";
void homeHandler(int x, int y)
{
}

void initHome()
{
    btThumAlbum.startX;
    btThumAlbum.startY;
    btThumAlbum.endX;
    btThumAlbum.endY;

    btAlbum.startX;
    btAlbum.startY;
    btAlbum.endX;
    btAlbum.endY;

    btThumVideoPlayer.startX;
    btThumVideoPlayer.startY;
    btThumVideoPlayer.endX;
    btThumVideoPlayer.endY;

    btVideoPlayer.startX;
    btVideoPlayer.startY;
    btVideoPlayer.endX;
    btVideoPlayer.endY;

    btThumMusicPlayer.startX;
    btThumMusicPlayer.startY;
    btThumMusicPlayer.endX;
    btThumMusicPlayer.endY;

    btMusicPlayer.startX;
    btMusicPlayer.startY;
    btMusicPlayer.endX;
    btMusicPlayer.endY;

    showBMPOO(home);
}