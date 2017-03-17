//;******************************************************************************
//;* Copyright (c) Acer (KR2600) Corporation. All Rights Reserved.
//;*
//;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
//;* transmit, broadcast, present, recite, release, license or otherwise exploit
//;* any part of this publication in any form, by any means, without the prior
//;* written permission of Acer (KR2600) Corporation.
//;*
//;******************************************************************************

//**********************************************************************
// Author:        Billy Huang
// Date:          2015.08.10
//**********************************************************************

#include <Library/BaseLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/FileInfo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimpleFileSystem.h>
#include <Library/PciLib.h>

#include "Object.h"
#include "GraphicUtility.h"
#include "PcxDecoder.h"
#include "PcxImage.h"

#define MAX_BUFFER_SIZE SIZE_1MB

#define abs(x) ((x)<0 ? -(x) : (x))
#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

#define LAND_H                   112
#define BACK_SPEED               1
#define ANIMATION_CREATE(frames) AllocatePool (sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*) * frames)

//BL fast math table
INTN mySin[361] =
{
	0,          71,         142,        214,        285,        356,        428,        499,        570,        640,        711,        781,        851,        921,        990,        1060,       1129,       1197,       1265,       1333,       1400,       1467,       1534,       1600,       1665,       1731,       1795,       1859,       1922,       1985,       2047,       2109,       2170,       2230,       2290,       2349,       2407,       2465,       2521,       2577,       2632,       2687,       2740,       2793,       2845,       2896,       2946,       2995,       3043,       3091,       3137,       3183,       3227,       3271,       3313,       3355,       3395,       3435,       3473,       3510,       3547,       3582,       3616,       3649,       3681,       3712,       3741,       3770,       3797,       3823,       3848,       3872,       3895,       3917,       3937,       3956,       3974,       3991,       4006,       4020,       4033,       4045,       4056,       4065,       4073,       4080,       4086,       4090,       4093,       4095,       4096,       4095,       4093,       4090,       4086,       4080,       4073,       4065,       4056,       4045,       4033,       4020,       4006,       3991,       3974,       3956,       3937,       3917,       3895,       3872,       3848,       3823,       3797,       3770,       3741,       3712,       3681,       3649,       3616,       3582,       3547,       3510,       3473,       3435,       3395,       3355,       3313,       3271,       3227,       3183,       3137,       3091,       3043,       2995,       2946,       2896,       2845,       2793,       2740,       2687,       2632,       2577,       2521,       2465,       2407,       2349,       2290,       2230,       2170,       2109,       2048,       1985,       1922,       1859,       1795,       1731,       1665,       1600,       1534,       1467,       1400,       1333,       1265,       1197,       1129,       1060,       990,        921,        851,        781,        711,        640,        570,        499,        428,        356,        285,        214,        142,        71,         0,          -71,        -142,       -214,       -285,       -356,       -428,       -499,       -570,       -640,       -711,       -781,       -851,       -921,       -990,       -1060,      -1129,      -1197,      -1265,      -1333,      -1400,      -1467,      -1534,      -1600,      -1665,      -1731,      -1795,      -1859,      -1922,      -1985,      -2047,      -2109,      -2170,      -2230,      -2290,      -2349,      -2407,      -2465,      -2521,      -2577,      -2632,      -2687,      -2740,      -2793,      -2845,      -2896,      -2946,      -2995,      -3043,      -3091,      -3137,      -3183,      -3227,      -3271,      -3313,      -3355,      -3395,      -3435,      -3473,      -3510,      -3547,      -3582,      -3616,      -3649,      -3681,      -3712,      -3741,      -3770,      -3797,      -3823,      -3848,      -3872,      -3895,      -3917,      -3937,      -3956,      -3974,      -3991,      -4006,      -4020,      -4033,      -4045,      -4056,      -4065,      -4073,      -4080,      -4086,      -4090,      -4093,      -4095,      -4096,      -4095,      -4093,      -4090,      -4086,      -4080,      -4073,      -4065,      -4056,      -4045,      -4033,      -4020,      -4006,      -3991,      -3974,      -3956,      -3937,      -3917,      -3895,      -3872,      -3848,      -3823,      -3797,      -3770,      -3741,      -3712,      -3681,      -3649,      -3616,      -3582,      -3547,      -3510,      -3473,      -3435,      -3395,      -3355,      -3313,      -3271,      -3227,      -3183,      -3137,      -3091,      -3043,      -2995,      -2946,      -2896,      -2845,      -2793,      -2740,      -2687,      -2632,      -2577,      -2521,      -2465,      -2407,      -2349,      -2290,      -2230,      -2170,      -2109,      -2048,      -1985,      -1922,      -1859,      -1795,      -1731,      -1665,      -1600,      -1534,      -1467,      -1400,      -1333,      -1265,      -1197,      -1129,      -1060,      -990,       -921,       -851,       -781,       -711,       -640,       -570,       -499,       -428,       -356,       -285,       -214,       -142,       -71,        0
};
INTN myCos[361] =
{
	4096,       4095,       4093,       4090,       4086,       4080,       4073,       4065,       4056,       4045,       4033,       4020,       4006,       3991,       3974,       3956,       3937,       3917,       3895,       3872,       3848,       3823,       3797,       3770,       3741,       3712,       3681,       3649,       3616,       3582,       3547,       3510,       3473,       3435,       3395,       3355,       3313,       3271,       3227,       3183,       3137,       3091,       3043,       2995,       2946,       2896,       2845,       2793,       2740,       2687,       2632,       2577,       2521,       2465,       2407,       2349,       2290,       2230,       2170,       2109,       2048,       1985,       1922,       1859,       1795,       1731,       1665,       1600,       1534,       1467,       1400,       1333,       1265,       1197,       1129,       1060,       990,        921,        851,        781,        711,        640,        570,        499,        428,        356,        285,        214,        142,        71,         0,          -71,        -142,       -214,       -285,       -356,       -428,       -499,       -570,       -640,       -711,       -781,       -851,       -921,       -990,       -1060,      -1129,      -1197,      -1265,      -1333,      -1400,      -1467,      -1534,      -1600,      -1665,      -1731,      -1795,      -1859,      -1922,      -1985,      -2047,      -2109,      -2170,      -2230,      -2290,      -2349,      -2407,      -2465,      -2521,      -2577,      -2632,      -2687,      -2740,      -2793,      -2845,      -2896,      -2946,      -2995,      -3043,      -3091,      -3137,      -3183,      -3227,      -3271,      -3313,      -3355,      -3395,      -3435,      -3473,      -3510,      -3547,      -3582,      -3616,      -3649,      -3681,      -3712,      -3741,      -3770,      -3797,      -3823,      -3848,      -3872,      -3895,      -3917,      -3937,      -3956,      -3974,      -3991,      -4006,      -4020,      -4033,      -4045,      -4056,      -4065,      -4073,      -4080,      -4086,      -4090,      -4093,      -4095,      -4096,      -4095,      -4093,      -4090,      -4086,      -4080,      -4073,      -4065,      -4056,      -4045,      -4033,      -4020,      -4006,      -3991,      -3974,      -3956,      -3937,      -3917,      -3895,      -3872,      -3848,      -3823,      -3797,      -3770,      -3741,      -3712,      -3681,      -3649,      -3616,      -3582,      -3547,      -3510,      -3473,      -3435,      -3395,      -3355,      -3313,      -3271,      -3227,      -3183,      -3137,      -3091,      -3043,      -2995,      -2946,      -2896,      -2845,      -2793,      -2740,      -2687,      -2632,      -2577,      -2521,      -2465,      -2407,      -2349,      -2290,      -2230,      -2170,      -2109,      -2048,      -1985,      -1922,      -1859,      -1795,      -1731,      -1665,      -1600,      -1534,      -1467,      -1400,      -1333,      -1265,      -1197,      -1129,      -1060,      -990,       -921,       -851,       -781,       -711,       -640,       -570,       -499,       -428,       -356,       -285,       -214,       -142,       -71,        0,          71,         142,        214,        285,        356,        428,        499,        570,        640,        711,        781,        851,        921,        990,        1060,       1129,       1197,       1265,       1333,       1400,       1467,       1534,       1600,       1665,       1731,       1795,       1859,       1922,       1985,       2047,       2109,       2170,       2230,       2290,       2349,       2407,       2465,       2521,       2577,       2632,       2687,       2740,       2793,       2845,       2896,       2946,       2995,       3043,       3091,       3137,       3183,       3227,       3271,       3313,       3355,       3395,       3435,       3473,       3510,       3547,       3582,       3616,       3649,       3681,       3712,       3741,       3770,       3797,       3823,       3848,       3872,       3895,       3917,       3937,       3956,       3974,       3991,       4006,       4020,       4033,       4045,       4056,       4065,       4073,       4080,       4086,       4090,       4093,       4095,       4096
};

EFI_SYSTEM_TABLE     *gST;
EFI_BOOT_SERVICES    *gBS;
EFI_RUNTIME_SERVICES *gRT;
EFI_GRAPHICS_OUTPUT_BLT_PIXEL *gCanvasBuffer = NULL;

INTN gXCoordinate = 120;
INTN gYCoordinate = 250;

INTN gVelocity = 5;
INTN gBirdForwardSpeed = BACK_SPEED;

EFI_EVENT gEvents[2];

//Global
AnimaiotnObject bird;
Object score[10];
Object tuto;
Object land[2];
Pipe pipe[2];

GameOver gameOver;

//useless
EFI_GRAPHICS_OUTPUT_BLT_PIXEL *ScoreImage[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer = NULL;//,*BirdBltBuffer = NULL;

UINTN w, h;
/*UINTN bw, bh;
UINTN sw, sh;
UINTN sw1, sh1;*/

UINT8
IsCollision(
    IN  Info object1,
    IN  Info object2
)
{
	object1.pos.x += 7;
	object1.pos.y += 7;

	object1.width -= 7;
	object1.height -= 7;

	if (object1.pos.x < object2.pos.x + (INTN)object2.width &&
	        object1.pos.x + (INTN)object1.width > object2.pos.x &&
	        object1.pos.y < object2.pos.y + (INTN)object2.height &&
	        (INTN)object1.height + object1.pos.y > object2.pos.y) {
		return 1;
	}
	else
		return 0;

}

UINTN
Rotate(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput,
    IN  AnimaiotnObject *bird, UINT16 angle
)
{
	INTN sina = mySin[angle];
	INTN cosa = myCos[angle];

	Point pLT, pRT, pLB, pRB;
	Point pLTN, pRTN, pLBN, pRBN;
	INTN srcW = bird->info.width;
	INTN srcH = bird->info.height;

	pLT.x = -srcW / 2; pLT.y = srcH / 2;
	pRT.x = srcW / 2; pRT.y = srcH / 2;
	pLB.x = -srcW / 2; pLB.y = -srcH / 2;
	pRB.x = srcW / 2; pRB.y = -srcH / 2;

	pLTN.x = (pLT.x * cosa >> 12) + ( (pLT.y * sina) >> 12);
	pLTN.y = ((-pLT.x * sina) >> 12) + (pLT.y * cosa >> 12);
	pRTN.x = (pRT.x * cosa >> 12) + ((pRT.y * sina) >> 12);
	pRTN.y = ((-pRT.x * sina) >> 12) + (pRT.y * cosa >> 12);
	pLBN.x = (pLB.x * cosa >> 12) + ((pLB.y * sina) >> 12);
	pLBN.y = ((-pLB.x * sina) >> 12) + (pLB.y * cosa >> 12);
	pRBN.x = (pRB.x * cosa >> 12) + ((pRB.y * sina) >> 12);
	pRBN.y = ((-pRB.x * sina) >> 12) + (pRB.y * cosa >> 12);


	INTN desWidth = max(abs(pRBN.x - pLTN.x), abs(pRTN.x - pLBN.x));
	INTN desHeight = max(abs(pRBN.y - pLTN.y), abs(pRTN.y - pLBN.y));


	INTN desLineSize = ((desWidth * 8 + 31) / 32) * 4;
	INTN i, j;

	INTN desBufSize = desWidth * desHeight * 8 / 8;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *desBuf = AllocateZeroPool(sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * desBufSize);

	if (desBuf == NULL) {
		Print(L"EFI_OUT_OF_RESOURCES  blt\n");
		return EFI_OUT_OF_RESOURCES;
	}


	for (i = 0; i < desHeight; i++)
	{
		for (j = 0; j < desWidth; j++)
		{
			INTN tX = ((j - desWidth / 2) * myCos[360 - angle] >> 12) + ((-i + desHeight / 2) * mySin[360 - angle] >> 12);
			INTN tY = (-(j - desWidth / 2) * mySin[360 - angle] >> 12) + ((-i + desHeight / 2) * myCos[360 - angle] >> 12);

			desBuf[i * desLineSize + j * 8 / 8].Blue = 255;

			desBuf[i * desLineSize + j * 8 / 8].Red = 255;

			if (tX > srcW / 2 || tX < -srcW / 2 || tY > srcH / 2 || tY < -srcH / 2)
			{
				continue;
			}
			INTN tXN = tX + srcW / 2; INTN tYN = abs(tY - srcH / 2);
			desBuf[i * desLineSize + j * 8 / 8].Blue = bird->Image[0][(tYN * srcW + tXN) * 8 / 8].Blue;
			desBuf[i * desLineSize + j * 8 / 8].Green = bird->Image[0][(tYN * srcW + tXN) * 8 / 8].Green;
			desBuf[i * desLineSize + j * 8 / 8].Red = bird->Image[0][(tYN * srcW + tXN) * 8 / 8].Red;
			desBuf[i * desLineSize + j * 8 / 8].Reserved = bird->Image[0][(tYN * srcW + tXN) * 8 / 8].Reserved;
		}
	}

	DrawGraphic (GraphicsOutput, desBuf, bird->info.pos.x, bird->info.pos.y, desWidth, desHeight, NULL);

	FreePool(desBuf);
	return EFI_OUT_OF_RESOURCES;

}

VOID
OnBird(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput,
    IN  AnimaiotnObject *bird,
    IN  EFI_INPUT_KEY key,
    IN  UINTN frame,
    IN  INTN *isTutorial)
{
	static UINT8 birdFrame = 0;
	if (frame % 10 == 0) {
		gVelocity += 2;
		//gBirdForwardSpeed++;
		birdFrame ++;
		if (birdFrame == 3)
			birdFrame = 0;
	}

	if (key.ScanCode == 4)gXCoordinate--;
	if (key.ScanCode == 3)gXCoordinate++;
	if (key.ScanCode == 1)
	{
		*isTutorial = 0;
		gVelocity = -5; //jump}
	}
	if (key.ScanCode == 2)gYCoordinate++;


	if (!*isTutorial)
		bird->info.pos.y += gVelocity;


	if (bird->info.pos.y >= 400)
		bird->info.pos.y = 400;

	/*if (v > 5)

		Rotate(GraphicsOutput, bird, 90);
	else
		Rotate(GraphicsOutput, bird, 30);*/

	DrawGraphic (GraphicsOutput, bird->Image[birdFrame], bird->info.pos.x, bird->info.pos.y, bird->info.width, bird->info.height, NULL);
}

void 
ObjectInit()
{
	bird.info.pos.x = 120;
	bird.info.pos.y = 200;

	land[0].info.pos.x = 0;
	land[0].info.pos.y = 400;
	land[1] = land[0];
	land[1].info.pos.x = land[0].info.width;
	land[1].info.pos.y = 400;

	pipe[0].info.pos.x = 500;
	pipe[0].info.pos.y = -200;
	pipe[1].info.pos.x = 500;
	pipe[1].info.pos.y = pipe[0].info.pos.y + 500;

	gameOver.info.pos.x = 40;
	gameOver.info.pos.y = 100;

	tuto.info.pos.x = 100;
	tuto.info.pos.y = 300;
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

EFI_STATUS 
LoadFromPCX(
    IN  UINT8 *Buffer,
    IN  UINTN BufferSize,
    OUT UINTN * width,
    OUT UINTN * height, UINT8 **bltBuffer)
{
	EFI_STATUS             Status;
	UINTN                  BltSize;
	UINTN                  Width;
	UINTN                  Height;
	Print(L"BufferSize:%x\n", BufferSize);
	Status = PcxDecoderDecodeImage (
	             Buffer,
	             BufferSize,
	             bltBuffer,
	             &BltSize,
	             &Height,
	             &Width
	         );

	*width = Width;
	*height = Height;

	if (EFI_ERROR (Status)) {
		return Status;
	}
	return Status;
}


EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE * SystemTable
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput;
	VOID *BmpBuffer = NULL;
	UINTN Index;
//VOID *BackBmpBuffer = NULL;
//UINTN BackBmpSize;
//VOID *BackBmpBuffer2 = NULL;
//UINTN BackBmpSize2;
//VOID *BlackBmpBuffer = NULL;
//UINTN BlackBmpSize;
	//INT32 offset = 5;
//CHAR16 *String1 = L"PciDump is written by MelosCheng 2011. All right is reserved.\n";

// UINT32 PciSpace[256/4];
//EFI_GRAPHICS_OUTPUT_BLT_PIXEL mBlack = {0, 0, 1};
	EFI_EVENT mEvent;
//
	gST = SystemTable;
	gBS = gST->BootServices;
	gRT = gST->RuntimeServices;
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
	    &mEvent
	);
	gBS->SetTimer (
	    mEvent,
	    TimerPeriodic,
	    10 * 1000 * 1000 / 60
	);
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *textOutput = NULL;
	Status = gBS -> LocateProtocol (
	             &gEfiSimpleTextOutProtocolGuid,
	             NULL,
	             &textOutput
	         );
	if (EFI_ERROR(Status)) {
		Print(L"Handle Protocol by textOutput fail...\n");
	}

	//EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BirdAnimation[3] = {NULL, NULL, NULL};
	//Bird bird;
	//bird.info.pos.x = 120;
	//bird.info.pos.y = 250;
	//static INTN pipeX = 100;
	//static INTN pipeY0 = -100;
	//static INTN pipeY1 = 400;
	//EFI_GRAPHICS_OUTPUT_BLT_PIXEL *PipeImage[2] = {NULL, NULL};
	//Status = LoadBitmapFile (L"bg_day.bmp", &w, &h, &BltBuffer);

	LoadFromPCX(bg_day, sizeof(bg_day), &w, &h, (UINT8**)&BltBuffer);
	w = 288;
	h = 512;

	if (EFI_ERROR (Status)) {
		if (BmpBuffer != NULL) {
			FreePool (BmpBuffer);
			//DEBUG ((EFI_D_ERROR, "%r on Open file.\n", Status));
			return Status;
		}
	}


	//Loading res
	bird.Image = ANIMATION_CREATE(3);

	LoadFromPCX(landPcx, sizeof(landPcx), &land[0].info.width, &land[0].info.height, (UINT8**)&land[0].Image);
	//Status = LoadBitmapFile (L"bird0_0.bmp", &bird.info.width, &bird.info.height, &bird.Image[0]);
	//Status = LoadBitmapFile (L"bird0_1.bmp", &bw, &bh, &bird.Image[1]);
	//Status = LoadBitmapFile (L"bird0_2.bmp", &bw, &bh, &bird.Image[2]);
	LoadFromPCX(bird0_0, sizeof(bird0_0), &bird.info.width, &bird.info.height, (UINT8**)&bird.Image[0]);
	LoadFromPCX(bird0_1, sizeof(bird0_1), &bird.info.width, &bird.info.height, (UINT8**)&bird.Image[1]);
	LoadFromPCX(bird0_2, sizeof(bird0_2), &bird.info.width, &bird.info.height, (UINT8**)&bird.Image[2]);
	LoadFromPCX(pipe_down, sizeof(pipe_down), &pipe[0].info.width, &pipe[0].info.height, (UINT8**)&pipe[0].PipeImage);
	LoadFromPCX(pipe_up, sizeof(pipe_up), &pipe[1].info.width, &pipe[1].info.height, (UINT8**)&pipe[1].PipeImage);
	/*Status = LoadBitmapFile (L"pipe_down.bmp", &pipe[0].info.width, &pipe[0].info.height, &pipe[0].PipeImage);
	Status = LoadBitmapFile (L"pipe_up.bmp", &pipe[1].info.width, &pipe[1].info.height, &pipe[1].PipeImage);*/
	/*Status = LoadBitmapFile (L"font_048.bmp", &score[0].info.width, &score[0].info.height, &score[0].Image);
	Status = LoadBitmapFile (L"font_049.bmp",  &score[1].info.width, &score[1].info.height, &score[1].Image);
	Status = LoadBitmapFile (L"font_050.bmp",  &score[2].info.width, &score[2].info.height, &score[2].Image);
	Status = LoadBitmapFile (L"font_051.bmp",  &score[3].info.width, &score[3].info.height, &score[3].Image);
	Status = LoadBitmapFile (L"font_052.bmp",  &score[4].info.width, &score[4].info.height, &score[4].Image);
	Status = LoadBitmapFile (L"font_053.bmp",  &score[5].info.width, &score[5].info.height, &score[5].Image);
	Status = LoadBitmapFile (L"font_054.bmp",  &score[6].info.width, &score[6].info.height, &score[6].Image);
	Status = LoadBitmapFile (L"font_055.bmp",  &score[7].info.width, &score[7].info.height, &score[7].Image);
	Status = LoadBitmapFile (L"font_056.bmp",  &score[8].info.width, &score[8].info.height, &score[8].Image);
	Status = LoadBitmapFile (L"font_057.bmp",  &score[9].info.width, &score[9].info.height, &score[9].Image);*/

	LoadFromPCX(font_048, sizeof(font_048), &score[0].info.width, &score[0].info.height, (UINT8**)&score[0].Image);
	LoadFromPCX(font_049, sizeof(font_049), &score[1].info.width, &score[1].info.height, (UINT8**)&score[1].Image);
	LoadFromPCX(font_050, sizeof(font_050), &score[2].info.width, &score[2].info.height, (UINT8**)&score[2].Image);
	LoadFromPCX(font_051, sizeof(font_051), &score[3].info.width, &score[3].info.height, (UINT8**)&score[3].Image);
	LoadFromPCX(font_052, sizeof(font_052), &score[4].info.width, &score[4].info.height, (UINT8**)&score[4].Image);
	LoadFromPCX(font_053, sizeof(font_053), &score[5].info.width, &score[5].info.height, (UINT8**)&score[5].Image);
	LoadFromPCX(font_054, sizeof(font_054), &score[6].info.width, &score[6].info.height, (UINT8**)&score[6].Image);
	LoadFromPCX(font_055, sizeof(font_055), &score[7].info.width, &score[7].info.height, (UINT8**)&score[7].Image);
	LoadFromPCX(font_056, sizeof(font_056), &score[8].info.width, &score[8].info.height, (UINT8**)&score[8].Image);
	LoadFromPCX(font_057, sizeof(font_057), &score[9].info.width, &score[9].info.height, (UINT8**)&score[9].Image);

	LoadFromPCX(tutorial, sizeof(tutorial),  &tuto.info.width, &tuto.info.height, (UINT8**)&tuto.Image);

	//Status = LoadBitmapFile (L"tutorial.bmp",  &tuto.info.width, &tuto.info.height, &tuto.Image);

	LoadFromPCX(text_game_over, sizeof(text_game_over),  &gameOver.info.width, &gameOver.info.height, (UINT8**)&gameOver.GameOverImage);
	//Status = LoadBitmapFile (L"text_game_over.bmp", &gameOver.info.width, &gameOver.info.height, &gameOver.GameOverImage);

	ObjectInit();

	static UINT8 scoreNum = 0;

	static UINT8 isGameOver = 0;
	static INTN isTutorial = 1;

	gCanvasBuffer = AllocateZeroPool (
	                    sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * CANVAS_W * CANVAS_H
	                );
	if (BltBuffer == NULL) {
		return EFI_OUT_OF_RESOURCES;
	}
	gEvents[0] = gST->ConIn->WaitForKey;
	gEvents[1] = mEvent;
	EFI_INPUT_KEY Key;
	Key.ScanCode = SCAN_NULL;
	do {
//textOutput->ClearScreen(textOutput);
//gBS->WaitForEvent (1, &gST->ConIn->WaitForKey, &Index);
//gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
//Print(L"input key:%d\n",Key.ScanCode );
		gBS->WaitForEvent (2, gEvents, &Index);
//if(Index ==0)
//{
		if (Index == 0) {
			gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);
			continue;
		}
		else
		{

			if (Key.ScanCode == SCAN_END)
				break;

			static UINTN frame = 0;

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

			static UINT8 l = 0;
			static INTN X = 0;
			static INTN X2 = CANVAS_W;

			Status = DrawGraphic (GraphicsOutput, BltBuffer, X, 0, w, h, NULL);
			Status = DrawGraphic (GraphicsOutput, BltBuffer, X2, 0, w, h, NULL);

			Status = DrawGraphic (GraphicsOutput, pipe[0].PipeImage, pipe[0].info.pos.x, pipe[0].info.pos.y, pipe[0].info.width, pipe[0].info.height, NULL);
			Status = DrawGraphic (GraphicsOutput, pipe[1].PipeImage, pipe[1].info.pos.x, pipe[1].info.pos.y, pipe[1].info.width, pipe[1].info.height, NULL);

			Status = DrawGraphic (GraphicsOutput, land[0].Image, land[0].info.pos.x, land[0].info.pos.y, land[0].info.width, land[0].info.height, NULL);
			Status = DrawGraphic (GraphicsOutput, land[1].Image, land[1].info.pos.x, land[1].info.pos.y, land[1].info.width, land[1].info.height, NULL);

			Status = DrawGraphic (GraphicsOutput, score[scoreNum % 10].Image, 145, 20, score[scoreNum % 10].info.width, score[scoreNum % 10].info.height, NULL);
			Status = DrawGraphic (GraphicsOutput, score[scoreNum / 10].Image, 120, 20, score[scoreNum / 10].info.width, score[scoreNum / 10].info.height, NULL);

			if (!isGameOver  && !isTutorial)
			{

				if (frame % 10 == 0) {
					X -= gBirdForwardSpeed;
					X2 -= gBirdForwardSpeed;
				}
				pipe[0].info.pos.x -= gBirdForwardSpeed;
				pipe[1].info.pos.x -= gBirdForwardSpeed;

				land[0].info.pos.x -= gBirdForwardSpeed;
				land[1].info.pos.x -= gBirdForwardSpeed;

				if (land[0].info.pos.x <= -(INTN)land[0].info.width)
					land[0].info.pos.x = 0;

				if (land[1].info.pos.x <= 0)
					land[1].info.pos.x = land[0].info.width;

				if (X <= -CANVAS_W)
					X = 0;
				if (X2 <= 0)
					X2 = CANVAS_W;

				if (pipe[0].info.pos.x <= -100) {
					pipe[0].info.pos.x = CANVAS_W;
					pipe[1].info.pos.x = CANVAS_W;
					l = 0;

					INTN nSeed;
					nSeed = RandomInitSeed();
					pipe[0].info.pos.y = nSeed % 100  - 200;
					pipe[1].info.pos.y = pipe[0].info.pos.y + 500;

				}
				if (pipe[0].info.pos.x < bird.info.pos.x && !l)
				{
					l = 1;
					scoreNum++;
				}
				if (IsCollision(bird.info , pipe[0].info) || IsCollision(bird.info , pipe[1].info) || IsCollision(bird.info , land[0].info) || IsCollision(bird.info , land[1].info))
				{
					isGameOver = 1;
					gBirdForwardSpeed = 0;
					gVelocity = 10;
				}
				if (frame % 1000 == 0)
				{

					if (gBirdForwardSpeed < 10)
						gBirdForwardSpeed++;
				}
			}

			if (isGameOver)
			{
				Status = DrawGraphic (GraphicsOutput, gameOver.GameOverImage, gameOver.info.pos.x, gameOver.info.pos.y, gameOver.info.width, gameOver.info.height, NULL);
				if (Key.ScanCode == SCAN_UP)
				{
					ObjectInit();
					isGameOver = 0;
					gVelocity = 5;
					gBirdForwardSpeed = 1;
					scoreNum = 0;
					frame = 0;
					isTutorial = 1;
					Key.ScanCode = SCAN_NULL;
				}
			}

			OnBird(GraphicsOutput, &bird, Key, frame, &isTutorial);

			if (Key.ScanCode == SCAN_F1)
			{
				ObjectInit();
				isGameOver = 0;
				gVelocity = 5;
				gBirdForwardSpeed = 1;
				scoreNum = 0;
				frame = 0;
				isTutorial = 1;
			}

			if (isTutorial)
			{
				Status = DrawGraphic (GraphicsOutput, tuto.Image, tuto.info.pos.x, tuto.info.pos.y, tuto.info.width, tuto.info.height, NULL);
				OnBird(GraphicsOutput, &bird, Key, frame, &isTutorial);
			}

			Status = GraphicsOutput->Blt (
			             GraphicsOutput,
			             gCanvasBuffer,
			             EfiBltBufferToVideo,
			             0 , 0 ,
			             CANVAS_X , CANVAS_Y , //xy
			             288, 512,
			             0
			         );

			frame++;

		}
		Key.ScanCode = SCAN_NULL;
	} while (Key.ScanCode != SCAN_END);//Key.ScanCode != SCAN_END
	return EFI_SUCCESS;
}
