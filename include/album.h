#ifndef _ALBUM_H_
#define _ALBUM_H_

#include <log.h>
#include <bmp.h>
#include <utils.h>
#include <global.h>
#include <picPaths.h>

/**
 * @brief 初始化 点击区域 矩阵
 * 
 */
void initAlbum();
/**
 * @brief 播放开机动画
 * 
 */
void playVideo();
/**
 * @brief 显示 相册 模块
 * 
 */
void showAlbum();
/**
 * @brief 相册 逻辑入口
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 * @return true 事件已被消费
 * @return false 事件未被消费
 */
bool albumHandler(int x, int y);
#endif