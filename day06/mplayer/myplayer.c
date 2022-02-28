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
const char *cmdPrefix = "mplayer -slave -quiet -input  file=/pipe -zoom -x 800 -y 430 -nosound ";
const char *cmdSuffix = " &";
/**
 * @brief 当前播放状态
 * 
 */
static int playStatus = STOPPED;
static int videoNum = 2;
const char *videos[] = {
    "/mnt/udisk/videos/1.avi",
    "/mnt/udisk/videos/2.avi",
    "/mnt/udisk/videos/3.avi",
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
 * @brief 开始播放
 * 
 * @param idx 
 */
void doPlay(int idx)
{
    playStatus = PLAYING;
    debug("Start Play", INFO);
    showBMP(uiStarting, 0, 0, 0);
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
 * @brief 快退 5s
 * 
 */
void doFB()
{
    debug("Back", INFO);
    system("echo seek -5 >> /pipe");
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
}
/**
 * @brief 点击事件, 屏幕被点击时触发
 * 
 * @param x 被点击的 x 坐标
 * @param y 被点击的 y 坐标
 */
void onClick(int x, int y)
{
    debug2D("Touch Thread Callback OnClick in Main : %d, %d", x, y, INFO);
    // 如果点击了 播放 & 暂停区域
    if (inArea2(btPlayAndPause, x, y))
    {
        // 如果当前播放状态是 已停止
        if (playStatus == STOPPED)
        {
            // TODO: 修改 idx 实现切换视频
            doPlay(0);
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
        // fixme: 主页 点击卡死
        // 如果当前播放状态是 播放中 或 暂停中
        if (playStatus == PLAYING || playStatus == PAUSED)
        {
            doHome();
        }
    }
    else if (inArea2(btPrevVideo, x, y))
    {
    }
    else if (inArea2(btNextVideo, x, y))
    {
    }
    // 如果未 点击有效区域
    else
    {
        debug("Not Hit", INFO);
    }
}

void init()
{
    // 初始化 上一个视频 按钮区域
    btPrevVideo.startX = 0;
    btPrevVideo.startY = 960;
    btPrevVideo.endX = 326;
    btPrevVideo.endY = 1024;
    // 初始化 快退 按钮区域
    btBack.startX = 326;
    btBack.startY = 960;
    btBack.endX = 422;
    btBack.endY = 1024;
    // 初始化 暂停&播放 按钮区域
    btPlayAndPause.startX = 422;
    btPlayAndPause.startY = 960;
    btPlayAndPause.endX = 601;
    btPlayAndPause.endY = 1024;
    // 初始化 快进 按钮区域
    btFastForward.startX = 601;
    btFastForward.startY = 960;
    btFastForward.endX = 736;
    btFastForward.endY = 1024;
    // 初始化 下一个视频 按钮区域
    btNextVideo.startX = 736;
    btNextVideo.startY = 960;
    btNextVideo.endX = 972;
    btNextVideo.endY = 1024;
    // 初始化 首页 按钮区域
    btHome.startX = 972;
    btHome.startY = 960;
    btHome.endX = 1024;
    btHome.endY = 1024;
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
