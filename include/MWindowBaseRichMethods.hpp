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
    static BOOL AnimateWindow(HWND hwnd, DWORD dwTime, DWORD dwAW_)
    {
        assert(::IsWindow(hwnd));
        return ::AnimateWindow(hwnd, dwTime, dwAW_);
    }
#endif

UINT ArrangeIconicWindows()
{
    assert(::IsWindow(Handle()));
    return ::ArrangeIconicWindows(Handle());
}
static UINT ArrangeIconicWindows(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::ArrangeIconicWindows(hwnd);
}

HDC BeginPaint(PAINTSTRUCT* pPS)
{
    assert(::IsWindow(Handle()));
    assert(pPS);
    return ::BeginPaint(Handle(), pPS);
}
static HDC BeginPaint(HWND hwnd, PAINTSTRUCT* pPS)
{
    assert(::IsWindow(hwnd));
    assert(pPS);
    return ::BeginPaint(hwnd, pPS);
}

BOOL BringWindowToTop()
{
    assert(::IsWindow(Handle()));
    return ::BringWindowToTop(Handle());
}
static BOOL BringWindowToTop(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::BringWindowToTop(hwnd);
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
static BOOL CheckDlgButton(HWND hwnd, INT nButtonID, UINT nBST_)
{
    assert(::IsWindow(hwnd));
    return ::CheckDlgButton(hwnd, nButtonID, nBST_);
}

HWND ChildWindowFromPoint(POINT pt)
{
    assert(Handle() == NULL || ::IsWindow(Handle()));
    return ::ChildWindowFromPoint(Handle(), pt);
}
static HWND ChildWindowFromPoint(HWND hwnd, POINT pt)
{
    assert(hwnd == NULL || ::IsWindow(hwnd));
    return ::ChildWindowFromPoint(hwnd, pt);
}

HWND ChildWindowFromPointEx(POINT pt, UINT nCWP_ = CWP_ALL)
{
    assert(Handle() == NULL || ::IsWindow(Handle()));
    return ::ChildWindowFromPointEx(Handle(), pt, nCWP_);
}
static HWND ChildWindowFromPointEx(HWND hwnd, POINT pt, UINT nCWP_ = CWP_ALL)
{
    assert(hwnd == NULL || ::IsWindow(hwnd));
    return ::ChildWindowFromPointEx(hwnd, pt, nCWP_);
}

BOOL ClientToScreen(LPPOINT ppt) const
{
    assert(::IsWindow(Handle()));
    return ::ClientToScreen(Handle(), ppt);
}
static BOOL ClientToScreen(HWND hwnd, LPPOINT ppt)
{
    assert(::IsWindow(hwnd));
    return ::ClientToScreen(hwnd, ppt);
}

BOOL ClientToScreen(RECT *prc) const
{
    assert(::IsWindow(Handle()));
    return ::MapWindowPoints(Handle(), NULL, (LPPOINT)prc, 2);
}
static BOOL ClientToScreen(HWND hwnd, RECT *prc)
{
    assert(::IsWindow(hwnd));
    return ::MapWindowPoints(hwnd, NULL, (LPPOINT)prc, 2);
}

BOOL CloseWindow()
{
    assert(::IsWindow(Handle()));
    return ::CloseWindow(Handle());
}
static BOOL CloseWindow(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::CloseWindow(hwnd);
}

BOOL CreateCaret(HBITMAP hbm)
{
    assert(::IsWindow(Handle()));
    BITMAP bm;
    ::GetObject(hbm, sizeof(bm), &bm);
    return ::CreateCaret(Handle(), hbm, bm.bmWidth, bm.bmHeight);
}
static BOOL CreateCaret(HWND hwnd, HBITMAP hbm)
{
    assert(::IsWindow(hwnd));
    BITMAP bm;
    ::GetObject(hbm, sizeof(bm), &bm);
    return ::CreateCaret(hwnd, hbm, bm.bmWidth, bm.bmHeight);
}

BOOL CreateCaret(HBITMAP hbm, INT cx, INT cy)
{
    assert(::IsWindow(Handle()));
    return ::CreateCaret(Handle(), hbm, cx, cy);
}
static BOOL CreateCaret(HWND hwnd, HBITMAP hbm, INT cx, INT cy)
{
    assert(::IsWindow(hwnd));
    return ::CreateCaret(hwnd, hbm, cx, cy);
}

BOOL CreateGrayCaret(INT cx, INT cy)
{
    return CreateCaret((HBITMAP)1, cx, cy);
}
static BOOL CreateGrayCaret(HWND hwnd, INT cx, INT cy)
{
    return CreateCaret(hwnd, (HBITMAP)1, cx, cy);
}

BOOL CreateSolidCaret(INT cx, INT cy)
{
    return CreateCaret(NULL, cx, cy);
}
static BOOL CreateSolidCaret(HWND hwnd, INT cx, INT cy)
{
    return CreateCaret(hwnd, NULL, cx, cy);
}

BOOL DestroyWindow()
{
    assert(::IsWindow(Handle()));
    return ::DestroyWindow(Handle());
}
static BOOL DestroyWindow(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::DestroyWindow(hwnd);
}

INT DlgDirList(LPTSTR pPathSpec, INT nListBoxID, INT nPathStaticID, UINT nDDL_ = DDL_DRIVES)
{
    assert(::IsWindow(Handle()));
    return ::DlgDirList(Handle(), pPathSpec, nListBoxID, nPathStaticID, nDDL_);
}
static INT DlgDirList(HWND hwnd, LPTSTR pPathSpec, INT nListBoxID, INT nPathStaticID, UINT nDDL_ = DDL_DRIVES)
{
    assert(::IsWindow(hwnd));
    return ::DlgDirList(hwnd, pPathSpec, nListBoxID, nPathStaticID, nDDL_);
}

INT DlgDirListComboBox(LPTSTR pPathSpec, INT nComboBoxID, INT nPathStaticID, UINT nDDL_ = DDL_DRIVES)
{
    assert(::IsWindow(Handle()));
    return ::DlgDirListComboBox(Handle(), pPathSpec, nComboBoxID, nPathStaticID, nDDL_);
}
static INT DlgDirListComboBox(HWND hwnd, LPTSTR pPathSpec, INT nComboBoxID, INT nPathStaticID, UINT nDDL_ = DDL_DRIVES)
{
    assert(::IsWindow(hwnd));
    return ::DlgDirListComboBox(hwnd, pPathSpec, nComboBoxID, nPathStaticID, nDDL_);
}

BOOL DlgDirSelectEx(LPTSTR pszPath, INT cchPath, INT nListBoxID)
{
    assert(::IsWindow(Handle()));
    return ::DlgDirSelectEx(Handle(), pszPath, cchPath, nListBoxID);
}
static BOOL DlgDirSelectEx(HWND hwnd, LPTSTR pszPath, INT cchPath, INT nListBoxID)
{
    assert(::IsWindow(hwnd));
    return ::DlgDirSelectEx(hwnd, pszPath, cchPath, nListBoxID);
}

BOOL DlgDirSelectComboBoxEx(LPTSTR pszPath, INT cchPath, INT nComboBoxID)
{
    assert(::IsWindow(Handle()));
    return ::DlgDirSelectComboBoxEx(Handle(), pszPath, cchPath, nComboBoxID);
}
static BOOL DlgDirSelectComboBoxEx(HWND hwnd, LPTSTR pszPath, INT cchPath, INT nComboBoxID)
{
    assert(::IsWindow(hwnd));
    return ::DlgDirSelectComboBoxEx(hwnd, pszPath, cchPath, nComboBoxID);
}

VOID DragAcceptFiles(BOOL bAccept = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::DragAcceptFiles(Handle(), bAccept);
}
static VOID DragAcceptFiles(HWND hwnd, BOOL bAccept = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::DragAcceptFiles(hwnd, bAccept);
}

BOOL DragDetect(POINT pt) const
{
    assert(::IsWindow(Handle()));
    return ::DragDetect(Handle(), pt);
}
static BOOL DragDetect(HWND hwnd, POINT pt)
{
    assert(::IsWindow(hwnd));
    return ::DragDetect(hwnd, pt);
}

BOOL DrawAnimatedRects(const RECT *prcFrom, const RECT *prcTo, INT idAni = 0)
{
    assert(::IsWindow(Handle()));
    return ::DrawAnimatedRects(Handle(), idAni, prcFrom, prcTo);
}
static BOOL DrawAnimatedRects(HWND hwnd, const RECT *prcFrom, const RECT *prcTo, INT idAni = 0)
{
    assert(::IsWindow(hwnd));
    return ::DrawAnimatedRects(hwnd, idAni, prcFrom, prcTo);
}

BOOL DrawCaption(HDC hDC, const RECT *prc, UINT nDC_)
{
    assert(::IsWindow(Handle()));
    return ::DrawCaption(Handle(), hDC, prc, nDC_);
}
static BOOL DrawCaption(HWND hwnd, HDC hDC, const RECT *prc, UINT nDC_)
{
    assert(::IsWindow(hwnd));
    return ::DrawCaption(hwnd, hDC, prc, nDC_);
}

BOOL DrawMenuBar()
{
    assert(::IsWindow(Handle()));
    return ::DrawMenuBar(Handle());
}
static BOOL DrawMenuBar(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::DrawMenuBar(hwnd);
}

BOOL EnableScrollBar(UINT nSB_, UINT nESB_ = ESB_ENABLE_BOTH)
{
    assert(::IsWindow(Handle()));
    return ::EnableScrollBar(Handle(), nSB_, nESB_);
}
static BOOL EnableScrollBar(HWND hwnd, UINT nSB_, UINT nESB_ = ESB_ENABLE_BOTH)
{
    assert(::IsWindow(hwnd));
    return ::EnableScrollBar(hwnd, nSB_, nESB_);
}

BOOL EnableScrollBarCtrl(UINT nBarID, BOOL bEnable = TRUE)
{
    assert(::IsWindow(Handle()));
    HWND hwndSB = ::GetDlgItem(Handle(), nBarID);
    return ::EnableScrollBar(hwndSB, SB_CTL,
        (bEnable ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH));
}
static BOOL EnableScrollBarCtrl(HWND hwnd, UINT nBarID, BOOL bEnable = TRUE)
{
    assert(::IsWindow(hwnd));
    HWND hwndSB = ::GetDlgItem(hwnd, nBarID);
    return ::EnableScrollBar(hwndSB, SB_CTL,
        (bEnable ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH));
}

// TODO: EnableToolTips

BOOL EnableWindow(BOOL bEnable = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::EnableWindow(Handle(), bEnable);
}
static BOOL EnableWindow(HWND hwnd, BOOL bEnable = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::EnableWindow(hwnd, bEnable);
}

BOOL EndPaint(const PAINTSTRUCT *pPS)
{
    assert(::IsWindow(Handle()));
    assert(pPS);
    return ::EndPaint(Handle(), pPS);
}
static BOOL EndPaint(HWND hwnd, const PAINTSTRUCT *pPS)
{
    assert(::IsWindow(hwnd));
    assert(pPS);
    return ::EndPaint(hwnd, pPS);
}

// TODO: ExecuteDlgInit(LPCTSTR pszResName)

BOOL FlashWindow(BOOL bInvert)
{
    assert(::IsWindow(Handle()));
    return ::FlashWindow(Handle(), bInvert);
}
static BOOL FlashWindow(HWND hwnd, BOOL bInvert)
{
    assert(::IsWindow(hwnd));
    return ::FlashWindow(hwnd, bInvert);
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
    static BOOL FlashWindowEx(HWND hwnd, DWORD dwFLASHW_, UINT uCount, DWORD dwTimeout)
    {
        assert(::IsWindow(hwnd));
        FLASHWINFO info;
        ZeroMemory(&info, sizeof(info));
        info.cbSize = sizeof(info);
        info.hwnd = hwnd;
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
    static HWND GetAncestor(HWND hwnd, UINT nGA_)
    {
        assert(::IsWindow(hwnd));
        return ::GetAncestor(hwnd, nGA_);
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
static INT GetCheckedRadioButton(HWND hwnd, INT nFirstID, INT nLastID)
{
    assert(::IsWindow(hwnd));
    while (nFirstID < nLastID)
    {
        if (::IsDlgButtonChecked(hwnd, nFirstID) == BST_CHECKED)
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
static BOOL GetClientRect(HWND hwnd, RECT *prc)
{
    assert(::IsWindow(hwnd));
    return ::GetClientRect(hwnd, prc);
}

RECT GetClientRect() const
{
    RECT rc;
    GetClientRect(&rc);
    return rc;
}
static RECT GetClientRect(HWND hwnd)
{
    RECT rc;
    GetClientRect(hwnd, &rc);
    return rc;
}

HDC GetDC()
{
    assert(::IsWindow(Handle()));
    return ::GetDC(Handle());
}
static HDC GetDC(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::GetDC(hwnd);
}

HDC GetDCEx(HRGN hRgnClip, DWORD dwDCX_)
{
    assert(::IsWindow(Handle()));
    return ::GetDCEx(Handle(), hRgnClip, dwDCX_);
}
static HDC GetDCEx(HWND hwnd, HRGN hRgnClip, DWORD dwDCX_)
{
    assert(::IsWindow(hwnd));
    return ::GetDCEx(hwnd, hRgnClip, dwDCX_);
}

INT GetDlgCtrlID() const
{
    assert(::IsWindow(Handle()));
    return ::GetDlgCtrlID(Handle());
}
static INT GetDlgCtrlID(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::GetDlgCtrlID(hwnd);
}

HWND GetDlgItem(INT nID) const
{
    assert(::IsWindow(Handle()));
    return ::GetDlgItem(Handle(), nID);
}
static HWND GetDlgItem(HWND hwnd, INT nID)
{
    assert(::IsWindow(hwnd));
    return ::GetDlgItem(hwnd, nID);
}

UINT GetDlgItemInt(INT nID, BOOL *lpTranslated = NULL, BOOL bSigned = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::GetDlgItemInt(Handle(), nID, lpTranslated, bSigned);
}
static UINT GetDlgItemInt(HWND hwnd, INT nID, BOOL *lpTranslated = NULL, BOOL bSigned = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::GetDlgItemInt(hwnd, nID, lpTranslated, bSigned);
}

INT GetDlgItemText(INT nID, LPTSTR psz, INT cchMax) const
{
    assert(::IsWindow(Handle()));
    return ::GetDlgItemText(Handle(), nID, psz, cchMax);
}
static INT GetDlgItemText(HWND hwnd, INT nID, LPTSTR psz, INT cchMax)
{
    assert(::IsWindow(hwnd));
    return ::GetDlgItemText(hwnd, nID, psz, cchMax);
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
static HWND GetLastActivePopup(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::GetLastActivePopup(hwnd);
}

HMENU GetMenu() const
{
    assert(::IsWindow(Handle()));
    return ::GetMenu(Handle());
}
static HMENU GetMenu(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::GetMenu(hwnd);
}

HWND GetNextDlgGroupItem(HWND hwndCtrl, BOOL bPrevious = FALSE) const
{
    assert(::IsWindow(Handle()));
    return ::GetNextDlgGroupItem(Handle(), hwndCtrl, bPrevious);
}
HWND GetNextDlgGroupItem(HWND hwnd, HWND hwndCtrl, BOOL bPrevious = FALSE)
{
    assert(::IsWindow(hwnd));
    return ::GetNextDlgGroupItem(hwnd, hwndCtrl, bPrevious);
}

HWND GetNextDlgTabItem(HWND hwndCtrl, BOOL bPrevious = FALSE) const
{
    assert(::IsWindow(Handle()));
    return ::GetNextDlgTabItem(Handle(), hwndCtrl, bPrevious);
}
static HWND GetNextDlgTabItem(HWND hwnd, HWND hwndCtrl, BOOL bPrevious = FALSE)
{
    assert(::IsWindow(hwnd));
    return ::GetNextDlgTabItem(hwnd, hwndCtrl, bPrevious);
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
static HWND GetParent(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::GetParent(hwnd);
}

// TODO: GetParentFrame
// TODO: GetParentOwner
// TODO: GetScrollBarCtrl

BOOL GetScrollInfo(INT nSB_, SCROLLINFO *pInfo) const
{
    assert(::IsWindow(Handle()));
    return ::GetScrollInfo(Handle(), nSB_, pInfo);
}
static BOOL GetScrollInfo(HWND hwnd, INT nSB_, SCROLLINFO *pInfo)
{
    assert(::IsWindow(hwnd));
    return ::GetScrollInfo(hwnd, nSB_, pInfo);
}

INT GetScrollPos(INT nSB_) const
{
    assert(::IsWindow(Handle()));
    return ::GetScrollPos(Handle(), nSB_);
}
static INT GetScrollPos(HWND hwnd, INT nSB_)
{
    assert(::IsWindow(hwnd));
    return ::GetScrollPos(hwnd, nSB_);
}

BOOL GetScrollRange(INT nSB_, LPINT pMinPos, LPINT pMaxPos) const
{
    assert(::IsWindow(Handle()));
    return ::GetScrollRange(Handle(), nSB_, pMinPos, pMaxPos);
}
static BOOL GetScrollRange(HWND hwnd, INT nSB_, LPINT pMinPos, LPINT pMaxPos)
{
    assert(::IsWindow(hwnd));
    return ::GetScrollRange(hwnd, nSB_, pMinPos, pMaxPos);
}

HMENU GetSystemMenu(BOOL bRevert = FALSE) const
{
    assert(::IsWindow(Handle()));
    return ::GetSystemMenu(Handle(), bRevert);
}
static HMENU GetSystemMenu(HWND hwnd, BOOL bRevert = FALSE)
{
    assert(::IsWindow(hwnd));
    return ::GetSystemMenu(hwnd, bRevert);
}

HWND GetTopWindow() const
{
    assert(::IsWindow(Handle()));
    return ::GetTopWindow(Handle());
}
static HWND GetTopWindow(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::GetTopWindow(hwnd);
}

BOOL GetUpdateRect(RECT *prc = NULL, BOOL bErase = TRUE) const
{
    assert(::IsWindow(Handle()));
    return ::GetUpdateRect(Handle(), prc, bErase);
}
static BOOL GetUpdateRect(HWND hwnd, RECT *prc = NULL, BOOL bErase = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::GetUpdateRect(hwnd, prc, bErase);
}

INT GetUpdateRgn(HRGN hRgn, BOOL bErase = TRUE) const
{
    assert(::IsWindow(Handle()));
    return ::GetUpdateRgn(Handle(), hRgn, bErase);
}
static INT GetUpdateRgn(HWND hwnd, HRGN hRgn, BOOL bErase = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::GetUpdateRgn(hwnd, hRgn, bErase);
}

HWND GetWindow(UINT nGW_) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindow(Handle(), nGW_);
}
static HWND GetWindow(HWND hwnd, UINT nGW_)
{
    assert(::IsWindow(hwnd));
    return ::GetWindow(hwnd, nGW_);
}

DWORD GetWindowContextHelpId() const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowContextHelpId(Handle());
}
static DWORD GetWindowContextHelpId(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::GetWindowContextHelpId(hwnd);
}

HDC GetWindowDC()
{
    assert(::IsWindow(Handle()));
    return ::GetWindowDC(Handle());
}
static HDC GetWindowDC(HWND hwnd) const
{
    assert(::IsWindow(hwnd));
    return ::GetWindowDC(hwnd);
}

BOOL GetWindowPlacement(WINDOWPLACEMENT *pwndpl) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowPlacement(Handle(), pwndpl);
}
static BOOL GetWindowPlacement(HWND hwnd, WINDOWPLACEMENT *pwndpl)
{
    assert(::IsWindow(hwnd));
    return ::GetWindowPlacement(hwnd, pwndpl);
}

BOOL GetWindowRect(RECT *prc) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowRect(Handle(), prc);
}
static BOOL GetWindowRect(HWND hwnd, RECT *prc)
{
    assert(::IsWindow(hwnd));
    return ::GetWindowRect(hwnd, prc);
}

RECT GetWindowRect() const
{
    RECT rc;
    GetWindowRect(&rc);
    return rc;
}
static RECT GetWindowRect(HWND hwnd)
{
    RECT rc;
    GetWindowRect(hwnd, &rc);
    return rc;
}

INT GetWindowRgn(HRGN hRgn) const
{
    assert(::IsWindow(Handle()));
    return ::GetWindowRgn(Handle(), hRgn);
}
static INT GetWindowRgn(HWND hwnd, HRGN hRgn)
{
    assert(::IsWindow(hwnd));
    return ::GetWindowRgn(hwnd, hRgn);
}

BOOL HideCaret()
{
    assert(::IsWindow(Handle()));
    return ::HideCaret(Handle());
}
static BOOL HideCaret(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::HideCaret(hwnd);
}

BOOL HiliteMenuItem(HMENU hMenu, UINT nItem,
                    UINT nMF_ = MF_BYCOMMAND | MF_HILITE)
{
    assert(::IsWindow(Handle()));
    return ::HiliteMenuItem(Handle(), hMenu, nItem, nMF_);
}
static BOOL
HiliteMenuItem(HWND hwnd, HMENU hMenu, UINT nItem,
               UINT nMF_ = MF_BYCOMMAND | MF_HILITE)
{
    assert(::IsWindow(hwnd));
    return ::HiliteMenuItem(hwnd, hMenu, nItem, nMF_);
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
static BOOL InvalidateRect(HWND hwnd, const RECT *prc, BOOL bErase = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::InvalidateRect(hwnd, prc, bErase);
}

BOOL InvalidateRgn(HRGN hRgn, BOOL bErase = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::InvalidateRgn(Handle(), hRgn, bErase);
}
static BOOL InvalidateRgn(HWND hwnd, HRGN hRgn, BOOL bErase = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::InvalidateRgn(hwnd, hRgn, bErase);
}

BOOL IsChild(HWND hwndChild) const
{
    assert(::IsWindow(Handle()));
    return ::IsChild(Handle(), hwndChild);
}
static BOOL IsChild(HWND hwnd, HWND hwndChild)
{
    assert(::IsWindow(hwnd));
    return ::IsChild(hwnd, hwndChild);
}

UINT IsDlgButtonChecked(INT nID) const
{
    assert(::IsWindow(Handle()));
    return ::IsDlgButtonChecked(Handle(), nID);
}
static UINT IsDlgButtonChecked(HWND hwnd, INT nID)
{
    assert(::IsWindow(hwnd));
    return ::IsDlgButtonChecked(hwnd, nID);
}

BOOL IsIconic() const
{
    assert(::IsWindow(Handle()));
    return ::IsIconic(Handle());
}
static BOOL IsIconic(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::IsIconic(hwnd);
}

BOOL IsWindowEnabled() const
{
    assert(::IsWindow(Handle()));
    return ::IsWindowEnabled(Handle());
}
static BOOL IsWindowEnabled(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::IsWindowEnabled(hwnd);
}

BOOL IsWindowVisible() const
{
    assert(::IsWindow(Handle()));
    return ::IsWindowVisible(Handle());
}
static BOOL IsWindowVisible(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::IsWindowVisible(hwnd);
}

BOOL IsZoomed() const
{
    assert(::IsWindow(Handle()));
    return ::IsZoomed(Handle());
}
static BOOL IsZoomed(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::IsZoomed(hwnd);
}

BOOL KillTimer(UINT_PTR nTimerID)
{
    assert(::IsWindow(Handle()));
    return ::KillTimer(Handle(), nTimerID);
}
static BOOL KillTimer(HWND hwnd, UINT_PTR nTimerID)
{
    assert(::IsWindow(hwnd));
    return ::KillTimer(hwnd, nTimerID);
}

BOOL LockWindowUpdate()
{
    assert(::IsWindow(Handle()));
    return ::LockWindowUpdate(Handle());
}
static BOOL LockWindowUpdate(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::LockWindowUpdate(hwnd);
}

INT MapWindowPoints(HWND hwndTo, LPRECT prc) const
{
    assert(::IsWindow(Handle()));
    return ::MapWindowPoints(Handle(), hwndTo, (LPPOINT)prc, 2);
}
static INT MapWindowPoints(HWND hwnd, HWND hwndTo, LPRECT prc)
{
    assert(::IsWindow(hwnd));
    return ::MapWindowPoints(hwnd, hwndTo, (LPPOINT)prc, 2);
}

INT MapWindowPoints(HWND hwndTo, LPPOINT ppt, UINT cPoints) const
{
    assert(::IsWindow(Handle()));
    return ::MapWindowPoints(Handle(), hwndTo, ppt, cPoints);
}
static INT MapWindowPoints(HWND hwnd, HWND hwndTo, LPPOINT ppt, UINT cPoints) const
{
    assert(::IsWindow(hwnd));
    return ::MapWindowPoints(hwnd, hwndTo, ppt, cPoints);
}

BOOL MoveWindow(INT x, INT y, INT cx, INT cy, BOOL bRepaint = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::MoveWindow(Handle(), x, y, cx, cy, bRepaint);
}
static BOOL MoveWindow(HWND hwnd, INT x, INT y, INT cx, INT cy, BOOL bRepaint = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::MoveWindow(hwnd, x, y, cx, cy, bRepaint);
}

BOOL MoveWindow(const RECT *prc, BOOL bRepaint = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::MoveWindow(Handle(), prc->left, prc->top,
                        prc->right - prc->left, prc->bottom - prc->top,
                        bRepaint);
}
static BOOL MoveWindow(HWND hwnd, const RECT *prc, BOOL bRepaint = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::MoveWindow(hwnd, prc->left, prc->top,
                        prc->right - prc->left, prc->bottom - prc->top,
                        bRepaint);
}

VOID Print(HDC hDC, UINT nPRF_) const
{
    assert(::IsWindow(Handle()));
    SendMessageDx(WM_PRINT, (WPARAM)hDC, (LPARAM)nPRF_);
}
static VOID Print(HWND hwnd, HDC hDC, UINT nPRF_)
{
    assert(::IsWindow(hwnd));
    ::SendMessage(hwnd, WM_PRINT, (WPARAM)hDC, (LPARAM)nPRF_);
}

VOID PrintClient(HDC hDC, UINT nPRF_) const
{
    assert(::IsWindow(Handle()));
    SendMessageDx(WM_PRINTCLIENT, (WPARAM)hDC, (LPARAM)nPRF_);
}
static VOID PrintClient(HWND hwnd, HDC hDC, UINT nPRF_)
{
    assert(::IsWindow(hwnd));
    ::SendMessage(hwnd, WM_PRINTCLIENT, (WPARAM)hDC, (LPARAM)nPRF_);
}

BOOL RedrawWindow(const RECT *prcUpdate = NULL, HRGN hRgnUpdate = NULL,
    UINT nRDW_ = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE)
{
    assert(::IsWindow(Handle()));
    return ::RedrawWindow(Handle(), prcUpdate, hRgnUpdate, nRDW_);
}
static BOOL RedrawWindow(HWND hwnd,
    const RECT *prcUpdate = NULL, HRGN hRgnUpdate = NULL,
    UINT nRDW_ = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE)
{
    assert(::IsWindow(hwnd));
    return ::RedrawWindow(hwnd, prcUpdate, hRgnUpdate, nRDW_);
}

INT ReleaseDC(HDC hDC)
{
    assert(::IsWindow(Handle()));
    return ::ReleaseDC(Handle(), hDC);
}
static INT ReleaseDC(HWND hwnd, HDC hDC)
{
    assert(::IsWindow(hwnd));
    return ::ReleaseDC(hwnd, hDC);
}

BOOL ScreenToClient(POINT *ppt) const
{
    assert(::IsWindow(Handle()));
    return ::ScreenToClient(Handle(), ppt);
}
static BOOL ScreenToClient(HWND hwnd, POINT *ppt)
{
    assert(::IsWindow(hwnd));
    return ::ScreenToClient(hwnd, ppt);
}

BOOL ScreenToClient(RECT *prc) const
{
    assert(::IsWindow(Handle()));
    return ::MapWindowPoints(NULL, Handle(), (LPPOINT)prc, 2);
}
static BOOL ScreenToClient(HWND hwnd, RECT *prc)
{
    assert(::IsWindow(hwnd));
    return ::MapWindowPoints(NULL, hwnd, (LPPOINT)prc, 2);
}

BOOL ScrollWindow(INT dx, INT dy, const RECT *prc = NULL,
                  const RECT *prcClip = NULL)
{
    assert(::IsWindow(Handle()));
    return ::ScrollWindow(Handle(), dx, dy, prc, prcClip);
}
static BOOL
ScrollWindow(HWND hwnd, INT dx, INT dy, const RECT *prc = NULL,
             const RECT *prcClip = NULL)
{
    assert(::IsWindow(hwnd));
    return ::ScrollWindow(hwnd, dx, dy, prc, prcClip);
}

BOOL ScrollWindowEx(INT dx, INT dy, const RECT *prc, const RECT *prcClip,
                    HRGN hRgnUpdate, RECT *prcUpdate, UINT nSW_)
{
    assert(::IsWindow(Handle()));
    return ::ScrollWindowEx(Handle(), dx, dy, prc, prcClip, hRgnUpdate,
                            prcUpdate, nSW_);
}
static BOOL
ScrollWindowEx(HWND hwnd, INT dx, INT dy, const RECT *prc, const RECT *prcClip,
               HRGN hRgnUpdate, RECT *prcUpdate, UINT nSW_)
{
    assert(::IsWindow(hwnd));
    return ::ScrollWindowEx(hwnd, dx, dy, prc, prcClip, hRgnUpdate,
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
static HWND SetActiveWindow(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::SetActiveWindow(hwnd);
}

INT SetDlgCtrlID(INT nID)
{
    assert(::IsWindow(Handle()));
    return SetWindowLong(Handle(), GWL_ID, nID);
}
static INT SetDlgCtrlID(HWND hwnd, INT nID)
{
    assert(::IsWindow(hwnd));
    return SetWindowLong(hwnd, GWL_ID, nID);
}

BOOL SetDlgItemInt(INT nCtrlID, UINT nValue, BOOL bSigned = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetDlgItemInt(Handle(), nCtrlID, nValue, bSigned);
}
static BOOL SetDlgItemInt(HWND hwnd, INT nCtrlID, UINT nValue, BOOL bSigned = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::SetDlgItemInt(hwnd, nCtrlID, nValue, bSigned);
}

BOOL SetDlgItemText(INT nCtrlID, LPCTSTR pszText)
{
    assert(::IsWindow(Handle()));
    return ::SetDlgItemText(Handle(), nCtrlID, pszText);
}
static BOOL SetDlgItemText(HWND hwnd, INT nCtrlID, LPCTSTR pszText)
{
    assert(::IsWindow(hwnd));
    return ::SetDlgItemText(hwnd, nCtrlID, pszText);
}

BOOL SetForegroundWindow()
{
    assert(::IsWindow(Handle()));
    return ::SetForegroundWindow(Handle());
}
static BOOL SetForegroundWindow(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::SetForegroundWindow(hwnd);
}

HWND SetFocus()
{
    assert(::IsWindow(Handle()));
    return ::SetFocus(Handle());
}
static HWND SetFocus(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::SetFocus(hwnd);
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
static BOOL SetMenu(HWND hwnd, HMENU hMenu)
{
    assert(::IsWindow(hwnd));
    return ::SetMenu(hwnd, hMenu);
}

HWND SetParent(HWND hwndParent)
{
    assert(::IsWindow(Handle()));
    return ::SetParent(Handle(), hwndParent);
}
static HWND SetParent(HWND hwnd, HWND hwndParent)
{
    assert(::IsWindow(hwnd));
    return ::SetParent(hwnd, hwndParent);
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
static INT SetScrollInfo(HWND hwnd, INT nSB_, SCROLLINFO *pInfo, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::SetScrollInfo(hwnd, nSB_, pInfo, bRedraw);
}

INT SetScrollPos(INT nSB_, INT nPos, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetScrollPos(Handle(), nSB_, nPos, bRedraw);
}
static INT SetScrollPos(HWND hwnd, INT nSB_, INT nPos, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::SetScrollPos(hwnd, nSB_, nPos, bRedraw);
}

BOOL SetScrollRange(INT nSB_, INT nMinPos, INT nMaxPos, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetScrollRange(Handle(), nSB_, nMinPos, nMaxPos, bRedraw);
}
static BOOL SetScrollRange(HWND hwnd, INT nSB_, INT nMinPos, INT nMaxPos, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::SetScrollRange(hwnd, nSB_, nMinPos, nMaxPos, bRedraw);
}

UINT_PTR SetTimer(UINT_PTR nEventID, UINT uElapse, TIMERPROC lpTimerFunc = NULL)
{
    assert(Handle() == NULL || ::IsWindow(Handle()));
    return ::SetTimer(Handle(), nEventID, uElapse, lpTimerFunc);
}
static UINT_PTR SetTimer(HWND hwnd, UINT_PTR nEventID, UINT uElapse, TIMERPROC lpTimerFunc = NULL)
{
    assert(hwnd == NULL || ::IsWindow(hwnd));
    return ::SetTimer(hwnd, nEventID, uElapse, lpTimerFunc);
}

BOOL SetWindowContextHelpId(DWORD dwContextID)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowContextHelpId(Handle(), dwContextID);
}
static BOOL SetWindowContextHelpId(HWND hwnd, DWORD dwContextID)
{
    assert(::IsWindow(hwnd));
    return ::SetWindowContextHelpId(hwnd, dwContextID);
}

BOOL SetWindowPlacement(const WINDOWPLACEMENT *pwndpl)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowPlacement(Handle(), pwndpl);
}
static BOOL SetWindowPlacement(HWND hwnd, const WINDOWPLACEMENT *pwndpl)
{
    assert(::IsWindow(hwnd));
    return ::SetWindowPlacement(hwnd, pwndpl);
}

BOOL SetWindowPos(HWND hwndInsertAfter, INT x, INT y, INT cx, INT cy,
                  UINT nSWP_)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowPos(Handle(), hwndInsertAfter, x, y, cx, cy, nSWP_);
}
static BOOL
SetWindowPos(HWND hwnd, HWND hwndInsertAfter, INT x, INT y, INT cx, INT cy,
             UINT nSWP_)
{
    assert(::IsWindow(hwnd));
    return ::SetWindowPos(hwnd, hwndInsertAfter, x, y, cx, cy, nSWP_);
}

INT SetWindowRgn(HRGN hRgn = NULL, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::SetWindowRgn(Handle(), hRgn, bRedraw);
}
static INT SetWindowRgn(HWND hwnd, HRGN hRgn = NULL, BOOL bRedraw = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::SetWindowRgn(hwnd, hRgn, bRedraw);
}

BOOL ShowCaret()
{
    assert(::IsWindow(Handle()));
    return ::ShowCaret(Handle());
}
static BOOL ShowCaret(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::ShowCaret(hwnd);
}

BOOL ShowOwnedPopups(BOOL bShow = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::ShowOwnedPopups(Handle(), bShow);
}
static BOOL ShowOwnedPopups(HWND hwnd, BOOL bShow = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::ShowOwnedPopups(hwnd, bShow);
}

BOOL ShowScrollBar(INT nSB_, BOOL bShow = TRUE)
{
    assert(::IsWindow(Handle()));
    return ::ShowScrollBar(Handle(), nSB_, bShow);
}
static BOOL ShowScrollBar(HWND hwnd, INT nSB_, BOOL bShow = TRUE)
{
    assert(::IsWindow(hwnd));
    return ::ShowScrollBar(hwnd, nSB_, bShow);
}

BOOL ShowWindow(INT nSW_ = SW_SHOWNOACTIVATE)
{
    assert(::IsWindow(Handle()));
    return ::ShowWindow(Handle(), nSW_);
}
static BOOL ShowWindow(HWND hwnd, INT nSW_ = SW_SHOWNOACTIVATE)
{
    assert(::IsWindow(hwnd));
    return ::ShowWindow(hwnd, nSW_);
}

BOOL ShowWindowAsync(INT nSW_ = SW_SHOWNOACTIVATE)
{
    assert(::IsWindow(Handle()));
    return ::ShowWindowAsync(Handle(), nSW_);
}
static BOOL ShowWindowAsync(HWND hwnd, INT nSW_ = SW_SHOWNOACTIVATE)
{
    assert(::IsWindow(hwnd));
    return ::ShowWindowAsync(hwnd, nSW_);
}

static BOOL UnlockWindowUpdate()
{
    return ::LockWindowUpdate(NULL);
}

BOOL UpdateWindow()
{
    assert(::IsWindow(Handle()));
    return ::UpdateWindow(Handle());
}
static BOOL UpdateWindow(HWND hwnd)
{
    assert(::IsWindow(hwnd));
    return ::UpdateWindow(hwnd);
}

BOOL ValidateRect(const RECT *prc = NULL)
{
    assert(::IsWindow(Handle()));
    return ::ValidateRect(Handle(), prc);
}
static BOOL ValidateRect(HWND hwnd, const RECT *prc = NULL)
{
    assert(::IsWindow(hwnd));
    return ::ValidateRect(hwnd, prc);
}

BOOL ValidateRgn(HRGN hRgn = NULL)
{
    assert(::IsWindow(Handle()));
    return ::ValidateRgn(Handle(), hRgn);
}
static BOOL ValidateRgn(HWND hwnd, HRGN hRgn = NULL)
{
    assert(::IsWindow(hwnd));
    return ::ValidateRgn(hwnd, hRgn);
}

BOOL WinHelp(LPCTSTR pszHelpFile, UINT nHELP_, ULONG_PTR dwData)
{
    assert(::IsWindow(Handle()));
    return ::WinHelp(Handle(), pszHelpFile, nHELP_, dwData);
}
static BOOL WinHelp(HWND hwnd, LPCTSTR pszHelpFile, UINT nHELP_, ULONG_PTR dwData)
{
    assert(::IsWindow(hwnd));
    return ::WinHelp(hwnd, pszHelpFile, nHELP_, dwData);
}

//////////////////////////////////////////////////////////////////////////////
