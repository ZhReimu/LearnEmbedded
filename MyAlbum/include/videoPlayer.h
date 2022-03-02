#ifndef _VPLAYER_H_
#define _VPLAYER_H_

#include <log.h>
#include <bmp.h>
#include <utils.h>

/**
 * @brief 视频播放器 逻辑入口
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 */
void videoPlayerHandler(int x, int y);
/**
 * @brief 初始化 点击区域
 * 
 */
void initVideoPlayer();
/**
 * @brief 显示 视频播放器
 * 
 */
void showVideoPlayer();
#endif