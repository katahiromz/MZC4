// MTreeView.hpp -- Win32API treeview wrapper                   -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MTREEVIEW_HPP_
#define MZC4_MTREEVIEW_HPP_     5       /* Version 5 */

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MTreeView : public MWindowBase
{
public:
    MTreeView();
    virtual LPCTSTR GetWndClassNameDx() const;

    BOOL GetItemRect(HTREEITEM hItem, LPRECT prc, BOOL bTextOnly) const;
    UINT GetCount() const;

    UINT GetIndent() const;
    VOID SetIndent(UINT nIndent);

    HIMAGELIST GetImageList(UINT nImageList) const;
    HIMAGELIST SetImageList(HIMAGELIST hImageList, INT nImageListType);

    HTREEITEM GetNextItem(HTREEITEM hItem, UINT nCode) const;
    HTREEITEM GetChildItem(HTREEITEM hItem) const;
    HTREEITEM GetNextSiblingItem(HTREEITEM hItem) const;
    HTREEITEM GetPrevSiblingItem(HTREEITEM hItem) const;
    HTREEITEM GetParentItem(HTREEITEM hItem) const;
    HTREEITEM GetFirstVisibleItem() const;
    HTREEITEM GetNextVisibleItem(HTREEITEM hItem) const;
    HTREEITEM GetPrevVisibleItem(HTREEITEM hItem) const;
    HTREEITEM GetSelectedItem() const;
    HTREEITEM GetDropHilightItem() const;
    HTREEITEM GetRootItem() const;
    BOOL GetItem(TV_ITEM* pItem) const;
    INT GetItemText(HTREEITEM hItem, LPTSTR lpszText, INT nLen) const;
    BOOL GetItemImage(HTREEITEM hItem, INT& nImage, INT& nSelectedImage) const;
    UINT GetItemState(HTREEITEM hItem, UINT nStateMask) const;
    DWORD_PTR GetItemData(HTREEITEM hItem) const;
    BOOL SetItem(TV_ITEM* pItem);
    BOOL SetItem(HTREEITEM hItem, UINT nMask, LPCTSTR lpszItem, INT nImage,
        INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam);
    BOOL SetItemText(HTREEITEM hItem, LPCTSTR lpszItem);
    BOOL SetItemImage(HTREEITEM hItem, INT nImage, INT nSelectedImage);
    BOOL SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask);
    BOOL SetItemData(HTREEITEM hItem, DWORD_PTR dwData);
    BOOL ItemHasChildren(HTREEITEM hItem) const;
    HWND GetEditControl() const;
    UINT GetVisibleCount() const;

    BOOL GetCheck(HTREEITEM hItem) const;
    BOOL SetCheck(HTREEITEM hItem, BOOL fCheck = TRUE);

    HTREEITEM InsertItem(LPTVINSERTSTRUCT lpInsertStruct);
    HTREEITEM InsertItem(LPCTSTR lpszItem, INT nImage, INT nSelectedImage,
        UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent,
        HTREEITEM hInsertAfter);
    HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT,
        HTREEITEM hInsertAfter = TVI_LAST);
    HTREEITEM InsertItem(UINT nMask, LPCTSTR lpszItem, INT nImage,
        INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam,
        HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
    BOOL DeleteItem(HTREEITEM hItem);
    BOOL DeleteAllItems();
    BOOL Expand(HTREEITEM hItem, UINT nCode = TVE_EXPAND);
    BOOL Select(HTREEITEM hItem, UINT nCode);
    BOOL SelectItem(HTREEITEM hItem);
    BOOL SelectDropTarget(HTREEITEM hItem);
    BOOL SelectSetFirstVisible(HTREEITEM hItem);
    HWND EditLabel(HTREEITEM hItem);
    HTREEITEM HitTest(POINT pt, UINT* pTVHT_flags = NULL) const;
    HTREEITEM HitTest(TVHITTESTINFO* pHitTestInfo) const;
    HIMAGELIST CreateDragImage(HTREEITEM hItem);
    BOOL SortChildren(HTREEITEM hItem, BOOL bRecurse = FALSE);
    BOOL EnsureVisible(HTREEITEM hItem);
    BOOL SortChildrenCB(LPTVSORTCB pSort, BOOL bRecurse = FALSE);

#if (_WIN32_IE >= 0x0300)
    HWND GetToolTips() const;
    HWND SetToolTips(HWND hwndTT);
#endif  // (_WIN32_IE >= 0x0300)

#if (_WIN32_IE >= 0x0400)
    COLORREF GetBkColor() const;
    COLORREF SetBkColor(COLORREF clr);

    SHORT GetItemHeight() const;
    SHORT SetItemHeight(SHORT cyHeight);

    COLORREF GetTextColor() const;
    COLORREF SetTextColor(COLORREF clr);

    BOOL SetInsertMark(HTREEITEM hItem, BOOL fAfter = TRUE);
    COLORREF GetInsertMarkColor() const;
    COLORREF SetInsertMarkColor(COLORREF clrNew);

    BOOL GetUnicodeFormat() const;
    BOOL SetUnicodeFormat(BOOL bUnicode = TRUE);
#endif  // (_WIN32_IE >= 0x0400)
};

////////////////////////////////////////////////////////////////////////////

inline MTreeView::MTreeView()
{
}

inline /*virtual*/ LPCTSTR MTreeView::GetWndClassNameDx() const
{
    return WC_TREEVIEW;
}

inline BOOL
MTreeView::GetItemRect(HTREEITEM hItem, LPRECT prc, BOOL bTextOnly) const
{
    *(HTREEITEM*) prc = hItem;
    return (BOOL)SendMessageDx(TVM_GETITEMRECT, (WPARAM)bTextOnly, (LPARAM)prc);
}

inline UINT MTreeView::GetCount() const
{
    return (UINT)SendMessageDx(TVM_GETCOUNT);
}

inline UINT MTreeView::GetIndent() const
{
    return (UINT)SendMessageDx(TVM_GETINDENT);
}

inline VOID MTreeView::SetIndent(UINT nIndent)
{
    SendMessageDx(TVM_SETINDENT, nIndent);
}

inline HIMAGELIST MTreeView::GetImageList(UINT nImageListType) const
{
    return (HIMAGELIST)SendMessageDx(TVM_GETIMAGELIST, (WPARAM)nImageListType);
}

inline HIMAGELIST MTreeView::SetImageList(HIMAGELIST hImageList, INT nImageListType)
{
    return (HIMAGELIST)SendMessageDx(TVM_SETIMAGELIST, (WPARAM)nImageListType, (LPARAM)hImageList);
}

inline HTREEITEM
MTreeView::GetNextItem(HTREEITEM hItem, UINT nCode) const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, nCode, (LPARAM)hItem);
}

inline HTREEITEM MTreeView::GetChildItem(HTREEITEM hItem) const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hItem);
}

inline HTREEITEM MTreeView::GetNextSiblingItem(HTREEITEM hItem) const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem); 
}

inline HTREEITEM MTreeView::GetPrevSiblingItem(HTREEITEM hItem) const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_PREVIOUS, (LPARAM)hItem);
}

inline HTREEITEM MTreeView::GetParentItem(HTREEITEM hItem) const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_PARENT, (LPARAM)hItem); 
}

inline HTREEITEM MTreeView::GetFirstVisibleItem() const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_FIRSTVISIBLE);
}

inline HTREEITEM MTreeView::GetNextVisibleItem(HTREEITEM hItem) const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_NEXTVISIBLE, (LPARAM)hItem);
}

inline HTREEITEM MTreeView::GetPrevVisibleItem(HTREEITEM hItem) const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_PREVIOUSVISIBLE, (LPARAM)hItem);
}

inline HTREEITEM MTreeView::GetSelectedItem() const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_CARET);
}

inline HTREEITEM MTreeView::GetDropHilightItem() const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_DROPHILITE);
}

inline HTREEITEM MTreeView::GetRootItem() const
{
    return (HTREEITEM)SendMessageDx(TVM_GETNEXTITEM, TVGN_ROOT);
}

inline BOOL MTreeView::GetItem(TV_ITEM* pItem) const
{
    return (BOOL)SendMessageDx(TVM_GETITEM, 0, (LPARAM)pItem);
}

inline BOOL MTreeView::SetItem(TV_ITEM* pItem)
{
    return (BOOL)SendMessageDx(TVM_SETITEM, 0, (LPARAM)pItem);
}

inline BOOL MTreeView::SetItemText(HTREEITEM hItem, LPCTSTR lpszItem)
{
    return SetItem(hItem, TVIF_TEXT, lpszItem, 0, 0, 0, 0, 0);
}

inline BOOL MTreeView::SetItemImage(HTREEITEM hItem, INT nImage, INT nSelectedImage)
{
    return SetItem(hItem, TVIF_IMAGE|TVIF_SELECTEDIMAGE, NULL, nImage, nSelectedImage, 0, 0, 0);
}

inline BOOL MTreeView::SetItemState(
    HTREEITEM hItem, UINT nState, UINT nStateMask)
{
    return SetItem(hItem, TVIF_STATE, NULL, 0, 0, nState, nStateMask, 0);
}

inline BOOL MTreeView::SetItemData(HTREEITEM hItem, DWORD_PTR dwData)
{
    return SetItem(hItem, TVIF_PARAM, NULL, 0, 0, 0, 0, (LPARAM)dwData);
}

inline BOOL MTreeView::ItemHasChildren(HTREEITEM hItem) const
{
    TV_ITEM item;
    ZeroMemory(&item, sizeof(item));
    item.hItem = hItem;
    item.mask = TVIF_CHILDREN;
    SendMessageDx(TVM_GETITEM, 0, (LPARAM)&item);
    return item.cChildren;
}

inline HWND MTreeView::GetEditControl() const
{
    return (HWND)SendMessageDx(TVM_GETEDITCONTROL);
}

inline UINT MTreeView::GetVisibleCount() const
{
    return (UINT)SendMessageDx(TVM_GETVISIBLECOUNT);
}

#if (_WIN32_IE >= 0x0300)
    inline HWND MTreeView::GetToolTips() const
    {
        return (HWND)SendMessageDx(TVM_GETTOOLTIPS);
    }

    inline HWND MTreeView::SetToolTips(HWND hwndTT)
    {
        return (HWND)SendMessageDx(TVM_SETTOOLTIPS, (WPARAM)hwndTT);
    }
#endif  // (_WIN32_IE >= 0x0300)

#if (_WIN32_IE >= 0x0400)
    inline COLORREF MTreeView::GetBkColor() const
    {
        return (COLORREF)SendMessageDx(TVM_GETBKCOLOR);
    }

    inline COLORREF MTreeView::SetBkColor(COLORREF clr)
    {
        return (COLORREF)SendMessageDx(TVM_SETBKCOLOR, 0, (LPARAM)clr);
    }

    inline SHORT MTreeView::GetItemHeight() const
    {
        return (SHORT)SendMessageDx(TVM_GETITEMHEIGHT);
    }

    inline SHORT MTreeView::SetItemHeight(SHORT cyHeight)
    {
        return (SHORT)SendMessageDx(TVM_SETITEMHEIGHT, (WPARAM)cyHeight);
    }

    inline COLORREF MTreeView::GetTextColor() const
    {
        return (COLORREF)SendMessageDx(TVM_GETTEXTCOLOR);
    }

    inline COLORREF MTreeView::SetTextColor(COLORREF clr)
    {
        return (COLORREF)SendMessageDx(TVM_SETTEXTCOLOR, 0, (LPARAM)clr);
    }

    inline BOOL MTreeView::SetInsertMark(HTREEITEM hItem, BOOL fAfter/* = TRUE*/)
    {
        return (BOOL)SendMessageDx(TVM_SETINSERTMARK, (WPARAM)fAfter, (LPARAM)hItem);
    }

    inline COLORREF MTreeView::GetInsertMarkColor() const
    {
        return (COLORREF)SendMessageDx(TVM_GETINSERTMARKCOLOR);
    }

    inline COLORREF MTreeView::SetInsertMarkColor(COLORREF clrNew)
    {
        return (COLORREF)SendMessageDx(TVM_SETINSERTMARKCOLOR, 0, (LPARAM)clrNew);
    }

    inline BOOL MTreeView::GetUnicodeFormat() const
    {
        return (BOOL)SendMessageDx(TVM_GETUNICODEFORMAT);
    }

    inline BOOL MTreeView::SetUnicodeFormat(BOOL bUnicode/* = TRUE*/)
    {
        return (BOOL)SendMessageDx(TVM_SETUNICODEFORMAT, (WPARAM)bUnicode);
    }
#endif  // (_WIN32_IE >= 0x0400)

inline BOOL MTreeView::GetCheck(HTREEITEM hItem) const
{
#if (_WIN32_IE >= 0x0300)
    assert((GetStyleDx() & TVS_CHECKBOXES) != 0);
#endif  // (_WIN32_IE >= 0x0300)
    UINT uRet = GetItemState(hItem, TVIS_STATEIMAGEMASK);
    return (BOOL) ((uRet >> 12) - 1);
}

inline BOOL MTreeView::SetCheck(HTREEITEM hItem, BOOL fCheck/* = TRUE*/)
{
    INT nCheck = (fCheck ? 2 : 1);
    return SetItemState(hItem, (UINT)INDEXTOSTATEIMAGEMASK(nCheck),
                        (UINT)TVIS_STATEIMAGEMASK);
}

inline HTREEITEM MTreeView::InsertItem(LPTVINSERTSTRUCT lpInsertStruct)
{
    return (HTREEITEM)SendMessageDx(TVM_INSERTITEM, 0, (LPARAM)lpInsertStruct);
}

inline HTREEITEM MTreeView::InsertItem(LPCTSTR lpszItem, INT nImage,
    INT nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam,
    HTREEITEM hParent, HTREEITEM hInsertAfter)
{
    return InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE,
        lpszItem, nImage, nSelectedImage, nState, nStateMask, lParam,
        hParent, hInsertAfter);
}

inline HTREEITEM MTreeView::InsertItem(LPCTSTR lpszItem,
    HTREEITEM hParent/* = TVI_ROOT*/, HTREEITEM hInsertAfter/* = TVI_LAST*/)
{
    return InsertItem(TVIF_TEXT, lpszItem, 0, 0, 0, 0, 0, hParent, hInsertAfter);
}

inline BOOL MTreeView::DeleteItem(HTREEITEM hItem)
{
    return (BOOL)SendMessageDx(TVM_DELETEITEM, 0, (LPARAM)hItem);
}

inline BOOL MTreeView::DeleteAllItems()
{
    return (BOOL)SendMessageDx(TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
}

inline BOOL MTreeView::Expand(HTREEITEM hItem, UINT nCode/* = TVE_EXPAND*/)
{
    return (BOOL)SendMessageDx(TVM_EXPAND, nCode, (LPARAM)hItem);
}

inline BOOL MTreeView::Select(HTREEITEM hItem, UINT nCode)
{
    return (BOOL)SendMessageDx(TVM_SELECTITEM, nCode, (LPARAM)hItem);
}

inline BOOL MTreeView::SelectItem(HTREEITEM hItem)
{
    return (BOOL)SendMessageDx(TVM_SELECTITEM, TVGN_CARET, (LPARAM)hItem);
}

inline BOOL MTreeView::SelectDropTarget(HTREEITEM hItem)
{
    return (BOOL)SendMessageDx(TVM_SELECTITEM, TVGN_DROPHILITE, (LPARAM)hItem);
}

inline BOOL MTreeView::SelectSetFirstVisible(HTREEITEM hItem)
{
    return (BOOL)SendMessageDx(TVM_SELECTITEM, TVGN_FIRSTVISIBLE, (LPARAM)hItem);
}

inline HWND MTreeView::EditLabel(HTREEITEM hItem)
{
    return (HWND)SendMessageDx(TVM_EDITLABEL, 0, (LPARAM)hItem);
}

inline HTREEITEM MTreeView::HitTest(TVHITTESTINFO* pHitTestInfo) const
{
    return (HTREEITEM)SendMessageDx(TVM_HITTEST, 0, (LPARAM)pHitTestInfo);
}

inline HIMAGELIST MTreeView::CreateDragImage(HTREEITEM hItem)
{
    return (HIMAGELIST)SendMessageDx(TVM_CREATEDRAGIMAGE, 0, (LPARAM)hItem);
}

inline BOOL MTreeView::SortChildren(HTREEITEM hItem, BOOL bRecurse/* = FALSE*/)
{
    return (BOOL)SendMessageDx(TVM_SORTCHILDREN, (WPARAM)bRecurse, (LPARAM)hItem);
}

inline BOOL MTreeView::EnsureVisible(HTREEITEM hItem)
{
    return (BOOL)SendMessageDx(TVM_ENSUREVISIBLE, 0, (LPARAM)hItem);
}

inline BOOL MTreeView::SortChildrenCB(LPTVSORTCB pSort, BOOL bRecurse/* = FALSE*/)
{
    return (BOOL)SendMessageDx(TVM_SORTCHILDRENCB, (WPARAM)bRecurse, (LPARAM)pSort);
}

inline INT
MTreeView::GetItemText(HTREEITEM hItem, LPTSTR lpszText, INT nLen) const
{
    TV_ITEM item;
    ZeroMemory(&item, sizeof(item));
    item.hItem = hItem;
    item.mask = TVIF_TEXT;
    item.pszText = lpszText;
    item.cchTextMax = nLen;
    return (INT)SendMessageDx(TVM_GETITEM, 0, (LPARAM)&item);
}

inline BOOL
MTreeView::GetItemImage(HTREEITEM hItem, INT& nImage, INT& nSelectedImage) const
{
    TV_ITEM item;
    ZeroMemory(&item, sizeof(item));
    item.hItem = hItem;
    item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE;
    BOOL bRes = (BOOL)SendMessageDx(TVM_GETITEM, 0, (LPARAM)&item);
    if (bRes)
    {
        nImage = item.iImage;
        nSelectedImage = item.iSelectedImage;
    }
    return bRes;
}

inline UINT
MTreeView::GetItemState(HTREEITEM hItem, UINT nStateMask) const
{
    TV_ITEM item;
    ZeroMemory(&item, sizeof(item));
    item.hItem = hItem;
    item.mask = TVIF_STATE;
    item.state = 0;
    item.stateMask = nStateMask;
    SendMessageDx(TVM_GETITEM, 0, (LPARAM)&item);
    return (item.state & nStateMask);
}

inline DWORD_PTR
MTreeView::GetItemData(HTREEITEM hItem) const
{
    TV_ITEM item;
    ZeroMemory(&item, sizeof(item));
    item.hItem = hItem;
    item.mask = TVIF_PARAM;
    BOOL bRet = (BOOL)SendMessageDx(TVM_GETITEM, 0, (LPARAM)&item);
    return (DWORD_PTR)(bRet ? item.lParam : 0);
}

inline BOOL
MTreeView::SetItem(HTREEITEM hItem, UINT nMask,
    LPCTSTR lpszItem, INT nImage, INT nSelectedImage, UINT nState,
    UINT nStateMask, LPARAM lParam)
{
    TV_ITEM item;
    ZeroMemory(&item, sizeof(item));
    item.hItem = hItem;
    item.mask = nMask;
    item.pszText = (LPTSTR) lpszItem;
    item.iImage = nImage;
    item.iSelectedImage = nSelectedImage;
    item.state = nState;
    item.stateMask = nStateMask;
    item.lParam = lParam;
    return (BOOL)SendMessageDx(TVM_SETITEM, 0, (LPARAM)&item);
}

inline HTREEITEM
MTreeView::InsertItem(UINT nMask, LPCTSTR lpszItem,
    INT nImage, INT nSelectedImage, UINT nState, UINT nStateMask,
    LPARAM lParam, HTREEITEM hParent/* = TVI_ROOT*/,
    HTREEITEM hInsertAfter/* = TVI_LAST*/)
{
    TVINSERTSTRUCT tvis;
    ZeroMemory(&tvis, sizeof(tvis));
    tvis.hParent = hParent;
    tvis.hInsertAfter = hInsertAfter;
    tvis.item.mask = nMask;
    tvis.item.pszText = (LPTSTR) lpszItem;
    tvis.item.iImage = nImage;
    tvis.item.iSelectedImage = nSelectedImage;
    tvis.item.state = nState;
    tvis.item.stateMask = nStateMask;
    tvis.item.lParam = lParam;
    return (HTREEITEM)SendMessageDx(TVM_INSERTITEM, 0, (LPARAM)&tvis);
}

inline HTREEITEM MTreeView::HitTest(POINT pt, UINT* pTVHT_flags/* = NULL*/) const
{
    TVHITTESTINFO hti;
    ZeroMemory(&hti, sizeof(hti));
    hti.pt = pt;
    HTREEITEM hTreeItem = (HTREEITEM)SendMessageDx(TVM_HITTEST, 0, (LPARAM)&hti);
    if (pTVHT_flags)
        *pTVHT_flags = hti.flags;
    return hTreeItem;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MTREEVIEW_HPP_
