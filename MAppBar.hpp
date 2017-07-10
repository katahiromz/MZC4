// MAppBar.hpp -- Win32API appbar wrapper                       -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MAPPBAR_HPP_
#define MZC4_MAPPBAR_HPP_       2       /* Version 2 */

class MAppBar;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#ifndef _INC_SHELLAPI
    #include <shellapi.h>
#endif

#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

#include "MPointSizeRect.hpp"

class MAppBar : public APPBARDATA
{
public:
    BOOL fAppRegistered;

    MAppBar();
    MAppBar(HWND hwnd, UINT uCallbackMsg);

    BOOL Register(HWND hwnd, UINT uCallbackMsg);
    BOOL Unregister();
    BOOL IsRegistered() const;

    HWND GetWindow() const;
    UINT GetCallbackMessage() const;
    UINT GetEdge() const;
          MRect& GetRect();
    const MRect& GetRect() const;
    LPARAM GetData() const;
    LPVOID GetDataPtr() const;
    VOID SetData(LPARAM lData);
    VOID SetDataPtr(LPVOID pData);

public:
    BOOL Activate();

    HWND GetAutoHideBar();
    HWND GetAutoHideBar(UINT uABE_);
    BOOL SetAutoHideBar(UINT uABE_, BOOL bRegister = TRUE);

    BOOL QueryPos();
    BOOL QueryPos(UINT uABE_);
    BOOL QueryPos(UINT uABE_, LPRECT prc);
    BOOL SetPos();
    BOOL SetPos(UINT uABE_);
    BOOL SetPos(UINT uABE_, LPRECT prc);
    BOOL QuerySetPos(UINT uABE_, INT width_or_height, LPRECT prc = NULL);

    UINT GetState();
    BOOL GetTaskBarPos(LPRECT prc);

    BOOL WindowPosChanged();

    // call back messages
    BOOL OnAppBarCallbackMessage(WPARAM wParam, LPARAM lParam);
    virtual VOID OnFullScreenPos(BOOL fOpen);
    virtual VOID OnPosChanged();
    virtual VOID OnStateChange();
    virtual VOID OnWindowArrange(BOOL fBeginning);

    UINT_PTR SHAppBarMessage(DWORD dwMessage);
};

#define DO_APPBAR_MESSAGE(AppBar) \
    DO_MESSAGE((AppBar).uCallbackMessage, (AppBar).OnAppBarCallbackMessage)

////////////////////////////////////////////////////////////////////////////

inline MAppBar::MAppBar()
{
    cbSize = sizeof(APPBARDATA);
    hWnd = NULL;
    uCallbackMessage = 0;
    uEdge = 0;
    fAppRegistered = FALSE;
}

inline MAppBar::MAppBar(HWND hwnd, UINT uCallbackMsg)
{
    cbSize = sizeof(APPBARDATA);
    hWnd = NULL;
    uCallbackMessage = 0;
    uEdge = 0;
    fAppRegistered = FALSE;
    Register(hwnd, uCallbackMsg);
}

inline BOOL MAppBar::Register(HWND hwnd, UINT uCallbackMsg)
{
    assert(::IsWindow(hwnd));
    assert(!fAppRegistered);
    assert((WM_USER <= uCallbackMsg && uCallbackMsg <= 0x7FFF) ||
           (0xC000 <= uCallbackMsg && uCallbackMsg <= 0xFFFF));
    hWnd = hwnd;
    uCallbackMessage = uCallbackMsg;
    BOOL bOK = (BOOL)SHAppBarMessage(ABM_NEW);
    if (bOK)
        fAppRegistered = TRUE;
    return bOK;
}

inline BOOL MAppBar::Unregister()
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    BOOL bOK = (BOOL)SHAppBarMessage(ABM_REMOVE);
    if (bOK)
        fAppRegistered = FALSE;
    return bOK;
}

inline BOOL MAppBar::IsRegistered() const
{
    return fAppRegistered;
}

inline HWND MAppBar::GetWindow() const
{
    return hWnd;
}

inline UINT MAppBar::GetCallbackMessage() const
{
    return uCallbackMessage;
}

inline UINT MAppBar::GetEdge() const
{
    return uEdge;
}

inline MRect& MAppBar::GetRect()
{
    return *reinterpret_cast<MRect *>(&rc);
}

inline const MRect& MAppBar::GetRect() const
{
    return *reinterpret_cast<const MRect *>(&rc);
}

inline LPARAM MAppBar::GetData() const
{
    return lParam;
}

inline LPVOID MAppBar::GetDataPtr() const
{
    return reinterpret_cast<LPVOID>(lParam);
}

inline VOID MAppBar::SetData(LPARAM lData)
{
    lParam = lData;
}

inline VOID MAppBar::SetDataPtr(LPVOID pData)
{
    lParam = (LPARAM)pData;
}

inline BOOL MAppBar::Activate()
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    return SHAppBarMessage(ABM_ACTIVATE);
}

inline HWND MAppBar::GetAutoHideBar()
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    return (HWND)SHAppBarMessage(ABM_GETAUTOHIDEBAR);
}

inline HWND MAppBar::GetAutoHideBar(UINT uABE_)
{
    assert(fAppRegistered);
    assert(uABE_ == ABE_LEFT || uABE_ == ABE_TOP ||
        uABE_ == ABE_RIGHT || uABE_ == ABE_BOTTOM);
    assert(::IsWindow(hWnd));
    uEdge = uABE_;
    return (HWND)SHAppBarMessage(ABM_GETAUTOHIDEBAR);
}

inline BOOL MAppBar::SetAutoHideBar(UINT uABE_, BOOL bRegister/* = TRUE*/)
{
    assert(fAppRegistered);
    assert(uABE_ == ABE_LEFT || uABE_ == ABE_TOP ||
        uABE_ == ABE_RIGHT || uABE_ == ABE_BOTTOM);
    assert(::IsWindow(hWnd));
    uEdge = uABE_;
    lParam = bRegister;
    return (BOOL)SHAppBarMessage(ABM_SETAUTOHIDEBAR);
}

inline BOOL MAppBar::QueryPos()
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    BOOL bOK = (BOOL)SHAppBarMessage(ABM_QUERYPOS);
    return bOK;
}

inline BOOL MAppBar::QueryPos(UINT uABE_)
{
    assert(fAppRegistered);
    assert(uABE_ == ABE_LEFT || uABE_ == ABE_TOP ||
           uABE_ == ABE_RIGHT || uABE_ == ABE_BOTTOM);
    assert(::IsWindow(hWnd));
    uEdge = uABE_;
    BOOL bOK = (BOOL)SHAppBarMessage(ABM_QUERYPOS);
    return bOK;
}

inline BOOL MAppBar::SetPos()
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    BOOL bOK = (BOOL)SHAppBarMessage(ABM_SETPOS);
    return bOK;
}

inline BOOL MAppBar::SetPos(UINT uABE_)
{
    assert(fAppRegistered);
    assert(uABE_ == ABE_LEFT || uABE_ == ABE_TOP ||
           uABE_ == ABE_RIGHT || uABE_ == ABE_BOTTOM);
    assert(::IsWindow(hWnd));
    uEdge = uABE_;
    BOOL bOK = (BOOL)SHAppBarMessage(ABM_SETPOS);
    return bOK;
}

inline UINT MAppBar::GetState()
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    return (UINT)SHAppBarMessage(ABM_GETSTATE);
}

inline BOOL MAppBar::GetTaskBarPos(LPRECT prc)
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    BOOL bOK = SHAppBarMessage(ABM_GETTASKBARPOS);
    *prc = rc;
    return bOK;
}

inline BOOL MAppBar::WindowPosChanged()
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    return SHAppBarMessage(ABM_WINDOWPOSCHANGED);
}

inline /*virtual*/ VOID MAppBar::OnStateChange()
{
    assert(fAppRegistered);
    UINT uState = GetState();
    ::SetWindowPos(hWnd, (ABS_ALWAYSONTOP & uState) ? HWND_TOPMOST : HWND_BOTTOM,
        0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

inline /*virtual*/ VOID MAppBar::OnWindowArrange(BOOL fBeginning)
{
}

inline UINT_PTR MAppBar::SHAppBarMessage(DWORD dwMessage)
{
    return ::SHAppBarMessage(dwMessage, this);
}

inline BOOL MAppBar::QueryPos(UINT uABE_, LPRECT prc)
{
    assert(fAppRegistered);
    assert(uABE_ == ABE_LEFT || uABE_ == ABE_TOP ||
        uABE_ == ABE_RIGHT || uABE_ == ABE_BOTTOM);
    assert(::IsWindow(hWnd));
    uEdge = uABE_;
    rc = *prc;
    BOOL bOK = (BOOL)SHAppBarMessage(ABM_QUERYPOS);
    *prc = rc;
    return bOK;
}

inline BOOL MAppBar::SetPos(UINT uABE_, LPRECT prc)
{
    assert(fAppRegistered);
    assert(uABE_ == ABE_LEFT || uABE_ == ABE_TOP ||
        uABE_ == ABE_RIGHT || uABE_ == ABE_BOTTOM);
    assert(::IsWindow(hWnd));
    uEdge = uABE_;
    rc = *prc;
    BOOL bOK = (BOOL)SHAppBarMessage(ABM_SETPOS);
    *prc = rc;
    return bOK;
}

inline BOOL
MAppBar::QuerySetPos(UINT uABE_, INT width_or_height, LPRECT prc/* = NULL*/)
{
    assert(fAppRegistered);
    assert(uABE_ == ABE_LEFT || uABE_ == ABE_TOP ||
           uABE_ == ABE_RIGHT || uABE_ == ABE_BOTTOM);
    assert(width_or_height >= 0);

    GetScreenRectDx(&rc);

    INT cx = 0, cy = 0;
    if (uABE_ == ABE_LEFT || uABE_ == ABE_RIGHT)
        cx = width_or_height;
    else
        cy = width_or_height;

    if (!QueryPos(uABE_))
    {
        return FALSE;
    }

    switch (uABE_)
    {
    case ABE_LEFT:
        rc.right = rc.left + cx;
        break;
    case ABE_TOP:
        rc.bottom = rc.top + cy;
        break;
    case ABE_RIGHT:
        rc.left = rc.right - cx;
        break;
    case ABE_BOTTOM:
        rc.top = rc.bottom - cy;
        break;
    }

    if (SetPos())
    {
        ::MoveWindow(hWnd, rc.left, rc.top,
            rc.right - rc.left, rc.bottom - rc.top, TRUE);
        return TRUE;
    }
    return FALSE;
}

inline BOOL MAppBar::OnAppBarCallbackMessage(WPARAM wParam, LPARAM lParam)
{
    assert(fAppRegistered);
    switch (wParam)
    {
    case ABN_FULLSCREENAPP:
        OnFullScreenPos((BOOL)lParam);
        return TRUE;
    case ABN_POSCHANGED:
        OnPosChanged();
        return TRUE;
    case ABN_STATECHANGE:
        OnStateChange();
        return TRUE;
    case ABN_WINDOWARRANGE:
        OnWindowArrange((BOOL)lParam);
        return TRUE;
    }
    return FALSE;
}

inline /*virtual*/ VOID MAppBar::OnFullScreenPos(BOOL fOpen)
{
    assert(fAppRegistered);
    assert(::IsWindow(hWnd));
    UINT uState = GetState();
    if (fOpen)
    {
        ::SetWindowPos(hWnd,
            (ABS_ALWAYSONTOP & uState) ? HWND_TOPMOST : HWND_BOTTOM,
            0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    else
    {
        if (uState & ABS_ALWAYSONTOP)
            ::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0,
                           SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

inline /*virtual*/ VOID MAppBar::OnPosChanged()
{
    assert(fAppRegistered);
    RECT rcWindow;
    ::GetWindowRect(hWnd, &rcWindow);

    switch (uEdge)
    {
    case ABE_LEFT:
        QuerySetPos(uEdge, rcWindow.right - rcWindow.left);
        break;
    case ABE_TOP:
        QuerySetPos(uEdge, rcWindow.bottom - rcWindow.top);
        break;
    case ABE_RIGHT:
        QuerySetPos(uEdge, rcWindow.right - rcWindow.left);
        break;
    case ABE_BOTTOM:
        QuerySetPos(uEdge, rcWindow.bottom - rcWindow.top);
        break;
    default:
        assert(false);
        break;
    }
}

#endif  // ndef MZC4_MAPPBAR_HPP_
