#include <passwd.h>

Rect btNums[10];
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
 * @brief 输入状态 枚举
 * 
 */
enum INPUT
{
    /**
     * @brief 正在输入 账号
     * 
     */
    ACCOUNT,
    /**
     * @brief 正在输入 密码
     * 
     */
    PASSWD,
};
/**
 * @brief 密码状态 枚举
 * 
 */
enum PASSWORD
{
    /**
     * @brief 显示密码
     * 
     */
    SHOW,
    /**
     * @brief 隐藏密码
     * 
     */
    HIDE
};
/**
 * @brief 当前输入状态
 * 
 */
static int INPUT_STATUS = ACCOUNT;
/**
 * @brief 密码状态
 * 
 */
static int PASSWD_STATUS = HIDE;
/**
 * @brief 当前 账号 文本框内文本个数
 * 
 */
static int accountIdx = 0;
/**
 * @brief 当前 密码 文本框内文本个数
 * 
 */
static int passwdIdx = 0;
/**
 * @brief 账号 内容
 * 
 */
static int account[4] = {0};
/**
 * @brief 密码 内容
 * 
 */
static int passwd[4] = {0};
/**
 * @brief 数字上屏
 * 
 * @param num 要上屏的数字
 * @param target 显示在哪里
 */
void showNum(int num, Rect target)
{
    showBMP(nums[num], target.startX, target.startY, 0);
}
/**
 * @brief 修改 账号 或 密码 数组
 * 
 * @param num 输入的数字
 */
void changeArr(int num)
{
    if (INPUT_STATUS == ACCOUNT)
    {
        if (accountIdx == 4)
        {
            return;
        }
        account[accountIdx++] = num;
    }
    else
    {
        if (passwdIdx == 4)
        {
            return;
        }
        passwd[passwdIdx++] = num;
    }
}
/**
 * @brief 刷新输入框
 * 
 */
void refreshEdit()
{
    showBMPOO(bg);
    for (int i = 0; i < accountIdx; i++)
    {
        showNum(account[i], edAccount[i]);
    }
    for (int i = 0; i < passwdIdx; i++)
    {
        if (PASSWD_STATUS == SHOW)
        {
            showNum(passwd[i], edPassword[i]);
        }
        else
        {
            showBMP(good, edPassword[i].startX, edPassword[i].startY, 0);
        }
    }
}
/**
 * @brief Int 数组 转换 char 数组
 * 
 * @param iArr 要转换的 int 数组
 * @param cArr 转换后的 char 数组
 * @param length int 数组长度
 */
void ia2ca(const int iArr[], char cArr[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cArr[i] = iArr[i] + '0';
    }
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
    for (int i = 0; i < 10; i++)
    {
        if (inArea2(btNums[i], x, y))
        {
            changeArr(i);
            refreshEdit();
            return;
        }
    }
    if (inArea2(btAccount, x, y))
    {
        INPUT_STATUS = ACCOUNT;
        debug("Hit Account", INFO);
    }
    else if (inArea2(btPasswd, x, y))
    {
        INPUT_STATUS = PASSWD;
        debug("Hit Passwd", INFO);
    }
    // 如果 点击了 删除 按钮
    else if (inArea2(btDel, x, y))
    {
        if (INPUT_STATUS == ACCOUNT)
        {
            if (accountIdx > 0)
            {
                accountIdx--;
            }
        }
        else
        {
            if (passwdIdx > 0)
            {
                passwdIdx--;
            }
        }
        debug("Hit Del", INFO);
    }
    else if (inArea2(btShowPass, x, y))
    {
        if (PASSWD_STATUS == SHOW)
        {
            PASSWD_STATUS = HIDE;
        }
        else
        {
            PASSWD_STATUS = SHOW;
        }
        debug("Hit ShowPass", INFO);
    }
    else if (inArea2(btYes, x, y))
    {
        char temp[4] = {0};
        ia2ca(passwd, temp, passwdIdx);
        if (stringCmp(pwd, temp))
        {
            debug("Pass", INFO);
        }
        else
        {
            debug("Error", INFO);
        }
        debug("Hit Yes", INFO);
    }
    else
    {
        debug("Not Hit", INFO);
    }
    refreshEdit();
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

    btNums[0].startX = 892;
    btNums[0].endX = 975;
    btNums[0].startY = 378;
    btNums[0].endY = 506;

    btNums[1].startX = 643;
    btNums[1].endX = 726;
    btNums[1].startY = 150;
    btNums[1].endY = 267;

    btNums[2].startX = 726;
    btNums[2].endX = 809;
    btNums[2].startY = 150;
    btNums[2].endY = 267;

    btNums[3].startX = 809;
    btNums[3].endX = 892;
    btNums[3].startY = 150;
    btNums[3].endY = 267;

    btNums[4].startX = 643;
    btNums[4].endX = 726;
    btNums[4].startY = 267;
    btNums[4].endY = 387;

    btNums[5].startX = 726;
    btNums[5].endX = 809;
    btNums[5].startY = 267;
    btNums[5].endY = 387;

    btNums[6].startX = 809;
    btNums[6].endX = 892;
    btNums[6].startY = 267;
    btNums[6].endY = 387;

    btNums[7].startX = 643;
    btNums[7].endX = 726;
    btNums[7].startY = 378;
    btNums[7].endY = 506;

    btNums[8].startX = 726;
    btNums[8].endX = 809;
    btNums[8].startY = 378;
    btNums[8].endY = 506;

    btNums[9].startX = 809;
    btNums[9].endX = 892;
    btNums[9].startY = 378;
    btNums[9].endY = 506;

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