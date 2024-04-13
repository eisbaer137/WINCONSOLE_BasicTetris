/*
	keyCurControl.cpp ver 1.3
*/

#include "keyCurControl.h"
#include <conio.h>
#include "point.h"
#include <Windows.h>
#include "blockStageControl.h"

#define KEY_SENSITIVITY	120
#define	SYS_DELAY	30

#define LEFT	75
#define	RIGHT	77
#define UP	72
#define	DOWN	80
#define PAUSE	112
#define SPACE	32	

static int keyDelayRate;
HANDLE hConsoleOut;

/*
	void RemoveCursor(void) : removing the blinking cursor
*/
void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hConsoleOut, &curInfo);
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsoleOut, &curInfo);
}

/*
	Point GetCurrentCursorPosition(void) :
	returning structural variable that contains current cursor position info.
*/
Point GetCurrentCursorPosition(void)
{
	Point curPoint;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(hConsoleOut, &curInfo);
	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

/*
	void SetCurrentCursorPosition(int x, int y) :
	setting cursor position
*/
void SetCurrentCursorPosition(int x, int y)
{
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hConsoleOut, pos);
}

/*
	void ProcessKeyInput(void) : it processes key input
*/
int ProcessKeyInput(void)
{
	int i, key;
	for (i = 0; i < KEY_SENSITIVITY; i++)
	{
		if (_kbhit() != 0)
		{
			key = _getch();

			switch (key)
			{
			case LEFT:
				ShiftLeft();
				break;
			case RIGHT:
				ShiftRight();
				break;
			case UP:
				RotateBlock();
				break;
			case SPACE:
				PutDownBlock();
				return 1;
			case PAUSE:
				while (1)
				{
					key = _getch();
					if (key == PAUSE)
						break;
				}
				break;
			}
		}
		if (i % keyDelayRate == 0)
			Sleep(SYS_DELAY);
	}
	return 0;
}

/*
	void InitKeyDelayRate(int rate) : it adjusts block's dropping rate,
	higher the rate, higher dropping speed
*/
void InitKeyDelayRate(int rate)
{
	if (rate < 1)
		return;
	keyDelayRate = rate;
}

/*
	void KeyDelaySpeedControl(int addSpeed) : it adjusts the block's dropping rate
*/
void KeyDelaySpeedControl(int addSpeed)
{
	keyDelayRate += addSpeed;
}

void ReturnHandle(void)
{
	CloseHandle(hConsoleOut);
}

