#ifndef _HOME_H_
#define _HOME_H_

#include <log.h>
#include <bmp.h>
#include <utils.h>
#include <global.h>
#include <picPaths.h>

/**
 * @brief 初始化 Home 模块有效点击区域
 * 
 */
void initHome();
/**
 * @brief 显示 Home 模块
 * 
 */
void showHome();
/**
 * @brief Home 模块 逻辑入口
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 * @return true 事件已被消费
 * @return false 事件未被消费
 */
bool homeHandler(int x, int y);
#endif