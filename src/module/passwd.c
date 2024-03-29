#include <passwd.h>
#include <picPaths.h>
#include <global.h>
#include <home.h>
#include <beep.h>

static Rect btNums[10];
/**
 * @brief 退格 按钮区域
 * 
 */
static Rect btDel;
/**
 * @brief 显示密码 按钮区域
 * 
 */
static Rect btShowAndHide;
/**
 * @brief 账号输入 按钮区域
 * 
 */
static Rect btAccount;
/**
 * @brief 密码输入 按钮区域
 * 
 */
static Rect btPasswd;
/**
 * @brief 登录 按钮区域
 * 
 */
static Rect btLogin;
/**
 * @brief 账号输入框矩形 数组
 * 
 */
static Rect edAccount[4];
/**
 * @brief 密码输入框矩形 数组
 * 
 */
static Rect edPassword[4];

/**
 * @brief 读取到的 密码内容
 * 
 */
static char pwd[5] = {0};
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
 * @brief 项目全局变量, 当前模块
 * 
 */
extern int CURRENT_MODULE;
/**
 * @brief 销毁界面时调用
 * 
 */
static void onDestroyed()
{
    INPUT_STATUS = ACCOUNT;
    PASSWD_STATUS = HIDE;
    accountIdx = 0;
    passwdIdx = 0;
}
/**
 * @brief 数字上屏
 * 
 * @param num 要上屏的数字
 * @param target 显示在哪里
 */
void showNum(int num, Rect target)
{
    showBMP(nums[num], target.startX, target.startY, 1);
}
/**
 * @brief 刷新输入框
 * 
 */
void refreshEdit()
{
    if (PASSWD_STATUS == SHOW)
    {
        showBMPOO(openBG[INPUT_STATUS]);
    }
    else
    {
        showBMPOO(closeBG[INPUT_STATUS]);
    }
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
            showBMP(good, edPassword[i].startX, edPassword[i].startY, 1);
        }
    }
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
            beepStart(100000);
            return;
        }
        account[accountIdx++] = num;
    }
    else
    {
        if (passwdIdx == 4)
        {
            beepStart(100000);
            return;
        }
        passwd[passwdIdx++] = num;
    }
    refreshEdit();
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
    int i = 0;
    for (i = 0; i < length; i++)
    {
        cArr[i] = iArr[i] + '0';
    }
    cArr[i] = '\0';
}
/**
 * @brief 密码界面 逻辑入口
 * 
 * @param x 点击的 x 坐标
 * @param y 点击的 y 坐标
 * @return true 事件已被消费
 * @return false 事件未被消费
 */
bool passwdHandler(int x, int y)
{
    if (CURRENT_MODULE != PASSWORD)
    {
        showCurrentModule("Password");
        return false;
    }
    debug2D("Passwd Handler %d, %d", x, y, DEBUG);
    for (int i = 0; i < 10; i++)
    {
        if (inArea2(btNums[i], x, y))
        {
            changeArr(i);
            return true;
        }
    }

    if (inArea2(btAccount, x, y))
    {
        INPUT_STATUS = ACCOUNT;
        refreshEdit();
        debug("Hit Account", INFO);
    }
    else if (inArea2(btPasswd, x, y))
    {
        INPUT_STATUS = PASSWD;
        refreshEdit();
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
            else
            {
                beepStart(100000);
            }
        }
        else
        {
            if (passwdIdx > 0)
            {
                passwdIdx--;
            }
            else
            {
                beepStart(100000);
            }
        }
        debug("Hit Del", INFO);
        refreshEdit();
    }
    else if (inArea2(btShowAndHide, x, y))
    {
        if (PASSWD_STATUS == SHOW)
        {
            PASSWD_STATUS = HIDE;
        }
        else
        {
            PASSWD_STATUS = SHOW;
        }
        refreshEdit();
        debug("Hit ShowPass", INFO);
    }
    else if (inArea2(btLogin, x, y))
    {
        char temp[5] = {0};
        ia2ca(passwd, temp, passwdIdx);
        debug(temp, INFO);
        debug(pwd, INFO);
        if (stringCmp(pwd, temp))
        {
            onDestroyed();
            showHome();
            debug("Pass", INFO);
        }
        else
        {
            beepStart(1500000);
            debug("Error", INFO);
        }
        debug("Hit Yes", INFO);
    }
    else
    {
        debug("Password Handler Not Hit", INFO);
    }
    return true;
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
    close(fd);
    debugS("Correct PWD Is %s", pwd, INFO);

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

    btLogin.startX = 122;
    btLogin.endX = 614;
    btLogin.startY = 388;
    btLogin.endY = 506;

    btAccount.startX = 120;
    btAccount.endX = 614;
    btAccount.startY = 150;
    btAccount.endY = 268;

    btPasswd.startX = 120;
    btPasswd.endX = 614;
    btPasswd.startY = 268;
    btPasswd.endY = 385;

    btShowAndHide.startX = 892;
    btShowAndHide.endX = 975;
    btShowAndHide.startY = 269;
    btShowAndHide.endY = 387;

    edAccount[0].startX = 219;
    edAccount[0].endX = 284;
    edAccount[0].startY = 117;
    edAccount[0].endY = 210;

    edAccount[1].startX = 284;
    edAccount[1].endX = 349;
    edAccount[1].startY = 117;
    edAccount[1].endY = 210;

    edAccount[2].startX = 349;
    edAccount[2].endX = 414;
    edAccount[2].startY = 117;
    edAccount[2].endY = 210;

    edAccount[3].startX = 414;
    edAccount[3].endX = 479;
    edAccount[3].startY = 117;
    edAccount[3].endY = 210;

    edPassword[0].startX = 219;
    edPassword[0].endX = 284;
    edPassword[0].startY = 210;
    edPassword[0].endY = 302;

    edPassword[1].startX = 284;
    edPassword[1].endX = 349;
    edPassword[1].startY = 210;
    edPassword[1].endY = 302;

    edPassword[2].startX = 349;
    edPassword[2].endX = 414;
    edPassword[2].startY = 210;
    edPassword[2].endY = 302;

    edPassword[3].startX = 414;
    edPassword[3].endX = 479;
    edPassword[3].startY = 210;
    edPassword[3].endY = 302;

    debug("Init Passwd", INFO);
}
/**
 * @brief 显示 密码模块
 * 
 */
void showLockScreen()
{
    debug("Show LockScreen", INFO);
    CURRENT_MODULE = PASSWORD;
    showBMPOO(closeBG[INPUT_STATUS]);
}