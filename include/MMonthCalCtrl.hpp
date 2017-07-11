// MAnimateCtrl.hpp -- Win32API month calender control wrapper  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MMONTHCALCTRL_HPP_
#define MZC4_MMONTHCALCTRL_HPP_     2   /* Version 2 */

#if (_WIN32_IE >= 0x0300)
    class MMonthCalCtrl;
#endif

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

#if (_WIN32_IE >= 0x0300)
    class MMonthCalCtrl : public MWindowBase
    {
    public:
        MMonthCalCtrl();
        virtual LPCTSTR GetWndClassName() const;

        COLORREF GetColor(INT nColorType) const;
        COLORREF SetColor(INT nColorType, COLORREF clr);

        BOOL GetCurSel(LPSYSTEMTIME lpSysTime) const;
        BOOL SetCurSel(LPSYSTEMTIME lpSysTime);

        INT GetFirstDayOfWeek(BOOL* pbLocaleVal = NULL) const;
        INT SetFirstDayOfWeek(INT nDay, BOOL* pbLocaleVal = NULL);

        INT GetMaxSelCount() const;
        BOOL SetMaxSelCount(INT nMax);

        INT GetMonthDelta() const;
        INT SetMonthDelta(INT nDelta);

        DWORD GetRange(LPSYSTEMTIME lprgSysTimeArray) const;
        BOOL SetRange(DWORD dwFlags, LPSYSTEMTIME lprgSysTimeArray);

        BOOL GetSelRange(LPSYSTEMTIME lprgSysTimeArray) const;
        BOOL SetSelRange(LPSYSTEMTIME lprgSysTimeArray);

        BOOL GetToday(LPSYSTEMTIME lpSysTime) const;
        VOID SetToday(LPSYSTEMTIME lpSysTime);

        BOOL GetMinReqRect(LPRECT lpRectInfo) const;
        INT GetMaxTodayWidth() const;
        INT GetMonthRange(DWORD dwFlags, LPSYSTEMTIME lprgSysTimeArray) const;

        BOOL SetDayState(INT nMonths, LPMONTHDAYSTATE lpDayStateArray);
        DWORD HitTest(PMCHITTESTINFO pMCHitTest) const;

        #if (_WIN32_IE >= 0x0400)
            BOOL GetUnicodeFormat() const;
            BOOL SetUnicodeFormat(BOOL bUnicode = TRUE);
        #endif // (_WIN32_IE >= 0x0400)
    };
#endif  // (_WIN32_IE >= 0x0300)

////////////////////////////////////////////////////////////////////////////

#if (_WIN32_IE >= 0x0300)
    inline MMonthCalCtrl::MMonthCalCtrl()
    {
    }

    inline /*virtual*/ LPCTSTR MMonthCalCtrl::GetWndClassName() const
    {
        return MONTHCAL_CLASS;
    }

    inline COLORREF MMonthCalCtrl::GetColor(INT nColorType) const
    {
        return (COLORREF)SendMessageDx(MCM_GETCOLOR, (WPARAM)nColorType);
    }

    inline COLORREF MMonthCalCtrl::SetColor(INT nColorType, COLORREF clr)
    {
        return (COLORREF)SendMessageDx(MCM_SETCOLOR, (WPARAM)nColorType, (LPARAM)clr);
    }

    inline BOOL MMonthCalCtrl::GetCurSel(LPSYSTEMTIME lpSysTime) const
    {
        return (BOOL)SendMessageDx(MCM_GETCURSEL, 0, (LPARAM)lpSysTime);
    }

    inline BOOL MMonthCalCtrl::SetCurSel(LPSYSTEMTIME lpSysTime)
    {
        return (BOOL)SendMessageDx(MCM_SETCURSEL, 0, (LPARAM)lpSysTime);
    }

    inline INT MMonthCalCtrl::GetFirstDayOfWeek(
        BOOL* pbLocaleVal/* = NULL*/) const
    {
        DWORD dwRet = (DWORD)SendMessageDx(MCM_GETFIRSTDAYOFWEEK);
        if(pbLocaleVal != NULL)
            *pbLocaleVal = (BOOL) HIWORD(dwRet);
        return (INT)(SHORT) LOWORD(dwRet);
    }

    inline INT MMonthCalCtrl::SetFirstDayOfWeek(
        INT nDay, BOOL* pbLocaleVal/* = NULL*/)
    {
        DWORD dwRet = (DWORD)SendMessageDx(MCM_SETFIRSTDAYOFWEEK, 0, nDay);
        if(pbLocaleVal != NULL)
            *pbLocaleVal = (BOOL) HIWORD(dwRet);
        return (INT)(SHORT) LOWORD(dwRet);
    }

    inline INT MMonthCalCtrl::GetMaxSelCount() const
    {
        return (INT)SendMessageDx(MCM_GETMAXSELCOUNT);
    }

    inline BOOL MMonthCalCtrl::SetMaxSelCount(INT nMax)
    {
        return (BOOL)SendMessageDx(MCM_SETMAXSELCOUNT, (WPARAM)nMax);
    }

    inline INT MMonthCalCtrl::GetMonthDelta() const
    {
        return (INT)SendMessageDx(MCM_GETMONTHDELTA);
    }

    inline INT MMonthCalCtrl::SetMonthDelta(INT nDelta)
    {
        return (INT)SendMessageDx(MCM_SETMONTHDELTA, (WPARAM)nDelta);
    }

    inline DWORD MMonthCalCtrl::GetRange(
        LPSYSTEMTIME lprgSysTimeArray) const
    {
        return (DWORD)SendMessageDx(MCM_GETRANGE, 0, (LPARAM)lprgSysTimeArray);
    }

    inline BOOL MMonthCalCtrl::SetRange(
        DWORD dwFlags, LPSYSTEMTIME lprgSysTimeArray)
    {
        return (BOOL)SendMessageDx(MCM_SETRANGE, dwFlags, (LPARAM)lprgSysTimeArray);
    }

    inline BOOL MMonthCalCtrl::GetSelRange(
        LPSYSTEMTIME lprgSysTimeArray) const
    {
        return (BOOL)SendMessageDx(MCM_GETSELRANGE, 0, (LPARAM)lprgSysTimeArray);
    }

    inline BOOL MMonthCalCtrl::SetSelRange(LPSYSTEMTIME lprgSysTimeArray)
    {
        return (BOOL)SendMessageDx(MCM_SETSELRANGE, 0, (LPARAM)lprgSysTimeArray);
    }

    inline BOOL MMonthCalCtrl::GetToday(LPSYSTEMTIME lpSysTime) const
    {
        return (BOOL)SendMessageDx(MCM_GETTODAY, 0, (LPARAM)lpSysTime);
    }

    inline VOID MMonthCalCtrl::SetToday(LPSYSTEMTIME lpSysTime)
    {
        SendMessageDx(MCM_SETTODAY, 0, (LPARAM)lpSysTime);
    }

    inline BOOL MMonthCalCtrl::GetMinReqRect(LPRECT lpRectInfo) const
    {
        return (BOOL)SendMessageDx(MCM_GETMINREQRECT, 0, (LPARAM)lpRectInfo);
    }

    inline INT MMonthCalCtrl::GetMaxTodayWidth() const
    {
        return (INT)SendMessageDx(MCM_GETMAXTODAYWIDTH);
    }

    #if (_WIN32_IE >= 0x0400)
        inline BOOL MMonthCalCtrl::GetUnicodeFormat() const
        {
            return (BOOL)SendMessageDx(MCM_GETUNICODEFORMAT);
        }

        inline BOOL MMonthCalCtrl::SetUnicodeFormat(
            BOOL bUnicode/* = TRUE*/)
        {
            return (BOOL)SendMessageDx(MCM_SETUNICODEFORMAT, (WPARAM)bUnicode);
        }
    #endif  // (_WIN32_IE >= 0x0400)

    inline INT MMonthCalCtrl::GetMonthRange(
        DWORD dwFlags, LPSYSTEMTIME lprgSysTimeArray) const
    {
        return (INT)SendMessageDx(MCM_GETMONTHRANGE, dwFlags, (LPARAM)lprgSysTimeArray);
    }

    inline BOOL MMonthCalCtrl::SetDayState(
        INT nMonths, LPMONTHDAYSTATE lpDayStateArray)
    {
        return (BOOL)SendMessageDx(MCM_SETDAYSTATE, (WPARAM)nMonths, (LPARAM)lpDayStateArray);
    }

    inline DWORD MMonthCalCtrl::HitTest(PMCHITTESTINFO pMCHitTest) const
    {
        return (DWORD)SendMessageDx(MCM_HITTEST, 0, (LPARAM)pMCHitTest);
    }
#endif  // (_WIN32_IE >= 0x0300)

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MMONTHCALCTRL_HPP_
