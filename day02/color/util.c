#include "myHeader.h"


void setColor(char* buff, int x, int y, int c){
	int start = 0 + 4 * x + 800 * 4 * y;
	
	buff[0 + start] = 0;
	buff[1 + start] = 0;
	buff[2 + start] = 0;
	buff[3 + start] = 0;
	
	switch(c) {
		case RED:
			buff[2 + start] = 0xFF;
			break;
		case GREEN:
			buff[1 + start] = 0xFF;
			break;
		case BLUE:
			buff[0 + start] = 0xFF;
			break;
	}
}