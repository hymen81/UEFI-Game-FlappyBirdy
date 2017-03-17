//**********************************************************************
// Author:      Billy Huang
// Date:        2015.08.11
//**********************************************************************

#include "GraphicUtility.h"


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

