#include <passwd.h>

/**
 * @brief 数字 0 按钮区域
 * 
 */
Rect btNum0;
/**
 * @brief 数字 1 按钮区域
 * 
 */
Rect btNum1;
/**
 * @brief 数字 2 按钮区域
 * 
 */
Rect btNum2;
/**
 * @brief 数字 3 按钮区域
 * 
 */
Rect btNum3;
/**
 * @brief 数字 4 按钮区域
 * 
 */
Rect btNum4;
/**
 * @brief 数字 5 按钮区域
 * 
 */
Rect btNum5;
/**
 * @brief 数字 6 按钮区域
 * 
 */
Rect btNum6;
/**
 * @brief 数字 7 按钮区域
 * 
 */
Rect btNum7;
/**
 * @brief 数字 8 按钮区域
 * 
 */
Rect btNum8;
/**
 * @brief 数字 9 按钮区域
 * 
 */
Rect btNum9;
/**
 * @brief 退格 按钮区域
 * 
 */
Rect btDel;
/**
 * @brief 登录 按钮区域
 * 
 */
Rect btYes;
/**
 * @brief 账号输入 按钮区域
 * 
 */
Rect btAccount;
/**
 * @brief 密码输入 按钮区域
 * 
 */
Rect btPasswd;
/**
 * @brief 显示密码 按钮区域
 * 
 */
Rect btShowPass;
/**
 * @brief 账号输入框矩形 数组
 * 
 */
Rect edAccount[4];
/**
 * @brief 密码输入框矩形 数组
 * 
 */
Rect edPassword[4];

/**
 * @brief 密码文件 路径
 * 
 */
static const char *pwdFile = "/mnt/udisk/passwd";
/**
 * @brief 锁屏界面 图片
 * 
 */
static const char *bg = "/mnt/udisk/lock/lockbg.bmp";
/**
 * @brief ※ 号图片
 * 
 */
static const char *good = "/mnt/udisk/lock/good.bmp";
/**
 * @brief 数字图片路径 数组
 * 
 */
static const char *nums[] = {
    "/mnt/udisk/lock/0.bmp",
    "/mnt/udisk/lock/1.bmp",
    "/mnt/udisk/lock/2.bmp",
    "/mnt/udisk/lock/3.bmp",
    "/mnt/udisk/lock/4.bmp",
    "/mnt/udisk/lock/5.bmp",
    "/mnt/udisk/lock/6.bmp",
    "/mnt/udisk/lock/7.bmp",
    "/mnt/udisk/lock/8.bmp",
    "/mnt/udisk/lock/9.bmp",
};
/**
 * @brief 读取到的 密码内容
 * 
 */
static char pwd[4] = {0};
/**
 * @brief 数字上屏
 * 
 * @param num 要上屏的数字
 * @param target 显示在哪里
 */
void showNum(int num, Rect target)
{
    showBMP(nums[num - 1], target.startX, target.startY, 0);
}
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
    // TODO: 修改坐标
    edAccount[0].startX = 122;
    edAccount[0].endX = 614;
    edAccount[0].startY = 388;
    edAccount[0].endY = 506;

    edAccount[1].startX = 122;
    edAccount[1].endX = 614;
    edAccount[1].startY = 388;
    edAccount[1].endY = 506;

    edAccount[2].startX = 122;
    edAccount[2].endX = 614;
    edAccount[2].startY = 388;
    edAccount[2].endY = 506;

    edAccount[3].startX = 122;
    edAccount[3].endX = 614;
    edAccount[3].startY = 388;
    edAccount[3].endY = 506;

    edPassword[0].startX = 122;
    edPassword[0].endX = 614;
    edPassword[0].startY = 388;
    edPassword[0].endY = 506;

    edPassword[1].startX = 122;
    edPassword[1].endX = 614;
    edPassword[1].startY = 388;
    edPassword[1].endY = 506;

    edPassword[2].startX = 122;
    edPassword[2].endX = 614;
    edPassword[2].startY = 388;
    edPassword[2].endY = 506;

    edPassword[3].startX = 122;
    edPassword[3].endX = 614;
    edPassword[3].startY = 388;
    edPassword[3].endY = 506;

    debug("Init Passwd", INFO);
}