//**********************************************************************
// Author:      Billy Huang
// Date:        2015.08.11
//**********************************************************************

#include "GraphicUtility.h"
#include "Object.h"

//My Fast Math Table
INTN mySin[361] =
{
	0,  71, 142, 214, 285, 356, 428, 499, 570, 640, 711, 781, 851, 921, 990, 1060, 1129, 1197, 1265, 1333, 1400, 1467, 1534, 1600, 1665, 1731, 1795, 1859, 1922, 1985, 2047, 2109, 2170, 2230, 2290, 2349, 2407, 2465, 2521, 2577, 2632, 2687, 2740, 2793, 2845, 2896, 2946, 2995, 3043, 3091, 3137, 3183, 3227, 3271, 3313, 3355, 3395, 3435, 3473, 3510, 3547, 3582, 3616, 3649, 3681, 3712, 3741, 3770, 3797, 3823, 3848, 3872, 3895, 3917, 3937, 3956, 3974, 3991, 4006, 4020, 4033, 4045, 4056, 4065, 4073, 4080, 4086, 4090, 4093, 4095, 4096, 4095, 4093, 4090, 4086, 4080, 4073, 4065, 4056, 4045, 4033, 4020, 4006, 3991, 3974, 3956, 3937, 3917, 3895, 3872, 3848, 3823, 3797, 3770, 3741, 3712, 3681, 3649, 3616, 3582, 3547, 3510, 3473, 3435, 3395, 3355, 3313, 3271, 3227, 3183, 3137, 3091, 3043, 2995, 2946, 2896, 2845, 2793, 2740, 2687, 2632, 2577, 2521, 2465, 2407, 2349, 2290, 2230, 2170, 2109, 2048, 1985, 1922, 1859, 1795, 1731, 1665, 1600, 1534, 1467, 1400, 1333, 1265, 1197, 1129, 1060, 990, 921, 851, 781, 711, 640, 570, 499, 428, 356, 285, 214, 142, 71, 0,  -71, -142, -214, -285, -356, -428, -499, -570, -640, -711, -781, -851, -921, -990, -1060,      -1129,      -1197,      -1265,      -1333,      -1400,      -1467,      -1534,      -1600,      -1665,      -1731,      -1795,      -1859,      -1922,      -1985,      -2047,      -2109,      -2170,      -2230,      -2290,      -2349,      -2407,      -2465,      -2521,      -2577,      -2632,      -2687,      -2740,      -2793,      -2845,      -2896,      -2946,      -2995,      -3043,      -3091,      -3137,      -3183,      -3227,      -3271,      -3313,      -3355,      -3395,      -3435,      -3473,      -3510,      -3547,      -3582,      -3616,      -3649,      -3681,      -3712,      -3741,      -3770,      -3797,      -3823,      -3848,      -3872,      -3895,      -3917,      -3937,      -3956,      -3974,      -3991,      -4006,      -4020,      -4033,      -4045,      -4056,      -4065,      -4073,      -4080,      -4086,      -4090,      -4093,      -4095,      -4096,      -4095,      -4093,      -4090,      -4086,      -4080,      -4073,      -4065,      -4056,      -4045,      -4033,      -4020,      -4006,      -3991,      -3974,      -3956,      -3937,      -3917,      -3895,      -3872,      -3848,      -3823,      -3797,      -3770,      -3741,      -3712,      -3681,      -3649,      -3616,      -3582,      -3547,      -3510,      -3473,      -3435,      -3395,      -3355,      -3313,      -3271,      -3227,      -3183,      -3137,      -3091,      -3043,      -2995,      -2946,      -2896,      -2845,      -2793,      -2740,      -2687,      -2632,      -2577,      -2521,      -2465,      -2407,      -2349,      -2290,      -2230,      -2170,      -2109,      -2048,      -1985,      -1922,      -1859,      -1795,      -1731,      -1665,      -1600,      -1534,      -1467,      -1400,      -1333,      -1265,      -1197,      -1129,      -1060,      -990, -921, -851, -781, -711, -640, -570, -499, -428, -356, -285, -214, -142, -71, 0
};
INTN myCos[361] =
{
	4096, 4095, 4093, 4090, 4086, 4080, 4073, 4065, 4056, 4045, 4033, 4020, 4006, 3991, 3974, 3956, 3937, 3917, 3895, 3872, 3848, 3823, 3797, 3770, 3741, 3712, 3681, 3649, 3616, 3582, 3547, 3510, 3473, 3435, 3395, 3355, 3313, 3271, 3227, 3183, 3137, 3091, 3043, 2995, 2946, 2896, 2845, 2793, 2740, 2687, 2632, 2577, 2521, 2465, 2407, 2349, 2290, 2230, 2170, 2109, 2048, 1985, 1922, 1859, 1795, 1731, 1665, 1600, 1534, 1467, 1400, 1333, 1265, 1197, 1129, 1060, 990, 921, 851, 781, 711, 640, 570, 499, 428, 356, 285, 214, 142, 71, 0,  -71, -142, -214, -285, -356, -428, -499, -570, -640, -711, -781, -851, -921, -990, -1060,      -1129,      -1197,      -1265,      -1333,      -1400,      -1467,      -1534,      -1600,      -1665,      -1731,      -1795,      -1859,      -1922,      -1985,      -2047,      -2109,      -2170,      -2230,      -2290,      -2349,      -2407,      -2465,      -2521,      -2577,      -2632,      -2687,      -2740,      -2793,      -2845,      -2896,      -2946,      -2995,      -3043,      -3091,      -3137,      -3183,      -3227,      -3271,      -3313,      -3355,      -3395,      -3435,      -3473,      -3510,      -3547,      -3582,      -3616,      -3649,      -3681,      -3712,      -3741,      -3770,      -3797,      -3823,      -3848,      -3872,      -3895,      -3917,      -3937,      -3956,      -3974,      -3991,      -4006,      -4020,      -4033,      -4045,      -4056,      -4065,      -4073,      -4080,      -4086,      -4090,      -4093,      -4095,      -4096,      -4095,      -4093,      -4090,      -4086,      -4080,      -4073,      -4065,      -4056,      -4045,      -4033,      -4020,      -4006,      -3991,      -3974,      -3956,      -3937,      -3917,      -3895,      -3872,      -3848,      -3823,      -3797,      -3770,      -3741,      -3712,      -3681,      -3649,      -3616,      -3582,      -3547,      -3510,      -3473,      -3435,      -3395,      -3355,      -3313,      -3271,      -3227,      -3183,      -3137,      -3091,      -3043,      -2995,      -2946,      -2896,      -2845,      -2793,      -2740,      -2687,      -2632,      -2577,      -2521,      -2465,      -2407,      -2349,      -2290,      -2230,      -2170,      -2109,      -2048,      -1985,      -1922,      -1859,      -1795,      -1731,      -1665,      -1600,      -1534,      -1467,      -1400,      -1333,      -1265,      -1197,      -1129,      -1060,      -990, -921, -851, -781, -711, -640, -570, -499, -428, -356, -285, -214, -142, -71, 0,  71, 142, 214, 285, 356, 428, 499, 570, 640, 711, 781, 851, 921, 990, 1060, 1129, 1197, 1265, 1333, 1400, 1467, 1534, 1600, 1665, 1731, 1795, 1859, 1922, 1985, 2047, 2109, 2170, 2230, 2290, 2349, 2407, 2465, 2521, 2577, 2632, 2687, 2740, 2793, 2845, 2896, 2946, 2995, 3043, 3091, 3137, 3183, 3227, 3271, 3313, 3355, 3395, 3435, 3473, 3510, 3547, 3582, 3616, 3649, 3681, 3712, 3741, 3770, 3797, 3823, 3848, 3872, 3895, 3917, 3937, 3956, 3974, 3991, 4006, 4020, 4033, 4045, 4056, 4065, 4073, 4080, 4086, 4090, 4093, 4095, 4096
};

EFI_STATUS
LoadFromPCX(
    IN  UINT8 *Buffer,
    IN  UINTN BufferSize,
    OUT UINTN * width,
    OUT UINTN * height, 
    UINT8 **bltBuffer)
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
LoadGraphicFromFile (
    IN CHAR16 * Path,
    OUT UINTN * Width,
    OUT UINTN * Height,
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL **BltBuffer
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFile;
	EFI_FILE_PROTOCOL *Root;
	EFI_FILE_PROTOCOL *File;
	UINTN BufferSize;
	VOID *Buffer = NULL;
	Status = gBS->LocateProtocol (
	             &gEfiSimpleFileSystemProtocolGuid,
	             NULL,
	             &SimpleFile
	         );
	if (EFI_ERROR (Status)) {
		Print(L"%r on Locate EFI Simple File System Protocol.\n", Status);
		//DEBUG ((EFI_D_ERROR, "%r on Locate EFI Simple File System Protocol.\n", Status);
		return Status;
	}
	Status = SimpleFile->OpenVolume (SimpleFile, &Root);
	if (EFI_ERROR (Status)) {
		Print(L"%r on Open volume.\n", Status);
		DEBUG ((EFI_D_ERROR, "%r on Open volume.\n", Status));
		return Status;
	}
	Status = Root->Open (Root, &File, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if (EFI_ERROR (Status)) {
		Print(L"%r on Open file.\n", Status);
		DEBUG ((EFI_D_ERROR, "%r on Open file.\n", Status));
		return Status;
	}
	BufferSize = MAX_BUFFER_SIZE;
	Buffer = AllocatePool (BufferSize);
	if (Buffer == NULL) {
		Print(L"EFI_OUT_OF_RESOURCES\n", Status);
		return EFI_OUT_OF_RESOURCES;
	}
	Status = File->Read (
	             File,
	             &BufferSize,
	             Buffer
	         );
	if (BufferSize == MAX_BUFFER_SIZE) {
		DEBUG ((EFI_D_ERROR, "Buffer Size Too Small.\n"));
		Print(L"Buffer Size Too Small.\n", Status);
		if (Buffer != NULL) {
			FreePool (Buffer);
		}
		return EFI_OUT_OF_RESOURCES;
	}

	BITMAP_FILE_HEADER *BitmapHeader;
	UINT8 *BitmapData;
	UINT32 *Palette;
	UINTN Pixels;
	UINTN XIndex;
	UINTN YIndex;
	UINTN Pos;
	UINTN BltPos;
	BitmapHeader = (BITMAP_FILE_HEADER *) Buffer;

	if (BitmapHeader->CoreHeaderSize != 40) {
		return EFI_UNSUPPORTED;
	}
	if (BitmapHeader->BitCount != 8) {
		return EFI_UNSUPPORTED;
	}
	BitmapData = (UINT8*)Buffer + BitmapHeader->Offset;
	Palette = (UINT32*) ((UINT8*)Buffer + 0x36);/*????*/
	*Width = BitmapHeader->Width;
	*Height = BitmapHeader->Height;
	Pixels = BitmapHeader->Width * BitmapHeader->Height;
	*BltBuffer = AllocateZeroPool (
	                 sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * Pixels
	             );
	if (BltBuffer == NULL) {
		Print(L"EFI_OUT_OF_RESOURCES  blt\n", Status);
		return EFI_OUT_OF_RESOURCES;
	}
	for (YIndex = BitmapHeader->Height; YIndex > 0; YIndex--) {
		for (XIndex = 0; XIndex < BitmapHeader->Width; XIndex++) {
			Pos = (YIndex - 1) * ((BitmapHeader->Width + 3) / 4) * 4 + XIndex;
			BltPos = (BitmapHeader->Height - YIndex) * BitmapHeader->Width + XIndex;
			(*BltBuffer)[BltPos].Blue = (UINT8) BitFieldRead32 (Palette[BitmapData[Pos]], 0 , 7 );
			(*BltBuffer)[BltPos].Green = (UINT8) BitFieldRead32 (Palette[BitmapData[Pos]], 8 , 15);
			(*BltBuffer)[BltPos].Red = (UINT8) BitFieldRead32 (Palette[BitmapData[Pos]], 16, 23);
			(*BltBuffer)[BltPos].Reserved = (UINT8) BitFieldRead32 (Palette[BitmapData[Pos]], 24, 31);
		}
	}

	if (File)
	{
		Status = Root->Close (File);
		Print(L"EFI_FILE_PROTOCOL Close file  %s\n", Path);
	}

	if (Root)
	{
		Root->Close (Root);
	}

	FreePool(Buffer);
	return EFI_SUCCESS;
}


EFI_STATUS
DrawGraphic (
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL * GraphicsOutput,
    IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL * BltBuffer,
    IN INTN X,
    IN INTN Y,
    IN INTN Width,
    IN INTN Height,
    OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL * BltOutBuffer
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	INTN XIndex;
	INTN YIndex;
	for (YIndex = Y; YIndex < Y + Height; YIndex++) {
		for (XIndex = X; XIndex < X + Width; XIndex++) {
			//Pos = (YIndex - 1) * ((BitmapHeader->Width + 3) / 4) * 4 + XIndex;
			UINTN BltPos = YIndex * CANVAS_W + XIndex;

			if (XIndex >= 0 && YIndex >= 0 && XIndex <= CANVAS_W && YIndex <= CANVAS_H)
			{
				if ( !( (*BltBuffer).Blue == 255 && (*BltBuffer).Red == 255
				        && (*BltBuffer).Green == 0 )  )
				{
					gCanvasBuffer[BltPos].Blue = (*BltBuffer).Blue;
					gCanvasBuffer[BltPos].Green = (*BltBuffer).Green;
					gCanvasBuffer[BltPos].Red = (*BltBuffer).Red;
					gCanvasBuffer[BltPos].Reserved = (*BltBuffer).Reserved;
				}
			}
			BltBuffer++;
		}
	}
	return Status;
}

UINTN
RotateImage(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput,
    IN  AnimationObject *bird, UINT16 angle
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
	FreePool(desBuf);

	return EFI_OUT_OF_RESOURCES;
}


