CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/

all: log.o utils.o bmp.o passwd.o
	$(CC) $(CFLAGS) $(INCLUDE) log.o utils.o bmp.o passwd.o $(SRC)main.c -o color

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

test:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)utils.c $(SRC)test.c -o color

clean:
	rm *.o