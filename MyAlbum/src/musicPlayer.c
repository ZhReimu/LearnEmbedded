#include <musicPlayer.h>
#include <picPaths.h>
#include <global.h>
#include <home.h>
#include <album.h>
#include <videoPlayer.h>

/**
 * @brief 首页 按钮区域
 * 
 */
static Rect btHome;
/**
 * @brief 相册 按钮区域
 * 
 */
static Rect btAlbum;
/**
 * @brief 视频播放器 按钮区域
 * 
 */
static Rect btVideoPlayer;
/**
 * @brief 停止播放 按钮区域
 * 
 */
static Rect btStop;
/**
 * @brief 第一首歌 按钮区域
 * 
 */
static Rect btMusic1;
/**
 * @brief 第二首歌 按钮区域
 * 
 */
static Rect btMusic2;
/**
 * @brief 第三首歌 按钮区域
 * 
 */
static Rect btMusic3;
/**
 * @brief 命令前缀
 * 
 */
static const char *cmdPrefix = "mplayer -slave -quiet -input  file=/pipe -vo null ";
/**
 * @brief 开始播放
 * 
 * @param idx 要播放的 视频 id
 */
void doPlayMusic(int idx);
/**
 * @brief 返回首页
 * 
 */
void doMusicHome();
/**
 * @brief 停止播放
 * 
 */
void doStopMusic();
/**
 * @brief 播放状态 枚举
 * 
 */
enum status
{
    /**
 * @brief 正在播放
 * 
 */
    PLAYING,
    /**
     * @brief 暂停中
     * 
     */
    PAUSED,
    /**
     * @brief 停止播放
     * 
     */
    STOPPED,
};
/**
 * @brief 当前播放状态
 * 
 */
static int playStatus = STOPPED;
/**
 * @brief 当前播放歌曲 id
 * 
 */
static int playingMusic = 0;
/**
 * @brief 项目全局变量, 当前模块
 * 
 */
extern int CURRENT_MODULE;
/**
 * @brief 获取 命令 字符串
 * 
 * @param dst 结果数组
 * @param idx 视频 id
 */
void getMusicCmd(char *dst, int idx)
{
    stringCat(dst, 3, cmdPrefix, music[idx], cmdSuffix);
    debugS("cmd -> %s", dst, INFO);
}

/**
 * @brief 开始播放
 * 
 * @param idx 要播放的 视频 id
 */
void doPlayMusic(int idx)
{
    playStatus = PLAYING;
    playingMusic = idx;
    debug("Start Play", INFO);
    char cmd[512] = {0};
    getMusicCmd(cmd, idx);
    system(cmd);
    showBMPOO(musicBG[idx]);
}
/**
 * @brief 暂停 & 继续播放
 * 
 */
void doPause(int idx)
{
    // 如果 当前是暂停状态
    if (playStatus == PAUSED)
    {
        // 那就将标志位修改为 播放中
        playStatus = PLAYING;
        debug("Resumed", INFO);
    }
    else
    {
        // 否则就将标志位修改为 暂停中
        playStatus = PAUSED;
        debug("Paused", INFO);
    }
    // 更新 当前播放歌曲 id
    playingMusic = idx;
    system("echo pause >> /pipe");
}
/**
 * @brief 暂停播放
 * 
 */
void doStopMusic()
{
    playStatus = STOPPED;
    debug("Stopped", INFO);
    system("killall -kill mplayer");
    showBMPOO(muusicPlayerBG);
}

/**
 * @brief 返回首页
 * 
 */
void doMusicHome()
{
    playStatus = STOPPED;
    system("killall -kill mplayer");
    debug("Back Music Home", INFO);
    showBMPOO(muusicPlayerBG);
}
/**
 * @brief 销毁界面时调用
 * 
 */
static void onDestroyed()
{
    playingMusic = 0;
    doMusicHome();
}
/**
 * @brief 音乐播放器 逻辑入口
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 */
bool musicPlayerHandler(int x, int y)
{
    if (CURRENT_MODULE != MPLAYER)
    {
        showCurrentModule("MusicPlayer");
        return false;
    }
    debug2D("MusicPlayer Handler %d, %d", x, y, INFO);
    int musicID = 0;
    if (inArea2(btHome, x, y))
    {
        debug("Hit btHome", INFO);
        onDestroyed();
        showHome();
        debug("Back Home", INFO);
    }
    else if (inArea2(btAlbum, x, y))
    {
        onDestroyed();
        showAlbum();
        debug("GO Album", INFO);
    }
    else if (inArea2(btVideoPlayer, x, y))
    {
        onDestroyed();
        showVideoPlayer();
        debug("GO VideoPlayer", INFO);
    }
    else if (inArea2(btStop, x, y))
    {
        debug("Hit BtStop", INFO);
        if (playStatus == PLAYING)
        {
            doStopMusic();
            debug("Stop Play", INFO);
        }
    }
    else if (inArea2(btMusic1, x, y))
    {
        musicID = 0;
        // 如果 没有开始播放, 那就开始播放
        if (playStatus == STOPPED)
        {
            doPlayMusic(musicID);
            debug("Play Music 1", INFO);
        }
        // 如果 正在播放, 并且正在播放的是这首歌, 那就暂停
        else if ((playStatus == PLAYING || playStatus == PAUSED) && playingMusic == musicID)
        {
            doPause(musicID);
        }
        else
        {
            doStopMusic();
            doPlayMusic(musicID);
        }
        debug("Hit Music1", INFO);
    }
    else if (inArea2(btMusic2, x, y))
    {
        musicID = 1;
        if (playStatus == STOPPED)
        {
            doPlayMusic(musicID);
            debug("Play Music 2", INFO);
        }
        else if ((playStatus == PLAYING || playStatus == PAUSED) && playingMusic == musicID)
        {
            doPause(musicID);
        }
        else
        {
            doStopMusic();
            doPlayMusic(musicID);
        }
        debug("Hit Music2", INFO);
    }
    else if (inArea2(btMusic3, x, y))
    {
        musicID = 2;
        if (playStatus == STOPPED)
        {
            doPlayMusic(musicID);
            debug("Play Music 3", INFO);
        }
        else if ((playStatus == PLAYING || playStatus == PAUSED) && playingMusic == musicID)
        {
            doPause(musicID);
        }
        else
        {
            doStopMusic();
            doPlayMusic(musicID);
        }
        debug("Hit Music3", INFO);
    }
    // 如果未 点击有效区域
    else
    {
        debug("MusicPlayer Handler Not Hit", INFO);
    }
    return true;
}
/**
 * @brief 初始化 点击区域
 * 
 */
void initMusicPlayer()
{
    btHome.startX = 13;
    btHome.endX = 64;
    btHome.startY = 557;
    btHome.endY = 614;

    btAlbum.startX = 90;
    btAlbum.endX = 141;
    btAlbum.startY = 557;
    btAlbum.endY = 614;

    btVideoPlayer.startX = 166;
    btVideoPlayer.endX = 218;
    btVideoPlayer.startY = 557;
    btVideoPlayer.endY = 614;

    btStop.startX = 979;
    btStop.endX = 1024;
    btStop.startY = 570;
    btStop.endY = 614;

    btMusic1.startX = 256;
    btMusic1.endX = 512;
    btMusic1.startY = 128;
    btMusic1.endY = 192;

    btMusic2.startX = 384;
    btMusic2.endX = 640;
    btMusic2.startY = 256;
    btMusic2.endY = 320;

    btMusic3.startX = 512;
    btMusic3.endX = 768;
    btMusic3.startY = 384;
    btMusic3.endY = 448;
    initPipe();
}
/**
 * @brief 显示 音乐播放器
 * 
 */
void showMusicPlayer()
{
    debug("Show MusicPlayer", INFO);
    CURRENT_MODULE = MPLAYER;
    showBMPOO(muusicPlayerBG);
}