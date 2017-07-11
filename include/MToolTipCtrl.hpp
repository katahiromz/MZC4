// MToolTipCtrl.hpp -- Win32API tool tip control wrapper        -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MTOOLTIPCTRL_HPP_
#define MZC4_MTOOLTIPCTRL_HPP_      2   /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MToolTipCtrl : public MWindowBase
{
public:
    MToolTipCtrl();
    virtual LPCTSTR GetWndClassName() const;

    VOID GetText(MString& str, HWND hWnd, UINT nToolID = 0) const;
    BOOL GetToolInfo(LPTOOLINFO lpToolInfo) const;
    VOID SetToolInfo(LPTOOLINFO lpToolInfo);
    VOID SetToolRect(HWND hWnd, UINT nToolID, LPCRECT prc);
    INT GetToolCount() const;

    VOID SetDelayTime(DWORD dwDuration, INT iTime);

    #if (_WIN32_IE >= 0x0300)
        INT GetDelayTime(DWORD dwDuration) const;

        VOID GetMargin(LPRECT lprc) const;
        VOID SetMargin(LPRECT lprc);

        INT GetMaxTipWidth() const;
        INT SetMaxTipWidth(INT iWidth);

        COLORREF GetTipBkColor() const;
        VOID SetTipBkColor(COLORREF clr);

        COLORREF GetTipTextColor() const;
        VOID SetTipTextColor(COLORREF clr);
    #endif  // (_WIN32_IE >= 0x0300)

    VOID Activate(BOOL bActivate);

    BOOL AddTool(HWND hWnd, UINT nTextID, LPCRECT lpRectTool = NULL,
        UINT nToolID = 0, HINSTANCE hInstance = NULL);
    BOOL AddTool(HWND hWnd, LPCTSTR lpszText = LPSTR_TEXTCALLBACK,
        LPCRECT lpRectTool = NULL, UINT nToolID = 0);

    VOID DelTool(HWND hWnd, UINT nToolID = 0);

    BOOL HitTest(HWND hWnd, POINT pt, LPTOOLINFO lpToolInfo) const;
    VOID RelayEvent(LPMSG lpMsg);
    VOID UpdateTipText(LPCTSTR lpszText, HWND hWnd, UINT nToolID = 0);
    VOID UpdateTipText(UINT nTextID, HWND hWnd, UINT nToolID = 0,
                       HINSTANCE hInstance = NULL);
    #if (_WIN32_IE >= 0x0400)
        VOID Update();
    #endif  // (_WIN32_IE >= 0x0400)

    VOID Pop();
};

////////////////////////////////////////////////////////////////////////////

inline MToolTipCtrl::MToolTipCtrl()
{
}

inline /*virtual*/ LPCTSTR MToolTipCtrl::GetWndClassName() const
{
    return TOOLTIPS_CLASS;
}

inline BOOL MToolTipCtrl::GetToolInfo(LPTOOLINFO lpToolInfo) const
{
    return (BOOL)SendMessageDx(TTM_GETTOOLINFO, 0, (LPARAM)lpToolInfo);
}

inline VOID MToolTipCtrl::SetToolInfo(LPTOOLINFO lpToolInfo)
{
    SendMessageDx(TTM_SETTOOLINFO, 0, (LPARAM)lpToolInfo);
}

inline INT MToolTipCtrl::GetToolCount() const
{
    return (INT)SendMessageDx(TTM_GETTOOLCOUNT);
}

inline VOID MToolTipCtrl::SetDelayTime(DWORD dwDuration, INT iTime)
{
    SendMessageDx(TTM_SETDELAYTIME, dwDuration, iTime);
}

#if (_WIN32_IE >= 0x0300)
    inline INT MToolTipCtrl::GetDelayTime(DWORD dwDuration) const
    {
        return (INT)SendMessageDx(TTM_GETDELAYTIME, dwDuration);
    }

    inline VOID MToolTipCtrl::GetMargin(LPRECT lprc) const
    {
        SendMessageDx(TTM_GETMARGIN, 0, (LPARAM)lprc);
    }

    inline VOID MToolTipCtrl::SetMargin(LPRECT lprc)
    {
        SendMessageDx(TTM_SETMARGIN, 0, (LPARAM)lprc);
    }

    inline INT MToolTipCtrl::GetMaxTipWidth() const
    {
        return (INT)SendMessageDx(TTM_GETMAXTIPWIDTH);
    }

    inline INT MToolTipCtrl::SetMaxTipWidth(INT iWidth)
    {
        return (INT)SendMessageDx(TTM_SETMAXTIPWIDTH, 0, iWidth);
    }

    inline COLORREF MToolTipCtrl::GetTipBkColor() const
    {
        return (COLORREF)SendMessageDx(TTM_GETTIPBKCOLOR);
    }

    inline VOID MToolTipCtrl::SetTipBkColor(COLORREF clr)
    {
        SendMessageDx(TTM_SETTIPBKCOLOR, (WPARAM)clr);
    }

    inline COLORREF MToolTipCtrl::GetTipTextColor() const
    {
        return (COLORREF)SendMessageDx(TTM_GETTIPTEXTCOLOR);
    }

    inline VOID MToolTipCtrl::SetTipTextColor(COLORREF clr)
    {
        SendMessageDx(TTM_SETTIPTEXTCOLOR, (WPARAM)clr);
    }
#endif  // (_WIN32_IE >= 0x0300)

inline VOID MToolTipCtrl::Activate(BOOL bActivate)
{
    SendMessageDx(TTM_ACTIVATE, (WPARAM)bActivate);
}

inline VOID MToolTipCtrl::DelTool(HWND hWnd, UINT nToolID/* = 0*/)
{
    TOOLINFO ti;
    ti.cbSize = sizeof(TOOLINFO);
    ti.hwnd = hWnd;
    ti.uId = nToolID;
    SendMessageDx(TTM_DELTOOL, 0, (LPARAM)&ti);
}

inline BOOL MToolTipCtrl::HitTest(
    HWND hWnd, POINT pt, LPTOOLINFO lpToolInfo) const
{
    TTHITTESTINFO hti;
    hti.hwnd = hWnd;
    hti.pt = pt;
    hti.ti = *lpToolInfo;
    hti.ti.cbSize = sizeof(TOOLINFO);
    return (BOOL)SendMessageDx(TTM_HITTEST, 0, (LPARAM)&hti);
}

inline VOID MToolTipCtrl::RelayEvent(LPMSG lpMsg)
{
    SendMessageDx(TTM_RELAYEVENT, 0, (LPARAM)lpMsg);
}

#if (_WIN32_IE >= 0x0400)
    inline VOID MToolTipCtrl::Update()
    {
        SendMessageDx(TTM_UPDATE);
    }
#endif  // (_WIN32_IE >= 0x0400)

#if (_WIN32_IE >= 0x0300)
    inline VOID MToolTipCtrl::Pop()
    {
        SendMessageDx(TTM_POP);
    }
#endif  // (_WIN32_IE >= 0x0300)

inline VOID MToolTipCtrl::GetText(
    MString& str, HWND hWnd, UINT nToolID/* = 0*/) const
{
    TCHAR sz[512];
    TOOLINFO ti;
    ZeroMemory(&ti, sizeof(ti));
    ti.cbSize = sizeof(TOOLINFO);
    ti.hwnd = hWnd;
    ti.uId = nToolID;
    ti.lpszText = sz;
    SendMessageDx(TTM_GETTEXT, 0, (LPARAM)&ti);
    str = sz;
}

inline VOID MToolTipCtrl::SetToolRect(HWND hWnd, UINT nToolID, LPCRECT prc)
{
    TOOLINFO ti;
    ti.cbSize = sizeof(TOOLINFO);
    ti.hwnd = hWnd;
    ti.uId = nToolID;
    ti.rect = *prc;
    SendMessageDx(TTM_NEWTOOLRECT, 0, (LPARAM)&ti);
}

inline BOOL MToolTipCtrl::AddTool(HWND hWnd, UINT nTextID,
    LPCRECT lpRectTool/* = NULL*/, UINT nToolID/* = 0*/,
    HINSTANCE hInstance/* = NULL*/)
{
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    TOOLINFO ti;
    ti.cbSize = sizeof(TOOLINFO);
    ti.hwnd = hWnd;
    ti.uId = nToolID;
    ti.rect = *lpRectTool;
    ti.hinst = hInstance;
    ti.lpszText = MAKEINTRESOURCE(nTextID);
    return (BOOL)SendMessageDx(TTM_ADDTOOL, 0, (LPARAM)&ti);
}

inline BOOL MToolTipCtrl::AddTool(HWND hWnd,
    LPCTSTR lpszText/* = LPSTR_TEXTCALLBACK*/,
    LPCRECT lpRectTool/* = NULL*/, UINT nToolID/* = 0*/)
{
    TOOLINFO ti;
    ti.cbSize = sizeof(TOOLINFO);
    ti.hwnd = hWnd;
    ti.uId = nToolID;
    ti.rect = *lpRectTool;
    ti.lpszText = const_cast<LPTSTR>(lpszText);
    return (BOOL)SendMessageDx(TTM_ADDTOOL, 0, (LPARAM)&ti);
}

inline VOID MToolTipCtrl::UpdateTipText(
    LPCTSTR lpszText, HWND hWnd, UINT nToolID/* = 0*/)
{
    TOOLINFO ti;
    ti.cbSize = sizeof(TOOLINFO);
    ti.hinst = ::GetModuleHandle(NULL);
    ti.lpszText = const_cast<LPTSTR>(lpszText);
    ti.hwnd = hWnd;
    ti.uId = nToolID;
    SendMessageDx(TTM_UPDATETIPTEXT, 0, (LPARAM)&ti);
}

inline VOID MToolTipCtrl::UpdateTipText(
    UINT nTextID, HWND hWnd, UINT nToolID/* = 0*/,
    HINSTANCE hInstance/* = NULL*/)
{
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    TOOLINFO ti;
    ti.cbSize = sizeof(TOOLINFO);
    ti.hinst = hInstance;
    ti.lpszText = MAKEINTRESOURCE(nTextID);
    ti.hwnd = hWnd;
    ti.uId = nToolID;
    SendMessageDx(TTM_UPDATETIPTEXT, 0, (LPARAM)&ti);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MTOOLTIPCTRL_HPP_
