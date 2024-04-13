/*
	scoreLevelContro.cpp ver 1.1
*/

#include "common.h"
#include "keyCurControl.h"
#include "scoreLevelControl.h"

#define	LEVEL_DIFFICULTY	2
#define	LEVEL_UP_POINT	300	

static int curGameLevel = 1;
static int curGameScore = 0;

/*
	void ShowCurrentScoreAndLevel(void) : it prints out the current score and the level
*/
void ShowCurrentScoreAndLevel(void)
{
	SetCurrentCursorPosition(30, 4);
	printf("¢º Current Level : %5d ¢¸", curGameLevel);

	SetCurrentCursorPosition(30, 7);
	printf("¢º Current Score : %5d ¢¸", curGameScore);
}

/*
	void GameLevelUp(void) : it levels up the game's level
*/
void GameLevelUp(void)
{
	curGameLevel++;
	KeyDelaySpeedControl(LEVEL_DIFFICULTY);
}

/*
	void AddGameScore(int score) : it scores the points and levels up
*/
void AddGameScore(int score)
{
	if (score < 1)
		return;
	
	curGameScore += score;

	if (curGameScore >= curGameLevel * LEVEL_UP_POINT)
		GameLevelUp();

}