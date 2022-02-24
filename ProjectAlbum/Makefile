CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include

all:
	$(CC) $(CFLAGS) $(INCLUDE) utils.c main.c -o color

clean:
	rm color