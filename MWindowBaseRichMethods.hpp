// MWindowBaseRichMethods.hpp --- MWindowBase rich methods      -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
//////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MWINDOWBASE_HPP_
    #error Do not #include "MWindowBaseRichMethods.hpp" directly. You lose.
#endif

//////////////////////////////////////////////////////////////////////////////

#if (WINVER >= 0x0500)
    BOOL AnimateWindow(DWORD dwTime, DWORD dwAW_)
    {
        assert(::IsWindow(Handle()));
        return ::AnimateWindow(Handle(), dwTime, dwAW_);
    }
#endif

UINT ArrangeIconicWindows()
{
    assert(::IsWindow(Handle()));
    return ::ArrangeIconicWindows(Handle());
}

HDC BeginPaint(PAINTSTRUCT* pPS)
{
    assert(::IsWindow(Handle()));
    return ::BeginPaint(Handle(), pPS);
}

BOOL BringWindowToTop()
{
    assert(::IsWindow(Handle()));
    return ::BringWindowToTop(Handle());
}

BOOL AdjustWindowRect(LPRECT prcClientToWindow)
{
    assert(::IsWindow(Handle()));
    return ::AdjustWindowRect(prcClientToWindow, GetStyleDx(),
                              ::GetMenu(Handle()) != NULL);
}

BOOL AdjustWindowRectEx(LPRECT prcClientToWindow)
{
    assert(::IsWindow(Handle()));
    return ::AdjustWindowRectEx(prcClientToWindow, GetStyleDx(),
                                ::GetMenu(Handle()) != NULL, GetExStyleDx());
}

BOOL CheckDlgButton(INT nButtonID, UINT nBST_)
{
    assert(::IsWindow(Handle()));
    return ::CheckDlgButton(Handle(), nButtonID, nBST_);
}

HWND ChildWindowFromPoint(POINT pt)
{
    assert(::IsWindow(Handle()));
    return ::ChildWindowFromPoint(Handle(), pt);
}

HWND ChildWindowFromPointEx(POINT pt, UINT nCWP_ = CWP_ALL)
{
    assert(::IsWindow(Handle()));
    return ::ChildWindowFromPointEx(Handle(), pt, nCWP_);
}

BOOL ClientToScreen(LPPOINT ppt) const
{
    assert(::IsWindow(Handle()));
    return ::ClientToScreen(Handle(), ppt);
}

BOOL ClientToScreen(RECT *prc) const
{
    assert(::IsWindow(Handle()));
    return ::MapWindowPoints(Handle(), NULL, (LPPOINT)prc, 2);
}

BOOL CloseWindow()
{
    assert(::IsWindow(Handle()));
    return ::CloseWindow(Handle());
}

BOOL CreateCaret(HBITMAP hbm)
{
    assert(::IsWindow(Handle()));
    BITMAP bm;
    ::GetObject(hbm, sizeof(bm), &bm);
    return ::CreateCaret(Handle(), hbm, bm.bmWidth, bm.bmHeight);
}

BOOL CreateCaret(HBITMAP hbm, INT cx, INT cy)
{
    assert(::IsWindow(Handle()));
    return ::CreateCaret(Handle(), hbm, cx, cy);
}

BOOL CreateGrayCaret(INT cx, INT cy)
{
    return CreateCaret((HBITMAP)1, cx, cy);
}

BOOL CreateSolidCaret(INT cx, INT cy)
{
    return CreateCaret(NULL, cx, cy);
}

BOOL DestroyWindow()
{
    assert(::IsWindow(Handle()));
    return ::DestroyWindow(Handle());
}

INT DlgDirList(LPTSTR pPathSpec, INT nListBoxID, INT nPathStaticID, UINT nDDL_ = DDL_DRIVES)
{
    assert(::IsWindow(Handle()));
    return ::DlgDirList(Handle(), pPathSpec, nListBoxID, nPathStaticID, nDDL_);
}

INT DlgDirListComboBox(LPTSTR pPathSpec, INT nComboBoxID, INT nPathStaticID, UINT nDDL_ = DDL_DRIVES)
{
    assert(::IsWindow(Handle()));
    return ::DlgDirListComboBox(Handle(), pPathSpec, nComboBoxID, nPathStaticID, nDDL_);
}

BOOL DlgDirSelectEx(LPTSTR pszPath, INT cchPath, INT nListBoxID)
{
    assert(::IsWindow(Handle()));
    return ::DlgDirSelectEx(Handle(), pszPath, cchPath, nListBoxID);
}

BOOL DlgDirSelectComboBoxEx(LPTSTR pszPath, INT cchPath, INT nComboBoxID)
{
    assert(::IsWindow(Handle()));
    return ::DlgDirSelectComboBoxEx(Handle(), pszPath, cchPath, nComboBoxID);
}

VOID DragAcceptFiles(BOOL bAccept = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::DragAcceptFiles(Handle(), bAccept);
}

BOOL DragDetect(POINT pt) const
{
    assert(::IsWindow(Handle()));
    return ::DragDetect(Handle(), pt);
}

BOOL DrawAnimatedRects(const RECT *prcFrom, const RECT *prcTo, INT idAni = 0)
{
    assert(::IsWindow(Handle()));
    return ::DrawAnimatedRects(Handle(), idAni, prcFrom, prcTo);
}

BOOL DrawCaption(HDC hDC, const RECT *prc, UINT nDC_)
{
    assert(::IsWindow(Handle()));
    return ::DrawCaption(Handle(), hDC, prc, nDC_);
}

BOOL DrawMenuBar()
{
    assert(::IsWindow(Handle()));
    return ::DrawMenuBar(Handle());
}

BOOL EnableScrollBar(UINT nSB_, UINT nESB_ = ESB_ENABLE_BOTH)
{
    assert(::IsWindow(Handle()));
    return ::EnableScrollBar(Handle(), nSB_, nESB_);
}

BOOL EnableScrollBarCtrl(UINT nBarID, BOOL bEnable = TRUE)
{
    assert(::IsWindow(Handle()));
    HWND hwndSB = ::GetDlgItem(Handle(), nBarID);
    return ::EnableScrollBar(hwndSB, SB_CTL,
        (bEnable ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH));
}

// TODO: EnableToolTips

BOOL EnableWindow(BOOL bEnable = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::EnableWindow(Handle(), bEnable);
}

BOOL EndPaint(const PAINTSTRUCT *pPS)
{
    assert(::IsWindow(Handle()));
    return ::EndPaint(Handle(), pPS);
}

// TODO: ExecuteDlgInit(LPCTSTR pszResName)

BOOL FlashWindow(BOOL bInvert)
{
    assert(::IsWindow(Handle()));
    return ::FlashWindow(Handle(), bInvert);
}

#if (WINVER >= 0x0500)
    BOOL FlashWindowEx(DWORD dwFLASHW_, UINT uCount, DWORD dwTimeout)
    {
        assert(::IsWindow(Handle()));
        FLASHWINFO info;
        ZeroMemory(&info, sizeof(info));
        info.cbSize = sizeof(info);
        info.hwnd = Handle();
        info.dwFlags = dwFLASHW_;
        info.uCount = uCount;
        info.dwTimeout = dwTimeout;
        return ::FlashWindowEx(&info);
    }
#endif

#if WINVER >= 0x0500
    HWND GetAncestor(UINT nGA_)
    {
        assert(::IsWindow(Handle()));
        return ::GetAncestor(Handle(), nGA_);
    }
#endif

INT GetCheckedRadioButton(INT nFirstID, INT nLastID) const
{
    assert(::IsWindow(Handle()));
    while (nFirstID < nLastID)
    {
        if (::IsDlgButtonChecked(Handle(), nFirstID) == BST_CHECKED)
            return nFirstID;
        ++nFirstID;
    }
    return 0;
}

BOOL GetClientRect(RECT *prc) const
{
    assert(::IsWindow(Handle()));
    return ::GetClientRect(Handle(), prc);
}

RECT GetClientRect() const
{
    RECT rc;
    GetClientRect(&rc);
    return rc;
}

HDC GetDC()
{
    assert(::IsWindow(Handle()));
    return ::GetDC(Handle());
}

HDC GetDCEx(HRGN hRgnClip, DWORD dwDCX_)
{
    assert(::IsWindow(Handle()));
    return ::GetDCEx(Handle(), hRgnClip, dwDCX_);
}

INT GetDlgCtrlID() const
{
    assert(::IsWindow(Handle()));
    return ::GetDlgCtrlID(Handle());
}

HWND GetDlgItem(INT nID) const
{
    assert(::IsWindow(Handle()));
    return ::GetDlgItem(Handle(), nID);
}

UINT GetDlgItemInt(INT nID, BOOL *lpTranslated = NULL, BOOL bSigned = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::GetDlgItemInt(Handle(), nID, lpTranslated, bSigned);
}

INT GetDlgItemText(INT nID, LPTSTR psz, INT cchMax) const
{
    assert(::IsWindow(Handle()));
    return ::GetDlgItemText(Handle(), nID, psz, cchMax);
}

HFONT GetFontDx() const
{
    return (HFONT)SendMessageDx(WM_GETFONT, 0, 0);
}

HICON GetIconDx(BOOL bBigIcon = TRUE) const
{
    return (HICON)SendMessageDx(WM_GETICON, (bBigIcon ? ICON_BIG : ICON_SMALL));
}

HWND GetLastActivePopup() const
{
    assert(::IsWindow(Handle()));
    return ::GetLastActivePopup(Handle());
}

HMENU GetMenu() const
{
    assert(::IsWindow(Handle()));
    return ::GetMenu(Handle());
}

HWND GetNextDlgGroupItem(HWND hwndCtrl, BOOL bPrevious = FALSE) const
{
    assert(::IsWindow(Handle()));
    return ::GetNextDlgGroupItem(Handle(), hwndCtrl, bPrevious);
}

HWND GetNextDlgTabItem(HWND hwndCtrl, BOOL bPrevious = FALSE) const
{
    assert(::IsWindow(Handle()));
    return ::GetNextDlgTabItem(Handle(), hwndCtrl, bPrevious);
}

#undef GetNextWindow
HWND GetNextWindow(UINT nGW_ = GW_HWNDNEXT) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindow(Handle(), nGW_);
}

static HWND GetNextWindow(HWND hwnd, UINT nGW_ = GW_HWNDNEXT)
{
    return ::GetWindow(hwnd, nGW_);
}

HWND GetOwnerDx() const
{
    assert(::IsWindow(Handle()));
    return ::GetWindow(Handle(), GW_OWNER);
}

HWND GetParent() const
{
    assert(::IsWindow(Handle()));
    return ::GetParent(Handle());
}

// TODO: GetParentFrame
// TODO: GetParentOwner
// TODO: GetScrollBarCtrl

BOOL GetScrollInfo(INT nSB_, SCROLLINFO *pInfo) const
{
    assert(::IsWindow(Handle()));
    return ::GetScrollInfo(Handle(), nSB_, pInfo);
}

INT GetScrollPos(INT nSB_) const
{
    assert(::IsWindow(Handle()));
    return ::GetScrollPos(Handle(), nSB_);
}

BOOL GetScrollRange(INT nSB_, LPINT pMinPos, LPINT pMaxPos) const
{
    assert(::IsWindow(Handle()));
    return ::GetScrollRange(Handle(), nSB_, pMinPos, pMaxPos);
}

HMENU GetSystemMenu(BOOL bRevert = FALSE) const
{
    assert(::IsWindow(Handle()));
    return ::GetSystemMenu(Handle(), bRevert);
}

HWND GetTopWindow() const
{
    assert(::IsWindow(Handle()));
    return ::GetTopWindow(Handle());
}

BOOL GetUpdateRect(RECT *prc = NULL, BOOL bErase = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::GetUpdateRect(Handle(), prc, bErase);
}

INT GetUpdateRgn(HRGN hRgn, BOOL bErase = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::GetUpdateRgn(Handle(), hRgn, bErase);
}

HWND GetWindow(UINT nGW_) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindow(Handle(), nGW_);
}

DWORD GetWindowContextHelpId() const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowContextHelpId(Handle());
}

HDC GetWindowDC()
{
    assert(::IsWindow(Handle()));
    return ::GetWindowDC(Handle());
}

BOOL GetWindowPlacement(WINDOWPLACEMENT *pwndpl) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowPlacement(Handle(), pwndpl);
}

BOOL GetWindowRect(RECT *prc) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowRect(Handle(), prc);
}

RECT GetWindowRect() const
{
    RECT rc;
    GetWindowRect(&rc);
    return rc;
}

INT GetWindowRgn(HRGN hRgn) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowRgn(Handle(), hRgn);
}

INT GetWindowTextLength() const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowTextLength(Handle());
}

BOOL HideCaret()
{
    assert(::IsWindow(Handle()));
    return ::HideCaret(Handle());
}

BOOL HiliteMenuItem(HMENU hMenu, UINT nItem,
                    UINT nMF_ = MF_BYCOMMAND | MF_HILITE)
{
    assert(::IsWindow(Handle()));
    return ::HiliteMenuItem(Handle(), hMenu, nItem, nMF_);
}

// TODO: HtmlHelp

BOOL Invalidate(BOOL bErase = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::InvalidateRect(Handle(), NULL, bErase);
}

BOOL InvalidateRect(const RECT *prc, BOOL bErase = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::InvalidateRect(Handle(), prc, bErase);
}

BOOL InvalidateRgn(HRGN hRgn, BOOL bErase = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::InvalidateRgn(Handle(), hRgn, bErase);
}

BOOL IsChild(HWND hwndChild) const
{
    assert(::IsWindow(Handle()));
    return ::IsChild(Handle(), hwndChild);
}

UINT IsDlgButtonChecked(INT nID) const
{
    assert(::IsWindow(Handle()));
    return ::IsDlgButtonChecked(Handle(), nID);
}

BOOL IsIconic() const
{
    assert(::IsWindow(Handle()));
    return ::IsIconic(Handle());
}

BOOL IsWindowEnabled() const
{
    assert(::IsWindow(Handle()));
    return ::IsWindowEnabled(Handle());
}

BOOL IsWindowVisible() const
{
    assert(::IsWindow(Handle()));
    return ::IsWindowVisible(Handle());
}

BOOL IsZoomed() const
{
    assert(::IsWindow(Handle()));
    return ::IsZoomed(Handle());
}

BOOL KillTimer(UINT_PTR nTimerID)
{
    assert(::IsWindow(Handle()));
    return ::KillTimer(Handle(), nTimerID);
}

BOOL LockWindowUpdate()
{
    assert(::IsWindow(Handle()));
    return ::LockWindowUpdate(Handle());
}

INT MapWindowPoints(HWND hwndTo, LPRECT prc) const
{
    assert(::IsWindow(Handle()));
    return ::MapWindowPoints(Handle(), hwndTo, (LPPOINT)prc, 2);
}

INT MapWindowPoints(HWND hwndTo, LPPOINT ppt, UINT cPoints) const
{
    assert(::IsWindow(Handle()));
    return ::MapWindowPoints(Handle(), hwndTo, ppt, cPoints);
}

BOOL MoveWindow(INT x, INT y, INT cx, INT cy, BOOL bRepaint = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::MoveWindow(Handle(), x, y, cx, cy, bRepaint);
}

BOOL MoveWindow(const RECT *prc, BOOL bRepaint = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::MoveWindow(Handle(), prc->left, prc->top,
                        prc->right - prc->left, prc->bottom - prc->top,
                        bRepaint);
}

VOID Print(HDC hDC, UINT nPRF_) const
{
    assert(::IsWindow(Handle()));
    SendMessageDx(WM_PRINT, (WPARAM)hDC, (LPARAM)nPRF_);
}

VOID PrintClient(HDC hDC, UINT nPRF_) const
{
    assert(::IsWindow(Handle()));
    SendMessageDx(WM_PRINTCLIENT, (WPARAM)hDC, (LPARAM)nPRF_);
}

BOOL RedrawWindow(const RECT *prcUpdate = NULL, HRGN hRgnUpdate = NULL,
    UINT nRDW_ = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE)
{
    assert(::IsWindow(Handle()));
    return ::RedrawWindow(Handle(), prcUpdate, hRgnUpdate, nRDW_);
}

INT ReleaseDC(HDC hDC)
{
    assert(::IsWindow(Handle()));
    return ::ReleaseDC(Handle(), hDC);
}

BOOL ScreenToClient(POINT *ppt) const
{
    assert(::IsWindow(Handle()));
    return ::ScreenToClient(Handle(), ppt);
}

BOOL ScreenToClient(RECT *prc) const
{
    assert(::IsWindow(Handle()));
    return ::MapWindowPoints(NULL, Handle(), (LPPOINT)prc, 2);
}

BOOL ScrollWindow(INT dx, INT dy, const RECT *prc = NULL,
                  const RECT *prcClip = NULL)
{
    assert(::IsWindow(Handle()));
    return ::ScrollWindow(Handle(), dx, dy, prc, prcClip);
}

BOOL ScrollWindowEx(INT dx, INT dy, const RECT *prc, const RECT *prcClip,
                    HRGN hRgnUpdate, RECT *prcUpdate, UINT nSW_)
{
    assert(::IsWindow(Handle()));
    return ::ScrollWindowEx(Handle(), dx, dy, prc, prcClip, hRgnUpdate,
                            prcUpdate, nSW_);
}

LRESULT SendDlgItemMessageDx(INT nCtrlID, UINT uMsg,
                             WPARAM wParam = 0, LPARAM lParam = 0)
{
    assert(::IsWindow(Handle()));
    return ::SendDlgItemMessage(Handle(), nCtrlID, uMsg, wParam, lParam);
}

HWND SetActiveWindow()
{
    assert(::IsWindow(Handle()));
    return ::SetActiveWindow(Handle());
}

INT SetDlgCtrlID(INT nID)
{
    assert(::IsWindow(Handle()));
    return SetWindowLong(Handle(), GWL_ID, nID);
}

BOOL SetDlgItemInt(INT nCtrlID, UINT nValue, BOOL bSigned = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetDlgItemInt(Handle(), nCtrlID, nValue, bSigned);
}

BOOL SetDlgItemText(INT nCtrlID, LPCTSTR pszText)
{
    assert(::IsWindow(Handle()));
    return ::SetDlgItemText(Handle(), nCtrlID, pszText);
}

BOOL SetForegroundWindow()
{
    assert(::IsWindow(Handle()));
    return ::SetForegroundWindow(Handle());
}

HWND SetFocus()
{
    assert(::IsWindow(Handle()));
    return ::SetFocus(Handle());
}

VOID SetFontDx(HFONT hFont, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(Handle()));
    SendMessageDx(WM_SETFONT, (WPARAM)hFont, bRedraw);
}

HICON SetIconDx(HICON hIcon, BOOL bBigIcon = TRUE)
{
    assert(::IsWindow(Handle()));
    return (HICON)SendMessageDx(WM_SETICON,
        (bBigIcon ? ICON_BIG : ICON_SMALL), (LPARAM)hIcon);
}

BOOL SetMenu(HMENU hMenu)
{
    assert(::IsWindow(Handle()));
    return ::SetMenu(Handle(), hMenu);
}

HWND SetParent(HWND hwndParent)
{
    assert(::IsWindow(Handle()));
    return ::SetParent(Handle(), hwndParent);
}

void SetRedrawDx(BOOL fRedraw)
{
    SendMessageDx(WM_SETREDRAW, fRedraw);
}

INT SetScrollInfo(INT nSB_, SCROLLINFO *pInfo, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetScrollInfo(Handle(), nSB_, pInfo, bRedraw);
}

INT SetScrollPos(INT nSB_, INT nPos, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetScrollPos(Handle(), nSB_, nPos, bRedraw);
}

BOOL SetScrollRange(INT nSB_, INT nMinPos, INT nMaxPos, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetScrollRange(Handle(), nSB_, nMinPos, nMaxPos, bRedraw);
}

UINT_PTR SetTimer(UINT_PTR nEventID, UINT uElapse, TIMERPROC lpTimerFunc = NULL)
{
    assert(::IsWindow(Handle()));
    return ::SetTimer(Handle(), nEventID, uElapse, lpTimerFunc);
}

BOOL SetWindowContextHelpId(DWORD dwContextID)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowContextHelpId(Handle(), dwContextID);
}

BOOL SetWindowPlacement(const WINDOWPLACEMENT *pwndpl)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowPlacement(Handle(), pwndpl);
}

BOOL SetWindowPos(HWND hwndInsertAfter, INT x, INT y, INT cx, INT cy,
                  UINT nSWP_)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowPos(Handle(), hwndInsertAfter, x, y, cx, cy, nSWP_);
}

INT SetWindowRgn(HRGN hRgn = NULL, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowRgn(Handle(), hRgn, bRedraw);
}

BOOL SetWindowText(LPCTSTR pszText = NULL)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowText(Handle(), pszText);
}

BOOL ShowCaret()
{
    assert(::IsWindow(Handle()));
    return ::ShowCaret(Handle());
}

BOOL ShowOwnedPopups(BOOL bShow = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::ShowOwnedPopups(Handle(), bShow);
}

BOOL ShowScrollBar(INT nSB_, BOOL bShow = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::ShowScrollBar(Handle(), nSB_, bShow);
}

BOOL ShowWindow(INT nSW_ = SW_SHOWNOACTIVATE)
{
    assert(::IsWindow(Handle()));
    return ::ShowWindow(Handle(), nSW_);
}

BOOL ShowWindowAsync(INT nSW_ = SW_SHOWNOACTIVATE)
{
    assert(::IsWindow(Handle()));
    return ::ShowWindowAsync(Handle(), nSW_);
}

BOOL UnlockWindowUpdate()
{
    return ::LockWindowUpdate(NULL);
}

BOOL UpdateWindow()
{
    assert(::IsWindow(Handle()));
    return ::UpdateWindow(Handle());
}

BOOL ValidateRect(const RECT *prc = NULL)
{
    assert(::IsWindow(Handle()));
    return ::ValidateRect(Handle(), prc);
}

BOOL ValidateRgn(HRGN hRgn = NULL)
{
    assert(::IsWindow(Handle()));
    return ::ValidateRgn(Handle(), hRgn);
}

BOOL WinHelp(LPCTSTR pszHelpFile, UINT nHELP_, ULONG_PTR dwData)
{
    assert(::IsWindow(Handle()));
    return ::WinHelp(Handle(), pszHelpFile, nHELP_, dwData);
}

//////////////////////////////////////////////////////////////////////////////
