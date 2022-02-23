CC = arm-linux-gcc
CFLAGS = -s -O2 --shared
# CC = arm-none-eabi-gcc
# Flags For NoneUnix
# CFLAGS = --specs=nosys.specs -O2 -s


all:
	$(CC) $(CFLAGS) utils.c -o utils.so

clean:
	rm utils.so