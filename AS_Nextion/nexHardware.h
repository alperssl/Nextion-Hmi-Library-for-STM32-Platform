/*
 * nexHardware.h
 *
 *  Created on: Aug 21, 2019
 *      Author: alpersuslu
 */

#ifndef AS_NEXHARDWARE_H_
#define AS_NEXHARDWARE_H_

#include "nexConfig.h"
#include "tm_stm32_usart.h"

/**
 * Init Nextion.
 *
 * @return true if success, false for failure.
 */
bool nexInit(uint32_t nexBaudrate);


/**
 * Listen touch event and calling callbacks attached before.
 *
 * Supports push and pop at present.
 *
 * @param nex_listen_list - index to Nextion Components list.
 * @return none.
 *
 * @warning This function must be called repeatedly to response touch events
 *  from Nextion touch panel. Actually, you should place it in your loop function.
 */
//void nexLoop(NexTouch *nex_listen_list[]);



bool recvRetNumber(uint32_t *number, uint32_t timeout);
uint16_t recvRetString(char *buffer, uint16_t len, uint32_t timeout);
void sendCommand(const char* cmd);
bool recvRetCommandFinished(void);

#endif /* AS_NEXHARDWARE_H_ */
