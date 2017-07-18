// MBrush.hpp -- Win32API brush object wrapper                  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MBRUSH_HPP_
#define MZC4_MBRUSH_HPP_        2   /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#include "MGdiObject.hpp"

class MBrush : public MGdiObject
{
public:
    MBrush();
    MBrush(HBRUSH hBrush);
    MBrush(COLORREF crColor);
    MBrush(const MBrush& br);

    operator HBRUSH() const;
    HBRUSH Handle() const;

    INT GetLogBrush(LOGBRUSH *lplb) const;

    MBrush& operator=(HBRUSH hBrush);
    MBrush& operator=(const MBrush& brush);

    BOOL Attach(HBRUSH hBrush);
    HBRUSH Detach(VOID);

    BOOL CreateBrushIndirect(CONST LOGBRUSH *lplb);
    BOOL CreateSolidBrush(COLORREF crColor);
    BOOL CreatePatternBrush(HBITMAP hbm8x8);
    BOOL CreateHatchBrush(INT fnHS_Style, COLORREF crColor = RGB(0, 0, 0));
    BOOL CreateDIBPatternBrushPt(CONST VOID *lpPackedDIB,
        UINT iUsage = DIB_RGB_COLORS);
    BOOL CreateSysColorBrush(INT nCOLOR_index);
    BOOL CreateHalftoneBrush();
    BOOL CreateBlackBrush();
    BOOL CreateDkGrayBrush();
    BOOL CreateGrayBrush();
    BOOL CreateLtGrayBrush();
    BOOL CreateWhiteBrush();
    BOOL CreateNullBrush();

    static HBRUSH CloneHandleDx(HBRUSH hBrush);
};

HBRUSH CreateHalftoneBrushDx(VOID);
HBRUSH CreateBlackBrushDx();
HBRUSH CreateWhiteBrushDx();
HBRUSH CreateNullBrushDx();
HBRUSH CreateDkGrayBrushDx();
HBRUSH CreateGrayBrushDx();
HBRUSH CreateLtGrayBrushDx();

////////////////////////////////////////////////////////////////////////////

inline /*static*/ HBRUSH MBrush::CloneHandleDx(HBRUSH hBrush)
{
    LOGBRUSH lb;
    ::GetObject(hBrush, sizeof(LOGBRUSH), &lb);
    return ::CreateBrushIndirect(&lb);
}

inline MBrush::MBrush()
{
}

inline MBrush::MBrush(HBRUSH hBrush) : MGdiObject(hBrush)
{
}

inline MBrush::MBrush(COLORREF crColor)
{
    CreateSolidBrush(crColor);
}

inline MBrush::MBrush(const MBrush& br) : MGdiObject(CloneHandleDx(br))
{
}

inline MBrush::operator HBRUSH() const
{
    return Handle();
}

inline HBRUSH MBrush::Handle() const
{
    return (this ? (HBRUSH)m_hGdiObj : NULL);
}

inline INT MBrush::GetLogBrush(LOGBRUSH *lplb) const
{
    assert(Handle());
    return ::GetObject(Handle(), sizeof(LOGBRUSH), lplb);
}

inline MBrush& MBrush::operator=(HBRUSH hBrush)
{
    assert(::GetObjectType(hBrush) == OBJ_BRUSH);
    if (Handle() != hBrush)
    {
        Attach(hBrush);
    }
    return *this;
}

inline MBrush& MBrush::operator=(const MBrush& brush)
{
    assert(::GetObjectType(brush.Handle()) == OBJ_BRUSH);
    if (Handle() != brush.Handle())
    {
        HBRUSH hbr = CloneHandleDx(brush);
        Attach(hbr);
    }
    return *this;
}

inline BOOL MBrush::Attach(HBRUSH hBrush)
{
    assert(::GetObjectType(hBrush) == OBJ_BRUSH);
    assert(Handle() == NULL);
    return MGdiObject::Attach(hBrush);
}

inline HBRUSH MBrush::Detach(VOID)
{
    return (HBRUSH)MGdiObject::Detach();
}

inline BOOL MBrush::CreateBrushIndirect(CONST LOGBRUSH *lplb)
{
    assert(Handle() == NULL);
    return Attach(::CreateBrushIndirect(lplb));
}

inline BOOL MBrush::CreateSolidBrush(COLORREF crColor)
{
    assert(Handle() == NULL);
    return Attach(::CreateSolidBrush(crColor));
}

inline BOOL MBrush::CreatePatternBrush(HBITMAP hbm8x8)
{
    assert(Handle() == NULL);
    return Attach(::CreatePatternBrush(hbm8x8));
}

inline BOOL MBrush::CreateHatchBrush(
    INT fnHS_Style, COLORREF crColor/* = RGB(0, 0, 0)*/)
{
    assert(Handle() == NULL);
    return Attach(::CreateHatchBrush(fnHS_Style, crColor));
}

inline BOOL MBrush::CreateDIBPatternBrushPt(
    CONST VOID *lpPackedDIB, UINT iUsage/* = DIB_RGB_COLORS*/)
{
    assert(Handle() == NULL);
    return Attach(::CreateDIBPatternBrushPt(lpPackedDIB, iUsage));
}

inline BOOL MBrush::CreateSysColorBrush(INT nCOLOR_index)
{
    assert(Handle() == NULL);
    return Attach(::GetSysColorBrush(nCOLOR_index));
}

inline BOOL MBrush::CreateHalftoneBrush()
{
    assert(Handle() == NULL);
    return Attach(CreateHalftoneBrushDx());
}

inline BOOL MBrush::CreateBlackBrush()
{
    assert(Handle() == NULL);
    return Attach(CreateBlackBrushDx());
}

inline BOOL MBrush::CreateDkGrayBrush()
{
    assert(Handle() == NULL);
    return Attach(CreateDkGrayBrushDx());
}

inline BOOL MBrush::CreateGrayBrush()
{
    assert(Handle() == NULL);
    return Attach(CreateGrayBrushDx());
}

inline BOOL MBrush::CreateLtGrayBrush()
{
    assert(Handle() == NULL);
    return Attach(CreateLtGrayBrushDx());
}

inline BOOL MBrush::CreateWhiteBrush()
{
    assert(Handle() == NULL);
    return Attach(CreateWhiteBrushDx());
}

inline BOOL MBrush::CreateNullBrush()
{
    assert(Handle() == NULL);
    return Attach(CreateNullBrushDx());
}

inline HBRUSH CreateHalftoneBrushDx(VOID)
{
    WORD grayPattern[8];
    for (INT i = 0; i < 8; i++)
        grayPattern[i] = (WORD)(0x5555 << (i & 1));

    HBRUSH hbr = NULL;
    HBITMAP grayBitmap = ::CreateBitmap(8, 8, 1, 1, &grayPattern);
    if (grayBitmap != NULL)
    {
        hbr = ::CreatePatternBrush(grayBitmap);
        ::DeleteObject(grayBitmap);
    }

    assert(hbr != NULL);
    return hbr;
}

inline HBRUSH CreateBlackBrushDx()
{
    return (HBRUSH)::GetStockObject(BLACK_BRUSH);
}

inline HBRUSH CreateWhiteBrushDx()
{
    return (HBRUSH)::GetStockObject(WHITE_BRUSH);
}

inline HBRUSH CreateNullBrushDx()
{
    return (HBRUSH)::GetStockObject(NULL_BRUSH);
}

inline HBRUSH CreateDkGrayBrushDx()
{
    return (HBRUSH)::GetStockObject(DKGRAY_BRUSH);
}

inline HBRUSH CreateGrayBrushDx()
{
    return (HBRUSH)::GetStockObject(GRAY_BRUSH);
}

inline HBRUSH CreateLtGrayBrushDx()
{
    return (HBRUSH)::GetStockObject(LTGRAY_BRUSH);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MBRUSH_HPP_
