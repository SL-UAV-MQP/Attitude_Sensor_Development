#ifndef AC_GPIO
#define AC_GPIO

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>

#include "RFFE.h"
#include "XBee_3_Pro.h"
#include "LIS3MDL.h"
#include "LSM6DSO.h"
#include "MS5607_02BA03.h"

    //Set 0 for main running, 1 for Verbose Debug
#define DEBUG 0

#define Serial_Port "/dev/ttyAMA0"

    //This is the main perrifferial I2C bus that all the sensors are connected to
#define I2CBUS "/dev/i2c-1"

    //Data Manipulation
        //Masks data to the right most 8 bits
#define BYTE_MASK 0xFF
        //Masks data to right most 24 bits (for a uint24_t inside of a uint32_t)
#define UINT24_T 0xFFFFFF

    // Power of 2 constants, mostly used for fixed point math
#define TWO_e1 2UL
#define TWO_e2 4UL
#define TWO_e3 8UL
#define TWO_e4 16UL
#define TWO_e5 32UL
#define TWO_e6 64UL
#define TWO_e7 128UL
#define TWO_e8 256UL
#define TWO_e9 512UL
#define TWO_e10 1024UL
#define TWO_e11 2048UL
#define TWO_e12 4096UL
#define TWO_e13 8192UL
#define TWO_e14 16384UL
#define TWO_e15 32768UL
#define TWO_e16 65536UL
#define TWO_e17 131072UL
#define TWO_e18 262144UL
#define TWO_e19 524288UL
#define TWO_e20 1048576UL
#define TWO_e21 2097152UL
#define TWO_e22 4194304UL
#define TWO_e23 8388608UL
#define TWO_e24 16777216UL
#define TWO_e25 33554432UL

#define IMU_RAD_TO_DEG (180/3.141592653589793)


    //Combine 1 bytes into 1 unsined 8-bit integer (yes ik its functionaly useless, but it can be good for unifomity ig?)
#define BUFF_RECON_UI8(b0) (uint8_t)(((uint8_t)(b0)) & BYTE_MASK)

    //Combine 2 bytes into 1 unsined 16-bit integer
#define BUFF_RECON_UI16(b0, b1)                             \
    (                                                       \
        ((uint16_t)(((uint8_t)(b0)) & BYTE_MASK) <<  8) |   \
        ((uint16_t)(((uint8_t)(b1)) & BYTE_MASK))           \
    )

    //Combine 3 bytes into 1 unsined 32-bit integer masked to 24-bits
#define BUFF_RECON_UI24(b0, b1, b2)                             \
    (                                                           \
        (                                                       \
            ((uint32_t)(((uint8_t)(b0)) & BYTE_MASK) << 16) |   \
            ((uint32_t)(((uint8_t)(b1)) & BYTE_MASK)  <<  8) |  \
            ((uint32_t)(((uint8_t)(b2)) & BYTE_MASK))           \
        ) & (UINT24_T)                                          \
    )

    //Combine 4 bytes into 1 unsined 32-bit integer
#define BUFF_RECON_UI32(b0, b1, b2, b3)                     \
    (                                                       \
        ((uint32_t)(((uint8_t)(b0)) & BYTE_MASK) << 24) |   \
        ((uint32_t)(((uint8_t)(b1)) & BYTE_MASK) << 16) |   \
        ((uint32_t)(((uint8_t)(b2)) & BYTE_MASK) <<  8) |   \
        ((uint32_t)(((uint8_t)(b3)) & BYTE_MASK))           \
    )

    //Combine 8 bytes into 1 unsined 64-bit integer
#define BUFF_RECON_UI64(b0, b1, b2, b3, b4, b5, b6, b7)     \
    (                                                       \
        ((uint64_t)(((uint8_t)(b0)) & BYTE_MASK) << 56) |   \
        ((uint64_t)(((uint8_t)(b1)) & BYTE_MASK)  << 48) |  \
        ((uint64_t)(((uint8_t)(b2)) & BYTE_MASK) << 40) |   \
        ((uint64_t)(((uint8_t)(b3)) & BYTE_MASK) << 32) |   \
        ((uint64_t)(((uint8_t)(b4)) & BYTE_MASK) << 24) |   \
        ((uint64_t)(((uint8_t)(b5)) & BYTE_MASK) << 16) |   \
        ((uint64_t)(((uint8_t)(b6)) & BYTE_MASK) <<  8) |   \
        ((uint64_t)(((uint8_t)(b7)) & BYTE_MASK))           \
    )

    //Graphical
void Dash_Line(void);

    //GPIO Initilization
void I2C_GPIO_ADDR_Init(int * const, int * const, int * const);
void RFFE_Control_Init(void);

    //RF Switch Control Functions
void Control_RF_Switch_State(uint8_t, uint8_t, uint8_t);
void Antenna_Bank_1_Enable(void);
void Antenna_Bank_2_Enable(void);
void Match_720_750_Enable(void);
void Match_750_800_Enable(void);
void Match_800_900_Enable(void);
void Match_900_1400_Enable(void);
void Low_Amp_Enable(void);
void High_Amp_Enable(void);
int8_t Get_RFFE_State(struct RFFE_STATE * const);
void Interp_RFFE_State(struct RFFE_STATE * const);

   //XBee 3 Functions
int8_t Enable_CTSRTS(const int );
int8_t Disable_CTSRTS(const int );
int16_t Serial_Puts_CTSRTS_Safe(const int, const char *, uint8_t);
int8_t Init_XBee(int * const);
int8_t Escalate_UART_Baud_Rate(const unsigned int);
int8_t UART_Port_Setup(int * const);
void PrintTelemetry(int, uint64_t, struct timespec * const, struct timespec * const, struct ALT_OUT * const, struct ACC_OUT * const, struct GYRO_OUT * const, struct ROLLING_INERTIAL_SUMS * const, struct DownVector * const, struct NorthVector * const);

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

    //NON-SMBUSS I2C Read
int8_t DirI2CRead_Reg_8(const int, const uint8_t, uint8_t * const);
int8_t DirI2CRead_LE_Reg_16(const int, const uint8_t, uint16_t * const);
int8_t DirI2CWrite_Reg_Block8(const int, const uint8_t, uint8_t * const, const uint8_t);

    //NON-SMBUSS I2C Write
int8_t DirI2CWrite_CMD_BYTE(const int, const uint8_t);
int8_t DirI2CWrite_Reg_8(const int, const uint8_t, const uint8_t);
int8_t DirI2CRead_Reg_Block8(const int, const uint8_t, uint8_t * const, const uint8_t);

    //Sensors
    //Altimeter functions found in ALT_Functions.c
void Init_Attitude_Sensors(const int, const int, const int, struct GYRO_OUT * const, struct ACC_OUT * const, struct ALT_CAL * const, struct GYRO_CAL * const, struct ACC_CAL * const, struct MAG_OUT * const MAG_Out);
int8_t Init_ALT(const int, struct ALT_CAL * const);
int8_t CRC_4(struct ALT_CAL * const);
int32_t Get_Raw_Pressure(const int, const uint16_t);
int32_t Get_Raw_Temperature(const int, const int);
int32_t Calculate_Temperature(const int32_t, struct ALT_CAL * const, int32_t * const);
int32_t Compensate_Pressure(const int32_t, struct ALT_CAL * const, const int32_t);
void GetAltitude(struct ALT_OUT * const );
void Run_Altimeter(const int, struct ALT_CAL * const, struct ALT_OUT * const);

    //IMU functions found in IMU_Functions.c
int8_t Init_IMU(const int);
void Zeroize_IMU(const int, struct GYRO_OUT * const, struct ACC_OUT * const,struct GYRO_CAL * const, struct ACC_CAL * const);
int8_t Get_IMU_Raw_Temperature(const int, int16_t * const);
int8_t Get_Raw_X_Gyroscope(const int, int16_t * const );
int8_t Get_Raw_Y_Gyroscope(const int, int16_t * const );
int8_t Get_Raw_Z_Gyroscope(const int, int16_t * const );
int8_t Get_Raw_X_Linear_Acceleration(const int, int16_t * const);
int8_t Get_Raw_Y_Linear_Acceleration(const int, int16_t * const);
int8_t Get_Raw_Z_Linear_Acceleration(const int, int16_t * const);
int8_t Poll_Gyroscope(const int, struct GYRO_OUT * const, struct GYRO_CAL * const);
int8_t Poll_Accelerometer(const int, struct ACC_OUT * const, struct ACC_CAL * const);
void FindDown(struct ACC_OUT * const, struct DownVector * const);
void Run_IMU(const int, struct GYRO_OUT * const, struct ACC_OUT * const, struct GYRO_CAL * const, struct ACC_CAL * const, struct DownVector * const);
void INS_COMPUTE(struct timespec * const, struct timespec * const, struct ACC_OUT * const, struct GYRO_OUT * const, struct DownVector * const, struct ROLLING_INERTIAL_SUMS * const);

    //Magnetometer functions found in MAG_Functions.c
int8_t Init_MAG(const int);
void Run_MAG_Self_Test(const int, struct MAG_OUT * const);
int8_t Get_Raw_X_Magnetometer(const int, int16_t * const);
int8_t Get_Raw_Y_Magnetometer(const int, int16_t * const);
int8_t Get_Raw_Z_Magnetometer(const int, int16_t * const);
int8_t Poll_Magnetometer(const int, const uint8_t, struct MAG_OUT * const);
void FindNorth(struct MAG_OUT * const, struct DownVector * const, struct NorthVector * const);
void Run_MAG(const int, struct MAG_OUT * const, struct DownVector * const, struct NorthVector * const);

#endif