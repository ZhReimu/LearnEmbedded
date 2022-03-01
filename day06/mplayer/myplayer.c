#include <myHeader.h>

/**
 * @brief 暂停, 继续 按钮
 * 
 */
Rect btPlayAndPause;
/**
 * @brief 快进 按钮
 * 
 */
Rect btFastForward;
/**
 * @brief 快退 按钮
 * 
 */
Rect btBack;
/**
 * @brief 首页 按钮
 * 
 */
Rect btHome;
/**
 * @brief 上一个视频 按钮
 * 
 */
Rect btPrevVideo;
/**
 * @brief 下一个视频 按钮
 * 
 */
Rect btNextVideo;
/**
 * @brief 播放状态 枚举
 * 
 */
enum STATUS
{
    /**
     * @brief 暂停中
     *
     */
    PAUSED,
    /**
     * @brief 播放中
     *
     */
    PLAYING,
    /**
     * @brief 停止中
     *
     */
    STOPPED,
};
/**
 * @brief 正在播放的 UI
 * 
 */
const char *uiStarting = "/mnt/udisk/2/video-ui-start.bmp";
/**
 * @brief 停止中的 UI
 * 
 */
const char *uiStopping = "/mnt/udisk/2/video-ui-stop.bmp";
/**
 * @brief 命令前缀
 * 
 */
const char *cmdPrefix = "mplayer -slave -quiet -input  file=/pipe -zoom -x 800 -y 430 -framedrop ";
/**
 * @brief 命令后缀
 * 
 */
const char *cmdSuffix = " &";
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
 * @brief 当前播放状态
 * 
 */
static int playStatus = STOPPED;
/**
 * @brief 视频总数, [0, videos 数组长度)
 * 
 */
static int videoNum = 6;
/**
 * @brief 视频路径 数组
 * 
 */
const char *videos[] = {
    "/mnt/udisk/videos/1.avi",
    "/mnt/udisk/videos/2.avi",
    "/mnt/udisk/videos/3.avi",
    "/mnt/udisk/videos/4.avi",
    "/mnt/udisk/videos/5.avi",
    "/mnt/udisk/videos/6.avi",
    "/mnt/udisk/videos/7.avi",
};
// TODO 使用 audios
/**
 * @brief 音乐路径 数组
 * 
 */
const char *audios[] = {
    "/mnt/udisk/audios/1.mp3",
    "/mnt/udisk/audios/2.mp3",
    "/mnt/udisk/audios/3.mp3",
    "/mnt/udisk/audios/4.mp3",
    "/mnt/udisk/audios/5.mp3",
    "/mnt/udisk/audios/6.mp3",
};

/**
 * @brief 获取 命令 字符串
 * 
 * @param dst 结果数组
 * @param idx 视频 id
 */
void getCmd(char *dst, int idx)
{
    stringCat(dst, 3, cmdPrefix, videos[idx], cmdSuffix);
    debugS("cmd -> %s", dst, INFO);
}
/**
 * @brief 播放 上一个视频
 * 
 */
void doPrevVideo(int idx)
{
    // 只有 正在播放其它视频 或 暂停播放 时, 才需要 先回到首页, 再 播放视频
    if (playStatus == PLAYING || playStatus == PAUSED)
    {
        doHome();
    }
    doPlay(idx);
}
/**
 * @brief 快退 5s
 * 
 */
void doFB()
{
    debug("Back", INFO);
    system("echo seek -5 >> /pipe");
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
    showBMP(uiStarting, 0, 0, 0);
    char cmd[512] = {0};
    getCmd(cmd, idx);
    system(cmd);
    debug("Set Volume", INFO);
    system("echo volume 0.1 >> /pipe");
}
/**
 * @brief 暂停播放
 * 
 */
void doStop()
{
    playStatus = PAUSED;
    debug("Paused", INFO);
    showBMP(uiStopping, 0, 0, 0);
    system("echo pause >> /pipe");
}
/**
 * @brief 继续播放
 * 
 */
void doResume()
{
    playStatus = PLAYING;
    debug("Resume", INFO);
    showBMP(uiStarting, 0, 0, 0);
    system("echo pause >> /pipe");
}
/**
 * @brief 快进 5s
 * 
 */
void doFF()
{
    debug("FastForward", INFO);
    system("echo seek +5 >> /pipe");
}
/**
 * @brief 播放下一个视频
 * 
 * @param idx 
 */
void doNextVideo(int idx)
{
    // 只有 正在播放其它视频 或 暂停播放 时, 才需要 先回到首页, 再 播放视频
    if (playStatus == PLAYING || playStatus == PAUSED)
    {
        doHome();
    }
    doPlay(idx);
}
/**
 * @brief 返回首页
 * 
 */
void doHome()
{
    playStatus = STOPPED;
    system("killall -kill mplayer");
    showBMP(uiStopping, 0, 0, 0);
    debug("Home", INFO);
    usleep(500000);
}
void playerHandler(int x, int y)
{
    static int idx = 0;
    debug2D("Touch Thread Callback OnClick in Main : %d, %d", x, y, INFO);
    // 如果点击了 播放 & 暂停区域
    if (inArea2(btPlayAndPause, x, y))
    {
        // 如果当前播放状态是 已停止
        if (playStatus == STOPPED)
        {
            doPlay(idx);
        }
        // 如果当前播放状态是 播放中
        else if (playStatus == PLAYING)
        {
            doStop();
        }
        // 如果当前播放状态是 暂停中
        else if (playStatus == PAUSED)
        {
            doResume();
        }
    }
    // 如果点击了 快进 区域
    else if (inArea2(btFastForward, x, y))
    {
        // 如果当前播放状态是 播放中
        if (playStatus == PLAYING)
        {
            doFF();
        }
    }
    // 如果点击了 快退 区域
    else if (inArea2(btBack, x, y))
    {
        // 如果当前播放状态是 播放中
        if (playStatus == PLAYING)
        {
            doFB();
        }
    }
    // 如果点击了 首页 区域
    else if (inArea2(btHome, x, y))
    {
        // 如果当前播放状态是 播放中 或 暂停中
        if (playStatus == PLAYING || playStatus == PAUSED)
        {
            doHome();
        }
    }
    else if (inArea2(btPrevVideo, x, y))
    {
        if (idx-- == 0)
        {
            idx = videoNum;
        }
        doPrevVideo(idx);
    }
    else if (inArea2(btNextVideo, x, y))
    {
        if (idx++ == videoNum)
        {
            idx = 0;
        }
        doNextVideo(idx);
    }
    // 如果未 点击有效区域
    else
    {
        debug("Not Hit", INFO);
    }
}
/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
    playerHandler(x, y);
}

void init()
{
    // 初始化 上一个视频 按钮区域
    btPrevVideo.startX = 0;
    btPrevVideo.startY = 550;
    btPrevVideo.endX = 326;
    btPrevVideo.endY = 614;
    // 初始化 快退 按钮区域
    btBack.startX = 326;
    btBack.startY = 550;
    btBack.endX = 422;
    btBack.endY = 614;
    // 初始化 暂停&播放 按钮区域
    btPlayAndPause.startX = 422;
    btPlayAndPause.startY = 550;
    btPlayAndPause.endX = 601;
    btPlayAndPause.endY = 614;
    // 初始化 快进 按钮区域
    btFastForward.startX = 601;
    btFastForward.startY = 550;
    btFastForward.endX = 736;
    btFastForward.endY = 614;
    // 初始化 下一个视频 按钮区域
    btNextVideo.startX = 736;
    btNextVideo.startY = 550;
    btNextVideo.endX = 972;
    btNextVideo.endY = 614;
    // 初始化 首页 按钮区域
    btHome.startX = 972;
    btHome.startY = 550;
    btHome.endX = 1024;
    btHome.endY = 614;
}

int main()
{
    init();
    // system("mplayer -slave -quiet -input  file=/pipe  -geometry  0:0 -zoom -x 800 -y 480  dream.avi &");
    // system("echo pause >> /pipe");
    system("rm /pipe");
    system("mkfifo /pipe");
    system("chmod 777 /pipe");
    showBMP(uiStopping, 0, 0, 0);
    startTouchThread(onClick);
    return 0;
}
