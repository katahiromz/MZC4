// MAccel.hpp -- Win32API accelerator wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MMENU_HPP_
#define MZC4_MMENU_HPP_     3       /* Version 3 */

class MMenu;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

// MString
#ifndef MString
    #include <string>       // std::string and std::wstring
    typedef std::string     MStringA;
    typedef std::wstring    MStringW;
    #ifdef UNICODE
        #define MString     MStringW
    #else
        #define MString     MStringA
    #endif
#endif

////////////////////////////////////////////////////////////////////////////

class MMenu
{
public:
    HMENU   m_hMenu;

    MMenu();
    MMenu(HMENU hMenu);
    ~MMenu();

    BOOL Attach(HMENU hMenu);
    HMENU Detach();
    HMENU Handle() const;

    bool operator!() const;
    operator HMENU() const;
    bool operator!=(const MMenu& menu) const;
    bool operator==(const MMenu& menu) const;
    MMenu& operator=(HMENU hMenu);

    BOOL AppendMenu(UINT nMF_, UINT_PTR nNewID, LPCTSTR pszItemText = NULL);
    BOOL AppendMenu(UINT nMF_, UINT_PTR nNewID, HBITMAP hbm);
    UINT CheckMenuItem(UINT nItem, UINT nMF_ = MF_CHECKED);
    BOOL CheckMenuRadioItem(UINT first, UINT last, UINT item, UINT nMF_ = MF_BYCOMMAND);
    BOOL CreateMenu();
    BOOL CreatePopupMenu();
    BOOL DeleteMenu(UINT nItem, UINT nMF_ = MF_BYCOMMAND);
    BOOL DestroyMenu();
    UINT EnableMenuItem(UINT nItem, UINT nMF_ = MF_BYCOMMAND | MF_ENABLED);
    UINT GetMenuDefaultItem(BOOL fByPos, UINT nGMDI_);
    DWORD GetMenuContextHelpId() const;
    INT GetMenuItemCount() const;
    UINT GetMenuItemID(INT nPos) const;
    BOOL GetMenuItemInfo(UINT nItem, LPMENUITEMINFO pMII, BOOL fByPos = FALSE);
    UINT GetMenuState(UINT nItem, UINT nMF_ = MF_BYCOMMAND);
    INT GetMenuString(UINT nItem, LPTSTR psz, INT cchMax, UINT nMF_ = MF_BYCOMMAND);
    INT GetMenuString(UINT nItem, MString& str, UINT nMF_ = MF_BYCOMMAND);
    HMENU GetSubMenu(INT nPos) const;
    BOOL InsertMenu(UINT nPos, UINT nMF_, UINT_PTR nNewID, LPCTSTR pszItemText = NULL);
    BOOL InsertMenu(UINT nPos, UINT nMF_, UINT_PTR nNewID, HBITMAP hbm);
    BOOL InsertMenuItem(UINT nItem, LPMENUITEMINFO pMII, BOOL fByPos = FALSE);
    BOOL LoadMenu(HINSTANCE hInst, LPCTSTR pszMenuName);
    BOOL LoadMenu(HINSTANCE hInst, UINT nMenuID);
    BOOL LoadMenu(LPCTSTR pszMenuName);
    BOOL LoadMenu(UINT nMenuID);
    BOOL LoadMenuIndirect(const void *pMenuTemplate);
    BOOL ModifyMenu(UINT nItem, UINT nMF_, UINT_PTR nNewID = 0, LPCTSTR pszMenuText = NULL);
    BOOL ModifyMenu(UINT nItem, UINT nMF_, UINT_PTR nNewID, HBITMAP hbm);
    BOOL RemoveMenu(UINT nItem, UINT nMF_ = MF_BYCOMMAND);
    BOOL SetMenuDefaultItem(UINT nItem, BOOL fByPos = FALSE);
    BOOL SetMenuContextHelpId(DWORD dwContextID);
    BOOL SetMenuItemBitmaps(UINT nItem, UINT nMF_, HBITMAP hbmUnchecked, HBITMAP hbmChecked);
    BOOL SetMenuItemInfo(UINT nItem, LPMENUITEMINFO pMII, BOOL fByPos = FALSE);
    BOOL TrackPopupMenu(UINT nTPM_, INT x, INT y, HWND hwnd, LPCRECT prc = NULL);
    BOOL TrackPopupMenuEx(UINT nTPM_, INT x, INT y, HWND hwnd, TPMPARAMS *params = NULL);

    virtual VOID DrawItemDx(LPDRAWITEMSTRUCT lpDIS);
    virtual VOID MeasureItemDx(LPMEASUREITEMSTRUCT pMIS);

private:
    // NOTE: MMenu is not copyable.
    MMenu(const MMenu&);
    MMenu& operator=(const MMenu&);
};

inline MMenu::MMenu() : m_hMenu(NULL)
{
}

inline MMenu::MMenu(HMENU hMenu) : m_hMenu(hMenu)
{
}

inline MMenu::~MMenu()
{
    DestroyMenu();
}

inline BOOL MMenu::Attach(HMENU hMenu)
{
    DestroyMenu();
    m_hMenu = hMenu;
    return m_hMenu != NULL;
}

inline HMENU MMenu::Detach()
{
    HMENU hMenu = m_hMenu;
    m_hMenu = NULL;
    return hMenu;
}

inline HMENU MMenu::Handle() const
{
    return (this ? m_hMenu : NULL);
}

inline bool MMenu::operator!() const
{
    return Handle() == NULL;
}

inline MMenu::operator HMENU() const
{
    return Handle();
}

inline bool MMenu::operator!=(const MMenu& menu) const
{
    return Handle() != menu.Handle();
}

inline bool MMenu::operator==(const MMenu& menu) const
{
    return Handle() == menu.Handle();
}

inline MMenu& MMenu::operator=(HMENU hMenu)
{
    DestroyMenu();
    m_hMenu = hMenu;
    return *this;
}

inline BOOL
MMenu::AppendMenu(UINT nMF_, UINT_PTR nNewID, LPCTSTR pszItemText/* = NULL*/)
{
    assert(Handle());
    return ::AppendMenu(Handle(), nMF_, nNewID, pszItemText);
}

inline BOOL MMenu::AppendMenu(UINT nMF_, UINT_PTR nNewID, HBITMAP hbm)
{
    assert(Handle());
    return ::AppendMenu(Handle(), nMF_, nNewID, reinterpret_cast<LPTSTR>(hbm));
}

inline UINT MMenu::CheckMenuItem(UINT nItem, UINT nMF_/* = MF_CHECKED*/)
{
    assert(Handle());
    return ::CheckMenuItem(Handle(), nItem, nMF_);
}

inline BOOL
MMenu::CheckMenuRadioItem(UINT first, UINT last, UINT item,
                          UINT nMF_/* = MF_BYCOMMAND*/)
{
    assert(Handle());
    return ::CheckMenuRadioItem(Handle(), first, last, item, nMF_);
}

inline BOOL MMenu::CreateMenu()
{
    return Attach(::CreateMenu());
}

inline BOOL MMenu::CreatePopupMenu()
{
    return Attach(::CreatePopupMenu());
}

inline BOOL MMenu::DeleteMenu(UINT nItem, UINT nMF_/* = MF_BYCOMMAND*/)
{
    assert(Handle());
    return ::DeleteMenu(Handle(), nItem, nMF_);
}

inline BOOL MMenu::DestroyMenu()
{
    if (Handle())
    {
        BOOL bOK = ::DestroyMenu(Handle());
        Detach();
        return bOK;
    }
    return FALSE;
}

inline UINT
MMenu::EnableMenuItem(UINT nItem, UINT nMF_/* = MF_BYCOMMAND | MF_ENABLED*/)
{
    assert(Handle());
    return ::EnableMenuItem(Handle(), nItem, nMF_);
}

inline UINT
MMenu::GetMenuDefaultItem(BOOL fByPos, UINT nGMDI_)
{
    assert(Handle());
    return ::GetMenuDefaultItem(Handle(), fByPos, nGMDI_);
}

inline DWORD MMenu::GetMenuContextHelpId() const
{
    assert(Handle());
    return ::GetMenuContextHelpId(Handle());
}

inline INT MMenu::GetMenuItemCount() const
{
    assert(Handle());
    return ::GetMenuItemCount(Handle());
}

inline UINT MMenu::GetMenuItemID(INT nPos) const
{
    assert(Handle());
    return ::GetMenuItemID(Handle(), nPos);
}

inline BOOL
MMenu::GetMenuItemInfo(UINT nItem, LPMENUITEMINFO pMII,
                       BOOL fByPos/* = FALSE*/)
{
    assert(Handle());
    return ::GetMenuItemInfo(Handle(), nItem, fByPos, pMII);
}

inline UINT
MMenu::GetMenuState(UINT nItem, UINT nMF_/* = MF_BYCOMMAND*/)
{
    assert(Handle());
    return ::GetMenuState(Handle(), nItem, nMF_);
}

inline INT
MMenu::GetMenuString(UINT nItem, LPTSTR psz, INT cchMax, UINT nMF_/* = MF_BYCOMMAND*/)
{
    assert(Handle());
    return ::GetMenuString(Handle(), nItem, psz, cchMax, nMF_);
}

inline INT
MMenu::GetMenuString(UINT nItem, MString& str, UINT nMF_/* = MF_BYCOMMAND*/)
{
    assert(Handle());
    INT cch = GetMenuString(nItem, NULL, 0, nMF_);
    str.resize(cch);
    cch = GetMenuString(nItem, &str[0], cch + 1, nMF_);
    if (cch == 0)
        str.clear();
    return cch;
}

inline HMENU MMenu::GetSubMenu(INT nPos) const
{
    assert(Handle());
    return ::GetSubMenu(Handle(), nPos);
}

inline BOOL
MMenu::InsertMenu(UINT nPos, UINT nMF_, UINT_PTR nNewID, LPCTSTR pszItemText/* = NULL*/)
{
    assert(Handle());
    return ::InsertMenu(Handle(), nPos, nMF_, nNewID, pszItemText);
}

inline BOOL MMenu::InsertMenu(UINT nPos, UINT nMF_, UINT_PTR nNewID, HBITMAP hbm)
{
    return InsertMenu(nPos, nMF_, nNewID, reinterpret_cast<LPTSTR>(hbm));
}

inline BOOL
MMenu::InsertMenuItem(UINT nItem, LPMENUITEMINFO pMII, BOOL fByPos/* = FALSE*/)
{
    assert(Handle());
    return ::InsertMenuItem(Handle(), nItem, fByPos, pMII);
}

inline BOOL MMenu::LoadMenu(LPCTSTR pszMenuName)
{
    assert(Handle());
    return LoadMenu(::GetModuleHandle(NULL), pszMenuName);
}

inline BOOL MMenu::LoadMenu(HINSTANCE hInst, LPCTSTR pszMenuName)
{
    return Attach(::LoadMenu(hInst, pszMenuName));
}

inline BOOL MMenu::LoadMenu(HINSTANCE hInst, UINT nMenuID)
{
    return Attach(::LoadMenu(hInst, MAKEINTRESOURCE(nMenuID)));
}

inline BOOL MMenu::LoadMenu(UINT nMenuID)
{
    return LoadMenu(MAKEINTRESOURCE(nMenuID));
}

inline BOOL MMenu::LoadMenuIndirect(const void *pMenuTemplate)
{
    return Attach(::LoadMenuIndirect(reinterpret_cast<const MENUTEMPLATE *>(pMenuTemplate)));
}

inline BOOL MMenu::ModifyMenu(UINT nItem, UINT nMF_, UINT_PTR nNewID/* = 0*/, LPCTSTR pszMenuText/* = NULL*/)
{
    assert(Handle());
    return ::ModifyMenu(Handle(), nItem, nMF_, nNewID, pszMenuText);
}

inline BOOL MMenu::ModifyMenu(UINT nItem, UINT nMF_, UINT_PTR nNewID, HBITMAP hbm)
{
    assert(Handle());
    return ModifyMenu(nItem, nMF_, nNewID, reinterpret_cast<LPTSTR>(hbm));
}

inline BOOL MMenu::RemoveMenu(UINT nItem, UINT nMF_/* = MF_BYCOMMAND*/)
{
    assert(Handle());
    return ::RemoveMenu(Handle(), nItem, nMF_);
}

inline BOOL MMenu::SetMenuDefaultItem(UINT nItem, BOOL fByPos/* = FALSE*/)
{
    assert(Handle());
    return ::SetMenuDefaultItem(Handle(), nItem, fByPos);
}

inline BOOL MMenu::SetMenuContextHelpId(DWORD dwContextID)
{
    assert(Handle());
    return ::SetMenuContextHelpId(Handle(), dwContextID);
}

inline BOOL MMenu::SetMenuItemBitmaps(UINT nItem, UINT nMF_, HBITMAP hbmUnchecked, HBITMAP hbmChecked)
{
    assert(Handle());
    return ::SetMenuItemBitmaps(Handle(), nItem, nMF_, hbmUnchecked, hbmChecked);
}

inline BOOL MMenu::SetMenuItemInfo(UINT nItem, LPMENUITEMINFO pMII, BOOL fByPos/* = FALSE*/)
{
    assert(Handle());
    return ::SetMenuItemInfo(Handle(), nItem, fByPos, pMII);
}

inline BOOL MMenu::TrackPopupMenu(UINT nTPM_, INT x, INT y, HWND hwnd, LPCRECT prc/* = NULL*/)
{
    assert(Handle());
    return ::TrackPopupMenu(Handle(), nTPM_, x, y, 0, hwnd, prc);
}

inline BOOL MMenu::TrackPopupMenuEx(UINT nTPM_, INT x, INT y, HWND hwnd, TPMPARAMS *params/* = NULL*/)
{
    assert(Handle());
    return ::TrackPopupMenuEx(Handle(), nTPM_, x, y, hwnd, params);
}

inline /*virtual*/ VOID
MMenu::DrawItemDx(LPDRAWITEMSTRUCT lpDIS)
{
    assert(FALSE);
}

inline /*virtual*/ VOID
MMenu::MeasureItemDx(LPMEASUREITEMSTRUCT pMIS)
{
    assert(FALSE);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MMENU_HPP_
