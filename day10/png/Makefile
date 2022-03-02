CC = arm-linux-gcc
CFLAGS = -s -O2 -lpthread
INCLUDE = -I./include
LIBPATH = -L ./lib
LIBS = -l png16 -l z -l m
SRC = ./src/

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBPATH) $(SRC)png.c $(LIBS)  -o color

clean:
	rm color