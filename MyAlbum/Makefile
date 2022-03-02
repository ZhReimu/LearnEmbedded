CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/

all: 
	$(CC) $(CFLAGS) $(INCLUDE) \
	$(SRC)log.c $(SRC)utils.c $(SRC)bmp.c \
	$(SRC)album.c $(SRC)passwd.c $(SRC)home.c \
	$(SRC)main.c -o color

album:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(SRC)album.c

home:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(SRC)home.c

music:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(SRC)musicPlayer.c

passwd:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(SRC)passwd.c

video:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(SRC)videoPlayer.c

utils:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c

log:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c

bmp:
	$(CC) $(CFLAGS) -c $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c

test:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)utils.c $(SRC)test.c -o color

clean:
	rm *.o