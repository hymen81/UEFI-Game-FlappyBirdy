//**********************************************************************
// Author:      Billy Huang
// Date:        2015.08.11
//**********************************************************************


#pragma pack(1)

typedef struct _Point
{
	INTN x;
	INTN y;
} Point;

typedef struct _Info
{
	Point pos;
	UINTN width;
	UINTN height;
} Info;

typedef struct _Bird
{
	Info info;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BirdImage[3];
} Bird;

typedef struct _Object
{
	Info info;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Image;
} Object;

typedef struct _AnimaiotnObject
{
	Info info;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL **Image;
	EFI_STATUS (*onDraw)(IN EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput,
	                     IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer,
	                     IN INTN X,
	                     IN INTN Y ,
	                     IN INTN Width,
	                     IN INTN Height,
	                     OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltOutBuffer);
} AnimaiotnObject;

typedef struct _Pipe
{
	Info info;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *PipeImage;
} Pipe;

typedef struct _GameOver
{
	Info info;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *GameOverImage;
} GameOver;

#pragma pack()