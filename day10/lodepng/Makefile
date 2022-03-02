CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
SRC = ./src/
LIBPATH = -L ./lib
LIB = -l lodepng

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBPATH) $(SRC)log.c $(SRC)utils.c $(SRC)main.c $(LIB) -o color

lodepng:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBPATH) $(SRC)lodepng.c --shared -fPIC -o ./lib/liblodepng.so

clean:
	rm color