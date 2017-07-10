// MListBox.hpp -- Win32API list box wrapper                    -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MLISTBOX_HPP_
#define MZC4_MLISTBOX_HPP_      4   /* Version 4 */

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MListBox : public MWindowBase
{
public:
    MListBox();

    virtual LPCTSTR GetWndClassName() const;

    INT GetCount() const;
    INT GetHorizontalExtent() const;
    VOID SetHorizontalExtent(INT cxExtent);
    BOOL IsEmpty() const;

    INT GetTopIndex() const;
    INT SetTopIndex(INT nIndex);

    LCID GetLocale() const;
    LCID SetLocale(LCID nNewLocale);

    INT InitStorage(INT nItems, UINT nBytes);
    INT ItemFromPoint(POINT pt, BOOL& bOutside) const;

    INT GetCurSel() const;
    INT SetCurSel(INT nSelect);

    INT GetSel(INT nIndex) const;
    INT SetSel(INT nIndex, BOOL bSelect = TRUE);

    INT GetSelCount() const;
    INT GetSelItems(INT nMaxItems, LPINT rgIndex) const;

    INT GetAnchorIndex() const;
    VOID SetAnchorIndex(INT nIndex);

    DWORD GetItemData(INT nIndex) const;
    INT SetItemData(INT nIndex, DWORD dwItemData);

    LPVOID GetItemDataPtr(INT nIndex) const;
    INT SetItemDataPtr(INT nIndex, LPVOID pData);

    INT GetItemRect(INT nIndex, LPRECT prc) const;
    INT GetText(INT nIndex, LPTSTR lpszBuffer) const;
    BOOL GetText(INT nIndex, MString& rString) const;
    INT GetTextLen(INT nIndex) const;

    VOID SetColumnWidth(INT cxWidth);
    BOOL SetTabStops(INT nTabStops, LPINT rgTabStops);
    VOID SetTabStops();
    BOOL SetTabStops(const INT& cxEachStop);

    INT GetItemHeight(INT nIndex) const;
    INT SetItemHeight(INT nIndex, UINT cyItemHeight);
    INT FindStringExact(INT nIndexStart, LPCTSTR lpszFind) const;
    INT GetCaretIndex() const;
    INT SetCaretIndex(INT nIndex, BOOL bScroll = TRUE);

    INT AddString(LPCTSTR lpszItem);
    INT DeleteString(INT nIndex);
    INT InsertString(INT nIndex, LPCTSTR lpszItem);
    VOID ResetContent();
    INT Dir(UINT attr, LPCTSTR lpszWildCard);

    INT FindString(INT nStartAfter, LPCTSTR lpszItem) const;
    INT SelectString(INT nStartAfter, LPCTSTR lpszItem);
    INT SelItemRange(BOOL bSelect, INT nFirstItem, INT nLastItem);
    VOID SelectAll();
    VOID SelectNone();
};

////////////////////////////////////////////////////////////////////////////

inline MListBox::MListBox()
{
}

inline /*virtual*/ LPCTSTR MListBox::GetWndClassName() const
{
    return TEXT("LISTBOX");
}

inline INT MListBox::GetCount() const
{
    return (INT)SendMessageDx(LB_GETCOUNT);
}

inline INT MListBox::GetSel(INT nIndex) const
{
    return (INT)SendMessageDx(LB_GETSEL, (WPARAM)nIndex);
}

inline INT MListBox::SetSel(INT nIndex, BOOL bSelect/* = TRUE*/)
{
    return (INT)SendMessageDx(LB_SETSEL, (WPARAM)bSelect, (LPARAM)nIndex);
}

inline INT MListBox::GetHorizontalExtent() const
{
    return (INT)SendMessageDx(LB_GETHORIZONTALEXTENT);
}

inline VOID MListBox::SetHorizontalExtent(INT cxExtent)
{
    SendMessageDx(LB_SETHORIZONTALEXTENT, (WPARAM)cxExtent);
}

inline BOOL MListBox::IsEmpty() const
{
    return GetCount() == 0;
}

inline INT MListBox::GetTopIndex() const
{
    return (INT)SendMessageDx(LB_GETTOPINDEX);
}

inline INT MListBox::SetTopIndex(INT nIndex)
{
    return (INT)SendMessageDx(LB_SETTOPINDEX, (WPARAM)nIndex);
}

inline LCID MListBox::GetLocale() const
{
    return (LCID)SendMessageDx(LB_GETLOCALE);
}

inline LCID MListBox::SetLocale(LCID nNewLocale)
{
    return (LCID)SendMessageDx(LB_SETLOCALE, (WPARAM)nNewLocale);
}

inline INT MListBox::InitStorage(INT nItems, UINT nBytes)
{
    return (INT)SendMessageDx(LB_INITSTORAGE, (WPARAM)nItems, (LPARAM)nBytes);
}

inline INT MListBox::ItemFromPoint(POINT pt, BOOL& bOutside) const
{
    DWORD dw = (DWORD)SendMessageDx(LB_ITEMFROMPOINT, 0, MAKELPARAM(pt.x, pt.y));
    bOutside = (BOOL) HIWORD(dw);
    return (INT) (SHORT) LOWORD(dw);
}

inline INT MListBox::GetCurSel() const
{
    return (INT)SendMessageDx(LB_GETCURSEL);
}

inline INT MListBox::SetCurSel(INT nSelect)
{
    return (INT)SendMessageDx(LB_SETCURSEL, (WPARAM)nSelect);
}

inline INT MListBox::GetSelCount() const
{
    return (INT)SendMessageDx(LB_GETSELCOUNT);
}

inline INT MListBox::GetSelItems(INT nMaxItems, LPINT rgIndex) const
{
    return (INT)SendMessageDx(LB_GETSELITEMS, (WPARAM)nMaxItems, (LPARAM)rgIndex);
}

inline VOID MListBox::SetAnchorIndex(INT nIndex)
{
    SendMessageDx(LB_SETANCHORINDEX, (WPARAM)nIndex);
}

inline INT MListBox::GetAnchorIndex() const
{
    return (INT)SendMessageDx(LB_GETANCHORINDEX);
}

inline DWORD MListBox::GetItemData(INT nIndex) const
{
    return (DWORD)SendMessageDx(LB_GETITEMDATA, (WPARAM)nIndex);
}

inline INT MListBox::SetItemData(INT nIndex, DWORD dwItemData)
{
    return (INT)SendMessageDx(LB_SETITEMDATA, (WPARAM)nIndex, (LPARAM)dwItemData);
}

inline LPVOID MListBox::GetItemDataPtr(INT nIndex) const
{
    return (LPVOID)SendMessageDx(LB_GETITEMDATA, (WPARAM)nIndex);
}

inline INT MListBox::SetItemDataPtr(INT nIndex, LPVOID pData)
{
    return (INT)SendMessageDx(LB_SETITEMDATA, (WPARAM)nIndex, (LPARAM)pData);
}

inline INT MListBox::GetItemRect(INT nIndex, LPRECT prc) const
{
    return (INT)SendMessageDx(LB_GETITEMRECT, (WPARAM)nIndex, (LPARAM)prc);
}

inline INT MListBox::GetText(INT nIndex, LPTSTR lpszBuffer) const
{
    return (INT)SendMessageDx(LB_GETTEXT, (WPARAM)nIndex, (LPARAM)lpszBuffer);
}

inline INT MListBox::GetTextLen(INT nIndex) const
{
    return (INT)SendMessageDx(LB_GETTEXTLEN, (WPARAM)nIndex);
}

inline VOID MListBox::SetColumnWidth(INT cxWidth)
{
    SendMessageDx(LB_SETCOLUMNWIDTH, (WPARAM)cxWidth);
}

inline BOOL MListBox::SetTabStops(INT nTabStops, LPINT rgTabStops)
{
    return (BOOL)SendMessageDx(LB_SETTABSTOPS, (WPARAM)nTabStops, (LPARAM)rgTabStops);
}

inline VOID MListBox::SetTabStops()
{
    SendMessageDx(LB_SETTABSTOPS);
}

inline BOOL MListBox::SetTabStops(const INT& cxEachStop)
{
    return (BOOL)SendMessageDx(LB_SETTABSTOPS, 1, (LPARAM)&cxEachStop);
}

inline INT MListBox::SetItemHeight(INT nIndex, UINT cyItemHeight)
{
    return (INT)SendMessageDx(LB_SETITEMHEIGHT, (WPARAM)nIndex, (LPARAM)cyItemHeight);
}

inline INT MListBox::GetItemHeight(INT nIndex) const
{
    return (INT)SendMessageDx(LB_GETITEMHEIGHT, (WPARAM)nIndex);
}

inline INT MListBox::FindStringExact(
    INT nIndexStart, LPCTSTR lpszFind) const
{
    return (INT)SendMessageDx(LB_FINDSTRINGEXACT, (WPARAM)nIndexStart, (LPARAM)lpszFind);
}

inline INT MListBox::GetCaretIndex() const
{
    return (INT)SendMessageDx(LB_GETCARETINDEX);
}

inline INT MListBox::SetCaretIndex(INT nIndex, BOOL bScroll/* = TRUE*/)
{
    return (INT)SendMessageDx(LB_SETCARETINDEX, (WPARAM)nIndex, (LPARAM)bScroll);
}

inline INT MListBox::AddString(LPCTSTR lpszItem)
{
    return (INT)SendMessageDx(LB_ADDSTRING, 0, (LPARAM)lpszItem);
}

inline INT MListBox::DeleteString(INT nIndex)
{
    return (INT)SendMessageDx(LB_DELETESTRING, (WPARAM)nIndex);
}

inline INT MListBox::InsertString(INT nIndex, LPCTSTR lpszItem)
{
    return (INT)SendMessageDx(LB_INSERTSTRING, (WPARAM)nIndex, (LPARAM)lpszItem);
}

inline VOID MListBox::ResetContent()
{
    SendMessageDx(LB_RESETCONTENT);
}

inline INT MListBox::Dir(UINT attr, LPCTSTR lpszWildCard)
{
    return (INT)SendMessageDx(LB_DIR, attr, (LPARAM)lpszWildCard);
}

inline INT MListBox::FindString(INT nStartAfter, LPCTSTR lpszItem) const
{
    return (INT)SendMessageDx(LB_FINDSTRING, (WPARAM)nStartAfter, (LPARAM)lpszItem);
}

inline INT MListBox::SelectString(INT nStartAfter, LPCTSTR lpszItem)
{
    return (INT)SendMessageDx(LB_SELECTSTRING, (WPARAM)nStartAfter, (LPARAM)lpszItem);
}

inline INT MListBox::SelItemRange(BOOL bSelect, INT nFirstItem, INT nLastItem)
{
    return (INT)SendMessageDx(LB_SELITEMRANGE, (WPARAM)bSelect, MAKELPARAM(nFirstItem, nLastItem));
}

inline VOID MListBox::SelectAll()
{
    SelItemRange(TRUE, 0, GetCount());
}

inline VOID MListBox::SelectNone()
{
    SelItemRange(FALSE, 0, GetCount());
}

inline BOOL MListBox::GetText(INT nIndex, MString& rString) const
{
    rString.clear();

    INT cch = GetTextLen(nIndex);
    if (cch == LB_ERR)
        return FALSE;

    rString.resize(cch);
    cch = GetText(nIndex, &rString[0]);
    if (cch == LB_ERR)
        rString.clear();

    return cch != LB_ERR;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MLISTBOX_HPP_
