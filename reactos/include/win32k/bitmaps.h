#ifndef __WIN32K_BITMAPS_H
#define __WIN32K_BITMAPS_H

/* GDI logical bitmap object */
typedef struct _BITMAPOBJ
{
  SURFOBJ     SurfObj;
  FLONG	      flHooks;
  FLONG       flFlags;
  SIZE        dimension;    /* For SetBitmapDimension(), do NOT use
                               to get width/height of bitmap, use
                               bitmap.bmWidth/bitmap.bmHeight for
                               that */
#ifdef NTOS_MODE_USER
  PVOID BitsLock;
#else
  PFAST_MUTEX BitsLock;     /* You need to hold this lock before you touch
                               the actual bits in the bitmap */
#endif

  /* For device-independent bitmaps: */
  DIBSECTION *dib;
  HPALETTE hDIBPalette;
} BITMAPOBJ, *PBITMAPOBJ;

#define BITMAPOBJ_IS_APIBITMAP		0x1

/*  Internal interface  */

#define  BITMAPOBJ_AllocBitmap()  \
  ((HBITMAP) GDIOBJ_AllocObj (GDI_OBJECT_TYPE_BITMAP))
#define  BITMAPOBJ_FreeBitmap(hBMObj)  \
  GDIOBJ_FreeObj((HGDIOBJ) hBMObj, GDI_OBJECT_TYPE_BITMAP)
/* NOTE: Use shared locks! */
#define  BITMAPOBJ_LockBitmap(hBMObj) (PBITMAPOBJ)EngLockSurface((HSURF)hBMObj)
#define  BITMAPOBJ_UnlockBitmap(pBMObj) EngUnlockSurface(&pBMObj->SurfObj)
BOOL INTERNAL_CALL BITMAP_Cleanup(PVOID ObjectBody);

BOOL INTERNAL_CALL BITMAPOBJ_InitBitsLock(BITMAPOBJ *pBMObj);
#define BITMAPOBJ_LockBitmapBits(pBMObj) ExEnterCriticalRegionAndAcquireFastMutexUnsafe((pBMObj)->BitsLock)
#define BITMAPOBJ_UnlockBitmapBits(pBMObj) ExReleaseFastMutexUnsafeAndLeaveCriticalRegion((pBMObj)->BitsLock)
void INTERNAL_CALL BITMAPOBJ_CleanupBitsLock(BITMAPOBJ *pBMObj);

INT     FASTCALL BITMAPOBJ_GetWidthBytes (INT bmWidth, INT bpp);
HBITMAP FASTCALL BITMAPOBJ_CopyBitmap (HBITMAP  hBitmap);
INT     FASTCALL DIB_GetDIBWidthBytes (INT  width, INT  depth);
int     STDCALL  DIB_GetDIBImageBytes (INT  width, INT  height, INT  depth);
INT     FASTCALL DIB_BitmapInfoSize (const BITMAPINFO * info, WORD coloruse);
INT     STDCALL  BITMAP_GetObject(BITMAPOBJ * bmp, INT count, LPVOID buffer);
HBITMAP FASTCALL BitmapToSurf(PBITMAPOBJ BitmapObj, HDEV GDIDevice);

HBITMAP FASTCALL IntCreateCompatibleBitmap(PDC Dc, INT Width, INT Height);

/*  User Entry Points  */
BOOL
STDCALL
NtGdiAlphaBlend(
	HDC  hDCDest,
	INT  XOriginDest,
	INT  YOriginDest,
	INT  WidthDest,
	INT  HeightDest,
	HDC  hDCSrc,
	INT  XOriginSrc,
	INT  YOriginSrc,
	INT  WidthSrc,
	INT  HeightSrc,
	BLENDFUNCTION  BlendFunc);

BOOL
STDCALL
NtGdiBitBlt (
	HDC	hDCDest,
	INT	XDest,
	INT	YDest,
	INT	Width,
	INT	Height,
	HDC	hDCSrc,
	INT	XSrc,
	INT	YSrc,
	DWORD	ROP
	);
HBITMAP
STDCALL
NtGdiCreateBitmap (
	INT		Width,
	INT		Height,
	UINT		Planes,
	UINT		BitsPerPel,
	CONST VOID	* Bits
	);
HBITMAP
STDCALL
NtGdiCreateCompatibleBitmap (
	HDC	hDC,
	INT	Width,
	INT	Height
	);
HBITMAP
STDCALL
NtGdiCreateBitmapIndirect (
	CONST BITMAP	* BM
	);
HBITMAP
STDCALL
NtGdiCreateDIBitmap (
	HDC			hDC,
	CONST BITMAPINFOHEADER	* bmih,
	DWORD			Init,
	CONST VOID		* bInit,
	CONST BITMAPINFO	* bmi,
	UINT			Usage
	);
HBITMAP
STDCALL
NtGdiCreateDIBSection (
	HDC			hDC,
	CONST BITMAPINFO	* bmi,
	UINT			Usage,
	VOID			* Bits,
	HANDLE			hSection,
	DWORD			dwOffset
	);
HBITMAP
STDCALL
NtGdiCreateDiscardableBitmap (
	HDC	hDC,
	INT	Width,
	INT	Height
	);
BOOL
STDCALL
NtGdiExtFloodFill (
	HDC		hDC,
	INT		XStart,
	INT		YStart,
	COLORREF	Color,
	UINT		FillType
	);
BOOL
STDCALL
NtGdiFloodFill (
	HDC		hDC,
	INT		XStart,
	INT		YStart,
	COLORREF	Fill
	);
LONG
STDCALL
NtGdiGetBitmapBits (
	HBITMAP	hBitmap,
	LONG	Buffer,
	LPVOID	Bits
	);
BOOL
STDCALL
NtGdiGetBitmapDimensionEx (
	HBITMAP	hBitmap,
	LPSIZE	Dimension
	);
UINT
STDCALL
NtGdiGetDIBColorTable (
	HDC	hDC,
	UINT	StartIndex,
	UINT	Entries,
	RGBQUAD	* Colors
	);
INT
STDCALL
NtGdiGetDIBits (
	HDC		hDC,
	HBITMAP		hBitmap,
	UINT		StartScan,
	UINT		ScanLines,
	LPVOID		Bits,
	LPBITMAPINFO	bi,
	UINT		Usage
	);
COLORREF
STDCALL
NtGdiGetPixel (
	HDC	hDC,
	INT	XPos,
	INT	YPos
	);
BOOL
STDCALL
NtGdiGradientFill (
	HDC hdc,
	PTRIVERTEX pVertex,
	ULONG uVertex,
	PVOID pMesh,
	ULONG uMesh,
	ULONG ulMode
	);
BOOL
STDCALL
NtGdiMaskBlt (
	HDC	hDCDest,
	INT	XDest,
	INT	YDest,
	INT	Width,
	INT	Height,
	HDC	hDCSrc,
	INT	XSrc,
	INT	YSrc,
	HBITMAP	hMaskBitmap,
	INT	xMask,
	INT	yMask,
	DWORD	ROP
	);
BOOL
STDCALL
NtGdiPlgBlt (
	HDC		hDCDest,
	CONST POINT	* Point,
	HDC		hDCSrc,
	INT		XSrc,
	INT		YSrc,
	INT		Width,
	INT		Height,
	HBITMAP		hMaskBitmap,
	INT		xMask,
	INT		yMask
	);
LONG
STDCALL
NtGdiSetBitmapBits (
	HBITMAP		hBitmap,
	DWORD		Bytes,
	CONST VOID	* Bits
	);
BOOL
STDCALL
NtGdiSetBitmapDimensionEx (
	HBITMAP	hBitmap,
	INT	Width,
	INT	Height,
	LPSIZE	Size
	);
UINT
STDCALL
NtGdiSetDIBColorTable (
	HDC		hDC,
	UINT		StartIndex,
	UINT		Entries,
	CONST RGBQUAD	* Colors
	);
INT
STDCALL
NtGdiSetDIBits (
	HDC			hDC,
	HBITMAP			hBitmap,
	UINT			StartScan,
	UINT			ScanLines,
	CONST VOID		* Bits,
	CONST BITMAPINFO	* bmi,
	UINT			ColorUse
	);
INT
STDCALL
NtGdiSetDIBitsToDevice (
	HDC			hDC,
	INT			XDest,
	INT			YDest,
	DWORD			Width,
	DWORD			Height,
	INT			XSrc,
	INT			YSrc,
	UINT			StartScan,
	UINT			ScanLines,
	CONST VOID		* Bits,
	CONST BITMAPINFO	* bmi,
	UINT			ColorUse
	);
COLORREF
STDCALL
NtGdiSetPixel (
	HDC		hDC,
	INT		X,
	INT		Y,
	COLORREF	Color
	);
BOOL
STDCALL
NtGdiSetPixelV (
	HDC		hDC,
	INT		X,
	INT		Y,
	COLORREF	Color
	);
BOOL
STDCALL
NtGdiStretchBlt (
	HDC	hDCDest,
	INT	XOriginDest,
	INT	YOriginDest,
	INT	WidthDest,
	INT	HeightDest,
	HDC	hDCSrc,
	INT	XOriginSrc,
	INT	YOriginSrc,
	INT	WidthSrc,
	INT	HeightSrc,
	DWORD	ROP
	);
INT
STDCALL
NtGdiStretchDIBits (
	HDC			hDC,
	INT			XDest,
	INT			YDest,
	INT			DestWidth,
	INT			DestHeight,
	INT			XSrc,
	INT			YSrc,
	INT			SrcWidth,
	INT			SrcHeight,
	CONST VOID		* Bits,
	CONST BITMAPINFO	* BitsInfo,
	UINT			Usage,
	DWORD			ROP
	);

BOOL
STDCALL
NtGdiTransparentBlt(
	HDC			hdcDst,
	INT			xDst,
	INT			yDst,
	INT			cxDst,
	INT			cyDst,
	HDC			hdcSrc,
	INT			xSrc,
	INT			ySrc,
	INT			cxSrc,
	INT			cySrc,
	COLORREF	TransColor
	);

#endif

