#ifndef _GLOBAL_H
#define _GLOBAL_H
#include <log.h>
/**
 * @brief 模块 枚举
 * 
 */
enum MODULE
{
    /**
     * @brief 密码 模块
     * 
     */
    PASSWORD,
    /**
     * @brief 主页 模块
     * 
     */
    HOME,
    /**
     * @brief 相册 模块
     * 
     */
    ALBUM,
    /**
     * @brief 视频播放器 模块
     * 
     */
    VPLAYER,
    /**
     * @brief 音乐播放器 模块
     * 
     */
    MPLAYER
};
extern int CURRENT_MODULE;

static void showCurrentModule(const char *from)
{
    switch (CURRENT_MODULE)
    {
    case PASSWORD:
        debugS("%s : 现在是 密码", from, DEBUG);
        break;
    case HOME:
        debugS("%s : 现在是 主页", from, DEBUG);
        break;
    case ALBUM:
        debugS("%s : 现在是 相册", from, DEBUG);
        break;
    case VPLAYER:
        debugS("%s : 现在是 视频播放器", from, DEBUG);
        break;
    case MPLAYER:
        debugS("%s : 现在是 音乐播放器", from, DEBUG);
        break;
    }
}
#endif