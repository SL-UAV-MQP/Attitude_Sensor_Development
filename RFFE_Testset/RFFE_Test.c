#include "RFFE.h"

int main()
{
    GPIO_Init();

    struct RFFE_STATE RF_Front_End_Switch_State_Log = {0,0,0,0,0};

     Get_RFFE_State(&RF_Front_End_Switch_State_Log);

    uint Switch_Sel = 0;
    uint Port_Sel = 0;
    uint State_Sel = 0;
    uint Test_Mode = 0;
    while(1)
    {
        //system("clear");
        puts("\n\n\n");
        Interp_RFFE_State(&RF_Front_End_Switch_State_Log);
        puts("Select Test Mode:\n1: RFFE State Select\n2: Switch and Port Select\n\n");
        printf("Type Selection Here And Hit Enter: ");
        scanf("%u", &Test_Mode);

        switch(Test_Mode)
        {
            case 1:
            {
                system("clear");
                printf("Select An Operating State\n");
                printf("1: Antenna 1\n2: Antenna 2\n3: Match 720-750\n4: Match 750-800\n5: Match 800-900\n6: Match 900-1400\n7: Amp Low\n8: Amp High\n\n");
                printf("Type Selection Here And Hit Enter: ");
                scanf("%u", &State_Sel);

                switch(State_Sel)
                {
                    case 1:
                    {
                        Antenna_Bank_1_Enable();
                        break;
                    }
                    case 2:
                    {
                        Antenna_Bank_2_Enable();
                        break;
                    }
                    case 3:
                    {
                        Match_720_750_Enable();
                        break;
                    }
                    case 4:
                    {
                        Match_750_800_Enable();
                        break;
                    }
                    case 5:
                    {
                        Match_800_900_Enable();
                        break;
                    }
                    case 6:
                    {
                        Match_900_1400_Enable();
                        break;
                    }
                    case 7:
                    {
                        Low_Amp_Enable();
                        break;
                    }
                    case 8:
                    {
                        High_Amp_Enable();
                        break;
                    }
                    default:
                    {
                        puts("");
                        puts("Requested State Not In Range [1,8].");
                        sleep(2);
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                system("clear");
                printf("Select Switch and Port\n");
                printf("SW 1: Antenna Select\nSW 2: Matching Network A\nSW 3: Matching Network B\nSW 4: Amplifier A\nSW 5: Amplifier B\n\n");
                printf("Type Selection Here And Hit Enter: ");
                scanf("%u", &Switch_Sel);
                system("clear");

                switch(Switch_Sel)
                {
                    case 1:
                    {
                        printf("P [3/4]\n\n");
                        printf("Type Selection Here And Hit Enter: ");
                        scanf("%u",&Port_Sel);
                        if((Port_Sel == 1) || (Port_Sel == 2))
                        {
                            printf("\nNotice: Port %u is Not Connected on RFFE.\n", Port_Sel);
                            sleep(1);
                            system("clear");
                        }
                        Control_RF_Switch_State(Port_Sel, ANT_SEL_P1_DISP, ANT_SEL_P2_DISP);
                        break;
                    }
                    case 2:
                    {
                        printf("P [1/2/3/4]\n\n");
                        printf("Type Selection Here And Hit Enter: ");
                        scanf("%u",&Port_Sel);
                        Control_RF_Switch_State(Port_Sel, MATCHING_SEL_A_P1_DISP, MATCHING_SEL_A_P2_DISP);
                        break;
                    }
                    case 3:
                    {
                        printf("P [4/3/2/1]\n\n");
                        printf("Type Selection Here And Hit Enter: ");
                        scanf("%u",&Port_Sel);
                        Control_RF_Switch_State(Port_Sel, MATCHING_SEL_B_P1_DISP, MATCHING_SEL_B_P2_DISP);
                        break;
                    }
                    case 4:
                    {
                        
                        printf("P [2/4]\n\n");
                        printf("Type Selection Here And Hit Enter: ");
                        scanf("%u",&Port_Sel);
                        if((Port_Sel == 1) || (Port_Sel == 3))
                        {
                            printf("\nNotice: Port %u is Not Connected on RFFE.\n", Port_Sel);
                            sleep(1);
                            system("clear");
                        }
                        Control_RF_Switch_State(Port_Sel, LNA_SEL_A_P1_DISP, LNA_SEL_A_P2_DISP);
                        break;
                    }
                    case 5:
                    {
                        printf("P [4/3]\n\n");
                        printf("Type Selection Here And Hit Enter: ");
                        scanf("%u",&Port_Sel);
                        if((Port_Sel == 2) || (Port_Sel == 1))
                        {
                            printf("\nNotice: Port %u is Not Connected on RFFE.\n", Port_Sel);
                            sleep(1);
                            system("clear");
                        }
                        Control_RF_Switch_State(Port_Sel, LNA_SEL_B_P1_DISP, LNA_SEL_B_P2_DISP);
                        break;
                    }
                    default:
                    {
                        puts("");
                        puts("Requested Switch Not In Range [1,5].");
                        break;
                    }
                }
                break;
            }
        }
        Get_RFFE_State(&RF_Front_End_Switch_State_Log);
    }
    return(1);
}