// MAccel.hpp -- Win32API IP address control wrapper            -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MIPADDRESSCTRL_HPP_
#define MZC4_MIPADDRESSCTRL_HPP_        2       /* Version 2 */

#if (_WIN32_IE >= 0x0400)
    class MIPAddressCtrl;
#endif

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

#if (_WIN32_IE >= 0x0400)
    class MIPAddressCtrl : public MWindowBase
    {
    public:
        MIPAddressCtrl();
        virtual LPCTSTR GetWndClassName() const;

        BOOL IsBlank() const;

        INT GetAddress(LPDWORD lpdwAddress) const;
        VOID SetAddress(DWORD dwAddress);
        VOID ClearAddress();

        VOID SetRange(INT nField, WORD wRange);
        VOID SetRange(INT nField, BYTE nMin, BYTE nMax);
        VOID SetFocus(INT nField);
    };
#endif  // (_WIN32_IE >= 0x0400)

////////////////////////////////////////////////////////////////////////////

#if (_WIN32_IE >= 0x0400)
    inline MIPAddressCtrl::MIPAddressCtrl()
    {
    }

    inline /*virtual*/ LPCTSTR MIPAddressCtrl::GetWndClassName() const
    {
        return WC_IPADDRESS;
    }

    inline BOOL MIPAddressCtrl::IsBlank() const
    {
        return (BOOL)SendMessageDx(IPM_ISBLANK);
    }

    inline INT MIPAddressCtrl::GetAddress(LPDWORD lpdwAddress) const
    {
        return (INT)SendMessageDx(IPM_GETADDRESS, 0, (LPARAM)lpdwAddress);
    }

    inline VOID MIPAddressCtrl::SetAddress(DWORD dwAddress)
    {
        SendMessageDx(IPM_SETADDRESS, 0, (LPARAM)dwAddress);
    }

    inline VOID MIPAddressCtrl::ClearAddress()
    {
        SendMessageDx(IPM_CLEARADDRESS);
    }

    inline VOID MIPAddressCtrl::SetRange(INT nField, WORD wRange)
    {
        SendMessageDx(IPM_SETRANGE, (WPARAM)nField, (LPARAM)wRange);
    }

    inline VOID MIPAddressCtrl::SetRange(INT nField, BYTE nMin, BYTE nMax)
    {
        SendMessageDx(IPM_SETRANGE, (WPARAM)nField, MAKEIPRANGE(nMin, nMax));
    }

    inline VOID MIPAddressCtrl::SetFocus(INT nField)
    {
        SendMessageDx(IPM_SETFOCUS, (WPARAM)nField);
    }
#endif  // (_WIN32_IE >= 0x0400)

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MIPADDRESSCTRL_HPP_
