/*
 * nexHardware.c
 *
 *  Created on: Aug 21, 2019
 *      Author: alpersuslu
 */

#include "nexHardware.h"


#define NEX_RET_CMD_FINISHED            (0x01)
#define NEX_RET_EVENT_LAUNCHED          (0x88)
#define NEX_RET_EVENT_UPGRADED          (0x89)
#define NEX_RET_EVENT_TOUCH_HEAD            (0x65)
#define NEX_RET_EVENT_POSITION_HEAD         (0x67)
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD   (0x68)
#define NEX_RET_CURRENT_PAGE_ID_HEAD        (0x66)
#define NEX_RET_STRING_HEAD                 (0x70)
#define NEX_RET_NUMBER_HEAD                 (0x71)
#define NEX_RET_INVALID_CMD             (0x00)
#define NEX_RET_INVALID_COMPONENT_ID    (0x02)
#define NEX_RET_INVALID_PAGE_ID         (0x03)
#define NEX_RET_INVALID_PICTURE_ID      (0x04)
#define NEX_RET_INVALID_FONT_ID         (0x05)
#define NEX_RET_INVALID_BAUD            (0x11)
#define NEX_RET_INVALID_VARIABLE        (0x1A)
#define NEX_RET_INVALID_OPERATION       (0x1B)

/*
 * Receive uint32_t data.
 *
 * @param number - save uint32_t data.
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed.
 *
 */
bool recvRetNumber(uint32_t *number, uint32_t timeout)
{
	uint8_t temp[8] = {0};

	if (!number){
		return false;
	}

	while(TM_USART_BufferCount(nexUsart) < 7){

	}
	HAL_Delay(10);

	int pos = TM_USART_FindCharacter(nexUsart, NEX_RET_NUMBER_HEAD);
	if(pos >= 0){

		for(int b = 0; b<pos; b++){
			TM_USART_Getc(nexUsart);
		}

		for(int i = 0; i<8; i++){
			temp[i] = TM_USART_Getc(nexUsart);
		}

		if (temp[0] == NEX_RET_NUMBER_HEAD
				&& temp[5] == 0xFF
				&& temp[6] == 0xFF
				&& temp[7] == 0xFF
		)
		{
			*number = (temp[4] << 24) | (temp[3] << 16) | (temp[2] << 8) | (temp[1]);
			return true;
		}
	}
	return false;
}


/*
 * Receive string data.
 *
 * @param buffer - save string data.
 * @param len - string buffer length.
 * @param timeout - set timeout time.
 *
 * @return the length of string buffer.
 *
 */
uint16_t recvRetString(char *buffer, uint16_t len, uint32_t timeout)
{
	uint16_t ret = 0;

	char strflag[5] = {NEX_RET_STRING_HEAD};
	char endflag[5] = {0xFF, 0xFF, 0xFF};
	char tempBuff[100] = {0};


	if (!buffer || len == 0)
	{
		return 0;
	}


	while (TM_USART_BufferCount(nexUsart) < (strlen(strflag) + strlen(endflag)) ) {

	}
	HAL_Delay(10);

	if(TM_USART_Gets_withStrandEndFlag(nexUsart, tempBuff, sizeof(tempBuff), strflag, endflag) > 0){
		ret = strlen(tempBuff);
		ret = ret > len ? len : ret;
		strncpy(buffer, tempBuff, ret);

		return ret;
	}

	return 0;

}


/*
 * Send command to Nextion.
 *
 * @param cmd - the string of command.
 */
void sendCommand(const char *cmd)
{
	while (!TM_USART_BufferEmpty(nexUsart))
	{
		TM_USART_Getc(nexUsart);
	}

	TM_USART_Puts(nexUsart, (char*)cmd);
	TM_USART_Putc(nexUsart, 0xFF);
	TM_USART_Putc(nexUsart, 0xFF);
	TM_USART_Putc(nexUsart, 0xFF);
}



/*
 * Command is executed successfully.
 *
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed.
 *
 */
bool recvRetCommandFinished(void){
	char temp[8] = {0};
	char endFlag[4] = {NEX_RET_CMD_FINISHED, 0xFF, 0xFF, 0xFF};

	//setTimeout(timeout);

	while (TM_USART_BufferCount(nexUsart) < strlen(endFlag)) {
	}

	if(TM_USART_Gets_withEndFlag(nexUsart, temp, sizeof(temp), endFlag) > 0){
		return true;
	}

	return false;
}


/*
 * Init Nextion.
 *
 * @return true if success, false for failure.
 */
bool nexInit(uint32_t nexBaudrate){

	TM_USART_Init(nexUsart, nexUsartPinsPack, nexBaudrate);

	bool ret1 = false;
	bool ret2 = false;

	sendCommand("");
	sendCommand("bkcmd=1");
	ret1 = recvRetCommandFinished();
	sendCommand("page 0");
	ret2 = recvRetCommandFinished();
	return ret1 && ret2;

}

/*
void nexLoop(NexTouch *nex_listen_list[])
{
    static uint8_t __buffer[10];

    uint16_t i;
    uint8_t c;

    while (TM_USART_BufferCount(nexUsart) > 0)
    {

        HAL_Delay(10);
        c = TM_USART_Getc(nexUsart);

        if (NEX_RET_EVENT_TOUCH_HEAD == c)
        {
            if (TM_USART_BufferCount(nexUsart) >= 6)
            {
                __buffer[0] = c;
                for (i = 1; i < 7; i++)
                {
                    __buffer[i] = TM_USART_Getc(nexUsart);
                }
                __buffer[i] = 0x00;

                if (0xFF == __buffer[4] && 0xFF == __buffer[5] && 0xFF == __buffer[6])
                {
                    NexTouch::iterate(nex_listen_list, __buffer[1], __buffer[2], (int32_t)__buffer[3]);
                }

            }
        }
    }
}
 */


