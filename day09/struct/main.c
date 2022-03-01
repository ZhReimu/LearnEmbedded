#include <stdio.h>

// void (*T)()
// 	(*T)();
typedef struct test
{
	int t;
	void (*callback)();
} T;

void test(){
	puts("I AM IN Test");
}

int main(){
	T t;
	t.t = 123;
	t.callback = test;
	printf("%d\n", t.t);
	t.callback();
	return 0;
}