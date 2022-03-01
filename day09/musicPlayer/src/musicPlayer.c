#include <musicPlayer.h>

/**
 * @brief 首页 按钮区域
 * 
 */
Rect btHome;
/**
 * @brief 相册 按钮区域
 * 
 */
Rect btAlbum;
/**
 * @brief 视频播放器 按钮区域
 * 
 */
Rect btVideoPlayer;
/**
 * @brief 停止播放 按钮区域
 * 
 */
Rect btStop;
/**
 * @brief 第一首歌 按钮区域
 * 
 */
Rect btMusic1;
/**
 * @brief 第二首歌 按钮区域
 * 
 */
Rect btMusic2;
/**
 * @brief 第三首歌 按钮区域
 * 
 */
Rect btMusic3;

/**
 * @brief 播放器背景
 * 
 */
static const char *bg = "/mnt/udisk/music/bg.bmp";
/**
 * @brief 命令前缀
 * 
 */
static const char *cmdPrefix = "mplayer -slave -quiet -input  file=/pipe -vo null ";
/**
 * @brief 命令后缀
 * 
 */
static const char *cmdSuffix = " &";
/**
 * @brief 音乐路径数组
 * 
 */
static const char *music[] = {
    "/mnt/udisk/music/1.mp3",
    "/mnt/udisk/music/2.mp3",
    "/mnt/udisk/music/3.mp3",
};
/**
 * @brief 背景图片 差分, 显示当前播放歌曲
 * 
 */
static const char *musicBG[] = {
    "/mnt/udisk/music/music1.bmp",
    "/mnt/udisk/music/music2.bmp",
    "/mnt/udisk/music/music3.bmp",
};
/**
 * @brief 开始播放
 * 
 * @param idx 要播放的 视频 id
 */
void doPlay(int idx);
/**
 * @brief 返回首页
 * 
 */
void doHome();
/**
 * @brief 停止播放
 * 
 */
void doStop();
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
 * @brief 获取 命令 字符串
 * 
 * @param dst 结果数组
 * @param idx 视频 id
 */
void getCmd(char *dst, int idx)
{
    stringCat(dst, 3, cmdPrefix, music[idx], cmdSuffix);
    debugS("cmd -> %s", dst, INFO);
}

/**
 * @brief 开始播放
 * 
 * @param idx 要播放的 视频 id
 */
void doPlay(int idx)
{
    playStatus = PLAYING;
    playingMusic = idx;
    debug("Start Play", INFO);
    char cmd[512] = {0};
    getCmd(cmd, idx);
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
void doStop()
{
    playStatus = STOPPED;
    debug("Stopped", INFO);
    system("killall -kill mplayer");
    showBMPOO(bg);
}

/**
 * @brief 返回首页
 * 
 */
void doHome()
{
    playStatus = STOPPED;
    system("killall -kill mplayer");
    debug("Home", INFO);
}
/**
 * @brief 播放器处理函数
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 */
void musicPlayerHandler(int x, int y)
{
    int musicID = 0;
    debug2D("Touch Thread Callback OnClick in Main : %d, %d", x, y, INFO);
    if (inArea2(btHome, x, y))
    {
        debug("Back Home", INFO);
    }
    else if (inArea2(btAlbum, x, y))
    {
        debug("GO Album", INFO);
    }
    else if (inArea2(btVideoPlayer, x, y))
    {
        debug("GO VideoPlayer", INFO);
    }
    else if (inArea2(btStop, x, y))
    {
        if (playStatus == PLAYING)
        {
            doStop();
            debug("Stop Play", INFO);
        }
    }
    else if (inArea2(btMusic1, x, y))
    {
        musicID = 0;
        // 如果 没有开始播放, 那就开始播放
        if (playStatus == STOPPED)
        {
            doPlay(musicID);
            debug("Play Music 1", INFO);
        }
        // 如果 正在播放, 并且正在播放的是这首歌, 那就暂停
        else if ((playStatus == PLAYING || playStatus == PAUSED) && playingMusic == musicID)
        {
            doPause(musicID);
        }
        else
        {
            doStop();
            doPlay(musicID);
        }
        debug("Hit Music1", INFO);
    }
    else if (inArea2(btMusic2, x, y))
    {
        musicID = 1;
        if (playStatus == STOPPED)
        {
            doPlay(musicID);
            debug("Play Music 2", INFO);
        }
        else if ((playStatus == PLAYING || playStatus == PAUSED) && playingMusic == musicID)
        {
            doPause(musicID);
        }
        else
        {
            doStop();
            doPlay(musicID);
        }
        debug("Hit Music2", INFO);
    }
    else if (inArea2(btMusic3, x, y))
    {
        musicID = 2;
        if (playStatus == STOPPED)
        {
            doPlay(musicID);
            debug("Play Music 3", INFO);
        }
        else if ((playStatus == PLAYING || playStatus == PAUSED) && playingMusic == musicID)
        {
            doPause(musicID);
        }
        else
        {
            doStop();
            doPlay(musicID);
        }
        debug("Hit Music3", INFO);
    }
    // 如果未 点击有效区域
    else
    {
        debug("Not Hit", INFO);
    }
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
    showBMPOO(bg);
}