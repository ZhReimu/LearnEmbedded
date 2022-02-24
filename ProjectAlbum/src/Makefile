CC = arm-linux-gcc
CFLAGS = -s -O2
INCLUDE = -I../include
LIBPATH = -L../libs
LDLIBS = -lutils
# CC = arm-none-eabi-gcc
# Flags For NoneUnix
# CFLAGS = --specs=nosys.specs -O2 -s


all:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBPATH) $(LDLIBS) main.c -o color

clean:
	rm color