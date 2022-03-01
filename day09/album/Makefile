CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)album.c $(SRC)main.c -o color

utils:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)utils.c -fPIC -shared -o $(SRC)utils.o

log:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)log.c -fPIC -shared -o $(SRC)log.o

album:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)album.c -fPIC -shared -o $(SRC)album.o

clean:
	- rm color
	- rm $(SRC)log.o
	- rm $(SRC)album.o
	- rm $(SRC)utils.o