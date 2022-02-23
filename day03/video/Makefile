CC = arm-linux-gcc
CFLAGS = -s -O2

# For Windows
#CC = arm-none-eabi-gcc
#CFLAGS = --specs=nosys.specs -O2 -s

INC = -I ../.././XUtils
UTILS = ../../XUtils/utils.c


all:color.c $(LIB)
	$(CC) $(CFLAGS) $(INC) $(UTILS) color.c -o color

clean:
	rm color