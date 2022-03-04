#include <log.h>

/**
 * @brief 在控制台输出一条日志 ( 字符串 )
 * 
 * @param msg 日志消息
 * @param logType 日志等级
 */
void debug(const char *msg, int logType)
{
    if (LOG_LEVEL <= DEBUG && logType == DEBUG)
    {
        printf("DEBUG: ");
        puts(msg);
        printf("\n");
    }
    else if (LOG_LEVEL <= INFO && logType == INFO)
    {
        printf("INFO: ");
        puts(msg);
        printf("\n");
    }
    else if (LOG_LEVEL <= WARN && logType == WARN)
    {
        printf("WARN: ");
        puts(msg);
        printf("\n");
    }
    else if (LOG_LEVEL <= ERROR && logType == ERROR)
    {
        printf("ERROR: ");
        puts(msg);
        printf("\n");
    }
}
/**
 * @brief 在控制台输出一条日志 ( 格式化字符串, 一个 char* 类型的参数 )
 * 
 * @param format 带格式化字符串的日志消息
 * @param args 格式参数 ( char* 类型 )
 * @param logType 日志等级
 */
void debugS(const char *format, const char *args, int logType)
{
    if (LOG_LEVEL <= DEBUG && logType == DEBUG)
    {
        printf("DEBUG: ");
        printf(format, args);
        printf("\n");
    }
    else if (LOG_LEVEL <= INFO && logType == INFO)
    {
        printf("INFO: ");
        printf(format, args);
        printf("\n");
    }
    else if (LOG_LEVEL <= WARN && logType == WARN)
    {
        printf("WARN: ");
        printf(format, args);
        printf("\n");
    }
    else if (LOG_LEVEL <= ERROR && logType == ERROR)
    {
        printf("ERROR: ");
        printf(format, args);
        printf("\n");
    }
}
/**
 * @brief 在控制台输出一条日志 ( 格式化字符串, 一个 int 类型的参数 )
 * 
 * @param format 带格式化字符串的日志消息
 * @param arg 格式参数( int 类型 )
 * @param logType 日志等级
 */
void debugD(const char *format, int arg, int logType)
{
    if (LOG_LEVEL <= DEBUG && logType == DEBUG)
    {
        printf("DEBUG: ");
        printf(format, arg);
        printf("\n");
    }
    else if (LOG_LEVEL <= INFO && logType == INFO)
    {
        printf("INFO: ");
        printf(format, arg);
        printf("\n");
    }
    else if (LOG_LEVEL <= WARN && logType == WARN)
    {
        printf("WARN: ");
        printf(format, arg);
        printf("\n");
    }
    else if (LOG_LEVEL <= ERROR && logType == ERROR)
    {
        printf("ERROR: ");
        printf(format, arg);
        printf("\n");
    }
}
/**
 * @brief 在控制台输出一条日志 ( 格式化字符串, 2 个 int 类型的参数 )
 * 
 * @param format 带格式化字符串的日志消息
 * @param arg 格式参数 1 ( int 类型 )
 * @param arg2 格式参数 2 ( int 类型 )
 * @param logType 日志等级
 */
void debug2D(const char *format, int arg, int arg2, int logType)
{
    if (LOG_LEVEL <= DEBUG && logType == DEBUG)
    {
        printf("DEBUG: ");
        printf(format, arg, arg2);
        printf("\n");
    }
    else if (LOG_LEVEL <= INFO && logType == INFO)
    {
        printf("INFO: ");
        printf(format, arg, arg2);
        printf("\n");
    }
    else if (LOG_LEVEL <= WARN && logType == WARN)
    {
        printf("WARN: ");
        printf(format, arg, arg2);
        printf("\n");
    }
    else if (LOG_LEVEL <= ERROR && logType == ERROR)
    {
        printf("ERROR: ");
        printf(format, arg, arg2);
        printf("\n");
    }
}