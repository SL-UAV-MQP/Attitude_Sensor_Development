#ifndef XBEE_3
#define XBEE_3

#define XBEE_MAC_ADDR "0x0013A200420633C3"

enum DEFAULT_AT_PARAMETERS
{
    SERIAL_HIGH = 0x13A200,

    SERIAL_LOW = 0x420633C3,

        //9600 Baud, 0x03 setting
    DEFAULT_BAUD = 9600,

        //no parity bits, 0x00 setting
    DEFAULT_PARITY = 0x00,

        //one stop bit, 0x00 setting
    DEFAULT_STOP_BITS = 1,

        //+, setting 0x2B
    DEFAULT_COMMAND_CHAR = '+',

        //10 seconds for command mode to time out with no futher commands, setting 0x64
    DEFUALT_COMMAND_MODE_TIMEOUT = 0x64,

        //1 second before and after command char, setting 0x3E8
    DEFAULT_GUARD_TIME = 0x3E8,

        //Pin Disabled (Used for RTS Flow Control in setting 1)
    DEFAULT_DIO6 = 0x00,

        //CTS Flow Control
    DEFUALT_DIO7 = 0x01
};

enum XBEE_3_PRO_S2C_Register_INIT_VAL
{
    COMMAND_ENTER_INIT = 0x2B,

        //In 100ms increment per byte
    COMMAND_MODE_TIMEOUT_INIT = 0x64,

        //In 1ms per byte
    COMMAND_GUARD_TIME_INIT = 0x3E8,

    COMMAND_PARITY_INIT = 0x00,

    COMMAND_STOP_BIT_INIT = 0x00,

    FLOW_CONTROL_CTS_INIT = 0x01,

    FLOW_CONTROL_RTS_INIT = 0x01,

    TRANPARENT_SERIAL_TERMINAL_MODE_INIT = 0x00,

    PAN_ID_EXTENDED_INIT = 0x906,

    ZIGBEE_RF_CHANNEL_BIT_MAP_INIT = 0x4210,

    ZIGBEE_RF_CHANNEL_SCAN_DURATION_INIT = 0x06,

    USB_DONGLE_DH_INIT = 0x13A200,

    USB_DONGLE_DL_INIT = 0x42804526,

    PRIME_BAUD_RATE_INIT = 115200,
    PRIME_BAUD_RATE_SEL_INIT = 0x07,

    SECONDARY_BAUD_RATE_INIT = 9600,
    SECONDARY_BAUD_RATE_SEL_INIT = 0x03,

    JOIN_NOTIFICATION_INIT = 0x01,

    ENDPOINT_STATUS_INIT = 0x00
};

enum AT_PARAMETERS
{
    BAUD_1200 = 0x00,
    BAUD_2400 = 0x01,
    BAUD_4800 = 0x02,
    BAUD_9600 = 0x03,
    BAUD_19200 = 0x04,
    BAUD_38400 = 0x05,
    BAUD_57600 = 0x06,
    BAUD_115200 = 0x07,
    BAUD_230400 = 0x08,
    BAUD_460800 = 0x09,
    BAUD_921600 = 0x0A,

    NO_PARITY = 0x00,
    EVEN_PARITY = 0x01,
    ODD_PARITY = 0x02,

    SINGLE_STOP_BIT = 0x00,
    DOUBLE_STOP_BIT = 0x01,

    CTS_DISABLE = 0x00,
    CTS_ENABLE = 0x01,

    RTS_DIABLE = 0x00,
    RTS_ENABLE = 0x01,

    AT_MODE = 0x00,
    API_MODE = 0x01,

    ROUTER_MODE = 0x00,
    CORDINATOR_MODE = 0x01,

    ZIGBEE_RF_CHANNEL_1 = 25,
    ZIGBEE_RF_CHANNEL_2 = 20,
    ZIGBEE_RF_CHANNEL_3 = 15,
};

    //Setting Code Alias List
#define DEST_ADDR_HIGH  "DH"
#define DEST_ADDR_LOW "DL"
#define NETWORK_ADDR_16_BIT "MY"
#define PARENT_NETWORK_ADDR_16_BIT "MP"
#define CHILDREN_REMAINING "NC"
#define SN_HIGH "SH"
#define SN_LOW "SL"
#define NODE_IDENTIFIER "NI"
#define SOURCE_ENDPOINT "SE"
#define DEST_ENDPOINT "DE"
#define CLUSTER_IDENTIFIER "CI"
#define TRANSMIT_OPTIONS "TO"
#define MAX_RF_PAYLOAD_BYTES "NP"
#define DEVICE_TYPE_IDENTIFIER "DD"
#define CONFLICT_REPORT "CR"

    //Networking Commands
#define NETWORK_COORDINATOR "CE"
#define OPERATIONS_CHANNEL "CH"
#define FORCE_DISASSOCIATION "DA"
#define PAN_ID_EXPANDED "ID"
#define OPERATION_PAN_ID_EXPANDED "OP"
#define MAX_UNICAST_HOP "NH"
#define BROADCAST_HOPS "BH"
#define OPERATIONG_PAN_ID_16_BIT "OI"
#define NODE_DISCOVERY_TIMEOUT "NT"
#define NETWORK_DSCOVERY_OPTIONS "NO"
#define CHANNELS_TO_SCAN "SC"
#define SCAN_DURATION "SD"
#define ZIGBEE_STACK_PROFILE "ZS"
#define NODE_JOIN_TIME "NJ"
#define CHANNEL_VERIFICATION "JV"
#define NETWORK_WATCHDOG_TIMEOUT "NW"
#define JOIN_NOTIF "JN"
#define AGGREGATE_ROUTING_NOTIF "AR"
#define JOIN_DISABLE "DJ"
#define INITIAL_ID "II"

    //Security Commands
#define ENABLE_ENCRYPTION "EE"
#define ENCRYPTION_OPTIONS "EO"
#define NETWORK_ENCRYPTION_KEY "NK"
#define LINK_KEY "KY"

    //RF Interface Commands
#define POWER_LEVEL "PL"
#define POWER_MODE "PM"
#define RSS "DB"
#define PEAK_POWER "PP"

    //Serial Interface Commands
#define API_ENABLE "AP"
#define API_OPTIONS "AO"
#define BAUD_RATE "BD"
#define SERIAL_PARITY "NB"
#define STOP_BITS "SB"
#define PACKETIZATION_TIMEOUT "RO"

    //I/O Commands
#define IO_SAMPLE_RATE "IR"
#define IO_DIGITAL_CHANNEL_DETECT "IC"
#define DIO0_CONFIG "D0"
#define DIO1_CONFIG "D1"
#define DIO2_CONFIG "D2"
#define DIO3_CONFIG "D3"
#define DIO4_CONFIG "D4"
#define DIO5_CONFIG "D5"
    //RTS Pin
#define DIO6_CONFIG "D6"
    //CTS Pin
#define DIO7_CONFIG "D7"
#define PMW0_CONFIG "P0"
#define DIO11_CONFIG "P1"
#define DIO12_CONFIG "P2"
#define DIO13_CONFIG "P3"
#define ASSOCIEATION_LED_BLINK_TIME "LT"
#define PULL_UP_RESISTOR_MODE_SEL "PR"
#define RSSI_PWM_TIMER "RP"
#define MODUAL_TEMPERATURE "TP"

    //Dignostic Commands
#define FIRMWARE_VERSION "VR"
#define HARDWARE_VERSION "HV"
#define ASSOCIATION_INDICATION "AI"

    //AT Mode Commands
#define COMMAND_MODE_TIMEOUT "CT"
#define EXIT_COMMAND_MODE "CN"
#define GUARD_TIME "GT"
#define COMMAND_SEQUENCE_CHARACTER "CC"

    //Sleep Commands
#define SLEEP_MODE "SM"
#define SLEEP_PERIOD_COUNT "SN"
#define SLEEP_PERIOD "SP"
#define TIME_BEFORE_SLEEP "ST"
#define SLEEP_OPTIONS "SO"
#define WAKE_HOST "WH"
#define SLEEP_NOW "SI"
#define POLLING_RATE "PO"

    //Excution Commands
#define APPLY_CHANGES "AC"
#define WRITE_CHANGES_TO_NV_MEMORY "WR"
#define RESTORE_DEFAULTS "RE"
#define SOFTWARE_RESET "FR"
#define NETWORK_RESET "NR"
#define COMMISSIONING_PUSHBUTTON "CB"
#define NODE_DISCOVER "ND"
#define DEST_NODE "DN"
#define FORCE_SAMPLE_ALL_PINS "IS"
#define XBEE_SENSOR_SAMPLE "1S"
#define ACTIVE_SCAN "AS"

 
    //Measured in nibbles (singluar hex charcters) not bytes
enum MAX_PARAMETER_SIZE
{
        //Networking Commands
    CH_MAX = 2,
    ID_MAX = 16,
    OP_MAX = 16,
    OI_MAX = 4, 
    SC_MAX = 4,
    SD_MAX = 1,
    ZS_MAX = 1,
    NJ_MAX = 2,
    JV_MAX = 1,
    NW_MAX = 4,
    JN_MAX = 1,
    II_MAX = 4,
    ED_MAX = 2,
    NC_MAX = 2,
    CE_MAX = 1,
    DO_MAX = 2,
    DC_MAX = 4,

    //AT Addressing Commands
    SH_MAX = 8,
    SL_MAX = 8,
    MY_MAX = 4,
    MP_MAX = 4,
    DH_MAX = 8,
    DL_MAX = 8,

        //DANGER - Exceeds the maximum storage of a uint64_t unless masked
    NI_MAX = 40,
    NH_MAX = 2,
    BH_MAX = 2,
    AR_MAX = 2,
    DD_MAX = 2,
    NT_MAX = 2,
    NO_MAX = 1,
    NP_MAX = 4,
    CR_MAX = 4,

        //Zigbee Addressing Commands
    SE_MAX = 2,
    DE_MAX = 2,
    CI_MAX = 4,
    TO_MAX = 2,

        //RF Interface Commands
    PL_MAX = 1,
    PP_MAX = 2,
    PM_MAX = 1,

        //Security Commands
    EE_MAX = 1, 
    EO_MAX = 2,
        //DANGER - Exceeds the maximum storace of uint64_t and CANNOT BE MASKED
    KY_MAX = 32,
        //DANGER - Exceeds the maximum storace of uint64_t and CANNOT BE MASKED
    NK_MAX = 32,

        //Serial Interface Commands
    BD_MAX = 1, 
    NB_MAX = 1,
    SB_MAX = 1,
    RO_MAX = 2,
    AP_MAX = 1,
    AO_MAX = 1,

        //Command Mode Options
    CT_MAX = 3,
    GT_MAX = 4,
    CC_MAX = 2,
    CN_MAX = 0,

        //Sleep Commands
    SP_MAX = 3,
    SN_MAX = 4,
    SM_MAX = 1,
    ST_MAX = 4,
    SO_MAX = 2,
    WH_MAX = 4,
    PO_MAX = 3,

        //I/O Commands
    D0_MAX = 1,
    D1_MAX = 1,
    D2_MAX = 1,
    D3_MAX = 1,
    D$_MAX = 1,
    D5_MAX = 1,
    //RTS Pin
    D6_MAX = 1,
        //CTS Pin
    D7_MAX = 1,
    D8_MAX = 1,
    D9_MAX = 1,
    P0_MAX = 1,
    P1_MAX = 1,
    P2_MAX = 1,
    P3_MAX = 1,
    P4_MAX = 1,
    P5_MAX = 1,
    P6_MAX = 1,
    P7_MAX = 1,
    P8_MAX = 1,
    P9_MAX = 1,
    PR_MAX = 4,
    PD_MAX = 4,
    LT_MAX = 2,
    RP_MAX = 2,

        //I/O Sampling
    IR_MAX = 4,
    IC_MAX = 4,

        //Dignostic Commands
    VR_MAX = 4,
    HV_MAX = 4,
    AI_MAX = 2,
    DB_MAX = 2,
    TP_MAX = 4,

        //Excution Commands
    AC_MAX = 0,
    AS_MAX = 1,
    WP_MAX = 0,
    RE_MAX = 0,
    FR_MAX = 0,
    NR_MAX = 1,
    SI_MAX = 0,
    CB_MAX = 1,
    ND_MAX = 1,
        //DANGER - Exceeds the maximum storage of a uint64_t unless masked
    DN_MAX = 40,
    DJ_MAX = 1,
    IS_MAX = 0
};

#endif