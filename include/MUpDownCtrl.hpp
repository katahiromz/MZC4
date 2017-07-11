// MUpDownCtrl.hpp -- Win32API up-down control wrapper          -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MUPDOWNCTRL_HPP_
#define MZC4_MUPDOWNCTRL_HPP_   2       /* Version 2 */

class MUpDownCtrl;

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MUpDownCtrl : public MWindowBase
{
public:
    MUpDownCtrl();
    virtual LPCTSTR GetWndClassName() const;

    UINT GetAccel(INT nAccel, UDACCEL* pAccel) const;
    BOOL SetAccel(INT nAccel, UDACCEL* pAccel);

    UINT GetBase() const;
    INT  SetBase(INT nBase);

    HWND GetBuddy() const;
    HWND SetBuddy(HWND hwndBuddy);

    INT GetPos() const;
    INT SetPos(INT nPos);

    DWORD GetRange() const;
    VOID GetRange(INT &lower, INT& upper) const;
    VOID SetRange(INT nLower, INT nUpper);

#if (_WIN32_IE >= 0x0500)
    INT GetPos32(LPBOOL pError = NULL) const;
    INT SetPos32(INT nPos);
#endif  // (_WIN32_IE >= 0x0500)

#if (_WIN32_IE >= 0x0400)
    VOID GetRange32(INT& lower, INT& upper) const;
    VOID SetRange32(INT nLower, INT nUpper);
#endif  // (_WIN32_IE >= 0x0400)
};

////////////////////////////////////////////////////////////////////////////

inline MUpDownCtrl::MUpDownCtrl()
{
}

inline /*virtual*/ LPCTSTR MUpDownCtrl::GetWndClassName() const
{
    return UPDOWN_CLASS;
}

inline BOOL MUpDownCtrl::SetAccel(INT nAccel, UDACCEL* pAccel)
{
    return (BOOL)SendMessageDx(UDM_SETACCEL, (WPARAM)nAccel, (LPARAM)pAccel);
}

inline UINT MUpDownCtrl::GetAccel(INT nAccel, UDACCEL* pAccel) const
{
    return (UINT)SendMessageDx(UDM_GETACCEL, (WPARAM)nAccel, (LPARAM)pAccel);
}

inline INT MUpDownCtrl::SetBase(INT nBase)
{
    return (INT)SendMessageDx(UDM_SETBASE, (WPARAM)nBase);
}

inline UINT MUpDownCtrl::GetBase() const
{
    return (UINT)SendMessageDx(UDM_GETBASE);
}

inline HWND MUpDownCtrl::SetBuddy(HWND hwndBuddy)
{
    return (HWND)SendMessageDx(UDM_SETBUDDY, (WPARAM)hwndBuddy);
}

inline HWND MUpDownCtrl::GetBuddy() const
{
    return (HWND)SendMessageDx(UDM_GETBUDDY);
}

inline INT MUpDownCtrl::SetPos(INT nPos)
{
    return (INT)SendMessageDx(UDM_SETPOS, 0, nPos);
}

inline INT MUpDownCtrl::GetPos() const
{
    return (INT)SendMessageDx(UDM_GETPOS);
}

inline VOID MUpDownCtrl::SetRange(INT nLower, INT nUpper)
{
    SendMessageDx(UDM_SETRANGE, 0, MAKELPARAM(nLower, nUpper));
}

inline DWORD MUpDownCtrl::GetRange() const
{
    return (DWORD)SendMessageDx(UDM_GETRANGE);
}

inline VOID MUpDownCtrl::GetRange(INT &lower, INT& upper) const
{
    DWORD dw = GetRange();
    lower = (INT)(SHORT) LOWORD(dw);
    upper = (INT)(SHORT) HIWORD(dw);
}

#if (_WIN32_IE >= 0x0500)
    inline INT MUpDownCtrl::GetPos32(LPBOOL pError/* = NULL*/) const
    {
        return (INT)SendMessageDx(UDM_GETPOS32, 0, (LPARAM)pError);
    }

    inline INT MUpDownCtrl::SetPos32(INT nPos)
    {
        return (INT)SendMessageDx(UDM_SETPOS32, 0, nPos);
    }
#endif  // (_WIN32_IE >= 0x0500)

#if (_WIN32_IE >= 0x0400)
    inline VOID MUpDownCtrl::GetRange32(INT& lower, INT& upper) const
    {
        SendMessageDx(UDM_GETRANGE32, (WPARAM)&lower, (LPARAM)&upper);
    }

    inline VOID MUpDownCtrl::SetRange32(INT nLower, INT nUpper)
    {
        SendMessageDx(UDM_SETRANGE32, (WPARAM)nLower, (LPARAM)nUpper);
    }
#endif  // (_WIN32_IE >= 0x0400)

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MUPDOWNCTRL_HPP_
