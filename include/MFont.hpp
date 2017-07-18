// MFont.hpp -- Win32API font object wrapper                    -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFONT_HPP_
#define MZC4_MFONT_HPP_         4   /* Version 4 */

class MFont;

////////////////////////////////////////////////////////////////////////////

// MString
#ifndef MString
    #include <string>       // std::string and std::wstring
    typedef std::string     MStringA;
    typedef std::wstring    MStringW;
    #ifdef UNICODE
        #define MString     MStringW
    #else
        #define MString     MStringA
    #endif
#endif

////////////////////////////////////////////////////////////////////////////

#include "MGdiObject.hpp"
#include <vector>

class MFont : public MGdiObject
{
public:
    MFont();
    MFont(HFONT hFont);
    MFont(const MFont& font);

    operator HFONT() const;
    HFONT Handle() const;

    INT GetLogFont(LOGFONT *lplf) const;

    MFont& operator=(HFONT hFont);
    MFont& operator=(const MFont& font);

    BOOL Attach(HFONT hFont);
    HFONT Detach(VOID);

    BOOL CreateFont(
        LPCTSTR pszFace,
        INT nHeight,
        INT nWidth = 0,
        INT nEscapement = 0,
        INT nOrientation = 0,
        INT fnWeight = FW_NORMAL,
        DWORD fdwItalic = FALSE,
        DWORD fdwUnderline = FALSE,
        DWORD fdwStrikeOut = FALSE,
        DWORD fdwCharSet = DEFAULT_CHARSET,
        DWORD fdwOutputPrecision = OUT_DEFAULT_PRECIS,
        DWORD fdwClipPrecision = CLIP_DEFAULT_PRECIS,
        DWORD fdwQuality = ANTIALIASED_QUALITY,
        DWORD fdwPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE);
    BOOL CreateFontIndirect(CONST LOGFONT *lplf);
    BOOL CreateAnsiFixedFont();
    BOOL CreateAnsiVarFont();
    BOOL CreateDeviceDefaultFont();
    BOOL CreateDefaultGuiFont();
    BOOL CreateOemFixedFont();
    BOOL CreateSystemFont();
    BOOL CreateSystemFixedFont();

    static HFONT CloneHandleDx(HFONT hFont);

    enum
    {
        fontset_no_vertical = 1,
        fontset_vertical_only = 2,
        fontset_truetype_only = 4,
        fontset_raster_only = 8,
        fontset_fixed_pitch_only = 16
    };
    static BOOL GetFontList(HDC hdc, std::vector<MString>& vec, LPCTSTR pszName = NULL,
                            DWORD dwFlags = fontset_no_vertical);
    static BOOL GetFontList(HDC hdc, std::vector<MString>& vec, LPLOGFONT plf,
                            DWORD dwFlags = fontset_no_vertical);
};

////////////////////////////////////////////////////////////////////////////

struct MEnumFontData
{
    std::vector<MString> m_vec;
    DWORD m_dwFlags;
};

INT CALLBACK EnumFontFamProcDx(
    ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm,
    INT nFontType, LPARAM lParam);

INT CALLBACK EnumFontFamExProcDx(
    ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme,
    INT nFontType, LPARAM lParam);

inline /*static*/ BOOL
MFont::GetFontList(HDC hdc, std::vector<MString>& vec,
                   LPCTSTR pszName/* = NULL*/,
                   DWORD dwFlags/* = fontset_no_vertical*/)
{
    MEnumFontData data;
    data.m_dwFlags = dwFlags;

    BOOL bCreateDC = FALSE;
    if (hdc == NULL)
    {
        hdc = CreateCompatibleDC(NULL);
        bCreateDC = TRUE;
    }

    BOOL bOK = ::EnumFontFamilies(hdc, pszName, (FONTENUMPROC)EnumFontFamProcDx, (LPARAM)&data);

    if (bCreateDC)
        ::DeleteDC(hdc);

    if (bOK)
        vec.assign(data.m_vec.begin(), data.m_vec.end());
    else
        vec.clear();

    return bOK;
}

inline /*static*/ BOOL
MFont::GetFontList(HDC hdc, std::vector<MString>& vec, LPLOGFONT plf,
                   DWORD dwFlags/* = fontset_no_vertical*/)
{
    MEnumFontData data;
    data.m_dwFlags = dwFlags;

    BOOL bCreateDC = FALSE;
    if (hdc == NULL)
    {
        hdc = CreateCompatibleDC(NULL);
        bCreateDC = TRUE;
    }

    BOOL bOK = ::EnumFontFamiliesEx(hdc, plf, (FONTENUMPROC)EnumFontFamExProcDx, (LPARAM)&data, 0);

    if (bCreateDC)
        ::DeleteDC(hdc);

    if (bOK)
        vec.assign(data.m_vec.begin(), data.m_vec.end());
    else
        vec.clear();

    return bOK;
}

////////////////////////////////////////////////////////////////////////////

inline /*static*/ HFONT MFont::CloneHandleDx(HFONT hFont)
{
    if (hFont == NULL)
        return NULL;
    LOGFONT lf;
    ::GetObject(hFont, sizeof(LOGFONT), &lf);
    return ::CreateFontIndirect(&lf);
}

inline MFont::MFont()
{
}

inline MFont::MFont(HFONT hFont) : MGdiObject(hFont)
{
}

inline MFont::MFont(const MFont& font) : MGdiObject(CloneHandleDx(font))
{
}

inline HFONT MFont::Handle() const
{
    return (this ? (HFONT)m_hGdiObj : NULL);
}

inline MFont::operator HFONT() const
{
    return Handle();
}

inline INT MFont::GetLogFont(LOGFONT *lplf) const
{
    assert(Handle());
    return ::GetObject(Handle(), sizeof(LOGFONT), lplf);
}

inline MFont& MFont::operator=(HFONT hFont)
{
    assert(hFont == NULL || ::GetObjectType(hFont) == OBJ_FONT);
    if (Handle() != hFont)
    {
        Attach(hFont);
    }
    return *this;
}

inline MFont& MFont::operator=(const MFont& font)
{
    if (Handle() != font.Handle())
    {
        HFONT hFont = CloneHandleDx(font);
        Attach(hFont);
    }
    return *this;
}

inline BOOL MFont::Attach(HFONT hFont)
{
    assert(::GetObjectType(hFont) == OBJ_FONT);
    return MGdiObject::Attach(hFont);
}

inline HFONT MFont::Detach(VOID)
{
    return reinterpret_cast<HFONT>(MGdiObject::Detach());
}

inline BOOL MFont::CreateFontIndirect(CONST LOGFONT *lplf)
{
    return Attach(::CreateFontIndirect(lplf));
}

inline BOOL MFont::CreateAnsiFixedFont()
{
    return Attach((HFONT)::GetStockObject(ANSI_FIXED_FONT));
}

inline BOOL MFont::CreateAnsiVarFont()
{
    return Attach((HFONT)::GetStockObject(ANSI_VAR_FONT));
}

inline BOOL MFont::CreateDeviceDefaultFont()
{
    assert(Handle() == NULL);
    return Attach((HFONT)::GetStockObject(DEVICE_DEFAULT_FONT));
}

inline BOOL MFont::CreateDefaultGuiFont()
{
    return Attach((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
}

inline BOOL MFont::CreateOemFixedFont()
{
    return Attach((HFONT)::GetStockObject(OEM_FIXED_FONT));
}

inline BOOL MFont::CreateSystemFont()
{
    return Attach((HFONT)::GetStockObject(SYSTEM_FONT));
}

inline BOOL MFont::CreateSystemFixedFont()
{
    return Attach((HFONT)::GetStockObject(SYSTEM_FIXED_FONT));
}

inline BOOL MFont::CreateFont(LPCTSTR pszFace, INT nHeight,
    INT nWidth/* = 0*/, INT nEscapement/* = 0*/, INT nOrientation/* = 0*/,
    INT fnWeight/* = FW_NORMAL*/, DWORD fdwItalic/* = FALSE*/,
    DWORD fdwUnderline/* = FALSE*/, DWORD fdwStrikeOut/* = FALSE*/,
    DWORD fdwCharSet/* = DEFAULT_CHARSET*/,
    DWORD fdwOutputPrecision/* = OUT_DEFAULT_PRECIS*/,
    DWORD fdwClipPrecision/* = CLIP_DEFAULT_PRECIS*/,
    DWORD fdwQuality/* = ANTIALIASED_QUALITY*/,
    DWORD fdwPitchAndFamily/* = DEFAULT_PITCH | FF_DONTCARE*/)
{
    return Attach(::CreateFont(nHeight, nWidth, nEscapement,
        nOrientation, fnWeight, fdwItalic, fdwUnderline, fdwStrikeOut,
        fdwCharSet, fdwOutputPrecision, fdwClipPrecision,
        fdwQuality, fdwPitchAndFamily, pszFace));
}

////////////////////////////////////////////////////////////////////////////

inline INT CALLBACK EnumFontFamProcDx(
    ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm,
    INT nFontType, LPARAM lParam)
{
    MEnumFontData *pData = reinterpret_cast<MEnumFontData *>(lParam);
    assert(pData);

    BOOL bAccept = TRUE;

    if (pData->m_dwFlags & MFont::fontset_truetype_only)
    {
        if (!(nFontType & TRUETYPE_FONTTYPE))
            bAccept = FALSE;
    }

    if (pData->m_dwFlags & MFont::fontset_raster_only)
    {
        if (!(nFontType & RASTER_FONTTYPE))
            bAccept = FALSE;
    }

    if (pData->m_dwFlags & MFont::fontset_fixed_pitch_only)
    {
        if (lpelf->elfLogFont.lfPitchAndFamily != FIXED_PITCH)
            bAccept = FALSE;
    }

    if (pData->m_dwFlags & MFont::fontset_no_vertical)
    {
        if (lpelf->elfLogFont.lfFaceName[0] == TEXT('@'))
            bAccept = FALSE;
    }

    if (pData->m_dwFlags & MFont::fontset_vertical_only)
    {
        if (lpelf->elfLogFont.lfFaceName[0] != TEXT('@'))
            bAccept = FALSE;
    }

    if (bAccept)
        pData->m_vec.push_back(lpelf->elfLogFont.lfFaceName);

    return TRUE;
}

inline INT CALLBACK
EnumFontFamExProcDx(
    ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme,
    INT nFontType, LPARAM lParam)
{
    MEnumFontData *pData = reinterpret_cast<MEnumFontData *>(lParam);
    assert(pData);

    BOOL bAccept = TRUE;

    if (pData->m_dwFlags & MFont::fontset_truetype_only)
    {
        if (!(nFontType & TRUETYPE_FONTTYPE))
            bAccept = FALSE;
    }

    if (pData->m_dwFlags & MFont::fontset_raster_only)
    {
        if (!(nFontType & RASTER_FONTTYPE))
            bAccept = FALSE;
    }

    if (pData->m_dwFlags & MFont::fontset_fixed_pitch_only)
    {
        if (lpelfe->elfLogFont.lfPitchAndFamily != FIXED_PITCH)
            bAccept = FALSE;
    }

    if (pData->m_dwFlags & MFont::fontset_no_vertical)
    {
        if (lpelfe->elfLogFont.lfFaceName[0] == TEXT('@'))
            bAccept = FALSE;
    }

    if (pData->m_dwFlags & MFont::fontset_vertical_only)
    {
        if (lpelfe->elfLogFont.lfFaceName[0] != TEXT('@'))
            bAccept = FALSE;
    }

    if (bAccept)
        pData->m_vec.push_back(lpelfe->elfLogFont.lfFaceName);

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFONT_HPP_
