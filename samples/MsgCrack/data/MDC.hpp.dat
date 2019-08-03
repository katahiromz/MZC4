// MDC.hpp -- Win32API DC wrapper                               -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MDC_HPP_
#define MZC4_MDC_HPP_       3       /* Version 3 */

class MDC;
    class MMemoryDC;
    class MClientDC;
    class MPaintDC;
    class MWindowDC;

    class MMetaDC;
    class MEnhMetaDC;

///////////////////////////////////////////////////////////////////////////////

#ifndef HIMETRIC_INCH
    #define HIMETRIC_INCH   2540  // HIMETRIC units per inch
#endif

///////////////////////////////////////////////////////////////////////////////

#pragma comment(lib, "gdi32.lib")
#if (WINVER >= 0x0400)
    #pragma comment(lib, "msimg32.lib")
#endif

///////////////////////////////////////////////////////////////////////////////

#include "MBitmap.hpp"
#include "MPointSizeRect.hpp"

VOID GetDpiDx(FLOAT *xdpi, FLOAT *ydpi);
FLOAT GetXDpiDx(VOID);
FLOAT GetYDpiDx(VOID);
FLOAT XDpiScaleDx(FLOAT xPixels, FLOAT base_xdpi = 96.0f);
FLOAT YDpiScaleDx(FLOAT yPixels, FLOAT base_ydpi = 96.0f);

class MDC
{
public:
    HDC m_hDC;

public:
    MDC();
    MDC(HDC hDC);
    MDC& operator=(HDC hDC);
    virtual ~MDC();

    BOOL Attach(HDC hDC);
    HDC Detach(VOID);
    HDC Handle() const;

    operator HDC() const;
    bool operator!() const;

    HWND WindowFromDC() const;
    BOOL DeleteDC();

public:
    BOOL CreateDC(LPCTSTR pszDriver = NULL, LPCTSTR pszDevice = NULL,
        LPCTSTR pszOutput = NULL, CONST DEVMODE *lpInitData = NULL);
    BOOL CreateCompatibleDC(HDC hBaseDC = NULL);

    HPEN        GetCurrentPen() const;
    HBRUSH      GetCurrentBrush() const;
    HPALETTE    GetCurrentPalette() const;
    HFONT       GetCurrentFont() const;
    HBITMAP     GetCurrentBitmap() const;

    INT     SaveDC(VOID);
    BOOL    RestoreDC(INT nSavedDC);

    INT GetDeviceCaps(INT nIndex) const;
    UINT GetBoundsRect(LPRECT lpRectBounds, UINT uDCB_flags) const;
    UINT SetBoundsRect(LPCRECT lpRectBounds, UINT uDCB_flags);
    BOOL ResetDC(CONST DEVMODE *lpDevMode);
    BOOL GetBrushOrg(LPPOINT ppt) const;
    BOOL SetBrushOrg(INT x, INT y, LPPOINT ppt = NULL);
    BOOL SetBrushOrg(POINT pt, LPPOINT lpPointRet = NULL);

    INT EnumObjects(INT nObjectType, INT (CALLBACK* lpfn)(LPVOID, LPARAM),
                    LPARAM lpData);

    HGDIOBJ     SelectStockObject(INT nIndex);
    HPEN        SelectObject(HPEN hPen);
    HBRUSH      SelectObject(HBRUSH hBrush);
    HFONT       SelectObject(HFONT hFont);
    HBITMAP     SelectObject(HBITMAP hBitmap);
    INT         SelectObject(HRGN hRgn);
    HGDIOBJ     SelectObject(HGDIOBJ hGdiObj);
    HPALETTE    SelectPalette(HPALETTE hPal, BOOL bForceBackground = FALSE);

    COLORREF    GetNearestColor(COLORREF crColor) const;
    UINT        RealizePalette(VOID);
    VOID        UpdateColors(VOID);

    COLORREF GetBkColor() const;
    COLORREF SetBkColor(COLORREF crColor);

    COLORREF GetTextColor() const;
    COLORREF SetTextColor(COLORREF crColor);

#if (_WIN32_WINNT >= 0x0500)
    COLORREF GetDCBrushColor();
    COLORREF GetDCPenColor();
#endif  //  (_WIN32_WINNT >= 0x0500)

    INT GetBkMode() const;
    INT SetBkMode(INT nBkMode);
    INT GetPolyFillMode() const;
    INT SetPolyFillMode(INT nPolyFillMode);
    INT GetROP2() const;
    INT SetROP2(INT nR2_);
    INT GetStretchBltMode() const;
    INT SetStretchBltMode(INT nSTRETCH_);
    BOOL GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
    BOOL SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);
    INT GetMapMode() const;
    INT SetMapMode(INT nMapMode);

    BOOL GetViewportOrg(LPPOINT lpPoint) const;
    BOOL SetViewportOrg(INT x, INT y, LPPOINT lpPoint = NULL);
    BOOL SetViewportOrg(POINT pt, LPPOINT lpPointRet = NULL);
    BOOL OffsetViewportOrg(INT nWidth, INT nHeight, LPPOINT lpPoint = NULL);
    BOOL GetViewportExt(LPSIZE lpSize) const;
    BOOL SetViewportExt(INT cx, INT cy, LPSIZE lpSize = NULL);
    BOOL SetViewportExt(SIZE size, LPSIZE lpSizeRet = NULL);
    BOOL ScaleViewportExt(INT xNum, INT xDenom, INT yNum, INT yDenom,
        LPSIZE lpSize = NULL);

    BOOL GetWindowOrg(LPPOINT lpPoint) const;
    BOOL SetWindowOrg(INT x, INT y, LPPOINT lpPoint = NULL);
    BOOL SetWindowOrg(POINT pt, LPPOINT lpPointRet = NULL);
    BOOL OffsetWindowOrg(INT nWidth, INT nHeight, LPPOINT lpPoint = NULL);
    BOOL GetWindowExt(LPSIZE lpSize) const;
    BOOL SetWindowExt(INT x, INT y, LPSIZE lpSize = NULL);
    BOOL SetWindowExt(SIZE size, LPSIZE lpSizeRet = NULL);
    BOOL ScaleWindowExt(INT xNum, INT xDenom, INT yNum, INT yDenom,
        LPSIZE lpSize = NULL);

    BOOL DPtoLP(LPPOINT lpPoints, INT nCount = 1) const;
    BOOL DPtoLP(LPRECT prc) const;
    BOOL DPtoLP(LPSIZE lpSize) const;
    BOOL LPtoDP(LPPOINT lpPoints, INT nCount = 1) const;
    BOOL LPtoDP(LPRECT prc) const;
    BOOL LPtoDP(LPSIZE lpSize) const;
    VOID DPtoHIMETRIC(LPSIZE lpSize) const;
    VOID HIMETRICtoDP(LPSIZE lpSize) const;
    VOID LPtoHIMETRIC(LPSIZE lpSize) const;
    VOID HIMETRICtoLP(LPSIZE lpSize) const;

    BOOL FillRgn(HRGN hRgn, HBRUSH hBrush);
    BOOL FrameRgn(HRGN hRgn, HBRUSH hBrush, INT nWidth, INT nHeight);
    BOOL InvertRgn(HRGN hRgn);
    BOOL PaintRgn(HRGN hRgn);

    INT GetClipBox(LPRECT prc) const;
    INT GetClipRgn(HRGN hRgn) const;
    BOOL PtVisible(INT x, INT y) const;
    BOOL PtVisible(POINT pt) const;
    BOOL RectVisible(LPCRECT prc) const;
    INT SelectClipRgn(HRGN hRgn);
    INT ExcludeClipRect(INT x1, INT y1, INT x2, INT y2);
    INT ExcludeClipRect(LPCRECT prc);
    INT ExcludeUpdateRgn(HWND hWnd);
    INT IntersectClipRect(INT x1, INT y1, INT x2, INT y2);
    INT IntersectClipRect(LPCRECT prc);
    INT OffsetClipRgn(INT x, INT y);
    INT OffsetClipRgn(SIZE size);
    INT SelectClipRgn(HRGN hRgn, INT nMode);

    BOOL GetCurrentPosition(LPPOINT lpPoint) const;
    BOOL MoveTo(INT x, INT y, LPPOINT lpPoint = NULL);
    BOOL MoveTo(POINT pt, LPPOINT lpPointRet = NULL);
    BOOL LineTo(INT x, INT y);
    BOOL LineTo(POINT pt);
    BOOL Line(INT x1, INT y1, INT x2, INT y2);
    BOOL Line(POINT pt1, POINT pt2);
    BOOL Arc(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4);
    BOOL Arc(LPCRECT prc, POINT ptStart, POINT ptEnd);
    BOOL Polyline(LPPOINT lpPoints, INT nCount);
    BOOL AngleArc(INT x, INT y, INT nRadius, FLOAT fStartAngle,
        FLOAT fSweepAngle);
    BOOL ArcTo(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4);
    BOOL ArcTo(LPCRECT prc, POINT ptStart, POINT ptEnd);
    INT GetArcDirection() const;
    INT SetArcDirection(INT nAD_);
    BOOL PolyDraw(CONST POINT* lpPoints, CONST BYTE* lpTypes, INT nCount);
    BOOL PolylineTo(CONST POINT* lpPoints, INT nCount);
    BOOL PolyPolyline(CONST POINT* lpPoints, CONST DWORD* lpPolyPoints,
        INT nCount);
    BOOL PolyBezier(CONST POINT* lpPoints, INT nCount);
    BOOL PolyBezierTo(CONST POINT* lpPoints, INT nCount);
    BOOL FillRect(LPCRECT prc, HBRUSH hBrush);
    BOOL FillRect(LPCRECT prc, INT nCOLOR_);
    VOID FillSolidRect(LPCRECT prc, COLORREF crColor);
    VOID FillSolidRect(INT x, INT y, INT cx, INT cy, COLORREF crColor);
    VOID Draw3dRect(LPCRECT prc, COLORREF clrTopLeft,
        COLORREF clrBottomRight);
    VOID Draw3dRect(INT x, INT y, INT cx, INT cy, COLORREF clrTopLeft,
        COLORREF clrBottomRight);
    BOOL FrameRect(LPCRECT prc, HBRUSH hBrush);
    BOOL InvertRect(LPCRECT prc);
    BOOL DrawIcon(INT x, INT y, HICON hIcon);
    BOOL DrawIcon(POINT pt, HICON hIcon);
    BOOL DrawIconEx(INT x, INT y, HICON hIcon, INT cx, INT cy,
        UINT uStepIfAniCur = 0, HBRUSH hbrFlickerFreeDraw = NULL,
        UINT uDI_flags = DI_NORMAL);
    BOOL DrawIconEx(POINT pt, HICON hIcon, SIZE size,
        UINT uStepIfAniCur = 0, HBRUSH hbrFlickerFreeDraw = NULL,
        UINT uDI_flags = DI_NORMAL);
    BOOL DrawState(POINT pt, SIZE size, HBITMAP hBitmap, UINT nDST_flags,
        HBRUSH hBrush = NULL);
    BOOL DrawState(POINT pt, SIZE size, HICON hIcon, UINT nDST_flags,
        HBRUSH hBrush = NULL);
    BOOL DrawState(POINT pt, SIZE size, LPCTSTR lpszText, UINT nDST_flags,
        BOOL bPrefixText = TRUE, INT nTextLen = 0, HBRUSH hBrush = NULL);
    BOOL DrawState(POINT pt, SIZE size, DRAWSTATEPROC lpDrawProc,
        LPARAM lData, UINT nDST_flags, HBRUSH hBrush = NULL);
    BOOL Chord(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4);
    BOOL Chord(LPCRECT prc, POINT ptStart, POINT ptEnd);
    VOID DrawFocusRect(LPCRECT prc);
    BOOL Ellipse(INT x1, INT y1, INT x2, INT y2);
    BOOL Ellipse(POINT pt1, POINT pt2);
    BOOL Ellipse(LPCRECT prc);
    BOOL Circle(INT x, INT y, INT nRadius);
    BOOL Circle(POINT pt, INT nRadius);
    BOOL Pie(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4);
    BOOL Pie(LPCRECT prc, POINT ptStart, POINT ptEnd);
    BOOL Polygon(LPPOINT lpPoints, INT nCount);
    BOOL PolyPolygon(LPPOINT lpPoints, LPINT lpPolyCounts, INT nCount);
    BOOL Rectangle(INT x1, INT y1, INT x2, INT y2);
    BOOL Rectangle(LPCRECT prc);
    BOOL RoundRect(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3);
    BOOL RoundRect(LPCRECT prc, POINT pt);
    BOOL PatBlt(INT x, INT y, INT cx, INT cy, DWORD dwRop = PATCOPY);
    BOOL PatBlt(LPCRECT prc, DWORD dwRop = PATCOPY);
    BOOL BitBlt(INT x, INT y, INT cx, INT cy, HDC hSrcDC,
        INT xSrc = 0, INT ySrc = 0, DWORD dwRop = SRCCOPY);
    BOOL BitBlt(LPCRECT prc, HDC hSrcDC, POINT ptSrc, DWORD dwRop = SRCCOPY);
    BOOL StretchBlt(INT x, INT y, INT cx, INT cy,
        HDC hSrcDC, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, DWORD dwRop);
    BOOL StretchBlt(LPCRECT prc, HDC hSrcDC, LPCRECT prcSrc, DWORD dwRop);

    COLORREF GetPixel(INT x, INT y) const;
    COLORREF GetPixel(POINT pt) const;
    COLORREF SetPixel(INT x, INT y, COLORREF crColor);
    COLORREF SetPixel(POINT pt, COLORREF crColor);
    BOOL SetPixelV(INT x, INT y, COLORREF crColor);
    BOOL SetPixelV(POINT pt, COLORREF crColor);

    BOOL FloodFill(INT x, INT y, COLORREF crColor);
    BOOL ExtFloodFill(INT x, INT y, COLORREF crColor, UINT nFillType);
    BOOL MaskBlt(INT x, INT y, INT cx, INT cy, HDC hSrcDC, INT xSrc, INT ySrc,
        HBITMAP hMaskBitmap, INT xMask, INT yMask, DWORD dwRop);
    BOOL PlgBlt(LPPOINT lpPoint, HDC hSrcDC, INT xSrc, INT ySrc,
        INT cxSrc, INT cySrc, HBITMAP hMaskBitmap, INT xMask, INT yMask);
    BOOL DitherBlt(INT x, INT y, INT nWidth, INT nHeight, HDC hSrcDC,
        HBITMAP hBitmap, INT xSrc, INT ySrc,
        HBRUSH hBrushBackground = ::GetSysColorBrush(COLOR_3DFACE),
        HBRUSH hBrush3DEffect = ::GetSysColorBrush(COLOR_3DHILIGHT),
        HBRUSH hBrushDisabledImage = ::GetSysColorBrush(COLOR_3DSHADOW));
    VOID GradientFill(COLORREF Color1, COLORREF Color2, LPRECT pRc,
        BOOL bVertical);

    BOOL TextOut(INT x, INT y, LPCTSTR lpsz, INT cch = -1);
    BOOL ExtTextOut(INT x, INT y, UINT nOptions, LPCRECT prc,
        LPCTSTR lpsz, UINT cch = (UINT)-1, LPINT lpDxWidths = NULL);
    SIZE TabbedTextOut(INT x, INT y, LPCTSTR lpsz, INT cch = -1,
        INT nTabPositions = 0, LPINT lpnTabStopPositions = NULL,
        INT nTabOrigin = 0);
    INT DrawText(LPCTSTR lpstrText, INT cchText, LPRECT prc, UINT uFormat);
    INT DrawText(LPTSTR lpstrText, INT cchText, LPRECT prc, UINT uFormat);
    INT DrawTextEx(LPTSTR lpstrText, INT cchText, LPRECT prc,
        UINT uFormat, LPDRAWTEXTPARAMS lpDTParams = NULL);
    MSize GetTextExtent(LPCTSTR lpszString) const;
    MSize GetTextExtent(LPCTSTR lpszString, INT nCount) const;
    BOOL GetTextExtent(LPCTSTR lpszString, INT nCount, LPSIZE lpSize) const;
    BOOL GetTextExtentExPoint(LPCTSTR lpszString, INT cchString,
        LPSIZE lpSize, INT nMaxExtent, LPINT lpnFit = NULL,
        LPINT alpDx = NULL);
    DWORD GetTabbedTextExtent(LPCTSTR lpszString, INT nCount = -1,
        INT nTabPositions = 0, LPINT lpnTabStopPositions = NULL) const;
    BOOL GrayString(HBRUSH hBrush,
        BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, INT),
        LPARAM lpData, INT nCount, INT x, INT y, INT nWidth, INT nHeight);
    UINT GetTextAlign(VOID) const;
    UINT SetTextAlign(UINT uTA_flags);
    INT GetTextFace(LPTSTR lpszFacename, INT nCount) const;
    INT GetTextFaceLen() const;
    BOOL GetTextMetrics(LPTEXTMETRIC lpMetrics) const;
    INT SetTextJustification(INT nBreakExtra, INT nBreakCount);
    INT GetTextCharacterExtra() const;
    INT SetTextCharacterExtra(INT nCharExtra);

    BOOL DrawEdge(LPRECT prc, UINT nEdge, UINT nFlags);
    BOOL DrawFrameControl(LPRECT prc, UINT nType, UINT nState);

    BOOL ScrollDC(INT dx, INT dy, LPCRECT lpRectScroll, LPCRECT lpRectClip,
        HRGN hRgnUpdate, LPRECT lpRectUpdate);

    BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
    BOOL GetCharWidth32(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
    DWORD SetMapperFlags(DWORD dwFlag);
    BOOL GetAspectRatioFilter(LPSIZE lpSize) const;
    BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;
    DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData,
        DWORD cbData) const;
    INT GetKerningPairs(INT nPairs, LPKERNINGPAIR lpkrnpair) const;
    UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const;
    DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
        DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;
    BOOL GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const;
    BOOL GetCharWidth(UINT nFirstChar, UINT nLastChar, PFLOAT lpFloatBuffer) const;
#if (_WIN32_WINNT >= 0x0500)
    DWORD GetFontUnicodeRanges(LPGLYPHSET lpgs) const;
    DWORD GetGlyphIndices(LPCTSTR lpstr, INT cch, LPWORD pgi, DWORD dwFlags) const;
    BOOL GetTextExtentPointI(LPWORD pgiIn, INT cgi, LPSIZE lpSize) const;
    BOOL GetTextExtentExPointI(LPWORD pgiIn, INT cgi, INT nMaxExtent,
        LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const;
    BOOL GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;
    BOOL GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;
#endif  // (_WIN32_WINNT >= 0x0500)

    INT Escape(INT nEscape, INT nCount, LPCSTR lpszInData, LPVOID lpOutData);
    INT Escape(INT nEscape, INT nInputSize, LPCSTR lpszInputData,
        INT nOutputSize, LPSTR lpszOutputData);
    INT DrawEscape(INT nEscape, INT nInputSize, LPCSTR lpszInputData);
    INT StartDoc(LPCTSTR lpszDocName);
    INT StartDoc(LPDOCINFO lpDocInfo);
    INT StartPage(VOID);
    INT EndPage(VOID);
    INT SetAbortProc(BOOL (CALLBACK* lpfn)(HDC, INT));
    INT AbortDoc(VOID);
    INT EndDoc(VOID);

    BOOL PlayMetaFile(HMETAFILE hMF);
    BOOL PlayEnhMetaFile(HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds);
    BOOL GdiComment(UINT nDataSize, CONST BYTE* pCommentData);

    BOOL BeginPath();
    BOOL EndPath();
    BOOL CloseFigure();
    BOOL AbortPath();
    BOOL FillPath();
    BOOL FlattenPath();
    BOOL StrokeAndFillPath();
    BOOL StrokePath();
    BOOL WidenPath();

    BOOL GetMiterLimit(PFLOAT pfMiterLimit) const;
    BOOL SetMiterLimit(FLOAT fMiterLimit, PFLOAT peOldLimit = NULL);
    INT GetPath(LPPOINT lpPoints, LPBYTE lpTypes, INT nCount) const;
    BOOL SelectClipPath(INT nRGN_);

    INT SetDIBitsToDevice(INT x, INT y, DWORD dwWidth, DWORD dwHeight,
        INT xSrc, INT ySrc, UINT uStartScan, UINT cScanLines, LPCVOID lpvBits,
        CONST BITMAPINFO* lpbmi, UINT uColorUse);
    INT StretchDIBits(INT x, INT y, INT nWidth, INT nHeight,
        INT xSrc, INT ySrc, INT nSrcWidth, INT nSrcHeight, LPCVOID lpvBits,
        CONST BITMAPINFO* lpbmi, UINT uColorUse, DWORD dwRop);
    UINT GetDIBColorTable(UINT uStartIndex, UINT cEntries,
        RGBQUAD* pColors) const;
    UINT SetDIBColorTable(UINT uStartIndex, UINT cEntries,
        CONST RGBQUAD* pColors);

private:
    // NOTE: MDC is not copyable.
    MDC(const MDC& dc);
    MDC& operator=(const MDC& dc);
};

INT CALLBACK EnumMetaFileProcDx(HDC hDC, HANDLETABLE* pHandleTable,
    METARECORD* pMetaRec, INT nHandles, LPARAM lParam);

////////////////////////////////////////////////////////////////////////////

class MMemoryDC : public MDC
{
public:
    MMemoryDC();
    MMemoryDC(HDC hBaseDC);
    BOOL CreateCompatibleDC(HDC hBaseDC = NULL);

private:
    // NOTE: MMemoryDC is not copyable.
    MMemoryDC(const MMemoryDC& mdc);
    MMemoryDC& operator=(const MMemoryDC& mdc);
};

////////////////////////////////////////////////////////////////////////////

class MClientDC : public MDC
{
public:
    MClientDC();
    MClientDC(HWND hWnd);
    virtual ~MClientDC();

    BOOL GetDC(HWND hWnd);
    INT ReleaseDC();

public:
    HWND m_hWnd;

private:
    // NOTE: MClientDC is not copyable.
    MClientDC(const MClientDC& cdc);
    MClientDC& operator=(const MClientDC& cdc);
};

////////////////////////////////////////////////////////////////////////////

class MPaintDC : public MDC
{
public:
    MPaintDC();
    MPaintDC(HWND hwnd);
    virtual ~MPaintDC();

    BOOL BeginPaint(HWND hWnd);
    BOOL EndPaint();

public:
    HWND m_hWnd;
    PAINTSTRUCT m_ps;

private:
    // NOTE: MPaintDC is not copyable.
    MPaintDC(const MPaintDC& pdc);
    MPaintDC& operator=(const MPaintDC& pdc);
};

////////////////////////////////////////////////////////////////////////////

class MWindowDC : public MDC
{
public:
    MWindowDC();
    MWindowDC(HWND hWnd);
    virtual ~MWindowDC();

    BOOL GetWindowDC(HWND hWnd);
    INT ReleaseDC();

public:
    HWND m_hWnd;

private:
    // NOTE: MWindowDC is not copyable.
    MWindowDC(const MWindowDC& wdc);
    MWindowDC& operator=(const MWindowDC& wdc);
};

////////////////////////////////////////////////////////////////////////////

class MMetaDC : public MDC
{
public:
    MMetaDC();
    MMetaDC(HDC hDC);
    MMetaDC(LPCTSTR pszFile);
    virtual ~MMetaDC();

    MMetaDC& operator=(HDC hDC);

    BOOL CreateMetaFile(LPCTSTR pszFile = NULL);
    HMETAFILE CloseMetaFile();
    BOOL DeleteMetaFile();

private:
    // NOTE: MMetaDC is not copyable.
    MMetaDC(const MMetaDC& mdc);
    MMetaDC& operator=(const MMetaDC& mdc);
};

////////////////////////////////////////////////////////////////////////////

class MEnhMetaDC : public MDC
{
public:
    MEnhMetaDC();
    MEnhMetaDC(HDC hDC);
    MEnhMetaDC(HDC hdcRef, LPCRECT prc, LPCTSTR pszFileName = NULL,
        LPCTSTR pszDescription = NULL);
    virtual ~MEnhMetaDC();

    MEnhMetaDC& operator=(HDC hDC);

    BOOL CreateEnhMetaFile(HDC hdcRef, LPCRECT prc, LPCTSTR pszFileName = NULL,
        LPCTSTR pszDescription = NULL);
    HENHMETAFILE CloseEnhMetaFile();
    BOOL DeleteEnhMetaFile();
};

////////////////////////////////////////////////////////////////////////////

inline FLOAT GetXDpiDx(VOID)
{
    FLOAT xdpi;
    GetDpiDx(&xdpi, NULL);
    return xdpi;
}

inline FLOAT GetYDpiDx(VOID)
{
    FLOAT ydpi;
    GetDpiDx(NULL, &ydpi);
    return ydpi;
}

inline FLOAT XDpiScaleDx(FLOAT xPixels, FLOAT base_xdpi/* = 96.0f*/)
{
    return xPixels * GetXDpiDx() / base_xdpi;
}

inline FLOAT YDpiScaleDx(FLOAT yPixels, FLOAT base_ydpi/* = 96.0f*/)
{
    return yPixels * GetYDpiDx() / base_ydpi;
}

////////////////////////////////////////////////////////////////////////////

inline MDC::MDC() : m_hDC(NULL)
{
}

inline MDC::MDC(HDC hDC) : m_hDC(hDC)
{
}

inline /*virtual*/ MDC::~MDC()
{
    DeleteDC();
}

inline MDC& MDC::operator=(HDC hDC)
{
    assert(hDC == NULL ||
           ::GetObjectType(hDC) == OBJ_DC ||
           ::GetObjectType(hDC) == OBJ_METADC ||
           ::GetObjectType(hDC) == OBJ_ENHMETADC);
    if (Handle() != hDC)
    {
        Attach(hDC);
    }
    return *this;
}

inline BOOL MDC::Attach(HDC hDC)
{
    DeleteDC();
    assert(::GetObjectType(hDC) == OBJ_DC ||
           ::GetObjectType(hDC) == OBJ_METADC ||
           ::GetObjectType(hDC) == OBJ_ENHMETADC);
    m_hDC = hDC;
    return m_hDC != NULL;
}

inline HDC MDC::Detach()
{
    HDC hDC = m_hDC;
    m_hDC = NULL;
    return hDC;
}

inline HDC MDC::Handle() const
{
    return (this ? m_hDC : NULL);
}

inline BOOL MDC::CreateDC(LPCTSTR pszDriver/* = NULL*/,
    LPCTSTR pszDevice/* = NULL*/, LPCTSTR pszOutput/* = NULL*/,
    CONST DEVMODE *lpInitData/* = NULL*/)
{
    return Attach(::CreateDC(pszDriver, pszDevice, pszOutput, lpInitData));
}

inline BOOL MDC::CreateCompatibleDC(HDC hBaseDC/* = NULL*/)
{
    return Attach(::CreateCompatibleDC(hBaseDC));
}

inline MDC::operator HDC() const
{
    return Handle();
}

inline bool MDC::operator!() const
{
    return (Handle() == NULL);
}

inline HWND MDC::WindowFromDC() const
{
    assert(Handle());
    return ::WindowFromDC(Handle());
}

inline BOOL MDC::DeleteDC()
{
    if (Handle())
    {
        assert(Handle());
        return ::DeleteDC(Detach());
    }
    return FALSE;
}

inline HPEN MDC::GetCurrentPen() const
{
    assert(Handle());
    return reinterpret_cast<HPEN>(::GetCurrentObject(Handle(), OBJ_PEN));
}

inline HBRUSH MDC::GetCurrentBrush() const
{
    assert(Handle());
    return reinterpret_cast<HBRUSH>(::GetCurrentObject(Handle(), OBJ_BRUSH));
}

inline HPALETTE MDC::GetCurrentPalette() const
{
    assert(Handle());
    return reinterpret_cast<HPALETTE>(::GetCurrentObject(Handle(), OBJ_PAL));
}

inline HFONT MDC::GetCurrentFont() const
{
    assert(Handle());
    return reinterpret_cast<HFONT>(::GetCurrentObject(Handle(), OBJ_FONT));
}

inline HBITMAP MDC::GetCurrentBitmap() const
{
    assert(Handle());
    return reinterpret_cast<HBITMAP>(::GetCurrentObject(Handle(), OBJ_BITMAP));
}

inline INT MDC::SaveDC(VOID)
{
    assert(Handle());
    return ::SaveDC(Handle());
}

inline BOOL MDC::RestoreDC(INT nSavedDC)
{
    assert(Handle());
    return ::RestoreDC(Handle(), nSavedDC);
}

inline INT MDC::GetDeviceCaps(INT nIndex) const
{
    assert(Handle());
    return ::GetDeviceCaps(Handle(), nIndex);
}

inline UINT MDC::GetBoundsRect(LPRECT lpRectBounds, UINT uDCB_flags) const
{
    assert(Handle());
    return ::GetBoundsRect(Handle(), lpRectBounds, uDCB_flags);
}

inline UINT MDC::SetBoundsRect(LPCRECT lpRectBounds, UINT uDCB_flags)
{
    assert(Handle());
    return ::SetBoundsRect(Handle(), lpRectBounds, uDCB_flags);
}

inline BOOL MDC::ResetDC(CONST DEVMODE *lpDevMode)
{
    assert(Handle());
    return ::ResetDC(Handle(), lpDevMode) != NULL;
}

inline BOOL MDC::GetBrushOrg(LPPOINT ppt) const
{
    assert(Handle());
    return ::GetBrushOrgEx(Handle(), ppt);
}

inline BOOL MDC::SetBrushOrg(INT x, INT y, LPPOINT ppt/* = NULL*/)
{
    assert(Handle());
    return ::SetBrushOrgEx(Handle(), x, y, ppt);
}

inline BOOL MDC::SetBrushOrg(POINT pt, LPPOINT lpPointRet/* = NULL*/)
{
    assert(Handle());
    return ::SetBrushOrgEx(Handle(), pt.x, pt.y, lpPointRet);
}

inline INT MDC::EnumObjects(
    INT nObjectType, INT (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
{
    assert(Handle());
    return ::EnumObjects(Handle(), nObjectType, (GOBJENUMPROC) lpfn, lpData);
}

inline HGDIOBJ MDC::SelectStockObject(INT nIndex)
{
    assert(Handle());
    return ::SelectObject(Handle(), ::GetStockObject(nIndex));
}

inline HPEN MDC::SelectObject(HPEN hPen)
{
    assert(Handle());
    return reinterpret_cast<HPEN>(::SelectObject(Handle(), hPen));
}

inline HBRUSH MDC::SelectObject(HBRUSH hBrush)
{
    assert(Handle());
    return reinterpret_cast<HBRUSH>(::SelectObject(Handle(), hBrush));
}

inline HFONT MDC::SelectObject(HFONT hFont) 
{
    assert(Handle());
    return reinterpret_cast<HFONT>(::SelectObject(Handle(), hFont));
}

inline HBITMAP MDC::SelectObject(HBITMAP hBitmap)
{
    assert(Handle());
    return reinterpret_cast<HBITMAP>(::SelectObject(Handle(), hBitmap));
}

inline INT MDC::SelectObject(HRGN hRgn)
{
    assert(Handle());
    return static_cast<INT>(reinterpret_cast<INT_PTR>(::SelectObject(Handle(), hRgn)));
}

inline HGDIOBJ MDC::SelectObject(HGDIOBJ hGdiObj)
{
    assert(Handle());
    return ::SelectObject(Handle(), hGdiObj);
}

inline HPALETTE MDC::SelectPalette(
    HPALETTE hPal, BOOL bForceBackground/* = FALSE*/)
{
    assert(Handle());
    return ::SelectPalette(Handle(), hPal, bForceBackground);
}

inline COLORREF MDC::GetNearestColor(COLORREF crColor) const
{
    assert(Handle());
    return ::GetNearestColor(Handle(), crColor);
}

inline UINT MDC::RealizePalette(VOID)
{
    assert(Handle());
    return ::RealizePalette(Handle());
}

inline VOID MDC::UpdateColors(VOID)
{
    assert(Handle());
    ::UpdateColors(Handle());
}

inline COLORREF MDC::GetBkColor() const
{
    assert(Handle());
    return ::GetBkColor(Handle());
}

inline INT MDC::GetBkMode() const
{
    assert(Handle());
    return ::GetBkMode(Handle());
}

inline INT MDC::GetPolyFillMode() const
{
    assert(Handle());
    return ::GetPolyFillMode(Handle());
}

inline INT MDC::GetROP2() const
{
    assert(Handle());
    return ::GetROP2(Handle());
}

inline INT MDC::GetStretchBltMode() const
{
    assert(Handle());
    return ::GetStretchBltMode(Handle());
}

inline COLORREF MDC::GetTextColor() const
{
    assert(Handle());
    return ::GetTextColor(Handle());
}

inline COLORREF MDC::SetBkColor(COLORREF crColor)
{
    assert(Handle());
    return ::SetBkColor(Handle(), crColor);
}

inline INT MDC::SetBkMode(INT nBkMode)
{
    assert(Handle());
    return ::SetBkMode(Handle(), nBkMode);
}

inline INT MDC::SetPolyFillMode(INT nPolyFillMode)
{
    assert(Handle());
    return ::SetPolyFillMode(Handle(), nPolyFillMode);
}

inline INT MDC::SetROP2(INT nR2_)
{
    assert(Handle());
    return ::SetROP2(Handle(), nR2_);
}

inline INT MDC::SetStretchBltMode(INT nSTRETCH_)
{
    assert(Handle());
    return ::SetStretchBltMode(Handle(), nSTRETCH_);
}

inline COLORREF MDC::SetTextColor(COLORREF crColor)
{
    assert(Handle());
    return ::SetTextColor(Handle(), crColor);
}

#if (_WIN32_WINNT >= 0x0500)
    inline COLORREF MDC::GetDCBrushColor()
    {
        assert(Handle());
        return ::GetDCBrushColor(Handle());
    }

    inline COLORREF MDC::GetDCPenColor()
    {
        assert(Handle());
        return ::GetDCPenColor(Handle());
    }
#endif  //  (_WIN32_WINNT >= 0x0500)

inline BOOL MDC::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
{
    assert(Handle());
    return ::GetColorAdjustment(Handle(), lpColorAdjust);
}

inline BOOL MDC::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
{
    assert(Handle());
    return ::SetColorAdjustment(Handle(), lpColorAdjust);
}

inline INT MDC::GetMapMode() const
{
    assert(Handle());
    return ::GetMapMode(Handle());
}

inline BOOL MDC::GetViewportOrg(LPPOINT lpPoint) const
{
    assert(Handle());
    return ::GetViewportOrgEx(Handle(), lpPoint);
}

inline INT MDC::SetMapMode(INT nMapMode)
{
    assert(Handle());
    return ::SetMapMode(Handle(), nMapMode);
}

inline BOOL MDC::SetViewportOrg(POINT pt, LPPOINT lpPointRet/* = NULL*/)
{
    return SetViewportOrg(pt.x, pt.y, lpPointRet);
}

inline BOOL MDC::GetViewportExt(LPSIZE lpSize) const
{
    assert(Handle());
    return ::GetViewportExtEx(Handle(), lpSize);
}

inline BOOL MDC::SetViewportExt(SIZE size, LPSIZE lpSizeRet/* = NULL*/)
{
    assert(Handle());
    return SetViewportExt(size.cx, size.cy, lpSizeRet);
}

inline BOOL MDC::ScaleViewportExt(
    INT xNum, INT xDenom, INT yNum, INT yDenom, LPSIZE lpSize/* = NULL*/)
{
    assert(Handle());
    return ::ScaleViewportExtEx(Handle(), xNum, xDenom, yNum, yDenom, lpSize);
}

inline BOOL MDC::GetWindowOrg(LPPOINT lpPoint) const
{
    assert(Handle());
    return ::GetWindowOrgEx(Handle(), lpPoint);
}

inline BOOL MDC::SetWindowOrg(POINT pt, LPPOINT lpPointRet/* = NULL*/)
{
    return SetWindowOrg(pt.x, pt.y, lpPointRet);
}

inline BOOL MDC::OffsetWindowOrg(
    INT nWidth, INT nHeight, LPPOINT lpPoint/* = NULL*/)
{
    assert(Handle());
    return ::OffsetWindowOrgEx(Handle(), nWidth, nHeight, lpPoint);
}

inline BOOL MDC::GetWindowExt(LPSIZE lpSize) const
{
    assert(Handle());
    return ::GetWindowExtEx(Handle(), lpSize);
}

inline BOOL MDC::SetWindowExt(SIZE size, LPSIZE lpSizeRet/* = NULL*/)
{
    return SetWindowExt(size.cx, size.cy, lpSizeRet);
}

inline BOOL MDC::ScaleWindowExt(INT xNum, INT xDenom,
    INT yNum, INT yDenom, LPSIZE lpSize/* = NULL*/)
{
    assert(Handle());
    return ::ScaleWindowExtEx(Handle(), xNum, xDenom, yNum, yDenom, lpSize);
}

inline BOOL MDC::DPtoLP(LPPOINT lpPoints, INT nCount/* = 1*/) const
{
    assert(Handle());
    return ::DPtoLP(Handle(), lpPoints, nCount);
}

inline BOOL MDC::DPtoLP(LPRECT prc) const
{
    assert(Handle());
    return ::DPtoLP(Handle(), (LPPOINT) prc, 2);
}

inline BOOL MDC::DPtoLP(LPSIZE lpSize) const
{
    SIZE sizeWinExt;
    sizeWinExt.cx = sizeWinExt.cy = 0;
    if (!GetWindowExt(&sizeWinExt))
        return FALSE;
    SIZE sizeVpExt;
    sizeVpExt.cx = sizeVpExt.cy = 0;
    if (!GetViewportExt(&sizeVpExt))
        return FALSE;
    lpSize->cx = ::MulDiv(lpSize->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
    lpSize->cy = ::MulDiv(lpSize->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));
    return TRUE;
}

inline BOOL MDC::LPtoDP(LPPOINT lpPoints, INT nCount/* = 1*/) const
{
    assert(Handle());
    return ::LPtoDP(Handle(), lpPoints, nCount);
}

inline BOOL MDC::LPtoDP(LPRECT prc) const
{
    assert(Handle());
    return ::LPtoDP(Handle(), (LPPOINT) prc, 2);
}

inline BOOL MDC::LPtoDP(LPSIZE lpSize) const
{
    SIZE sizeWinExt;
    sizeWinExt.cx = sizeWinExt.cy = 0;
    if (!GetWindowExt(&sizeWinExt))
        return FALSE;
    SIZE sizeVpExt;
    sizeVpExt.cx = sizeVpExt.cy = 0;
    if (!GetViewportExt(&sizeVpExt))
        return FALSE;
    lpSize->cx = ::MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
    lpSize->cy = ::MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
    return TRUE;
}

inline VOID MDC::DPtoHIMETRIC(LPSIZE lpSize) const
{
    assert(Handle());
    INT nMapMode;
    if ((nMapMode = GetMapMode()) < MM_ISOTROPIC && nMapMode != MM_TEXT)
    {
        // when using a constrained map mode, map against physical inch
        ::SetMapMode(Handle(), MM_HIMETRIC);
        DPtoLP(lpSize);
        ::SetMapMode(Handle(), nMapMode);
    }
    else
    {
        // map against logical inch for non-constrained mapping modes
        INT cxPerInch = GetDeviceCaps(LOGPIXELSX);
        INT cyPerInch = GetDeviceCaps(LOGPIXELSY);
        assert(cxPerInch != 0 && cyPerInch != 0);
        lpSize->cx = ::MulDiv(lpSize->cx, HIMETRIC_INCH, cxPerInch);
        lpSize->cy = ::MulDiv(lpSize->cy, HIMETRIC_INCH, cyPerInch);
    }
}

inline VOID MDC::HIMETRICtoDP(LPSIZE lpSize) const
{
    assert(Handle());
    INT nMapMode;
    if ((nMapMode = GetMapMode()) < MM_ISOTROPIC && nMapMode != MM_TEXT)
    {
        // when using a constrained map mode, map against physical inch
        ::SetMapMode(Handle(), MM_HIMETRIC);
        LPtoDP(lpSize);
        ::SetMapMode(Handle(), nMapMode);
    }
    else
    {
        // map against logical inch for non-constrained mapping modes
        INT cxPerInch = GetDeviceCaps(LOGPIXELSX);
        INT cyPerInch = GetDeviceCaps(LOGPIXELSY);
        assert(cxPerInch != 0 && cyPerInch != 0);
        lpSize->cx = ::MulDiv(lpSize->cx, cxPerInch, HIMETRIC_INCH);
        lpSize->cy = ::MulDiv(lpSize->cy, cyPerInch, HIMETRIC_INCH);
    }
}

inline VOID MDC::LPtoHIMETRIC(LPSIZE lpSize) const
{
    LPtoDP(lpSize);
    DPtoHIMETRIC(lpSize);
}

inline VOID MDC::HIMETRICtoLP(LPSIZE lpSize) const
{
    HIMETRICtoDP(lpSize);
    DPtoLP(lpSize);
}

inline BOOL MDC::FillRgn(HRGN hRgn, HBRUSH hBrush)
{
    assert(Handle());
    return ::FillRgn(Handle(), hRgn, hBrush);
}

inline BOOL MDC::FrameRgn(
    HRGN hRgn, HBRUSH hBrush, INT nWidth, INT nHeight)
{
    assert(Handle());
    return ::FrameRgn(Handle(), hRgn, hBrush, nWidth, nHeight);
}

inline BOOL MDC::InvertRgn(HRGN hRgn)
{
    assert(Handle());
    return ::InvertRgn(Handle(), hRgn);
}

inline BOOL MDC::PaintRgn(HRGN hRgn)
{
    assert(Handle());
    return ::PaintRgn(Handle(), hRgn);
}

inline INT MDC::GetClipBox(LPRECT prc) const
{
    assert(Handle());
    return ::GetClipBox(Handle(), prc);
}

inline INT MDC::GetClipRgn(HRGN hRgn) const
{
    assert(Handle());
    INT nRet = ::GetClipRgn(Handle(), hRgn);
    return nRet;
}

inline BOOL MDC::PtVisible(INT x, INT y) const
{
    assert(Handle());
    return ::PtVisible(Handle(), x, y);
}

inline BOOL MDC::PtVisible(POINT pt) const
{
    assert(Handle());
    return ::PtVisible(Handle(), pt.x, pt.y);
}

inline BOOL MDC::RectVisible(LPCRECT prc) const
{
    assert(Handle());
    return ::RectVisible(Handle(), prc);
}

inline INT MDC::SelectClipRgn(HRGN hRgn)
{
    assert(Handle());
    return ::SelectClipRgn(Handle(), (HRGN) hRgn);
}

inline INT MDC::ExcludeClipRect(INT x1, INT y1, INT x2, INT y2)
{
    assert(Handle());
    return ::ExcludeClipRect(Handle(), x1, y1, x2, y2);
}

inline INT MDC::ExcludeClipRect(LPCRECT prc)
{
    assert(Handle());
    return ::ExcludeClipRect(Handle(),
        prc->left, prc->top, prc->right, prc->bottom);
}

inline INT MDC::ExcludeUpdateRgn(HWND hWnd)
{
    assert(Handle());
    return ::ExcludeUpdateRgn(Handle(), hWnd);
}

inline INT MDC::IntersectClipRect(INT x1, INT y1, INT x2, INT y2)
{
    assert(Handle());
    return ::IntersectClipRect(Handle(), x1, y1, x2, y2);
}

inline INT MDC::IntersectClipRect(LPCRECT prc)
{
    assert(Handle());
    return ::IntersectClipRect(Handle(),
        prc->left, prc->top, prc->right, prc->bottom);
}

inline INT MDC::OffsetClipRgn(INT x, INT y)
{
    assert(Handle());
    return ::OffsetClipRgn(Handle(), x, y);
}

inline INT MDC::OffsetClipRgn(SIZE size)
{
    assert(Handle());
    return ::OffsetClipRgn(Handle(), size.cx, size.cy);
}

inline INT MDC::SelectClipRgn(HRGN hRgn, INT nMode)
{
    assert(Handle());
    return ::ExtSelectClipRgn(Handle(), hRgn, nMode);
}

inline BOOL MDC::GetCurrentPosition(LPPOINT lpPoint) const
{
    assert(Handle());
    return ::GetCurrentPositionEx(Handle(), lpPoint);
}

inline BOOL MDC::MoveTo(INT x, INT y, LPPOINT lpPoint/* = NULL*/)
{
    assert(Handle());
    return ::MoveToEx(Handle(), x, y, lpPoint);
}

inline BOOL MDC::MoveTo(POINT pt, LPPOINT lpPointRet/* = NULL*/)
{
    return MoveTo(pt.x, pt.y, lpPointRet);
}

inline BOOL MDC::LineTo(INT x, INT y)
{
    assert(Handle());
    return ::LineTo(Handle(), x, y);
}

inline BOOL MDC::LineTo(POINT pt)
{
    assert(Handle());
    return LineTo(pt.x, pt.y);
}

inline BOOL MDC::Line(INT x1, INT y1, INT x2, INT y2)
{
    return MoveTo(x1, y1) && LineTo(x2, y2);
}

inline BOOL MDC::Line(POINT pt1, POINT pt2)
{
    return MoveTo(pt1) && LineTo(pt2);
}

inline BOOL MDC::Arc(
    INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
{
    assert(Handle());
    return ::Arc(Handle(), x1, y1, x2, y2, x3, y3, x4, y4);
}

inline BOOL MDC::Arc(LPCRECT prc, POINT ptStart, POINT ptEnd)
{
    assert(Handle());
    return ::Arc(Handle(), prc->left, prc->top,
        prc->right, prc->bottom, ptStart.x, ptStart.y,
        ptEnd.x, ptEnd.y);
}

inline BOOL MDC::Polyline(LPPOINT lpPoints, INT nCount)
{
    assert(Handle());
    return ::Polyline(Handle(), lpPoints, nCount);
}

inline BOOL MDC::AngleArc(
    INT x, INT y, INT nRadius, FLOAT fStartAngle, FLOAT fSweepAngle)
{
    assert(Handle());
    return ::AngleArc(Handle(), x, y, (DWORD) nRadius, fStartAngle, fSweepAngle);
}

inline BOOL MDC::ArcTo(
    INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
{
    assert(Handle());
    return ::ArcTo(Handle(), x1, y1, x2, y2, x3, y3, x4, y4);
}

inline BOOL MDC::ArcTo(LPCRECT prc, POINT ptStart, POINT ptEnd)
{
    return ArcTo(prc->left, prc->top, prc->right,
                 prc->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}

inline INT MDC::GetArcDirection() const
{
    assert(Handle());
    return ::GetArcDirection(Handle());
}

inline INT MDC::SetArcDirection(INT nAD_)
{
    assert(Handle());
    return ::SetArcDirection(Handle(), nAD_);
}

inline BOOL MDC::PolyDraw(
    CONST POINT* lpPoints, CONST BYTE* lpTypes, INT nCount)
{
    assert(Handle());
    return ::PolyDraw(Handle(), lpPoints, lpTypes, nCount);
}

inline BOOL MDC::PolylineTo(CONST POINT* lpPoints, INT nCount)
{
    assert(Handle());
    return ::PolylineTo(Handle(), lpPoints, static_cast<DWORD>(nCount));
}

inline BOOL MDC::PolyPolyline(
    CONST POINT* lpPoints, CONST DWORD* lpPolyPoints, INT nCount)
{
    assert(Handle());
    return ::PolyPolyline(Handle(), lpPoints, lpPolyPoints, static_cast<DWORD>(nCount));
}

inline BOOL MDC::PolyBezier(CONST POINT* lpPoints, INT nCount)
{
    assert(Handle());
    return ::PolyBezier(Handle(), lpPoints, static_cast<DWORD>(nCount));
}

inline BOOL MDC::PolyBezierTo(CONST POINT* lpPoints, INT nCount)
{
    assert(Handle());
    return ::PolyBezierTo(Handle(), lpPoints, static_cast<DWORD>(nCount));
}

inline BOOL MDC::FillRect(LPCRECT prc, HBRUSH hBrush)
{
    assert(Handle());
    return ::FillRect(Handle(), prc, hBrush);
}

inline BOOL MDC::FillRect(LPCRECT prc, INT nCOLOR_)
{
    assert(Handle());
    return ::FillRect(Handle(), prc, reinterpret_cast<HBRUSH>(static_cast<INT_PTR>(nCOLOR_ + 1)));
}

inline BOOL MDC::FrameRect(LPCRECT prc, HBRUSH hBrush)
{
    assert(Handle());
    return ::FrameRect(Handle(), prc, hBrush);
}

inline BOOL MDC::InvertRect(LPCRECT prc)
{
    assert(Handle());
    return ::InvertRect(Handle(), prc);
}

inline BOOL MDC::DrawIcon(INT x, INT y, HICON hIcon)
{
    assert(Handle());
    return ::DrawIcon(Handle(), x, y, hIcon);
}

inline BOOL MDC::DrawIcon(POINT pt, HICON hIcon)
{
    assert(Handle());
    return ::DrawIcon(Handle(), pt.x, pt.y, hIcon);
}

inline BOOL MDC::DrawIconEx(INT x, INT y, HICON hIcon, INT cx, INT cy,
    UINT uStepIfAniCur/* = 0*/, HBRUSH hbrFlickerFreeDraw/* = NULL*/,
    UINT uDI_flags/* = DI_NORMAL*/)
{
    assert(Handle());
    return ::DrawIconEx(Handle(), x, y, hIcon, cx, cy,
                        uStepIfAniCur, hbrFlickerFreeDraw, uDI_flags);
}

inline BOOL MDC::DrawIconEx(POINT pt, HICON hIcon, SIZE size,
    UINT uStepIfAniCur/* = 0*/, HBRUSH hbrFlickerFreeDraw/* = NULL*/,
    UINT uDI_flags/* = DI_NORMAL*/)
{
    assert(Handle());
    return ::DrawIconEx(Handle(), pt.x, pt.y, hIcon, size.cx, size.cy,
                        uStepIfAniCur, hbrFlickerFreeDraw, uDI_flags);
}

inline BOOL MDC::DrawState(POINT pt, SIZE size, HBITMAP hBitmap,
    UINT nDST_flags, HBRUSH hBrush/* = NULL*/)
{
    assert(Handle());
    return ::DrawState(Handle(), hBrush, NULL, (LPARAM)hBitmap, 0,
        pt.x, pt.y, size.cx, size.cy, nDST_flags | DST_BITMAP);
}

inline BOOL MDC::DrawState(POINT pt, SIZE size, HICON hIcon,
    UINT nDST_flags, HBRUSH hBrush/* = NULL*/)
{
    assert(Handle());
    return ::DrawState(Handle(), hBrush, NULL, (LPARAM)hIcon, 0,
                       pt.x, pt.y, size.cx, size.cy, nDST_flags | DST_ICON);
}

inline BOOL MDC::DrawState(POINT pt, SIZE size, LPCTSTR lpszText,
    UINT nDST_flags, BOOL bPrefixText/* = TRUE*/, INT nTextLen/* = 0*/,
    HBRUSH hBrush/* = NULL*/)
{
    assert(Handle());
    return ::DrawState(Handle(), hBrush, NULL, (LPARAM)lpszText,
                       (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy,
                       nDST_flags | (bPrefixText ? DST_PREFIXTEXT : DST_TEXT));
}

inline BOOL MDC::DrawState(POINT pt, SIZE size, DRAWSTATEPROC lpDrawProc,
    LPARAM lData, UINT nDST_flags, HBRUSH hBrush/* = NULL*/)
{
    assert(Handle());
    return ::DrawState(Handle(), hBrush, lpDrawProc, lData, 0,
                       pt.x, pt.y, size.cx, size.cy, nDST_flags | DST_COMPLEX);
}

inline BOOL MDC::Chord(
    INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
{
    assert(Handle());
    return ::Chord(Handle(), x1, y1, x2, y2, x3, y3, x4, y4);
}

inline BOOL MDC::Chord(LPCRECT prc, POINT ptStart, POINT ptEnd)
{
    assert(Handle());
    return ::Chord(Handle(), prc->left, prc->top,
        prc->right, prc->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}

inline VOID MDC::DrawFocusRect(LPCRECT prc)
{
    assert(Handle());
    ::DrawFocusRect(Handle(), prc);
}

inline BOOL MDC::Ellipse(INT x1, INT y1, INT x2, INT y2)
{
    assert(Handle());
    return ::Ellipse(Handle(), x1, y1, x2, y2);
}

inline BOOL MDC::Ellipse(POINT pt1, POINT pt2)
{
    return MDC::Ellipse(pt1.x, pt1.y, pt2.x, pt2.y);
}

inline BOOL MDC::Ellipse(LPCRECT prc)
{
    assert(Handle());
    return ::Ellipse(Handle(),
        prc->left, prc->top, prc->right, prc->bottom);
}

inline BOOL MDC::Circle(INT x, INT y, INT nRadius)
{
    return MDC::Ellipse(x - nRadius, y - nRadius, x + nRadius, y + nRadius);
}

inline BOOL MDC::Circle(POINT pt, INT nRadius)
{
    return MDC::Circle(pt.x, pt.y, nRadius);
}

inline BOOL MDC::Pie(
    INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
{
    assert(Handle());
    return ::Pie(Handle(), x1, y1, x2, y2, x3, y3, x4, y4);
}

inline BOOL MDC::Pie(LPCRECT prc, POINT ptStart, POINT ptEnd)
{
    assert(Handle());
    return ::Pie(Handle(), prc->left, prc->top, prc->right,
        prc->bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}

inline BOOL MDC::Polygon(LPPOINT lpPoints, INT nCount)
{
    assert(Handle());
    return ::Polygon(Handle(), lpPoints, nCount);
}

inline BOOL MDC::PolyPolygon(
    LPPOINT lpPoints, LPINT lpPolyCounts, INT nCount)
{
    assert(Handle());
    return ::PolyPolygon(Handle(), lpPoints, lpPolyCounts, nCount);
}

inline BOOL MDC::Rectangle(INT x1, INT y1, INT x2, INT y2)
{
    assert(Handle());
    return ::Rectangle(Handle(), x1, y1, x2, y2);
}

inline BOOL MDC::Rectangle(LPCRECT prc)
{
    assert(Handle());
    return ::Rectangle(Handle(),
        prc->left, prc->top, prc->right, prc->bottom);
}

inline BOOL MDC::RoundRect(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3)
{
    assert(Handle());
    return ::RoundRect(Handle(), x1, y1, x2, y2, x3, y3);
}

inline BOOL MDC::RoundRect(LPCRECT prc, POINT pt)
{
    assert(Handle());
    return ::RoundRect(Handle(), prc->left, prc->top,
        prc->right, prc->bottom, pt.x, pt.y);
}

inline BOOL MDC::PatBlt(INT x, INT y, INT cx, INT cy, DWORD dwRop/* = PATCOPY*/)
{
    assert(Handle());
    return ::PatBlt(Handle(), x, y, cx, cy, dwRop);
}

inline BOOL MDC::BitBlt(INT x, INT y, INT cx, INT cy,
    HDC hSrcDC, INT xSrc/* = 0*/, INT ySrc/* = 0*/, DWORD dwRop/* = SRCCOPY*/)
{
    assert(Handle());
    return ::BitBlt(Handle(), x, y, cx, cy, hSrcDC, xSrc, ySrc, dwRop);
}

inline BOOL MDC::StretchBlt(INT x, INT y, INT cx, INT cy,
    HDC hSrcDC, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, DWORD dwRop)
{
    assert(Handle());
    return ::StretchBlt(Handle(), x, y, cx, cy,
        hSrcDC, xSrc, ySrc, cxSrc, cySrc, dwRop);
}

inline BOOL MDC::StretchBlt(
    LPCRECT prc, HDC hSrcDC, LPCRECT prcSrc, DWORD dwRop)
{
    MRect rc(prc), rcSrc(prcSrc);
    return StretchBlt(rc.left, rc.top, rc.Width(), rc.Height(),
        hSrcDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), dwRop);
}

inline COLORREF MDC::GetPixel(INT x, INT y) const
{
    assert(Handle());
    return ::GetPixel(Handle(), x, y);
}

inline COLORREF MDC::GetPixel(POINT pt) const
{
    assert(Handle());
    return ::GetPixel(Handle(), pt.x, pt.y);
}

inline COLORREF MDC::SetPixel(INT x, INT y, COLORREF crColor)
{
    assert(Handle());
    return ::SetPixel(Handle(), x, y, crColor);
}

inline COLORREF MDC::SetPixel(POINT pt, COLORREF crColor)
{
    assert(Handle());
    return ::SetPixel(Handle(), pt.x, pt.y, crColor);
}

inline BOOL MDC::FloodFill(INT x, INT y, COLORREF crColor)
{
    assert(Handle());
    return ::FloodFill(Handle(), x, y, crColor);
}

inline BOOL MDC::ExtFloodFill(INT x, INT y, COLORREF crColor, UINT nFillType)
{
    assert(Handle());
    return ::ExtFloodFill(Handle(), x, y, crColor, nFillType);
}

inline BOOL MDC::MaskBlt(INT x, INT y, INT cx, INT cy,
    HDC hSrcDC, INT xSrc, INT ySrc, HBITMAP hMaskBitmap,
    INT xMask, INT yMask, DWORD dwRop)
{
    assert(Handle());
    return ::MaskBlt(Handle(), x, y, cx, cy,
                     hSrcDC, xSrc, ySrc, hMaskBitmap, xMask, yMask, dwRop);
}

inline BOOL MDC::PlgBlt(LPPOINT lpPoint, HDC hSrcDC, INT xSrc, INT ySrc,
    INT cxSrc, INT cySrc, HBITMAP hMaskBitmap, INT xMask, INT yMask)
{
    assert(Handle());
    return ::PlgBlt(Handle(), lpPoint, hSrcDC, xSrc, ySrc, cxSrc, cySrc,
                    hMaskBitmap, xMask, yMask);
}

inline BOOL MDC::SetPixelV(INT x, INT y, COLORREF crColor)
{
    assert(Handle());
    return ::SetPixelV(Handle(), x, y, crColor);
}

inline BOOL MDC::SetPixelV(POINT pt, COLORREF crColor)
{
    assert(Handle());
    return ::SetPixelV(Handle(), pt.x, pt.y, crColor);
}

inline BOOL MDC::TextOut(INT x, INT y, LPCTSTR lpsz, INT cch/* = -1*/)
{
    assert(Handle());
    if(cch == -1)
        cch = lstrlen(lpsz);
    return ::TextOut(Handle(), x, y, lpsz, cch);
}

inline SIZE MDC::TabbedTextOut(INT x, INT y, LPCTSTR lpsz,
    INT cch/* = -1*/, INT nTabPositions/* = 0*/,
    LPINT lpnTabStopPositions/* = NULL*/, INT nTabOrigin/* = 0*/)
{
    assert(Handle());
    if (cch == -1) cch = lstrlen(lpsz);
    LONG lRes = ::TabbedTextOut(
        Handle(), x, y, lpsz, cch, nTabPositions, lpnTabStopPositions, nTabOrigin);
    SIZE size;
    size.cx = (SHORT) LOWORD(lRes);
    size.cy = (SHORT) HIWORD(lRes);
    return size;
}

inline INT MDC::DrawText(
    LPCTSTR lpstrText, INT cchText, LPRECT prc, UINT uFormat)
{
    assert(Handle());
    assert((uFormat & DT_MODIFYSTRING) == 0);
    return ::DrawText(Handle(), lpstrText, cchText, prc, uFormat);
}

inline INT MDC::DrawText(
    LPTSTR lpstrText, INT cchText, LPRECT prc, UINT uFormat)
{
    assert(Handle());
    return ::DrawText(Handle(), lpstrText, cchText, prc, uFormat);
}

inline INT MDC::DrawTextEx(LPTSTR lpstrText, INT cchText,
    LPRECT prc, UINT uFormat, LPDRAWTEXTPARAMS lpDTParams/* = NULL*/)
{
    assert(Handle());
    return ::DrawTextEx(Handle(), lpstrText, cchText, prc, uFormat, lpDTParams);
}

inline MSize MDC::GetTextExtent(LPCTSTR lpszString, INT nCount) const
{
    MSize siz;
    MDC::GetTextExtent(lpszString, nCount, &siz);
    return siz;
}

inline BOOL MDC::GetTextExtent(
    LPCTSTR lpszString, INT nCount, LPSIZE lpSize) const
{
    assert(Handle());
    if (nCount == -1) nCount = lstrlen(lpszString);
    return ::GetTextExtentPoint32(Handle(), lpszString, nCount, lpSize);
}

inline BOOL MDC::GetTextExtentExPoint(LPCTSTR lpszString, INT cchString,
    LPSIZE lpSize, INT nMaxExtent, LPINT lpnFit/* = NULL*/,
    LPINT alpDx/* = NULL*/)
{
    assert(Handle());
    return ::GetTextExtentExPoint(Handle(), lpszString, cchString,
        nMaxExtent, lpnFit, alpDx, lpSize);
}

inline DWORD MDC::GetTabbedTextExtent(LPCTSTR lpszString,
    INT nCount/* = -1*/, INT nTabPositions/* = 0*/,
    LPINT lpnTabStopPositions/* = NULL*/) const
{
    assert(Handle());
    if (nCount == -1)
        nCount = lstrlen(lpszString);
    return ::GetTabbedTextExtent(Handle(), lpszString, nCount,
                                 nTabPositions, lpnTabStopPositions);
}

inline BOOL MDC::GrayString(
    HBRUSH hBrush, BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, INT),
    LPARAM lpData, INT nCount, INT x, INT y, INT nWidth, INT nHeight)
{
    assert(Handle());
    return ::GrayString(Handle(),
        hBrush, reinterpret_cast<GRAYSTRINGPROC>(lpfnOutput), lpData, nCount,
        x, y, nWidth, nHeight);
}

inline UINT MDC::GetTextAlign(VOID) const
{
    assert(Handle());
    return ::GetTextAlign(Handle());
}

inline UINT MDC::SetTextAlign(UINT uTA_flags)
{
    assert(Handle());
    return ::SetTextAlign(Handle(), uTA_flags);
}

inline INT MDC::GetTextFace(LPTSTR lpszFacename, INT nCount) const
{
    assert(Handle());
    return ::GetTextFace(Handle(), nCount, lpszFacename);
}

inline INT MDC::GetTextFaceLen() const
{
    assert(Handle());
    return ::GetTextFace(Handle(), 0, NULL);
}

inline BOOL MDC::GetTextMetrics(LPTEXTMETRIC lpMetrics) const
{
    assert(Handle());
    return ::GetTextMetrics(Handle(), lpMetrics);
}

inline INT MDC::SetTextJustification(INT nBreakExtra, INT nBreakCount)
{
    assert(Handle());
    return ::SetTextJustification(Handle(), nBreakExtra, nBreakCount);
}

inline INT MDC::GetTextCharacterExtra() const
{
    assert(Handle());
    return ::GetTextCharacterExtra(Handle());
}

inline INT MDC::SetTextCharacterExtra(INT nCharExtra)
{
    assert(Handle());
    return ::SetTextCharacterExtra(Handle(), nCharExtra);
}

inline BOOL MDC::DrawEdge(LPRECT prc, UINT nEdge, UINT nFlags)
{
    assert(Handle());
    return ::DrawEdge(Handle(), prc, nEdge, nFlags);
}

inline BOOL MDC::DrawFrameControl(LPRECT prc, UINT nType, UINT nState)
{
    assert(Handle());
    return ::DrawFrameControl(Handle(), prc, nType, nState);
}

inline BOOL MDC::ScrollDC(INT dx, INT dy, LPCRECT lpRectScroll,
    LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate)
{
    assert(Handle());
    return ::ScrollDC(Handle(),
        dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate);
}

inline BOOL MDC::GetCharWidth(
    UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
{
    assert(Handle());
    return ::GetCharWidth(Handle(), nFirstChar, nLastChar, lpBuffer);
}

inline BOOL MDC::GetCharWidth32(
    UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const
{
    assert(Handle());
    return ::GetCharWidth32(Handle(), nFirstChar, nLastChar, lpBuffer);
}

inline DWORD MDC::SetMapperFlags(DWORD dwFlag)
{
    assert(Handle());
    return ::SetMapperFlags(Handle(), dwFlag);
}

inline BOOL MDC::GetAspectRatioFilter(LPSIZE lpSize) const
{
    assert(Handle());
    return ::GetAspectRatioFilterEx(Handle(), lpSize);
}

inline BOOL MDC::GetCharABCWidths(
    UINT nFirstChar, UINT nLastChar, LPABC lpabc) const
{
    assert(Handle());
    return ::GetCharABCWidths(Handle(), nFirstChar, nLastChar, lpabc);
}

inline DWORD MDC::GetFontData(
    DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) const
{
    assert(Handle());
    return ::GetFontData(Handle(), dwTable, dwOffset, lpData, cbData);
}

inline INT MDC::GetKerningPairs(INT nPairs, LPKERNINGPAIR lpkrnpair) const
{
    assert(Handle());
    return static_cast<INT>(::GetKerningPairs(Handle(), static_cast<DWORD>(nPairs), lpkrnpair));
}

inline UINT MDC::GetOutlineTextMetrics(
    UINT cbData, LPOUTLINETEXTMETRIC lpotm) const
{
    assert(Handle());
    return ::GetOutlineTextMetrics(Handle(), cbData, lpotm);
}

inline DWORD MDC::GetGlyphOutline(UINT nChar, UINT nFormat,
    LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpBuffer,
    const MAT2* lpmat2) const
{
    assert(Handle());
    return ::GetGlyphOutline(Handle(), nChar, nFormat, lpgm,
        cbBuffer, lpBuffer, lpmat2);
}

inline BOOL MDC::GetCharABCWidths(
    UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const
{
    assert(Handle());
    return ::GetCharABCWidthsFloat(Handle(), nFirstChar, nLastChar, lpABCF);
}

inline BOOL MDC::GetCharWidth(
    UINT nFirstChar, UINT nLastChar, PFLOAT lpFloatBuffer) const
{
    assert(Handle());
    return ::GetCharWidthFloat(Handle(), nFirstChar, nLastChar, lpFloatBuffer);
}

inline INT MDC::Escape(
    INT nEscape, INT nCount, LPCSTR lpszInData, LPVOID lpOutData)
{
    assert(Handle());
    return ::Escape(Handle(), nEscape, nCount, lpszInData, lpOutData);
}

inline INT MDC::Escape(INT nEscape, INT nInputSize, LPCSTR lpszInputData,
    INT nOutputSize, LPSTR lpszOutputData)
{
    assert(Handle());
    return ::ExtEscape(Handle(),
        nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
}

inline INT MDC::DrawEscape(
    INT nEscape, INT nInputSize, LPCSTR lpszInputData)
{
    assert(Handle());
    return ::DrawEscape(Handle(), nEscape, nInputSize, lpszInputData);
}

inline INT MDC::StartDoc(LPCTSTR lpszDocName)
{
    DOCINFO di;
    using namespace std;
    ZeroMemory(&di, sizeof(DOCINFO));
    di.cbSize = sizeof(DOCINFO);
    di.lpszDocName = lpszDocName;
    return StartDoc(&di);
}

inline INT MDC::StartDoc(LPDOCINFO lpDocInfo)
{
    assert(Handle());
    return ::StartDoc(Handle(), lpDocInfo);
}

inline INT MDC::StartPage(VOID)
{
    assert(Handle());
    return ::StartPage(Handle());
}

inline INT MDC::EndPage(VOID)
{
    assert(Handle());
    return ::EndPage(Handle());
}

inline INT MDC::SetAbortProc(BOOL (CALLBACK* lpfn)(HDC, INT))
{
    assert(Handle());
    return ::SetAbortProc(Handle(), (ABORTPROC) lpfn);
}

inline INT MDC::AbortDoc(VOID)
{
    assert(Handle());
    return ::AbortDoc(Handle());
}

inline INT MDC::EndDoc(VOID)
{
    assert(Handle());
    return ::EndDoc(Handle());
}

inline BOOL MDC::PlayEnhMetaFile(
    HENHMETAFILE hEnhMetaFile, LPCRECT lpBounds)
{
    assert(Handle());
    return ::PlayEnhMetaFile(Handle(), hEnhMetaFile, lpBounds);
}

inline BOOL MDC::GdiComment(UINT nDataSize, CONST BYTE* pCommentData)
{
    assert(Handle());
    return ::GdiComment(Handle(), nDataSize, pCommentData);
}

inline BOOL MDC::AbortPath()
{
    assert(Handle());
    return ::AbortPath(Handle());
}

inline BOOL MDC::BeginPath()
{
    assert(Handle());
    return ::BeginPath(Handle());
}

inline BOOL MDC::CloseFigure()
{
    assert(Handle());
    return ::CloseFigure(Handle());
}

inline BOOL MDC::EndPath()
{
    assert(Handle());
    return ::EndPath(Handle());
}

inline BOOL MDC::FillPath()
{
    assert(Handle());
    return ::FillPath(Handle());
}

inline BOOL MDC::FlattenPath()
{
    assert(Handle());
    return ::FlattenPath(Handle());
}

inline BOOL MDC::StrokeAndFillPath()
{
    assert(Handle());
    return ::StrokeAndFillPath(Handle());
}

inline BOOL MDC::StrokePath()
{
    assert(Handle());
    return ::StrokePath(Handle());
}

inline BOOL MDC::WidenPath()
{
    assert(Handle());
    return ::WidenPath(Handle());
}

inline BOOL MDC::GetMiterLimit(PFLOAT pfMiterLimit) const
{
    assert(Handle());
    return ::GetMiterLimit(Handle(), pfMiterLimit);
}

inline BOOL MDC::SetMiterLimit(FLOAT fMiterLimit, PFLOAT peOldLimit/* = NULL*/)
{
    assert(Handle());
    return ::SetMiterLimit(Handle(), fMiterLimit, peOldLimit);
}

inline INT MDC::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, INT nCount) const
{
    assert(Handle());
    return ::GetPath(Handle(), lpPoints, lpTypes, nCount);
}

inline BOOL MDC::SelectClipPath(INT nRGN_)
{
    assert(Handle());
    return ::SelectClipPath(Handle(), nRGN_);
}

inline INT MDC::SetDIBitsToDevice(INT x, INT y,
    DWORD dwWidth, DWORD dwHeight, INT xSrc, INT ySrc,
    UINT uStartScan, UINT cScanLines, LPCVOID lpvBits,
    CONST BITMAPINFO* lpbmi, UINT uColorUse)
{
    assert(Handle());
    return ::SetDIBitsToDevice(Handle(), x, y, dwWidth, dwHeight,
        xSrc, ySrc, uStartScan, cScanLines, lpvBits, lpbmi, uColorUse);
}

inline INT MDC::StretchDIBits(INT x, INT y, INT nWidth, INT nHeight,
    INT xSrc, INT ySrc, INT nSrcWidth, INT nSrcHeight, LPCVOID lpvBits,
    CONST BITMAPINFO* lpbmi, UINT uColorUse, DWORD dwRop)
{
    assert(Handle());
    return ::StretchDIBits(Handle(), x, y, nWidth, nHeight, xSrc, ySrc,
        nSrcWidth, nSrcHeight, lpvBits, lpbmi, uColorUse, dwRop);
}

inline UINT MDC::GetDIBColorTable(
    UINT uStartIndex, UINT cEntries, RGBQUAD* pColors) const
{
    assert(Handle());
    return ::GetDIBColorTable(Handle(), uStartIndex, cEntries, pColors);
}

inline UINT MDC::SetDIBColorTable(
    UINT uStartIndex, UINT cEntries, CONST RGBQUAD* pColors)
{
    assert(Handle());
    return ::SetDIBColorTable(Handle(), uStartIndex, cEntries, pColors);
}

#if (_WIN32_WINNT >= 0x0500)
    inline DWORD MDC::GetFontUnicodeRanges(LPGLYPHSET lpgs) const
    {
        assert(Handle());
        return ::GetFontUnicodeRanges(Handle(), lpgs);
    }

    inline DWORD MDC::GetGlyphIndices(
        LPCTSTR lpstr, INT cch, LPWORD pgi, DWORD dwFlags) const
    {
        assert(Handle());
        return ::GetGlyphIndices(Handle(), lpstr, cch, pgi, dwFlags);
    }

    inline BOOL MDC::GetTextExtentPointI(
        LPWORD pgiIn, INT cgi, LPSIZE lpSize) const
    {
        assert(Handle());
        return ::GetTextExtentPointI(Handle(), pgiIn, cgi, lpSize);
    }

    inline BOOL MDC::GetTextExtentExPointI(LPWORD pgiIn, INT cgi,
        INT nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize) const
    {
        assert(Handle());
        return ::GetTextExtentExPointI(Handle(),
            pgiIn, cgi, nMaxExtent, lpnFit, alpDx, lpSize);
    }

    inline BOOL MDC::GetCharWidthI(UINT giFirst, UINT cgi,
        LPWORD pgi, LPINT lpBuffer) const
    {
        assert(Handle());
        return ::GetCharWidthI(Handle(), giFirst, cgi, pgi, lpBuffer);
    }

    inline BOOL MDC::GetCharABCWidthsI(
        UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const
    {
        assert(Handle());
        return ::GetCharABCWidthsI(Handle(), giFirst, cgi, pgi, lpabc);
    }
#endif  // (_WIN32_WINNT >= 0x0500)

inline BOOL MDC::SetWindowExt(INT x, INT y, LPSIZE lpSize/* = NULL*/)
{
    assert(Handle());
    return ::SetWindowExtEx(Handle(), x, y, lpSize);
}

inline BOOL MDC::SetWindowOrg(INT x, INT y, LPPOINT lpPoint/* = NULL*/)
{
    assert(Handle());
    return ::SetWindowOrgEx(Handle(), x, y, lpPoint);
}

inline BOOL MDC::SetViewportExt(INT cx, INT cy, LPSIZE lpSize/* = NULL*/)
{
    assert(Handle());
    return ::SetViewportExtEx(Handle(), cx, cy, lpSize);
}

inline BOOL MDC::SetViewportOrg(INT x, INT y, LPPOINT lpPoint/* = NULL*/)
{
    assert(Handle());
    return ::SetViewportOrgEx(Handle(), x, y, lpPoint);
}

inline BOOL MDC::OffsetViewportOrg(
    INT nWidth, INT nHeight, LPPOINT lpPoint/* = NULL*/)
{
    assert(Handle());
    return ::OffsetViewportOrgEx(Handle(), nWidth, nHeight, lpPoint);
}

inline BOOL MDC::PatBlt(LPCRECT prc, DWORD dwRop/* = PATCOPY*/)
{
    assert(Handle());
    MRect rc(prc);
    return PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), dwRop);
}

inline VOID GetDpiDx(FLOAT *xdpi, FLOAT *ydpi)
{
    static FLOAT s_xdpi = 0.0f, s_ydpi = 0.0f;
    if (s_xdpi == 0.0)
    {
        HWND hwnd = ::GetDesktopWindow();
        HDC hdc = ::GetDC(hwnd);
        s_xdpi = ::GetDeviceCaps(hdc, LOGPIXELSX);
        s_ydpi = ::GetDeviceCaps(hdc, LOGPIXELSY);
        ::ReleaseDC(hwnd, hdc);
    }
    if (xdpi)
        *xdpi = s_xdpi;
    if (ydpi)
        *ydpi = s_ydpi;
}

inline VOID MDC::Draw3dRect(INT x, INT y, INT cx, INT cy,
    COLORREF clrTopLeft, COLORREF clrBottomRight)
{
    FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
    FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
    FillSolidRect(x + cx, y, -1, cy, clrBottomRight);
    FillSolidRect(x, y + cy, cx, -1, clrBottomRight);
}

inline MSize MDC::GetTextExtent(LPCTSTR lpszString) const
{
    return MDC::GetTextExtent(lpszString, lstrlen(lpszString));
}

inline BOOL MDC::DitherBlt(INT x, INT y, INT nWidth, INT nHeight,
    HDC hSrcDC, HBITMAP hBitmap, INT xSrc, INT ySrc,
    HBRUSH hBrushBackground/* = ::GetSysColorBrush(COLOR_3DFACE)*/,
    HBRUSH hBrush3DEffect/* = ::GetSysColorBrush(COLOR_3DHILIGHT)*/,
    HBRUSH hBrushDisabledImage/* = ::GetSysColorBrush(COLOR_3DSHADOW)*/)
{
    assert(Handle() || hBitmap);
    assert(nWidth > 0 && nHeight > 0);

    // Create a generic DC for all BitBlts
    MDC dc((hSrcDC) ? hSrcDC : ::CreateCompatibleDC(Handle()));
    assert(!!dc);
    if (!dc)
        return FALSE;

    // Create a DC for the monochrome DIB section
    MMemoryDC dcBW(Handle());
    assert(!!dcBW);
    if (!dcBW)
    {
        if(hSrcDC)
            dc.Detach();
        return FALSE;
    }

    // Create the monochrome DIB section with a black and white palette
    struct RGBBWBITMAPINFO
    {
        BITMAPINFOHEADER bmiHeader;
        RGBQUAD bmiColors[2];
    };

    RGBBWBITMAPINFO rgbBWBitmapInfo =
    {
        { sizeof(BITMAPINFOHEADER), nWidth, nHeight, 1, 1,
          BI_RGB, 0, 0, 0, 0, 0 },
        { { 0x00, 0x00, 0x00, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 } }
    };

    VOID* pbitsBW;
    MBitmap bmpBW;
    bmpBW.CreateDIBSection(reinterpret_cast<LPBITMAPINFO>(&rgbBWBitmapInfo),
                           &pbitsBW);
    assert(!!bmpBW);
    if (!bmpBW)
    {
        if(hSrcDC)
            dc.Detach();
        return FALSE;
    }

    // Attach the monochrome DIB section and the bitmap to the DCs
    HBITMAP hbmOldBW = dcBW.SelectObject(bmpBW);
    HBITMAP hbmOldDC = NULL;
    if (hBitmap)
        hbmOldDC = dc.SelectObject(hBitmap);

    {
        MMemoryDC dcTemp1(Handle());
        MMemoryDC dcTemp2(Handle());
        MBitmap bmpTemp1;
        bmpTemp1.CreateCompatibleBitmap(dc, nWidth, nHeight);
        MBitmap bmpTemp2;
        bmpTemp2.CreateBitmap(nWidth, nHeight, 1);
        HBITMAP hOldBmp1 = dcTemp1.SelectObject(bmpTemp1);
        HBITMAP hOldBmp2 = dcTemp2.SelectObject(bmpTemp2);
        dcTemp1.BitBlt(0, 0, nWidth, nHeight, dc, xSrc, ySrc, SRCCOPY);
        dcTemp1.SetBkColor(RGB(128, 128, 128));
        dcTemp2.BitBlt(0, 0, nWidth, nHeight, dcTemp1, 0, 0, SRCCOPY);
        dcTemp1.BitBlt(0, 0, nWidth, nHeight, dcTemp2, 0, 0, SRCINVERT);
        dcBW.BitBlt(0, 0, nWidth, nHeight, dcTemp1, 0, 0, SRCCOPY);
        dcTemp1.SelectObject(hOldBmp1);
        dcTemp2.SelectObject(hOldBmp2);
    }

    if (hBrushBackground)
        FillRect(MRect(x, y, x + nWidth, y + nHeight), hBrushBackground);

    HBRUSH hOldBrush = SelectObject(hBrush3DEffect);
    BitBlt(x + 1, y + 1, nWidth, nHeight, dcBW, 0, 0, 0xB8074A);
    SelectObject(hBrushDisabledImage);
    BitBlt(x, y, nWidth, nHeight, dcBW, 0, 0, 0xB8074A);
    SelectObject(hOldBrush);

    dcBW.SelectObject(hbmOldBW);
    dc.SelectObject(hbmOldDC);

    if (hSrcDC)
        dc.Detach();

    return TRUE;
}

inline VOID MDC::GradientFill(COLORREF Color1, COLORREF Color2, LPRECT prc,
    BOOL bVertical)
{
    INT cx = prc->right - prc->left;
    INT cy = prc->bottom - prc->top;
    INT r1 = GetRValue(Color1);
    INT g1 = GetGValue(Color1);
    INT b1 = GetBValue(Color1);
    INT r2 = GetRValue(Color2);
    INT g2 = GetGValue(Color2);
    INT b2 = GetBValue(Color2);

    COLORREF OldBkColor = GetBkColor();

    INT r = r1;
    INT g = g1;
    INT b = b1;
    if (bVertical)
    {
        INT dr = (r2 - r1) / cx;
        INT dg = (g2 - g1) / cx;
        INT db = (b2 - b1) / cx;
        for(INT i = 0; i < cx; i++)
        {
            SetBkColor(RGB(r, g, b));
            MRect line(i + prc->left, prc->top,
                       prc->left + i + 1, prc->top + cy);
            ExtTextOut(0, 0, ETO_OPAQUE, &line, NULL, 0);
            r += dr;
            g += dg;
            b += db;
        }
    }
    else
    {
        INT dr = (r2 - r1) / cy;
        INT dg = (g2 - g1) / cy;
        INT db = (b2 - b1) / cy;
        for(INT i = 0; i < cy; i++)
        {
            SetBkColor(RGB(r, g, b));
            MRect line(prc->left, i + prc->top,
                       prc->left + cx, prc->top + i + 1);
            ExtTextOut(0, 0, ETO_OPAQUE, &line, NULL, 0);
            r += dr;
            g += dg;
            b += db;
        }
    }

    SetBkColor(OldBkColor);
}

inline VOID MDC::FillSolidRect(INT x, INT y, INT cx, INT cy, COLORREF crColor)
{
    FillSolidRect(MRect(x, y, x + cx, y + cy), crColor);
}

inline VOID MDC::FillSolidRect(LPCRECT prc, COLORREF crColor)
{
    assert(Handle());
    COLORREF OldColor = ::SetBkColor(Handle(), crColor);
    if (OldColor != CLR_INVALID)
    {
        ::ExtTextOut(Handle(), 0, 0, ETO_OPAQUE, prc, NULL, 0, NULL);
        ::SetBkColor(Handle(), OldColor);
    }
}

inline INT CALLBACK EnumMetaFileProcDx(HDC hDC, HANDLETABLE* pHandleTable,
    METARECORD* pMetaRec, INT nHandles, LPARAM lParam)
{
    MDC* pDC = (MDC *) lParam;

    switch (pMetaRec->rdFunction)
    {
    case META_SETMAPMODE:
        pDC->SetMapMode(static_cast<INT>(static_cast<SHORT>(pMetaRec->rdParm[0])));
        break;

    case META_SETWINDOWEXT:
        pDC->SetWindowExt(
            static_cast<SHORT>(pMetaRec->rdParm[1]),
            static_cast<SHORT>(pMetaRec->rdParm[0]));
        break;

    case META_SETWINDOWORG:
        pDC->SetWindowOrg(
            static_cast<SHORT>(pMetaRec->rdParm[1]),
            static_cast<SHORT>(pMetaRec->rdParm[0]));
        break;

    case META_SETVIEWPORTEXT:
        pDC->SetViewportExt(
            static_cast<SHORT>(pMetaRec->rdParm[1]),
            static_cast<SHORT>(pMetaRec->rdParm[0]));
        break;

    case META_SETVIEWPORTORG:
        pDC->SetViewportOrg(
            static_cast<SHORT>(pMetaRec->rdParm[1]),
            static_cast<SHORT>(pMetaRec->rdParm[0]));
        break;

    case META_SCALEWINDOWEXT:
        pDC->ScaleWindowExt(
            static_cast<SHORT>(pMetaRec->rdParm[3]),
            static_cast<SHORT>(pMetaRec->rdParm[2]),
            static_cast<SHORT>(pMetaRec->rdParm[1]),
            static_cast<SHORT>(pMetaRec->rdParm[0]));
        break;

    case META_SCALEVIEWPORTEXT:
        pDC->ScaleViewportExt(
            static_cast<SHORT>(pMetaRec->rdParm[3]),
            static_cast<SHORT>(pMetaRec->rdParm[2]),
            static_cast<SHORT>(pMetaRec->rdParm[1]),
            static_cast<SHORT>(pMetaRec->rdParm[0]));
        break;

    case META_OFFSETVIEWPORTORG:
        pDC->OffsetViewportOrg(
            static_cast<SHORT>(pMetaRec->rdParm[1]),
            static_cast<SHORT>(pMetaRec->rdParm[0]));
        break;

    case META_SAVEDC:
        pDC->SaveDC();
        break;

    case META_RESTOREDC:
        pDC->RestoreDC(static_cast<SHORT>(pMetaRec->rdParm[0]));
        break;

    case META_SETBKCOLOR:
        {
            WORD wLow = pMetaRec->rdParm[0], wHigh = pMetaRec->rdParm[1];
            pDC->SetBkColor(MAKELONG(wLow, wHigh));
        }
        break;

    case META_SETTEXTCOLOR:
        {
            WORD wLow = pMetaRec->rdParm[0], wHigh = pMetaRec->rdParm[1];
            pDC->SetTextColor(MAKELONG(wLow, wHigh));
        }
        break;

    // need to watch out for SelectObject(HFONT), for custom font mapping
    case META_SELECTOBJECT:
        {
            HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
            UINT nObjType = ::GetObjectType(hObject);
            if (nObjType == 0)
            {
                HFONT hStockFont = reinterpret_cast<HFONT>(::GetStockObject(SYSTEM_FONT));
                HFONT hFontOld = reinterpret_cast<HFONT>(::SelectObject(*pDC, hStockFont));
                HGDIOBJ hObjOld = ::SelectObject(*pDC, hObject);
                if(hObjOld == hStockFont)
                {
                    pDC->SelectObject(reinterpret_cast<HFONT>(hObject));
                    break;
                }
                else
                {
                    pDC->SelectObject(hFontOld);
                    ::SelectObject(*pDC, hObjOld);
                }
            }
            else if(nObjType == OBJ_FONT)
            {
                pDC->SelectObject(reinterpret_cast<HFONT>(hObject));
                break;
            }
        }

    default:
        ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
        break;
    }

    return 1;
}

inline BOOL MDC::PlayMetaFile(HMETAFILE hMF)
{
    assert(Handle());
    if (::GetDeviceCaps(Handle(), TECHNOLOGY) == DT_METAFILE)
        return ::PlayMetaFile(Handle(), hMF);
    // for special playback, lParam == pDC
    LPARAM lParam = reinterpret_cast<LPARAM>(this);
    return ::EnumMetaFile(Handle(), hMF, EnumMetaFileProcDx, lParam);
}

inline BOOL MDC::ExtTextOut(INT x, INT y, UINT nOptions, LPCRECT prc,
    LPCTSTR lpsz, UINT cch/* = (UINT)-1*/, LPINT lpDxWidths/* = NULL*/)
{
    assert(Handle());
    if (cch == static_cast<UINT>(-1))
        cch = ::lstrlen(lpsz);
    return ::ExtTextOut(Handle(), x, y, nOptions, prc, lpsz, cch, lpDxWidths);
}

inline VOID MDC::Draw3dRect(
    LPCRECT prc, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
    Draw3dRect(prc->left, prc->top, prc->right - prc->left,
        prc->bottom - prc->top, clrTopLeft, clrBottomRight);
}

inline BOOL MDC::BitBlt(LPCRECT prc, HDC hSrcDC, POINT ptSrc, DWORD dwRop/* = SRCCOPY*/)
{
    assert(Handle());
    MRect rc(prc);
    return BitBlt(rc.left, rc.top, rc.Width(), rc.Height(),
        hSrcDC, ptSrc.x, ptSrc.y, dwRop);
}

////////////////////////////////////////////////////////////////////////////

inline MMemoryDC::MMemoryDC()
{
}

inline MMemoryDC::MMemoryDC(HDC hBaseDC) : MDC(::CreateCompatibleDC(hBaseDC))
{
    assert(Handle());
}

inline BOOL MMemoryDC::CreateCompatibleDC(HDC hBaseDC/* = NULL*/)
{
    return Attach(::CreateCompatibleDC(hBaseDC));
}

////////////////////////////////////////////////////////////////////////////

inline MClientDC::MClientDC() : MDC(), m_hWnd(NULL)
{
}

inline MClientDC::MClientDC(HWND hWnd) : MDC(::GetDC(hWnd)), m_hWnd(hWnd)
{
    assert(hWnd == NULL || ::IsWindow(hWnd));
    assert(Handle());
}

inline /*virtual*/ MClientDC::~MClientDC()
{
    ReleaseDC();
}

inline BOOL MClientDC::GetDC(HWND hWnd)
{
    return Attach(::GetDC(hWnd));
}

inline INT MClientDC::ReleaseDC()
{
    if (Handle())
    {
        INT nResult = ::ReleaseDC(m_hWnd, Detach());
        m_hWnd = NULL;
        return nResult;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////

inline MPaintDC::MPaintDC() : MDC()
{
}

inline MPaintDC::MPaintDC(HWND hWnd) : MDC()
{
    BeginPaint(hWnd);
}

inline /*virtual*/ MPaintDC::~MPaintDC()
{
    EndPaint();
}

inline BOOL MPaintDC::BeginPaint(HWND hWnd)
{
    assert(::IsWindow(hWnd));
    assert(Handle() == NULL);
    if (Attach(::BeginPaint(hWnd, &m_ps)))
    {
        m_hWnd = hWnd;
        return TRUE;
    }
    return FALSE;
}

inline BOOL MPaintDC::EndPaint()
{
    assert(Handle());
    if (Handle())
    {
        BOOL bOK = ::EndPaint(m_hWnd, &m_ps);
        if (bOK)
        {
            m_hWnd = NULL;
            Detach();
        }
        return bOK;
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////

inline MWindowDC::MWindowDC(HWND hWnd)
    : MDC(::GetWindowDC(hWnd)), m_hWnd(hWnd)
{
    assert(Handle());
    assert(hWnd == NULL || ::IsWindow(hWnd));
}

inline /*virtual*/ MWindowDC::~MWindowDC()
{
    ReleaseDC();
}

inline BOOL MWindowDC::GetWindowDC(HWND hWnd)
{
    if (Attach(::GetWindowDC(hWnd)))
    {
        m_hWnd = hWnd;
        return TRUE;
    }
    return FALSE;
}

inline INT MWindowDC::ReleaseDC()
{
    if (Handle())
    {
        INT nOK = ::ReleaseDC(m_hWnd, Detach());
        m_hWnd = NULL;
        return nOK;
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////

inline MMetaDC::MMetaDC()
{
}

inline MMetaDC::MMetaDC(HDC hDC) : MDC(hDC)
{
}

inline MMetaDC::MMetaDC(LPCTSTR pszFile) : MDC(::CreateMetaFile(pszFile))
{
    assert(Handle());
}

inline BOOL MMetaDC::DeleteMetaFile()
{
    if (Handle())
    {
        BOOL bOK = ::DeleteMetaFile(::CloseMetaFile(Detach()));
        return bOK;
    }
    return FALSE;
}

inline /*virtual*/ MMetaDC::~MMetaDC()
{
    DeleteMetaFile();
}

inline MMetaDC& MMetaDC::operator=(HDC hDC)
{
    assert(hDC);
    assert(::GetObjectType(hDC) == OBJ_METADC);
    if (Handle() != hDC)
    {
        Attach(hDC);
    }
    return *this;
}

inline BOOL MMetaDC::CreateMetaFile(LPCTSTR pszFile/* = NULL*/)
{
    return Attach(::CreateMetaFile(pszFile));
}

inline HMETAFILE MMetaDC::CloseMetaFile()
{
    HMETAFILE hWMF = ::CloseMetaFile(Detach());
    return hWMF;
}

////////////////////////////////////////////////////////////////////////////

inline MEnhMetaDC::MEnhMetaDC() : MDC()
{
}

inline MEnhMetaDC::MEnhMetaDC(HDC hDC) : MDC(hDC)
{
}

inline MEnhMetaDC::MEnhMetaDC(HDC hdcRef, LPCRECT prc,
    LPCTSTR pszFileName/* = NULL*/, LPCTSTR pszDescription/* = NULL*/)
    : MDC(::CreateEnhMetaFile(hdcRef, pszFileName, prc, pszDescription))
{
    assert(Handle());
}

inline /*virtual*/ MEnhMetaDC::~MEnhMetaDC()
{
    DeleteEnhMetaFile();
}

inline BOOL MEnhMetaDC::CreateEnhMetaFile(HDC hdcRef, LPCRECT prc,
    LPCTSTR pszFileName/* = NULL*/, LPCTSTR pszDescription/* = NULL*/)
{
    return Attach(::CreateEnhMetaFile(hdcRef, pszFileName, prc, pszDescription));
}

inline HENHMETAFILE MEnhMetaDC::CloseEnhMetaFile()
{
    assert(Handle());
    assert(::GetObjectType(Handle()) == OBJ_ENHMETAFILE);
    HENHMETAFILE hEMF = ::CloseEnhMetaFile(Detach());
    return hEMF;
}

inline MEnhMetaDC& MEnhMetaDC::operator=(HDC hDC)
{
    assert(::GetObjectType(hDC) == OBJ_ENHMETADC);
    if (Handle() != hDC)
    {
        Attach(hDC);
    }
    return *this;
}

inline BOOL MEnhMetaDC::DeleteEnhMetaFile()
{
    return ::DeleteEnhMetaFile(CloseEnhMetaFile());
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MDC_HPP_
