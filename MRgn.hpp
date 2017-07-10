// MRgn.hpp -- Win32API region wrapper                      -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MRGN_HPP_
#define MZC4_MRGN_HPP_      2       /* Version 2 */

class MRgn;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

#include "MGdiObject.hpp"

class MRgn : public MGdiObject
{
public:
    MRgn();
    MRgn(HRGN hRgn);
    MRgn(INT x1, INT y1, INT x2, INT y2, BOOL bElliptic = FALSE);
    MRgn(LPCRECT prc, BOOL bElliptic = FALSE);
    MRgn(const MRgn& rgn);

    operator HRGN() const;
    MRgn& operator=(HRGN hRgn);
    MRgn& operator=(const MRgn& rgn);

    BOOL Attach(HRGN hRgn);
    HRGN Detach(VOID);
    HRGN Handle() const;

    BOOL IsRgnEmptyDx() const;
    BOOL CreateEmptyRgn();
    BOOL CreateRectRgn(INT x1, INT y1, INT x2, INT y2);
    BOOL CreateRectRgnIndirect(LPCRECT prc);
    BOOL CreateEllipticRgn(INT x1, INT y1, INT x2, INT y2);
    BOOL CreateEllipticRgnIndirect(LPCRECT prc);
    BOOL CreatePolygonRgn(LPPOINT ppts, INT nCount, INT nMode);
    BOOL CreatePolyPolygonRgn(LPPOINT ppts, LPINT lpPolyCounts, INT nCount,
                              INT nPolyFillMode);
    BOOL CreateRoundRectRgn(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3);
    BOOL PathToRegion(HDC hDC);
    BOOL ExtCreateRegion(CONST XFORM* lpXForm OPTIONAL, INT nCount,
                         CONST RGNDATA* pRgnData);

    VOID SetRectRgn(INT x1, INT y1, INT x2, INT y2);
    VOID SetRectRgn(LPCRECT prc);
    INT CombineRgn(HRGN hRgnSrc1, HRGN hRgnSrc2, INT nCombineMode);
    INT CombineRgn(HRGN hRgnSrc, INT nCombineMode);
    INT CopyRgnDx(HRGN hRgnSrc);
    BOOL EqualRgn(HRGN hRgn) const;
    INT OffsetRgn(INT x, INT y);
    INT OffsetRgn(POINT pt);
    INT GetRgnBox(LPRECT prc) const;
    BOOL PtInRegion(INT x, INT y) const;
    BOOL PtInRegion(POINT pt) const;
    BOOL RectInRegion(LPCRECT prc) const;
    DWORD GetRegionData(DWORD nDataSize, LPRGNDATA pRgnData) const;

    INT IntersectRgnDx(HRGN hrgnA, HRGN hrgnB)
    {
        return CombineRgn(hrgnA, hrgnB, RGN_AND);
    }
    INT SubtractRgnDx(HRGN hrgnA, HRGN hrgnB)
    {
        return CombineRgn(hrgnA, hrgnB, RGN_DIFF);
    }
    INT UnionRgnDx(HRGN hrgnA, HRGN hrgnB)
    {
        return CombineRgn(hrgnA, hrgnB, RGN_OR);
    }
    INT XorRgnDx(HRGN hrgnA, HRGN hrgnB)
    {
        return CombineRgn(hrgnA, hrgnB, RGN_XOR);
    }

    INT IntersectRgnDx(HRGN hrgnB)
    {
        return CombineRgn(hrgnB, RGN_AND);
    }
    INT SubtractRgnDx(HRGN hrgnB)
    {
        return CombineRgn(hrgnB, RGN_DIFF);
    }
    INT UnionRgnDx(HRGN hrgnB)
    {
        return CombineRgn(hrgnB, RGN_OR);
    }
    INT XorRgnDx(HRGN hrgnB)
    {
        return CombineRgn(hrgnB, RGN_XOR);
    }

    static HRGN CloneHandleDx(HRGN hRgn);
};

BOOL IsRgnEmptyDx(HRGN hRgn);

////////////////////////////////////////////////////////////////////////////

inline /*static*/ HRGN MRgn::CloneHandleDx(HRGN hRgn)
{
    HRGN hRgnNew = ::CreateRectRgn(0, 0, 0, 0);
    assert(hRgnNew != NULL);
    ::CombineRgn(hRgnNew, hRgnNew, hRgn, RGN_OR);
    return hRgnNew;
}

inline MRgn::MRgn()
{
}

inline MRgn::MRgn(HRGN hRgn)
{
    Attach(hRgn);
}

inline MRgn::MRgn(
    INT x1, INT y1, INT x2, INT y2, BOOL bElliptic/* = FALSE*/)
{
    if (bElliptic)
        MRgn::CreateEllipticRgn(x1, y1, x2, y2);
    else
        MRgn::CreateRectRgn(x1, y1, x2, y2);
}

inline MRgn::MRgn(LPCRECT prc, BOOL bElliptic/* = FALSE*/)
{
    m_hGdiObj = NULL;
    if (bElliptic)
        MRgn::CreateEllipticRgnIndirect(prc);
    else
        MRgn::CreateRectRgnIndirect(prc);
}

inline MRgn::MRgn(const MRgn& rgn)
{
    Attach(MRgn::CloneHandleDx(rgn));
}

inline MRgn::operator HRGN() const
{
    return Handle();
}

inline MRgn& MRgn::operator=(HRGN hRgn)
{
    assert(hRgn == NULL || ::GetObjectType(hRgn) == OBJ_REGION);
    if (m_hGdiObj != (HGDIOBJ)hRgn)
    {
        if (m_hGdiObj)
            DeleteObject();
        m_hGdiObj = (HGDIOBJ)hRgn;
    }
    return *this;
}

inline MRgn& MRgn::operator=(const MRgn& rgn)
{
    if (m_hGdiObj != rgn.m_hGdiObj)
    {
        if (m_hGdiObj)
            DeleteObject();
        m_hGdiObj = MRgn::CloneHandleDx(rgn);
    }
    return *this;
}

inline BOOL MRgn::Attach(HRGN hRgn)
{
    assert(::GetObjectType(hRgn) == OBJ_REGION);
    assert(m_hGdiObj == NULL);
    return MGdiObject::Attach(hRgn);
}

inline HRGN MRgn::Detach(VOID)
{
    return (HRGN)MGdiObject::Detach();
}

inline HRGN MRgn::Handle() const
{
    return (this ? (HRGN)m_hGdiObj : NULL);
}

inline BOOL MRgn::CreateEmptyRgn()
{
    assert(m_hGdiObj == NULL);
    return CreateRectRgn(0, 0, 0, 0);
}

inline BOOL MRgn::CreateRectRgn(INT x1, INT y1, INT x2, INT y2)
{
    assert(m_hGdiObj == NULL);
    return Attach(::CreateRectRgn(x1, y1, x2, y2));
}

inline BOOL MRgn::CreateRectRgnIndirect(LPCRECT prc)
{
    assert(m_hGdiObj == NULL);
    return Attach(::CreateRectRgnIndirect(prc));
}

inline BOOL MRgn::CreateEllipticRgn(INT x1, INT y1, INT x2, INT y2)
{
    assert(Handle() == NULL);
    return Attach(::CreateEllipticRgn(x1, y1, x2, y2));
}

inline BOOL MRgn::CreateEllipticRgnIndirect(LPCRECT prc)
{
    assert(Handle() == NULL);
    return Attach(::CreateEllipticRgnIndirect(prc));
}

inline BOOL MRgn::CreatePolygonRgn(LPPOINT ppts, INT nCount, INT nMode)
{
    assert(Handle() == NULL);
    return Attach(::CreatePolygonRgn(ppts, nCount, nMode));
}

inline BOOL MRgn::CreatePolyPolygonRgn(
    LPPOINT ppts, LPINT lpPolyCounts, INT nCount, INT nPolyFillMode)
{
    assert(Handle() == NULL);
    return Attach(::CreatePolyPolygonRgn(ppts, lpPolyCounts, nCount, nPolyFillMode));
}

inline BOOL MRgn::CreateRoundRectRgn(
    INT x1, INT y1, INT x2, INT y2, INT x3, INT y3)
{
    assert(Handle() == NULL);
    return Attach(::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3));
}

inline BOOL MRgn::PathToRegion(HDC hDC)
{
    assert(Handle() == NULL);
    assert(hDC != NULL);
    return Attach(::PathToRegion(hDC));
}

inline BOOL MRgn::ExtCreateRegion(
    CONST XFORM* lpXForm OPTIONAL, INT nCount, CONST RGNDATA* pRgnData)
{
    assert(Handle() == NULL);
    return Attach(::ExtCreateRegion(lpXForm, (DWORD) nCount, pRgnData));
}

inline VOID MRgn::SetRectRgn(INT x1, INT y1, INT x2, INT y2)
{
    assert(m_hGdiObj);
    ::SetRectRgn(Handle(), x1, y1, x2, y2);
}

inline VOID MRgn::SetRectRgn(LPCRECT prc)
{
    assert(m_hGdiObj);
    ::SetRectRgn(Handle(), prc->left, prc->top, prc->right, prc->bottom);
}

inline INT MRgn::CombineRgn(HRGN hRgnSrc1, HRGN hRgnSrc2, INT nCombineMode)
{
    assert(m_hGdiObj);
    return ::CombineRgn(Handle(), hRgnSrc1, hRgnSrc2, nCombineMode);
}

inline INT MRgn::CombineRgn(HRGN hRgnSrc, INT nCombineMode)
{
    assert(m_hGdiObj);
    return ::CombineRgn(Handle(), Handle(), hRgnSrc, nCombineMode);
}

inline INT MRgn::CopyRgnDx(HRGN hRgnSrc)
{
    assert(m_hGdiObj);
    return ::CombineRgn(Handle(), hRgnSrc, NULL, RGN_COPY);
}

inline BOOL MRgn::EqualRgn(HRGN hRgn) const
{
    assert(m_hGdiObj);
    return ::EqualRgn(Handle(), hRgn);
}

inline INT MRgn::OffsetRgn(INT x, INT y)
{
    assert(m_hGdiObj);
    return ::OffsetRgn(Handle(), x, y);
}

inline INT MRgn::OffsetRgn(POINT pt)
{
    assert(m_hGdiObj);
    return ::OffsetRgn(Handle(), pt.x, pt.y);
}

inline INT MRgn::GetRgnBox(LPRECT prc) const
{
    assert(m_hGdiObj);
    return ::GetRgnBox(Handle(), prc);
}

inline BOOL MRgn::PtInRegion(INT x, INT y) const
{
    assert(m_hGdiObj);
    return ::PtInRegion(Handle(), x, y);
}

inline BOOL MRgn::PtInRegion(POINT pt) const
{
    assert(m_hGdiObj);
    return ::PtInRegion(Handle(), pt.x, pt.y);
}

inline BOOL MRgn::RectInRegion(LPCRECT prc) const
{
    assert(m_hGdiObj);
    return ::RectInRegion(Handle(), prc);
}

inline DWORD MRgn::GetRegionData(DWORD nDataSize, LPRGNDATA pRgnData) const
{
    assert(m_hGdiObj);
    return ::GetRegionData(Handle(), nDataSize, pRgnData);
}

inline BOOL MRgn::IsRgnEmptyDx() const
{
    assert(m_hGdiObj);
    return ::IsRgnEmptyDx(Handle());
}

inline BOOL IsRgnEmptyDx(HRGN hRgn)
{
    HRGN hrgnEmpty = ::CreateRectRgn(0, 0, 0, 0);
    BOOL bOK = ::EqualRgn(hRgn, hrgnEmpty);
    ::DeleteObject(hrgnEmpty);
    return bOK;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MRGN_HPP_
