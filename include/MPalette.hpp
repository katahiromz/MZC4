// MPalette.hpp -- Win32API palette object wrapper              -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPALETTE_HPP_
#define MZC4_MPALETTE_HPP_     5   /* Version 5 */

class MPalette;

////////////////////////////////////////////////////////////////////////////

#include "MGdiObject.hpp"

class MPalette : public MGdiObject
{
public:
    MPalette();
    MPalette(HPALETTE hPal);
    MPalette(const MPalette& pal);
    MPalette& operator=(HPALETTE hPalette);
    MPalette& operator=(const MPalette& pal);

    HPALETTE Handle() const;
    operator HPALETTE() const;

    BOOL Attach(HPALETTE hPalette);
    HPALETTE Detach(VOID);

    WORD GetEntryCount(VOID) const;
    LOGPALETTE *GetLogPalette(VOID) const;

    BOOL CreatePalette(CONST LOGPALETTE *lplp);
    BOOL CreateHalftonePalette(HDC hDC);
    BOOL CreateDefaultPalette();

    UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
        LPPALETTEENTRY lpPaletteColors) const;
    UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
        LPPALETTEENTRY lpPaletteColors);
    UINT GetNearestPaletteIndex(COLORREF crColor) const;
    VOID AnimatePalette(UINT nStartIndex, UINT nNumEntries,
        LPPALETTEENTRY lpPaletteColors);
    BOOL ResizePalette(UINT nNumEntries);

    static HPALETTE CloneHandleDx(HPALETTE hPalette);
};

////////////////////////////////////////////////////////////////////////////

inline /*static*/ HPALETTE MPalette::CloneHandleDx(HPALETTE hPalette)
{
    if (hPalette == NULL)
        return NULL;

    MPalette pal(hPalette);
    LOGPALETTE *lp = pal.GetLogPalette();
    HPALETTE hPaletteNew = ::CreatePalette(lp);
    ::LocalFree(lp);
    pal.Detach();
    return hPaletteNew;
}

inline MPalette::MPalette()
{
}

inline MPalette::MPalette(HPALETTE hPal) : MGdiObject(hPal)
{
}

inline MPalette::MPalette(const MPalette& pal)
    : MGdiObject(CloneHandleDx(pal))
{
}

inline HPALETTE MPalette::Handle() const
{
    return (this ? (HPALETTE)m_hGdiObj : NULL);
}

inline MPalette::operator HPALETTE() const
{
    return Handle();
}

inline MPalette& MPalette::operator=(HPALETTE hPalette)
{
    assert(hPalette == NULL || ::GetObjectType(hPalette) == OBJ_PAL);
    if (Handle() != hPalette)
    {
        Attach(hPalette);
    }
    return *this;
}

inline MPalette& MPalette::operator=(const MPalette& pal)
{
    if (Handle() != pal.Handle())
    {
        HPALETTE hPal = CloneHandleDx(pal);
        Attach(hPal);
    }
    return *this;
}

inline BOOL MPalette::Attach(HPALETTE hPalette)
{
    assert(::GetObjectType(hPalette) == OBJ_PAL);
    return MGdiObject::Attach(hPalette);
}

inline HPALETTE MPalette::Detach(VOID)
{
    return reinterpret_cast<HPALETTE>(MGdiObject::Detach());
}

inline WORD MPalette::GetEntryCount(VOID) const
{
    WORD w;
    ::GetObject(Handle(), sizeof(WORD), &w);
    return w;
}

inline LOGPALETTE *MPalette::GetLogPalette(VOID) const
{
    assert(Handle());
    WORD wCount = GetEntryCount();
    DWORD cb = 2 * sizeof(WORD) + wCount * sizeof(PALETTEENTRY);
    LOGPALETTE *pal = (LOGPALETTE *)::LocalAlloc(LPTR, cb);
    assert(pal);
    pal->palVersion  = 0x300;
    pal->palNumEntries  = wCount;
    ::GetPaletteEntries(Handle(), 0, wCount, pal->palPalEntry);
    return pal;
}

inline BOOL MPalette::CreatePalette(CONST LOGPALETTE *lplp)
{
    return Attach(::CreatePalette(lplp));
}

inline BOOL MPalette::CreateHalftonePalette(HDC hDC)
{
    return Attach(::CreateHalftonePalette(hDC));
}

inline BOOL MPalette::CreateDefaultPalette()
{
    return Attach((HPALETTE)::GetStockObject(DEFAULT_PALETTE));
}

inline UINT MPalette::GetPaletteEntries(
    UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
{
    assert(Handle());
    return ::GetPaletteEntries(Handle(), nStartIndex, nNumEntries,
                               lpPaletteColors);
}

inline UINT MPalette::SetPaletteEntries(
    UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
{
    assert(Handle());
    return ::SetPaletteEntries(Handle(),
        nStartIndex, nNumEntries, lpPaletteColors);
}

inline UINT MPalette::GetNearestPaletteIndex(COLORREF crColor) const
{
    assert(Handle());
    return ::GetNearestPaletteIndex(Handle(), crColor);
}

inline VOID MPalette::AnimatePalette(
    UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
{
    assert(Handle());
    ::AnimatePalette(Handle(), nStartIndex, nNumEntries, lpPaletteColors);
}

inline BOOL MPalette::ResizePalette(UINT nNumEntries)
{
    assert(Handle());
    return ::ResizePalette(Handle(), nNumEntries);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MPALETTE_HPP_
