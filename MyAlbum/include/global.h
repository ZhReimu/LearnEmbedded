#ifndef _GLOBAL_H
#define _GLOBAL_H

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
/**
 * @brief 项目全局变量, 当前模块
 * 
 */
static int CURRENT_MODULE = PASSWORD;

#endif