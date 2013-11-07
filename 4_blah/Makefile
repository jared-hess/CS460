# To use this makefile to create the executable file, type:
# make
# To use this makefile to delete all the object files, type:
# make clean
#
# Author: Dr. Zaman; WSU-5261
# Date: 2013/08/22
#

CC=gcc
CFLAGS=-I. -std=c99
DEPS = MyHeader.h
OBJ = prog4.o LateByDays.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

aa.exe: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f ./*.o
