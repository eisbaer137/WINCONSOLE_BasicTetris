/*
	blockStageControl.cpp ver 1.3
	definitions of block, game screen control functions
*/

#include "blockStageControl.h"
#include <time.h>
#include "common.h"
#include "point.h"
#include "blockInfo.h"
#include "keyCurControl.h"
#include <cstring>
#include "scoreLevelControl.h"

#define	TSTAGE_WIDTH	10
#define	TSTAGE_HEIGHT	20

#define	TSTAGE_ORIGIN_X	4
#define TSTAGE_ORIGIN_Y	2	

static int tetrisStageInfo[TSTAGE_HEIGHT + 1][TSTAGE_WIDTH + 2] = { 0, };
static int currentBlockModel;
static int nextBlockModel;
static int curPosX, curPosY;
static int rotationState;


/*
	void DrawTetrisStage(void) : it draws a tetris background stage
*/
void DrawTetrisStage(void)
{
	int x, y;
	// drawing the boundary of tetris stage
	for (y = 0; y <= TSTAGE_HEIGHT; y++)
	{
		SetCurrentCursorPosition(TSTAGE_ORIGIN_X, TSTAGE_ORIGIN_Y + y);
		if (y == TSTAGE_HEIGHT)
		{
			printf("¦¦");
		}
		else
		{
			printf("¦¢");
		}
	}
	for (x = 1; x <= TSTAGE_WIDTH; x++)
	{
		SetCurrentCursorPosition(TSTAGE_ORIGIN_X + x * 2, TSTAGE_ORIGIN_Y + TSTAGE_HEIGHT);
		printf("¦¡");
	}
	for (y = 0; y <= TSTAGE_HEIGHT; y++)
	{
		SetCurrentCursorPosition(TSTAGE_ORIGIN_X + (TSTAGE_WIDTH + 1) * 2, TSTAGE_ORIGIN_Y + y);
		if (y == TSTAGE_HEIGHT)
		{
			printf("¦¥");
		}
		else
		{
			printf("¦¢");
		}
	}
	SetCurrentCursorPosition(0, 0);

	// imposing logical values for detecting overlap to the stage
	for (y = 0; y < TSTAGE_HEIGHT; y++)
	{
		tetrisStageInfo[y][0] = 1;
		tetrisStageInfo[y][TSTAGE_WIDTH + 1] = 1;
	}
	for (x = 0; x < TSTAGE_WIDTH + 2; x++)
	{
		tetrisStageInfo[TSTAGE_HEIGHT][x] = 1;
	}
}

/*
	void InitNewBlockPosition(int x, int y) : Initialize new block's position
*/
void InitNewBlockPosition(int x, int y)
{
	if (x < 0 || y < 0)
		return;
	curPosX = x; curPosY = y;
	SetCurrentCursorPosition(x, y);
}

/*
	void ChooseBlock(void) : it randomly chooses a block to show up
*/
void ChooseBlock(void)
{
	srand((unsigned int)time(NULL));
	currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
}

void NextBlock(void)
{
	//srand((unsigned int)time(NULL));
	nextBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
}

void blockChange(void)
{
	currentBlockModel = nextBlockModel;
}


/*
	int GetCurrentBlockIdx(void) : it returns block's id(index) to be show up right now
*/
int GetCurrentBlockIdx(void)
{
	return currentBlockModel + rotationState;
}
/*
	void ShowBlock(char blockInfo[][4]) : it shows a block up
*/
void ShowBlock(char blockInfo[][4])
{
	int x, y;
	Point curPos = GetCurrentCursorPosition();

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			SetCurrentCursorPosition(curPos.x + x * 2, curPos.y + y);
			if (blockInfo[y][x] == 1)
				printf("¡á");
		}
	}
	SetCurrentCursorPosition(curPos.x, curPos.y);
}

/*
	void DeleteBlock(char blockInfo[][4]) : delete block at current location
*/
void DeleteBlock(char blockInfo[][4])
{
	int x, y;
	Point curPos = GetCurrentCursorPosition();

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			SetCurrentCursorPosition(curPos.x + x * 2, curPos.y + y);
			if (blockInfo[y][x] == 1)
			{
				printf("  ");
			}
		}
	}
	SetCurrentCursorPosition(curPos.x, curPos.y);
}

void ShowNextBlock(void)
{
	SetCurrentCursorPosition(39, 15);
	printf("Next Block");
	SetCurrentCursorPosition(41, 17);
	Point curPos = GetCurrentCursorPosition();
	//printf("%d, %d", curPos.x, curPos.y);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetCurrentCursorPosition(curPos.x + x * 2, curPos.y + y);
			if (blockModel[nextBlockModel][y][x] == 1)
			{
				printf("¡á");
			}
			else
			{
				printf("  ");
			}
		}
	}

}

/*
	void BlockDown(void) : it lowers a block down one row
	it returns 1 if successful, 0 otherwise
*/
int BlockDown(void)
{
	if (!DetectOverlap(curPosX, curPosY + 1, blockModel[GetCurrentBlockIdx()])) // assuming the block is moved, 
	{
		RenewStageState();
		RemoveFilledLine();
		return 0;
	}

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosY += 1;

	SetCurrentCursorPosition(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);

	return 1;
}

/*
	void ShiftLeft(void) : it moves a block in one left column
*/
void ShiftLeft(void)
{
	if (!DetectOverlap(curPosX - 2, curPosY, blockModel[GetCurrentBlockIdx()]))
		return;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX -= 2;
	SetCurrentCursorPosition(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

/*
	void ShiftRight(void)
*/
void ShiftRight(void)
{
	if (!DetectOverlap(curPosX + 2, curPosY, blockModel[GetCurrentBlockIdx()]))
		return;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX += 2;
	SetCurrentCursorPosition(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

/*
	void RotateBlock(void) : it rotates a block in counterclockwise 90 degrees
*/
void RotateBlock(void)
{
	//int nextRotationState = rotationState + 1;
	//nextRotationState = nextRotationState % 4; 
	//DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	//rotationState = nextRotationState;
	int nextRotationState;
	int previousRotationState = rotationState;
	DeleteBlock(blockModel[GetCurrentBlockIdx()]);

	nextRotationState = rotationState + 1;
	nextRotationState = nextRotationState % 4;
	rotationState = nextRotationState;

	if (!DetectOverlap(curPosX, curPosY, blockModel[GetCurrentBlockIdx()]))
	{
		rotationState = previousRotationState;
		//return;
	}

	SetCurrentCursorPosition(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

/*
	int DetectOverlap(int posX, int posY, char blockModel[][4]) :
	it detects if the block is overlapped with the boundary or any piled blocks
	when overlap is happened. it returns 0, 1 otherwise
*/
int DetectOverlap(int posX, int posY, char blockModel[][4])
{
	int x, y;
	// transformation of block's position into indices of its counterpart in tetris stage array
	int arrX = (posX - TSTAGE_ORIGIN_X) / 2;
	int arrY = posY - TSTAGE_ORIGIN_Y;
	// checking the overlap

	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			if (blockModel[y][x] == 1 && tetrisStageInfo[arrY + y][arrX + x] == 1)
				return 0;
		}
	}
	return 1;
}

/*
	void RenewStageStage(void) : it renews the stage state.
*/
void RenewStageState(void)
{
	int x, y;
	int arrCurX, arrCurY;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			arrCurX = (curPosX - TSTAGE_ORIGIN_X) / 2;
			arrCurY = curPosY - TSTAGE_ORIGIN_Y;

			if (blockModel[GetCurrentBlockIdx()][y][x] == 1)
			{
				tetrisStageInfo[arrCurY + y][arrCurX + x] = 1;
			}
		}
	}
}

/*
	int IsGameOver(void) : it determines if the game is over
	if game ends, it returns 1, 0 otherwise
*/
int IsGameOver(void)
{
	if (!DetectOverlap(curPosX, curPosY, blockModel[GetCurrentBlockIdx()]))
		return 1;
	else
		return 0;
}

/*
	void DrawSolidBlocks(void) : it draws solid blocks on the tetris stage
*/
void DrawSolidBlocks(void)
{
	int x, y;
	int curX, curY;
	
	for (y = 0; y < TSTAGE_HEIGHT; y++)
	{
		for (x = 1; x < TSTAGE_WIDTH + 1; x++)
		{
			curX = x * 2 + TSTAGE_ORIGIN_X;
			curY = y + TSTAGE_ORIGIN_Y;
			SetCurrentCursorPosition(curX, curY);
			if (tetrisStageInfo[y][x] == 1)
			{
				printf("¡á");
			}
			else
			{
				printf("  ");
			}
		}
	}
}

/*
	void RemoveFilledLine(void) : it removes filled up lines	
*/
void RemoveFilledLine(void)
{
	int x, y, line;
	for (y = TSTAGE_HEIGHT - 1; y > 0; y--)
	{
		for (x = 1; x < TSTAGE_WIDTH + 1; x++)
		{
			if (tetrisStageInfo[y][x] != 1)
				break;
		}
		if (x == (TSTAGE_WIDTH + 1))
		{
			for (line = 0; y > line; line++)
			{
				memcpy(&tetrisStageInfo[y - line][1],
					&tetrisStageInfo[y - line - 1][1], (TSTAGE_WIDTH) * sizeof(int));
			}
			y++;
			AddGameScore(10);
			ShowCurrentScoreAndLevel();
		}
	}
	DrawSolidBlocks();
}

void PutDownBlock(void)
{
	while (BlockDown());
}

void pauseGuide(void)
{
	SetCurrentCursorPosition(30, 12);
	printf("Press 'p' to pause the game.");
}
