// MDateTimePick.hpp -- Win32API date time picker wrapper       -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MDATETIMEPICK_HPP_
#define MZC4_MDATETIMEPICK_HPP_     2   /* Version 2 */

#if (_WIN32_IE >= 0x0300)
    class MDateTimePick;
#endif

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

#if (_WIN32_IE >= 0x0300)
    class MDateTimePick : public MWindowBase
    {
    public:
        MDateTimePick();
        virtual LPCTSTR GetWndClassNameDx() const;

        BOOL SetFormat(LPCTSTR lpszFormat);

        COLORREF GetMonthCalColor(INT nColorType) const;
        COLORREF SetMonthCalColor(INT nColorType, COLORREF clr);

        DWORD GetRange(LPSYSTEMTIME lpSysTimeArray) const;
        BOOL  SetRange(DWORD dwFlags, LPSYSTEMTIME lpSysTimeArray);

        DWORD GetSystemTime(LPSYSTEMTIME lpSysTime) const;
        BOOL  SetSystemTime(DWORD dwFlags, LPSYSTEMTIME lpSysTime);

        HWND GetMonthCal() const;

        #if (_WIN32_IE >= 0x0400)
            HFONT GetMonthCalFont() const;
            VOID  SetMonthCalFont(HFONT hFont, BOOL bRedraw = TRUE);
        #endif // (_WIN32_IE >= 0x0400)
    };
#endif  // (_WIN32_IE >= 0x0300)

////////////////////////////////////////////////////////////////////////////

#if (_WIN32_IE >= 0x0300)
    inline MDateTimePick::MDateTimePick()
    {
    }

    inline /*virtual*/ LPCTSTR MDateTimePick::GetWndClassNameDx() const
    {
        return DATETIMEPICK_CLASS;
    }

    inline BOOL MDateTimePick::SetFormat(LPCTSTR lpszFormat)
    {
        return (BOOL)SendMessageDx(DTM_SETFORMAT, 0, (LPARAM)lpszFormat);
    }

    inline COLORREF MDateTimePick::GetMonthCalColor(
        INT nColorType) const
    {
        return (COLORREF)SendMessageDx(DTM_GETMCCOLOR, (WPARAM)nColorType);
    }

    inline COLORREF MDateTimePick::SetMonthCalColor(
        INT nColorType, COLORREF clr)
    {
        return (COLORREF)SendMessageDx(DTM_SETMCCOLOR, (WPARAM)nColorType, (LPARAM)clr);
    }

    inline DWORD MDateTimePick::GetRange(
        LPSYSTEMTIME lpSysTimeArray) const
    {
        return (DWORD)SendMessageDx(DTM_GETRANGE, 0, (LPARAM)lpSysTimeArray);
    }

    inline BOOL MDateTimePick::SetRange(
        DWORD dwFlags, LPSYSTEMTIME lpSysTimeArray)
    {
        return (BOOL)SendMessageDx(DTM_SETRANGE, dwFlags, (LPARAM)lpSysTimeArray);
    }

    inline DWORD MDateTimePick::GetSystemTime(
        LPSYSTEMTIME lpSysTime) const
    {
        return (DWORD)SendMessageDx(DTM_GETSYSTEMTIME, 0, (LPARAM)lpSysTime);
    }

    inline BOOL MDateTimePick::SetSystemTime(
        DWORD dwFlags, LPSYSTEMTIME lpSysTime)
    {
        return (BOOL)SendMessageDx(DTM_SETSYSTEMTIME, dwFlags, (LPARAM)lpSysTime);
    }

    inline HWND MDateTimePick::GetMonthCal() const
    {
        return (HWND)SendMessageDx(DTM_GETMONTHCAL);
    }

    #if (_WIN32_IE >= 0x0400)
        inline HFONT MDateTimePick::GetMonthCalFont() const
        {
            return (HFONT)SendMessageDx(DTM_GETMCFONT);
        }

        inline VOID
        MDateTimePick::SetMonthCalFont(HFONT hFont, BOOL bRedraw/* = TRUE*/)
        {
            SendMessageDx(DTM_SETMCFONT, (WPARAM)hFont, MAKELPARAM(bRedraw, 0));
        }
    #endif  // (_WIN32_IE >= 0x0400)
#endif  // (_WIN32_IE >= 0x0300)

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MDATETIMEPICK_HPP_
