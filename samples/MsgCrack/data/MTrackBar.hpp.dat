// MTrackBar.hpp -- Win32API track bar wrapper                  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MTRACKBAR_HPP_
#define MZC4_MTRACKBAR_HPP_     2       /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MTrackBar : public MWindowBase
{
public:
    MTrackBar();
    virtual LPCTSTR GetWndClassNameDx() const;

    INT GetLineSize() const;
    INT SetLineSize(INT nSize);

    INT GetPageSize() const;
    INT SetPageSize(INT nSize);

    INT GetRangeMax() const;
    INT GetRangeMin() const;

    VOID GetRange(INT& nMin, INT& nMax) const;
    VOID SetRangeMin(INT nMin, BOOL bRedraw = TRUE);
    VOID SetRangeMax(INT nMax, BOOL bRedraw = TRUE);
    VOID SetRange(INT nMin, INT nMax, BOOL bRedraw = TRUE);

    VOID GetSelection(INT& nMin, INT& nMax) const;
    VOID SetSelection(INT nMin, INT nMax, BOOL bRedraw = TRUE);

    VOID GetChannelRect(LPRECT lprc) const;
    VOID GetThumbRect(LPRECT lprc) const;

    INT GetPos() const;
    VOID SetPos(INT nPos);

    UINT GetNumTics() const;
    DWORD* GetTicArray() const;

    INT GetTic(INT nTic) const;
    INT GetTicPos(INT nTic) const;
    BOOL SetTic(INT nTic);
    VOID SetTicFreq(INT nFreq);

    VOID ClearSel(BOOL bRedraw = TRUE);
    VOID VerifyPos();
    VOID ClearTics(BOOL bRedraw = TRUE);

#if (_WIN32_IE >= 0x0300)
    HWND GetBuddy(BOOL fLeft = TRUE) const;
    HWND SetBuddy(HWND hwndBuddy, BOOL fLeft = TRUE);

    HWND GetToolTips() const;
    VOID SetToolTips(HWND hwndTT);
    INT SetTipSide(INT nLocation);
#endif  // (_WIN32_IE >= 0x0300)
};
typedef MTrackBar MSlider;

////////////////////////////////////////////////////////////////////////////

inline MTrackBar::MTrackBar()
{
}

inline /*virtual*/ LPCTSTR MTrackBar::GetWndClassNameDx() const
{
    return TRACKBAR_CLASS;
}

inline INT MTrackBar::GetLineSize() const
{
    return (INT)SendMessageDx(TBM_GETLINESIZE);
}

inline INT MTrackBar::SetLineSize(INT nSize)
{
    return (INT)SendMessageDx(TBM_SETLINESIZE, 0, nSize);
}

inline INT MTrackBar::GetPageSize() const
{
    return (INT)SendMessageDx(TBM_GETPAGESIZE);
}

inline INT MTrackBar::SetPageSize(INT nSize)
{
    return (INT)SendMessageDx(TBM_SETPAGESIZE, 0, nSize);
}

inline INT MTrackBar::GetRangeMax() const
{
    return (INT)SendMessageDx(TBM_GETRANGEMAX);
}

inline INT MTrackBar::GetRangeMin() const
{
    return (INT)SendMessageDx(TBM_GETRANGEMIN);
}

inline VOID MTrackBar::GetRange(INT& nMin, INT& nMax) const
{
    nMin = GetRangeMin();
    nMax = GetRangeMax();
}

inline VOID MTrackBar::SetRangeMin(INT nMin, BOOL bRedraw/* = TRUE*/)
{
    SendMessageDx(TBM_SETRANGEMIN, (WPARAM)bRedraw, (LPARAM)nMin);
}

inline VOID MTrackBar::SetRangeMax(INT nMax, BOOL bRedraw/* = TRUE*/)
{
    SendMessageDx(TBM_SETRANGEMAX, (WPARAM)bRedraw, (LPARAM)nMax);
}

inline VOID MTrackBar::SetRange(INT nMin, INT nMax, BOOL bRedraw/* = TRUE*/)
{
    SendMessageDx(TBM_SETRANGE, (WPARAM)bRedraw, MAKELPARAM(nMin, nMax));
}

inline VOID MTrackBar::GetSelection(INT& nMin, INT& nMax) const
{
    nMin = (INT)SendMessageDx(TBM_GETSELSTART);
    nMax = (INT)SendMessageDx(TBM_GETSELEND);
}

inline VOID MTrackBar::SetSelection(INT nMin, INT nMax, BOOL bRedraw/* = TRUE*/)
{
    SendMessageDx(TBM_SETSEL, (WPARAM)bRedraw, MAKELPARAM(nMin, nMax));
}

inline VOID MTrackBar::GetChannelRect(LPRECT lprc) const
{
    SendMessageDx(TBM_GETCHANNELRECT, 0, (LPARAM)lprc);
}

inline VOID MTrackBar::GetThumbRect(LPRECT lprc) const
{
    SendMessageDx(TBM_GETTHUMBRECT, 0, (LPARAM)lprc);
}

inline INT MTrackBar::GetPos() const
{
    return (INT)SendMessageDx(TBM_GETPOS);
}

inline VOID MTrackBar::SetPos(INT nPos)
{
    SendMessageDx(TBM_SETPOS, TRUE, nPos);
}

inline UINT MTrackBar::GetNumTics() const
{
    return (UINT)SendMessageDx(TBM_GETNUMTICS);
}

inline DWORD* MTrackBar::GetTicArray() const
{
    return (DWORD *)SendMessageDx(TBM_GETPTICS);
}

inline INT MTrackBar::GetTic(INT nTic) const
{
    return (INT)SendMessageDx(TBM_GETTIC, (WPARAM)nTic);
}

inline INT MTrackBar::GetTicPos(INT nTic) const
{
    return (INT)SendMessageDx(TBM_GETTICPOS, (WPARAM)nTic);
}

inline BOOL MTrackBar::SetTic(INT nTic)
{
    return (BOOL)SendMessageDx(TBM_SETTIC, 0, nTic);
}

inline VOID MTrackBar::SetTicFreq(INT nFreq)
{
    SendMessageDx(TBM_SETTICFREQ, (WPARAM)nFreq);
}

#if (_WIN32_IE >= 0x0300)
    inline HWND MTrackBar::GetBuddy(BOOL fLeft/* = TRUE*/) const
    {
        return (HWND)SendMessageDx(TBM_GETBUDDY, (WPARAM)fLeft);
    }

    inline HWND MTrackBar::SetBuddy(HWND hwndBuddy, BOOL fLeft/* = TRUE*/)
    {
        return (HWND)SendMessageDx(TBM_SETBUDDY, (WPARAM)fLeft, (LPARAM)hwndBuddy);
    }

    inline HWND MTrackBar::GetToolTips() const
    {
        return (HWND)SendMessageDx(TBM_GETTOOLTIPS);
    }

    inline VOID MTrackBar::SetToolTips(HWND hwndTT)
    {
        SendMessageDx(TBM_SETTOOLTIPS, (WPARAM)hwndTT);
    }

    inline INT MTrackBar::SetTipSide(INT nLocation)
    {
        return (INT)SendMessageDx(TBM_SETTIPSIDE, (WPARAM)nLocation);
    }
#endif  // (_WIN32_IE >= 0x0300)

inline VOID MTrackBar::ClearSel(BOOL bRedraw/* = TRUE*/)
{
    SendMessageDx(TBM_CLEARSEL, (WPARAM)bRedraw);
}

inline VOID MTrackBar::VerifyPos()
{
    SendMessageDx(TBM_SETPOS, (WPARAM)FALSE);
}

inline VOID MTrackBar::ClearTics(BOOL bRedraw/* = TRUE*/)
{
    SendMessageDx(TBM_CLEARTICS, (WPARAM)bRedraw);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MTRACKBAR_HPP_
