#include <stdio.h>

#define DEBUG_INFO(format, ...) printf(format, ##__VA_ARGS__)
#ifdef 1
#define AAA 123
#endif
int main(){
	
	DEBUG_INFO("%d\n", AAA);
	return 0;
}