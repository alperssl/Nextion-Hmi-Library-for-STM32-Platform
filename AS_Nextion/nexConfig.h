/*
 * nexConfig.h
 *
 *  Created on: Aug 21, 2019
 *      Author: alpersuslu
 */

#ifndef AS_NEXCONFIG_H_
#define AS_NEXCONFIG_H_

#include <stdbool.h>
#include <stdint.h>

/*
	             Pins pack 1	    Pins pack 2	    Pins pack 3
	U(S)ARTx	  TX	RX	          TX	RX	      TX	RX
	USART1	     PA9	PA10	     PB6	PB7
	USART2	     PA2	PA3	         PD5	PD6
	USART3	     PB10	PB11	    PC10	PC11	  PD8	PD9
	UART4	     PA0	PA1	        PC10	PC11
	UART5	     PC12	PD2
	USART6	     PC6	PC7	        PG14	PG9
	UART7	     PE8	PE7	         PF7	PF6
	UART8	     PE1	PE0
 */

//#define nexUsart USART1
#define nexUsart USART2
//#define nexUsart USART3
//#define nexUsart UART4
//#define nexUsart UART5
//#define nexUsart USART6
//#define nexUsart UART7
//#define nexUsart UART8

#define nexUsartPinsPack 0 // Pins Pack 1
//#define nexUsartPinsPack 1 // Pins Pack 2
//#define nexUsartPinsPack 2 // Pins Pack 3

#define nex_maxTextChar 10 // Maximum length of texts of objects, 10 is default on nextion editor.

#endif /* AS_NEXCONFIG_H_ */
