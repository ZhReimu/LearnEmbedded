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
 * @brief 当前播放状态
 * 
 */
static int playStatus = STOPPED;

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
            // 那就调整标志位, 修改 UI 为 开始播放 状态, 并开始播放
            playStatus = PLAYING;
            debug("Start Play", INFO);
            showBMP(uiStarting, 0, 0, 0);
            system("mplayer -slave -quiet -input  file=/pipe -zoom -x 800 -y 430 -nosound /mnt/udisk/dream.avi &");
        }
        // 如果当前播放状态是 播放中
        else if (playStatus == PLAYING)
        {
            // 那就调整标志位, 修改 UI 为 暂停播放 状态, 并暂停播放
            playStatus = PAUSED;
            debug("Paused", INFO);
            showBMP(uiStopping, 0, 0, 0);
            system("echo pause >> /pipe");
        }
        // 如果当前播放状态是 暂停中
        else if (playStatus == PAUSED)
        {
            // 那就调整标志位, 修改 UI 为 开始播放 状态, 并继续播放
            playStatus = PLAYING;
            debug("Resume", INFO);
            showBMP(uiStarting, 0, 0, 0);
            system("echo pause >> /pipe");
        }
    }
    // 如果点击了 快进 区域
    else if (inArea2(btFastForward, x, y))
    {
        // 如果当前播放状态是 播放中
        if (playStatus == PLAYING)
        {
            // 那就 快进 5s
            debug("FastForward", INFO);
            system("echo seek +5 >> /pipe");
        }
    }
    // 如果点击了 快退 区域
    else if (inArea2(btBack, x, y))
    {
        // 如果当前播放状态是 播放中
        if (playStatus == PLAYING)
        {
            // 那就 快退 5s
            debug("Back", INFO);
            system("echo seek -5 >> /pipe");
        }
    }
    // 如果点击了 首页 区域
    else if (inArea2(btHome, x, y))
    {
        // fixme: 主页 点击卡死
        // 如果当前播放状态是 播放中 或 暂停中
        if (playStatus == PLAYING || playStatus == PAUSED)
        {
            // 那就调整标志位, 结束 mplayer 进程, 修改 UI 为 停止播放 状态
            playStatus = STOPPED;
            system("killall -kill mplayer");
            showBMP(uiStopping, 0, 0, 0);
            debug("Home", INFO);
        }
    }
    // 如果未 点击有效区域
    else
    {
        debug("Not Hit", INFO);
    }
}

void init()
{
    btPlayAndPause.startX = 342;
    btPlayAndPause.startY = 550;
    btPlayAndPause.endX = 684;
    btPlayAndPause.endY = 614;

    btFastForward.startX = 684;
    btFastForward.startY = 550;
    btFastForward.endX = 960;
    btFastForward.endY = 614;

    btBack.startX = 0;
    btBack.startY = 550;
    btBack.endX = 341;
    btBack.endY = 614;

    btHome.startX = 960;
    btHome.startY = 563;
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
