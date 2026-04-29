#include "Attitude_Comms_GPIO.h"

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

//inputs: xbee address, cycle number, cycle rate, structs for: altimeter read, down vector, motion vectors, north vector, coordinates from localization code
//outputs prints all this information to the Xbee serial connection and a file
void PrintTelemetry(int XBEE_fd, uint64_t CycleStamp, struct timespec * const Start, struct timespec * const Tail, struct ALT_OUT * const AltimeterRead, struct ACC_OUT * const IMU_Lin_Accel_Read, struct GYRO_OUT * const IMU_Rot_Rate_Read, struct ROLLING_INERTIAL_SUMS * const INS_Lin_Gyro_Rolling, struct DownVector * const DownVector, struct NorthVector * const NorthVector)
{
        //declare fixed-size strings since we want to keep the total data sent in a cycle small
    char Telemetry_Header_Data[50] = {0};

    //char Latitude_Readout[50] = {0};
    //char Longitude_Readout[50] = {0};

    char Altimeter_Readout[50] = {0};

    char IMU_GComp_Pos_Readout[50] = {0};
    char IMU_GComp_V_Readout[50] = {0};
    char IMU_GComp_Accel_Readout[50] = {0};

    char IMU_Gyro_Pos_Readout[50] = {0};
    char IMU_Gyro_Rate_Readout[50] = {0};

    char MAG_North_Readout[50] = {0};

        //calculate this before the snprintfs for readability
    float North_Direction_Magnitude = hypot((NorthVector->NorthX), hypot((NorthVector->NorthY), (NorthVector->NorthZ)));
    uint64_t Time_Since_Main_Process_Start = (uint64_t)((((Tail->tv_sec)-(Start->tv_sec))*1000.0)+(((Tail->tv_nsec)-(Start->tv_nsec))/1000000.0));
        //make all the strings
    snprintf(Telemetry_Header_Data, sizeof(Telemetry_Header_Data), "Time/Cycle|[%lu] %lu ms\n", CycleStamp, Time_Since_Main_Process_Start);
    
    //snprintf(Latitude_Readout, sizeof(Latitude_Readout), "Lat|%.4f", LatitudeIn) commented out until we have those structs ready
    //snprintf(Longitude_Readout, sizeof(Longitude_Readout), "Lon|%.4f", LongitudeIn)
    
    snprintf(Altimeter_Readout, sizeof(Altimeter_Readout), "Alt|%.3f\n", (float)(AltimeterRead->Altitude));    
    
    snprintf(IMU_GComp_Pos_Readout, sizeof(IMU_GComp_Pos_Readout), "Pos|%+.3f,%+.3f,%+.3f\n", (INS_Lin_Gyro_Rolling->X_Lin_Pos), (INS_Lin_Gyro_Rolling->Y_Lin_Pos), (INS_Lin_Gyro_Rolling->Z_Lin_Pos));
    snprintf(IMU_GComp_V_Readout, sizeof(IMU_GComp_V_Readout), "Vel|%+.3f,%+.3f,%+.3f\n", (INS_Lin_Gyro_Rolling->X_Lin_V), (INS_Lin_Gyro_Rolling->Y_Lin_V), (INS_Lin_Gyro_Rolling->Z_Lin_V));
    snprintf(IMU_GComp_Accel_Readout, sizeof(IMU_GComp_Accel_Readout), "Acc|%+.3f,%+.3f,%+.3f\n", (IMU_Lin_Accel_Read->X_Lin_Accel)+((DownVector->DownX)*GRAVITY_ACCEL), (IMU_Lin_Accel_Read->Y_Lin_Accel)+((DownVector->DownY)*GRAVITY_ACCEL), (IMU_Lin_Accel_Read->Z_Lin_Accel)+((DownVector->DownZ)*GRAVITY_ACCEL));
    
    snprintf(IMU_Gyro_Pos_Readout, sizeof(IMU_Gyro_Pos_Readout), "Angle|%+.3f,%+.3f,%+.3f\n", (INS_Lin_Gyro_Rolling->X_Rot_Pos)/1e3, (INS_Lin_Gyro_Rolling->Y_Rot_Pos)/1e3, (INS_Lin_Gyro_Rolling->Z_Rot_Pos)/1e3);
    snprintf(IMU_Gyro_Rate_Readout, sizeof(IMU_Gyro_Rate_Readout), "Spin|%+.3f,%+.3f,%+.3f\n", (IMU_Rot_Rate_Read->X_Rot_Rate)/1e3, (IMU_Rot_Rate_Read->Y_Rot_Rate)/1e3, (IMU_Rot_Rate_Read->Z_Rot_Rate)/1e3);
    
    snprintf(MAG_North_Readout, sizeof(MAG_North_Readout), "North|%+.3f,%+.3f,%+.3f\n", North_Direction_Magnitude, (double)(atan2((NorthVector->NorthY), (NorthVector->NorthX))*IMU_RAD_TO_DEG), (double)(acos(((NorthVector->NorthZ)/North_Direction_Magnitude))*IMU_RAD_TO_DEG));

    ssize_t Bytes_In_Buff  = 0;
    ioctl(XBEE_fd, TIOCOUTQ, &Bytes_In_Buff);
    printf("UART Buffer Contains [%lu] Bytes.\n", Bytes_In_Buff);


        //send the strings to the Xbee
    int16_t Telemetry_Header_Data_Status =  Serial_Puts_CTSRTS_Safe(XBEE_fd, Telemetry_Header_Data, (FLAGS | O_FORCE | O_FLUSH));
    if(Telemetry_Header_Data_Status < 0)
    {
        printf("[WARNING] Telemetry [%lu] Failed To Send In Full.\n", CycleStamp);
    }
    //int16_t Latitude_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, Latitude_Readout, (FLAGS | O_FORCE | O_FLUSH));
    //int16_t Longitude_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, Longitude_Readout, (FLAGS | O_FORCE | O_FLUSH));
    
    int16_t Altimeter_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, Altimeter_Readout, ((FLAGS | O_FORCE) & ~O_FLUSH));
    if(Altimeter_Readout_Status < 0)
    {
        printf("[WARNING] Altimiter [%lu] Failed To Send In Full.\n", CycleStamp);
    }
    
    int16_t IMU_GComp_Pos_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, IMU_GComp_Pos_Readout, ((FLAGS | O_FORCE) & ~O_FLUSH));
    if(IMU_GComp_Pos_Readout_Status < 0)
    {
        printf("[WARNING] IMU GComp Position [%lu] Failed To Send In Full.\n", CycleStamp);
    }

    int16_t IMU_GComp_V_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, IMU_GComp_V_Readout, (FLAGS & ~O_FORCE & ~O_FLUSH));
    if(IMU_GComp_V_Readout_Status < 0)
    {
        printf("[WARNING] IMU GComp Velocity [%lu] Failed To Send In Full.\n", CycleStamp);
    }

    int16_t IMU_GComp_Accel_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, IMU_GComp_Accel_Readout, (FLAGS & ~O_FORCE & ~O_FLUSH));
    if(IMU_GComp_Accel_Readout_Status < 0)
    {
        printf("[WARNING] GComp Acceleration [%lu] Failed To Send In Full.\n", CycleStamp);
    }
    
    int16_t IMU_Gyro_Pos_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, IMU_Gyro_Pos_Readout, ((FLAGS | O_FORCE) & ~O_FLUSH));
    if(IMU_Gyro_Pos_Readout_Status < 0)
    {
        printf("[WARNING] Gyro Position [%lu] Failed To Send In Full.\n", CycleStamp);
    }

    int16_t IMU_Gyro_Rate_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, IMU_Gyro_Rate_Readout, (FLAGS & ~O_FORCE & ~O_FLUSH));
    if(IMU_Gyro_Rate_Readout_Status < 0)
    {
        printf("[WARNING] Gyro Rate [%lu] Failed To Send In Full.\n", CycleStamp);
    }
    
    int16_t MAG_North_Readout_Status = Serial_Puts_CTSRTS_Safe(XBEE_fd, MAG_North_Readout, (FLAGS | O_FORCE | O_FLUSH));
    if(MAG_North_Readout_Status < 0)
    {
        printf("[WARNING] North Heading [%lu] Failed To Send In Full.\n", CycleStamp);
    }
    serialPuts(XBEE_fd, "\r\n");

/*
    serialPuts(XBEE_fd, Telemetry_Header_Data);
    serialPuts(XBEE_fd, Altimeter_Readout);
    serialPuts(XBEE_fd, IMU_Gyro_Rate_Readout);
    serialPuts(XBEE_fd, IMU_Gyro_Pos_Readout);
    serialPuts(XBEE_fd, IMU_GComp_Accel_Readout);
    serialPuts(XBEE_fd, IMU_GComp_V_Readout);
    serialPuts(XBEE_fd, IMU_GComp_Pos_Readout);
    serialPuts(XBEE_fd, MAG_North_Readout);
    serialPuts(XBEE_fd, "\r\n");

    //Reasearch has indicated it is not nessisary to memset to overwrite the contents of the arrays as they immedieatly go out of scope once printed and thus are not relivant there after.

    memset(Telemetry_Header_Data, '\0', sizeof(Telemetry_Header_Data));
    memset(Altimeter_Readout, '\0', sizeof(Altimeter_Readout));
    memset(IMU_Gyro_Rate_Readout, '\0', sizeof(IMU_Gyro_Rate_Readout));
    memset(IMU_Gyro_Pos_Readout, '\0', sizeof(IMU_Gyro_Pos_Readout));
    memset(IMU_GComp_Accel_Readout, '\0', sizeof(IMU_GComp_Accel_Readout));
    memset(IMU_GComp_V_Readout, '\0', sizeof(IMU_GComp_V_Readout));
    memset(IMU_GComp_Pos_Readout, '\0', sizeof(IMU_GComp_Pos_Readout));
    memset(MAG_North_Readout, '\0', sizeof(MAG_North_Readout));
*/
}