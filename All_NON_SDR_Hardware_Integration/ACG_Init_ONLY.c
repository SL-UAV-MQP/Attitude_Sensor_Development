#include "Attitude_Comms_GPIO.h"

int main()
{
        //Create varibles to store additude sensor file handles.
    int ALT_fd = 0;
    int IMU_fd = 0;
    int MAG_fd = 0;
    int XBEE_fd = 0;

    int8_t Serial_Init_Status = Init_XBee(&XBEE_fd);

        //Call function to initualize the GPIO pins for the RFFE control and generating the attitude sensor file handels.
    I2C_GPIO_ADDR_Init(&ALT_fd, &IMU_fd, &MAG_fd);

    
        //Struct for holding timing information pertinant to INS
    struct timespec Start_Of_Process_Sample, Head_Of_Process_Sample, Tail_Of_Process_Sample;

        //Make struct to store the states of the 5 RFFE Switchs, from which the RFFE state can be derived
    struct RFFE_STATE RF_Front_End_Switch_State_Log = {0,0,0,0,0};

        //Make struct to store IMU linear acceleration final values.
    struct ACC_OUT IMU_Lin_Accel_Read = {0xFFFF, 0xFFFF, 0xFFFF};

    struct ACC_CAL IMU_ACCEL_CAL_VALUES = {0x0000, 0x0000, 0x0000};
        //Make struct to store IMU rotational rate final values.
    struct GYRO_OUT IMU_Rot_Rate_Read = {0xFFFF, 0xFFFF, 0xFFFF};

    struct GYRO_CAL IMU_GYRO_CAL_VALUES = {0x0000, 0x0000, 0x0000};

        //Make struct to hold inertial location data for drift reffrence
    struct ROLLING_INERTIAL_SUMS INS_Lin_Gyro_Rolling = {LOCAL_X_ROT_POS_INIT, LOCAL_Y_ROT_POS_INIT, LOCAL_Z_ROT_POS_INIT, LOCAL_X_V_INIT, LOCAL_Y_V_INIT, LOCAL_Z_V_INIT, LOCAL_X_POS_INIT, LOCAL_Y_POS_INIT, LOCAL_Z_POS_INIT};


        //Make struct to store MAG field strengths final values.
    struct MAG_OUT Compass_Mag_Read = {0xFFFF, 0xFFFF, 0xFFFF};

        //Make struct to store ALT calibration, Factor code, and CRC values from the PROM.
    struct ALT_CAL ALTIMETER_CAL_VALUES = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        //Make struct to store ALT preasure and temprature final values.
    struct ALT_OUT Altimeter_Read = {0xFFFF, 0xFFFF};

        //Institiate structs to store the orientation
    struct DownVector DownVector = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    struct NorthVector NorthVector = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};

        //Run initalization scripts for each of the sensors, to clear and set up registers, read proms, and ensure communication is working.

    Init_Attitude_Sensors(ALT_fd, IMU_fd, MAG_fd, &IMU_Rot_Rate_Read, &IMU_Lin_Accel_Read, &ALTIMETER_CAL_VALUES, &IMU_GYRO_CAL_VALUES, &IMU_ACCEL_CAL_VALUES, &Compass_Mag_Read);
    

    puts("Initalization Completed.");
    if(clock_gettime(CLOCK_MONOTONIC, &Start_Of_Process_Sample) == -1)
    {
        printf("[WARNING] Could Not Get CLOCK_MONOTONIC Time for Start_Of_Process_Sample.");
    }
    return(0);
}