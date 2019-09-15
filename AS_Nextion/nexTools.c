/*
 * nexTools.c
 *
 *  Created on: Aug 24, 2019
 *      Author: alpersuslu
 */

#include "nexTools.h"
#include "nexHardware.h"
#include <string.h>

uint16_t nex_getText(NexObject obj, char *buffer, uint16_t len){

	char cmd[50] = {};
	strcat(cmd, "get ");
	strcat(cmd, obj.name);
	strcat(cmd, ".txt");
	sendCommand(cmd);
	return recvRetString(buffer,len,100);
}

bool nex_setText(NexObject obj, char text[nex_maxTextChar]){

	char cmd[50] = {};
	strcat(cmd, obj.name);
	strcat(cmd, ".txt=\"");
	strcat(cmd, text);
	strcat(cmd, "\"");
	sendCommand(cmd);
	return recvRetCommandFinished();
}

bool nex_getPic(NexObject obj, uint32_t *number){

	char cmd[50] = {};
	strcat(cmd, "get ");
	strcat(cmd, obj.name);
	strcat(cmd, ".pic");
	sendCommand(cmd);
	return recvRetNumber(number,100);
}

bool nex_setPic(NexObject obj, uint32_t number){

	char buf[10] = {};
	char cmd[50] = {};

	utoa(number, buf, 10);
	strcat(cmd, obj.name);
	strcat(cmd, ".pic=");
	strcat(cmd, buf);

	sendCommand(cmd);
	return recvRetCommandFinished();
}

bool nex_getValue(NexObject obj, uint32_t *number){

	char cmd[50] = {};

	strcat(cmd, "get ");
	strcat(cmd, obj.name);
	strcat(cmd, ".val");
	sendCommand(cmd);
	return recvRetNumber(number,100);

}

bool nex_setValue(NexObject obj, uint32_t number){

	char buf[10] = {0};
	char cmd[50] = {};

	utoa(number, buf, 10);
	strcat(cmd, obj.name);
	strcat(cmd, ".val=");
	strcat(cmd, buf);

	sendCommand(cmd);
	return recvRetCommandFinished();

}

bool nex_goToPage(NexObject obj){

	const char *name = obj.name;
	if (!name)
	{
		return false;
	}

	char cmd[50] = {};
	strcat(cmd, "page ");
	strcat(cmd, name);
	sendCommand(cmd);
	return recvRetCommandFinished();

}

void nex_click(NexObject obj){
	char cmd[50] = {};
	strcat(cmd, "click ");
	strcat(cmd, obj.name);
	strcat(cmd, ",1");
	sendCommand(cmd);

	char cmd2[50] = {};
	strcat(cmd2, "click ");
	strcat(cmd2, obj.name);
	strcat(cmd2, ",0");
	sendCommand(cmd2);
}

void nex_hide(NexObject obj){
	char cmd[50] = {};
	strcat(cmd, "vis ");
	strcat(cmd, obj.name);
	strcat(cmd, ",0");
	sendCommand(cmd);
}

void nex_show(NexObject obj){
	char cmd[50] = {};
	strcat(cmd, "vis ");
	strcat(cmd, obj.name);
	strcat(cmd, ",1");
	sendCommand(cmd);
}

void nex_reset(void){
	sendCommand("rest");
}

/*bool nex_addValue(NexObject obj, uint8_t ch, uint8_t number){

	char buf[15] = {0};

	if (ch > 3)
	{
		return false;
	}

	sprintf(buf, "add %u,%u,%u", getObjCid(), ch, number);

	sendCommand(buf);
	return true;

}*/



