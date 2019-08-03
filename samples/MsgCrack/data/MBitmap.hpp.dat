// MBitmap.hpp -- Win32API bitmap object wrapper                -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MBITMAP_HPP_
#define MZC4_MBITMAP_HPP_       5       /* Version 5 */

class MBitmap;
union BITMAPINFODX;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#ifndef _INC_COMMCTRL
    #include <commctrl.h>   // for COLORMAP
#endif
#include <algorithm>        // for std::min
#include <cmath>            // for RotateBitmapTo32BppDx

////////////////////////////////////////////////////////////////////////////

#include "MGdiObject.hpp"

class MBitmap : public MGdiObject
{
public:
    MBitmap();
    MBitmap(HBITMAP hbm);
    MBitmap(UINT nResourceID, HINSTANCE hInstance = NULL);
    MBitmap(LPCTSTR pszFileName, FLOAT *dpi = NULL);
    MBitmap(const MBitmap& bmp);
    MBitmap& operator=(HBITMAP hBitmap);
    MBitmap& operator=(const MBitmap& bmp);

    operator HBITMAP() const;
    HBITMAP Handle() const;

    BOOL GetBitmap(BITMAP *pbm) const;
    BOOL GetDIBSection(DIBSECTION *pds) const;
    BOOL GetSize(SIZE *psiz) const;
    BOOL Attach(HBITMAP hBitmap);
    HBITMAP Detach(VOID);

    BOOL LoadBitmap(UINT nResourceID, HINSTANCE hInstance = NULL);
    BOOL LoadBitmap(LPCTSTR pszResourceName, HINSTANCE hInstance = NULL);
    BOOL LoadDIBSection(UINT nResourceID, HINSTANCE hInstance = NULL);
    BOOL LoadDIBSection(LPCTSTR pszResourceName, HINSTANCE hInstance = NULL);
    BOOL LoadImage(UINT nResourceID, UINT fuLoad = LR_CREATEDIBSECTION,
        INT cxDesired = 0, INT cyDesired = 0, HINSTANCE hInstance = NULL);
    BOOL LoadImage(LPCTSTR pszResourceName, UINT fuLoad = LR_CREATEDIBSECTION,
        INT cxDesired = 0, INT cyDesired = 0, HINSTANCE hInstance = NULL);

    BOOL LoadMappedBitmap(INT_PTR nResourceID, LPCOLORMAP lpColorMap, INT iNumMap,
                          HINSTANCE hInstance = NULL);
    BOOL CreateBitmap(INT cx, INT cy, INT cBitsPerPixel = 1,
        LPCVOID pvBits = NULL);

    BOOL CreateDIBSection(CONST BITMAPINFO *pbi, VOID **ppvBits);
    BOOL CreateDIBSection(HDC hDC, CONST BITMAPINFO *pbi, VOID **ppvBits);

    BOOL CreateCompatibleBitmap(HDC hDC, INT cx, INT cy);
    INT GetDIBits(HDC hDC, UINT uStartScan, UINT cScanLines,
        LPVOID lpvBits, LPBITMAPINFO lpbi, UINT uUsage) const;
    INT SetDIBits(HDC hDC, UINT uStartScan, UINT cScanLines, LPCVOID lpvBits,
        CONST BITMAPINFO* lpbi, UINT uUsage);

    static HBITMAP CloneHandleDx(HBITMAP hBitmap);
};

////////////////////////////////////////////////////////////////////////////

#ifndef RGBA
    #define RGBA(r,g,b,a)       MAKELONG(MAKEWORD(r, g), MAKEWORD(b, a))
#endif
#ifndef GetAValue
    #define GetAValue(rgba)     HIBYTE(HIWORD(rgba))
#endif

////////////////////////////////////////////////////////////////////////////

HBITMAP LoadBitmapCommonDx(HANDLE hFile, HBITMAP hbm, FLOAT *dpi = NULL);
BOOL    SaveBitmapCommonDx(HANDLE hFile, HBITMAP hbm, FLOAT dpi = 0.0);

HBITMAP LoadBitmapFromFileDx(LPCTSTR pszFileName, FLOAT* dpi = NULL);
BOOL    SaveBitmapToFileDx(LPCTSTR pszFileName, HBITMAP hbm, FLOAT dpi = 0.0);
HBITMAP RotateBitmapTo32BppDx(HBITMAP hbmSrc, DOUBLE angle, BOOL fGrow = TRUE);

////////////////////////////////////////////////////////////////////////////
// BITMAPINFODX

#include <pshpack1.h>
union BITMAPINFODX
{
    DWORD biSize;
    BITMAPINFOHEADER bmiHeader;
    BITMAPINFO bi;
    BITMAPV4HEADER bV4;
#if (WINVER >= 0x0500)
    BITMAPV5HEADER bV5;
#endif

    LPBITMAPINFO operator&()           { return &bi; }
    operator       BITMAPINFO&()       { return bi; }
    operator const BITMAPINFO&() const { return bi; }
};
typedef BITMAPINFODX *LPBITMAPINFODX;

#define WidthBytesDx(widthbits) (((widthbits) + 31) / 32 * 4)

////////////////////////////////////////////////////////////////////////////

inline MBitmap::MBitmap()
{
}

inline MBitmap::MBitmap(const MBitmap& bmp) : MGdiObject(CloneHandleDx(bmp))
{
}

inline MBitmap::MBitmap(HBITMAP hbm) : MGdiObject(hbm)
{
}

inline MBitmap::MBitmap(UINT nResourceID, HINSTANCE hInstance/* = NULL*/)
{
    LoadDIBSection(nResourceID, hInstance);
}

inline MBitmap::MBitmap(LPCTSTR pszFileName, FLOAT *dpi/* = NULL*/)
{
    LoadBitmapFromFileDx(pszFileName, dpi);
}

inline HBITMAP MBitmap::Handle() const
{
    return (this ? (HBITMAP)m_hGdiObj : NULL);
}

inline MBitmap::operator HBITMAP() const
{
    return Handle();
}

inline BOOL MBitmap::GetBitmap(BITMAP *pbm) const
{
    assert(Handle());
    return ::GetObject(Handle(), sizeof(BITMAP), pbm) == sizeof(BITMAP);
}

inline BOOL MBitmap::GetDIBSection(DIBSECTION *pds) const
{
    assert(Handle());
    return ::GetObject(Handle(), sizeof(DIBSECTION), pds) ==
           sizeof(DIBSECTION);
}

inline MBitmap& MBitmap::operator=(HBITMAP hBitmap)
{
    assert(hBitmap == NULL || ::GetObjectType(hBitmap) == OBJ_BITMAP);
    if (Handle() != hBitmap)
    {
        Attach(hBitmap);
    }
    return *this;
}

inline MBitmap& MBitmap::operator=(const MBitmap& bmp)
{
    if (Handle() != bmp.Handle())
    {
        HBITMAP hbm = CloneHandleDx(bmp);
        Attach(hbm);
    }
    return *this;
}

inline BOOL MBitmap::Attach(HBITMAP hBitmap)
{
    assert(::GetObjectType(hBitmap) == OBJ_BITMAP);
    return MGdiObject::Attach(hBitmap);
}

inline HBITMAP MBitmap::Detach(VOID)
{
    return reinterpret_cast<HBITMAP>(MGdiObject::Detach());
}

inline BOOL MBitmap::GetSize(SIZE *psiz) const
{
    BITMAP bm;
    if (GetBitmap(&bm))
    {
        psiz->cx = bm.bmWidth;
        psiz->cy = bm.bmHeight;
        return TRUE;
    }
    return FALSE;
}

inline BOOL MBitmap::LoadBitmap(LPCTSTR pszResourceName, HINSTANCE hInstance/* = NULL*/)
{
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    return Attach(::LoadBitmap(hInstance, pszResourceName));
}

inline BOOL MBitmap::LoadBitmap(UINT nResourceID, HINSTANCE hInstance/* = NULL*/)
{
    assert(nResourceID != 0);
    return LoadBitmap(MAKEINTRESOURCE(nResourceID), hInstance);
}

inline BOOL MBitmap::LoadDIBSection(LPCTSTR pszResourceName, HINSTANCE hInstance/* = NULL*/)
{
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    HBITMAP hbm;
    hbm = reinterpret_cast<HBITMAP>(::LoadImage(hInstance, pszResourceName, IMAGE_BITMAP,
                                                0, 0, LR_CREATEDIBSECTION));
    return Attach(hbm);
}

inline BOOL MBitmap::LoadDIBSection(UINT nResourceID, HINSTANCE hInstance/* = NULL*/)
{
    assert(Handle() == NULL);
    assert(nResourceID != 0);
    return LoadDIBSection(MAKEINTRESOURCE(nResourceID), hInstance);
}

inline BOOL MBitmap::LoadImage(LPCTSTR pszResourceName,
    UINT fuLoad/* = LR_CREATEDIBSECTION*/,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, HINSTANCE hInstance/* = NULL*/)
{
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    HBITMAP hbm;
    hbm = reinterpret_cast<HBITMAP>(::LoadImage(hInstance, pszResourceName, IMAGE_BITMAP,
                                                cxDesired, cyDesired, fuLoad));
    return Attach(hbm);
}

inline BOOL MBitmap::LoadImage(UINT nResourceID,
    UINT fuLoad/* = LR_CREATEDIBSECTION*/,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, HINSTANCE hInstance/* = NULL*/)
{
    assert(nResourceID != 0);
    return LoadImage(MAKEINTRESOURCE(nResourceID), fuLoad, cxDesired, cyDesired, hInstance);
}

inline BOOL MBitmap::LoadMappedBitmap(
    INT_PTR nResourceID, LPCOLORMAP lpColorMap, INT iNumMap, HINSTANCE hInstance/* = NULL*/)
{
#ifndef NDEBUG
    BITMAP bm;
    HBITMAP hbm = ::LoadBitmap(
        ::GetModuleHandle(NULL), MAKEINTRESOURCE(nResourceID));
    assert(::GetObject(hbm, sizeof(BITMAP), &bm) != 0);
    assert(bm.bmBitsPixel <= 8);
    assert(::DeleteObject(hbm));
#endif
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    return Attach(::CreateMappedBitmap(hInstance, nResourceID, 0, lpColorMap, iNumMap));
}

inline BOOL MBitmap::CreateBitmap(INT cx, INT cy,
    INT cBitsPerPixel/* = 1*/, LPCVOID pvBits/* = NULL*/)
{
    return Attach(::CreateBitmap(cx, cy, (UINT) 1, (UINT) cBitsPerPixel, pvBits));
}

inline BOOL MBitmap::CreateDIBSection(
    CONST BITMAPINFO *pbi, VOID **ppvBits)
{
    return Attach(::CreateDIBSection(NULL, pbi, DIB_RGB_COLORS, ppvBits, NULL, 0));
}

inline BOOL MBitmap::CreateDIBSection(
    HDC hDC, CONST BITMAPINFO *pbi, VOID **ppvBits)
{
    return Attach(::CreateDIBSection(hDC, pbi, DIB_PAL_COLORS, ppvBits, NULL, 0));
}

inline BOOL MBitmap::CreateCompatibleBitmap(HDC hDC, INT cx, INT cy)
{
    return Attach(::CreateCompatibleBitmap(hDC, cx, cy));
}

inline INT MBitmap::GetDIBits(
    HDC hDC, UINT uStartScan, UINT cScanLines,  LPVOID lpvBits,
    LPBITMAPINFO lpbi, UINT uUsage) const
{
    assert(Handle());
    return ::GetDIBits(hDC, Handle(), uStartScan, cScanLines,
                       lpvBits, lpbi, uUsage);
}

inline INT MBitmap::SetDIBits(HDC hDC, UINT uStartScan, UINT cScanLines,
    LPCVOID lpvBits, CONST BITMAPINFO* lpbi, UINT uUsage)
{
    assert(Handle());
    return ::SetDIBits(hDC, Handle(), uStartScan, cScanLines,
                       lpvBits, lpbi, uUsage);
}

inline /*static*/ HBITMAP MBitmap::CloneHandleDx(HBITMAP hBitmap)
{
    if (hBitmap == NULL)
        return NULL;
    return (HBITMAP)::CopyImage(hBitmap, IMAGE_BITMAP, 0, 0,
                                LR_COPYRETURNORG | LR_CREATEDIBSECTION);
}

inline HBITMAP
LoadBitmapCommonDx(HANDLE hFile, HBITMAP hbm, FLOAT *dpi/* = NULL*/)
{
    BITMAPFILEHEADER bf;
    BITMAPINFODX bi;
    DWORD cb, cbImage;
    LPVOID pBits, pBits2;
    HDC hDC, hMemDC;

    if (!ReadFile(hFile, &bf, sizeof(BITMAPFILEHEADER), &cb, NULL))
    {
        CloseHandle(hFile);
        return hbm;
    }

    pBits = NULL;
    if (bf.bfType == 0x4D42 && bf.bfReserved1 == 0 && bf.bfReserved2 == 0 &&
        bf.bfSize > bf.bfOffBits && bf.bfOffBits > sizeof(BITMAPFILEHEADER) &&
        bf.bfOffBits <= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFODX))
    {
        if (ReadFile(hFile, &bi, bf.bfOffBits -
                     sizeof(BITMAPFILEHEADER), &cb, NULL))
        {
            if (dpi)
                *dpi = (float)(bi.bmiHeader.biXPelsPerMeter * 2.54 / 100.0);

            cbImage = bf.bfSize - bf.bfOffBits;
            pBits = malloc(cbImage);
            if (pBits)
            {
                if (ReadFile(hFile, pBits, cbImage, &cb, NULL))
                {
                    ;
                }
                else
                {
                    free(pBits);
                    pBits = NULL;
                }
            }
        }
    }
    CloseHandle(hFile);

    if (hbm)
    {
        free(pBits);
        return hbm;
    }

    hDC = CreateCompatibleDC(NULL);
    hMemDC = CreateCompatibleDC(hDC);
    hbm = CreateDIBSection(hMemDC, (BITMAPINFO*)&bi, DIB_RGB_COLORS,
                           &pBits2, NULL, 0);
    if (hbm)
    {
        if (SetDIBits(hMemDC, hbm, 0, abs(bi.bmiHeader.biHeight),
                      pBits, (BITMAPINFO*)&bi, DIB_RGB_COLORS))
        {
            ;
        }
        else
        {
            DeleteObject(hbm);
            hbm = NULL;
        }
    }
    DeleteDC(hMemDC);
    DeleteDC(hDC);

    free(pBits);
    return hbm;
}

inline HBITMAP
LoadBitmapFromFileDx(LPCTSTR pszFileName, FLOAT* dpi/* = NULL*/)
{
    HANDLE hFile;
    HBITMAP hbm;

    hbm = (HBITMAP)LoadImage(NULL, pszFileName, IMAGE_BITMAP,
        0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
                       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
        return LoadBitmapCommonDx(hFile, hbm, dpi);
    return NULL;
}

inline BOOL
SaveBitmapCommonDx(HANDLE hFile, HBITMAP hbm, FLOAT dpi/* = 0.0*/)
{
    BITMAPFILEHEADER bf;
    BITMAPINFODX bi;
    BITMAPINFOHEADER *pbmih;
    DWORD cb;
    UINT cColors, cbColors;
    HDC hDC;
    LPVOID pvBits;
    BITMAP bm;
    BOOL bOK;

    if (!::GetObject(hbm, sizeof(bm), &bm))
    {
        CloseHandle(hFile);
        return FALSE;
    }

    pbmih = &bi.bmiHeader;
    ZeroMemory(pbmih, sizeof(BITMAPINFOHEADER));
    pbmih->biSize             = sizeof(BITMAPINFOHEADER);
    pbmih->biWidth            = bm.bmWidth;
    pbmih->biHeight           = bm.bmHeight;
    pbmih->biPlanes           = 1;
    pbmih->biBitCount         = bm.bmBitsPixel;
    pbmih->biCompression      = BI_RGB;
    pbmih->biSizeImage        = bm.bmWidthBytes * bm.bmHeight;
    if (dpi != 0.0)
    {
        pbmih->biXPelsPerMeter = (LONG)(dpi * 100 / 2.54 + 0.5);
        pbmih->biYPelsPerMeter = (LONG)(dpi * 100 / 2.54 + 0.5);
    }

    if (bm.bmBitsPixel < 16)
        cColors = 1 << bm.bmBitsPixel;
    else
        cColors = 0;

    cbColors = cColors * sizeof(RGBQUAD);
    bf.bfType = 0x4d42;
    bf.bfReserved1 = 0;
    bf.bfReserved2 = 0;
    cb = sizeof(BITMAPFILEHEADER) + pbmih->biSize + cbColors;
    bf.bfOffBits = cb;
    bf.bfSize = cb + pbmih->biSizeImage;

    pvBits = malloc(pbmih->biSizeImage);
    if (pvBits == NULL)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    bOK = FALSE;
    hDC = CreateCompatibleDC(NULL);
    if (GetDIBits(hDC, hbm, 0, bm.bmHeight, pvBits, (BITMAPINFO*)&bi,
                  DIB_RGB_COLORS))
    {
        bOK = WriteFile(hFile, &bf, sizeof(BITMAPFILEHEADER), &cb, NULL) &&
              WriteFile(hFile, &bi, sizeof(BITMAPINFOHEADER), &cb, NULL) &&
              WriteFile(hFile, bi.bi.bmiColors, cbColors, &cb, NULL) &&
              WriteFile(hFile, pvBits, pbmih->biSizeImage, &cb, NULL);
    }
    DeleteDC(hDC);
    free(pvBits);
    if (!CloseHandle(hFile))
        bOK = FALSE;
    return bOK;
}

inline BOOL
SaveBitmapToFileDx(LPCTSTR pszFileName, HBITMAP hbm, FLOAT dpi/* = 0.0*/)
{
    HANDLE hFile;
    hFile = CreateFile(pszFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                       CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL |
                       FILE_FLAG_WRITE_THROUGH, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        if (SaveBitmapCommonDx(hFile, hbm, dpi))
        {
            return TRUE;
        }
        DeleteFile(pszFileName);
    }
    return false;
}

inline HBITMAP
RotateBitmapTo32BppDx(HBITMAP hbmSrc, DOUBLE angle, BOOL fGrow/* = TRUE*/)
{
    HDC hdc;
    HBITMAP hbm;
    BITMAP bm;
    BITMAPINFO bi;
    LPBYTE pbBits, pbBitsSrc;
    UINT widthbytes, widthbytesSrc;
    INT cost, sint;
    INT cx, cy, x0, x1, y0, y1, px, py, qx, qy;
    BYTE r0, g0, b0, a0, r1, g1, b1, a1;
    INT mx, my;
    INT x, y, ex0, ey0, ex1, ey1;
    using namespace std;

    if (!GetObject(hbmSrc, sizeof(bm), &bm))
        return NULL;

    if (fGrow)
    {
        cx = (INT)(fabs(bm.bmWidth * cos(angle)) + fabs(bm.bmHeight * sin(angle)) + 0.5);
        cy = (INT)(fabs(bm.bmWidth * sin(angle)) + fabs(bm.bmHeight * cos(angle)) + 0.5);
    }
    else
    {
        cx = bm.bmWidth;
        cy = bm.bmHeight;
    }

    ZeroMemory(&bi.bmiHeader, sizeof(BITMAPINFOHEADER));
    bi.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth    = cx;
    bi.bmiHeader.biHeight   = cy;
    bi.bmiHeader.biPlanes   = 1;
    bi.bmiHeader.biBitCount = 32;

    widthbytesSrc = (bm.bmWidth << 2);
    widthbytes = (cx << 2);

    do
    {
        hdc = CreateCompatibleDC(NULL);
        if (hdc != NULL)
        {
            hbm = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (VOID **)&pbBits,
                                   NULL, 0);
            if (hbm != NULL)
            {
                pbBitsSrc = (LPBYTE)malloc(widthbytesSrc * bm.bmHeight);
                if (pbBitsSrc != NULL)
                    break;
                DeleteObject(hbm);
            }
            DeleteDC(hdc);
        }
        return NULL;
    } while (0);

    px = (bm.bmWidth - 1) << 15;
    py = (bm.bmHeight - 1) << 15;
    qx = (cx - 1) << 7;
    qy = (cy - 1) << 7;
    cost = (INT)(cos(angle) * 256);
    sint = (INT)(sin(angle) * 256);
    bi.bmiHeader.biWidth    = bm.bmWidth;
    bi.bmiHeader.biHeight   = bm.bmHeight;
    GetDIBits(hdc, hbmSrc, 0, bm.bmHeight, pbBitsSrc, &bi, DIB_RGB_COLORS);
    if (bm.bmBitsPixel < 32)
    {
        UINT cdw = bm.bmWidth * bm.bmHeight;
        LPBYTE pb = pbBitsSrc;
        while (cdw--)
        {
            pb++;
            pb++;
            pb++;
            *pb++ = 0xFF;
        }
    }
    ZeroMemory(pbBits, widthbytes * cy);

    x = (0 - qx) * cost + (0 - qy) * sint + px;
    y = -(0 - qx) * sint + (0 - qy) * cost + py;
    for (my = 0; my < cy; my++)
    {
        /* x = (0 - qx) * cost + ((my << 8) - qy) * sint + px; */
        /* y = -(0 - qx) * sint + ((my << 8) - qy) * cost + py; */
        for (mx = 0; mx < cx; mx++)
        {
            /* x = ((mx << 8) - qx) * cost + ((my << 8) - qy) * sint + px; */
            /* y = -((mx << 8) - qx) * sint + ((my << 8) - qy) * cost + py; */
            x0 = x >> 16;
            x1 = std::min(x0 + 1, (INT)bm.bmWidth - 1);
            ex1 = x & 0xFFFF;
            ex0 = 0x10000 - ex1;
            y0 = y >> 16;
            y1 = std::min(y0 + 1, (INT)bm.bmHeight - 1);
            ey1 = y & 0xFFFF;
            ey0 = 0x10000 - ey1;
            if (0 <= x0 && x0 < bm.bmWidth && 0 <= y0 && y0 < bm.bmHeight)
            {
                DWORD c00 = *(DWORD *)&pbBitsSrc[(x0 << 2) + y0 * widthbytesSrc];
                DWORD c01 = *(DWORD *)&pbBitsSrc[(x0 << 2) + y1 * widthbytesSrc];
                DWORD c10 = *(DWORD *)&pbBitsSrc[(x1 << 2) + y0 * widthbytesSrc];
                DWORD c11 = *(DWORD *)&pbBitsSrc[(x1 << 2) + y1 * widthbytesSrc];
                b0 = (BYTE)(((ex0 * (c00 & 0xFF)) + (ex1 * (c10 & 0xFF))) >> 16);
                b1 = (BYTE)(((ex0 * (c01 & 0xFF)) + (ex1 * (c11 & 0xFF))) >> 16);
                g0 = (BYTE)(((ex0 * ((c00 >> 8) & 0xFF)) + (ex1 * ((c10 >> 8) & 0xFF))) >> 16);
                g1 = (BYTE)(((ex0 * ((c01 >> 8) & 0xFF)) + (ex1 * ((c11 >> 8) & 0xFF))) >> 16);
                r0 = (BYTE)(((ex0 * ((c00 >> 16) & 0xFF)) + (ex1 * ((c10 >> 16) & 0xFF))) >> 16);
                r1 = (BYTE)(((ex0 * ((c01 >> 16) & 0xFF)) + (ex1 * ((c11 >> 16) & 0xFF))) >> 16);
                a0 = (BYTE)(((ex0 * ((c00 >> 24) & 0xFF)) + (ex1 * ((c10 >> 24) & 0xFF))) >> 16);
                a1 = (BYTE)(((ex0 * ((c01 >> 24) & 0xFF)) + (ex1 * ((c11 >> 24) & 0xFF))) >> 16);
                b0 = (ey0 * b0 + ey1 * b1) >> 16;
                g0 = (ey0 * g0 + ey1 * g1) >> 16;
                r0 = (ey0 * r0 + ey1 * r1) >> 16;
                a0 = (ey0 * a0 + ey1 * a1) >> 16;
                *(DWORD *)&pbBits[(mx << 2) + my * widthbytes] =
                    MAKELONG(MAKEWORD(b0, g0), MAKEWORD(r0, a0));
            }
            x += cost << 8;
            y -= sint << 8;
        }
        x -= cx * cost << 8;
        x += sint << 8;
        y -= -cx * sint << 8;
        y += cost << 8;
    }
    free(pbBitsSrc);
    DeleteDC(hdc);
    return hbm;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MBITMAP_HPP_
