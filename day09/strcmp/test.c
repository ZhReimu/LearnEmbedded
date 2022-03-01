#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief 判断两个字符串是否相等
 * 
 * @param arg1 字符串 1
 * @param arg2 字符串 2
 * @return true 相等就返回 true
 * @return false 不等就返回 false
 */
bool stringCmp(const char *arg1, const char *arg2)
{
	if (strcmp(arg1, arg2) == 0)
	{
		return true;
	}
	return false;
}

int main()
{
	const char *pwd = "123456";
	if (stringCmp(pwd, "1234567"))
	{
		puts("true");
	}
	else
	{
		puts("false");
	}
	return 0;
}