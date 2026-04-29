CC = gcc -std=gnu99
CFLAGS = -e c -pedantic -g -Wall -Wno-unused-variable
CFLAGSO = -e c -pedantic -g -Wall -Wno-unused-variable -c

ACG_Init_ONLY: ACG_Init_ONLY.o General_Functions.o RFFE_Functions.o XBee_3_Pro_Functions.o Attitude_Sensor_Functions.o ALT_Functions.o IMU_Functions.o MAG_Functions.o I2C_Functions.o AT_Command_Functions.o 
	$(CC) $(CFLAG) ACG_Init_ONLY.o General_Functions.o RFFE_Functions.o XBee_3_Pro_Functions.o Attitude_Sensor_Functions.o ALT_Functions.o IMU_Functions.o MAG_Functions.o I2C_Functions.o AT_Command_Functions.o -o ACG_Init_ONLY -lm -lwiringPi

ACG_Init_ONLY.o: ACG_Init_ONLY.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) ACG_Init_ONLY.c

Attitude_Comms_GPIO: Attitude_Comms_GPIO.o General_Functions.o RFFE_Functions.o XBee_3_Pro_Functions.o Attitude_Sensor_Functions.o ALT_Functions.o IMU_Functions.o MAG_Functions.o I2C_Functions.o AT_Command_Functions.o 
	$(CC) $(CFLAG) Attitude_Comms_GPIO.o General_Functions.o RFFE_Functions.o XBee_3_Pro_Functions.o Attitude_Sensor_Functions.o ALT_Functions.o IMU_Functions.o MAG_Functions.o I2C_Functions.o AT_Command_Functions.o -o Attitude_Comms_GPIO -lm -lwiringPi

Attitude_Comms_GPIO.o: Attitude_Comms_GPIO.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) Attitude_Comms_GPIO.c

General_Functions.o: General_Functions.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) General_Functions.c

RFFE_Functions.o: RFFE_Functions.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) RFFE_Functions.c

XBee_3_Pro_Functions.o: XBee_3_Pro_Functions.c  Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) XBee_3_Pro_Functions.c

Attitude_Sensor_Functions.o: Attitude_Sensor_Functions.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) Attitude_Sensor_Functions.c

ALT_Functions.o: ALT_Functions.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) ALT_Functions.c

IMU_Functions.o: IMU_Functions.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) IMU_Functions.c

MAG_Functions.o: MAG_Functions.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) MAG_Functions.c

AT_Command_Functions.o: AT_Command_Functions.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) AT_Command_Functions.c

I2C_Functions.o: I2C_Functions.c Attitude_Comms_GPIO.h
	$(CC) $(CFLAGSO) I2C_Functions.c

clean:
	rm -f *.o
	rm -f Attitude_Comms_GPIO
	rm -f ACG_Init_ONLY

run:
	clear
	sudo ./Attitude_Comms_GPIO

all: clean Attitude_Comms_GPIO

INIT: clean ACG_Init_ONLY

INIT_RUN: 
	clear
	sudo ./ACG_Init_ONLY
