// MComboBoxEx.hpp -- Win32API extended combo box wrapper       -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MCOMBOBOXEX_HPP_
#define MZC4_MCOMBOBOXEX_HPP_       2   /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#include "MComboBox.hpp"

#if (_WIN32_IE >= 0x0300)
    class MComboBoxEx : public MComboBox
    {
    public:
        MComboBoxEx();
        virtual LPCTSTR GetWndClassName() const;

        HIMAGELIST GetImageList();
        HIMAGELIST SetImageList(HIMAGELIST hImageList);

        INT InsertItem(const COMBOBOXEXITEM* lpcCBItem);
        INT InsertItem(UINT nMask, INT nIndex, LPCTSTR lpszItem, INT nImage,
            INT nSelImage, INT iIndent, INT iOverlay, LPARAM lParam);
        INT InsertItem(INT nIndex, LPCTSTR lpszItem, INT nImage, INT nSelImage,
            INT iIndent, LPARAM lParam = 0);
        INT AddItem(UINT nMask, LPCTSTR lpszItem, INT nImage, INT nSelImage,
            INT iIndent, INT iOverlay, LPARAM lParam);
        INT AddItem(LPCTSTR lpszItem, INT nImage, INT nSelImage, INT iIndent,
            LPARAM lParam = 0);

        INT DeleteItem(INT nIndex);

        BOOL GetItem(PCOMBOBOXEXITEM pCBItem) const;
        BOOL SetItem(const COMBOBOXEXITEM* lpcCBItem);
        INT SetItem(INT nIndex, UINT nMask, LPCTSTR lpszItem, INT nImage,
            INT nSelImage, INT iIndent, INT iOverlay, LPARAM lParam);
        BOOL GetItemText(INT nIndex, LPTSTR lpszItem, INT nLen) const;
        BOOL SetItemText(INT nIndex, LPCTSTR lpszItem);
        HWND GetComboCtrl() const;
        HWND GetEditCtrl() const;
        BOOL HasEditChanged() const;

        INT AddString(LPCTSTR);
        INT InsertString(INT, LPCTSTR);
        INT Dir(UINT, LPCTSTR);
        INT FindString(INT, LPCTSTR) const;

        #if (_WIN32_IE >= 0x0400)
            DWORD GetExtendedStyle() const;
            DWORD SetExtendedStyle(DWORD dwExMask, DWORD dwExStyle);
            BOOL GetUnicodeFormat() const;
            BOOL SetUnicodeFormat(BOOL bUnicode = TRUE);
        #endif  // (_WIN32_IE >= 0x0400)

        #if (_WIN32_WINNT >= 0x0501)
            VOID SetWindowTheme(LPCWSTR lpstrTheme);
        #endif  // (_WIN32_WINNT >= 0x0501)
    };
#endif  // (_WIN32_IE >= 0x0300)

////////////////////////////////////////////////////////////////////////////

#if (_WIN32_IE >= 0x0300)
    inline MComboBoxEx::MComboBoxEx()
    {
    }

    inline /*virtual*/ LPCTSTR MComboBoxEx::GetWndClassName() const
    {
        return WC_COMBOBOXEX;
    }

    inline HIMAGELIST MComboBoxEx::GetImageList()
    {
        return (HIMAGELIST)SendMessageDx(CBEM_GETIMAGELIST);
    }

    inline HIMAGELIST MComboBoxEx::SetImageList(HIMAGELIST hImageList)
    {
        return (HIMAGELIST)
            SendMessageDx(CBEM_SETIMAGELIST, 0, (LPARAM)hImageList);
    }

    inline INT MComboBoxEx::InsertItem(const COMBOBOXEXITEM* lpcCBItem)
    {
        return (INT)SendMessageDx(CBEM_INSERTITEM, 0, (LPARAM)lpcCBItem);
    }

    inline INT MComboBoxEx::AddItem(
        UINT nMask, LPCTSTR lpszItem, INT nImage, INT nSelImage,
        INT iIndent, INT iOverlay, LPARAM lParam)
    {
        return InsertItem(nMask, -1, lpszItem, nImage, nSelImage,
            iIndent, iOverlay, lParam);
    }

    inline INT MComboBoxEx::AddItem(LPCTSTR lpszItem, INT nImage,
        INT nSelImage, INT iIndent, LPARAM lParam/* = 0*/)
    {
        return InsertItem(-1, lpszItem, nImage, nSelImage, iIndent, lParam);
    }

    inline INT MComboBoxEx::DeleteItem(INT nIndex)
    {
        return (INT)SendMessageDx(CBEM_DELETEITEM, (WPARAM)nIndex);
    }

    inline BOOL MComboBoxEx::GetItem(PCOMBOBOXEXITEM pCBItem) const
    {
        return (BOOL)SendMessageDx(CBEM_GETITEM, 0, (LPARAM)pCBItem);
    }

    inline BOOL MComboBoxEx::SetItem(const COMBOBOXEXITEM* lpcCBItem)
    {
        return (BOOL)SendMessageDx(CBEM_SETITEM, 0, (LPARAM)lpcCBItem);
    }

    inline BOOL MComboBoxEx::SetItemText(INT nIndex, LPCTSTR lpszItem)
    {
        return SetItem(nIndex, CBEIF_TEXT, lpszItem, 0, 0, 0, 0, 0);
    }

    inline HWND MComboBoxEx::GetComboCtrl() const
    {
        return (HWND)SendMessageDx(CBEM_GETCOMBOCONTROL);
    }

    inline HWND MComboBoxEx::GetEditCtrl() const
    {
        return (HWND)SendMessageDx(CBEM_GETEDITCONTROL);
    }

    inline BOOL MComboBoxEx::HasEditChanged() const
    {
        return (BOOL)SendMessageDx(CBEM_HASEDITCHANGED);
    }

    inline INT MComboBoxEx::AddString(LPCTSTR)
    {
        DebugPrintDx(TEXT("WARNING: You shouldn't call AddString for MComboBoxEx!\n"));
        FootmarkThisDx();
        assert(FALSE);
        return 0;
    }

    inline INT MComboBoxEx::InsertString(INT, LPCTSTR)
    {
        DebugPrintDx(TEXT("WARNING: You shouldn't call InsertString for MComboBoxEx!\n"));
        FootmarkThisDx();
        assert(FALSE);
        return 0;
    }

    inline INT MComboBoxEx::Dir(UINT, LPCTSTR)
    {
        DebugPrintDx(TEXT("WARNING: You shouldn't call Dir for MComboBoxEx!\n"));
        FootmarkThisDx();
        assert(FALSE);
        return 0;
    }

    inline INT MComboBoxEx::FindString(INT, LPCTSTR) const
    {
        DebugPrintDx(TEXT("WARNING: You shouldn't call FindString for MComboBoxEx!\n"));
        FootmarkThisDx();
        assert(FALSE);
        return 0;
    }

#if (_WIN32_IE >= 0x0400)
    inline DWORD MComboBoxEx::GetExtendedStyle() const
    {
        return (DWORD)SendMessageDx(CBEM_GETEXTENDEDSTYLE);
    }

    inline DWORD MComboBoxEx::SetExtendedStyle(
        DWORD dwExMask, DWORD dwExStyle)
    {
        return (DWORD)SendMessageDx(CBEM_SETEXTENDEDSTYLE, (WPARAM)dwExMask, (LPARAM)dwExStyle);
    }

    inline BOOL MComboBoxEx::GetUnicodeFormat() const
    {
        return (BOOL)SendMessageDx(CBEM_GETUNICODEFORMAT);
    }

    inline BOOL MComboBoxEx::SetUnicodeFormat(BOOL bUnicode/* = TRUE*/)
    {
        return (BOOL)SendMessageDx(CBEM_SETUNICODEFORMAT, (WPARAM)bUnicode);
    }
#endif  // (_WIN32_IE >= 0x0400)

#if (_WIN32_WINNT >= 0x0501)
    inline VOID MComboBoxEx::SetWindowTheme(LPCWSTR lpstrTheme)
    {
        SendMessageDx(CBEM_SETWINDOWTHEME, 0, (LPARAM)lpstrTheme);
    }
#endif  // (_WIN32_WINNT >= 0x0501)
#endif  // (_WIN32_IE >= 0x0300)

#if (_WIN32_IE >= 0x0300)
    inline INT MComboBoxEx::InsertItem(UINT nMask, INT nIndex,
        LPCTSTR lpszItem, INT nImage, INT nSelImage, INT iIndent,
        INT iOverlay, LPARAM lParam)
    {
        COMBOBOXEXITEM cbex;
        ZeroMemory(&cbex, sizeof(cbex));
        cbex.mask = nMask;
        cbex.iItem = nIndex;
        cbex.pszText = const_cast<LPTSTR>(lpszItem);
        cbex.iImage = nImage;
        cbex.iSelectedImage = nSelImage;
        cbex.iIndent = iIndent;
        cbex.iOverlay = iOverlay;
        cbex.lParam = lParam;
        return (INT)SendMessageDx(CBEM_INSERTITEM, 0, (LPARAM)&cbex);
    }

    inline INT MComboBoxEx::InsertItem(
        INT nIndex, LPCTSTR lpszItem, INT nImage, INT nSelImage,
        INT iIndent, LPARAM lParam/* = 0*/)
    {
        COMBOBOXEXITEM cbex;
        ZeroMemory(&cbex, sizeof(cbex));
        cbex.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE |
                    CBEIF_INDENT | CBEIF_LPARAM;
        cbex.iItem = nIndex;
        cbex.pszText = const_cast<LPTSTR>(lpszItem);
        cbex.iImage = nImage;
        cbex.iSelectedImage = nSelImage;
        cbex.iIndent = iIndent;
        cbex.lParam = lParam;
        return (INT)SendMessageDx(CBEM_INSERTITEM, 0, (LPARAM)&cbex);
    }

    inline INT MComboBoxEx::SetItem(INT nIndex, UINT nMask,
        LPCTSTR lpszItem, INT nImage, INT nSelImage, INT iIndent,
        INT iOverlay, LPARAM lParam)
    {
        COMBOBOXEXITEM cbex;
        ZeroMemory(&cbex, sizeof(cbex));
        cbex.mask = nMask;
        cbex.iItem = nIndex;
        cbex.pszText = const_cast<LPTSTR>(lpszItem);
        cbex.iImage = nImage;
        cbex.iSelectedImage = nSelImage;
        cbex.iIndent = iIndent;
        cbex.iOverlay = iOverlay;
        cbex.lParam = lParam;
        return (INT)SendMessageDx(CBEM_SETITEM, 0, (LPARAM)&cbex);
    }

    inline BOOL MComboBoxEx::GetItemText(
        INT nIndex, LPTSTR lpszItem, INT nLen) const
    {
        COMBOBOXEXITEM cbex;
        ZeroMemory(&cbex, sizeof(cbex));
        cbex.mask = CBEIF_TEXT;
        cbex.iItem = nIndex;
        cbex.pszText = lpszItem;
        cbex.cchTextMax = nLen;
        return (BOOL)SendMessageDx(CBEM_GETITEM, 0, (LPARAM)&cbex);
    }
#endif  // (_WIN32_IE >= 0x0300)

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCOMBOBOXEX_HPP_
