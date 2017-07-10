// MAccel.hpp -- Win32API button wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MBUTTON_HPP_
#define MZC4_MBUTTON_HPP_       2   /* Version 2 */

class MButton;

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MButton : public MWindowBase
{
public:
    MButton();

    virtual LPCTSTR GetWndClassName() const;

    UINT GetState() const;
    VOID SetState(BOOL bHighlight);

    INT  GetCheck() const;
    VOID SetCheck(INT nBST_);

    UINT GetButtonStyle() const;
    VOID SetButtonStyle(UINT nBS_flags, BOOL bRedraw = TRUE);

    HICON GetIcon() const;
    HICON SetIcon(HICON hIcon);

    HBITMAP GetBitmap() const;
    HBITMAP SetBitmap(HBITMAP hBitmap);

    HCURSOR GetCursor();
    HCURSOR SetCursor(HCURSOR hCursor);
};
typedef MButton MRadioButton;
typedef MButton MGroupBox;
typedef MButton MCheckButton;
typedef MButton MPushButton;

////////////////////////////////////////////////////////////////////////////

inline MButton::MButton()
{
}

inline /*virtual*/ LPCTSTR MButton::GetWndClassName() const
{
    return TEXT("BUTTON");
}

inline UINT MButton::GetState() const
{
    return (UINT)SendMessageDx(BM_GETSTATE);
}

inline VOID MButton::SetState(BOOL bHighlight)
{
    SendMessageDx(BM_SETSTATE, (WPARAM)bHighlight);
}

inline INT MButton::GetCheck() const
{
    return (INT)SendMessageDx(BM_GETCHECK);
}

inline VOID MButton::SetCheck(INT nBST_)
{
    SendMessageDx(BM_SETCHECK, (WPARAM)nBST_);
}

inline UINT MButton::GetButtonStyle() const
{
    return (UINT)(GetStyleDx() & 0xFFFF);
}

inline VOID MButton::SetButtonStyle(UINT nBS_flags, BOOL bRedraw/* = TRUE*/)
{
    SendMessageDx(BM_SETSTYLE, nBS_flags, bRedraw);
}

inline HICON MButton::SetIcon(HICON hIcon)
{
    return (HICON)SendMessageDx(BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
}

inline HICON MButton::GetIcon() const
{
    return (HICON)SendMessageDx(BM_GETIMAGE, IMAGE_ICON);
}

inline HBITMAP MButton::SetBitmap(HBITMAP hBitmap)
{
    return (HBITMAP)SendMessageDx(BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
}

inline HBITMAP MButton::GetBitmap() const
{
    return (HBITMAP)SendMessageDx(BM_GETIMAGE, IMAGE_BITMAP);
}

inline HCURSOR MButton::SetCursor(HCURSOR hCursor)
{
    return (HCURSOR)SendMessageDx(BM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);
}

inline HCURSOR MButton::GetCursor()
{
    return (HCURSOR)SendMessageDx(BM_GETIMAGE, IMAGE_CURSOR);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MBUTTON_HPP_
