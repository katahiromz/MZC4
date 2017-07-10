// MAccel.hpp -- Win32API cursor wrapper                    -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MCURSOR_HPP_
#define MZC4_MCURSOR_HPP_

class MCursor;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

inline HCURSOR CopyCursorDx(HCURSOR hCursor)
{
    return ::CopyIcon(hCursor);
}

////////////////////////////////////////////////////////////////////////////

class MCursor
{
public:
    MCursor();
    MCursor(HCURSOR hCursor);
    MCursor(const MCursor& cur);
    virtual ~MCursor();

    bool operator!() const;
    bool operator==(HCURSOR hCursor) const;
    bool operator!=(HCURSOR hCursor) const;
    HCURSOR Handle() const;

    operator HCURSOR() const;
    VOID operator=(HCURSOR hCursor);
    VOID operator=(const MCursor& cur);

    BOOL Attach(HCURSOR hCursor);
    HCURSOR Detach();

    BOOL CopyCursorDx(HCURSOR hCursor);
    BOOL CreateCursor(HINSTANCE hInstance, INT xHotSpot, INT yHotSpot,
                      INT width, INT height,
                      const BYTE *pbANDbits, const BYTE *pbXORbits);
    BOOL CreateIconFromResource(PBYTE presbits, DWORD dwResSize,
                                BOOL fIcon = FALSE,
                                DWORD dwVer = 0x00030000);
    BOOL CreateIconFromResourceEx(PBYTE presbits, DWORD dwResSize,
                                  BOOL fIcon = FALSE,
                                  DWORD dwVer = 0x00030000,
                                  INT cxDesired = 0, INT cyDesired = 0,
                                  UINT uFlags = LR_DEFAULTCOLOR);
    BOOL LoadCursor(LPCTSTR pszResourceName, HINSTANCE hInstance = NULL);
    BOOL LoadCursor(UINT nCursorID, HINSTANCE hInstance = NULL);
    BOOL LoadCursorFromFile(LPCTSTR pszFileName);
    BOOL LoadImage(HINSTANCE hInstance, LPCTSTR pszName,
                   INT cxDesired = 0, INT cyDesired = 0, UINT fuLoad = 0);
    BOOL LoadImageFromFile(HINSTANCE hInstance, LPCTSTR pszName,
                           INT cxDesired = 0, INT cyDesired = 0,
                           UINT fuLoad = 0);
    BOOL CreateIconIndirect(PICONINFO pIconInfo);
    BOOL DestroyCursor();

    BOOL DrawIcon(HDC hDC, INT x, INT y);
    BOOL DrawIconEx(HDC hDC, INT x, INT y, INT cx, INT cy,
                    UINT index = 0, HBRUSH hbr = NULL,
                    UINT uDI_flags = DI_NORMAL);
    BOOL GetIconInfo(PICONINFO pIconInfo) const;

    static HCURSOR CloneHandleDx(HCURSOR hCursor);

protected:
    HCURSOR m_hCursor;
};

////////////////////////////////////////////////////////////////////////////

inline MCursor::MCursor() : m_hCursor(NULL)
{
}

inline MCursor::MCursor(HCURSOR hCursor) : m_hCursor(hCursor)
{
}

inline MCursor::MCursor(const MCursor& cur)
    : m_hCursor(MCursor::CloneHandleDx(cur.m_hCursor))
{
}

inline /*virtual*/ MCursor::~MCursor()
{
    if (m_hCursor)
        DestroyCursor();
}

inline bool MCursor::operator!() const
{
    return Handle() == NULL;
}

inline bool MCursor::operator==(HCURSOR hCursor) const
{
    return Handle() == hCursor;
}

inline bool MCursor::operator!=(HCURSOR hCursor) const
{
    return Handle() != hCursor;
}

inline HCURSOR MCursor::Handle() const
{
    return (this ? m_hCursor : NULL);
}

inline MCursor::operator HCURSOR() const
{
    return Handle();
}

inline VOID MCursor::operator=(HCURSOR hCursor)
{
    if (m_hCursor != hCursor)
        Attach(hCursor);
}

inline VOID MCursor::operator=(const MCursor& cur)
{
    if (this != &cur)
        Attach(MCursor::CloneHandleDx(cur));
}

inline BOOL MCursor::Attach(HCURSOR hCursor)
{
    if (m_hCursor)
        DestroyCursor();
    assert(m_hCursor == NULL);
    m_hCursor = hCursor;
    return m_hCursor != NULL;
}

inline HCURSOR MCursor::Detach()
{
    HCURSOR hCursor = m_hCursor;
    m_hCursor = NULL;
    return hCursor;
}

inline BOOL MCursor::CopyCursorDx(HCURSOR hCursor)
{
    return Attach(::CopyCursorDx(hCursor));
}

inline BOOL MCursor::CreateCursor(HINSTANCE hInstance, INT xHotSpot, INT yHotSpot,
    INT width, INT height, const BYTE *pbANDbits, const BYTE *pbXORbits)
{
    HCURSOR hCursor = ::CreateCursor(hInstance, xHotSpot, yHotSpot,
                                     width, height, pbANDbits, pbXORbits);
    if (hCursor == NULL && hInstance == NULL)
    {
        hInstance = ::GetModuleHandle(NULL);
        hCursor = ::CreateCursor(hInstance, xHotSpot, yHotSpot,
                                 width, height, pbANDbits, pbXORbits);
    }
    return Attach(hCursor);
}

inline BOOL MCursor::CreateIconFromResource(PBYTE presbits, DWORD dwResSize,
    BOOL fIcon/* = FALSE*/, DWORD dwVer/* = 0x00030000*/)
{
    HCURSOR hCursor = ::CreateIconFromResource(presbits, dwResSize, fIcon, dwVer);
    return Attach(hCursor);
}

inline BOOL MCursor::CreateIconFromResourceEx(PBYTE presbits, DWORD dwResSize,
    BOOL fIcon/* = FALSE*/, DWORD dwVer/* = 0x00030000*/,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, UINT uFlags/* = LR_DEFAULTCOLOR*/)
{
    return Attach(::CreateIconFromResourceEx(presbits, dwResSize, fIcon, dwVer,
                                             cxDesired, cyDesired, uFlags));
}

inline BOOL MCursor::LoadCursor(
    LPCTSTR pszResourceName, HINSTANCE hInstance/* = NULL*/)
{
    HCURSOR hCursor = ::LoadCursor(hInstance, pszResourceName);
    if (hCursor == NULL && hInstance == NULL)
    {
        hInstance = ::GetModuleHandle(NULL);
        hCursor = ::LoadCursor(hInstance, pszResourceName);
    }
    return Attach(hCursor);
}

inline BOOL MCursor::LoadCursor(UINT nCursorID, HINSTANCE hInstance/* = NULL*/)
{
    return LoadCursor(MAKEINTRESOURCE(nCursorID), hInstance);
}

inline BOOL MCursor::LoadCursorFromFile(LPCTSTR pszFileName)
{
    return Attach(::LoadCursorFromFile(pszFileName));
}

inline BOOL MCursor::LoadImage(HINSTANCE hInstance, LPCTSTR pszName,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, UINT fuLoad/* = 0*/)
{
    HCURSOR hCursor = reinterpret_cast<HCURSOR>(
        ::LoadImage(hInstance, pszName, IMAGE_ICON,
                    cxDesired, cyDesired, fuLoad));
    if (hCursor == NULL && hInstance == NULL)
    {
        hInstance = ::GetModuleHandle(NULL);
        hCursor = reinterpret_cast<HCURSOR>(
            ::LoadImage(hInstance, pszName, IMAGE_ICON,
                        cxDesired, cyDesired, fuLoad));
    }
    return Attach(hCursor);
}

inline BOOL MCursor::LoadImageFromFile(HINSTANCE hInstance, LPCTSTR pszName,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, UINT fuLoad/* = 0*/)
{
    return LoadImage(hInstance, pszName, cxDesired, cyDesired,
        fuLoad | LR_LOADFROMFILE);
}

inline BOOL MCursor::CreateIconIndirect(PICONINFO pIconInfo)
{
    assert(pIconInfo);
    assert(pIconInfo->fIcon == FALSE);
    return Attach(reinterpret_cast<HCURSOR>(::CreateIconIndirect(pIconInfo)));
}

inline BOOL MCursor::DestroyCursor()
{
    BOOL bOK = ::DestroyCursor(m_hCursor);
    m_hCursor = NULL;
    return bOK;
}

inline BOOL MCursor::DrawIcon(HDC hDC, INT x, INT y)
{
    assert(m_hCursor);
    assert(hDC);
    return ::DrawIcon(hDC, x, y, m_hCursor);
}

inline BOOL MCursor::DrawIconEx(HDC hDC, INT x, INT y,
    INT cx, INT cy, UINT index/* = 0*/, HBRUSH hbr/* = NULL*/,
    UINT uDI_flags/* = DI_NORMAL*/)
{
    assert(m_hCursor);
    assert(hDC);
    return ::DrawIconEx(hDC, x, y, m_hCursor, cx, cy,
        index, hbr, uDI_flags);
}

inline BOOL MCursor::GetIconInfo(PICONINFO pIconInfo) const
{
    assert(m_hCursor);
    return ::GetIconInfo(m_hCursor, pIconInfo);
}

inline /*static*/ HCURSOR MCursor::CloneHandleDx(HCURSOR hCursor)
{
    return ::CopyCursorDx(hCursor);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCURSOR_HPP_
