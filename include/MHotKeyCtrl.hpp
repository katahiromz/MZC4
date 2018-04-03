// MHotKeyCtrl.hpp -- Win32API hot-key control wrapper               -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MHOTKEYCTRL_HPP_
#define MZC4_MHOTKEYCTRL_HPP_    2       /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MHotKeyCtrl : public MWindowBase
{
public:
    MHotKeyCtrl();
    virtual LPCTSTR GetWndClassNameDx() const;

    DWORD GetHotKey() const;
    VOID GetHotKey(WORD &wVK_, WORD &wHOTKEYF_flags) const;
    VOID SetHotKey(WORD wVK_, WORD wHOTKEYF_flags);

    VOID SetRules(WORD wHKCOMB_invalid, WORD wHOTKEYF_flags);
};

////////////////////////////////////////////////////////////////////////////

inline MHotKeyCtrl::MHotKeyCtrl()
{
}

inline /*virtual*/ LPCTSTR MHotKeyCtrl::GetWndClassNameDx() const
{
    return HOTKEY_CLASS;
}

inline DWORD MHotKeyCtrl::GetHotKey() const
{
    return (DWORD)SendMessageDx(HKM_GETHOTKEY);
}

inline VOID
MHotKeyCtrl::GetHotKey(WORD &wVK_, WORD &wHOTKEYF_flags) const
{
    DWORD dw = (DWORD)SendMessageDx(HKM_GETHOTKEY);
    wVK_ = LOBYTE(LOWORD(dw));
    wHOTKEYF_flags = HIBYTE(LOWORD(dw));
}

inline VOID MHotKeyCtrl::SetHotKey(WORD wVK_, WORD wHOTKEYF_flags)
{
    SendMessageDx(HKM_SETHOTKEY, MAKEWPARAM(wVK_, wHOTKEYF_flags));
}

inline VOID MHotKeyCtrl::SetRules(WORD wHKCOMB_invalid, WORD wHOTKEYF_flags)
{
    SendMessageDx(HKM_SETRULES, wHKCOMB_invalid, wHOTKEYF_flags);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MHOTKEYCTRL_HPP_
