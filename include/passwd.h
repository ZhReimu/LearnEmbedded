#ifndef _PASSWD_H_
#define _PASSWD_H_

#include <log.h>
#include <bmp.h>
#include <utils.h>

/**
 * @brief 密码界面 逻辑入口
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 * @return true 事件已被消费
 * @return false 事件未被消费
 */
bool passwdHandler(int x, int y);
/**
 * @brief 初始化 点击区域
 * 
 */
void initPasswd();
/**
 * @brief 显示 密码模块
 * 
 */
void showLockScreen();
#endif