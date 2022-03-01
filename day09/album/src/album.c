#include <album.h>
#include <picPaths.h>

/**
 * @brief 上一页 按钮区域
 * 
 */
Rect btPrev;
/**
 * @brief 下一页 按钮区域
 * 
 */
Rect btNext;
/**
 * @brief 暂停播放 按钮区域
 * 
 */
Rect btPause;

/**
 * @brief 是否正在播放 标志位
 * 
 */
static char isPlaying = 0;
static char canTap = 1;
/**
 * @brief 自动播放线程函数
 * 
 * @param arg 线程函数参数
 * @return void* 永远返回 NULL
 */
void *autoPlayThread(void *arg)
{
    int *x = arg;
    if (*x == 0)
    {
        *x = 1;
    }

    debugD("AutoPlay Thread idx is %d", *x, INFO);
    while (isPlaying)
    {
        canTap = 0;
        debugD("AutoPlay Thread Change Pic To %d", *x, INFO);
        showBMPOO(picsPlaying[*x]);
        if (*x == 8)
        {
            *x = 0;
        }
        sleep(1);
        canTap = 1;
        *x = *x + 1;
    }
    return NULL;
}
/**
 * @brief 启动自动播放线程
 * 
 * @param i 当前播放图片的 id
 */
void startAutoPlayThread(int *i)
{
    pthread_t th;
    int ret;
    int *thread_ret = NULL;
    ret = pthread_create(&th, NULL, autoPlayThread, i);
    if (ret != 0)
    {
        debug("Create thread error!", ERROR);
        return;
    }
    debug("AutoPlay Thread Started Successful", DEBUG);
}
void albumHandler(int x, int y)
{
    static int i = 0;
    debug2D("Touch Thread Callback OnClick in Main : %d, %d", x, y, DEBUG);
    // 如果点击了 上一页 按钮, 并且没有启用 自动播放
    if (inArea2(btPrev, x, y) && !isPlaying && canTap)
    {
        if (i++ == 8)
        {
            i = 0;
        }
        debugD("Touch Thread Callback Next -> Change Pic To %d", i, INFO);
        showBMPOO(pics[i]);
    }
    // 如果点击了 下一页 按钮, 并且没有启用 自动播放
    else if (inArea2(btNext, x, y) && !isPlaying && canTap)
    {
        if (i-- == 0)
        {
            i = 8;
        }
        debugD("Prev -> Change Pic To %d", i, INFO);
        showBMPOO(pics[i]);
    }
    // 如果点击了 暂停/继续 按钮, 并且启用了 自动播放
    else if (inArea2(btPause, x, y))
    {
        // 如果没在自动播放, 那就开启自动播放
        if (!isPlaying)
        {
            if (canTap)
            {
                isPlaying = 1;
                debug("AutoPlay Start", INFO);
                startAutoPlayThread(&i);
            }
            else
            {
                debug("Filtered", INFO);
            }
            return;
        }
        // 如果正在自动播放, 那就暂停播放
        else if (isPlaying)
        {
            isPlaying = 0;
            debug("AutoPlay Paused", INFO);
            showBMPOO(pics[i]);
        }
    }
    else
    {
        debug("Not Hit", INFO);
    }
}

/**
 * @brief 播放开机动画
 * 
 */
void playVideo()
{
    debug("Playing Video", INFO);
    int idx = 0;
    float pid = 1;
    for (idx = 0; idx < 352; idx++)
    {
        // 绘制一帧 图片
        showBMPOO(videos[idx]);
        pid += 2.3;
        // 绘制 进度条
        showBMP(pb, (int)pid, 440, 1);
        usleep(100000 / 60);
    }
    debug("Video End", INFO);
}

/**
 * @brief 初始化 点击区域 矩阵
 * 
 */
void initAlbum()
{
    btPrev.startX = 0;
    btPrev.startY = 512;
    btPrev.endX = 102;
    btPrev.endY = 614;

    btNext.startX = 102;
    btNext.startY = 512;
    btNext.endX = 204;
    btNext.endY = 614;

    btPause.startX = 960;
    btPause.startY = 0;
    btPause.endX = 1024;
    btPause.endY = 64;

    playVideo();
    showBMPOO(pics[0]);
}