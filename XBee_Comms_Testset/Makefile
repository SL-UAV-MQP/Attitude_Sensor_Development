CC = gcc -std=gnu99
CFLAGS = -e c -pedantic -g -Wall -Wno-unused-variable
CFLAGSO = -e c -pedantic -g -Wall -Wno-unused-variable -c

Serial_Comms_Test: Serial_Comms_Test.o XBee_3_Pro_Functions.o AT_Command_Functions.o
	$(CC) $(CFLAG) Serial_Comms_Test.o XBee_3_Pro_Functions.o AT_Command_Functions.o -o Serial_Comms_Test -l wiringPi

Serial_Comms_Test.o: Serial_Comms_Test.c Serial_Comms.h
	$(CC) $(CFLAGSO) Serial_Comms_Test.c

XBee_3_Pro_Functions.o: XBee_3_Pro_Functions.c  Serial_Comms.h
	$(CC) $(CFLAGSO) XBee_3_Pro_Functions.c

AT_Command_Functions.o: AT_Command_Functions.c Serial_Comms.h
	$(CC) $(CFLAGSO) AT_Command_Functions.c

clean:
	rm -f *.o
	rm -f Serial_Comms_Test

run:
	clear
	sudo ./Serial_Comms_Test

all: clean Serial_Comms_Test