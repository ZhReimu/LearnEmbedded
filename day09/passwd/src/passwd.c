#include <passwd.h>

/**
 * @brief 密码文件 路径
 * 
 */
static const char *pwdFile = "/mnt/udisk/passwd";
/**
 * @brief 读取到的 密码内容
 * 
 */
static char pwd[4] = {0};
/**
 * @brief 播放器处理函数
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
    debug("Init Passwd", INFO);
}