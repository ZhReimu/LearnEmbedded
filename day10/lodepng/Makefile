CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBPATH) $(SRC)lodepng.c $(SRC)main.c -o color

clean:
	rm color