// MScrollView.hpp -- MZC4 scroll view                          -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////
// MScrollView provides a scrollable area in the parent window that
// contains some scrolled child windows.

#ifndef MZC4_MSCROLLVIEW_HPP_
#define MZC4_MSCROLLVIEW_HPP_       2       /* Version 2 */

class MScrollView;
struct MScrollCtrlInfo;

////////////////////////////////////////////////////////////////////////////

#include "MPointSizeRect.hpp"   // for MPoint, MSize, MRect
#include "MScrollBar.hpp"       // for MScrollBar

#include <vector>               // for std::vector

////////////////////////////////////////////////////////////////////////////

struct MScrollCtrlInfo
{
    HWND    m_hwndCtrl;
    MRect   m_rcCtrl;

    MScrollCtrlInfo();
    MScrollCtrlInfo(HWND hwndCtrl);
    MScrollCtrlInfo(HWND hwndCtrl, const MRect& rcCtrl);
    MScrollCtrlInfo(HWND hwndCtrl, const MPoint& ptCtrl, const MSize& sizCtrl);
};

////////////////////////////////////////////////////////////////////////////

class MScrollView
{
public:
    MScrollView();
    MScrollView(HWND hwndParent);
    virtual ~MScrollView();

    // parent
    HWND GetParent() const;
    void SetParent(HWND hwndParent);

    // scroll bar control
    HWND GetHScrollBar() const;
    VOID SetHScrollBar(HWND hHScrollBar);
    HWND GetVScrollBar() const;
    VOID SetVScrollBar(HWND hVScrollBar);

    // parent scroll bars
    void ShowScrollBars(BOOL fHScroll, BOOL fVScroll);

    // add/set control info
    void AddCtrlInfo(HWND hwndCtrl);
    void AddCtrlInfo(HWND hwndCtrl, const MRect& rcCtrl);
    void AddCtrlInfo(HWND hwndCtrl, const MPoint& ptCtrl, const MSize& sizCtrl);
    void SetCtrlInfo(HWND hwndCtrl, const MRect& rcCtrl);
    void SetCtrlInfo(HWND hwndCtrl, const MPoint& ptCtrl, const MSize& sizCtrl);
    void RemoveCtrlInfo(HWND hwndCtrl);
    void AddCtrlInfo(UINT idCtrl);
    void AddCtrlInfo(UINT idCtrl, const MRect& rcCtrl);
    void AddCtrlInfo(UINT idCtrl, const MPoint& ptCtrl, const MSize& sizCtrl);
    void SetCtrlInfo(UINT idCtrl, const MRect& rcCtrl);
    void SetCtrlInfo(UINT idCtrl, const MPoint& ptCtrl, const MSize& sizCtrl);
    void RemoveCtrlInfo(UINT idCtrl);

    bool empty() const;
    void clear();
    size_t size() const;

    // find control info
          MScrollCtrlInfo* FindCtrlInfo(HWND hwndCtrl);
    const MScrollCtrlInfo* FindCtrlInfo(HWND hwndCtrl) const;

    // scroll pos
          MPoint& ScrollPos();
    const MPoint& ScrollPos() const;
    void OffsetScrollPos(INT dx, INT dy);
    void OffsetScrollPos(const MPoint& pt);
    void ResetScrollPos();

    // extent
          MSize& Extent();
    const MSize& Extent() const;
    void SetExtentForAllCtrls();

    // ensure visible
    void EnsureCtrlVisible(HWND hwndCtrl, bool update_all = true);

    // update
    void UpdateScrollInfo();
    void UpdateCtrlsPos();
    void UpdateAll();

    // NOTE: Call MScrollView::HScroll on parent's WM_HSCROLL.
    void HScroll(INT nSB_, INT nPos);
    // NOTE: Call MScrollView::VScroll on parent's WM_VSCROLL.
    void VScroll(INT nSB_, INT nPos);

          MScrollCtrlInfo& operator[](size_t index);
    const MScrollCtrlInfo& operator[](size_t index) const;

    // scroll info
    BOOL GetHScrollInfo(LPSCROLLINFO psi) const;
    BOOL GetVScrollInfo(LPSCROLLINFO psi) const;
    BOOL SetHScrollInfo(const SCROLLINFO *psi, BOOL bRedraw = TRUE);
    BOOL SetVScrollInfo(const SCROLLINFO *psi, BOOL bRedraw = TRUE);

    // scroll position
    INT  GetHScrollPos() const;
    void SetHScrollPos(INT nPos, BOOL bRedraw = TRUE);
    INT  GetVScrollPos() const;
    void SetVScrollPos(INT nPos, BOOL bRedraw = TRUE);

    virtual void GetClientRect(LPRECT prcClient) const;

protected:
    HWND        m_hwndParent;
    MPoint      m_ptScrollPos;
    MSize       m_sizExtent;
    std::vector<MScrollCtrlInfo> m_vecInfo;
    HWND        m_h_scroll_bar;
    HWND        m_v_scroll_bar;

    BOOL HasChildStyle(HWND hwnd) const;

private:
    // NOTE: MScrollView is not copyable.
    MScrollView(const MScrollView&);
    MScrollView& operator=(const MScrollView&);
};

////////////////////////////////////////////////////////////////////////////

inline MScrollCtrlInfo::MScrollCtrlInfo()
{
}

inline MScrollCtrlInfo::MScrollCtrlInfo(HWND hwndCtrl) :
    m_hwndCtrl(hwndCtrl)
{
}

inline
MScrollCtrlInfo::MScrollCtrlInfo(HWND hwndCtrl, const MRect& rcCtrl) :
    m_hwndCtrl(hwndCtrl), m_rcCtrl(rcCtrl)
{
}

inline MScrollCtrlInfo::MScrollCtrlInfo(
    HWND hwndCtrl, const MPoint& ptCtrl, const MSize& sizCtrl) :
    m_hwndCtrl(hwndCtrl), m_rcCtrl(ptCtrl, sizCtrl)
{
}

////////////////////////////////////////////////////////////////////////////

inline MScrollView::MScrollView() : m_hwndParent(NULL)
{
}

inline MScrollView::MScrollView(HWND hwndParent) : m_hwndParent(NULL)
{
    MScrollView::SetParent(hwndParent);
}

inline /*virtual*/ MScrollView::~MScrollView()
{
}

inline HWND MScrollView::GetParent() const
{
    return m_hwndParent;
}

inline void MScrollView::SetParent(HWND hwndParent)
{
    assert(::IsWindow(hwndParent));
    m_hwndParent = hwndParent;
    DWORD style = ::GetWindowLong(m_hwndParent, GWL_STYLE);
    style |= WS_CLIPCHILDREN;
    ::SetWindowLong(m_hwndParent, GWL_STYLE, style);
}

inline HWND MScrollView::GetHScrollBar() const
{
    return m_h_scroll_bar;
}

inline VOID MScrollView::SetHScrollBar(HWND hHScrollBar)
{
    m_h_scroll_bar = hHScrollBar;
}

inline HWND MScrollView::GetVScrollBar() const
{
    return m_v_scroll_bar;
}

inline VOID MScrollView::SetVScrollBar(HWND hVScrollBar)
{
    m_v_scroll_bar = hVScrollBar;
}

inline void
MScrollView::ShowScrollBars(BOOL fHScroll, BOOL fVScroll)
{
    if (::IsWindow(m_h_scroll_bar))
        ::ShowScrollBar(m_h_scroll_bar, SB_CTL, fHScroll);
    else
        ::ShowScrollBar(m_hwndParent, SB_HORZ, fHScroll);

    if (::IsWindow(m_v_scroll_bar))
        ::ShowScrollBar(m_v_scroll_bar, SB_CTL, fHScroll);
    else
        ::ShowScrollBar(m_hwndParent, SB_VERT, fVScroll);
}

inline void MScrollView::AddCtrlInfo(HWND hwndCtrl)
{
    assert(::IsWindow(hwndCtrl));
    assert(HasChildStyle(hwndCtrl));

#if CXX11
    m_vecInfo.emplace_back(hwndCtrl);
#else
    MScrollCtrlInfo info(hwndCtrl);
    m_vecInfo.push_back(info);
#endif
}

inline void MScrollView::AddCtrlInfo(HWND hwndCtrl, const MRect& rcCtrl)
{
    assert(::IsWindow(hwndCtrl));
    assert(HasChildStyle(hwndCtrl));
    assert(rcCtrl.left >= 0);
    assert(rcCtrl.top >= 0);
#if CXX11
    m_vecInfo.emplace_back(hwndCtrl, rcCtrl);
#else
    MScrollCtrlInfo info(hwndCtrl, rcCtrl);
    m_vecInfo.push_back(info);
#endif
}

inline void MScrollView::AddCtrlInfo(
    HWND hwndCtrl, const MPoint& ptCtrl, const MSize& sizCtrl)
{
    assert(::IsWindow(hwndCtrl));
    assert(HasChildStyle(hwndCtrl));
    assert(ptCtrl.x >= 0);
    assert(ptCtrl.y >= 0);
#if CXX11
    m_vecInfo.emplace_back(hwndCtrl, ptCtrl, sizCtrl);
#else
    MScrollCtrlInfo info(hwndCtrl, ptCtrl, sizCtrl);
    m_vecInfo.push_back(info);
#endif
}

inline MSize& MScrollView::Extent()
{
    return m_sizExtent;
}

inline const MSize& MScrollView::Extent() const
{
    return m_sizExtent;
}

inline MPoint& MScrollView::ScrollPos()
{
    return m_ptScrollPos;
}

inline const MPoint& MScrollView::ScrollPos() const
{
    return m_ptScrollPos;
}

inline void MScrollView::OffsetScrollPos(INT dx, INT dy)
{
    m_ptScrollPos.Offset(dx, dy);
}

inline void MScrollView::OffsetScrollPos(const MPoint& pt)
{
    m_ptScrollPos.Offset(pt);
}

inline BOOL MScrollView::HasChildStyle(HWND hwnd) const
{
    return (::GetWindowLong(hwnd, GWL_STYLE) & WS_CHILD);
}

inline bool MScrollView::empty() const
{
    return m_vecInfo.empty();
}

inline void MScrollView::clear()
{
    m_vecInfo.clear();
}

inline size_t MScrollView::size() const
{
    return m_vecInfo.size();
}

inline void MScrollView::UpdateAll()
{
    UpdateScrollInfo();
    UpdateCtrlsPos();
}

inline void MScrollView::AddCtrlInfo(UINT idCtrl)
{
    AddCtrlInfo(::GetDlgItem(m_hwndParent, idCtrl));
}

inline void MScrollView::AddCtrlInfo(UINT idCtrl, const MRect& rcCtrl)
{
    AddCtrlInfo(::GetDlgItem(m_hwndParent, idCtrl), rcCtrl);
}

inline void MScrollView::AddCtrlInfo(
    UINT idCtrl, const MPoint& ptCtrl, const MSize& sizCtrl)
{
    AddCtrlInfo(::GetDlgItem(m_hwndParent, idCtrl), ptCtrl, sizCtrl);
}

inline void MScrollView::SetCtrlInfo(UINT idCtrl, const MRect& rcCtrl)
{
    SetCtrlInfo(::GetDlgItem(m_hwndParent, idCtrl), rcCtrl);
}

inline void MScrollView::SetCtrlInfo(
    UINT idCtrl, const MPoint& ptCtrl, const MSize& sizCtrl)
{
    SetCtrlInfo(::GetDlgItem(m_hwndParent, idCtrl), ptCtrl, sizCtrl);
}

inline void MScrollView::RemoveCtrlInfo(UINT idCtrl)
{
    RemoveCtrlInfo(::GetDlgItem(m_hwndParent, idCtrl));
}

inline MScrollCtrlInfo& MScrollView::operator[](size_t index)
{
    assert(index < size());
    return m_vecInfo[index];
}

inline const MScrollCtrlInfo& MScrollView::operator[](size_t index) const
{
    assert(index < size());
    return m_vecInfo[index];
}

inline void MScrollView::ResetScrollPos()
{
    ScrollPos() = MPoint();
}

inline INT MScrollView::GetHScrollPos() const
{
    if (::IsWindow(m_h_scroll_bar)) {
        return ::GetScrollPos(m_h_scroll_bar, SB_CTL);
    } else {
        return ::GetScrollPos(m_hwndParent, SB_HORZ);
    }
}

inline void MScrollView::SetHScrollPos(INT nPos, BOOL bRedraw)
{
    if (::IsWindow(m_h_scroll_bar)) {
        ::SetScrollPos(m_h_scroll_bar, SB_CTL, nPos, bRedraw);
    } else {
        ::SetScrollPos(m_hwndParent, SB_HORZ, nPos, bRedraw);
    }
}

inline INT MScrollView::GetVScrollPos() const
{
    if (::IsWindow(m_v_scroll_bar)) {
        return ::GetScrollPos(m_v_scroll_bar, SB_CTL);
    } else {
        return ::GetScrollPos(m_hwndParent, SB_VERT);
    }
}

inline void MScrollView::SetVScrollPos(INT nPos, BOOL bRedraw)
{
    if (::IsWindow(m_v_scroll_bar)) {
        ::SetScrollPos(m_v_scroll_bar, SB_CTL, nPos, bRedraw);
    } else {
        ::SetScrollPos(m_hwndParent, SB_VERT, nPos, bRedraw);
    }
}

inline BOOL MScrollView::GetHScrollInfo(LPSCROLLINFO psi) const
{
    if (::IsWindow(m_h_scroll_bar)) { 
        return ::GetScrollInfo(m_h_scroll_bar, SB_CTL, psi);
    } else {
        return ::GetScrollInfo(m_hwndParent, SB_HORZ, psi);
    }
}

inline BOOL MScrollView::GetVScrollInfo(LPSCROLLINFO psi) const
{
    if (::IsWindow(m_v_scroll_bar)) { 
        return ::GetScrollInfo(m_v_scroll_bar, SB_CTL, psi);
    } else {
        return ::GetScrollInfo(m_hwndParent, SB_VERT, psi);
    }
}

inline BOOL
MScrollView::SetHScrollInfo(const SCROLLINFO *psi, BOOL bRedraw)
{
    if (::IsWindow(m_h_scroll_bar)) { 
        return ::SetScrollInfo(m_h_scroll_bar, SB_CTL, psi, bRedraw);
    } else {
        return ::SetScrollInfo(m_hwndParent, SB_HORZ, psi, bRedraw);
    }
}

inline BOOL
MScrollView::SetVScrollInfo(const SCROLLINFO *psi, BOOL bRedraw)
{
    if (::IsWindow(m_v_scroll_bar)) { 
        return ::SetScrollInfo(m_v_scroll_bar, SB_CTL, psi, bRedraw);
    } else {
        return ::SetScrollInfo(m_hwndParent, SB_VERT, psi, bRedraw);
    }
}

inline void MScrollView::SetCtrlInfo(HWND hwndCtrl, const MRect& rcCtrl)
{
    assert(::IsWindow(hwndCtrl));
    assert(HasChildStyle(hwndCtrl));
    assert(rcCtrl.left >= 0);
    assert(rcCtrl.top >= 0);
    MScrollCtrlInfo* info = FindCtrlInfo(hwndCtrl);
    if (info)
        info->m_rcCtrl = rcCtrl;
    else
        AddCtrlInfo(hwndCtrl, rcCtrl);
}

inline void
MScrollView::SetCtrlInfo(
    HWND hwndCtrl, const MPoint& ptCtrl, const MSize& sizCtrl)
{
    assert(::IsWindow(hwndCtrl));
    assert(HasChildStyle(hwndCtrl));
    assert(ptCtrl.x >= 0);
    assert(ptCtrl.y >= 0);
    MScrollCtrlInfo* info = FindCtrlInfo(hwndCtrl);
    if (info)
        info->m_rcCtrl = MRect(ptCtrl, sizCtrl);
    else
        AddCtrlInfo(hwndCtrl, ptCtrl, sizCtrl);
}

inline MScrollCtrlInfo*
MScrollView::FindCtrlInfo(HWND hwndCtrl)
{
    assert(::IsWindow(hwndCtrl));
    assert(HasChildStyle(hwndCtrl));
    size_t siz = size();
    for (size_t i = 0; i < siz; ++i)
    {
        if (m_vecInfo[i].m_hwndCtrl == hwndCtrl)
            return &m_vecInfo[i];
    }
    return NULL;
}

inline const MScrollCtrlInfo*
MScrollView::FindCtrlInfo(HWND hwndCtrl) const
{
    assert(::IsWindow(hwndCtrl));
    assert(HasChildStyle(hwndCtrl));
    size_t siz = size();
    for (size_t i = 0; i < siz; ++i)
    {
        if (m_vecInfo[i].m_hwndCtrl == hwndCtrl)
            return &m_vecInfo[i];
    }
    return NULL;
}

inline void MScrollView::RemoveCtrlInfo(HWND hwndCtrl)
{
    assert(::IsWindow(hwndCtrl));
    assert(HasChildStyle(hwndCtrl));
    std::vector<MScrollCtrlInfo>::iterator it, end = m_vecInfo.end();
    for (it = m_vecInfo.begin(); it != end; ++it)
    {
        if (it->m_hwndCtrl == hwndCtrl)
        {
            m_vecInfo.erase(it);
            break;
        }
    }
}

inline /*virtual*/ void MScrollView::GetClientRect(LPRECT prcClient) const
{
    assert(prcClient);
    ::GetClientRect(m_hwndParent, prcClient);
}

// ensure visible
inline void
MScrollView::EnsureCtrlVisible(HWND hwndCtrl, bool update_all/* = true*/)
{
    MRect rcClient;
    MScrollView::GetClientRect(&rcClient);

    const INT siz = static_cast<INT>(size());
    for (INT i = 0; i < siz; ++i)
    {
        if (m_vecInfo[i].m_hwndCtrl != hwndCtrl)
            continue;

        if (!::IsWindow(hwndCtrl))
            break;

        MRect& rcCtrl = m_vecInfo[i].m_rcCtrl;
        if (rcCtrl.bottom > m_ptScrollPos.y + rcClient.Height())
        {
            m_ptScrollPos.y = rcCtrl.bottom - rcClient.Height();
        }
        if (rcCtrl.top < m_ptScrollPos.y)
        {
            m_ptScrollPos.y = rcCtrl.top;
        }
        break;
    }
    if (update_all)
        UpdateAll();
}

inline void MScrollView::SetExtentForAllCtrls()
{
    Extent().cx = Extent().cy = 0;
    const INT siz = static_cast<INT>(size());
    for (INT i = 0; i < siz; ++i)
    {
        if (!::IsWindowVisible(m_vecInfo[i].m_hwndCtrl))
            continue;

        MRect& rcCtrl = m_vecInfo[i].m_rcCtrl;
        if (Extent().cx < rcCtrl.right - 1)
            Extent().cx = rcCtrl.right - 1;
        if (Extent().cy < rcCtrl.bottom - 1)
            Extent().cy = rcCtrl.bottom - 1;
    }
}

// TODO: Avoid flickering!
inline void MScrollView::UpdateScrollInfo()
{
    MRect rcClient;
    MScrollView::GetClientRect(&rcClient);

    SCROLLINFO si;

    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL | SIF_DISABLENOSCROLL;
    si.nMin = 0;
    si.nMax = Extent().cx;
    si.nPage = rcClient.Width();
    if (static_cast<UINT>(si.nMax) < si.nPage)
        ScrollPos().x = 0;
    si.nPos = ScrollPos().x;
    SetHScrollInfo(&si, TRUE);

    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL | SIF_DISABLENOSCROLL;
    si.nMin = 0;
    si.nMax = Extent().cy;
    si.nPage = rcClient.Height();
    if (static_cast<UINT>(si.nMax) < si.nPage)
        ScrollPos().y = 0;
    si.nPos = ScrollPos().y;
    SetVScrollInfo(&si, TRUE);

    ::InvalidateRect(m_hwndParent, NULL, TRUE);
}

inline void MScrollView::UpdateCtrlsPos()
{
    const INT siz = static_cast<INT>(size());
    HDWP hDWP = ::BeginDeferWindowPos(siz);
    if (hDWP)
    {
        for (INT i = 0; i < siz; ++i)
        {
            MRect& rcCtrl = m_vecInfo[i].m_rcCtrl;
            ::DeferWindowPos(hDWP, m_vecInfo[i].m_hwndCtrl,
                NULL,
                rcCtrl.left - ScrollPos().x, rcCtrl.top - ScrollPos().y,
                rcCtrl.Width(), rcCtrl.Height(),
                SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOCOPYBITS);
        }
        ::EndDeferWindowPos(hDWP);
    }
}

inline void MScrollView::HScroll(INT nSB_, INT nPos)
{
    SCROLLINFO si;
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    GetHScrollInfo(&si);

    switch (nSB_)
    {
    case SB_TOP:
        SetHScrollPos(0);
        break;

    case SB_BOTTOM:
        SetHScrollPos(si.nMax - si.nPage);
        break;

    case SB_LINELEFT:
        SetHScrollPos(si.nPos - 16);
        break;

    case SB_LINERIGHT:
        SetHScrollPos(si.nPos + 16);
        break;

    case SB_PAGELEFT:
        SetHScrollPos(si.nPos - si.nPage);
        break;

    case SB_PAGERIGHT:
        SetHScrollPos(si.nPos + si.nPage);
        break;

    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        SetHScrollPos(nPos);
        break;
    }

    ScrollPos().x = GetHScrollPos();
    UpdateAll();
}

inline void MScrollView::VScroll(INT nSB_, INT nPos)
{
    SCROLLINFO si;
    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    GetVScrollInfo(&si);

    switch (nSB_)
    {
    case SB_TOP:
        SetVScrollPos(0);
        break;

    case SB_BOTTOM:
        SetVScrollPos(si.nMax - si.nPage);
        break;

    case SB_LINELEFT:
        SetVScrollPos(si.nPos - 16);
        break;

    case SB_LINERIGHT:
        SetVScrollPos(si.nPos + 16);
        break;

    case SB_PAGELEFT:
        SetVScrollPos(si.nPos - si.nPage);
        break;

    case SB_PAGERIGHT:
        SetVScrollPos(si.nPos + si.nPage);
        break;

    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        SetVScrollPos(nPos);
        break;
    }

    ScrollPos().y = GetVScrollPos();
    UpdateAll();
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSCROLLVIEW_HPP_
