#include "Attitude_Comms_GPIO.h"

    //Purpose: Sequetialy call functions to initalize the altimiter, IMU and magnetometer
    //Ingests the following values:
    //ALT: const signed integer, File handle to the altimiter I2C address
    //IMU: const signed integer, File handle to the IMU I2C address
    //MAG: const signed integer, File handle to the magnetometer I2C address
    //Altimeter_Calibration_Data: const pointer to a ALT_CAL structure, Pointer to array where all altimiter calibration values will get stored
    //Return Type: Void
    //App Notes: Make sure to pass an ALT_CAL pointer and not a ALT_OUT pointer
void Init_Attitude_Sensors(const int ALT_fd, const int IMU_fd, const int MAG_fd, struct GYRO_OUT * const GYRO_Out, struct ACC_OUT * const ACC_Out, struct ALT_CAL * const Altimeter_Calibration_Data, struct GYRO_CAL * const Gyrometer_Calibration_Data, struct ACC_CAL * const Accelerometer_Calibration_Data, struct MAG_OUT * const MAG_Out)
{
    int8_t ALT_Status = Init_ALT(ALT_fd, Altimeter_Calibration_Data);
    sleep(2);

    Dash_Line();

    int8_t IMU_Status = Init_IMU(IMU_fd);
    sleep(2);
    Zeroize_IMU(IMU_fd, GYRO_Out, ACC_Out, Gyrometer_Calibration_Data, Accelerometer_Calibration_Data);
    sleep(2);

    Dash_Line();

    int8_t MAG_Status = Init_MAG(MAG_fd);
    sleep(2);
    Run_MAG_Self_Test(MAG_fd, MAG_Out);
    sleep(2);


    Dash_Line();
}