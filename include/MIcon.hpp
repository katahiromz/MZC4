// MIcon.hpp -- Win32API icon class                             -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MICON_HPP_
#define MZC4_MICON_HPP_         3   /* Version 3 */

class MIcon;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

class MIcon
{
public:
    MIcon();
    MIcon(HICON hIcon);
    MIcon(const MIcon& icon);
    MIcon& operator=(HICON hIcon);
    MIcon& operator=(const MIcon& icon);
    virtual ~MIcon();

    bool operator!() const;
    bool operator==(HICON hIcon) const;
    bool operator!=(HICON hIcon) const;
    HICON Handle() const;
    operator HICON() const;

    BOOL Attach(HICON hIcon);
    HICON Detach();

    BOOL CopyIcon(HICON hIcon);
    BOOL CreateIcon(HINSTANCE hInstance, INT width, INT height,
                    BYTE cPlanes, BYTE cBitsPixel,
                    const BYTE *pbANDbits, const BYTE *pbXORbits);
    BOOL CreateIcon(HINSTANCE hInstance, SIZE siz, BYTE cPlanes,
                    BYTE cBitsPixel, const BYTE *pbANDbits,
                    const BYTE *pbXORbits);
    BOOL CreateIconFromResource(PBYTE presbits, DWORD dwResSize,
                                BOOL fIcon = TRUE,
                                DWORD dwVer = 0x00030000);
    BOOL CreateIconFromResourceEx(PBYTE presbits, DWORD dwResSize,
                                  BOOL fIcon = TRUE,
                                  DWORD dwVer = 0x00030000,
                                  INT cxDesired = 0, INT cyDesired = 0,
                                  UINT uFlags = LR_DEFAULTCOLOR);
    BOOL LoadIcon(LPCTSTR pszResourceName, HINSTANCE hInstance = NULL);
    BOOL LoadIcon(UINT nIconID, HINSTANCE hInstance = NULL);
    BOOL LoadImage(HINSTANCE hInstance, LPCTSTR pszName,
                   INT cxDesired = 0, INT cyDesired = 0, UINT fuLoad = 0);
    BOOL LoadImageFromFile(HINSTANCE hInstance, LPCTSTR pszName,
                           INT cxDesired = 0, INT cyDesired = 0,
                           UINT fuLoad = 0);
    BOOL CreateIconIndirect(PICONINFO pIconInfo);
    BOOL ExtractIcon(LPCTSTR pszFile, UINT nIconIndex,
                     HINSTANCE hInst = NULL);
    UINT GetNumberOfIcons(LPCTSTR pszFile) const;
    BOOL ExtractIconEx(LPCTSTR pszFile, INT nIconIndex, UINT nIcons,
                       HICON *phIcons = NULL, HICON *phSmallIcons = NULL);
    BOOL ExtractAssociatedIcon(LPTSTR pszPath, LPWORD pnIndex,
                               HINSTANCE hInst = NULL);
    BOOL DestroyIcon();

    BOOL DrawIcon(HDC hDC, INT x, INT y);
    BOOL DrawIconEx(HDC hDC, INT x, INT y, INT cx, INT cy,
        UINT index = 0, HBRUSH hbr = NULL, UINT uDI_flags = DI_NORMAL);
    BOOL GetIconInfo(PICONINFO pIconInfo) const;

    static HICON CloneHandleDx(HICON hIcon);

protected:
    HICON m_hIcon;
};

////////////////////////////////////////////////////////////////////////////

inline MIcon::MIcon() : m_hIcon(NULL)
{
}

inline MIcon::MIcon(HICON hIcon) : m_hIcon(hIcon)
{
}

inline MIcon::MIcon(const MIcon& icon)
    : m_hIcon(CloneHandleDx(icon.m_hIcon))
{
    
}

inline /*virtual*/ MIcon::~MIcon()
{
    DestroyIcon();
}

inline bool MIcon::operator!() const
{
    return Handle() == NULL;
}

inline bool MIcon::operator==(HICON hIcon) const
{
    return Handle() == hIcon;
}

inline bool MIcon::operator!=(HICON hIcon) const
{
    return Handle() != hIcon;
}

inline HICON MIcon::Handle() const
{
    return (this ? m_hIcon : NULL);
}

inline MIcon::operator HICON() const
{
    return Handle();
}

inline MIcon& MIcon::operator=(HICON hIcon)
{
    if (Handle() != hIcon)
    {
        Attach(hIcon);
    }
    return *this;
}

inline MIcon& MIcon::operator=(const MIcon& icon)
{
    if (Handle() != icon.Handle())
    {
        HICON hIcon = CloneHandleDx(icon);
        Attach(hIcon);
    }
    return *this;
}

inline BOOL MIcon::Attach(HICON hIcon)
{
    DestroyIcon();
    m_hIcon = hIcon;
    return m_hIcon != NULL;
}

inline HICON MIcon::Detach()
{
    HICON hIcon = m_hIcon;
    m_hIcon = NULL;
    return hIcon;
}

inline BOOL MIcon::CopyIcon(HICON hIcon)
{
    return Attach(::CopyIcon(hIcon));
}

inline BOOL MIcon::CreateIcon(HINSTANCE hInstance,
    INT width, INT height, BYTE cPlanes,
    BYTE cBitsPixel, const BYTE *pbANDbits, const BYTE *pbXORbits)
{
    HICON hIcon = ::CreateIcon(hInstance, width, height,
                               cPlanes, cBitsPixel, pbANDbits, pbXORbits);
    if (hIcon == NULL && hInstance == NULL)
    {
        hInstance = ::GetModuleHandle(NULL);
        hIcon = ::CreateIcon(hInstance, width, height,
                             cPlanes, cBitsPixel, pbANDbits, pbXORbits);
    }
    return Attach(hIcon);
}

inline BOOL MIcon::CreateIcon(HINSTANCE hInstance, SIZE siz, BYTE cPlanes,
    BYTE cBitsPixel, const BYTE *pbANDbits, const BYTE *pbXORbits)
{
    return MIcon::CreateIcon(hInstance, siz.cx, siz.cy, cPlanes,
        cBitsPixel, pbANDbits, pbXORbits);
}

inline BOOL MIcon::CreateIconFromResource(PBYTE presbits, DWORD dwResSize,
    BOOL fIcon/* = TRUE*/, DWORD dwVer/* = 0x00030000*/)
{
    return Attach(::CreateIconFromResource(presbits, dwResSize, fIcon, dwVer));
}

inline BOOL MIcon::CreateIconFromResourceEx(PBYTE presbits,
    DWORD dwResSize, BOOL fIcon/* = TRUE*/, DWORD dwVer/* = 0x00030000*/,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, UINT uFlags/* = LR_DEFAULTCOLOR*/)
{
    return Attach(::CreateIconFromResourceEx(presbits, dwResSize, fIcon, dwVer,
                                             cxDesired, cyDesired, uFlags));
}

inline BOOL MIcon::LoadIcon(
    LPCTSTR pszResourceName, HINSTANCE hInstance/* = NULL*/)
{
    HICON hIcon = ::LoadIcon(hInstance, pszResourceName);
    if (hIcon == NULL && hInstance == NULL)
    {
        hInstance = ::GetModuleHandle(NULL);
        hIcon = ::LoadIcon(hInstance, pszResourceName);
    }
    return Attach(hIcon);
}

inline BOOL MIcon::LoadIcon(UINT nIconID, HINSTANCE hInstance/* = NULL*/)
{
    return LoadIcon(MAKEINTRESOURCE(nIconID), hInstance);
}

inline BOOL MIcon::LoadImage(HINSTANCE hInstance, LPCTSTR pszName,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, UINT fuLoad/* = 0*/)
{
    HICON hIcon = reinterpret_cast<HICON>(
        ::LoadImage(hInstance, pszName, IMAGE_ICON, cxDesired, cyDesired,
                    fuLoad));
    if (hIcon == NULL && hInstance == NULL)
    {
        hInstance = ::GetModuleHandle(NULL);
        hIcon = reinterpret_cast<HICON>(
            ::LoadImage(hInstance, pszName, IMAGE_ICON, cxDesired, cyDesired,
                        fuLoad));
    }
    return Attach(hIcon);
}

inline BOOL MIcon::LoadImageFromFile(HINSTANCE hInstance, LPCTSTR pszName,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, UINT fuLoad/* = 0*/)
{
    fuLoad |= LR_LOADFROMFILE;
    return LoadImage(hInstance, pszName, cxDesired, cyDesired, fuLoad);
}

inline BOOL MIcon::CreateIconIndirect(PICONINFO pIconInfo)
{
    return Attach(::CreateIconIndirect(pIconInfo));
}

inline BOOL MIcon::DestroyIcon()
{
    if (m_hIcon)
    {
        BOOL bOK = ::DestroyIcon(m_hIcon);
        m_hIcon = NULL;
        return bOK;
    }
    return FALSE;
}

inline BOOL MIcon::DrawIcon(HDC hDC, INT x, INT y)
{
    assert(Handle());
    assert(hDC);
    return ::DrawIcon(hDC, x, y, Handle());
}

inline BOOL MIcon::DrawIconEx(HDC hDC, INT x, INT y,
    INT cx, INT cy, UINT index/* = 0*/, HBRUSH hbr/* = NULL*/,
    UINT uDI_flags/* = DI_NORMAL*/)
{
    assert(Handle());
    assert(hDC);
    return ::DrawIconEx(hDC, x, y, Handle(),
        cx, cy, index, hbr, uDI_flags);
}

inline BOOL MIcon::GetIconInfo(PICONINFO pIconInfo) const
{
    assert(Handle());
    assert(pIconInfo);
    return ::GetIconInfo(Handle(), pIconInfo);
}

inline /*static*/ HICON MIcon::CloneHandleDx(HICON hIcon)
{
    return ::CopyIcon(hIcon);
}

inline BOOL MIcon::ExtractIcon(
    LPCTSTR pszFile, UINT nIconIndex, HINSTANCE hInst/* = NULL*/)
{
    HICON hIcon = ::ExtractIcon(hInst, pszFile, nIconIndex);
    if (hIcon == NULL && hInst == NULL)
    {
        hInst = ::GetModuleHandle(NULL);
        hIcon = ::ExtractIcon(hInst, pszFile, nIconIndex);
    }
    return Attach(hIcon);
}

inline UINT MIcon::GetNumberOfIcons(LPCTSTR pszFile) const
{
    return ::ExtractIconEx(pszFile, -1, NULL, NULL, 0);
}

inline BOOL MIcon::ExtractIconEx(LPCTSTR pszFile, INT nIconIndex,
    UINT nIcons, HICON *phIcons/* = NULL*/, HICON *phSmallIcons/* = NULL*/)
{
    return ::ExtractIconEx(pszFile, nIconIndex, phIcons, phSmallIcons, nIcons);
}

inline BOOL MIcon::ExtractAssociatedIcon(
    LPTSTR pszPath, LPWORD pnIndex, HINSTANCE hInst/* = NULL*/)
{
    HICON hIcon = ::ExtractAssociatedIcon(hInst, pszPath, pnIndex);
    if (hIcon == NULL && hInst == NULL)
    {
        hInst = ::GetModuleHandle(NULL);
        hIcon = ::ExtractAssociatedIcon(hInst, pszPath, pnIndex);
    }
    return Attach(hIcon);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MICON_HPP_
