// MPen.hpp -- Win32API pen object wrapper                      -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPEN_HPP_
#define MZC4_MPEN_HPP_      2   /* Version 2 */

class MPen;

////////////////////////////////////////////////////////////////////////////

#include "MGdiObject.hpp"

class MPen : public MGdiObject
{
public:
    MPen();
    MPen(HPEN hPen);
    MPen(const MPen& pen);

    HPEN Handle() const;
    operator HPEN() const;

    INT GetLogPen(LOGPEN *lplp) const;

    MPen& operator=(HPEN hPen);
    MPen& operator=(const MPen& pen);

    BOOL Attach(HPEN hPen);
    HPEN Detach(VOID);

    BOOL CreatePen(COLORREF crColor = RGB(0, 0, 0), INT nWidth = 0,
                   INT fnPenStyle = PS_SOLID);
    BOOL CreatePenIndirect(CONST LOGPEN *lplp);
    BOOL ExtCreatePen(DWORD dwPenStyle, DWORD dwWidth, CONST LOGBRUSH *lplb,
                      DWORD dwStyleCount = 0, CONST DWORD *lpStyle = NULL);
    BOOL CreateBlackPen();
    BOOL CreateWhitePen();
    BOOL CreateNullPen();

    static HPEN CloneHandleDx(HPEN hPen);
};

HPEN CreateBlackPenDx();
HPEN CreateWhitePenDx();
HPEN CreateNullPenDx();

////////////////////////////////////////////////////////////////////////////
inline MPen::MPen()
{
}

inline MPen::MPen(HPEN hPen)
{
    Attach(hPen);
}

inline MPen::MPen(const MPen& pen)
{
    Attach(MPen::CloneHandleDx(pen));
}

inline HPEN MPen::Handle() const
{
    return (this ? (HPEN)m_hGdiObj : NULL);
}

inline MPen::operator HPEN() const
{
    return Handle();
}

inline INT MPen::GetLogPen(LOGPEN *lplp) const
{
    assert(m_hGdiObj);
    return ::GetObject(m_hGdiObj, sizeof(LOGPEN), lplp);
}

inline MPen& MPen::operator=(HPEN hPen)
{
    assert(hPen == NULL || ::GetObjectType(hPen) == OBJ_PEN);
    if (m_hGdiObj != (HGDIOBJ)hPen)
    {
        if (m_hGdiObj)
            DeleteObject();
        m_hGdiObj = (HGDIOBJ)hPen;
    }
    return *this;
}

inline MPen& MPen::operator=(const MPen& pen)
{
    if (m_hGdiObj != pen.m_hGdiObj)
    {
        if (m_hGdiObj)
            DeleteObject();
        m_hGdiObj = MPen::CloneHandleDx(pen);
    }
    return *this;
}

inline BOOL MPen::Attach(HPEN hPen)
{
    assert(::GetObjectType(hPen) == OBJ_PEN);
    assert(m_hGdiObj == NULL);
    return MGdiObject::Attach(hPen);
}

inline HPEN MPen::Detach(VOID)
{
    return (HPEN)MGdiObject::Detach();
}

inline BOOL MPen::CreatePen(COLORREF crColor/* = RGB(0, 0, 0)*/,
    INT nWidth/* = 0*/, INT fnPenStyle/* = PS_SOLID*/)
{
    assert(m_hGdiObj == NULL);
    return Attach(::CreatePen(fnPenStyle, nWidth, crColor));
}

inline BOOL MPen::CreatePenIndirect(CONST LOGPEN *lplp)
{
    assert(m_hGdiObj == NULL);
    return Attach(::CreatePenIndirect(lplp));
}

inline BOOL MPen::ExtCreatePen(DWORD dwPenStyle, DWORD dwWidth,
    CONST LOGBRUSH *lplb, DWORD dwStyleCount/* = 0*/,
    CONST DWORD *lpStyle/* = NULL*/)
{
    assert(m_hGdiObj == NULL);
    return Attach(::ExtCreatePen(dwPenStyle, dwWidth, lplb, dwStyleCount, lpStyle));
}

inline /*static*/ HPEN MPen::CloneHandleDx(HPEN hPen)
{
    LOGPEN lp;
    EXTLOGPEN elp;
    if (::GetObject(hPen, sizeof(EXTLOGPEN), &elp) != 0)
    {
        LOGBRUSH lb;
        lb.lbStyle = elp.elpBrushStyle;
        lb.lbColor = elp.elpColor;
        lb.lbHatch = elp.elpHatch;
        return ::ExtCreatePen(elp.elpPenStyle,
            elp.elpWidth, &lb, elp.elpNumEntries, elp.elpStyleEntry);
    }
    else
    {
        ::GetObject(hPen, sizeof(LOGPEN), &lp);
        return ::CreatePenIndirect(&lp);
    }
}

inline BOOL MPen::CreateBlackPen()
{
    return Attach(CreateBlackPenDx());
}

inline BOOL MPen::CreateWhitePen()
{
    return Attach(CreateWhitePenDx());
}

inline BOOL MPen::CreateNullPen()
{
    return Attach(CreateNullPenDx());
}

inline HPEN CreateBlackPenDx()
{
    return (HPEN)::GetStockObject(BLACK_PEN);
}

inline HPEN CreateWhitePenDx()
{
    return (HPEN)::GetStockObject(WHITE_PEN);
}

inline HPEN CreateNullPenDx()
{
    return (HPEN)::GetStockObject(NULL_PEN);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MPEN_HPP_