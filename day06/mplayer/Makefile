CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)utils.c $(SRC)videoPlayer.c $(SRC)myplayer.c -o color

test:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)utils.c $(SRC)test.c -o color

clean:
	rm color