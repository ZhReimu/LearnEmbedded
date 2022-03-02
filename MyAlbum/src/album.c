#include <album.h>

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
 * @brief 返回首页 按钮区域
 * 
 */
Rect btHome;
/**
 * @brief 精选 图片 1
 * 
 */
Rect nPic1;
/**
 * @brief 精选 图片 2
 * 
 */
Rect nPic2;
/**
 * @brief 是否正在播放 标志位
 * 
 */
static char isPlaying = 0;
/**
 * @brief 是否能点击
 * 
 */
static char canTap = 1;
/**
 * @brief 是否在首页
 * 
 */
static bool isInHome = false;
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
        if (*x == 7)
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
/**
 * @brief 相册 逻辑入口
 * 
 * @param x 点击的坐标的 x
 * @param y 点击的坐标的 y
 */
void albumHandler(int x, int y)
{
    if (CURRENT_MODULE != ALBUM)
    {
        return;
    }
    debug2D("Album Handler %d, %d", x, y, INFO);
    static int i = 0;
    // 如果点击了 上一页 按钮, 并且没有启用 自动播放
    if (inArea2(btPrev, x, y) && !isPlaying && canTap)
    {
        if (i++ == 7)
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
            i = 7;
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
    else if (inArea2(btHome, x, y))
    {
        if (isInHome)
        {
            isInHome = false;
            showBMPOO(home);
            debug("Back To Home", INFO);
        }
        else
        {
            isPlaying = 0;
            isInHome = true;
            showBMPOO(albumBG);
            debug("Back To Album Home", INFO);
        }
    }
    else if (isInHome)
    {
        if (inArea2(nPic1, x, y))
        {
            showBMPOO(pics[0]);
            isInHome = false;
        }
        else if (inArea2(nPic2, x, y))
        {
            showBMPOO(pics[1]);
            isInHome = false;
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

    btHome.startX = 972;
    btHome.startY = 569;
    btHome.endX = 1024;
    btHome.endY = 614;

    nPic1.startX = 102;
    nPic1.startY = 128;
    nPic1.endX = 358;
    nPic1.endY = 281;

    nPic2.startX = 256;
    nPic2.startY = 307;
    nPic2.endX = 512;
    nPic2.endY = 460;
    isInHome = true;
}
/**
 * @brief 显示 相册 模块
 * 
 */
void showAlbum()
{
    CURRENT_MODULE = ALBUM;
    showBMPOO(albumBG);
}