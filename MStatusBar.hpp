// MStatusBar.hpp -- Win32API status bar wrapper                -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSTATUSBAR_HPP_
#define MZC4_MSTATUSBAR_HPP_        2   /* Version 2 */

class MStatusBar;

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MStatusBar : public MWindowBase
{
public:
    MStatusBar();
    virtual LPCTSTR GetWndClassName() const;

    INT GetText(LPCTSTR lpszText, INT nPane, INT* pnSBT_ = NULL) const;
    MString GetText(INT nPane, INT* pnSBT_ = NULL) const;
    INT GetTextLength(INT nPane, INT* pnSBT_ = NULL) const;
    BOOL SetText(LPCTSTR lpszText, INT nPane = 0, INT nSBT_ = 0);

    INT GetParts(INT nParts, INT* pParts) const;
    BOOL SetParts(INT nParts, INT* pWidths);
    BOOL GetBorders(INT* pBorders) const;
    BOOL GetBorders(INT& nHorz, INT& nVert, INT& nSpacing) const;
    BOOL GetRect(INT iPart, LPRECT prc) const;
    VOID SetMinHeight(INT nMin);

#if (_WIN32_IE >= 0x0300)
    BOOL IsSimple() const;
#endif  // (_WIN32_IE >= 0x0300)
    BOOL SetSimple(BOOL bSimple = TRUE);

#if (_WIN32_IE >= 0x0400)
    VOID GetTipText(INT nPane, LPTSTR lpstrText, INT nSize) const;
    MString GetTipText(INT nPane) const;
    VOID SetTipText(INT nPane, LPCTSTR pszTipText);

    HICON GetIcon(INT nPane);
    BOOL SetIcon(INT nPane, HICON hIcon);

    COLORREF SetBkColor(COLORREF cr);
#endif  // (_WIN32_IE >= 0x0400)

    VOID AutoSize();
};

////////////////////////////////////////////////////////////////////////////

inline MStatusBar::MStatusBar()
{
}

inline /*virtual*/ LPCTSTR MStatusBar::GetWndClassName() const
{
    return STATUSCLASSNAME;
}

inline BOOL MStatusBar::SetText(
    LPCTSTR lpszText, INT nPane/* = 0*/, INT nSBT_/* = 0*/)
{
    assert(nPane < 256);
    return (BOOL)SendMessageDx(SB_SETTEXT, (WPARAM)(nPane | nSBT_), (LPARAM)lpszText);
}

inline INT MStatusBar::GetText(
    LPCTSTR lpszText, INT nPane, INT* pnSBT_/* = NULL*/) const
{
    assert(nPane < 256);
    DWORD dw = (DWORD)SendMessageDx(SB_GETTEXT, (WPARAM)nPane, (LPARAM)lpszText);
    if (pnSBT_ != NULL)
        *pnSBT_ = (INT) HIWORD(dw);
    return (INT) LOWORD(dw);
}

inline INT MStatusBar::GetTextLength(
    INT nPane, INT* pnSBT_/* = NULL*/) const
{
    assert(nPane < 256);
    DWORD dw = (DWORD)SendMessageDx(SB_GETTEXTLENGTH, (WPARAM)nPane);
    if (pnSBT_ != NULL)
        *pnSBT_ = (INT) HIWORD(dw);
    return (INT) LOWORD(dw);
}

inline BOOL MStatusBar::SetParts(INT nParts, INT* pWidths)
{
    return (BOOL)SendMessageDx(SB_SETPARTS, (WPARAM)nParts, (LPARAM)pWidths);
}

inline INT MStatusBar::GetParts(INT nParts, INT* pParts) const
{
    return (INT)SendMessageDx(SB_GETPARTS, (WPARAM)nParts, (LPARAM)pParts);
}

inline BOOL MStatusBar::GetBorders(INT* pBorders) const
{
    return (BOOL)SendMessageDx(SB_GETBORDERS, 0, (LPARAM)pBorders);
}

inline BOOL MStatusBar::GetBorders(
    INT& nHorz, INT& nVert, INT& nSpacing) const
{
    INT an[3];
    BOOL b = (BOOL)SendMessageDx(SB_GETBORDERS, 0, (LPARAM)an);
    if (b)
    {
        nHorz = an[0];
        nVert = an[1];
        nSpacing = an[2];
    }
    return b;
}

inline VOID MStatusBar::SetMinHeight(INT nMin)
{
    SendMessageDx(SB_SETMINHEIGHT, (WPARAM)nMin);
}

inline BOOL MStatusBar::GetRect(INT iPart, LPRECT prc) const
{
    assert(iPart < 256);
    return (BOOL)SendMessageDx(SB_GETRECT, (WPARAM)iPart, (LPARAM)prc);
}
#if (_WIN32_IE >= 0x0300)
    
inline BOOL MStatusBar::IsSimple() const
    {
        return (BOOL)SendMessageDx(SB_ISSIMPLE);
    }
#endif  // (_WIN32_IE >= 0x0300)

inline BOOL MStatusBar::SetSimple(BOOL bSimple/* = TRUE*/)
{
    return (BOOL)SendMessageDx(SB_SIMPLE, (WPARAM)bSimple);
}

inline VOID MStatusBar::AutoSize()
{
    SendMessageDx(WM_SIZE);
}

#if (_WIN32_IE >= 0x0400)
    inline VOID MStatusBar::GetTipText(
        INT nPane, LPTSTR lpstrText, INT nSize) const
    {
        assert(nPane < 256);
        SendMessageDx(SB_GETTIPTEXT, MAKEWPARAM(nPane, nSize), (LPARAM)lpstrText);
    }
    
    inline MString MStatusBar::GetTipText(INT nPane) const
    {
        assert(nPane < 256);
        TCHAR sz[512];
        GetTipText(nPane, sz, 512);
        MString str = sz;
        return str;
    }
    
    inline VOID MStatusBar::SetTipText(INT nPane, LPCTSTR pszTipText)
    {
        assert(nPane < 256);
        SendMessageDx(SB_SETTIPTEXT, (WPARAM)nPane, (LPARAM)pszTipText);
    }
    
    inline HICON MStatusBar::GetIcon(INT nPane)
    {
        assert(nPane < 256);
        return (HICON)SendMessageDx(SB_GETICON, (WPARAM)nPane);
    }
    
    inline BOOL MStatusBar::SetIcon(INT nPane, HICON hIcon)
    {
        assert(nPane < 256);
        return (BOOL)SendMessageDx(SB_SETICON, (WPARAM)nPane, (LPARAM)hIcon);
    }
    
    inline COLORREF MStatusBar::SetBkColor(COLORREF cr)
    {
        return (COLORREF)SendMessageDx(SB_SETBKCOLOR, 0, (LPARAM)cr);
    }
#endif  // (_WIN32_IE >= 0x0400)

inline MString MStatusBar::GetText(INT nPane, INT* pType/* = NULL*/) const
{
    assert(nPane < 256);
    DWORD dw = (DWORD)(DWORD_PTR)SendMessageDx(SB_GETTEXTLENGTH, (WPARAM)nPane);

    TCHAR sz[512];
    dw = (DWORD)(DWORD_PTR)SendMessageDx(SB_GETTEXT, (WPARAM)nPane, (LPARAM)sz);
    if (pType != NULL)
        *pType = (INT) HIWORD(dw);

    MString str = sz;
    return str;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSTATUSBAR_HPP_
