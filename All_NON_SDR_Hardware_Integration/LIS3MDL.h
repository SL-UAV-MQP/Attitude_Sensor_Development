#ifndef LIS3MDL_h
#define LIS3MDL_h

    //Address From Factory for magnetometer is 0011110b or 0x1E
#define MAG_ADDR 0x1E

    //Register to hold final axial magnetic magnitudes (yes they are signed magnitudes, suck it)
struct MAG_OUT
{
    float X_Mag_Strength;
    float Y_Mag_Strength;
    float Z_Mag_Strength;
};

    //struct for a vector that indicates north
struct NorthVector
{
    float NorthX;
    float NorthY;
    float NorthZ;
    float NorthTheta;
    float NorthPhi;
};

    //Chosen Register values for initalized registers, safer then adding them manualy and ensures program wide compatiblity.
enum LIS3MDL_REGISTER_INIT_VAL
{
            //Fire a REBOOT
    INIT_REBOOT_LIS = 0x08, // 00001000b

        //Fire a SOFT_RST
    INIT_RST_LIS = 0x04, //00000100b

        //Temp Sensor Diable, X-Y axis Ultra High Preformance Mode, 155Hz ODR, Self Test Off
    CTRL_REG1_INIT = 0x7E, //01111110b

        //Full scale mag range set to +- 4 gauss
    CTRL_REG2_INIT = 0x00, //00000000b

        //Full scale mag range set to +- 12 gauss
    //CTRL_REG2_INIT = 0x40, //01100000b

        //Set Operating mode to Full Power, SPI to 4 wire, and Sample Turn over to Continious Mode
    CTRL_REG3_INIT = 0x00, //00000000b

        //Set Zaxis to Ultra High Preformance Mode, Data to Big Endian mode to match other sensors
    CTRL_REG4_INIT = 0x0E, //00001110b

        //Disables Fast Read, Enables Block Read to avoid partial data read in errors
    CTRL_REG5_INIT = 0x40 //01000000b
};

#define SELF_TEST_MASK 0x01

    //Keep to 5, behavior above 5 is undefined
#define MAG_SELF_TEST_DURRATION 6

enum LIS3MDL_SELF_TEST_RANGE
{
    TEST_X_AXIS_MIN = 1000,
    TEST_X_AXIS_MAX = 3000,

    TEST_Y_AXIS_MIN = 1000,
    TEST_Y_AXIS_MAX = 3000,

    TEST_Z_AXIS_MIN = 100,
    TEST_Z_AXIS_MAX = 1000,
};

enum LIS3MDL_STATUS_REGISTER_MASKS
{
        //Mask to single out the status bit for XYZ registers are all new
    MAG_FULL_NEW = 0x08,

        //Mask to single out the status bit for Z register has all new data (block status read is enabled)
    MAG_Z_NEW = 0x04,

        //Mask to single out the status bit for Y registers has all new data (block status read is enabled)
    MAG_Y_NEW = 0x02,

        //Mask to single out the status bit for X registers has all new data (block status read is enabled)
    MAG_X_NEW = 0x01,

    MAG_FULL_OVERRUN = 0x80,

    MAG_Z_OVERRUN = 0x40,

    MAG_Y_OVERRUN = 0x20,

    MAG_X_OVERRUN = 0x10,

    MAG_X_POS_THRESH_EXCEED = 0x80,

    MAG_Y_POS_THRESH_EXCEED = 0x40,

    MAG_Z_POS_THRESH_EXCEED = 0x20,

    MAG_X_NEG_THRESH_EXCEED = 0x10,

    MAG_Y_NEG_THRESH_EXCEED = 0x08,

    MAG_Z_NEG_THRESH_EXCEED = 0x04,

    MAG_MEASUREMENT_OVERFLOW = 0x02
};

    //Mask to read only the FSR set bits when that register is polled to check what the FSR scale factor needs to be
#define FSR_MASK_LIS 0x60

    //FS sub-byte value for +- 4 Gauss 
#define LIS_FS_00 0x00

    //FS sub-byte value for +- 8 Gauss
#define LIS_FS_01 0x20

    //FS sub-byte value for +- 12 Gauss
#define LIS_FS_10 0x40

    //FS sub-byte value for +- 16 Gauss
#define LIS_FS_11 0x60

    //Predefined FSR scaling constants to convert from code values to real measurement values
    //+-4 Gauss FSR
#define FS_4GA 0.000146f

    //+-8 Gauss FSR
#define FS_8GA 0.000292f

    //+-12 Gauss FSR
#define FS_12GA 0.000438f

    //16+- Gauss FSR
#define FS_16GA 0.000584f

    //Aliases for all of the LIS3MDL registers
enum LIS3MDL_Register_Addresses
{
    WHO_AM_I_LIS = 0x0F,

    CTRL_REG1 = 0x20,
    CTRL_REG2 = 0x21,
    CTRL_REG3 = 0x22,
    CTRL_REG4 = 0x23,
    CTRL_REG5 = 0x24,

    STATUS_REG_LIS = 0x27,

    OUT_X_L = 0x28,
    OUT_X_H = 0x29,
    OUT_Y_L = 0x2A,
    OUT_Y_H = 0x2B,
    OUT_Z_L = 0x2C,
    OUT_Z_H = 0x2D,

    TEMP_OUT_L = 0x2E,
    TEMP_OUT_H = 0x2F,

    INT_CFG = 0x30,
    INT_SRC = 0x31,
    INT_THS_L = 0x32,
    INT_THS_H = 0x33
};

#endif