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

typedef struct _AnimationObject
{
	Info info;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL **Image;
} AnimationObject;

typedef struct _Object
{
	Info info;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Image;
} Object;

typedef struct _AnimaiotnObjectEx
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
} AnimaiotnObjectEx;


#pragma pack()