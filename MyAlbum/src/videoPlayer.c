#include <videoPlayer.h>
#include <picPaths.h>
#include <global.h>

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
 * @brief 命令前缀
 * 
 */
const char *cmdPrefix = "mplayer -slave -quiet -input  file=/pipe -zoom -x 800 -y 430 -framedrop ";
/**
 * @brief 开始播放
 * 
 * @param idx 要播放的 视频 id
 */
void doPlayVideo(int idx);
/**
 * @brief 返回首页
 * 
 */
void doVideoHome();
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
void getVideoCmd(char *dst, int idx)
{
    stringCat(dst, 3, cmdPrefix, aviVideos[idx], cmdSuffix);
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
        doVideoHome();
    }
    doPlayVideo(idx);
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
void doPlayVideo(int idx)
{
    playStatus = PLAYING;
    debug("Start Play", INFO);
    showBMPOO(videoPlayerStaringUI);
    char cmd[512] = {0};
    getVideoCmd(cmd, idx);
    system(cmd);
    debug("Set Volume", INFO);
    system("echo volume 0.1 >> /pipe");
}
/**
 * @brief 暂停播放
 * 
 */
void doStopVideo()
{
    playStatus = PAUSED;
    debug("Paused", INFO);
    showBMPOO(videoPlayerStoppingUI);
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
    showBMPOO(videoPlayerStaringUI);
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
        doVideoHome();
    }
    doPlayVideo(idx);
}
/**
 * @brief 返回首页
 * 
 */
void doVideoHome()
{
    playStatus = STOPPED;
    system("killall -kill mplayer");
    showBMPOO(videoPlayerStoppingUI);
    debug("Home", INFO);
    usleep(500000);
}
/**
 * @brief 视频播放器 逻辑入口
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 */
void videoPlayerHandler(int x, int y)
{
    if (CURRENT_MODULE != VPLAYER)
    {
        return;
    }
    debug2D("VideoPlayer Handler %d, %d", x, y, INFO);
    static int idx = 0;
    // 如果点击了 播放 & 暂停区域
    if (inArea2(btPlayAndPause, x, y))
    {
        // 如果当前播放状态是 已停止
        if (playStatus == STOPPED)
        {
            doPlayVideo(idx);
        }
        // 如果当前播放状态是 播放中
        else if (playStatus == PLAYING)
        {
            doStopVideo();
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
            doVideoHome();
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
 * @brief 初始化 点击区域
 * 
 */
void initVideoPlayer()
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
    // system("mplayer -slave -quiet -input  file=/pipe  -geometry  0:0 -zoom -x 800 -y 480  dream.avi &");
    // system("echo pause >> /pipe");
    initPipe();
}
/**
 * @brief 显示 视频播放器
 * 
 */
void showVideoPlayer()
{
    CURRENT_MODULE = VPLAYER;
    showBMPOO(videoPlayerStoppingUI);
}