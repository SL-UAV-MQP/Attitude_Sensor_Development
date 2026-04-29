#include "Attitude_Comms_GPIO.h"

    //IMU Sensor functions

    //Purpose: Reset the IMU state and set the internal configuration registers
    //Ingests the following values:
    //IMU: const signed integer, File handle to the IMU I2C address
    //Return Type: signed 8-bit integer
    //Return on Sucess: 12 (total number of bytes writen for full config)
    //Return on Fail: Total number of missed bytes (negitive values from -12 to -1)
int8_t Init_IMU(const int IMU_fd)
{
    puts("\nConfigureing IMU Control Registers...\n");

    if(DEBUG > 0)
    {
        puts("\nRestarting IMU Hardware...");
    }

    int8_t Reboot_Status = DirI2CWrite_Reg_8(IMU_fd, CTRL3_C, INIT_REBOOT_LSM);
    uint8_t Reboot_Reg = 0x00;
    while(1)
    {
        DirI2CRead_Reg_8(IMU_fd, CTRL3_C, &Reboot_Reg);
        if(Reboot_Reg == INIT_REBOOT_LSM)
        {
            usleep(12000);
            puts("IMU Hardware Restart Checks [GOOD]");
            break;
        }
        printf("Booting Status: %X\n", Reboot_Status);
        usleep(1000);
        Reboot_Status = DirI2CWrite_Reg_8(IMU_fd, CTRL3_C, INIT_REBOOT_LSM);
    }
    
    if(DEBUG > 0)
    {
        puts("\nRestarting IMU Software...");
    }

    DirI2CWrite_Reg_8(IMU_fd, CTRL3_C, INIT_RST_LSM);
    usleep(25);

    uint8_t Reset_Reg = INIT_RST_LSM;
    while(1)
    {
        DirI2CRead_Reg_8(IMU_fd, CTRL3_C, &Reset_Reg);
        if((Reset_Reg != INIT_RST_LSM) && (Reset_Reg != INIT_REBOOT_LSM))
        {
            puts("IMU Software Restart Checks [GOOD]");
            break;
        }
        usleep(10);
        printf("Booting Status: %X\n", Reset_Reg);
    }

        //See LSM6DSO.h for configuration setting
    int8_t FUNC_CFG_ACCESS_Write_Status = DirI2CWrite_Reg_8(IMU_fd, FUNC_CFG_ACCESS, FUNC_CFG_ACCESS_INIT);
    uint8_t FUNC_CFG_ACCESS_Read = 0;
    int8_t FUNC_CFG_ACCESS_Read_Status = DirI2CRead_Reg_8(IMU_fd, FUNC_CFG_ACCESS, &FUNC_CFG_ACCESS_Read);
    if(FUNC_CFG_ACCESS_Read == FUNC_CFG_ACCESS_INIT)
    {
        puts("IMU FUNC_CFG_ACCESS Register Checks [GOOD]");
    }
    else
    {
        puts("IMU FUNC_CFG_ACCESS Register Checks [BAD]");
        printf("FUNC_CFG_ACCESS set to: %X, Expected: %X\n\n", FUNC_CFG_ACCESS_Read, FUNC_CFG_ACCESS_INIT);
    }

        //See LSM6DSO.h for configuration setting
    int8_t PIN_CTRL_Write_Status = DirI2CWrite_Reg_8(IMU_fd, DSO_PIN_CTRL, PIN_CTRL_INIT);
    uint8_t PIN_CTRL_Read = 0;
    int8_t PIN_CTRL_Read_Status = DirI2CRead_Reg_8(IMU_fd, DSO_PIN_CTRL, &PIN_CTRL_Read);
    if(PIN_CTRL_Read == PIN_CTRL_INIT)
    {
        puts("IMU PIN_CTRL Register Checks [GOOD]");
    }
    else
    {
        puts("IMU PIN_CTRL Register Checks [BAD]");
        printf("PIN_CTRL set to: %X, Expected: %X\n\n", PIN_CTRL_Read, PIN_CTRL_INIT);
    }

        //See LSM6DSO.h for configuration setting
    int8_t FIFO_CTRL4_Write_Status = DirI2CWrite_Reg_8(IMU_fd, DSO_FIFO_CTRL4, FIFO_CTRL4_INIT);
    uint8_t FIFO_CTRL4_Read = 0;
    int8_t FIFO_CTRL4_Read_Status = DirI2CRead_Reg_8(IMU_fd, DSO_FIFO_CTRL4, &FIFO_CTRL4_Read);
    if(FIFO_CTRL4_Read == FIFO_CTRL4_INIT)
    {
        puts("IMU FIFO Control 4 Register Checks [GOOD]");
    }
    else
    {
        puts("IMU FIFO Control 4 Register Checks [BAD]");
        printf("FIFO_CTRL4 set to: %X, Expected: %X\n\n", FIFO_CTRL4_Read, FIFO_CTRL4_INIT);
    }

        //See LSM6DSO.h for configuration setting
    int8_t CTRL1_XL_Write_Status = DirI2CWrite_Reg_8(IMU_fd, CTRL1_XL, CTRL1_XL_INIT);
    uint8_t CTRL1_XL_Read = 0;
    int8_t CTRL1_XL_Read_Status = DirI2CRead_Reg_8(IMU_fd, CTRL1_XL, &CTRL1_XL_Read);
    if(CTRL1_XL_Read == CTRL1_XL_INIT)
    {
        puts("IMU Control 1 XL Register Checks [GOOD]");
    }
    else
    {
        puts("IMU Control 1 XL Register Checks [BAD]");
        printf("CTRL1_XL set to: %X, Expected: %X\n\n", CTRL1_XL_Read, CTRL1_XL_INIT);
    }

        //See LSM6DSO.h for configuration setting
    int8_t CTRL2_G_Write_Status = DirI2CWrite_Reg_8(IMU_fd, CTRL2_G, CTRL2_G_INIT);
    uint8_t CTRL2_G_Read = 0;
    int8_t CTRL2_G_Read_Status = DirI2CRead_Reg_8(IMU_fd, CTRL2_G, &CTRL2_G_Read);
    if(CTRL2_G_Read == CTRL2_G_INIT)
    {
        puts("IMU Control 2 G Register Checks [GOOD]");
    }
    else
    {
        puts("IMU Control 2 G Register Checks [BAD]");
        printf("CTRL2_G set to: %X, Expected: %X\n\n", CTRL2_G_Read, CTRL2_G_INIT);
    }

        //See LSM6DSO.h for configuration setting
    int8_t CTRL4_C_Write_Status = DirI2CWrite_Reg_8(IMU_fd, CTRL4_C, CTRL4_C_INIT);
    uint8_t CTRL4_C_Read = 0;
    int8_t CTRL4_C_Read_Status = DirI2CRead_Reg_8(IMU_fd, CTRL4_C, &CTRL4_C_Read);
    if(CTRL4_C_Read == CTRL4_C_INIT)
    {
        puts("IMU Control 4 C Register Checks [GOOD]");
    }
    else
    {
        puts("IMU Control 4 C Register Checks [BAD]");
        printf("CTRL4_C set to: %X, Expected: %X\n\n", CTRL4_C_Read, CTRL4_C_INIT);
    }

    if((FUNC_CFG_ACCESS_Write_Status+PIN_CTRL_Write_Status+FIFO_CTRL4_Write_Status+CTRL1_XL_Write_Status+CTRL2_G_Write_Status+CTRL4_C_Write_Status) == 12)
    {
        puts("IMU Configuration Complete!");
        return(12);
    }
    else
    {
        puts("IMU Configuration Errors Occured.");
        return((FUNC_CFG_ACCESS_Write_Status+PIN_CTRL_Write_Status+FIFO_CTRL4_Write_Status+CTRL1_XL_Write_Status+CTRL2_G_Write_Status+CTRL4_C_Write_Status)-12);
    }
}

    //Purpose: Get raw IMU temperature values from the IMU
    //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //Raw_Temp: const signed 16-bit integer pointer, pointer to raw temperature values
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw temperature 16-bit signed integer out if sucess
int8_t Get_IMU_Raw_Temperature(const int IMU_fd, int16_t * const Raw_Temp)
{
    uint8_t Temp_High = 0;
    int8_t Temp_High_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUT_TEMP_H, &Temp_High);
    
    uint8_t Temp_Low = 0;
    int8_t Temp_Low_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUT_TEMP_L, &Temp_Low);


    if((Temp_High_Read_Status < 0) || (Temp_Low_Read_Status < 0))
    {
        puts("IMU Temprature Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_Temp = ((int16_t)BUFF_RECON_UI16(Temp_High, Temp_Low));
        return(1);
    }
}

    //Purpose: Get raw IMU X axis Gyroscope values from the IMU
    //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //Raw_X_Rot: const signed 16-bit integer pointer, pointer to raw X axis rotational value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw X axis rotational value 16-bit signed integer out if Sucess
int8_t Get_Raw_X_Gyroscope(const int IMU_fd, int16_t * const Raw_X_Rot)
{
    uint8_t X_GA_High = 0;
    int8_t X_GA_High_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTX_H_G, &X_GA_High);

    uint8_t X_GA_Low = 0;
    int8_t X_GA_Low_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTX_L_G, &X_GA_Low);

    if((X_GA_High_Read_Status < 0) || (X_GA_Low_Read_Status < 0))
    {
        puts("IMU Gyro X Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_X_Rot = ((int16_t)BUFF_RECON_UI16(X_GA_High, X_GA_Low));
        return(1);
    }
}

    //Purpose: Get raw IMU Y axis Gyroscope values from the IMU
    //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //Raw_Y_Rot: const signed 16-bit integer pointer, pointer to raw Y axis rotational value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw Y axis rotational value 16-bit signed integer out if Sucess
int8_t Get_Raw_Y_Gyroscope(const int IMU_fd, int16_t * const Raw_Y_Rot)
{
    uint8_t Y_GA_High = 0;
    int8_t Y_GA_High_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTY_H_G, &Y_GA_High);
    
    uint8_t Y_GA_Low = 0;
    int8_t Y_GA_Low_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTY_L_G, &Y_GA_Low);

    if((Y_GA_High_Read_Status < 0) || (Y_GA_Low_Read_Status < 0))
    {
        puts("IMU Gyro Y Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_Y_Rot = ((int16_t)BUFF_RECON_UI16(Y_GA_High, Y_GA_Low));
        return(1);
    }
}

    //Purpose: Get raw IMU Z axis Gyroscope values from the IMU
    //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //Raw_Z_Rot: const signed 16-bit integer pointer, pointer to raw Z axis rotational value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw Z axis rotational value 16-bit signed integer out if Sucess
int8_t Get_Raw_Z_Gyroscope(const int IMU_fd, int16_t * const Raw_Z_Rot)
{
    uint8_t Z_GA_High = 0;
    int8_t Z_GA_High_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTZ_H_G, &Z_GA_High);
    
    uint8_t Z_GA_Low = 0;
    int8_t Z_GA_Low_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTZ_L_G, &Z_GA_Low);
    
    if((Z_GA_High_Read_Status < 0) || (Z_GA_Low_Read_Status < 0))
    {
        puts("IMU Gyro Z Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_Z_Rot = ((int16_t)BUFF_RECON_UI16(Z_GA_High, Z_GA_Low));
        return(1);
        
    }
}

    //Purpose: Get raw IMU X axis Accelerometer values from the IMU
    //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //Raw_X_Lin: const signed 16-bit integer pointer, pointer to raw X axis acceleration  value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw X axis acceleration 16-bit signed integer out if Sucess
int8_t Get_Raw_X_Linear_Acceleration(const int IMU_fd, int16_t * const Raw_X_Lin)
{
    uint8_t X_LA_High = 0;
    int8_t X_LA_High_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTX_H_A, &X_LA_High);
    
    uint8_t X_LA_Low = 0;
    int8_t X_LA_Low_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTX_L_A, &X_LA_Low);

    
    if((X_LA_High_Read_Status < 0) || (X_LA_Low_Read_Status < 0))
    {
        puts("IMU Accel X Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_X_Lin = ((int16_t)BUFF_RECON_UI16(X_LA_High, X_LA_Low));
        return(1);
    }
}

    //Purpose: Get raw IMU Y axis Accelerometer values from the IMU
    //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //Raw_Y_Lin: const signed 16-bit integer pointer, pointer to raw Y axis acceleration  value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw Y axis acceleration 16-bit signed integer out if Sucess
int8_t Get_Raw_Y_Linear_Acceleration(const int IMU_fd, int16_t * const Raw_Y_Lin)
{
    uint8_t Y_LA_High = 0;
    int8_t Y_LA_High_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTY_H_A, &Y_LA_High);
    
    uint8_t Y_LA_Low = 0;
    int8_t Y_LA_Low_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTY_L_A, &Y_LA_Low);


    if((Y_LA_High_Read_Status < 0) || (Y_LA_Low_Read_Status < 0))
    {
        puts("IMU Accel Y Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_Y_Lin = ((int16_t)BUFF_RECON_UI16(Y_LA_High, Y_LA_Low));
        return(1);
    }
}

    //Purpose: Get raw IMU Z axis Accelerometer values from the IMU
    //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //Raw_Z_Lin: const signed 16-bit integer pointer, pointer to raw Z axis acceleration  value
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: -1
    //App Notes: passes the raw Z axis acceleration 16-bit signed integer out if Sucess
int8_t Get_Raw_Z_Linear_Acceleration(const int IMU_fd, int16_t * const Raw_Z_Lin)
{
    uint8_t Z_LA_High = 0;
    int8_t Z_LA_High_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTZ_H_A, &Z_LA_High);
    
    uint8_t Z_LA_Low = 0;
    int8_t Z_LA_Low_Read_Status = DirI2CRead_Reg_8(IMU_fd, OUTZ_L_A, &Z_LA_Low);


    if((Z_LA_High_Read_Status < 0) || (Z_LA_Low_Read_Status < 0))
    {
        puts("IMU Accel Y Read Checks [BAD]");
        return(-1);
    }
    else
    {
        *Raw_Z_Lin = ((int16_t)BUFF_RECON_UI16(Z_LA_High, Z_LA_Low));
        return(1);
    }
}

    //Purpose: Check the Full Scale Register values for the gyroscope, get the rotational axis data and write final sensor data to the output structure
    //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //GYRO_Out: const pointer to a GYRO_Out structure, Pointer to array where all gyroscope final output data will get stored
    //Gyrometer_Calibration_Data: const pointer to a GYRO_Out structure, Pointer to array where all gyroscope calibration values will get stored
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: number of failed register reads (-1 to -3)
    //App Notes: None
int8_t Poll_Gyroscope(const int IMU_fd, struct GYRO_OUT * const GYRO_Out, struct GYRO_CAL * const Gyrometer_Calibration_Data)
{
    uint8_t Get_Success = 0;
    uint8_t Rot_FSR_Check = 0x00;
    uint8_t Rot_FSR_Read_Status = DirI2CRead_Reg_8(IMU_fd, CTRL2_G, &Rot_FSR_Check);
    if(Rot_FSR_Read_Status > 0)
    {
        Rot_FSR_Check = (Rot_FSR_Check & FSR_MASK_LSM);
    }

    float Rot_FSR = 0;

    switch(Rot_FSR_Check)
    {
        case LSM_FS_00:
        {
            Rot_FSR = FS_250DPS;
            break;
        }
        case LSM_FS_01:
        {
            Rot_FSR = FS_500DPS;
            break;
        }
        case LSM_FS_10:
        {
            Rot_FSR = ((float)(FS_1000DPS));
            break;
        }
        case LSM_FS_11:
        {
            Rot_FSR = ((float)(FS_2000DPS));
            break;
        }
    }

    if(DEBUG == 2)
    {
        printf("Gyroscope FSR: %f\n\n", Rot_FSR);
    }

    int16_t Raw_X_GR = 0;
    int16_t Raw_Y_GR = 0;
    int16_t Raw_Z_GR = 0;

    if(DEBUG == 2)
    {
        puts("\nGetting X Rot...");
    }
    if(Get_Raw_X_Gyroscope(IMU_fd, &Raw_X_GR) > 0)
    {
        Get_Success++;

        if(DEBUG == 2)
        {
            printf("Raw X Rot: %i\n\n", Raw_X_GR);
        }
        (GYRO_Out->X_Rot_Rate) = (((float)Raw_X_GR) * Rot_FSR) - (Gyrometer_Calibration_Data->X_ROT);
    }
    if(DEBUG == 2)
    {
        puts("\nGetting Y Rot...");
    }
    if(Get_Raw_Y_Gyroscope(IMU_fd, &Raw_Y_GR) > 0)
    {
        Get_Success++;

        if(DEBUG == 2)
        {
            printf("Raw Y Rot: %i\n\n", Raw_Y_GR);
        }
        (GYRO_Out->Y_Rot_Rate) = (((float)Raw_Y_GR) * Rot_FSR) - (Gyrometer_Calibration_Data->Y_ROT);
    }

    if(DEBUG == 2)
    {
        puts("\nGetting Z Rot...");
    }
    if(Get_Raw_Z_Gyroscope(IMU_fd, &Raw_Z_GR) > 0)
    {
        Get_Success++;

        if(DEBUG == 2)
        {
            printf("Raw Z Rot: %i\n\n", Raw_Z_GR);
        }
        (GYRO_Out->Z_Rot_Rate) = (((float)Raw_Z_GR) * Rot_FSR) - (Gyrometer_Calibration_Data->Z_ROT);
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


    //Purpose: Check the Full Scale Register values for the accelerometer, get the linear acceleration axis data and write final sensor data to the output structure
    // //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //ACC_Out: const pointer to a ACC_OUT structure, Pointer to array where all accelerometer final output data will get stored
    //Accelerometer_Calibration_Data: const pointer to a ACC_CAL structure, Pointer to array where all accelerometer calibration values will get stored
    //Return Type: signed 8-bit integer
    //Return On Sucess: 1
    //Return On Fail: number of failed register reads (-1 to -3)
    //App Notes: none
int8_t Poll_Accelerometer(const int IMU_fd, struct ACC_OUT * const ACC_Out, struct ACC_CAL * const Accelerometer_Calibration_Data)
{
    uint8_t Get_Success = 0;
    uint8_t Lin_FSR_Check = 0x00;
    uint8_t Lin_FSR_Read_Status = DirI2CRead_Reg_8(IMU_fd, CTRL1_XL, &Lin_FSR_Check);
    if(Lin_FSR_Read_Status > 0)
    {
        Lin_FSR_Check = (Lin_FSR_Check & FSR_MASK_LSM);
    }

    float Lin_FSR = 0;

    switch(Lin_FSR_Check)
    {
        case LSM_FS_00:
        {
            Lin_FSR = FS_2G;
            break;
        }
        case LSM_FS_01:
        {
            Lin_FSR = FS_4G;
            break;
        }
        case LSM_FS_10:
        {
            Lin_FSR = FS_8G;
            break;
        }
        case LSM_FS_11:
        {
            Lin_FSR = FS_16G;
            break;
        }
    }

    if(DEBUG == 2)
    {
        printf("Accelerometer FSR: %f\n\n", Lin_FSR);
    }

    int16_t Raw_X_Acc = 0;
    int16_t Raw_Y_Acc = 0;
    int16_t Raw_Z_Acc = 0;

    if(DEBUG == 2)
    {
        puts("\nGetting X Accel...");
    }
    if(Get_Raw_X_Linear_Acceleration(IMU_fd, &Raw_X_Acc) > 0)
    {
        Get_Success++;

        if(DEBUG == 2)
        {
            printf("Raw X Accel: %i\n\n", Raw_X_Acc);
        }
        (ACC_Out->X_Lin_Accel) = (((float)Raw_X_Acc) * Lin_FSR) - (Accelerometer_Calibration_Data->X_LIN);
    }

    if(DEBUG == 2)
    {
        puts("\nGetting Y Accel...");
    }

    if(Get_Raw_Y_Linear_Acceleration(IMU_fd, &Raw_Y_Acc) > 0)
    {
        Get_Success++;

        if(DEBUG == 2)
        {
            printf("Raw Y Accel: %i\n\n", Raw_Y_Acc);
        }
        (ACC_Out->Y_Lin_Accel) = (((float)Raw_Y_Acc) * Lin_FSR) - (Accelerometer_Calibration_Data->Y_LIN);
    }

    if(DEBUG == 2)
    {
        puts("\nGetting Z Accel...");
    }
    if(Get_Raw_Z_Linear_Acceleration(IMU_fd, &Raw_Z_Acc) > 0)
    {   
        Get_Success++;

        if(DEBUG == 2)
        {
            printf("Raw Z Accel: %i\n\n", Raw_Z_Acc);
        }
        (ACC_Out->Z_Lin_Accel) = (((float)Raw_Z_Acc) * Lin_FSR) - (Accelerometer_Calibration_Data->Z_LIN);
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

    //Purpose: Average out the static offsets in the gyroscope and accelerometer sensors
    // //Ingests the following values:
    //IMU: const signed integer, File handle to the altimiter I2C address
    //GYRO_Out: const pointer to a GYRO_Out structure, Pointer to array where all gyroscope final output data will get stored
    //Gyrometer_Calibration_Data: const pointer to a GYRO_Out structure, Pointer to array where all gyroscope calibration values will get stored
    //ACC_Out: const pointer to a ACC_OUT structure, Pointer to array where all accelerometer final output data will get stored
    //Accelerometer_Calibration_Data: const pointer to a ACC_CAL structure, Pointer to array where all accelerometer calibration values will get stored
    //Return Type: void
    //App Notes: Do not confuse the different structures and parameter inputs
void Zeroize_IMU(const int IMU_fd, struct GYRO_OUT * const GYRO_Out, struct ACC_OUT * const ACC_Out, struct GYRO_CAL * const Gyrometer_Calibration_Data, struct ACC_CAL * const Accelerometer_Calibration_Data)
{
    puts("\nZeroizing IMU...");
    float X_Rot_Cal = 0;
    float Y_Rot_Cal = 0;
    float Z_Rot_Cal = 0;
    float X_Lin_Cal = 0;
    float Y_Lin_Cal = 0;
    float Z_Lin_Cal = 0;

    uint32_t imu_gyro_cal = 0;
    uint32_t imu_accel_cal = 0;
    
    while((imu_gyro_cal < GYRO_CAL_DURRATION) && (imu_accel_cal < ACC_CAL_DURRATION))
    {
        uint8_t IMU_Data_Status = 0x00;
        uint8_t Status_Reg_Poll_Status = DirI2CRead_Reg_8(IMU_fd, STATUS_REG_LSM, &IMU_Data_Status);
        if(Status_Reg_Poll_Status > 0)
        {
            uint8_t New_Gyro = IMU_Data_Status & GYRO_NEW;
            uint8_t New_Acc = IMU_Data_Status & ACC_NEW;

            if((New_Gyro > 0) && (imu_gyro_cal < GYRO_CAL_DURRATION))
            {
                int8_t Poll_Gyro_Status = Poll_Gyroscope(IMU_fd, GYRO_Out, Gyrometer_Calibration_Data);
                if(Poll_Gyro_Status > 0)
                {
                    X_Rot_Cal += (GYRO_Out->X_Rot_Rate);
                    Y_Rot_Cal += (GYRO_Out->Y_Rot_Rate);
                    Z_Rot_Cal += (GYRO_Out->Z_Rot_Rate);
                    imu_gyro_cal++;
                    printf("Gyro Compleation  | [%i/%i]\n", imu_gyro_cal, GYRO_CAL_DURRATION);
                }
            }

            if((New_Acc > 0) && (imu_accel_cal < ACC_CAL_DURRATION))
            {
                int8_t Poll_Acc_Status = Poll_Accelerometer(IMU_fd, ACC_Out, Accelerometer_Calibration_Data);
                if(Poll_Acc_Status > 0)
                {
                    X_Lin_Cal += (ACC_Out->X_Lin_Accel);
                    Y_Lin_Cal += (ACC_Out->Y_Lin_Accel);
                    Z_Lin_Cal += (ACC_Out->Z_Lin_Accel);
                    imu_accel_cal++;
                    printf("Accel Compleation | [%i/%i]\n", imu_accel_cal, ACC_CAL_DURRATION);
                }
            }
        }
    }

    (Gyrometer_Calibration_Data->X_ROT) = X_Rot_Cal/GYRO_CAL_DURRATION;
    (Gyrometer_Calibration_Data->Y_ROT) = Y_Rot_Cal/GYRO_CAL_DURRATION;
    (Gyrometer_Calibration_Data->Z_ROT) = Z_Rot_Cal/GYRO_CAL_DURRATION;


    float X_Lin_Temp = X_Lin_Cal/ACC_CAL_DURRATION;
    float Y_Lin_Temp = Y_Lin_Cal/ACC_CAL_DURRATION;
    float Z_Lin_Temp = Z_Lin_Cal/ACC_CAL_DURRATION;

    float Down_Magnitude = hypot(X_Lin_Temp, hypot(Y_Lin_Temp, Z_Lin_Temp));
        
    float Uvec_Gravity_X = (-1*X_Lin_Temp)/Down_Magnitude;
    float Uvec_Gravity_Y = (-1*Y_Lin_Temp)/Down_Magnitude;
    float Uvec_Gravity_Z = (-1*Z_Lin_Temp)/Down_Magnitude;

    
    (Accelerometer_Calibration_Data->X_LIN) = X_Lin_Temp+(Uvec_Gravity_X*GRAVITY_ACCEL);
    (Accelerometer_Calibration_Data->Y_LIN) = Y_Lin_Temp+(Uvec_Gravity_Y*GRAVITY_ACCEL);
    (Accelerometer_Calibration_Data->Z_LIN) = Z_Lin_Temp+(Uvec_Gravity_Z*GRAVITY_ACCEL);

    puts("\nIMU Zeroizeing Checks [GOOD]");
    printf("Rotation Offset:     | [%+.4f , %+.4f , %+.4f] Deg/s\n", (Gyrometer_Calibration_Data->X_ROT)/1000, (Gyrometer_Calibration_Data->Y_ROT)/1000, (Gyrometer_Calibration_Data->Z_ROT)/1000);
    printf("Acceleration Offset: | [%+.4f , %+.4f , %+.4f] m/s^2\n", (Accelerometer_Calibration_Data->X_LIN), (Accelerometer_Calibration_Data->Y_LIN), (Accelerometer_Calibration_Data->Z_LIN));
    
}

    //purpose: if there is not acceleration in the horizontal axes, set the vector indicating down to the inverse of the acceleration vector
    //inputs: pointers to the accelerometer output struct and the down vector struct
    //does not technically have outputs but modifies the down vector struct via pointers
void FindDown(struct ACC_OUT * const ACC_OUT_ptr, struct DownVector * const DownVectorPtr)
{
        //if the acceleration is less than 0.01g, the drone is probably stationary
        //if its moving, we don't want to update the down vector
    
        float Oriented_Down_X = ACC_OUT_ptr->X_Lin_Accel;
        float Oriented_Down_Y = ACC_OUT_ptr->Y_Lin_Accel;
        float Oriented_Down_Z = ACC_OUT_ptr->Z_Lin_Accel;

        float Down_Magnitude = hypot(Oriented_Down_X, hypot(Oriented_Down_Y,Oriented_Down_Z));
     
    
        if(abs(Down_Magnitude - GRAVITY_ACCEL) < 0.05)
        {
            DownVectorPtr->DownX = (-1*ACC_OUT_ptr->X_Lin_Accel)/Down_Magnitude;
            DownVectorPtr->DownY = (-1*ACC_OUT_ptr->Y_Lin_Accel)/Down_Magnitude;
            DownVectorPtr->DownZ = (-1*ACC_OUT_ptr->Z_Lin_Accel)/Down_Magnitude;
            DownVectorPtr->DownTheta = atan2((ACC_OUT_ptr->Z_Lin_Accel), (ACC_OUT_ptr->X_Lin_Accel));
            DownVectorPtr->DownPhi = acos((ACC_OUT_ptr->Y_Lin_Accel)/Down_Magnitude);
        }
}

    //Purpose: Call for polling the IMU and prints the returns
    //Ingests the following values:
    //IMU: const signed integer, File handle to the IMU I2C address
    //GYRO_Out: const pointer to a GYRO_Out structure, Pointer to array where all gyroscope final output data will get stored
    //Gyrometer_Calibration_Data: const pointer to a GYRO_Out structure, Pointer to array where all gyroscope calibration values will get stored
    //ACC_Out: const pointer to a ACC_OUT structure, Pointer to array where all accelerometer final output data will get stored
    //Accelerometer_Calibration_Data: const pointer to a ACC_CAL structure, Pointer to array where all accelerometer calibration values will get stored
    //Return Type: Void
void Run_IMU(const int IMU_fd, struct GYRO_OUT * const GYRO_Out, struct ACC_OUT * const ACC_Out, struct GYRO_CAL * const Gyrometer_Calibration_Data, struct ACC_CAL * const Accelerometer_Calibration_Data, struct DownVector * const DownVectorPtr)
{
    uint8_t IMU_Data_Status = 0x00;
    uint8_t Status_Reg_Poll_Status = DirI2CRead_Reg_8(IMU_fd, STATUS_REG_LSM, &IMU_Data_Status);
    if(Status_Reg_Poll_Status > 0)
    {
        uint8_t New_Temp = IMU_Data_Status & TEMP_NEW;
        uint8_t New_Gyro = IMU_Data_Status & GYRO_NEW;
        uint8_t New_Acc = IMU_Data_Status & ACC_NEW;
    

        if(DEBUG == 2)
        {
            printf("New Temp: %i\nNew Gyro: %i\nNew Accel: %i\n", New_Temp, New_Gyro, New_Acc);
        }

        if(New_Temp > 0)
        {
            float Temp_FSR = 0;
            int8_t Temp_Offset = 0;

            int16_t IMU_Raw_Temp = 0;
            int8_t Get_Temp_Status = Get_IMU_Raw_Temperature(IMU_fd, &IMU_Raw_Temp);
        }
        else
        {
            puts("\n");
        }

        if(New_Gyro > 0)
        {
            int8_t Poll_Gyro_Status = Poll_Gyroscope(IMU_fd, GYRO_Out, Gyrometer_Calibration_Data);
        }
        else
        {
            puts("\n");
        }
        
        if(New_Acc > 0)
        {
            int8_t Poll_Acc_Status = Poll_Accelerometer(IMU_fd, ACC_Out, Accelerometer_Calibration_Data);
            FindDown(ACC_Out, DownVectorPtr);
        }
        else
        {
            puts("\n");
        }
    }
}

void INS_COMPUTE(struct timespec * const Head, struct timespec * const Tail, struct ACC_OUT * const ACC_Out, struct GYRO_OUT * const GYRO_Out, struct DownVector * const DownVectorPtr, struct ROLLING_INERTIAL_SUMS * const INS)
{

    double Delta_T = ((Tail->tv_sec)-(Head->tv_sec))+(((Tail->tv_nsec)-(Head->tv_nsec))/1e9);

    (INS->X_Rot_Pos) += ((GYRO_Out->X_Rot_Rate)*Delta_T);
    (INS->Y_Rot_Pos) += ((GYRO_Out->Y_Rot_Rate)*Delta_T);
    (INS->Z_Rot_Pos) += ((GYRO_Out->Z_Rot_Rate)*Delta_T);

    (INS->X_Lin_V) += (((ACC_Out->X_Lin_Accel)+((DownVectorPtr->DownX)*GRAVITY_ACCEL))*Delta_T);
    (INS->Y_Lin_V) += (((ACC_Out->Y_Lin_Accel)+((DownVectorPtr->DownY)*GRAVITY_ACCEL))*Delta_T);
    (INS->Z_Lin_V) += (((ACC_Out->Z_Lin_Accel)+((DownVectorPtr->DownZ)*GRAVITY_ACCEL))*Delta_T);

    (INS->X_Lin_Pos) += ((INS->X_Lin_V)*Delta_T);
    (INS->Y_Lin_Pos) += ((INS->Y_Lin_V)*Delta_T);
    (INS->Z_Lin_Pos) += ((INS->Z_Lin_V)*Delta_T);
}