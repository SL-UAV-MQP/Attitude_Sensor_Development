#include "I2C_Test.h"

int main()
{
        //Create varibles to store additude sensor file handles.
    int ALT_fd = 0;
    int IMU_fd = 0;
    int MAG_fd = 0;

        //Call function to initualize the GPIO pins for the RFFE control and generating the attitude sensor file handels.
    I2C_GPIO_ADDR_Init(&ALT_fd, &IMU_fd, &MAG_fd);

        //Make struct to store IMU linear acceleration final values.
    struct ACC_OUT IMU_Lin_Accel_Read = {0xFFFF, 0xFFFF, 0xFFFF};
        
        //Make struct to hold the calibration data for the IMU acceleration values
    struct ACC_CAL IMU_ACCEL_CAL_VALUES = {0x0000, 0x0000, 0x0000};
        
        //Make struct to store IMU rotational rate final values.
    struct GYRO_OUT IMU_Rot_Rate_Read = {0xFFFF, 0xFFFF, 0xFFFF};
        
        //Make struct to hold the calibration data for the IMU gyrometer values
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
            //Wait one sec at end of system setup.
        sleep(5);
    }

        //Loop Forever.
    uint64_t Cycle_Rate = 50000;
    while(DEBUG == 0)
    {
            //Clear terminal screen.
        system("clear");
            //Run Altimeter and get temprature and preasure final values and print to terminal.
        Run_Altimeter(ALT_fd, &ALTIMETER_CAL_VALUES, &Altimeter_Read);
            //Poll IMU for new temp, rot and linear values and print to terminal.
        Run_IMU(IMU_fd, &IMU_Rot_Rate_Read, &IMU_Lin_Accel_Read, &IMU_GYRO_CAL_VALUES, &IMU_ACCEL_CAL_VALUES, &DownVector);
            //Read the magnetometer
        Run_MAG(MAG_fd, &Compass_Mag_Read, &DownVector, &NorthVector);

        INS_COMPUTE(Cycle_Rate, &IMU_Lin_Accel_Read, &IMU_Rot_Rate_Read, &DownVector, &INS_Lin_Gyro_Rolling);

        printf("Altimiter TPA    | [%.4f C , %.3f Bar , %.3f m]\n", (float)(Altimeter_Read.Temperature)/100, (float)(Altimeter_Read.Preasure)/100000, (float)(Altimeter_Read.Altitude));
          puts("                 |");
        printf("IMU Gyro         | [%+.6f , %+.6f , %+.6f] Deg/s\n", (IMU_Rot_Rate_Read.X_Rot_Rate)/1000, (IMU_Rot_Rate_Read.Y_Rot_Rate)/1000, (IMU_Rot_Rate_Read.Z_Rot_Rate)/1000);
        printf("IMU Gyro         | [%+.6f , %+.6f , %+.6f] Deg\n", (INS_Lin_Gyro_Rolling.X_Rot_Pos)/1000, (INS_Lin_Gyro_Rolling.Y_Rot_Pos)/1000, (INS_Lin_Gyro_Rolling.Z_Rot_Pos)/1000);
          puts("                 |");
        //printf("IMU Raw Accel    | [%+.6f ,  %+.6f ,  %+.6f] m/s^2\n", (IMU_Lin_Accel_Read.X_Lin_Accel), (IMU_Lin_Accel_Read.Y_Lin_Accel), (IMU_Lin_Accel_Read.Z_Lin_Accel));
        printf("IMU G-Comp Accel | [%+.6f , %+.6f , %+.6f] m/s^2\n", (IMU_Lin_Accel_Read.X_Lin_Accel)+((DownVector.DownX)*GRAVITY_ACCEL), (IMU_Lin_Accel_Read.Y_Lin_Accel)+((DownVector.DownY)*GRAVITY_ACCEL), (IMU_Lin_Accel_Read.Z_Lin_Accel)+((DownVector.DownZ)*GRAVITY_ACCEL));
        printf("IMU G-Comp Accel | [%+.6f , %+.6f , %+.6f] m/s\n", (INS_Lin_Gyro_Rolling.X_Lin_V), (INS_Lin_Gyro_Rolling.Y_Lin_V), (INS_Lin_Gyro_Rolling.Z_Lin_V));
        printf("IMU G-Comp Accel | [%+.6f , %+.6f , %+.6f] m\n", (INS_Lin_Gyro_Rolling.X_Lin_Pos), (INS_Lin_Gyro_Rolling.Y_Lin_Pos), (INS_Lin_Gyro_Rolling.Z_Lin_Pos));
          puts("                 |");

        float Down_Direction_Magnitude = hypot((DownVector.DownX), hypot((DownVector.DownY) , (DownVector.DownZ)));
        printf("Down XYZ         | [%+.6f , %+.6f , %+.6f]\n", (DownVector.DownX), (DownVector.DownY), (DownVector.DownZ));
        printf("Down RTP         | [%+.6lf] [%+.6f , %+.6f] Rad\n", Down_Direction_Magnitude, DownVector.DownTheta, DownVector.DownPhi);
          puts("                 |"); 
        printf("MAG              | [%+.6f , %+.6f , %+.6f] G\n", (Compass_Mag_Read.X_Mag_Strength), (Compass_Mag_Read.Y_Mag_Strength), (Compass_Mag_Read.Z_Mag_Strength));
          puts("                 |");

        float North_Direction_Magnitude = hypot((NorthVector.NorthX), hypot((NorthVector.NorthY), (NorthVector.NorthZ)));
        printf("North XYZ        | [%+.6f , %+.6f , %+.6f]\n", (NorthVector.NorthX), (NorthVector.NorthY), (NorthVector.NorthZ));
        printf("North RTP        | [%+.6lf] [%+.6f , %+.6f] Rad\n", North_Direction_Magnitude, atan2((NorthVector.NorthY), (NorthVector.NorthX)), acos(((NorthVector.NorthZ)/North_Direction_Magnitude)));

            //Wait for Cycle_Rate micro seconds (50ms).
        usleep(Cycle_Rate);
    }

    switch(DEBUG)
    {
        case 1:
        {
            while(1)
            {
                system("clear");
                Run_Altimeter(ALT_fd, &ALTIMETER_CAL_VALUES, &Altimeter_Read);
                printf("Real Temperature Read: %.3f C \nReal Pressure Read: %.3f Bar \nComputed Altitude: %.3f m\n", (float)(Altimeter_Read.Temperature)/100, (float)(Altimeter_Read.Preasure)/100000, (float)(Altimeter_Read.Altitude));
                usleep(Cycle_Rate);
            }
            break;
        }
        case 2:
        {
            Run_IMU(IMU_fd, &IMU_Rot_Rate_Read, &IMU_Lin_Accel_Read, &IMU_GYRO_CAL_VALUES, &IMU_ACCEL_CAL_VALUES, &DownVector);
            break;
        }
        case 3:
        {
            while(1)
            {
                system("clear");
                Run_MAG(MAG_fd, &Compass_Mag_Read, &DownVector, &NorthVector);
                printf("MAG              | [%+.6f , %+.6f , %+.6f] G\n", (Compass_Mag_Read.X_Mag_Strength), (Compass_Mag_Read.Y_Mag_Strength), (Compass_Mag_Read.Z_Mag_Strength));
                usleep(Cycle_Rate);
            }
            break;
        }
    };
    return(0);
}