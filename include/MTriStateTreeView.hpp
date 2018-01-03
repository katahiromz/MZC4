// MTriStateTreeView.hpp -- Win32API three-state treeview     -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MTRISTATETREEVIEW_HPP_
#define MZC4_MTRISTATETREEVIEW_HPP_     6       /* Version 6 */

#include "MTreeView.hpp"

////////////////////////////////////////////////////////////////////////////

#define UM_TRISTATETREEVIEW     (WM_APP + 100)

// width and height of check mark
#ifndef CSTATE_WIDTH
    #define CSTATE_WIDTH  16
    #define CSTATE_HEIGHT 16
#endif

////////////////////////////////////////////////////////////////////////////

class MTriStateTreeView : public MTreeView
{
public:
    // 3 states
    enum {
        CSTATE_UNCHECKED            = 0,
        CSTATE_CHECKED              = 1,
        CSTATE_INDETERMINATE        = 2,
        CSTATE_GRAYED_UNCHECKED     = 3,  // for future use
        CSTATE_GRAYED_CHECKED       = 4,  // for future use
        CSTATE_GRAYED_INDETERMINATE = 5   // for future use
    };
    MTriStateTreeView();
    virtual ~MTriStateTreeView();

    // Call me. Please use "3statechecks.bmp" for nBitmapResourceID.
    BOOL InitStateImageList(INT nBitmapResourceID);

    // Call me from parent's WM_NOTIFY.
    LRESULT OnNotifyFromParent(HWND hwnd, int idFrom, LPNMHDR pnmhdr);

    BOOL IsValidCheckState(INT nState) const;
    INT GetCheckState(HTREEITEM hItem);

    void InternalCheck(HTREEITEM hItem, INT nNewState = CSTATE_CHECKED);
    void SetCheckState(HTREEITEM hItem, INT nNewState = CSTATE_CHECKED);

    virtual INT GetNextCheckState(HTREEITEM hItem, INT nState) const;

protected:
    HIMAGELIST m_himl;
    void ChangeParent(HTREEITEM hParent);
    void ChangeItemState(HTREEITEM hItem, INT nNewState);
    LRESULT OnTriStateTreeViewClick(HWND hwnd, WPARAM wParam, LPARAM lParam);
    INT StripCheckState(INT nState) const;

    virtual LRESULT CALLBACK
    WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

////////////////////////////////////////////////////////////////////////////

inline MTriStateTreeView::MTriStateTreeView() : m_himl(NULL)
{
}

inline MTriStateTreeView::~MTriStateTreeView()
{
    if (m_himl)
    {
        ImageList_Destroy(m_himl);
        m_himl = NULL;
    }
}

inline BOOL MTriStateTreeView::IsValidCheckState(INT nState) const
{
    return 0 <= nState && nState < CSTATE_GRAYED_INDETERMINATE;
}

inline INT MTriStateTreeView::GetCheckState(HTREEITEM hItem)
{
    LRESULT res = SendMessageDx(TVM_GETITEMSTATE, (WPARAM)hItem, TVIS_STATEIMAGEMASK);
    INT nState = (UINT(res) >> 12) - 1;
    assert(IsValidCheckState(nState));
    return nState;
}

inline INT MTriStateTreeView::StripCheckState(INT nState) const
{
    if (nState < CSTATE_GRAYED_UNCHECKED)
        return nState;
    return nState - CSTATE_GRAYED_UNCHECKED;
}

inline INT MTriStateTreeView::GetNextCheckState(HTREEITEM hItem, INT nState) const
{
    assert(IsValidCheckState(nState));
    if (nState == CSTATE_UNCHECKED)
    {
        return CSTATE_CHECKED;
    }
    else
    {
        return CSTATE_UNCHECKED;
    }
}

inline BOOL MTriStateTreeView::InitStateImageList(INT nBitmapResourceID)
{
    assert(IsWindow(m_hwnd));

    ModifyStyleDx(0, TVS_CHECKBOXES);

    if (m_himl)
    {
        ImageList_Destroy(m_himl);
        m_himl = NULL;
    }

    m_himl = ImageList_LoadBitmap(
        GetModuleHandle(NULL), MAKEINTRESOURCE(nBitmapResourceID),
        CSTATE_WIDTH, 0, RGB(255, 0, 255));
    SetImageList(m_himl, TVSIL_STATE);
    if (m_himl == NULL)
    {
        DebugPrintDx(TEXT("nBitmapResource:%d is not a valid resource bitmap!\n"));
    }

    return m_himl != NULL;
}

inline void MTriStateTreeView::InternalCheck(HTREEITEM hItem, INT nNewState)
{
    assert(IsValidCheckState(nNewState));
    TV_ITEM item = {0};
    item.mask = TVIF_HANDLE | TVIF_STATE;
    item.hItem = hItem;
    item.state = INDEXTOSTATEIMAGEMASK(nNewState + 1);
    item.stateMask = TVIS_STATEIMAGEMASK;
    SetItem(&item);
}

inline void MTriStateTreeView::SetCheckState(HTREEITEM hItem, INT nNewState)
{
    InternalCheck(hItem, nNewState);

    HTREEITEM hChildItem = GetChildItem(hItem);
    while (hChildItem)
    {
        SetCheckState(hChildItem, nNewState);

        hChildItem = GetNextSiblingItem(hChildItem);
    }
}

inline void MTriStateTreeView::ChangeParent(HTREEITEM hParent)
{
    while (hParent)
    {
        HTREEITEM hItem = GetChildItem(hParent);
        if (hItem)
        {
            INT nState = GetCheckState(hItem);
            while (hItem)
            {
                INT nAnotherState = GetCheckState(hItem);
                if (nAnotherState != nState)
                {
                    nState = CSTATE_INDETERMINATE;
                    break;
                }
                hItem = GetNextSiblingItem(hItem);
            }
            InternalCheck(hParent, nState);
        }
        hParent = GetParentItem(hParent);
    }
}

inline void MTriStateTreeView::ChangeItemState(HTREEITEM hItem, INT nNewState)
{
    assert(IsValidCheckState(nNewState));
    SetCheckState(hItem, nNewState);

    HTREEITEM hParent = GetParentItem(hItem);
    ChangeParent(hParent);
}

inline LRESULT CALLBACK
MTriStateTreeView::WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        DO_MESSAGE(UM_TRISTATETREEVIEW, OnTriStateTreeViewClick);
    }
    return DefaultProcDx(hwnd, uMsg, wParam, lParam);
}

inline LRESULT
MTriStateTreeView::OnTriStateTreeViewClick(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    HTREEITEM hItem = HTREEITEM(wParam);
    INT nState = INT(lParam);
    nState = GetNextCheckState(hItem, nState);
    assert(IsValidCheckState(nState));
    ChangeItemState(hItem, nState);
}

inline LRESULT
MTriStateTreeView::OnNotifyFromParent(HWND hwnd, int idFrom, LPNMHDR pnmhdr)
{
    switch (pnmhdr->code)
    {
    case NM_CLICK:
        {
            TV_HITTESTINFO ht = { 0 };

            DWORD dwPos = GetMessagePos();
            ht.pt.x = GET_X_LPARAM(dwPos);
            ht.pt.y = GET_Y_LPARAM(dwPos);
            ScreenToClient(m_hwnd, &ht.pt);

            HTREEITEM hItem = HitTest(&ht);
            if (hItem)
            {
                SelectItem(hItem);
                if (ht.flags & TVHT_ONITEMSTATEICON)
                {
                    INT nPreState = GetCheckState(hItem);
                    PostMessageDx(UM_TRISTATETREEVIEW, (WPARAM)ht.hItem, nPreState);
                }
            }
        }
        break;
    case TVN_KEYDOWN:
        if (((LPNMTVKEYDOWN)pnmhdr)->wVKey == VK_SPACE)
        {
            HTREEITEM hItem = GetSelectedItem();
            INT nPreState = GetCheckState(hItem);
            PostMessageDx(UM_TRISTATETREEVIEW, (WPARAM)hItem, nPreState);
            break;
        }
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MTRISTATETREEVIEW_HPP_
