#include "I2C_Test.h"

    //Generates a full terminal width dashed line with 2 carrage returns before and after.
    //For diviging up terminal responces for human readablity.
void Dash_Line(void)
{
    printf("\n\n");
    for(int i = 0; i < 80; i++)
    {
        printf("-");
    }
    printf("\n\n");
}

    //Purpose: reading one 8-bit byte from target I2C devices
    //Ingests the following values:
    //fd: const  signed 16-bit integer, address handel to the I2C device
    //Reg: const  unsigned 8-bit integer, Name of the target register (1 byte in Hex, likly a macro)
    //Data_8: const unsigned pointer, Points to a singular unsigned 8-bit integer 
    //Bytes: const unsigned 8-bit integer, Number of DATA bytes to be returned from the target
    //Return Type: signed 8-bit integer
    //Return on Sucess: the number of read bytes from the target register
    //Return on Fail: -1
    //App Notes: Functionaly a special case of 'DirI2CRead_Reg_Block8', just limited to one block
int8_t DirI2CRead_Reg_8(const int fd, const uint8_t Reg, uint8_t * const Data_8)
{
    const int8_t Write_Status = wiringPiI2CRawWrite(fd, &Reg, 1);
    const int8_t Read_Status = wiringPiI2CRawRead(fd, Data_8, 1);

    if((Write_Status > 0) && (Read_Status > 0))
    {
        if(DEBUG > 0)
        {
            printf("Reg: %X -> Byte 0: %X\n", Reg,  *Data_8);
        }
        return(Read_Status);
    }
    else
    {
        if(Write_Status < 1)
        {
            puts("[WARNING] Pre-Read Bad Write Detected.");
        }
        if(Read_Status < 1)
        {
            puts("[WARNING] Bad Read Detected.");
        }
        return(-1);
    }
}

    //Purpose: reading two 8-bit bytes from target I2C devices and convert them into a single 16-bit integer converted from Big Endian to Little Endian
    //Ingests the following values:
    //fd: const signed 16-bit integer, address handel to the I2C device
    //Reg: const unsigned 8-bit integer, Name of the target register (1 byte in Hex, likly a macro)
    //Data_8: const unsigned pointer, Points to a singular unsigned 16-bit integer 
    //Bytes: const unsigned 8-bit integer, Number of DATA bytes to be returned from the target
    //Return Type: signed 8-bit integer
    //Return on Sucess: the number of read bytes from the target register (should always be 2)
    //Return on Fail: -1
    //App Notes: none
int8_t DirI2CRead_LE_Reg_16(const int fd, const uint8_t Reg, uint16_t * const Data_16)
{
    uint8_t Payload[2];
    const int8_t Write_Status = wiringPiI2CRawWrite(fd, &Reg, 1);
    const int8_t Read_Status = wiringPiI2CRawRead(fd, Payload, 2);
    *Data_16 = BUFF_RECON_UI16(Payload[0], Payload[1]);
    
    if((Write_Status > 0) && (Read_Status > 0))
    {
        if(DEBUG > 0)
        {
            for(uint8_t bytes = 0; bytes < 2; bytes++)
            {
                printf("Reg: %X -> Byte %d: %X\n", Reg, bytes, Payload[bytes]);
            }
        }
        return(Read_Status);
    }
    else
    {
        if(Write_Status < 1)
        {
            puts("[WARNING] Bad Pre-Read Write Detected.");
        }
        if(Read_Status < 1)
        {
            puts("[WARNING] Bad Read Detected.");
        }
        return(-1);
    }
}

    //Purpose: reading one 8-bit byte from target I2C devices
    //Ingests the following values:
    //fd: const signed 16-bit integer, address handel to the I2C device
    //Reg: const unsigned 8-bit integer, Name of the target register (1 byte in Hex, likly a macro)
    //Data_8: const unsigned pointer, Points to array of unsigned 8-bit integer data to be read from the target register, MSb left, Lowest register Byte first (a[0] -> a[1] -> a[2] -> a[3]...a[n])
    //Bytes: const unsigned 8-bit integer, Number of DATA bytes to be returned from the target
    //Return Type: signed 8-bit integer
    //Return on Sucess: the number of read bytes from the target register
    //Return on Fail: -1
int8_t DirI2CRead_Reg_Block8(const int fd, const uint8_t Reg, uint8_t * const Data_8, const uint8_t Bytes)
{
    const int8_t Write_Status = wiringPiI2CRawWrite(fd, &Reg, 1);
    const int8_t Read_Status = wiringPiI2CRawRead(fd, Data_8, Bytes);

    if((Write_Status > 0) && (Read_Status > 0))
    {
        if(DEBUG > 0)
        {
            for(uint8_t bytes = 0; bytes < Bytes; bytes++)
            {
                printf("Reg: %X -> Byte %d: %X\n", Reg, bytes, Data_8[bytes]);
            }
        }
        return(Read_Status);
    }
    else
    {
        if(Write_Status < 1)
        {
            puts("[WARNING] Bad Pre-Read Write Detected.");
        }
        if(Read_Status < 1)
        {
            puts("[WARNING] Bad Read Detected.");
        }
        return(-1);
    }
}


    //Purpose: writing Command Bytes to target I2C devices with no individual target registers
    //Ingests the following values:
    //fd: const signed 16-bit integer, address handel to the I2C device
    //CMDByte: const unsigned 8-bit integer, command byte value (1 byte in Hex, likly a macro)
    //Return Type: signed 8-bit integer
    //Return on Sucess: # of Bytes writen to the target device (should always be 1)
    //Return on Fail: -1
    //App Notes: Use only on the Altimiter Modual
    //App Notes: When filling 'Data' do not use a pointer, DO use a macro.
int8_t DirI2CWrite_CMD_BYTE(const int fd, const uint8_t CMDByte)
{
        //Send the data
    const int8_t Write_Status = wiringPiI2CRawWrite(fd, &CMDByte, 1);
        //Return the sucess/failure value of the function
    if(Write_Status > 0)
    {
        return(Write_Status);
    }
    else
    {
        if(Write_Status < 1)
        {
            puts("[WARNING] Bad Write Detected.");
        }
        return(-1);
    }
}

    //Purpose: writing 8 bits of data to a 1 byte target register on a target I2C device
    //Ingests the following values:
    //fd: const signed 16-bit integer, address handel to the I2C device
    //Reg: const unsigned 8-bit integer, Name of the target register (1 byte in Hex, likly a macro)
    //Data: const unsigned 8-bit integer, data to be writen to the target register, MSb left
    //Return Type: signed 8-bit integer
    //Return on Sucess: # of Bytes writen to the target device (should always be 2)
    //Return on Fail: -1
    //App Notes: Use on I2C devices with 8 bit registers. Please only place 1 uin8_t into 'Data' 
    //App Notes: When filling 'Data' do not use a pointer, do not use a macro.
    //App Notes: If multiple bytes are required, use 'DirI2CWrite_Reg_Block8' or 'DirI2CWrite_Reg_16'.
    //App Notes: 'DirI2CWrite_Reg_16' not presently implemented for endianness stupidity reasons
int8_t DirI2CWrite_Reg_8(const int fd, const uint8_t Reg, const uint8_t Data)
{
        //Load the payload array with the regirster and then the data byte
    const uint8_t Payload[] = {Reg, Data};
    //printf("Payload Size: %li, b0: %X, b1: %X\n", sizeof(Payload),  Payload[0], Payload[1]);
        //Send the data
    const int8_t Write_Status = wiringPiI2CRawWrite(fd, Payload, sizeof(Payload));
        //Return the sucess/failure value of the function
    if(Write_Status > 0)
    {
        return(Write_Status);
    }
    else
    {
        if(Write_Status < 1)
        {
            puts("[WARNING] Bad Write Detected.");
        }
        return(-1);
    }
}

    //Purpose: writing n 8- bit bytes of data to a n byte target register on a target I2C device
    //Ingests the following values:
    //fd: const signed 16-bit integer, address handel to the I2C device
    //Reg: const unsigned 8-bit integer, Name of the target register (1 byte in Hex, likly a macro)
    //Data_8: const unsigned pointer, Points to array of unsigned 8-bit integer data to be writen to the target register, MSb left, Lowest register Byte first (a[0] -> a[1] -> a[2] -> a[3]...a[n])
    //Bytes: const unsigned 8-bit integer, Number of DATA bytes to be sent over the wire +1
    //Return Type: signed 8-bit integer
    //Return on Sucess: # of Bytes writen to the target device (should always be equal to 'Bytes')
    //Return on Fail: -1
    //App Notes: When filling 'Data' DO use a pointer, do not use a macro.
    //App Notes: If single bytes are required, use 'DirI2CWrite_Reg_8'.
int8_t DirI2CWrite_Reg_Block8(const int fd, const uint8_t Reg, uint8_t * const Data_8, const uint8_t Bytes)
{
        //Malloc varible size register for all the data + the register address
    uint8_t * Payload = (uint8_t*)malloc((Bytes+1) * sizeof(uint8_t));
        //Start payload with regrister address
    Payload[0] = Reg;
        //Loop through all of the data to be sent
    for(int bytes = 1; bytes <= Bytes; bytes++)
    {
        Payload[bytes] = Data_8[(bytes-1)];
    }
        //Send the data 
    const int8_t Write_Status = wiringPiI2CRawWrite(fd, Payload, sizeof(Payload));
        //Return the sucess/failure value of the function
    if(Write_Status > 0)
    {
        return(Write_Status);
    }
    else
    {
        if(Write_Status < 1)
        {
            puts("[WARNING] Bad Write Detected.");
        }
        return(-1);
    }
}


    //Purpose: Call functions to configure the I/O mode and PU/PD mode of the GPIO pins on the MCU, spesificaly those used to control RFFE Switchs. Also creates the I2C address handles for useage elsewhere.
    //Ingests the following values:
    //ALT: const pointer to a signed integer, Pointer to the I2C address handel of the altimiter
    //IMU: const pointer to a signed integer, Pointer to the I2C address handel of the IMU
    //MAG: const pointer to a signed integer, Pointer to the I2C address handel of the magnotometer
    //Return Type: (Void)
    //App Notes: Can only fail if setting the pin addressing type fails, this does not ensure that the individual pins were properly set as the set functions are of type void.
void I2C_GPIO_ADDR_Init(int * const ALT, int * const IMU, int * const MAG)
{
    puts("\nSetting Up GPIO Pin Names ...");
        //Set all of the pin reffrences to use the BCM pin numbering scheme
    int Pin_Enumerate_Init = wiringPiSetupPinType(WPI_PIN_BCM);

        //Run if the pin numbering assignment worked
    if(Pin_Enumerate_Init == 0)
    {
        puts("Pin Nameing Setup Checks [GOOD]");

        Dash_Line();

        puts("\nAddressing Sensors...");

            //Generate file address handles for the altimiter, IMU and magnetometer and change their values via pointer derefrence
        *ALT = wiringPiI2CSetup(ALT_ADDR);
        puts("ALT Address Setup Checks [GOOD]");
        *IMU = wiringPiI2CSetup(IMU_ADDR);
        puts("IMU Address Setup Checks [GOOD]");
        *MAG = wiringPiI2CSetup(MAG_ADDR);
        puts("MAG Address Setup Checks [GOOD]");

        puts("Sensors Addressed Sucessfuly!");

        Dash_Line();
    }
}
