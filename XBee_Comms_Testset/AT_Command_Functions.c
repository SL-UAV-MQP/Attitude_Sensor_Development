#include "Serial_Comms.h"

int8_t Recive_Bytes_Blocking(const int XBEE_fd)
{
    uint8_t Bytes_Available = serialDataAvail(XBEE_fd);
    uint16_t Waiting_Timeout = 100;

    while(serialDataAvail(XBEE_fd) < 1)
    {
        usleep(25000);
        Bytes_Available = serialDataAvail(XBEE_fd);
        if(DEBUG == 1)
        {
            printf("Buffered Bytes: %u\n", Bytes_Available);
        }
        
        Waiting_Timeout--;
        if(Waiting_Timeout < 1)
        {
            puts("No Bytes Recived Before Timeout.");
            return(-1);
        }
    }
    return(Bytes_Available);
}

int8_t Get_Parameter_Value(const int XBEE_fd, uint64_t * Read_Value, const char * Setting_Code)
{
    char Check_String[6] = {0};
    snprintf(Check_String, sizeof(Check_String), "AT%s\r", Setting_Code);

    if(DEBUG == 1)
    {
        for(uint8_t cs =0; cs < sizeof(Check_String); cs++)
        {
            printf("CCS[%u]: %X\n", cs, Check_String[cs]);
        }
    }

    printf("%s\n", Check_String);
    serialPuts(XBEE_fd, Check_String);

    int8_t Bytes_Available = Recive_Bytes_Blocking(XBEE_fd);

    if(Bytes_Available > 0)
    {
        char *Parameter_Value = calloc((Bytes_Available), sizeof(char));
        char * End_Pointer = NULL;

        for(uint8_t pram_value = 0; pram_value < (Bytes_Available); pram_value++)
        {
            Parameter_Value[pram_value] = serialGetchar(XBEE_fd);
            if(DEBUG == 1)
            {
                printf("New Byte: %c\n", Parameter_Value[pram_value]);
            }
            if(Parameter_Value[pram_value] == 0x0D)
            {
                break;
            }
        }

        *Read_Value = ((uint64_t)strtol(Parameter_Value, &End_Pointer, 16));
        free(Parameter_Value);
        Parameter_Value = NULL;
        return(1);
    }
    else
    {
        puts("Byte Reception Timed Out.");
        return(-1);
    }
}

int8_t Check_Parameter_Set(const int XBEE_fd, const uint64_t Set_Value, uint64_t * New_Value, const char * Setting_Code)
{
    uint64_t Read_Value = 0;

    int8_t Get_Parameter_Status = Get_Parameter_Value(XBEE_fd, &Read_Value, Setting_Code);

    if(DEBUG == 1)
    {
        printf("Parameter Read As: %lX\n", Read_Value);
    }

    if(Set_Value == Read_Value)
    {
        if(DEBUG == 1)
        {
            puts("Parameter Set Checks [GOOD]");
        }
        *New_Value = Read_Value;
        Apply_Changes(XBEE_fd);
        return(1);
    }
    else
    {
        puts("Parameter Set Checks [BAD]");
        return(-1);
    }
}

int8_t Write_OK(const int XBEE_fd)
{
    int8_t Bytes_Available = Recive_Bytes_Blocking(XBEE_fd);

    if(Bytes_Available > 0)
    {
        char *IS_OK = calloc(Bytes_Available, sizeof(char));

        for(uint8_t bytes = 0; bytes < Bytes_Available; bytes++)
        {
            IS_OK[bytes] = serialGetchar(XBEE_fd);
            if(DEBUG == 1)
            {
                printf("New Byte Read: %c\n", IS_OK[bytes]);
            }
        }

        printf("%s\n", IS_OK);
        if(strcmp(IS_OK, "OK\r") == 0)
        {
            free(IS_OK);
            IS_OK = NULL;
            serialFlush(XBEE_fd);
            return(1);
        }
        else if(strcmp(IS_OK, "ERROR\r") == 0)
        {
            free(IS_OK);
            IS_OK = NULL;
            puts("XBee Did Not ACK");
            serialFlush(XBEE_fd);
            return(-1);
        }
        else
        {
            free(IS_OK);
            IS_OK = NULL;
            puts("UNEXPECTED RETURN VALUE DETECTED");
            serialFlush(XBEE_fd);
            return(0);
        }
    }
    else
    {
        puts("Confirmation Timed Out");
        serialFlush(XBEE_fd);
        return(-1);
    }
}


void Guard_Wait(void)
{
    usleep(DEFAULT_GUARD_TIME*1000);
}

int8_t Enter_AT_Command_Mode(const int XBEE_fd)
{
    char Enter_AT_Command[4] = {DEFAULT_COMMAND_CHAR, DEFAULT_COMMAND_CHAR, DEFAULT_COMMAND_CHAR, '\0'};
    
    Guard_Wait();
    printf("%s\n", Enter_AT_Command);
    serialPuts(XBEE_fd, Enter_AT_Command);
    Guard_Wait();
    
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(1);
    }
    else
    {
        return(-1);
    }
}

int8_t Exit_AT_Command_Mode(const int XBEE_fd)
{
    char Exit_At_Command[] = "ATCN\r";

    printf("%s\n", Exit_At_Command);
    serialPuts(XBEE_fd, Exit_At_Command);
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(1);
    }
    else
    {
        return(-1);
    }
}

int8_t Apply_Changes(const int XBEE_fd)
{
    puts("Attempting Change Application...");
    char Apply_Configureation_Changes[] = "ATAC\r";

    serialPuts(XBEE_fd, Apply_Configureation_Changes);

    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        puts("Changes Sucessfuly Applied");
        return(1);
    }
    else
    {
        puts("Changes Unsucessfuly Applied");
        return(-1);
    }
}

    //App Notes: Use Sparingly - 10,000 write cycles ever
int8_t Write_Changes(const int XBEE_fd)
{
    char Write_Configureation_Changes[] = "ATWR\r";

    serialPuts(XBEE_fd, Write_Configureation_Changes);

    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(1);
    }
    else
    {
        return(-1);
    }
}

int8_t XBee_3_Software_Reset(const int XBEE_fd)
{
    char Write_Configureation_Changes[] = "ATFR\r";

    serialPuts(XBEE_fd, Write_Configureation_Changes);

    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(1);
    }
    else
    {
        return(-1);
    }
}

int8_t Change_Arbitrary_Setting(const int XBEE_fd, const char * Setting_Code, uint64_t New_Parameter, uint8_t Max_Parameter_Size)
{
    uint64_t Byte_Mask = (~((uint64_t)0) >> ((16-Max_Parameter_Size)*4));
    New_Parameter = (New_Parameter & Byte_Mask);
    if(DEBUG == 1)
    {
        printf("Mask: %lX\n", Byte_Mask);
    }

    uint64_t New_Value = 0;

    char *Write_Command_String = calloc((Max_Parameter_Size+7), sizeof(char));

    if(DEBUG == 1)
    {
        printf("Write Command String Length: %u\n", (Max_Parameter_Size+7));
    }
    
    snprintf(Write_Command_String, (Max_Parameter_Size+7), "AT%s %0*lX\r", Setting_Code, Max_Parameter_Size, New_Parameter);

    
    if(DEBUG == 1)
    {
        for(uint8_t wcs =0; wcs < (Max_Parameter_Size+7); wcs++)
        {
            printf("WCS[%u]: %X\n", wcs, Write_Command_String[wcs]);
        }
        puts("");
    }

    printf("%s\n", Write_Command_String);
    serialPuts(XBEE_fd, Write_Command_String);
    free(Write_Command_String);
    Write_Command_String = NULL;
    
    int8_t Write_Status = 0;
    Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(Check_Parameter_Set(XBEE_fd, New_Parameter, &New_Value, Setting_Code)); 
    }
    else
    {
        return(-1);
    }
}



    //App notes: DOES NOT AUTO APPLY CHANGES!!! use CN to apply changes and close connection or clocking desync WILL Occur
int8_t Set_Baud_Rate(const int XBEE_fd, uint8_t Rate_Sel)
{
    Rate_Sel = (Rate_Sel & 0xFF);
    uint64_t New_Baud_Rate = 0x00;

    char Write_Command_String[9] = {0x00};
    
    snprintf(Write_Command_String, sizeof(Write_Command_String), "ATBD %1X\r", Rate_Sel);

    printf("%s\n", Write_Command_String);
    serialPuts(XBEE_fd, Write_Command_String);
    
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(Check_Parameter_Set(XBEE_fd, Rate_Sel, &New_Baud_Rate, BAUD_RATE));    
    }
    else
    {
        return(-1);
    }
}

/*
int8_t Set_Parity_Bit(const int XBEE_fd, uint8_t Even_Odd_Parity)
{
    Even_Odd_Parity = (Even_Odd_Parity & 0xFF);
    uint64_t New_Even_Odd_Parity = 0x00;

    char Write_Command_String[9] = {0x00};

    snprintf(Write_Command_String, sizeof(Write_Command_String), "ATNB %1X\r", Even_Odd_Parity);

    printf("%s\n", Write_Command_String);
    serialPuts(XBEE_fd, Write_Command_String);
    
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(Check_Parameter_Set(XBEE_fd, Even_Odd_Parity, &New_Even_Odd_Parity, SERIAL_PARITY));    
    }
    else
    {
        return(-1);
    }
}

int8_t Set_Stop_Bits(const int XBEE_fd, uint8_t Bit_Count)
{
    Bit_Count = (Bit_Count & 0xFF);
    uint64_t New_Bit_Count = 0x00;

    char Write_Command_String[9] = {0x00};

    snprintf(Write_Command_String, sizeof(Write_Command_String), "ATSB %1X\r", Bit_Count);

    printf("%s\n", Write_Command_String);
    serialPuts(XBEE_fd, Write_Command_String);
    
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(Check_Parameter_Set(XBEE_fd, Bit_Count, &New_Bit_Count, STOP_BITS));    
    }
    else
    {
        return(-1);
    }
}


int8_t CTS_Set(const int XBEE_fd, uint16_t CTS_Mode)
{
    CTS_Mode = (CTS_Mode & 0x0F);
    uint64_t New_CTS_Mode = 0x00;

    char Write_Command_String[8] = {0x00};

    snprintf(Write_Command_String, sizeof(Write_Command_String), "ATD7 %X\r", CTS_Mode);

    printf("%s\n", Write_Command_String);
    serialPuts(XBEE_fd, Write_Command_String);
    
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(Check_Parameter_Set(XBEE_fd, CTS_Mode, &New_CTS_Mode, DIO7_CONFIG));
    }
    else
    {
        return(-1);
    }
}

int8_t RTS_Set(const int XBEE_fd, uint16_t RTS_Mode)
{
    RTS_Mode = (RTS_Mode & 0x0F);
    uint64_t New_RTS_Mode = 0x00;

    char Write_Command_String[8] = {0x00};

    snprintf(Write_Command_String, sizeof(Write_Command_String), "ATD6 %X\r", RTS_Mode);

    printf("%s\n", Write_Command_String);
    serialPuts(XBEE_fd, Write_Command_String);
    
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(Check_Parameter_Set(XBEE_fd, RTS_Mode, &New_RTS_Mode, DIO6_CONFIG));
    }
    else
    {
        return(-1);
    }
}

int8_t Set_Command_Timeout(const int XBEE_fd, uint16_t Timeout)
{
    Timeout = (Timeout & 0xFFFF);
    uint64_t New_Timeout_Time = 0x0000;

    char Write_Command_String[11] = {0x00};

    snprintf(Write_Command_String, sizeof(Write_Command_String), "ATCT %04X\r", Timeout);

    printf("%s\n", Write_Command_String);
    serialPuts(XBEE_fd, Write_Command_String);
    
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(Check_Parameter_Set(XBEE_fd, Timeout, &New_Timeout_Time, COMMAND_MODE_TIMEOUT));
    }
    else
    {
        return(-1);
    }
}

int8_t Set_Guard_Time(const int XBEE_fd, uint16_t Guard_Time)
{
    Guard_Time = (Guard_Time & 0xFFF);
    uint64_t New_Guard_Time = 0x000;

    char Write_Command_String[10] = {0x00};

    snprintf(Write_Command_String, sizeof(Write_Command_String), "ATGT %03X\r", Guard_Time);

    printf("%s\n", Write_Command_String);
    serialPuts(XBEE_fd, Write_Command_String);
    
    int8_t Write_Status = Write_OK(XBEE_fd);
    if(Write_Status > 0)
    {
        return(Check_Parameter_Set(XBEE_fd, Guard_Time, &New_Guard_Time, GUARD_TIME));
    }
    else
    {
        return(-1);
    }
}
*/