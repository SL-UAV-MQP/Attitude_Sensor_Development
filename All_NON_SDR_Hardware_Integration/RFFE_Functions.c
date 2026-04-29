#include "Attitude_Comms_GPIO.h"    


    //Purpose: configuring the I/O mode and PU/PD mode of the GPIO pins on the MCU, spesificaly those used to control RFFE Switchs
    //Ingests the following values: (Void)
    //Return Type: Void
    //App Notes: Can only fail if setting the pin addressing type fails, this does not ensure that the individual pins were properly set as the set functions are of type void.
void RFFE_Control_Init(void)
{
    puts("\nStarting Pin configuration...");

    pinMode(ANT_SEL_P1_DISP, OUTPUT);
    pullUpDnControl(ANT_SEL_P1_DISP, PUD_DOWN);
    digitalWrite(ANT_SEL_P1_DISP, HIGH);
    printf("Pin [%u] 'ANT_SEL_P1_DISP' Configuation Checks [GOOD]\n", ANT_SEL_P1_DISP);

    pinMode(ANT_SEL_P2_DISP, OUTPUT);
    pullUpDnControl(ANT_SEL_P2_DISP, PUD_DOWN);
    digitalWrite(ANT_SEL_P2_DISP, LOW);
    printf("Pin [%u] 'ANT_SEL_P2_DISP' Configuation Checks [GOOD]\n", ANT_SEL_P2_DISP);

    pinMode(MATCHING_SEL_A_P1_DISP, OUTPUT);
    pullUpDnControl(MATCHING_SEL_A_P1_DISP, PUD_DOWN);
    digitalWrite(MATCHING_SEL_A_P1_DISP, HIGH);
    printf("Pin [%u] 'MATCHING_SEL_A_P1_DISP' Configuation Checks [GOOD]\n", MATCHING_SEL_A_P1_DISP);

    pinMode(MATCHING_SEL_A_P2_DISP, OUTPUT);
    pullUpDnControl(MATCHING_SEL_A_P2_DISP, PUD_DOWN);
    digitalWrite(MATCHING_SEL_A_P2_DISP, LOW);
    printf("Pin [%u] 'MATCHING_SEL_A_P2_DISP' Configuation Checks [GOOD]\n", MATCHING_SEL_A_P2_DISP);

    pinMode(MATCHING_SEL_B_P1_DISP, OUTPUT);
    pullUpDnControl(MATCHING_SEL_B_P1_DISP, PUD_DOWN);
    digitalWrite(MATCHING_SEL_B_P1_DISP, LOW);
    printf("Pin [%u] 'MATCHING_SEL_B_P1_DISP' Configuation Checks [GOOD]\n", MATCHING_SEL_B_P1_DISP);

    pinMode(MATCHING_SEL_B_P2_DISP, OUTPUT);
    pullUpDnControl(MATCHING_SEL_B_P2_DISP, PUD_DOWN);
    digitalWrite(MATCHING_SEL_B_P2_DISP, LOW);
    printf("Pin [%u] 'MATCHING_SEL_B_P2_DISP' Configuation Checks [GOOD]\n", MATCHING_SEL_B_P2_DISP);

    pinMode(LNA_SEL_A_P1_DISP, OUTPUT);
    pullUpDnControl(LNA_SEL_A_P1_DISP, PUD_DOWN);
    digitalWrite(LNA_SEL_A_P1_DISP, HIGH);
    printf("Pin [%u] 'LNA_SEL_A_P1_DISP' Configuation Checks [GOOD]\n", LNA_SEL_A_P1_DISP);

    pinMode(LNA_SEL_A_P2_DISP, OUTPUT);
    pullUpDnControl(LNA_SEL_A_P2_DISP, PUD_DOWN);
    digitalWrite(LNA_SEL_A_P2_DISP, LOW);
    printf("Pin [%u] 'LNA_SEL_A_P2_DISP' Configuation Checks [GOOD]\n", LNA_SEL_A_P2_DISP);

    pinMode(LNA_SEL_B_P1_DISP, OUTPUT);
    pullUpDnControl(LNA_SEL_B_P1_DISP, PUD_DOWN);
    digitalWrite(LNA_SEL_B_P1_DISP, HIGH);
    printf("Pin [%u] 'LNA_SEL_B_P1_DISP' Configuation Checks [GOOD]\n", LNA_SEL_B_P1_DISP);

    pinMode(LNA_SEL_B_P2_DISP, OUTPUT);
    pullUpDnControl(LNA_SEL_B_P2_DISP, PUD_DOWN);
    digitalWrite(LNA_SEL_B_P2_DISP, LOW);
    printf("Pin [%u] 'LNA_SEL_B_P2_DISP' Configuation Checks [GOOD]\n", LNA_SEL_B_P2_DISP);
}


    //Purpose: Selects port 1-4 on an arbitrary RF switch (1-5). Note all switches of the same type across the RFFE boards are tied together.
    //Ingests the following values:
    //Port_Enable: unsigned 8-bit int, Select a port 1-4 on the switch to select
    //Signal_Pin_1: unsigned 8-bit int, Set first control pin High or low 
    //Signal_Pin_2: unsigned 8-bit int, Set second control pin High or low 
    //Return Type: (Void)
    //App Notes: Providing a value not 1-4 decimal for Port_Enable is not valid, use of the wrong pins for a single switch will cause undefined behavior.
void Control_RF_Switch_State(uint8_t Port_Enable, uint8_t Signal_Pin_1, uint8_t Signal_Pin_2)
{
    switch(Port_Enable)
    {
        case 1:
        {
            digitalWrite(Signal_Pin_1, HIGH);
            digitalWrite(Signal_Pin_2, LOW);
            break;
        }
        case 2:
        {
            digitalWrite(Signal_Pin_1, LOW);
            digitalWrite(Signal_Pin_2, HIGH);
            break;
        }
        case 3:
        {
            digitalWrite(Signal_Pin_1, HIGH);
            digitalWrite(Signal_Pin_2, HIGH);
            break;
        }
        case 4:
        {
            digitalWrite(Signal_Pin_1, LOW);
            digitalWrite(Signal_Pin_2, LOW);
            break;
        }
        default:
        {
            puts("Requested Port Not In Range [1-4].");
        }

    }
}

    //Purpose: Sets the current antenna to bank 1 (thus disabling antenna bank 2).
    //Ingests the following values: (Void)
    //Return Type: (Void)
    //App Notes: Will change antenna port on all RFFE boards
void Antenna_Bank_1_Enable(void)
{
        //RF3
    digitalWrite(ANT_SEL_P1_DISP, HIGH);
    digitalWrite(ANT_SEL_P2_DISP, HIGH);
}

    //Purpose: Sets the current antenna to bank 2 (thus disabling antenna bank 1).
    //Ingests the following values: (Void)
    //Return Type: (Void)
    //App Notes: Will change antenna port on all RFFE boards
void Antenna_Bank_2_Enable(void)
{
        //RF4
    digitalWrite(ANT_SEL_P1_DISP, LOW);
    digitalWrite(ANT_SEL_P2_DISP, LOW);
}

    //Purpose: Sets Matching Network Switch A and B to proper potsion for 720-750 MHz matching network
    //Ingests the following values: (Void)
    //Return Type: (Void)
    //App Notes: Will change matching network on all RFFE boards
void Match_720_750_Enable(void)
{
        //RF1
    digitalWrite(MATCHING_SEL_A_P1_DISP, HIGH);
    digitalWrite(MATCHING_SEL_A_P2_DISP, LOW);

        //RF4
    digitalWrite(MATCHING_SEL_B_P1_DISP, LOW);
    digitalWrite(MATCHING_SEL_B_P2_DISP, LOW);
}

    //Purpose: Sets Matching Network Switch A and B to proper potsion for 750-800 MHz matching network
    //Ingests the following values: (Void)
    //Return Type: (Void)
    //App Notes: Will change matching network on all RFFE boards
void Match_750_800_Enable(void)
{
        //RF2
    digitalWrite(MATCHING_SEL_A_P1_DISP, LOW);
    digitalWrite(MATCHING_SEL_A_P2_DISP, HIGH);

        //RF3
    digitalWrite(MATCHING_SEL_B_P1_DISP, HIGH);
    digitalWrite(MATCHING_SEL_B_P2_DISP, HIGH);
}

    //Purpose: Sets Matching Network Switch A and B to proper potsion for 800-900 MHz matching network
    //Ingests the following values: (Void)
    //Return Type: (Void)
    //App Notes: Will change matching network on all RFFE boards
void Match_800_900_Enable(void)
{
        //RF3
    digitalWrite(MATCHING_SEL_A_P1_DISP, HIGH);
    digitalWrite(MATCHING_SEL_A_P2_DISP, HIGH);

        //RF2
    digitalWrite(MATCHING_SEL_B_P1_DISP, LOW);
    digitalWrite(MATCHING_SEL_B_P2_DISP, HIGH);
}

    //Purpose: Sets Matching Network Switch A and B to proper potsion for 900-1400 MHz matching network
    //Ingests the following values: (Void)
    //Return Type: (Void)
    //App Notes: Will change matching network on all RFFE boards
void Match_900_1400_Enable(void)
{
        //RF4
    digitalWrite(MATCHING_SEL_A_P1_DISP, LOW);
    digitalWrite(MATCHING_SEL_A_P2_DISP, LOW);

        //RF1
    digitalWrite(MATCHING_SEL_B_P1_DISP, HIGH);
    digitalWrite(MATCHING_SEL_B_P2_DISP, LOW);
}

    //Purpose: Sets LNA switch A and B to proper potsion for single LNA stage.
    //Ingests the following values: (Void)
    //Return Type: (Void)
    //App Notes: Will change amplifier staging on all RFFE boards
void Low_Amp_Enable(void)
{
        //RF2
    digitalWrite(LNA_SEL_A_P1_DISP, LOW);
    digitalWrite(LNA_SEL_A_P2_DISP, HIGH);

        //RF4
    digitalWrite(LNA_SEL_B_P1_DISP, LOW);
    digitalWrite(LNA_SEL_B_P2_DISP, LOW);
}

    //Purpose: Sets LNA switch A and B to proper potsion for cascaded LNA stage.
    //Ingests the following values: (Void)
    //Return Type: (Void)
    //App Notes: Will change amplifier staging on all RFFE boards
void High_Amp_Enable(void)
{
        //RF4
    digitalWrite(LNA_SEL_A_P1_DISP, LOW);
    digitalWrite(LNA_SEL_A_P2_DISP, LOW);

        //RF3
    digitalWrite(LNA_SEL_B_P1_DISP, HIGH);
    digitalWrite(LNA_SEL_B_P2_DISP, HIGH);
}

int8_t Get_RFFE_State(struct RFFE_STATE * const RFFE_Data)
{
    uint8_t ANT_Sel_P1_State = 0;
    uint8_t ANT_Sel_P2_State = 0;
    ANT_Sel_P1_State = (uint8_t)digitalRead(ANT_SEL_P1_DISP);
    ANT_Sel_P2_State = (uint8_t)digitalRead(ANT_SEL_P2_DISP);
    if(DEBUG ==1)
    {
        printf("Ant Sel P1: %u - Ant Sel P2: %u\n", ANT_Sel_P1_State, ANT_Sel_P2_State);
    }

    uint8_t ANT_Sel_State = ((ANT_Sel_P2_State & 0x01) << 1) | (ANT_Sel_P1_State & 0x01);
    switch(ANT_Sel_State)
    {
        case RFSW_P1_Sel:
        {
            (RFFE_Data->SW_1_Port_Sel) = 1;
            break;
        }
        case RFSW_P2_Sel:
        {
            (RFFE_Data->SW_1_Port_Sel) = 2;
            break;
        }
        case RFSW_P3_Sel:
        {
            (RFFE_Data->SW_1_Port_Sel) = 3;
            break;
        }
        case RFSW_P4_Sel:
        {
            (RFFE_Data->SW_1_Port_Sel) = 4;
            break;
        }
        default:
        {
            (RFFE_Data->SW_1_Port_Sel) = 0;
            break;
        }
    }

    uint8_t Match_Sel_A_P1_State = 0;
    uint8_t Match_Sel_A_P2_State = 0;
    Match_Sel_A_P1_State = (uint8_t)digitalRead(MATCHING_SEL_A_P1_DISP);
    Match_Sel_A_P2_State = (uint8_t)digitalRead(MATCHING_SEL_A_P2_DISP);
    if(DEBUG ==1)
    {
        printf("MatA Sel P1: %u - MatA Sel P2: %u\n", Match_Sel_A_P1_State, Match_Sel_A_P2_State);
    }

    uint8_t Match_Sel_A_State = ((Match_Sel_A_P2_State & 0x01) << 1) | (Match_Sel_A_P1_State & 0x01);
    switch(Match_Sel_A_State)
    {
        case RFSW_P1_Sel:
        {
            (RFFE_Data->SW_2_Port_Sel) = 1;
            break;
        }
        case RFSW_P2_Sel:
        {
            (RFFE_Data->SW_2_Port_Sel) = 2;
            break;
        }
        case RFSW_P3_Sel:
        {
            (RFFE_Data->SW_2_Port_Sel) = 3;
            break;
        }
        case RFSW_P4_Sel:
        {
            (RFFE_Data->SW_2_Port_Sel) = 4;
            break;
        }
        default:
        {
            (RFFE_Data->SW_2_Port_Sel) = 0;
            break;
        }
    }

    
    uint8_t Match_Sel_B_P1_State = 0;
    uint8_t Match_Sel_B_P2_State = 0;
    Match_Sel_B_P1_State = (uint8_t)digitalRead(MATCHING_SEL_B_P1_DISP);
    Match_Sel_B_P2_State = (uint8_t)digitalRead(MATCHING_SEL_B_P2_DISP);
    if(DEBUG ==1)
    {
        printf("MatB Sel P1: %u - MatB Sel P2: %u\n", Match_Sel_B_P1_State, Match_Sel_B_P2_State);
    }

    uint8_t Match_Sel_B_State = ((Match_Sel_B_P2_State & 0x01) << 1) | (Match_Sel_B_P1_State & 0x01);
    switch(Match_Sel_B_State)
    {
        case RFSW_P1_Sel:
        {
            (RFFE_Data->SW_3_Port_Sel) = 1;
            break;
        }
        case RFSW_P2_Sel:
        {
            (RFFE_Data->SW_3_Port_Sel) = 2;
            break;
        }
        case RFSW_P3_Sel:
        {
            (RFFE_Data->SW_3_Port_Sel) = 3;
            break;
        }
        case RFSW_P4_Sel:
        {
            (RFFE_Data->SW_3_Port_Sel) = 4;
            break;
        }
        default:
        {
            (RFFE_Data->SW_3_Port_Sel) = 0;
            break;
        }
    }

    uint8_t LNA_Sel_A_P1_State = 0;
    uint8_t LNA_Sel_A_P2_State = 0;
    LNA_Sel_A_P1_State = (uint8_t)digitalRead(LNA_SEL_A_P1_DISP);
    LNA_Sel_A_P2_State = (uint8_t)digitalRead(LNA_SEL_A_P2_DISP);
    if(DEBUG ==1)
    {
        printf("LNAA Sel P1: %u - LNAA Sel P2: %u\n", LNA_Sel_A_P1_State, LNA_Sel_A_P2_State);
    }

    uint8_t LNA_Sel_A_State = ((LNA_Sel_A_P2_State & 0x01) << 1) | (LNA_Sel_A_P1_State & 0x01);
    switch(LNA_Sel_A_State)
    {
        case RFSW_P1_Sel:
        {
            (RFFE_Data->SW_4_Port_Sel) = 1;
            break;
        }
        case RFSW_P2_Sel:
        {
            (RFFE_Data->SW_4_Port_Sel) = 2;
            break;
        }
        case RFSW_P3_Sel:
        {
            (RFFE_Data->SW_4_Port_Sel) = 3;
            break;
        }
        case RFSW_P4_Sel:
        {
            (RFFE_Data->SW_4_Port_Sel) = 4;
            break;
        }
        default:
        {
            (RFFE_Data->SW_4_Port_Sel) = 0;
            break;
        }
    }

    uint8_t LNA_Sel_B_P1_State = 0;
    uint8_t LNA_Sel_B_P2_State = 0;
    LNA_Sel_B_P1_State = (uint8_t)digitalRead(LNA_SEL_B_P1_DISP);
    LNA_Sel_B_P2_State = (uint8_t)digitalRead(LNA_SEL_B_P2_DISP);
    if(DEBUG ==1)
    {
        printf("LNAB Sel P1: %u - LNAB Sel P2: %u\n", LNA_Sel_B_P1_State, LNA_Sel_B_P2_State);
    }

    uint8_t LNA_Sel_B_State = 0;
    LNA_Sel_B_State = ((LNA_Sel_B_P2_State & 0x01) << 1) | (LNA_Sel_B_P1_State & 0x01);
    switch(LNA_Sel_B_State)
    {
        case RFSW_P1_Sel:
        {
            (RFFE_Data->SW_5_Port_Sel) = 1;
            break;
        }
        case RFSW_P2_Sel:
        {
            (RFFE_Data->SW_5_Port_Sel) = 2;
            break;
        }
        case RFSW_P3_Sel:
        {
            (RFFE_Data->SW_5_Port_Sel) = 3;
            break;
        }
        case RFSW_P4_Sel:
        {
            (RFFE_Data->SW_5_Port_Sel) = 4;
            break;
        }
        default:
        {
            (RFFE_Data->SW_5_Port_Sel) = 0;
            break;
        }
    }
    
    if(((RFFE_Data->SW_1_Port_Sel) < 1) || ((RFFE_Data->SW_1_Port_Sel) > 4))
    {
        return(-1);
    }
    else if(((RFFE_Data->SW_2_Port_Sel) < 1) || ((RFFE_Data->SW_2_Port_Sel) > 4))
    {
        return(-2);
    }
    else if(((RFFE_Data->SW_3_Port_Sel) < 1) || ((RFFE_Data->SW_3_Port_Sel) > 4))
    {
        return(-3);
    }
    else if(((RFFE_Data->SW_4_Port_Sel) < 1) || ((RFFE_Data->SW_4_Port_Sel) > 4))
    {
        return(-4);
    }
    else if(((RFFE_Data->SW_5_Port_Sel) < 1) || ((RFFE_Data->SW_5_Port_Sel) > 4))
    {
        return(-5);
    }
    else
    {
        return(1);
    }
} 

void Interp_RFFE_State(struct RFFE_STATE * const RFFE_Data)
{
    printf("\n\n\n----RF Front End Curent State----\n\n");
    switch(RFFE_Data->SW_1_Port_Sel)
    {
        case 1:
        {
            puts("P1: Antanna Port NOT CONNECTED");
            break;
        }
        case 2:
        {
            puts("P2: Antanna Port NOT CONNECTED");
            break;
        }
        case 3:
        {
            puts("P3: Antanna Port 1 CONNECTED");
            break;
        }
        case 4:
        {
            puts("P4: Antanna Port 2 CONNECTED");
            break;
        }
        default:
        {
            puts("P0: Antenna Port UNKNOWN");
            break;
        }
    }
    switch(RFFE_Data->SW_2_Port_Sel)
    {
        case 1:
        {
            puts("P1: Matching Network A 720MHz - 750MHz CONNECTED");
            break;
        }
        case 2:
        {
            puts("P2: Matching Network A 750MHz - 800MHz CONNECTED");
            break;
        }
        case 3:
        {
            puts("P3: Matching Network A 800MHz - 900MHz CONNECTED");
            break;
        }
        case 4:
        {
            puts("P4: Matching Network A 900MHz - 1400MHz CONNECTED");
            break;
        }
        default:
        {
            puts("P0: Matching Network A Port UNKNOWN");
            break;
        }
    }
    switch(RFFE_Data->SW_3_Port_Sel)
    {
        case 1:
        {
            puts("P1: Matching Network B 900MHz - 1400MHz CONNECTED");
            break;
        }
        case 2:
        {
            puts("P2: Matching Network B 800MHz - 900MHz CONNECTED");
            break;
        }
        case 3:
        {
            puts("P3: Matching Network B 750MHz - 800MHz CONNECTED");
            break;
        }
        case 4:
        {
            puts("P4: Matching Network B 720MHz - 750MHz CONNECTED");
            break;
        }
        default:
        {
            puts("P0: Matching Network B Port UNKNOWN");
            break;
        }
    }
    switch(RFFE_Data->SW_4_Port_Sel)
    {
        case 1:
        {
            puts("P1: Amplifier A Port NOT CONNECTED");
            break;
        }
        case 2:
        {
            puts("P2: Amplifier A Port LOW CONNECTED");
            break;
        }
        case 3:
        {
            puts("P3: Amplifier A Port NOT CONNECTED");
            break;
        }
        case 4:
        {
            puts("P4: Amplifier A Port HIGH CONNECTED");
            break;
        }
        default:
        {
            puts("P0: Amplifier Port UNKNOWN");
            break;
        }
    }
    switch(RFFE_Data->SW_5_Port_Sel)
    {
        case 1:
        {
            puts("P1: Amplifier B Port NOT CONNECTED");
            break;
        }
        case 2:
        {
            puts("P2: Amplifier B Port NOT CONNECTED");
            break;
        }
        case 3:
        {
            puts("P3: Amplifier B Port HIGH CONNECTED");
            break;
        }
        case 4:
        {
            puts("P4: Amplifier B Port LOW CONNECTED");
            break;
        }
        default:
        {
            puts("P0: Amplifier B Port UNKNOWN");
            break;
        }
    }
    printf("\n---------------------------------\n\n\n");
}