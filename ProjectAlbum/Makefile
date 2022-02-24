CC = arm-linux-gcc
CFLAGS = -s -O2
INCLUDE = -I../include

# CC = arm-none-eabi-gcc
# Flags For NoneUnix
# CFLAGS = --specs=nosys.specs -O2 -s


all:libs main


.PHONY: libs main

libs:
	cd libs && make

main:
	cd src && make

clean:
	- rm ./libs/libutils.so
	- rm ./src/color