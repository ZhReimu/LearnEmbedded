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
 * @brief 音乐个数, music [0, music 数组长度)
 * 
 */
static const int musicNum = 2;
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
    system("rm /pipe");
    system("mkfifo /pipe");
    system("chmod 777 /pipe");
    showBMP(bg, 0, 0, 0);
}