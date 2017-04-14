#include <Library/BaseLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/GraphicsOutput.h>

#include "GraphicUtility.h"
#include "GameCore.h"


EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *gCanvasBuffer = NULL;
EFI_EVENT                      gEvents[2];
EFI_EVENT                      timerEvent;
EFI_GRAPHICS_OUTPUT_PROTOCOL   *GraphicsOutput;



VOID Initialize()
{
	gBS->LocateProtocol (
	    &gEfiGraphicsOutputProtocolGuid,
	    NULL,
	    &GraphicsOutput
	);

	gBS->CreateEvent (
	    EVT_TIMER,
	    0,
	    NULL,
	    NULL,
	    &timerEvent
	);
	gBS->SetTimer (
	    timerEvent,
	    TimerPeriodic,
	    10 * 1000 * 1000 / 60
	);

	gCanvasBuffer = AllocateZeroPool (
	                    sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * CANVAS_W * CANVAS_H
	                );

}

VOID ClearCanvas()
{
	UINTN XIndex;
	UINTN YIndex;
	for (YIndex = CANVAS_Y; YIndex < CANVAS_Y + CANVAS_H; YIndex++) {
		for (XIndex = CANVAS_X; XIndex < CANVAS_X + CANVAS_W; XIndex++) {
			UINTN BltPos = YIndex * CANVAS_W + XIndex;
			gCanvasBuffer[BltPos].Blue = 255;
			gCanvasBuffer[BltPos].Green = 255;
			gCanvasBuffer[BltPos].Red = 0;
			gCanvasBuffer[BltPos].Reserved = 0;
		}
	}
}

VOID GameLoop(
    VOID (*func)(EFI_INPUT_KEY, EFI_GRAPHICS_OUTPUT_PROTOCOL*)
)
{
	EFI_STATUS    Status = EFI_SUCCESS;
	UINTN         Index;
	EFI_INPUT_KEY Key;

	gEvents[0] = gST->ConIn->WaitForKey;
	gEvents[1] = timerEvent;

	Key.ScanCode = SCAN_NULL;
	do {
		gBS->WaitForEvent (2, gEvents, &Index);
		if (Index == 0) {
			gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
			continue;
		}
		else
		{
			ClearCanvas();
			//Callback user logic
			func(Key, GraphicsOutput);

			Status = GraphicsOutput->Blt (
			             GraphicsOutput,
			             gCanvasBuffer,
			             EfiBltBufferToVideo,
			             0 , 0 ,
			             CANVAS_X , CANVAS_Y , //xy
			             288, 512,
			             0
			         );

		}
		Key.ScanCode = SCAN_NULL;
	} while (Key.ScanCode != SCAN_END);//Key.ScanCode != SCAN_END

}

INTN
RandomInitSeed()
{
	EFI_TIME Time;
	INTN Seed;

	gRT->GetTime( &Time, NULL );

	Seed = ( ~Time.Hour << 24 | Time.Day << 16 | Time.Minute << 8 | Time.Second );
	Seed ^= Time.Nanosecond;
	Seed ^= Time.Year << 7;
	return Seed;
}

GameCore*
GameCoreInstance()
{
	GameCore *gc = AllocateZeroPool (sizeof(GameCore));
	gc->Initialize = Initialize;
	gc->GameLoop = GameLoop;
	gc->RandomInitSeed = RandomInitSeed;
	return gc;
}