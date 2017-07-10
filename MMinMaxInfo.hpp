// MMinMaxInfo.hpp -- Win32API window min max info wrapper      -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MMINMAXINFO_HPP_
#define MZC4_MMINMAXINFO_HPP_       2   /* Version 2 */

class MMinMaxInfo;

////////////////////////////////////////////////////////////////////////////

#include "MPointSizeRect.hpp"

////////////////////////////////////////////////////////////////////////////

class MMinMaxInfo : public MINMAXINFO
{
public:
    MMinMaxInfo();

    // NOTE: Call MMinMaxInfo::OnGetMinMaxInfo on WM_GETMINMAXINFO
    VOID OnGetMinMaxInfo(LPMINMAXINFO lpMMI);

    VOID SetMaximizedRect(const MRect& rc);
    VOID SetMinTrackSize(const MSize& psiz);
    VOID SetMaxTrackSize(const MSize& psiz);
    VOID ResetMaximizedRect();
    VOID ResetMinTrackSize();
    VOID ResetMaxTrackSize();

    // adjust window rect to fit for min max info
    VOID FixWindowRect(HWND hWnd) const;

protected:
    bool m_bUseMaxRect;
    bool m_bUseMinTrack;
    bool m_bUseMaxTrack;
};

////////////////////////////////////////////////////////////////////////////

inline MMinMaxInfo::MMinMaxInfo()
{
    m_bUseMaxRect = m_bUseMinTrack = m_bUseMaxTrack = false;
}

inline VOID MMinMaxInfo::OnGetMinMaxInfo(LPMINMAXINFO lpMMI)
{
    if (m_bUseMaxRect)
    {
        lpMMI->ptMaxPosition = ptMaxPosition;
        lpMMI->ptMaxSize = ptMaxSize;
    }

    if (m_bUseMinTrack)
        lpMMI->ptMinTrackSize = ptMinTrackSize;

    if (m_bUseMaxTrack)
        lpMMI->ptMaxTrackSize = ptMaxTrackSize;
}

inline VOID MMinMaxInfo::SetMaximizedRect(const MRect& rc)
{
    m_bUseMaxRect = true;
    ptMaxPosition = rc.TopLeft();
    ptMaxSize.x = rc.Width();
    ptMaxSize.y = rc.Height();
}

inline VOID MMinMaxInfo::ResetMaximizedRect()
{
    m_bUseMaxRect = false;
}

inline VOID MMinMaxInfo::SetMinTrackSize(const MSize& siz)
{
    m_bUseMinTrack = true;
    ptMinTrackSize.x = siz.cx;
    ptMinTrackSize.y = siz.cy;
}

inline VOID MMinMaxInfo::ResetMinTrackSize()
{
    m_bUseMinTrack = false;
}

inline VOID MMinMaxInfo::SetMaxTrackSize(const MSize& siz)
{
    m_bUseMaxTrack = true;
    ptMaxTrackSize.x = siz.cx;
    ptMaxTrackSize.y = siz.cy;
}

inline VOID MMinMaxInfo::ResetMaxTrackSize()
{
    m_bUseMaxTrack = false;
}

inline VOID MMinMaxInfo::FixWindowRect(HWND hWnd) const
{
    MRect rc;
    ::GetWindowRect(hWnd, &rc);

    if (::GetWindowLong(hWnd, GWL_STYLE) & WS_MAXIMIZE)
    {
        ::SetWindowPos(hWnd, NULL,
            ptMaxPosition.x, ptMaxPosition.y,
            ptMaxSize.x, ptMaxSize.y,
            SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);
        return;
    }
    if (m_bUseMinTrack)
    {
        if (rc.Width() < ptMinTrackSize.x)
            rc.right = rc.left + ptMinTrackSize.x;
        if (rc.Height() < ptMinTrackSize.x)
            rc.bottom = rc.top + ptMinTrackSize.y;
    }
    if (m_bUseMaxTrack)
    {
        if (ptMaxTrackSize.x < rc.Width())
            rc.right = rc.left + ptMaxTrackSize.x;
        if (ptMaxTrackSize.x < rc.Height())
            rc.bottom = rc.top + ptMaxTrackSize.y;
    }
    ::SetWindowPos(hWnd, NULL,
        rc.left, rc.top, rc.Width(), rc.Height(),
        SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);

    CHAR szClsName[16];
    if (::GetClassNameA(hWnd, szClsName, 16) &&
        ::lstrcmpA(szClsName, "#32770") == 0)
    {
        ::SendMessage(hWnd, DM_REPOSITION, 0, 0);
    }
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MMINMAXINFO_HPP_
