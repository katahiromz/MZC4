// MTriStateTreeView.hpp -- Win32API three-state treeview     -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MTRISTATETREEVIEW_HPP_
#define MZC4_MTRISTATETREEVIEW_HPP_     1       /* Version 1 */

#include "MTreeView.hpp"

////////////////////////////////////////////////////////////////////////////

#define UM_TRISTATETREEVIEW     (WM_USER + 100)
#define TSTV_UNCHECKED      0
#define TSTV_CHECKED        1
#define TSTV_INDETERMINATE  2

////////////////////////////////////////////////////////////////////////////


class MTriStateTreeView : public MTreeView
{
public:
    MTriStateTreeView();
    virtual ~MTriStateTreeView();

    // Call me. Please use "3statechecks.bmp" for nBitmapResourceID.
    BOOL InitStateImageList(INT nBitmapResourceID);

    // Call me from parent's WM_NOTIFY
    LRESULT OnNotifyFromParent(HWND hwnd, int idFrom, LPNMHDR pnmhdr);

    INT GetCheckState(HTREEITEM hItem);

    void InternalCheck(HTREEITEM hItem, INT nNewState);
    void SetCheckState(HTREEITEM hItem, INT nNewState);

protected:
    HIMAGELIST m_himl;
    void ChangeParent(HTREEITEM hParent);
    void ChangeItemState(HTREEITEM hItem, INT nNewState);
    LRESULT OnTriStateTreeViewClick(HWND hwnd, WPARAM wParam, LPARAM lParam);

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

inline INT MTriStateTreeView::GetCheckState(HTREEITEM hItem)
{
    LRESULT res = SendMessageDx(TVM_GETITEMSTATE, (WPARAM)hItem, TVIS_STATEIMAGEMASK);
    return (UINT(res) >> 12) - 1;
}

inline BOOL MTriStateTreeView::InitStateImageList(INT nBitmapResourceID)
{
    assert(IsWindow(m_hwnd));

    if (m_himl)
    {
        ImageList_Destroy(m_himl);
        m_himl = NULL;
    }

    m_himl = ImageList_LoadBitmap(
        GetModuleHandle(NULL), MAKEINTRESOURCE(nBitmapResourceID),
        16, 0, RGB(255, 0, 255));
    TreeView_SetImageList(m_hwnd, m_himl, TVSIL_STATE);
    if (m_himl == NULL)
    {
        DebugPrintDx(TEXT("nBitmapResource:%d is not a valid resource bitmap!\n"));
    }
    SetItemHeight(16);

    ModifyStyleDx(0, TVS_CHECKBOXES);
    return m_himl != NULL;
}

inline void MTriStateTreeView::InternalCheck(HTREEITEM hItem, INT nNewState)
{
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
    if (hParent == NULL)
        return;

    HTREEITEM hItem = GetChildItem(hParent);
    INT nState = GetCheckState(hItem);
    while (hItem)
    {
        INT nAnotherState = GetCheckState(hItem);
        if (nAnotherState != nState)
        {
            nState = TSTV_INDETERMINATE;
            break;
        }

        hItem = GetNextSiblingItem(hItem);
    }

    InternalCheck(hParent, nState);
    hParent = GetParentItem(hParent);
    ChangeParent(hParent);
}

inline void MTriStateTreeView::ChangeItemState(HTREEITEM hItem, INT nNewState)
{
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
    HTREEITEM hItem = (HTREEITEM)wParam;
    INT nPreState = (INT)lParam;
    if (nPreState == TSTV_UNCHECKED)
    {
        ChangeItemState(hItem, TSTV_CHECKED);
    }
    else
    {
        ChangeItemState(hItem, TSTV_UNCHECKED);
    }
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
