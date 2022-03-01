#include <passwd.h>

Rect btNum0;
Rect btNum1;
Rect btNum2;
Rect btNum3;
Rect btNum4;
Rect btNum5;
Rect btNum6;
Rect btNum7;
Rect btNum8;
Rect btNum9;
Rect btDel;
Rect btYes;
Rect btAccount;
Rect btPasswd;
Rect btShowPass;

/**
 * @brief 密码文件 路径
 * 
 */
static const char *pwdFile = "/mnt/udisk/passwd";
static const char *bg = "/mnt/udisk/lock/lockbg.bmp";
/**
 * @brief 读取到的 密码内容
 * 
 */
static char pwd[4] = {0};
/**
 * @brief 密码界面处理函数
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 */
void passwdHandler(int x, int y)
{
    debug2D("PasswdHandler %d, %d", x, y, INFO);
    if (inArea2(btNum0, x, y))
    {
        debug("Hit Num0", INFO);
    }
    else if (inArea2(btNum1, x, y))
    {
        debug("Hit Num1", INFO);
    }
    else if (inArea2(btNum2, x, y))
    {
        debug("Hit Num2", INFO);
    }
    else if (inArea2(btNum3, x, y))
    {
        debug("Hit Num3", INFO);
    }
    else if (inArea2(btNum4, x, y))
    {
        debug("Hit Num4", INFO);
    }
    else if (inArea2(btNum5, x, y))
    {
        debug("Hit Num5", INFO);
    }
    else if (inArea2(btNum6, x, y))
    {
        debug("Hit Num6", INFO);
    }
    else if (inArea2(btNum7, x, y))
    {
        debug("Hit Num7", INFO);
    }
    else if (inArea2(btNum8, x, y))
    {
        debug("Hit Num8", INFO);
    }
    else if (inArea2(btNum9, x, y))
    {
        debug("Hit Num9", INFO);
    }
    else if (inArea2(btAccount, x, y))
    {
        debug("Hit Account", INFO);
    }
    else if (inArea2(btDel, x, y))
    {
        debug("Hit Del", INFO);
    }
    else if (inArea2(btPasswd, x, y))
    {
        debug("Hit Passwd", INFO);
    }
    else if (inArea2(btShowPass, x, y))
    {
        debug("Hit ShowPass", INFO);
    }
    else if (inArea2(btYes, x, y))
    {
        debug("Hit Yes", INFO);
    }
    else
    {
        debug("Not Hit", INFO);
    }
}
/**
 * @brief 初始化 点击区域
 * 
 */
void initPasswd()
{
    int fd = open(pwdFile, O_RDONLY);
    if (fd < 0)
    {
        debug("Open Password File Failure!", ERROR);
        exit(-1);
    }
    read(fd, pwd, 4);
    debugS("Correct PWD Is %s", pwd, INFO);
    showBMPOO(bg);

    btNum0.startX = 892;
    btNum0.endX = 975;
    btNum0.startY = 378;
    btNum0.endY = 506;

    btNum1.startX = 643;
    btNum1.endX = 726;
    btNum1.startY = 150;
    btNum1.endY = 267;

    btNum2.startX = 726;
    btNum2.endX = 809;
    btNum2.startY = 150;
    btNum2.endY = 267;

    btNum3.startX = 809;
    btNum3.endX = 892;
    btNum3.startY = 150;
    btNum3.endY = 267;

    btNum4.startX = 643;
    btNum4.endX = 726;
    btNum4.startY = 267;
    btNum4.endY = 387;

    btNum5.startX = 726;
    btNum5.endX = 809;
    btNum5.startY = 267;
    btNum5.endY = 387;

    btNum6.startX = 809;
    btNum6.endX = 892;
    btNum6.startY = 267;
    btNum6.endY = 387;

    btNum7.startX = 643;
    btNum7.endX = 726;
    btNum7.startY = 378;
    btNum7.endY = 506;

    btNum8.startX = 726;
    btNum8.endX = 809;
    btNum8.startY = 378;
    btNum8.endY = 506;

    btNum9.startX = 809;
    btNum9.endX = 892;
    btNum9.startY = 378;
    btNum9.endY = 506;

    btDel.startX = 892;
    btDel.endX = 975;
    btDel.startY = 150;
    btDel.endY = 267;

    btYes.startX = 892;
    btYes.endX = 975;
    btYes.startY = 269;
    btYes.endY = 387;

    btAccount.startX = 120;
    btAccount.endX = 614;
    btAccount.startY = 150;
    btAccount.endY = 268;

    btPasswd.startX = 120;
    btPasswd.endX = 614;
    btPasswd.startY = 268;
    btPasswd.endY = 385;

    btShowPass.startX = 122;
    btShowPass.endX = 614;
    btShowPass.startY = 388;
    btShowPass.endY = 506;

    debug("Init Passwd", INFO);
}