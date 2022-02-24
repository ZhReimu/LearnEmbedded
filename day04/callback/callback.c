#include<stdio.h>

void T(){
	puts("This is T");
}

void test(void (*T)()){
	(*T)();
}

int main(){
	test(T);
	return 0;
}