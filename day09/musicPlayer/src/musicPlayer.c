#include <musicPlayer.h>

Rect btHome;
Rect btAlbum;
Rect btVideoPlayer;
Rect btStop;
Rect btMusic1;
Rect btMusic2;
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
    PAUSEING,
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
    debug("Start Play", INFO);
    char cmd[512] = {0};
    getCmd(cmd, idx);
    system(cmd);
    showBMPOO(musicBG[idx]);
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
    static int idx = 0;
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
        if (playStatus == STOPPED)
        {
            doPlay(0);
            debug("Play Music 1", INFO);
        }
        else
        {
            doStop();
            doPlay(0);
        }
    }
    else if (inArea2(btMusic2, x, y))
    {
        if (playStatus == STOPPED)
        {
            doPlay(1);
            debug("Play Music 2", INFO);
        }
        else
        {
            doStop();
            doPlay(1);
        }
    }
    else if (inArea2(btMusic3, x, y))
    {
        if (playStatus == STOPPED)
        {
            doPlay(2);
            debug("Play Music 3", INFO);
        }
        else
        {
            doStop();
            doPlay(2);
        }
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
    btHome.startX = 10 * 1.28;
    btHome.endX = 50 * 1.28;
    btHome.startY = 435 * 1.28;
    btHome.endY = 614;

    btAlbum.startX = 70 * 1.28;
    btAlbum.endX = 110 * 1.28;
    btAlbum.startY = 435 * 1.28;
    btAlbum.endY = 614;

    btVideoPlayer.startX = 130 * 1.28;
    btVideoPlayer.endX = 170 * 1.28;
    btVideoPlayer.startY = 435 * 1.28;
    btVideoPlayer.endY = 614;

    btStop.startX = 765 * 1.28;
    btStop.endX = 1024;
    btStop.startY = 445 * 1.28;
    btStop.endY = 48 * 1.28;

    btMusic1.startX = 200 * 1.28;
    btMusic1.endX = 400 * 1.28;
    btMusic1.startY = 100 * 1.28;
    btMusic1.endY = 150 * 1.28;

    btMusic2.startX = 300 * 1.28;
    btMusic2.endX = 500 * 1.28;
    btMusic2.startY = 200 * 1.28;
    btMusic2.endY = 250 * 1.28;

    btMusic3.startX = 400 * 1.28;
    btMusic3.endX = 600 * 1.28;
    btMusic3.startY = 300 * 1.28;
    btMusic3.endY = 350 * 1.28;

    system("rm /pipe");
    system("mkfifo /pipe");
    system("chmod 777 /pipe");
    showBMP(bg, 0, 0, 0);
}