#include "I2C_Test.h"

    //Altitude sensor functions

    //Purpose: Reset the Altimeter state and query the PROM for the Factory code, 6 calibration values, and the CRC
    //Ingests the following values:
    //ALT: const signed integer, File handle to the altimiter I2C address
    //Altimeter_Calibration_Data: const pointer to a ALT_CAL struct, storage location of the altimeter calibration data
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return on Fail: -1
    //App Notes: Make sure to pass an ALT_CAL pointer and not a ALT_OUT pointer
int8_t Init_ALT(const int ALT, struct ALT_CAL * const Altimeter_Calibration_Data)
{
    puts("\nConfigureing Altimeter Control Registers...\n");

    int8_t Reset_Status = DirI2CWrite_CMD_BYTE(ALT, RESET);
    if(Reset_Status < 0)
    {
        puts("Altimeter Reset Failed.");
        return(-1);
    }

    puts("\nRebooting Altimeter...");
    
        //DO NOT SHORTEN WILL FAIL OTHERWISE
    uint16_t Reboot_Reg = 0x00;
    while(1)
    {
        int8_t Reboot_Status = DirI2CRead_LE_Reg_16(ALT, FACTORY_PROM_READ, &Reboot_Reg);
        printf("Booting Status: %X\n", Reboot_Reg);
        if((Reboot_Reg > 0) && (Reboot_Status > 0))
        {
            puts("Altimeter Reboot Checks [GOOD]");
            break;
        }
        usleep(1000);
    }

    if(Reset_Status == 1)
    {
        puts("\nReading Altimeter Factory Data...");
        int8_t Prom_Read_Status = DirI2CRead_LE_Reg_16(ALT, FACTORY_PROM_READ, &(Altimeter_Calibration_Data->FACTORY_DATA));
        if(Prom_Read_Status == 2)
        {
            puts("ALT Factory Bytes Read Checks [GOOD]");
        }
        else
        {
            puts("ALT Factory Bytes Read Checks [BAD]");
            printf("Read [%i] Bytes, Expected [%i] Bytes\n\n", Prom_Read_Status, 2);
        }   
        if(DEBUG == 1)
        {
            printf("Factory Data: %i\n\n", (Altimeter_Calibration_Data->FACTORY_DATA));
        }

        int8_t T1_Sense_Read_Status = DirI2CRead_LE_Reg_16(ALT, C1_PROM_READ, &(Altimeter_Calibration_Data->T1_SENS));
        if(T1_Sense_Read_Status == 2)
        {
            puts("ALT T1 Sense Bytes Read Checks [GOOD]");
        }
        else
        {
            puts("ALT T1 Sense Bytes Read Checks [BAD]");
            printf("Read [%i] Bytes, Expected [%i] Bytes\n\n", T1_Sense_Read_Status, 2);
        }   
        if(DEBUG == 1)
        {
            printf("Pressure sensitivity: %i\n\n", (Altimeter_Calibration_Data->T1_SENS));
        }

        int8_t T1_OFF_Read_Status = DirI2CRead_LE_Reg_16(ALT, C2_PROM_READ, &(Altimeter_Calibration_Data->T1_OFF));
        if(T1_OFF_Read_Status == 2)
        {
            puts("ALT T1 OFF Bytes Read Checks [GOOD]");
        }
        else
        {
            puts("ALT T1 OFF Bytes Read Checks [BAD]");
            printf("Read [%i] Bytes, Expected [%i] Bytes\n\n", T1_OFF_Read_Status, 2);
        }   
        if(DEBUG == 1)
        {
            printf("Pressure offset: %i\n\n", (Altimeter_Calibration_Data->T1_OFF));
        }

        int8_t TCS_Read_Status = DirI2CRead_LE_Reg_16(ALT, C3_PROM_READ, &(Altimeter_Calibration_Data->TCS));
        if(TCS_Read_Status == 2)
        {
            puts("ALT TCS Bytes Read Checks [GOOD]");
        }
        else
        {
            puts("ALT TCS Bytes Read Checks [BAD]");
            printf("Read [%i] Bytes, Expected [%i] Bytes\n\n", TCS_Read_Status, 2);
        }
        if(DEBUG == 1)
        {
            printf("Temperature coefficient of pressure sensitivity: %i\n\n", (Altimeter_Calibration_Data->TCS));
        }

        int8_t TCO_Read_Status = DirI2CRead_LE_Reg_16(ALT, C4_PROM_READ, &(Altimeter_Calibration_Data->TCO));
        if(TCO_Read_Status == 2)
        {
            puts("ALT TCO Bytes Read Checks [GOOD]");
        }
        else
        {
            puts("ALT TCO Bytes Read Checks [BAD]");
            printf("Read [%i] Bytes, Expected [%i] Bytes\n\n", TCO_Read_Status, 2);
        }
        if(DEBUG == 1)
        {
            printf("Temperature coefficient of pressure offset: %i\n\n", (Altimeter_Calibration_Data->TCO));
        }

        int8_t TREFF_Read_Status = DirI2CRead_LE_Reg_16(ALT, C5_PROM_READ, &(Altimeter_Calibration_Data->TREFF));
        if(TREFF_Read_Status == 2)
        {
            puts("ALT TR REFF Bytes Read Checks [GOOD]");
        }
        else
        {
            puts("ALT TR REFF Bytes Read Checks [BAD]");
            printf("Read [%i] Bytes, Expected [%i] Bytes\n\n", TREFF_Read_Status, 2);
        }
        if(DEBUG == 1)
        {
            printf("Reference temperature: %i\n\n", (Altimeter_Calibration_Data->TREFF));
        }

        int8_t TEMPSENS_Read_Status = DirI2CRead_LE_Reg_16(ALT, C6_PROM_READ, &(Altimeter_Calibration_Data->TEMPSENS));
        if(TEMPSENS_Read_Status == 2)
        {
            puts("ALT TEMP SENSE Bytes Read Checks [GOOD]");
        }
        else
        {
            puts("ALT TEMP SENSE Bytes Read Checks [BAD]");
            printf("Read [%i] Bytes, Expected [%i] Bytes\n\n", TEMPSENS_Read_Status, 2);
        }
        if(DEBUG == 1)
        {
            printf("Temperature coefficient of the temperature: %i\n\n", (Altimeter_Calibration_Data->TEMPSENS));
        }

        int8_t SERIAL_CRC_Read_Status = DirI2CRead_LE_Reg_16(ALT, SERIAL_PROM_READ, &(Altimeter_Calibration_Data->SERIAL_AND_CRC));
        if(SERIAL_CRC_Read_Status == 2)
        {
            puts("ALT CRC Bytes Read Checks [GOOD]");
        }
        else
        {
            puts("ALT CRC Bytes Read Checks [BAD]");
            printf("Read [%i] Bytes, Expected [%i] Bytes\n\n", SERIAL_CRC_Read_Status, 2);
        }
        if(DEBUG == 1)
        {
            printf("Serial Code and CRC: %X\n\n", (Altimeter_Calibration_Data->SERIAL_AND_CRC));
        }

        int8_t CRC_Status = CRC_4(Altimeter_Calibration_Data);

        if(CRC_Status < 0)
        {
            puts("Altimeter Factory Data Checks [BAD]");
            return(-1);
        }
        else
        {
            puts("Altimeter Factory Data Checks [GOOD]");
            puts("Altimeter Configuration Complete!");
            return(1);
        }
    }
    else
    {
        puts("Altimeter Reset Checks [BAD]");
        puts("Altimiter Factory Data Will Not Be Read.");
        return(-1);
    }
}

    //Purpose: Confirm that the Factory data is uncorrupted, does not do error correction
    //Ingests the following values:
    //Prom_Data: const pointer to a ALT_CAL structure, pointer to array where all altimiter calibration values is stored
    //Return Type: signed 8-bit integer
    //Retun on Sucess: 1
    //Return on Fail: -1
    //App Notes: Make sure to pass an ALT_CAL pointer and not a ALT_OUT pointer
int8_t CRC_4(struct ALT_CAL * const Prom_Data)
{
    uint16_t CRC_Sum; 
    uint16_t CRC_Remainder = 0x00; // crc reminder
    uint16_t CRC_Base = (Prom_Data->SERIAL_AND_CRC); // original value of the crc
    uint16_t Prom_Array[] = {(Prom_Data->FACTORY_DATA), (Prom_Data->T1_SENS), (Prom_Data->T1_OFF), (Prom_Data->TCS), (Prom_Data->TCO), (Prom_Data->TREFF), (Prom_Data->TEMPSENS), (Prom_Data->SERIAL_AND_CRC)};

    uint8_t  spindown_bit_counter;

    Prom_Array[7] = (0xFF00 & Prom_Array[7]); //CRC byte is replaced by 0
    for (uint16_t CRC_Sum = 0; CRC_Sum < 16; CRC_Sum++) // operation is performed on bytes
    { // choose LSB or MSB
        if (CRC_Sum % 2 == 1)
        {
            CRC_Remainder ^= (uint16_t)((Prom_Array[CRC_Sum >> 1]) & 0x00FF);
        }
        else 
        {
            CRC_Remainder ^= (uint16_t)(Prom_Array[CRC_Sum >> 1] >> 8);
        }
        for (spindown_bit_counter = 8; spindown_bit_counter > 0; spindown_bit_counter--)
        {
            if (CRC_Remainder & 0x8000)
            {
                CRC_Remainder = (CRC_Remainder << 1) ^ 0x3000;
            }
            else
            {
                CRC_Remainder = (CRC_Remainder << 1);
            }
        }
    }
    Prom_Array[7] = CRC_Base;
    CRC_Remainder = (0x000F & (CRC_Remainder >> 12)); // // final 4-bit reminder is CRC code
    
    if((CRC_Remainder ^ 0x00) == (CRC_Base & 0x000F))
    {
        if(DEBUG == 1)
        {
            printf("CRC Remainder: %X - CRC From PROM: %X\n", CRC_Remainder, CRC_Base);
        }
        return(1);
    }
    else
    {
        return(-1);
    }
}


    //Purpose: Get raw ADC pressure values from the altimiter at a specified OSR
    //Ingests the following values:
    //ALT: const signed integer, File handle to the altimiter I2C address
    //Pressure_OSR: const unsigned 16-bit integer, pressure oversampling rate, options in powers of 2 from 256 to 4096
    //Return Type: signed 32-bit integer
    //Return On Sucess: 24-bit (masked 32-bit signed) unsigned integer representing raw ADC pressure code
    //Return On Fail: -1
    //App Notes: Make sure to pass an Pressure OSR 256, 512, 1024, 2048 or 4096 and no other values
int32_t Get_Raw_Pressure(const int ALT, const uint16_t Pressure_OSR)
{
    int8_t Conversion_Start_Status = 0;
    uint8_t ADC_Pressure_Return[3] = {0};
    int8_t Bytes_Read = 0;

    switch(Pressure_OSR)
    {
        case TWO_e8:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D1_CONV_256);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("256 sample Pressure conversion starting...");
                }
                usleep(900);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start Pressure Conversion.");
            }
            break;
        }
        case TWO_e9:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D1_CONV_512);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("512 sample Pressure conversion starting...");
                }
                usleep(1400);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start Pressure Conversion.");
            }
            break;
        }
        case TWO_e10:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D1_CONV_1024);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("1024 sample Pressure conversion starting...");
                }
                usleep(2500);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start Pressure Conversion.");
            }
            break;
        }
        case TWO_e11:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D1_CONV_2048);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("2048 sample Pressure conversion starting...");
                }
                usleep(4700);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start Pressure Conversion.");
            }
            break;
        }
        case TWO_e12:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D1_CONV_4096);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("4096 sample Pressure conversion starting...");
                }
                usleep(9200);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start Pressure Conversion.");
            }
            break;
        }
        default:
        {
            puts("Invalid Pressure OSR Value Request.\nLimit OSR Value Requests to:\n - 256\n - 512\n - 1024\n - 2048\n - 4096\nConversion NOT initieated.");
            break;
        }
    }

    if(Conversion_Start_Status == 1)
    {
        Bytes_Read = DirI2CRead_Reg_Block8(ALT, ADC_READ, ADC_Pressure_Return, 3);

        if(Bytes_Read == -1)
        {
            puts("Read Operation Failed...");
        }
    }

    if(Bytes_Read > 0)
    {
        if(DEBUG == 1)
        {
            printf("Return: %X\n", BUFF_RECON_UI24(ADC_Pressure_Return[0], ADC_Pressure_Return[1], ADC_Pressure_Return[2]));
        }
        return(BUFF_RECON_UI24(ADC_Pressure_Return[0], ADC_Pressure_Return[1], ADC_Pressure_Return[2]));
    }
    else
    {
        return(-1);
    }
}

    //Purpose: Get raw ADC temperature values from the altimiter at a specified OSR
    //Ingests the following values:
    //ALT: const signed integer, File handle to the altimiter I2C address
    //Temperature_OSR: const unsigned 16-bit integer, temperature oversampling rate, options in powers of 2 from 256 to 4096
    //Return Type: signed 32-bit integer
    //Return On Sucess: 24-bit (masked 32-bit signed) unsigned integer representing raw ADC temperature code
    //Return On Fail: -1
    //App Notes: Make sure to pass an Pressure OSR 256, 512, 1024, 2048 or 4096 and no other values
int32_t Get_Raw_Temperature(const int ALT, const int Temperature_OSR)
{
    int8_t Conversion_Start_Status = 0;
    uint8_t ADC_Temp_Return[3] = {0};
    int8_t Bytes_Read = 0;

    switch(Temperature_OSR)
    {
        case TWO_e8:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D2_CONV_256);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("256 sample Temperature conversion starting...");
                }
                usleep(900);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start temperature Conversion.");
            }
            break;
        }
        case TWO_e9:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D2_CONV_512);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("512 sample Temperature conversion starting...");
                }
                usleep(1400);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start temperature Conversion.");
            }
            break;
        }
        case TWO_e10:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D2_CONV_1024);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("1024 sample Temperature conversion starting...");
                }
                usleep(2500);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start temperature Conversion.");
            }
            break;
        }
        case TWO_e11:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D2_CONV_2048);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("2048 sample Temperature conversion starting...");
                }
                usleep(4700);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start temperature Conversion.");
            }
            break;
        }
        case TWO_e12:
        {
            Conversion_Start_Status = DirI2CWrite_CMD_BYTE(ALT, D2_CONV_4096);
            if(Conversion_Start_Status == 1)
            {
                if(DEBUG == 1)
                {
                    puts("4096 sample Temperature conversion starting...");
                }
                usleep(9200);
            }
            if(Conversion_Start_Status == -1)
            {
                puts("Failed To Start temperature Conversion.");
            }
            break;
        }
        default:
        {
            puts("Invalid temperature OSR Value Request.\nLimit OSR Value Requests to:\n - 256\n - 512\n - 1024\n - 2048\n - 4096\nConversion NOT initieated.");
            break;
        }
    }

    if(Conversion_Start_Status == 1)
    {
        Bytes_Read = DirI2CRead_Reg_Block8(ALT, ADC_READ, ADC_Temp_Return, 3);

        if(Bytes_Read == -1)
        {
            puts("Read Operation Failed...");
        }
    }

    if(Bytes_Read > 0)
    {
        if(DEBUG == 1)
        {
            printf("Return: %X\n", BUFF_RECON_UI24(ADC_Temp_Return[0], ADC_Temp_Return[1], ADC_Temp_Return[2]));
        }
        return(BUFF_RECON_UI24(ADC_Temp_Return[0], ADC_Temp_Return[1], ADC_Temp_Return[2]));
    }
    else
    {
        return(-1);
    }
}

    //Purpose: Get real temperature value
    //Ingests the following values:
    //Raw_Temperature_Code: const unsigned 24-bit (masked 32-bit) integer, ADC code value for the temperature
    //Altimeter_Calibration_Data: const pointer to a ALT_CAL struct, storage location of the altimeter calibration data
    //Temp_Differential: const pointer to a signed 32-bit integer for storing the differential temp
    //Return Type: signed 32-bit integer
    //Return On Sucess: signed 32-bit integer representing true temperature
    //Return On Fail: no such thing... trust me bro
    //App Notes: Make sure to pass an ALT_CAL pointer and not a ALT_OUT pointer
    //App Notes: Passes the differential temprature out via pointer
int32_t Calculate_Temperature(const int32_t Raw_Temperature_Code, struct ALT_CAL * const Altimeter_Calibration_Data, int32_t * const Temp_Differential)
{
    //int32_t dT = 68;
    int32_t dT = Raw_Temperature_Code - ((Altimeter_Calibration_Data->TREFF)*TWO_e8);
    *Temp_Differential = dT;

    if(DEBUG == 1)
    {
        printf("Temperature Diff: %i\n", dT);
        printf("((%i*(%u))/%lu))\n", dT, (Altimeter_Calibration_Data->TEMPSENS), TWO_e23);
        printf("Real Temperature Shift: %li\n", ((dT*(Altimeter_Calibration_Data->TEMPSENS))/TWO_e23));
    }
    return(2000 + ((dT*(Altimeter_Calibration_Data->TEMPSENS))/TWO_e23));
}


    //Purpose: Get real pressure value
    //Ingests the following values:
    //Raw_Pressure_Code: const unsigned 24-bit (masked 32-bit) integer, ADC code value for the pressure
    //Altimeter_Calibration_Data: const pointer to a ALT_CAL struct, storage location of the altimeter calibration data
    //Temp_Differential: const signed 32-bit integer for storing the differential temp
    //Return Type: signed 32-bit integer
    //Return On Sucess: signed 32-bit integer representing true pressure
    //Return On Fail: no such thing... trust me bro
    //App Notes: Make sure to pass an ALT_CAL pointer and not a ALT_OUT pointer
int32_t Compensate_Pressure(const int32_t Raw_Pressure_Code, struct ALT_CAL * const Altimeter_Calibration_Data, const int32_t Temp_Differential)
{

    int64_t Pressure_Offset = ((Altimeter_Calibration_Data->T1_OFF)*TWO_e17)+(((double)(Altimeter_Calibration_Data->TCO)*Temp_Differential)/TWO_e6);

    if(DEBUG == 1)
    {
        printf("((%i)*(%li))+(((%i)*(%i))/%li)\n", (Altimeter_Calibration_Data->T1_OFF), TWO_e17, (Altimeter_Calibration_Data->TCO), Temp_Differential, TWO_e6);
    }

    int64_t Sensitivity = ((Altimeter_Calibration_Data->T1_SENS)*TWO_e16)+(((double)(Altimeter_Calibration_Data->TCS)*Temp_Differential)/TWO_e7);

    if(DEBUG == 1)
    {
        printf("((%i)*(%li))+(((%i)*(%i))/%li)\n", (Altimeter_Calibration_Data->T1_SENS), TWO_e16, (Altimeter_Calibration_Data->TCS), Temp_Differential, TWO_e7);
    }

    if(DEBUG == 1)
    {
        printf("Preasure Offset: %li\nSensitivity: %li\n", Pressure_Offset, Sensitivity);
    }

    if(DEBUG == 1)
    {
        printf("(((((%i)*(%li))/%li)-%li)/%li)\n", Raw_Pressure_Code, Sensitivity, TWO_e21, Pressure_Offset,TWO_e15);
    }

    return(((((Raw_Pressure_Code*Sensitivity)/TWO_e21)-Pressure_Offset)/TWO_e15));
}

//function: calculates altitude based on barometric pressure measurement and a starting height and pressure
//inputs: pressure and temperature readings from the device.
//outputs: modifies the MeasuredAltitude global variable
//Applicatio notes: h0, p0 and T0 should be set before flight/testing

void GetAltitude(struct ALT_OUT * const Altimeter_Out)
{
         //measured pressure in mbar. divide by 100 is because of the data being stored as a fixed point value
    float Last_Comp_Preasure = (float)(Altimeter_Out->Preasure)/100;
        //barometric formula solved for height. 29.25 is a pre-calculated ratio of constants.
    (Altimeter_Out->Altitude) = (float)(STARTING_HEIGHT_ABOVE_SEA_LEVEL_AT_GROUND +\
                                        (STARTING_TEMPRATURE_AT_GROUND/STD_LAPSE_RATE)*\
                                        (pow((STARTING_PREASURE_AT_GROUND/Last_Comp_Preasure),(STD_LAPSE_RATE*29.25))-1)\
                                       );
}


    //Purpose: Run all of the altimeter functions and display the real pressure and temperature values
    //Ingests the following values:
    //ALT: const signed integer, File handle to the altimiter I2C address
    //Altimeter_Calibration_Data: const pointer to a ALT_CAL struct, storage location of the altimeter calibration data
    //Altimeter_Out: const pointer to a ALT_OUT struct, storage location of the altimeter real pressure and temperature values
    //Return Type: Void
    //App Notes: Make sure to pass ALT_CAL and ALT_OUT pointers to the correct pararmeters, DO NOT FLIP
void Run_Altimeter(const int ALT, struct ALT_CAL * const Altimeter_Calibration_Data, struct ALT_OUT * const Altimeter_Out)
{
    int32_t Raw_Temperature = Get_Raw_Temperature(ALT, 512);
    int32_t Raw_Pressure = Get_Raw_Pressure(ALT, 512);
    //int32_t Raw_Temperature = 8077636;
    //int32_t Raw_Pressure = 6465444;
    
    if(DEBUG == 1)
    {
        printf("Raw Temperature: %u\nRaw Pressure: %u\n", Raw_Temperature, Raw_Pressure);
    }

    int32_t Temp_Diff = 0;

    (Altimeter_Out->Temperature) = ((float)Calculate_Temperature(Raw_Temperature ,Altimeter_Calibration_Data, &Temp_Diff));
    (Altimeter_Out->Preasure) = ((float)Compensate_Pressure(Raw_Pressure ,Altimeter_Calibration_Data, Temp_Diff));
    GetAltitude(Altimeter_Out);    
}