#include "Serial_Comms.h"

int main()
{
    int XBEE_fd = 0;
    int8_t UART_Close = -1;
    
    int8_t Serial_Init_Status = 0;
    Serial_Init_Status = Init_XBee(&XBEE_fd);

    if(Serial_Init_Status > 0)
    {
        char MSG_BUFFER[265] = {0};
        while(1)
        {
            printf("Please Supply Next Message: ");
            scanf("%s", MSG_BUFFER);
            printf("\nTransmitting...\n");
            serialPuts(XBEE_fd, MSG_BUFFER);
            puts("Message Sent");
            memset(MSG_BUFFER, '\0', sizeof(MSG_BUFFER));
        }

        UART_Close = 1;

    if(UART_Close == 1)
    {
        serialClose (XBEE_fd);
    }
    }
    return(0);
}