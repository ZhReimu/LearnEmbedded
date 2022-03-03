#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
/**
 * @brief 当前日志等级
 * 
 */
#define LOG_LEVEL WARN
/**
 * @brief 日志等级枚举
 * 
 */
enum LOG
{
	/**
	 * @brief DEBUG 、输出最多的日志，包含大量调试信息
	 * 
	 */
	DEBUG,
	/**
	 * @brief INFO、输出需要注意的一些日志
	 * 
	 */
	INFO,
	/**
	 * @brief WARN、输出可能会出问题的一些日志
	 * 
	 */
	WARN,
	/**
	 * @brief ERROR、输出错误日志
	 * 
	 */
	ERROR
};

/**
 * @brief 在控制台输出一条日志 ( 字符串 )
 * 
 * @param msg 日志消息
 * @param logType 日志等级
 */
void debug(const char *msg, int logType);
/**
 * @brief 在控制台输出一条日志 ( 格式化字符串, 一个 int 类型的参数 )
 * 
 * @param format 带格式化字符串的日志消息
 * @param arg 格式参数( int 类型 )
 * @param logType 日志等级
 */
void debugD(const char *format, int arg, int logType);
/**
 * @brief 在控制台输出一条日志 ( 格式化字符串, 一个 char* 类型的参数 )
 * 
 * @param format 带格式化字符串的日志消息
 * @param args 格式参数 ( char* 类型 )
 * @param logType 日志等级
 */
void debugS(const char *format, const char *args, int logType);
/**
 * @brief 在控制台输出一条日志 ( 格式化字符串, 2 个 int 类型的参数 )
 * 
 * @param format 带格式化字符串的日志消息
 * @param arg 格式参数 1 ( int 类型 )
 * @param arg2 格式参数 2 ( int 类型 )
 * @param logType 日志等级
 */
void debug2D(const char *format, int arg, int arg2, int logType);
#endif