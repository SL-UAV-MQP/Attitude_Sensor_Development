#ifndef RFFE_h
#define RFFE_h

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

#endif