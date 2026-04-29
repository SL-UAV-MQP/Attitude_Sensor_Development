#include "Serial_Comms.h"


int8_t Escalate_UART_Baud_Rate(const unsigned int Final_Baud_Rate_Sel)
{
    puts("\nNegotieating Baud Rate...");
    uint8_t Attempt_Counter = 0;
    int UART_Open_Default_Status = serialOpen(Serial_Port, DEFAULT_BAUD);
    if(UART_Open_Default_Status > 0)
    {
        int XBee_Temp_fd = UART_Open_Default_Status;
        int8_t Command_Mode_Status = Enter_AT_Command_Mode(XBee_Temp_fd);
        if(Command_Mode_Status > 0)
        {
            int8_t Baud_Rate_Status = 0;
            do{
                Baud_Rate_Status = Set_Baud_Rate(XBee_Temp_fd, Final_Baud_Rate_Sel);
                if(Baud_Rate_Status > 0)
                {
                    switch(Final_Baud_Rate_Sel)
                    {
                        case BAUD_1200:
                        {
                            puts("Baud Rate Escelated To 1200 Baud.");
                            break;
                        }
                        case BAUD_2400:
                        {
                            puts("Baud Rate Escelated To 2400 Baud.");
                            break;
                        }
                        case BAUD_4800:
                        {
                            puts("Baud Rate Escelated To 4800 Baud.");
                            break;
                        }
                        case BAUD_9600:
                        {
                            puts("Baud Rate Escelated To 9600 Baud.");
                            break;
                        }
                        case BAUD_19200:
                        {
                            puts("Baud Rate Escelated To 19200 Baud.");
                            break;
                        }
                        case BAUD_38400:
                        {
                            puts("Baud Rate Escelated To 38400 Baud.");
                            break;
                        }
                        case BAUD_57600:
                        {
                            puts("Baud Rate Escelated To 57600 Baud.");
                            break;
                        }
                        case BAUD_115200:
                        {
                            puts("Baud Rate Escelated To 115200 Baud.");
                            break;
                        }
                        case BAUD_230400:
                        {
                            puts("Baud Rate Escelated To 230400 Baud.");
                            break;
                        }
                        case BAUD_460800:
                        {
                            puts("Baud Rate Escelated To 460800 Baud");
                            break;
                        }
                        case BAUD_921600:
                        {
                            puts("Baud Rate Escelated To 921600 Baud.");
                            break;
                        }
                    }
                    printf("Applying Baude Rate Change and Closing Connection %i.\n", XBee_Temp_fd);
                    printf("%s\n", "ATCN\r");
                    serialPuts(XBee_Temp_fd, "ATCN\r");

                    sleep(1);

                    serialClose (XBee_Temp_fd);
                    puts("Connection Closed");

                    return(1);
                }
                else
                {
                    puts("Failed To Set Baud Rate.");
                }
            Attempt_Counter++;
            } while((Baud_Rate_Status < 0) && (Attempt_Counter < 10));
        }
        else
        {
            puts("[ERROR] Failed To Enter AT Command Mode.");
            return(-1);
        }
    }
    else if(UART_Open_Default_Status == -1)
    {
        puts("[ERROR] UART Failed To Open At Defualt Baud Rate.");
        return(-1);
    }
    else if(UART_Open_Default_Status == -2)
    {
        puts("[ERROR] Bad Default Baud Rate Request.\nValid Baud Rate is 9600 Baud\n");
        return(-1);
    }
    puts("[ERROR] UART Port Setup Encountered Unrecodnized Error State.");
    return(-3);
}


int8_t UART_Port_Setup(int * const XBEE_fd)
{

    printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, PRIME_BAUD_RATE_INIT);
    int XBee_3_Reset_Address = serialOpen(Serial_Port, PRIME_BAUD_RATE_INIT);
    int8_t Command_Mode_Enter_Status = Enter_AT_Command_Mode(XBee_3_Reset_Address);
    if(Command_Mode_Enter_Status > 0)
    {
        puts("Resetting XBee Software.");
        int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
    }

    uint8_t Attempts = 0;
    while(Command_Mode_Enter_Status < 1)
    {
        puts("Connection Attempt Failed.");
        Attempts++;
        switch(Attempts)
        {
            case 1:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, PRIME_BAUD_RATE_INIT);
                XBee_3_Reset_Address = serialOpen(Serial_Port, PRIME_BAUD_RATE_INIT);
                Command_Mode_Enter_Status = Enter_AT_Command_Mode(XBee_3_Reset_Address);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 2:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, SECONDARY_BAUD_RATE_INIT);
                XBee_3_Reset_Address = serialOpen(Serial_Port, SECONDARY_BAUD_RATE_INIT);
                Command_Mode_Enter_Status = Enter_AT_Command_Mode(XBee_3_Reset_Address);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 3:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 921600);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 921600);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 4:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 460800);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 460800);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 5:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 230400);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 230400);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 6:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 115200);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 115200);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 7:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 57600);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 57600);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 8:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 38400);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 38400);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 9:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 19200);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 19200);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 10:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 9600);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 9600);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 11:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 4800);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 4800);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 12:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 2400);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 2400);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            case 13:
            {
                printf("\nAttempting UART Connection to %s at %i Baud...\n", Serial_Port, 1200);
                XBee_3_Reset_Address = serialOpen(Serial_Port, 1200);
                if(Command_Mode_Enter_Status > 0)
                {
                    puts("Resetting XBee Software.");
                    int8_t XBee_Reset_Status = XBee_3_Software_Reset(XBee_3_Reset_Address);
                }
                break;
            }
            default:
            {
                puts("[ERROR] UART Port Failed To Establish At Any Standardized Baud Rate.");
                return(-1);
            }
        }
    }

    sleep(3);

    system("clear");

    int8_t Primary_Escalation_Status = Escalate_UART_Baud_Rate(PRIME_BAUD_RATE_SEL_INIT);
    printf("\nOpening UART Connection to %s at Preferred Rate: %i Baud...\n", Serial_Port, PRIME_BAUD_RATE_INIT);
    int UART_Open_Prime_Status = serialOpen(Serial_Port, PRIME_BAUD_RATE_INIT);
    if(UART_Open_Prime_Status > 0)
    {
        *XBEE_fd = UART_Open_Prime_Status;
        return(1);
    }
    else if(UART_Open_Prime_Status == -1)
    {
        puts("UART Failed To Open At Preferred Baud Rate.");

        int8_t Secondary_Escalation_Status = Escalate_UART_Baud_Rate(SECONDARY_BAUD_RATE_SEL_INIT);
        printf("\nOpening UART Connection to %s at Backup Rate: %i Baud...\n", Serial_Port, SECONDARY_BAUD_RATE_INIT);
        int UART_Open_Second_Status = serialOpen (Serial_Port, SECONDARY_BAUD_RATE_INIT);
        if(UART_Open_Second_Status > 0)
        {
            *XBEE_fd = UART_Open_Second_Status;
            return(2);
        }
        else if(UART_Open_Prime_Status == -1)
        {
            puts("UART Failed To Open At Backup Baud Rate.");
            return(-1);
        }
        else if(UART_Open_Prime_Status == -2)
        {
            puts("Bad Baud Rate Request.\nValid Baud Rates Are As Follows:\n  - 1200\n - 2400\n - 4800\n - 9600\n - 19200\n - 38400\n - 57600\n - 115200\n - 230400\n - 460800\n - 921600\n");
            return(-1);
        }
        else
        {
            puts("UART port setup encountered unrecodnized error state.");
            return(-3);
        }

    }
    else if(UART_Open_Prime_Status == -2)
    {
        puts("Bad Baud Rate Request.\nValid Baud Rates are as follows:\n  - 1200\n - 2400\n - 4800\n - 9600\n - 19200\n - 38400\n - 57600\n - 115200\n - 230400\n - 460800\n - 921600\n");
        return(-1);
    }
    else
    {
        puts("UART port setup encountered unrecodnized error state.");
        return(-3);
    }
}

int8_t Init_XBee(int * const XBEE_fd)
{
    int8_t UART_Port_Setup_Status = UART_Port_Setup(XBEE_fd);

    if(UART_Port_Setup_Status > 0)
    {
        puts("XBee Address Checks [GOOD]");

        serialFlush(*XBEE_fd);

        int8_t Command_Mode_Enter_Status = Enter_AT_Command_Mode(*XBEE_fd);
        uint64_t SN_Upper = SERIAL_HIGH;
        uint64_t SN_Lower = SERIAL_LOW; 

        int8_t Serial_Upper_Status = 0;
        int8_t Serial_Lower_Status = 0;



        if(SN_Upper < 1)
        {
            
            Serial_Upper_Status = Get_Parameter_Value(*XBEE_fd, ((uint64_t *)&SN_Upper), SN_HIGH);
        }
        if(SN_Upper < 1)
        {
            
            Serial_Lower_Status = Get_Parameter_Value(*XBEE_fd, ((uint64_t *)&SN_Lower), SN_LOW);
        }
        
        if( (Serial_Upper_Status > -1) && (Serial_Lower_Status > -1))
        {
            printf("\nSN: %lX - %lX\n\n",  SN_Upper, SN_Lower);
        }

        sleep(2);
        if(Command_Mode_Enter_Status > 0)
        {   
            int8_t Command_Timeout_Status = Change_Arbitrary_Setting(*XBEE_fd, COMMAND_MODE_TIMEOUT, COMMAND_MODE_TIMEOUT_INIT, CT_MAX);
            if(Command_Timeout_Status > 0)
            {
                puts("Command Mode Timeout Set Checks [GOOD]\n");
            }
            else
            {
                puts("Command Mode Timeout Set Checks [BAD]\n");
            }

            
            int8_t Guard_Time_Status = Change_Arbitrary_Setting(*XBEE_fd, GUARD_TIME, COMMAND_GUARD_TIME_INIT, GT_MAX);
            if(Guard_Time_Status > 0)
            {
                puts("Guard Time Set Checks [GOOD]\n");
            }
            else
            {
                puts("Guard Time Set Checks [BAD]\n");
            }

                //No parity is set by serialOpen
            int8_t Parity_Bit_Status = Change_Arbitrary_Setting(*XBEE_fd, SERIAL_PARITY, COMMAND_PARITY_INIT, NB_MAX);
            if(Parity_Bit_Status > 0)
            {
                puts("Parity Bit Mode Set Checks [GOOD]\n");
            }
            else
            {
                puts("Parity Bit Mode Set Checks [BAD]\n");
            }

                //single stop bit set by serialOpen
            int8_t Stop_Bit_Status = Change_Arbitrary_Setting(*XBEE_fd, STOP_BITS, COMMAND_STOP_BIT_INIT, SB_MAX);
            if(Stop_Bit_Status > 0)
            {
                puts("Stop Bit Count Set Checks [GOOD]\n");
            }
            else
            {
                puts("Stop Bit Count Set Checks [BAD]\n");
            }

            int8_t CTS_Status = Change_Arbitrary_Setting(*XBEE_fd, DIO7_CONFIG, FLOW_CONTROL_CTS_INIT, D7_MAX);
            if(CTS_Status > 0)
            {
                puts("CTS Enable Set Checks [GOOD]\n");
            }
            else
            {
                puts("CTS Enable Set Checks [BAD]\n");
            }

            int8_t RTS_Status = Change_Arbitrary_Setting(*XBEE_fd, DIO6_CONFIG, FLOW_CONTROL_RTS_INIT, D6_MAX);
            if(RTS_Status > 0)
            {
                puts("RTS Enable Set Checks [GOOD]\n");
            }
            else
            {
                puts("RTS Enable Set Checks [BAD]\n");
            }

            int8_t AT_Mode_Status = Change_Arbitrary_Setting(*XBEE_fd, API_ENABLE, TRANPARENT_SERIAL_TERMINAL_MODE_INIT, AP_MAX);
            if(AT_Mode_Status > 0)
            {
                puts("Transparent Serial Mode Set Checks [GOOD]\n");
            }
            else
            {
                puts("Transparent Serial Mode Set Checks [BAD]\n");
            }

            int8_t EPAN_Status = Change_Arbitrary_Setting(*XBEE_fd, PAN_ID_EXPANDED, PAN_ID_EXTENDED_INIT, ID_MAX);
            if(EPAN_Status > 0)
            {
                puts("Extended PAN ID Set Checks [GOOD]\n");
            }
            else
            {
                puts("Extended PAN ID Set Checks [BAD]\n");
            }

            int8_t Channel_Scan_Status = Change_Arbitrary_Setting(*XBEE_fd, CHANNELS_TO_SCAN, ZIGBEE_RF_CHANNEL_BIT_MAP_INIT, SC_MAX);
            if(Channel_Scan_Status > 0)
            {
                puts("Channel Scan Bitmap Set Checks [GOOD]\n");
            }
            else
            {
                puts("Channel Scan Bitmap Set Checks [BAD]\n");
            }

            int8_t Channel_Scan_Durration_Status = Change_Arbitrary_Setting(*XBEE_fd, SCAN_DURATION, ZIGBEE_RF_CHANNEL_SCAN_DURATION_INIT, SD_MAX);
            if(RTS_Status > 0)
            {
                puts("Channel Scanning Duration Set Checks [GOOD]\n");
            }
            else
            {
                puts("Channel Scanning Duration Set Checks [BAD]\n");
            }

            int8_t USB_DONGLE_SERIAL_HIGH_Status = Change_Arbitrary_Setting(*XBEE_fd, DEST_ADDR_HIGH, USB_DONGLE_DH_INIT, DH_MAX);
            if(USB_DONGLE_SERIAL_HIGH_Status > 0)
            {
                puts("Destination Serial High Address Set Checks [GOOD]\n");
            }
            else
            {
                puts("Destination Serial High Address Set Checks [BAD]\n");
            }

            int8_t USB_DONGLE_SERIAL_LOW_Status = Change_Arbitrary_Setting(*XBEE_fd, DEST_ADDR_LOW, USB_DONGLE_DL_INIT, DL_MAX);
            if(USB_DONGLE_SERIAL_LOW_Status > 0)
            {
                puts("Destination Serial Low Address Set Checks [GOOD]\n");
            }
            else
            {
                puts("Destination Serial Low Address Set Checks [BAD]\n");
            }

            int8_t Join_Notif_Status = Change_Arbitrary_Setting(*XBEE_fd, JOIN_NOTIF, JOIN_NOTIFICATION_INIT, JN_MAX);
            if(RTS_Status > 0)
            {
                puts("RTS Mode Set Checks [GOOD]\n");
            }
            else
            {
                puts("RTS Mode Set Checks [BAD]\n");
            }

            int8_t Coordinator_Status = Change_Arbitrary_Setting(*XBEE_fd, NETWORK_COORDINATOR, ENDPOINT_STATUS_INIT, CE_MAX);
            if(RTS_Status > 0)
            {
                puts("End Point Designation Checks [GOOD]\n");
            }
            else
            {
                puts("End Point Designation Checks [BAD]\n");
            }

            sleep(2);

            serialFlush (*XBEE_fd);

            sleep(2);

            int8_t Exit_AT_Command_Mode_Status = Exit_AT_Command_Mode(*XBEE_fd);
            int8_t Init_Status = Command_Mode_Enter_Status + Command_Timeout_Status + Guard_Time_Status + Parity_Bit_Status + Stop_Bit_Status + CTS_Status + RTS_Status;
            return(Init_Status);
        }
        else
        {
            puts("Failed To Enter AT Command Mode\n");
            return(-7);
        }
    }
    else
    {
        puts("XBee Address Checks [GOOD]");
        return(-1);
    }
}