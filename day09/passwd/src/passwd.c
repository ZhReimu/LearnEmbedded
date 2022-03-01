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

    btNum0.startX = 697;
    btNum0.endX = 762;
    btNum0.startY = 302;
    btNum0.endY = 395;

    btNum1.startX = 502;
    btNum1.endX = 567;
    btNum1.startY = 117;
    btNum1.endY = 210;

    btNum2.startX = 567;
    btNum2.endX = 632;
    btNum2.startY = 117;
    btNum2.endY = 210;

    btNum3.startX = 632;
    btNum3.endX = 697;
    btNum3.startY = 117;
    btNum3.endY = 210;

    btNum4.startX = 502;
    btNum4.endX = 567;
    btNum4.startY = 210;
    btNum4.endY = 302;

    btNum5.startX = 567;
    btNum5.endX = 632;
    btNum5.startY = 210;
    btNum5.endY = 302;

    btNum6.startX = 632;
    btNum6.endX = 697;
    btNum6.startY = 210;
    btNum6.endY = 302;

    btNum7.startX = 502;
    btNum7.endX = 567;
    btNum7.startY = 302;
    btNum7.endY = 395;

    btNum8.startX = 567;
    btNum8.endX = 632;
    btNum8.startY = 302;
    btNum8.endY = 395;

    btNum9.startX = 632;
    btNum9.endX = 697;
    btNum9.startY = 302;
    btNum9.endY = 395;

    btDel.startX = 697;
    btDel.endX = 762;
    btDel.startY = 117;
    btDel.endY = 210;

    btYes.startX = 697;
    btYes.endX = 762;
    btYes.startY = 210;
    btYes.endY = 302;

    btAccount.startX = 94;
    btAccount.endX = 480;
    btAccount.startY = 117;
    btAccount.endY = 209;

    btPasswd.startX = 94;
    btPasswd.endX = 480;
    btPasswd.startY = 209;
    btPasswd.endY = 301;

    btShowPass.startX = 95;
    btShowPass.endX = 480;
    btShowPass.startY = 303;
    btShowPass.endY = 395;

    debug("Init Passwd", INFO);
}