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
    
    if(DEBUG == 0)
    {
        serialPuts(XBEE_fd, "Prepare For Data Stream In 5 Seconds.\n");
            //Wait five sec at end of system setup.
        sleep(5);
        system("clear");
        puts("Entering Main Process Loop...");
    }
    if(clock_gettime(CLOCK_MONOTONIC, &Start_Of_Process_Sample) == -1)
    {
        printf("[WARNING] Could Not Get CLOCK_MONOTONIC Time for Start_Of_Process_Sample.");
    }
    if(clock_gettime(CLOCK_MONOTONIC_RAW, &Head_Of_Process_Sample) == -1)
    {
        printf("[WARNING] Could Not Get CLOCK_MONOTONIC Time for Head_Of_Process_Sample.");
    }
        //Loop Forever.

/*
    char Telemetry_Header_Data[512] = {0};
    char Altimiter_Readout[512] = {0};
    char IMU_Gyro_Rate_Readout[512] = {0};
    char IMU_Gyro_Pos_Readout[512] = {0};
    char IMU_GComp_Accel_Readout[512] = {0};
    char IMU_GComp_V_Readout[512] = {0};
    char IMU_GComp_Pos_Readout[512] = {0};
    char IMU_Down_Readout[512] = {0};
    char Magnetometer_Readout[512] = {0};
    char MAG_North_Readout[512] = {0};
*/

    uint64_t Cycle_Stamp = 0;
    uint64_t Cycle_Rate = 200000;
    while(DEBUG == 0)
    {
            //Clear terminal screen.
        //system("clear");
        Cycle_Stamp++;
            //Run Altimeter and get temprature and preasure final values and print to terminal.
        Run_Altimeter(ALT_fd, &ALTIMETER_CAL_VALUES, &Altimeter_Read);
            //Poll IMU for new temp, rot and linear values and print to terminal.
        Run_IMU(IMU_fd, &IMU_Rot_Rate_Read, &IMU_Lin_Accel_Read, &IMU_GYRO_CAL_VALUES, &IMU_ACCEL_CAL_VALUES, &DownVector);
            //Read the magnetometer
        Run_MAG(MAG_fd, &Compass_Mag_Read, &DownVector, &NorthVector);
        
        if(clock_gettime(CLOCK_MONOTONIC_RAW, &Tail_Of_Process_Sample) == -1)
        {
            printf("[WARNING] Could Not Get CLOCK_MONOTONIC Time for Tail_Of_Process_Sample.");
        }
        
        INS_COMPUTE(&Head_Of_Process_Sample, &Tail_Of_Process_Sample, &IMU_Lin_Accel_Read, &IMU_Rot_Rate_Read, &DownVector, &INS_Lin_Gyro_Rolling);
        
        if(clock_gettime(CLOCK_MONOTONIC_RAW, &Head_Of_Process_Sample) == -1)
        {
            printf("[WARNING] Could Not Get CLOCK_MONOTONIC Time for Head_Of_Process_Sample.");
        }

        PrintTelemetry(XBEE_fd, Cycle_Stamp, &Start_Of_Process_Sample, &Tail_Of_Process_Sample, &Altimeter_Read, &IMU_Lin_Accel_Read, &IMU_Rot_Rate_Read, &INS_Lin_Gyro_Rolling,  &DownVector, &NorthVector);

        /*
        snprintf(Telemetry_Header_Data, sizeof(Telemetry_Header_Data), "Telemetry Time Stamp [%.lf ms]\n", (double)((Tail_Of_Process_Sample.tv_nsec)-(Head_Of_Process_Sample.tv_nsec)/1e6));
        
        snprintf(Altimiter_Readout, sizeof(Altimiter_Readout), "Altimiter TPA    | [%.4f C , %.3f Bar , %.3f m]\n", (float)(Altimeter_Read.Temperature)/100, (float)(Altimeter_Read.Preasure)/100000, (float)(Altimeter_Read.Altitude));
        
        snprintf(IMU_Gyro_Rate_Readout, sizeof(IMU_Gyro_Rate_Readout), "IMU Gyro         | [%+.3f , %+.3f , %+.3f] mDeg/s\n", (IMU_Rot_Rate_Read.X_Rot_Rate), (IMU_Rot_Rate_Read.Y_Rot_Rate), (IMU_Rot_Rate_Read.Z_Rot_Rate));
        snprintf(IMU_Gyro_Pos_Readout, sizeof(IMU_Gyro_Pos_Readout), "IMU Gyro         | [%+.3f , %+.3f , %+.3f] mDeg\n", (INS_Lin_Gyro_Rolling.X_Rot_Pos), (INS_Lin_Gyro_Rolling.Y_Rot_Pos), (INS_Lin_Gyro_Rolling.Z_Rot_Pos));

        snprintf(IMU_GComp_Accel_Readout, sizeof(IMU_GComp_Accel_Readout), "IMU G-Comp Accel | [%+.6f , %+.6f , %+.6f] m/s^2\n", (IMU_Lin_Accel_Read.X_Lin_Accel)+((DownVector.DownX)*GRAVITY_ACCEL), (IMU_Lin_Accel_Read.Y_Lin_Accel)+((DownVector.DownY)*GRAVITY_ACCEL), (IMU_Lin_Accel_Read.Z_Lin_Accel)+((DownVector.DownZ)*GRAVITY_ACCEL));
        snprintf(IMU_GComp_V_Readout, sizeof(IMU_GComp_V_Readout), "IMU G-Comp Accel | [%+.6f , %+.6f , %+.6f] m/s\n", (INS_Lin_Gyro_Rolling.X_Lin_V), (INS_Lin_Gyro_Rolling.Y_Lin_V), (INS_Lin_Gyro_Rolling.Z_Lin_V));
        snprintf(IMU_GComp_Pos_Readout, sizeof(IMU_GComp_Pos_Readout), "IMU G-Comp Accel | [%+.6f , %+.6f , %+.6f] m\n", (INS_Lin_Gyro_Rolling.X_Lin_Pos), (INS_Lin_Gyro_Rolling.Y_Lin_Pos), (INS_Lin_Gyro_Rolling.Z_Lin_Pos));

        float Down_Direction_Magnitude = hypot((DownVector.DownX), hypot((DownVector.DownY) , (DownVector.DownZ)));
        snprintf(IMU_Down_Readout, sizeof(IMU_Down_Readout), "Down RTP         | [%+.6lf] [%+.6f , %+.6f] Deg\n",  Down_Direction_Magnitude, (double)(DownVector.DownTheta*IMU_RAD_TO_DEG), (double)(DownVector.DownPhi*IMU_RAD_TO_DEG));
        
        float North_Direction_Magnitude = hypot((NorthVector.NorthX), hypot((NorthVector.NorthY), (NorthVector.NorthZ)));
        snprintf(Magnetometer_Readout, sizeof(Magnetometer_Readout), "MAG              | [%+.6f , %+.6f , %+.6f] G\n", (Compass_Mag_Read.X_Mag_Strength), (Compass_Mag_Read.Y_Mag_Strength), (Compass_Mag_Read.Z_Mag_Strength));
        snprintf(MAG_North_Readout, sizeof(MAG_North_Readout), "North RTP        | [%+.6lf] [%+.6f , %+.6f] Deg\n", North_Direction_Magnitude, (double)(atan2((NorthVector.NorthY), (NorthVector.NorthX))*IMU_RAD_TO_DEG), (double)(acos(((NorthVector.NorthZ)/North_Direction_Magnitude))*IMU_RAD_TO_DEG));

        printf("%s", Telemetry_Header_Data);
        serialPuts(XBEE_fd, Telemetry_Header_Data);
        memset(Telemetry_Header_Data, '\0', sizeof(Telemetry_Header_Data));

        printf("%s", Altimiter_Readout);
        serialPuts(XBEE_fd, Altimiter_Readout);
        memset(Altimiter_Readout, '\0', sizeof(Altimiter_Readout));

        printf("%s", IMU_Gyro_Rate_Readout);
        serialPuts(XBEE_fd, IMU_Gyro_Rate_Readout);
        memset(IMU_Gyro_Rate_Readout, '\0', sizeof(IMU_Gyro_Rate_Readout));

        printf("%s", IMU_Gyro_Pos_Readout);
        serialPuts(XBEE_fd, IMU_Gyro_Pos_Readout);
        memset(IMU_Gyro_Pos_Readout, '\0', sizeof(IMU_Gyro_Pos_Readout));

        printf("%s", IMU_GComp_Accel_Readout);
        serialPuts(XBEE_fd, IMU_GComp_Accel_Readout);
        memset(IMU_GComp_Accel_Readout, '\0', sizeof(IMU_GComp_Accel_Readout));

        printf("%s", IMU_GComp_V_Readout);
        serialPuts(XBEE_fd, IMU_GComp_V_Readout);
        memset(IMU_GComp_V_Readout, '\0', sizeof(IMU_GComp_V_Readout));

        printf("%s", IMU_GComp_Pos_Readout);
        serialPuts(XBEE_fd, IMU_GComp_Pos_Readout);
        memset(IMU_GComp_Pos_Readout, '\0', sizeof(IMU_GComp_Pos_Readout));

        printf("%s", IMU_Down_Readout);
        serialPuts(XBEE_fd, IMU_Down_Readout);
        memset(IMU_Down_Readout, '\0', sizeof(IMU_Down_Readout));
        
        printf("%s", Magnetometer_Readout);
        serialPuts(XBEE_fd, Magnetometer_Readout);
        memset(Magnetometer_Readout, '\0', sizeof(Magnetometer_Readout));

        printf("%s",MAG_North_Readout);
        serialPuts(XBEE_fd, MAG_North_Readout);
        memset(MAG_North_Readout, '\0', sizeof(MAG_North_Readout));

        serialPuts(XBEE_fd, "\r\n");
        */

        //Wait for Cycle_Rate micro seconds (50ms).
        usleep(Cycle_Rate);
    }
    return(0);
}