#ifndef _GLOBAL_H
#define _GLOBAL_H

enum MODULE
{
    PASSWORD,
    HOME,
    ALBUM,
    VPLAYER,
    MPLAYER
};
/**
 * @brief 项目全局变量, 当前模块
 * 
 */
static int CURRENT_MODULE = PASSWORD;

#endif