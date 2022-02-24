CC = arm-linux-gcc
CFLAGS = -s -O2 -fPIC --shared
INCLUDE = -I../include
# CC = arm-none-eabi-gcc
# Flags For NoneUnix
# CFLAGS = --specs=nosys.specs -O2 -s


all:
	$(CC) $(CFLAGS) $(INCLUDE) utils.c -o libutils.so

clean:
	rm libutils.so