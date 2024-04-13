/*
	keyCurControl.h ver 1.1
*/

#ifndef __KEY_CUR_CONTROL_H__

#define __KEY_CUR_CONTROL_H__

#include "point.h"

void RemoveCursor(void);
Point GetCurrentCursorPosition(void);
void SetCurrentCursorPosition(int x, int y);
void ReturnHandle(void);
int ProcessKeyInput(void);
void InitKeyDelayRate(int rate);
void KeyDelaySpeedControl(int addSpeed);

#endif
