CC = arm-linux-gcc
CFLAGS = -s -O2
# CC = arm-none-eabi-gcc
# Flags For NoneUnix
# CFLAGS = --specs=nosys.specs -O2 -s


all:
	$(CC) $(CFLAGS) color.c util.c -o color

clean:
	rm color