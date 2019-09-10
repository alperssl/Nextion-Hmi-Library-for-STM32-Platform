/*
 * nexTools.h
 *
 *  Created on: Aug 24, 2019
 *      Author: alpersuslu
 */

#ifndef AS_NEXTOOLS_H_
#define AS_NEXTOOLS_H_

#include <stdint.h>
#include "nexConfig.h"
#include <stdbool.h>

/*
 * types of nexObjects is types of nextion objects in editor
 */
enum nexObjects{ button, crop, gauge, hotspot, page, picture, progressbar, slider, text, waveform };

/*
 * @param nObj - type of object.
 * @param pid - page id.
 * @param cid - component id.
 */
typedef struct {
	enum nexObjects nObj;
	char *name;
	uint8_t pid;
	uint8_t cid;
}NexObject;

void nex_addTouchListener(NexObject obj);

uint16_t nex_getText(NexObject obj, char *buffer, uint16_t len);

bool nex_setText(NexObject obj, char text[nex_maxTextChar]);

bool nex_getPic(NexObject obj, uint32_t *number);

bool nex_setPic(NexObject obj, uint32_t number);

bool nex_getValue(NexObject obj, uint32_t *number);

bool nex_setValue(NexObject obj, uint32_t number);

bool nex_goToPage(NexObject obj);

//bool nex_addValue(NexObject obj, uint8_t ch, uint8_t number);


#endif /* AS_NEXTOOLS_H_ */
