// MNotifyIcon.hpp -- task bar notification icon                -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MNOTIFYICON_HPP_
#define MZC4_MNOTIFYICON_HPP_       2   /* Version 2 */

class MNotifyIcon;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#ifndef _INC_SHELLAPI
    #include <shellapi.h>
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

class MNotifyIcon : public NOTIFYICONDATA
{
public:
    MNotifyIcon();
    MNotifyIcon(HWND hWnd_, HICON hIcon_, UINT uID_, LPCTSTR pszTip = NULL);
    ~MNotifyIcon();

    VOID Init(HWND hWnd_, HICON hIcon_, UINT uID_, LPCTSTR pszTip = NULL);
    BOOL Add();
    BOOL Delete();
    BOOL Modify();
    BOOL ModifyIcon(HICON hIcon);
    BOOL ModifyTip(LPCTSTR pszTip);
    static UINT GetTaskbarCreatedMessage();
};

#ifndef MZC_WM_NOTIFYICON
    #define MZC_WM_NOTIFYICON   (WM_USER + 666)
#endif

////////////////////////////////////////////////////////////////////////////

inline MNotifyIcon::MNotifyIcon()
{
    ZeroMemory(this, sizeof(NOTIFYICONDATA));
}

inline MNotifyIcon::MNotifyIcon(HWND hWnd_, HICON hIcon_, UINT uID_, LPCTSTR pszTip_/* = NULL*/)
{
    Init(hWnd_, hIcon_, uID_, pszTip_);
}

inline VOID
MNotifyIcon::Init(HWND hWnd_, HICON hIcon_, UINT uID_, LPCTSTR pszTip_/* = NULL*/)
{
    assert(hWnd_);
    assert(::IsWindow(hWnd_));
    assert(hIcon_ != NULL);
    assert(pszTip_ == NULL || lstrlen(pszTip_) + 1 < (int)_countof(szTip));

    ZeroMemory(this, sizeof(NOTIFYICONDATA));
    cbSize = sizeof(NOTIFYICONDATA);
    hWnd = hWnd_;
    uID = uID_;
    uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    uCallbackMessage = MZC_WM_NOTIFYICON;
    hIcon = hIcon_;

    if (pszTip_)
        ::lstrcpyn(szTip, pszTip_, _countof(szTip));
    else
        szTip[0] = TEXT('\0');
}

inline MNotifyIcon::~MNotifyIcon()
{
    ::DestroyIcon(hIcon);
}

inline BOOL MNotifyIcon::Add()
{
    return ::Shell_NotifyIcon(NIM_ADD, this);
}

inline BOOL MNotifyIcon::Delete()
{
    return ::Shell_NotifyIcon(NIM_DELETE, this);
}

inline BOOL MNotifyIcon::Modify()
{
    return ::Shell_NotifyIcon(NIM_MODIFY, this);
}

inline BOOL MNotifyIcon::ModifyIcon(HICON hIcon_)
{
    assert(hIcon_ != NULL);
    ::DestroyIcon(hIcon);
    hIcon = hIcon_;
    return Modify();
}

inline BOOL MNotifyIcon::ModifyTip(LPCTSTR pszTip)
{
    assert(pszTip == NULL || lstrlen(pszTip) + 1 < (int)_countof(szTip));
    if (pszTip == NULL)
        szTip[0] = TEXT('\0');
    else
        ::lstrcpyn(szTip, pszTip, _countof(szTip));
    return Modify();
}

inline /*static*/ UINT MNotifyIcon::GetTaskbarCreatedMessage()
{
    static UINT uTaskbarCreatedMsg =
        ::RegisterWindowMessage(TEXT("TaskbarCreated"));
    return uTaskbarCreatedMsg;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MNOTIFYICON_HPP_
