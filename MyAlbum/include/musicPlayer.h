#ifndef _MPLAYER_H_
#define _MPLAYER_H_

#include <log.h>
#include <utils.h>
#include <bmp.h>
/**
 * @brief 音乐播放器 逻辑入口
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 */
bool musicPlayerHandler(int x, int y);
/**
 * @brief 初始化 点击区域
 * 
 */
void initMusicPlayer();
/**
 * @brief 显示 音乐播放器
 * 
 */
void showMusicPlayer();

#endif