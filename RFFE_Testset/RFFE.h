#ifndef RFFE_h
#define RFFE_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

    //Allows for GPIO control of the RFFE, noteably matching, lna, and antennas through the RF switches.
#include <wiringPi.h>

    //Set 0 for main running, 1 for DEBUG, 0 for Normal
#define DEBUG 1

#define SDA_DISP 2
#define SCL_DISP 3

#define PI_UART_TX 14
#define PI_UART_RX 15
#define PI_UART_CTS 16
#define PI_UART_RTS 17

#define ANT_SEL_P1_DISP 23
#define ANT_SEL_P2_DISP 22

#define MATCHING_SEL_A_P1_DISP 25
#define MATCHING_SEL_A_P2_DISP 9

#define MATCHING_SEL_B_P1_DISP 1
#define MATCHING_SEL_B_P2_DISP 0

#define LNA_SEL_A_P1_DISP 12
#define LNA_SEL_A_P2_DISP 6

#define LNA_SEL_B_P1_DISP 20
#define LNA_SEL_B_P2_DISP 26

#define RFSW_P1_Sel 0x01
#define RFSW_P2_Sel 0x02
#define RFSW_P3_Sel 0x03
#define RFSW_P4_Sel 0x00

struct RFFE_STATE
{
    uint8_t SW_1_Port_Sel;
    uint8_t SW_2_Port_Sel;
    uint8_t SW_3_Port_Sel;
    uint8_t SW_4_Port_Sel;
    uint8_t SW_5_Port_Sel;
};

    //GPIO Initilization
void GPIO_Init(void);
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
#endif