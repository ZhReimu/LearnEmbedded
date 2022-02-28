CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I.

all:
	$(CC) $(CFLAGS) $(INCLUDE) utils.c myplayer.c -o color

test:
	$(CC) $(CFLAGS) $(INCLUDE) utils.c test.c -o color

clean:
	rm color