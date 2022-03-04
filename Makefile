CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/
MODULE = $(SRC)module/

all: 
	$(CC) $(CFLAGS) $(INCLUDE) \
	$(SRC)log.c $(SRC)utils.c $(SRC)bmp.c \
	$(MODULE)album.c $(MODULE)passwd.c $(MODULE)home.c \
	$(MODULE)videoPlayer.c $(MODULE)musicPlayer.c $(SRC)beep.c \
	$(SRC)main.c -o color

album:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(MODULE)album.c

home:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(MODULE)home.c

music:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(MODULE)musicPlayer.c

passwd:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(MODULE)passwd.c

video:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(MODULE)videoPlayer.c

utils:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c

log:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c

bmp:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c

beep:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)beep.c

test:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)utils.c $(SRC)test.c -o color

clean:
	rm *.o