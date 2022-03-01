CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)videoPlayer.c $(SRC)myplayer.c -o color

test:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)test.c -o ./src/test.o

log:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)log.c -fPIC -shared -o ./src/log.o

player:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)videoPlayer.c -fPIC -shared -o ./src/player.o

utils:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)utils.c -fPIC -shared -o ./src/utils.o

clean:
	rm color
	rm log.o
	rm player.o
	rm utils.o