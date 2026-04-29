#ifndef UART_h
#define UART_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "XBee_3_Pro.h"

#define DEBUG 0

#define Serial_Port "/dev/ttyAMA0"

    //XBee 3 Functions
int8_t Init_XBee(int * const);
int8_t Escalate_UART_Baud_Rate(const unsigned int);
int8_t UART_Port_Setup(int * const);


    //AT Command Mode
int8_t Recive_Bytes_Blocking(const int);
int8_t Write_OK(const int);
void Guard_Wait(void);
int8_t Get_Parameter_Value(const int, uint64_t *, const char *);
int8_t Check_Parameter_Set(const int, const uint64_t, uint64_t *, const char *);
int8_t Enter_AT_Command_Mode(const int);
int8_t Exit_AT_Command_Mode(const int);
int8_t Apply_Changes(const int);
int8_t Write_Changes(const int);
int8_t XBee_3_Software_Reset(const int);
int8_t Change_Arbitrary_Setting(const int, const char *, uint64_t, uint8_t);
int8_t Set_Baud_Rate(const int, uint8_t);

/*
int8_t Set_Parity_Bit(const int, uint8_t);
int8_t Set_Stop_Bits(const int, uint8_t);
int8_t CTS_Set(const int fd, uint16_t CTS_Mode);
int8_t RTS_Set(const int fd, uint16_t RTS_Mode);
int8_t Set_Flow_Control_Threshold(const int, uint16_t);
int8_t Set_Command_Timeout(const int, uint16_t);
int8_t Set_Guard_Time(const int, uint16_t);
*/


#endif