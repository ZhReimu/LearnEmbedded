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
 * @brief Home 模块主要逻辑
 * 
 * @param x 点击的坐标的 x
 * @param y 点击的坐标的 y
 */
void homeHandler(int x, int y);
#endif