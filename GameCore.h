//**********************************************************************
// Author:      Billy Huang
// Date:        2015.08.10
//**********************************************************************

typedef struct _GameCore
{
	VOID (*Initialize)();
	VOID (*GameLoop)(VOID (*func)(EFI_INPUT_KEY, EFI_GRAPHICS_OUTPUT_PROTOCOL*));
	INTN (*RandomInitSeed)();
} GameCore;

GameCore* GameCoreInstance();
