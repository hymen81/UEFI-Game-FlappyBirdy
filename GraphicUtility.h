//**********************************************************************
// Author:      Billy Huang
// Date:        2015.08.11
//**********************************************************************

#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/FileInfo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimpleFileSystem.h>

extern EFI_SYSTEM_TABLE *gST;
extern EFI_BOOT_SERVICES *gBS;
extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_GRAPHICS_OUTPUT_BLT_PIXEL *gCanvasBuffer;

#define MAX_BUFFER_SIZE SIZE_1MB
//Draw size
#define CANVAS_W      288
#define CANVAS_H      512
//Draw on screen offset
#define CANVAS_X      50
#define CANVAS_Y      50

typedef struct {
    CHAR8 Type[2];
    UINT32 Size;
    UINT32 Reserved;
    UINT32 Offset;
    UINT32 CoreHeaderSize;
    UINT32 Width;
    UINT32 Height;
    UINT16 Planes;
    UINT16 BitCount;
} BITMAP_FILE_HEADER;

EFI_STATUS
LoadGraphicFromFile (
    IN CHAR16 *Path,
    OUT UINTN *Width,
    OUT UINTN *Height,
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL **BltBuffer
);

EFI_STATUS
DrawGraphic (
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput,
    IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer,
    IN INTN X,
    IN INTN Y ,
    IN INTN Width,
    IN INTN Height,
    OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltOutBuffer
);
