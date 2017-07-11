// MFontDialog.hpp -- MZC4 font dialog wrapper                  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFONTDIALOG_HPP_
#define MZC4_MFONTDIALOG_HPP_       2       /* Version 2 */

class MFontDialog;

////////////////////////////////////////////////////////////////////////////

#include "MCommonDialog.hpp"

class MFontDialog : public MCommonDialog
{
public:
    CHOOSEFONT  m_cf;
    LOGFONT     m_lf;

    // before main
    MFontDialog(HWND hwndOwner, LPLOGFONT plfInitial = NULL,
                DWORD dwCF_ = CF_EFFECTS | CF_SCREENFONTS,
                HDC hdcPrinter = NULL);

    // main
    BOOL ChooseFont();

    // after main
    COLORREF GetColor() const;
    VOID GetCurrentFont(LPLOGFONT plf);
    MString GetFaceName() const;
    INT GetSize() const;
    MString GetStyleName() const;
    INT GetWeight() const;
    BOOL IsBold() const;
    BOOL IsItalic() const;
    BOOL IsStrikeOut() const;
    BOOL IsUnderline() const;
};

////////////////////////////////////////////////////////////////////////////

inline
MFontDialog::MFontDialog(HWND hwndOwner,
                         LPLOGFONT plfInitial/* = NULL*/,
                         DWORD dwCF_/* = CF_EFFECTS | CF_SCREENFONTS*/,
                         HDC hdcPrinter/* = NULL*/)
    : MCommonDialog(hwndOwner)
{
    m_bModal = TRUE;

    ZeroMemory(&m_cf, sizeof(m_cf));
    m_cf.lStructSize = sizeof(m_cf);
    m_cf.hwndOwner = hwndOwner;
    m_cf.hDC = hdcPrinter;
    m_cf.lpLogFont = &m_lf;
    m_cf.Flags = dwCF_;
    if (hdcPrinter)
        m_cf.Flags |= CF_PRINTERFONTS;

    if (plfInitial)
    {
        CopyMemory(&m_lf, plfInitial, sizeof(LOGFONT));
        m_cf.Flags |= CF_INITTOLOGFONTSTRUCT;
    }
    else
    {
        ZeroMemory(&m_lf, sizeof(m_lf));
        m_lf.lfCharSet = DEFAULT_CHARSET;
    }
}

inline BOOL MFontDialog::ChooseFont()
{
    return ::ChooseFont(&m_cf);
}

inline COLORREF MFontDialog::GetColor() const
{
    assert(m_cf.Flags & CF_EFFECTS);
    return (COLORREF)m_cf.rgbColors;
}

inline VOID MFontDialog::GetCurrentFont(LPLOGFONT plf)
{
    CopyMemory(plf, &m_lf, sizeof(LOGFONT));
}

inline MString MFontDialog::GetFaceName() const
{
    MString ret(m_lf.lfFaceName);
    return ret;
}

inline INT MFontDialog::GetSize() const
{
    return m_cf.iPointSize;
}

inline MString MFontDialog::GetStyleName() const
{
    MString ret;
    if ((m_cf.Flags & CF_USESTYLE) && m_cf.lpszStyle)
        ret = m_cf.lpszStyle;
    return ret;
}

inline INT MFontDialog::GetWeight() const
{
    return m_lf.lfWeight;
}

inline BOOL MFontDialog::IsBold() const
{
    return GetWeight() >= FW_BOLD;
}

inline BOOL MFontDialog::IsItalic() const
{
    return m_lf.lfItalic;
}

inline BOOL MFontDialog::IsStrikeOut() const
{
    return m_lf.lfStrikeOut;
}

inline BOOL MFontDialog::IsUnderline() const
{
    return m_lf.lfUnderline;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFONTDIALOG_HPP_
