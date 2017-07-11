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

    // before main
    MColorDialog(HWND hwndOwner, COLORREF clrInit = RGB(0, 0, 0),
                 DWORD dwCC_ = 0);

    // main
    BOOL ChooseColor();

    // after main
    COLORREF GetColor() const;

    VOID SetColor(COLORREF clr);

    static COLORREF *GetSavedCustomColors();
};

////////////////////////////////////////////////////////////////////////////

inline
MColorDialog::MColorDialog(HWND hwndOwner,
                           COLORREF clrInit/* = RGB(0, 0, 0)*/,
                           DWORD dwCC_/* = 0*/)
    : MCommonDialog(hwndOwner)
{
    m_bModal = TRUE;

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

inline VOID MColorDialog::SetColor(COLORREF clr)
{
    m_cc.rgbResult = clr;
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
