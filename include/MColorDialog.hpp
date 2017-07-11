// MColorDialog.hpp -- MZC4 color dialog wrapper                -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MCOLORDIALOG_HPP_
#define MZC4_MCOLORDIALOG_HPP_      2       /* Version 2 */

class MColorDialog;

////////////////////////////////////////////////////////////////////////////

#include "MCommonDialog.hpp"

class MColorDialog : public MCommonDialog
{
public:
    CHOOSECOLOR m_cc;

    MColorDialog(HWND hwndOwner, COLORREF clrInit = RGB(0, 0, 0),
                 DWORD dwCC_ = 0);

    BOOL ChooseColor();
    COLORREF GetColor() const;
    static COLORREF *GetSavedCustomColors();
    VOID SetCurrentColor(COLORREF clr);
    virtual BOOL OnColorOK();
};

////////////////////////////////////////////////////////////////////////////

inline
MColorDialog::MColorDialog(HWND hwndOwner,
                           COLORREF clrInit/* = RGB(0, 0, 0)*/,
                           DWORD dwCC_/* = 0*/)
    : MCommonDialog(hwndOwner)
{
    ZeroMemory(&m_cc, sizeof(m_cc));
    m_cc.lStructSize = sizeof(CHOOSECOLOR);
    m_cc.hwndOwner = hwndOwner;
    m_cc.rgbResult = clrInit;
    m_cc.lpCustColors = GetSavedCustomColors();
    m_cc.Flags = dwCC_ | CC_RGBINIT;
}

inline /*virtual*/ BOOL MColorDialog::ChooseColor()
{
    return ::ChooseColor(&m_cc);
}

inline COLORREF MColorDialog::GetColor() const
{
    return m_cc.rgbResult;
}

inline VOID MColorDialog::SetCurrentColor(COLORREF clr)
{
    m_cc.rgbResult = clr;
}

inline /*virtual*/ BOOL MColorDialog::OnColorOK()
{
    return TRUE;
}

inline /*static*/ COLORREF *MColorDialog::GetSavedCustomColors()
{
    static COLORREF s_colors[16] =
    {
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF),
        RGB(0xFF, 0xFF, 0xFF)
    };
    return s_colors;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCOLORDIALOG_HPP_
