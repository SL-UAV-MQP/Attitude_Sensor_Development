CC = gcc -std=gnu99
CFLAGS = -e c -pedantic -g -Wall -Wno-unused-variable
CFLAGSO = -e c -pedantic -g -Wall -Wno-unused-variable -c

RFFE_Test: RFFE_Test.o RFFE_Functions.o
	$(CC) $(CFLAG) RFFE_Test.o RFFE_Functions.o  -o RFFE_Test -l wiringPi

RFFE_Test.o: RFFE_Test.c RFFE.h
	$(CC) $(CFLAGSO) RFFE_Test.c

RFFE_Functions.o: RFFE_Functions.c RFFE.h
	$(CC) $(CFLAGSO) RFFE_Functions.c

clean:
	rm -f *.o
	rm -f RFFE_Test

run:
	clear
	sudo ./RFFE_Test

all: clean RFFE_Test