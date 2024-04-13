/*
	blockStageControl.h
*/

#ifndef __BLOCK_STAGE_CONTROL_H__

#define __BLOCK_STAGE_CONTROL_H__


void DrawTetrisStage(void);
void InitNewBlockPosition(int x, int y);
void ChooseBlock(void);
void NextBlock(void);
void ShowNextBlock(void);
int GetCurrentBlockIdx(void);
void ShowBlock(char blockInfo[][4]);
void DeleteBlock(char blockInfo[][4]);
int BlockDown(void);
void ShiftLeft(void);
void ShiftRight(void);
void RotateBlock(void);
int DetectOverlap(int posX, int posY, char blockModel[][4]);
void RenewStageState(void);
int IsGameOver(void);
void blockChange(void);
void pauseGuide(void);
void RemoveFilledLine(void);
void DrawSolidBlocks(void);
void PutDownBlock(void);


#endif

