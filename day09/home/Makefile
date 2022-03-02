CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)log.c $(SRC)utils.c $(SRC)bmp.c $(SRC)home.c $(SRC)main.c -o color

clean:
	- rm color