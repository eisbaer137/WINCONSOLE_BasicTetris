/*
	TetrisMain.cpp ver 1.3
*/

#include <Windows.h>
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "common.h"
#include "scoreLevelControl.h"
#include <cstdio>

#define	START_CURPOS_X	(6 *2)
#define START_CURPOS_Y	(0)

void pauseGuide(void);

int main(int argc, char* argv[])
{
	system("mode con: cols=60 lines=25");

	InitKeyDelayRate(5);

	DrawTetrisStage();

	RemoveCursor();

	pauseGuide();

	ChooseBlock();

	ShowCurrentScoreAndLevel();

	while (1) // new block's emergence loop
	{
		InitNewBlockPosition(START_CURPOS_X, START_CURPOS_Y);

		//ChooseBlock();
		NextBlock();
		ShowNextBlock();

		if (IsGameOver())
			break;
		while (1) // each block's falling loop
		{
			if (BlockDown() == 0)
			{
				//RenewStageState();
				blockChange();
				break;
			}
			if (ProcessKeyInput())
			{
				blockChange();
				break;
			}
			
		}
	}

	SetCurrentCursorPosition(10, 10);
	printf("Game is Over...");
	
	getchar();

	ReturnHandle();
	return 0;
}

