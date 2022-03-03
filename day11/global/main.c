#include <stdio.h>
#include "test.h"
int g = 123;

int main(){
	printf("g in main %d\n", g);
	g = 456;
	testInTest();
	return 0;
}