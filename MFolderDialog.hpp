// MFolderDialog.hpp -- MZC4 folder dialog                      -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFOLDERDIALOG_HPP_
#define MZC4_MFOLDERDIALOG_HPP_     3       /* Version 3 */

class MFolderDialog;

///////////////////////////////////////////////////////////////////////////////

#include "MDialogBase.hpp"
#include "MTextToText.hpp"

#ifndef _SHLOBJ_H_
    #include <shlobj.h>
#endif

class MFolderDialog : public MDialogBase
{
public:
    LPCITEMIDLIST   m_pidlInitialSelection;
    LPITEMIDLIST    m_pidlSelected;
    BOOL            m_bExpand;
    BROWSEINFO      m_bi;
    TCHAR           m_szInitialDir[MAX_PATH];
    TCHAR           m_szFolderPath[MAX_PATH];
    TCHAR           m_szFolderDisplayName[MAX_PATH];

public:
    MFolderDialog(HWND hwndOwner = NULL, LPCTSTR pszTitle = NULL,
                  UINT uBIF_flags = BIF_RETURNONLYFSDIRS);
    virtual ~MFolderDialog();

    /* before main */
    VOID SetInitial(LPCTSTR pszInitialFolder, BOOL bExpand = TRUE);
    VOID SetInitial(LPCITEMIDLIST pidl, BOOL bExpand = TRUE);

    /* main */
    BOOL SHBrowseForFolder();

    /* after main */
    LPITEMIDLIST GetSelectedItem(BOOL bDetach = FALSE);
    LPCTSTR GetFolderPath() const;
    LPCTSTR GetFolderDisplayName() const;
    INT GetFolderImageIndex() const;

    /* overridables */
    virtual VOID OnInitialized();
    virtual VOID OnSelChanged(LPITEMIDLIST pidl);
    virtual INT  OnValidateFailed(LPCTSTR pszFolderPath);
    virtual VOID OnIUnknown(IUnknown* pUnknown);

protected:
    /* manipulation in callback */
    VOID EnableOK(BOOL bEnable);
    VOID SetSelection(LPCITEMIDLIST pidl);
    VOID SetSelection(LPCTSTR pszFolderPath);
    VOID SetStatusText(LPCTSTR pszText);
    VOID SetOKText(LPCTSTR pszOKText);
    VOID SetExpanded(LPCITEMIDLIST pidl);
    VOID SetExpanded(LPCTSTR pszFolderPath);

    static INT CALLBACK BrowseCallbackProc(
        HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};

///////////////////////////////////////////////////////////////////////////////

inline
MFolderDialog::MFolderDialog(
    HWND hwndOwner/* = NULL*/,
    LPCTSTR pszTitle/* = NULL*/,
    UINT uBIF_flags/* = BIF_RETURNONLYFSDIRS*/)
    : MDialogBase(hwndOwner), m_pidlInitialSelection(NULL),
      m_pidlSelected(NULL), m_bExpand(FALSE)
{
    m_bModal = TRUE;

    ZeroMemory(&m_bi, sizeof(m_bi));
    m_bi.hwndOwner = hwndOwner;
    m_bi.pidlRoot = NULL;
    m_bi.pszDisplayName = m_szFolderDisplayName;
    m_bi.lpszTitle = pszTitle;
    m_bi.ulFlags = uBIF_flags;
    m_bi.lpfn = MFolderDialog::BrowseCallbackProc;
    m_bi.lParam = reinterpret_cast<LPARAM>(this);

    m_szInitialDir[0] = 0;
    m_szFolderPath[0] = 0;
    m_szFolderDisplayName[0] = 0;
}

inline /*virtual*/ MFolderDialog::~MFolderDialog()
{
    ::CoTaskMemFree(m_pidlSelected);
}

inline VOID
MFolderDialog::SetInitial(LPCTSTR pszInitialFolder, BOOL bExpand/* = TRUE*/)
{
    ::lstrcpyn(m_szInitialDir, pszInitialFolder, MAX_PATH);
    m_bExpand = bExpand;
}

inline VOID
MFolderDialog::SetInitial(LPCITEMIDLIST pidl, BOOL bExpand/* = TRUE*/)
{
    m_pidlInitialSelection = pidl;
    m_bExpand = bExpand;
}

inline BOOL MFolderDialog::SHBrowseForFolder()
{
    m_szFolderPath[0] = 0;
    m_szFolderDisplayName[0] = 0;
    ::CoTaskMemFree(m_pidlSelected);

    m_pidlSelected = ::SHBrowseForFolder(&m_bi);
    if (m_pidlSelected)
    {
        if (!::SHGetPathFromIDList(m_pidlSelected, m_szFolderPath))
            m_szFolderPath[0] = 0;
    }
    Detach();
    return m_pidlSelected != NULL;
}

inline LPITEMIDLIST
MFolderDialog::GetSelectedItem(BOOL bDetach/* = FALSE*/)
{
    LPITEMIDLIST pidl = m_pidlSelected;
    if (bDetach)
        m_pidlSelected = NULL;
    return pidl;
}

inline LPCTSTR MFolderDialog::GetFolderPath() const
{
    return m_szFolderPath;
}

inline LPCTSTR MFolderDialog::GetFolderDisplayName() const
{
    return m_szFolderDisplayName;
}

inline INT MFolderDialog::GetFolderImageIndex() const
{
    return m_bi.iImage;
}

inline VOID MFolderDialog::EnableOK(BOOL bEnable)
{
    SendMessageDx(BFFM_ENABLEOK, 0, bEnable);
}

inline VOID MFolderDialog::SetStatusText(LPCTSTR pszText)
{
    SendMessageDx(BFFM_SETSTATUSTEXT, 0, (LPARAM)pszText);
}

inline VOID MFolderDialog::SetOKText(LPCTSTR pszOKText)
{
#ifndef BFFM_SETOKTEXT
    const UINT BFFM_SETOKTEXT = WM_USER + 105;
#endif
    MTextToWide str(pszOKText);
    SendMessageDx(BFFM_SETOKTEXT, (WPARAM)str.c_str());
}

inline VOID MFolderDialog::SetExpanded(LPCITEMIDLIST pidl)
{
#ifndef BFFM_SETEXPANDED
    const UINT BFFM_SETEXPANDED = WM_USER + 106;
#endif
    SendMessageDx(BFFM_SETEXPANDED, FALSE, (LPARAM)pidl);
}

inline VOID MFolderDialog::SetExpanded(LPCTSTR pszFolderPath)
{
#ifndef BFFM_SETEXPANDED
    const UINT BFFM_SETEXPANDED = WM_USER + 106;
#endif
    MTextToWide str(pszFolderPath);
    SendMessageDx(BFFM_SETEXPANDED, TRUE, (LPARAM)str.c_str());
}

inline VOID MFolderDialog::SetSelection(LPCITEMIDLIST pidl)
{
    SendMessageDx(BFFM_SETSELECTION, FALSE, (LPARAM)pidl);
}

inline VOID MFolderDialog::SetSelection(LPCTSTR pszFolderPath)
{
    SendMessageDx(BFFM_SETSELECTION, TRUE, (LPARAM)pszFolderPath);
}

inline /*static*/ INT CALLBACK
MFolderDialog::BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
#ifndef BFFM_VALIDATEFAILED
    #ifdef _UNICODE
        const INT BFFM_VALIDATEFAILED = 4;
    #else
        const INT BFFM_VALIDATEFAILED = 3;
    #endif
#endif
#ifndef BFFM_IUNKNOWN
    const INT BFFM_IUNKNOWN = 5;
#endif
    MFolderDialog *pDialog = reinterpret_cast<MFolderDialog *>(lpData);
    if (pDialog->m_hwnd == NULL)
        pDialog->Attach(hWnd);

    INT nRet = 0;
    switch (uMsg)
    {
    case BFFM_INITIALIZED:
        /* set selection */
        if (pDialog->m_pidlInitialSelection)
            pDialog->SetSelection(pDialog->m_pidlInitialSelection);
        else if (pDialog->m_szInitialDir[0] != 0)
            pDialog->SetSelection(pDialog->m_szInitialDir);

        /* expand if necessary */
        if (pDialog->m_bExpand)
        {
            if (pDialog->m_pidlInitialSelection)
                pDialog->SetExpanded(pDialog->m_pidlInitialSelection);
            else if (pDialog->m_szInitialDir[0] != 0)
                pDialog->SetExpanded(pDialog->m_szInitialDir);
        }

        pDialog->OnInitialized();
        break;

    case BFFM_SELCHANGED:
        pDialog->OnSelChanged(reinterpret_cast<LPITEMIDLIST>(lParam));
        break;

    case BFFM_VALIDATEFAILED:
        nRet = pDialog->OnValidateFailed(reinterpret_cast<LPCTSTR>(lParam));
        break;

    case BFFM_IUNKNOWN:
        pDialog->OnIUnknown(reinterpret_cast<IUnknown *>(lParam));
        break;

    default:
        break;
    }

    return nRet;
}

inline /*virtual*/ VOID MFolderDialog::OnInitialized()
{
}

inline /*virtual*/ VOID MFolderDialog::OnSelChanged(LPITEMIDLIST)
{
}

inline /*virtual*/ INT MFolderDialog::OnValidateFailed(LPCTSTR)
{
    return 1;   // 1: continue, 0: EndDialog
}

inline /*virtual*/ VOID MFolderDialog::OnIUnknown(IUnknown*)
{
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFOLDERDIALOG_HPP_
