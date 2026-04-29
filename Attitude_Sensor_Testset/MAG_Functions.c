#include "I2C_Test.h"

    //Magnetometer Sensor functions

    //Purpose: Reset the Magnetometer state and set the internal configuration registers
    //Ingests the following values:
    //MAG: const signed integer, File handle to the Magnetometer I2C address
    //Return Type: signed 8-bit integer
    //Return on Sucess: 10 (total number of bytes writen for full config)
    //Return on Fail: Total number of missed bytes (negitive values from -10 to -1)
int8_t Init_MAG(const int MAG)
{
    puts("\nConfigureing Magnotometer Control Registers...\n");

    DirI2CWrite_Reg_8(MAG, CTRL_REG2, INIT_RST_LIS);
    usleep(5000);

    //puts("Configureing Magnotometer Control 1 Register...");
        //See LIS3MDL.h for configuration setting
    int8_t CTRL1_Write_Status = DirI2CWrite_Reg_8(MAG, CTRL_REG1, CTRL_REG1_INIT);
    uint8_t CTRL1_Read = 0;
    int8_t CTRL1_Read_Status = DirI2CRead_Reg_8(MAG, CTRL_REG1, &CTRL1_Read);
    if(CTRL1_Read == CTRL_REG1_INIT)
    {
        puts("Magnotometer Control 1 Register Checks [GOOD]");
    }
    else
    {
        puts("Magnotometer Control 1 Register Checks [BAD]");
        printf("Control Register 1 set to: %X, Expected: %X\n\n", CTRL1_Read, CTRL_REG1_INIT);
    }

    //puts("Configureing Magnotometer Control 2 Register...");
        //See LIS3MDL.h for configuration setting
    int8_t CTRL2_Write_Status = DirI2CWrite_Reg_8(MAG, CTRL_REG2, CTRL_REG2_INIT);
    uint8_t CTRL2_Read = 0;
    int8_t CTRL2_Read_Status = DirI2CRead_Reg_8(MAG, CTRL_REG2, &CTRL2_Read);
    if(CTRL2_Read == CTRL_REG2_INIT)
    {
        puts("Magnotometer Control 2 Register Checks [GOOD]");
    }
    else
    {
        puts("Magnotometer Control 2 Register Checks [BAD]");
        printf("Control Register 2 set to: %X, Expected: %X\n\n", CTRL2_Read, CTRL_REG2_INIT);
    }

    //puts("Configureing Magnotometer Control 3 Register...");
        //See LIS3MDL.h for configuration setting
    int8_t CTRL3_Write_Status = DirI2CWrite_Reg_8(MAG, CTRL_REG3, CTRL_REG3_INIT);
    uint8_t CTRL3_Read = 0;
    int8_t CTRL3_Read_Status = DirI2CRead_Reg_8(MAG, CTRL_REG3, &CTRL3_Read);
    if(CTRL3_Read == CTRL_REG3_INIT)
    {
        puts("Magnotometer Control 3 Register Checks [GOOD]");
    }
    else
    {
        puts("Magnotometer Control 3 Register Checks [BAD]");
        printf("Control Register 3 set to: %X, Expected: %X\n\n", CTRL3_Read, CTRL_REG3_INIT);
    }

    //puts("Configureing Magnotometer Control 4 Register...");
        //See LIS3MDL.h for configuration setting
    int8_t CTRL4_Write_Status = DirI2CWrite_Reg_8(MAG, CTRL_REG4, CTRL_REG4_INIT);
    uint8_t CTRL4_Read = 0;
    int8_t CTRL4_Read_Status = DirI2CRead_Reg_8(MAG, CTRL_REG4, &CTRL4_Read);
    if(CTRL4_Read == CTRL_REG4_INIT)
    {
        puts("Magnotometer Control 4 Register Checks [GOOD]");
    }
    else
    {
        puts("Magnotometer Control 4 Register Checks [BAD]");
        printf("Control Register 4 set to: %X, Expected: %X\n\n", CTRL4_Read, CTRL_REG4_INIT);
    }

    //puts("Configureing Magnotometer Control 5 Register...");
        //See LIS3MDL.h for configuration setting
    int8_t CTRL5_Write_Status = DirI2CWrite_Reg_8(MAG, CTRL_REG5, CTRL_REG5_INIT);
    uint8_t CTRL5_Read = 0;
    int8_t CTRL5_Read_Status = DirI2CRead_Reg_8(MAG, CTRL_REG5, &CTRL5_Read);
    if(CTRL5_Read == CTRL_REG5_INIT)
    {
        puts("Magnotometer Control 5 Register Checks [GOOD]");
    }
    else
    {
        puts("Magnotometer Control 5 Register Checks [BAD]");
        printf("Control Register 5 set to: %X, Expected: %X\n\n", CTRL5_Read, CTRL_REG5_INIT);
    }
    
    if((CTRL1_Write_Status+CTRL2_Write_Status+CTRL3_Write_Status+CTRL4_Write_Status+CTRL5_Write_Status) == 10)
    {
        puts("Magnotometer Configuration Complete!");
        return(10);
    }
    else
    {
        puts("Magnotometer Configuration Errors Occured.");
        return((CTRL1_Write_Status+CTRL2_Write_Status+CTRL3_Write_Status+CTRL4_Write_Status+CTRL5_Write_Status)-10);
    }
}

    //Purpose: Get raw Mag X axis Magnetometer values from the IMU
    //Ingests the following values:
    //MAG: const signed integer, File handle to the altimiter I2C address
    //Raw_X_MAG: const signed 16-bit integer pointer, pointer to raw X axis rotational value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw X axis magnetic field value 16-bit signed integer out if Sucess
int8_t Get_Raw_X_Magnetometer(const int MAG, int16_t * const Raw_X_MAG)
{
    uint8_t X_MAG_High = 0;
    int8_t X_MAG_High_Read_Status = DirI2CRead_Reg_8(MAG, OUT_X_H, &X_MAG_High);

    uint8_t X_MAG_Low = 0;
    int8_t X_MAG_Low_Read_Status = DirI2CRead_Reg_8(MAG, OUT_X_L, &X_MAG_Low);

    if((X_MAG_High_Read_Status < 0) || (X_MAG_Low_Read_Status < 0))
    {
        puts("MAG X Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_X_MAG = ((int16_t)BUFF_RECON_UI16(X_MAG_High, X_MAG_Low));
        return(1);
    }
}

    //Purpose: Get raw Mag Y axis Magnetometer values from the IMU
    //Ingests the following values:
    //MAG: const signed integer, File handle to the altimiter I2C address
    //Raw_Y_MAG: const signed 16-bit integer pointer, pointer to raw Y axis rotational value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw Y axis magnetic field value 16-bit signed integer out if Sucess
int8_t Get_Raw_Y_Magnetometer(const int MAG, int16_t * const Raw_Y_MAG)
{
    uint8_t Y_MAG_High = 0;
    int8_t Y_MAG_High_Read_Status = DirI2CRead_Reg_8(MAG, OUT_Y_H, &Y_MAG_High);
    
    uint8_t Y_MAG_Low = 0;
    int8_t Y_MAG_Low_Read_Status = DirI2CRead_Reg_8(MAG, OUT_Y_L, &Y_MAG_Low);

    if((Y_MAG_High_Read_Status < 0) || (Y_MAG_Low_Read_Status < 0))
    {
        puts("MAG Y Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_Y_MAG = ((int16_t)BUFF_RECON_UI16(Y_MAG_High, Y_MAG_Low));
        return(1);
    }
}

    //Purpose: Get raw Mag Z axis Magnetometer values from the IMU
    //Ingests the following values:
    //MAG: const signed integer, File handle to the altimiter I2C address
    //Raw_Z_MAG: const signed 16-bit integer pointer, pointer to raw Z axis rotational value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw Z axis magnetic field value 16-bit signed integer out if Sucess
int8_t Get_Raw_Z_Magnetometer(const int MAG, int16_t * const Raw_Z_MAG)
{
    uint8_t Z_MAG_High = 0;
    int8_t Z_MAG_High_Read_Status = DirI2CRead_Reg_8(MAG, OUT_Z_H, &Z_MAG_High);
    
    uint8_t Z_MAG_Low = 0;
    int8_t Z_MAG_Low_Read_Status = DirI2CRead_Reg_8(MAG, OUT_Z_L, &Z_MAG_Low);
    
    if((Z_MAG_High_Read_Status < 0) || (Z_MAG_Low_Read_Status < 0))
    {
        puts("MAG Z Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_Z_MAG = ((int16_t)BUFF_RECON_UI16(Z_MAG_High, Z_MAG_Low));
        return(1);
    }
}

    //Purpose: Check for when the Magnetometer, X Y and Z axis have new data, ingest that data, scale it and place it into the proper struct
    // //Ingests the following values:
    //MAG: const signed integer, File handle to the altimiter I2C address
    //MAG_Out: const pointer to a MAG_OUT structure, Pointer to array where all magnetometer  final output data will get stored
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: number of failed register reads (-1 to -3)
    //App Notes: none
int8_t Poll_Magnetometer(const int MAG, const uint8_t MAG_Status_Register, struct MAG_OUT * const MAG_Out)
{
    uint8_t Get_Success = 0;
    
    uint8_t New_Z = MAG_Status_Register & MAG_Z_NEW;
    uint8_t New_Y = MAG_Status_Register & MAG_Y_NEW;
    uint8_t New_X = MAG_Status_Register & MAG_X_NEW;

    if(DEBUG == 3)
    {
        //printf("New X: %i\nNew Y: %i\nNew Z %i\n", New_X, New_Y, New_Z);
    }
    

    uint8_t MAG_FSR_Check = 0x00;
    uint8_t MAG_FSR_Read_Status = DirI2CRead_Reg_8(MAG, CTRL_REG2, &MAG_FSR_Check);
    if(MAG_FSR_Read_Status > 0)
    {
        MAG_FSR_Check = (MAG_FSR_Check & FSR_MASK_LIS);
    }

    float MAG_FSR = 0;

    switch(MAG_FSR_Check)
    {
        case LIS_FS_00:
        {
            MAG_FSR = FS_4GA;
            break;
        }
        case LIS_FS_01:
        {
            MAG_FSR = FS_8GA;
            break;
        }
        case LIS_FS_10:
        {
            MAG_FSR = FS_12GA;
            break;
        }
        case LIS_FS_11:
        {
            MAG_FSR = FS_16GA;
            break;
        }
    }

    if(DEBUG == 3)
    {
        printf("Magnetometer FSR: %f\n", MAG_FSR);
    }

    int16_t Raw_X_MAG = 0;
    int16_t Raw_Y_MAG = 0;
    int16_t Raw_Z_MAG = 0;

    if(New_X > 0)
    {
        if(DEBUG == 3)
        {
            puts("\nGetting X Mag...");
        }
        if(Get_Raw_X_Magnetometer(MAG, &Raw_X_MAG) > 0)
        {
            Get_Success++;

            if(DEBUG == 3)
            {
                printf("Raw X Mag: %f\n", (float)Raw_X_MAG);
            }
        }
        (MAG_Out->X_Mag_Strength) = (((float)Raw_X_MAG) * MAG_FSR);
    }
    
    if(New_Y > 0)
    {
        if(DEBUG == 3)
        {
            puts("\nGetting Y Mag...");
        }
        if(Get_Raw_Y_Magnetometer(MAG, &Raw_Y_MAG) > 0)
        {
            Get_Success++;

            if(DEBUG == 3)
            {
                printf("Raw Y Mag: %f\n", (float)Raw_Y_MAG);
            }
        }
        (MAG_Out->Y_Mag_Strength) = (((float)Raw_Y_MAG) * MAG_FSR);
    }

    if(New_Z > 0)
    {
        if(DEBUG == 3)
        {
            puts("\nGetting Z Mag...");
        }
        if(Get_Raw_Z_Magnetometer(MAG, &Raw_Z_MAG) > 0)
        {
            Get_Success++;

            if(DEBUG == 3)
            {
                printf("Raw Z Mag: %f\n",(float)Raw_Z_MAG);
            }
        }
        (MAG_Out->Z_Mag_Strength) = (((float)Raw_Z_MAG) * MAG_FSR);
    }

    if(Get_Success == 3)
    {
        return(1);
    }
    else
    {
        return(Get_Success - 3);
    }
}

//purpose: determine geographic north
//inputs: pointers to the down vector struct, the magnetometer reading struct and the north vector struct
//does not technically have outptus but modifies the north vector struct via pointers
void FindNorth(struct MAG_OUT * const MAG_Out_ptr, struct DownVector * const DownVectorPtr, struct NorthVector * const NorthVectorPtr)
{
        //cross the magnetic field vector with the down vector to get the east vector
        //then cross east and down to get magnetic north
    float TempEastVectorX = MAG_Out_ptr->Z_Mag_Strength*DownVectorPtr->DownZ - MAG_Out_ptr->Z_Mag_Strength*DownVectorPtr->DownY;
    float TempEastVectorY = MAG_Out_ptr->Z_Mag_Strength*DownVectorPtr->DownX - MAG_Out_ptr->X_Mag_Strength*DownVectorPtr->DownZ;
    float TempEastVectorZ = MAG_Out_ptr->X_Mag_Strength*DownVectorPtr->DownY - MAG_Out_ptr->Y_Mag_Strength*DownVectorPtr->DownX;
    
    float MagNorthX = TempEastVectorY*DownVectorPtr->DownZ - TempEastVectorZ*DownVectorPtr->DownY;
    float MagNorthY = TempEastVectorZ*DownVectorPtr->DownX - TempEastVectorX*DownVectorPtr->DownZ;
    float MagNorthZ = TempEastVectorX*DownVectorPtr->DownY - TempEastVectorY*DownVectorPtr->DownX;
    
        //need to rotate the vecotr in the yz plane (for some reason x is up/down here) to account for magnetic declination
        //rotating **clockwise** 15 degrees, since the magnetic north is 15 degrees west of geographic north
        //just hardcoding the rotation matrix (cos15 ~= 0.966, sin15 ~= 0.259)
    float Oriented_North_X = MagNorthX;
    float Oriented_North_Y = MagNorthY*0.966 + MagNorthZ*0.259;
    float Oriented_North_Z = MagNorthZ*0.966 - MagNorthY*0.259;

        //Find magnitude of the north pointing vector
    float North_Magnitude = sqrt((Oriented_North_X*Oriented_North_X)+(Oriented_North_Y*Oriented_North_Y)+(Oriented_North_Z*Oriented_North_Z));

    NorthVectorPtr->NorthX = Oriented_North_X/North_Magnitude;
    NorthVectorPtr->NorthY = Oriented_North_Y/North_Magnitude;
    NorthVectorPtr->NorthZ = Oriented_North_Z/North_Magnitude;
}


    //Purpose: Call for polling the the Magnetometer and prints the returns
    //Ingests the following values:
    //IMU: const signed integer, File handle to the IMU I2C address
    //MAG_Out: const pointer to a MAG_OUT structure, Pointer to array where all magnetometer final output data will get stored
    //Return Type: Void
void Run_MAG(const int MAG, struct MAG_OUT * const MAG_Out, struct DownVector * const DownVectorPtr, struct NorthVector * const NorthVectorPtr)
{
    uint8_t Get_Success = 0;
    uint8_t MAG_Data_Status = 0x00;
    uint8_t MAG_Data_SRC_Status = 0x00;

    uint8_t Status_Reg_Poll_Status = DirI2CRead_Reg_8(MAG, STATUS_REG_LIS, &MAG_Data_Status);
    uint8_t SRC_Reg_Poll_Status = DirI2CRead_Reg_8(MAG, STATUS_REG_LIS, &MAG_Data_SRC_Status);
    if(DEBUG == 3)
    {
        if((MAG_Data_Status & MAG_FULL_OVERRUN) > 0)
        {
            puts("[NOTICE] Data Overrun Detected for ALL Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_Status & MAG_Z_OVERRUN) > 0)
        {
            puts("[NOTICE] Data Overrun Detected for Z Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_Status & MAG_Y_OVERRUN) > 0)
        {
            puts("[NOTICE] Data Overrun Detected for Y Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_Status & MAG_X_OVERRUN) > 0)
        {
            puts("[NOTICE] Data Overrun Detected for X Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_SRC_Status & MAG_MEASUREMENT_OVERFLOW) > 0)
        {
            puts("[DANGER] MAG Overflow Detected!");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_SRC_Status & MAG_X_POS_THRESH_EXCEED) > 0)
        {
            puts("[WARNING] Positve Bound Exceeded for X Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_SRC_Status & MAG_Y_POS_THRESH_EXCEED) > 0)
        {
            puts("[WARNING] Positve Bound Exceeded for Y Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_SRC_Status & MAG_Z_POS_THRESH_EXCEED) > 0)
        {
            puts("[WARNING] Positve Bound Exceeded for Z Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_SRC_Status & MAG_X_NEG_THRESH_EXCEED) > 0)
        {
            puts("[WARNING] Negitive Bound Exceeded for X Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_SRC_Status & MAG_Y_NEG_THRESH_EXCEED) > 0)
        {
            puts("[WARNING] Negitive Bound Exceeded for Y Axis.");
        }
        else
        {
            puts("");
        }
        
        if((MAG_Data_SRC_Status & MAG_Z_NEG_THRESH_EXCEED) > 0)
        {
            puts("[WARNING] Negitive Bound Exceeded for Z Axis.");
        }
        else
        {
            puts("");
        }
    }

    if(Status_Reg_Poll_Status > 0)
    {
        uint8_t New_Data = MAG_Data_Status & MAG_FULL_NEW;
        if(New_Data > 0)
        {
            int8_t Poll_MAG_Status = Poll_Magnetometer(MAG, MAG_Data_Status, MAG_Out);
            FindNorth(MAG_Out, DownVectorPtr, NorthVectorPtr);
        }
        else
        {
            puts("\n");
        }
    }
}

void Run_MAG_Self_Test(const int MAG, struct MAG_OUT * const MAG_Out)
{
    Dash_Line();

    uint8_t Self_Test_Register_Setting = (CTRL_REG1_INIT | SELF_TEST_MASK);
    int8_t Self_Test_Write_Status = DirI2CWrite_Reg_8(MAG, CTRL_REG1, Self_Test_Register_Setting);
    uint8_t Self_Test_Read = 0;
    int8_t Self_Test_Status = DirI2CRead_Reg_8(MAG, CTRL_REG1, &Self_Test_Read);
    if(Self_Test_Read == Self_Test_Register_Setting)
    {
        puts("Magnotometer Self Test Initieation Checks [GOOD]");
       
        puts("Please Wait...");
        usleep(61000);

        uint8_t MAG_Data_Status = 0x00;
        uint8_t MAG_Overflow_Status = 0x00;
        uint8_t Sample_Set = 0;

        float X_Sum = 0;
        float Y_Sum = 0;
        float Z_Sum = 0;

        while(Sample_Set < MAG_SELF_TEST_DURRATION)
        {
            uint8_t Status_Reg_Poll_Status = DirI2CRead_Reg_8(MAG, STATUS_REG_LIS, &MAG_Data_Status);
            if((MAG_Data_Status & MAG_FULL_NEW) > 0)
            {
                Sample_Set++;
                int8_t Poll_MAG_Status = Poll_Magnetometer(MAG, MAG_Data_Status, MAG_Out);
                uint8_t SRC_Reg_Poll_Status = DirI2CRead_Reg_8(MAG, STATUS_REG_LIS, &MAG_Overflow_Status);

                if((Poll_MAG_Status > 0) && (Sample_Set > 1))
                {
                    printf("\nSample [%u] Collected\n", Sample_Set);
                    if((MAG_Overflow_Status & MAG_MEASUREMENT_OVERFLOW) > 0)
                    {
                        puts("[DANGER] MAG Overflow Detected!");
                    }
                    printf("X Axis: %f G\n", (MAG_Out->X_Mag_Strength));
                    X_Sum += (MAG_Out->X_Mag_Strength);

                    printf("Y Axis: %f G\n", (MAG_Out->Y_Mag_Strength));
                    Y_Sum += (MAG_Out->Y_Mag_Strength);

                    printf("Z Axis: %f G\n", (MAG_Out->Z_Mag_Strength));
                    Z_Sum += (MAG_Out->Z_Mag_Strength);
                    puts("");
                }
            }
            else
            {
                printf("Waiting for Sample [%u]...\n", Sample_Set);
            }
        }

        float X_Mean = (X_Sum/MAG_SELF_TEST_DURRATION)*1000;
        float Y_Mean = (Y_Sum/MAG_SELF_TEST_DURRATION)*1000;
        float Z_Mean = (Z_Sum/MAG_SELF_TEST_DURRATION)*1000;

        if((X_Mean < TEST_X_AXIS_MAX) && (TEST_X_AXIS_MIN < X_Mean))
        {
            puts("Magnotometer Self Test X Axis Checks [GOOD]");
        }
        else
        {
            puts("Magnotometer Self Test X Axis Checks [BAD]");
            printf("Mean X Read: %.f, Expected: %i < X < %i\n\n", X_Mean, TEST_X_AXIS_MIN, TEST_X_AXIS_MAX);
        }
        
        if((Y_Mean < TEST_Y_AXIS_MAX) && (TEST_Y_AXIS_MIN < Y_Mean))
        {
            puts("Magnotometer Self Test Y Axis Checks [GOOD]");
        }
        else
        {
            puts("Magnotometer Self Test Y Axis Checks [BAD]");
            printf("Mean Y Read: %.f, Expected: %i < Y < %i\n\n", Y_Mean, TEST_Y_AXIS_MIN, TEST_Y_AXIS_MAX);
        }
        
        if((X_Mean < TEST_Z_AXIS_MAX) && (TEST_Z_AXIS_MIN < Z_Mean))
        {
            puts("Magnotometer Self Test Z Axis Checks [GOOD]");
        }
        else
        {
            puts("Magnotometer Self Test Z Axis Checks [BAD]");
            printf("Mean Z Read: %.f, Expected: %i < Z < %i\n\n", Z_Mean, TEST_Z_AXIS_MIN, TEST_Z_AXIS_MAX);
        }
    }
    else
    {
        puts("Magnotometer Self Test Initieation Checks [BAD]");
        printf("Control Register 1 set to: %X, Expected: %X\n\n", Self_Test_Read, Self_Test_Register_Setting);
    }
    Dash_Line();
}
