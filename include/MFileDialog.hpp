// MFileDialog.hpp -- Win32API file dialog wrapper              -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFILEDIALOG_HPP_
#define MZC4_MFILEDIALOG_HPP_       3       /* Version 3 */

class MFileDialog;

////////////////////////////////////////////////////////////////////////////

#include "MCommonDialog.hpp"
#include "MFile.hpp"

class MFileDialog : public MCommonDialog
{
public:
    OPENFILENAME m_ofn;

    // before main
    // NOTE: pszFilter should be separated by '|'s.
    MFileDialog(HWND hwndOwner, LPCTSTR pszDefExt = NULL,
                LPCTSTR pszFileName = NULL,
                LPCTSTR pszFilter = NULL,
                LPCTSTR pszTitle = NULL,
                DWORD dwOFN_ = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT);

    // main
    BOOL GetOpenFileName();
    BOOL GetSaveFileName();

    // after main
    MString GetPathName() const;
    MString GetFileTitle() const;
    MString GetFileExt() const;
    BOOL GetReadOnly() const;

    // dialog properties
    MString GetFilePath() const;
    MString GetFolderPath() const;
    MString GetSpec() const;

    // dialog manipulators
    void SetControlText(INT nID, LPCSTR lpsz);
    void HideControl(INT nID);
    void SetDefExt(LPCTSTR pszDefExt);

    // messaging
    static UINT GetFileOkMessage();
    static UINT GetShareViolationMessage();
    static UINT GetLBSelChangeMessage();

    // convert '|' to '\0'
    static void MakeFilter(MString& m_strFilter);

protected:
    MString m_strFilter;
    TCHAR m_szFileName[MAX_PATH];
    OFNOTIFY *m_pon;

    // overridables
    virtual void OnInitDone();
    virtual void OnFileNameChange();
    virtual void OnFolderChange();
    virtual void OnTypeChange();
    virtual UINT OnShareViolation(LPCTSTR lpszPathName);
    virtual BOOL OnFileNameOK();
    virtual void OnLBSelChangedNotify(UINT nIDBox, UINT iCurSel, UINT nCode);

    LRESULT OnNotify(HWND hwnd, int idFrom, LPNMHDR pnmhdr);

    static UINT_PTR APIENTRY
    OFNHookProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    virtual INT_PTR CALLBACK
    DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // get file name extension from filter string
    static BOOL FileExtFromFilter(LPTSTR pExt, OPENFILENAME *pOFN);
};

////////////////////////////////////////////////////////////////////////////

inline
MFileDialog::MFileDialog(HWND hwndOwner, LPCTSTR pszDefExt/* = NULL*/,
                         LPCTSTR pszFileName/* = NULL*/,
                         LPCTSTR pszFilter/* = NULL*/,
                         LPCTSTR pszTitle/* = NULL*/,
                         DWORD dwOFN_/* = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT*/)
{
    m_bModal = TRUE;

    if (pszFileName)
    {
        lstrcpyn(m_szFileName, pszFileName, _countof(m_szFileName));
    }
    else
    {
        m_szFileName[0] = 0;
    }

    if (pszFilter)
    {
        m_strFilter = pszFilter;
        MakeFilter(m_strFilter);
    }

    ZeroMemory(&m_ofn, sizeof(m_ofn));
    m_ofn.lStructSize = sizeof(m_ofn);
    m_ofn.hwndOwner = hwndOwner;
    m_ofn.lpstrFilter = m_strFilter.c_str();
    m_ofn.lpstrFile = m_szFileName;
    m_ofn.nMaxFile = _countof(m_szFileName);
    m_ofn.Flags = dwOFN_;
    m_ofn.lpfnHook = MFileDialog::OFNHookProc;
    m_ofn.lpstrDefExt = pszDefExt;
    m_ofn.lCustData = (LPARAM)this;
}

inline BOOL MFileDialog::GetOpenFileName()
{
    m_ofn.Flags |= OFN_EXPLORER | OFN_ENABLESIZING | OFN_ENABLEHOOK;
    return ::GetOpenFileName(&m_ofn);
}

inline BOOL MFileDialog::GetSaveFileName()
{
    m_ofn.Flags |= OFN_EXPLORER | OFN_ENABLESIZING | OFN_ENABLEHOOK;
    return ::GetSaveFileName(&m_ofn);
}

inline MString MFileDialog::GetPathName() const
{
    return MString(m_ofn.lpstrFile);
}

inline MString MFileDialog::GetFileTitle() const
{
    return MString(&m_ofn.lpstrFile[m_ofn.nFileOffset]);
}

inline MString MFileDialog::GetFileExt() const
{
    return MString(&m_ofn.lpstrFile[m_ofn.nFileExtension]);
}

inline MString MFileDialog::GetFilePath() const
{
    MString ret = m_ofn.lpstrFile;
    TCHAR sz[MAX_PATH];
    HWND hwndParent = ::GetParent(m_hwnd);

    if (::IsWindow(m_hwnd) &&
        ::SendMessage(hwndParent, CDM_GETFILEPATH, (WPARAM)_countof(sz), (LPARAM)sz) >= 0)
    {
        ret = sz;
    }

    return ret;
}

inline MString MFileDialog::GetFolderPath() const
{
    MString ret;
    TCHAR sz[MAX_PATH];
    HWND hParent = ::GetParent(m_hwnd);

    if (::IsWindow(m_hwnd) &&
        ::SendMessage(hParent, CDM_GETFOLDERPATH, (WPARAM)_countof(sz), (LPARAM)sz) >= 0)
    {
        ret = sz;
    }
    else
    {
        lstrcpyn(sz, m_ofn.lpstrFile, _countof(sz));
        LPTSTR pch = FindFileNameDx(sz);
        if (pch)
        {
            *pch = 0;
            ret = sz;
        }
    }

    return ret;
}

inline MString MFileDialog::GetSpec() const
{
    MString ret;
    TCHAR sz[MAX_PATH];
    HWND hParent = ::GetParent(m_hwnd);

    if (::IsWindow(m_hwnd) &&
        ::SendMessage(hParent, CDM_GETSPEC, (WPARAM)_countof(sz), (LPARAM)sz))
    {
        ret = sz;
    }
    else
    {
        ret = &m_ofn.lpstrFile[m_ofn.nFileOffset];
    }

    return ret;
}

inline void MFileDialog::SetControlText(INT nID, LPCSTR psz)
{
    assert(::IsWindow(m_hwnd));
    HWND hParent = ::GetParent(m_hwnd);
    ::SendMessage(hParent, CDM_SETCONTROLTEXT, nID, (LPARAM)psz);
}

inline void MFileDialog::HideControl(INT nID)
{
    assert(::IsWindow(m_hwnd));
    HWND hParent = ::GetParent(m_hwnd);
    ::SendMessage(hParent, CDM_HIDECONTROL, nID, 0);
}

inline void MFileDialog::SetDefExt(LPCSTR pszDefExt)
{
    assert(::IsWindow(m_hwnd));
    HWND hParent = ::GetParent(m_hwnd);
    ::SendMessage(hParent, CDM_SETDEFEXT, 0, (LPARAM)pszDefExt);
}

inline /*static*/ UINT MFileDialog::GetFileOkMessage()
{
    static UINT s_uMsg = ::RegisterWindowMessage(FILEOKSTRING);
    return s_uMsg;
}

inline /*static*/ UINT MFileDialog::GetShareViolationMessage()
{
    static UINT s_uMsg = ::RegisterWindowMessage(SHAREVISTRING);
    return s_uMsg;
}

inline /*static*/ UINT MFileDialog::GetLBSelChangeMessage()
{
    static UINT s_uMsg = ::RegisterWindowMessage(LBSELCHSTRING);
    return s_uMsg;
}

inline BOOL MFileDialog::GetReadOnly() const
{
    return (m_ofn.Flags & OFN_READONLY) != 0;
}

inline /*static*/ void MFileDialog::MakeFilter(MString& m_strFilter)
{
    m_strFilter += TEXT('|');

    for (size_t i = 0; i < m_strFilter.size(); ++i)
    {
        if (m_strFilter[i] == TEXT('|'))
            m_strFilter[i] = 0;
    }
}

inline /*virtual*/ UINT
MFileDialog::OnShareViolation(LPCTSTR lpszPathName)
{
    return OFN_SHAREWARN;
}

inline /*virtual*/ BOOL MFileDialog::OnFileNameOK()
{
    return FALSE;
}

inline /*virtual*/ void
MFileDialog::OnLBSelChangedNotify(UINT nIDBox, UINT iCurSel, UINT nCode)
{
}

inline /*virtual*/ void MFileDialog::OnInitDone()
{
    CenterWindowDx(::GetParent(m_hwnd));
}

inline /*virtual*/ void MFileDialog::OnFileNameChange()
{
}

inline /*virtual*/ void MFileDialog::OnFolderChange()
{
}

inline /*static*/ BOOL
MFileDialog::FileExtFromFilter(LPTSTR pExt, OPENFILENAME *pOFN)
{
    if (pOFN->lpstrFilter == NULL)
        return FALSE;   /* not found */

    LPTSTR pchExt = pExt;
    *pchExt = 0;

    DWORD nIndex = 1;
    for (LPCTSTR pch = pOFN->lpstrFilter; *pch; ++nIndex)
    {
        pch += lstrlen(pch) + 1;
        if (pOFN->nFilterIndex == nIndex)
        {
            for (++pch; *pch && *pch != _T(';'); ++pch)
            {
                *pchExt++ = *pch;
            }
            *pchExt = 0;
            ::CharLower(pExt);
            return TRUE;    /* found */
        }
        pch += lstrlen(pch) + 1;
    }
    return FALSE;   /* not found */
}

inline /*virtual*/ void MFileDialog::OnTypeChange()
{
    assert(::IsWindow(m_hwnd));
    assert(m_pon);

    // We should change the extension
    TCHAR szPath[MAX_PATH];
    HWND hParent = ::GetParent(m_hwnd);
    ::SendMessage(hParent, CDM_GETFILEPATH, _countof(szPath), (LPARAM)szPath);

    LPTSTR pchTitle = FindFileNameDx(szPath);
    LPTSTR pch = FindDotExtDx(szPath);
    if (pch && pchTitle)
    {
        *pch = 0;
        if (FileExtFromFilter(pch, m_pon->lpOFN))
        {
            ::SendMessage(hParent, CDM_SETCONTROLTEXT, 0x047c, (LPARAM)pchTitle);
            lstrcpyn(m_pon->lpOFN->lpstrFile, szPath, MAX_PATH);
        }
    }
}

inline LRESULT MFileDialog::OnNotify(HWND hwnd, int idFrom, LPNMHDR pnmhdr)
{
    OFNOTIFY *pon = (OFNOTIFY *)pnmhdr;
    m_pon = pon;

    LRESULT ret = 0;
    switch (pon->hdr.code)
    {
    case CDN_INITDONE:
        OnInitDone();
        break;
    case CDN_SELCHANGE:
        OnFileNameChange();
        break;
    case CDN_FOLDERCHANGE:
        OnFolderChange();
        break;
    case CDN_SHAREVIOLATION:
        ret = OnShareViolation(pon->pszFile);
    case CDN_HELP:
        // FIXME:
        break;
    case CDN_FILEOK:
        ret = OnFileNameOK();
    case CDN_TYPECHANGE:
        OnTypeChange();
        break;
    }
    m_pon = NULL;

    return ret;
}

inline /*static*/ UINT_PTR APIENTRY
MFileDialog::OFNHookProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (hwnd == NULL)
        return 0;

    MFileDialog *base;
	OPENFILENAME *pofn;
    if (uMsg == WM_INITDIALOG)
    {
        assert(lParam);
        pofn = (OPENFILENAME *)lParam;
		assert(pofn->lCustData);
		base = (MFileDialog *)pofn->lCustData;
        base->Attach(hwnd);
    }

    UINT_PTR ret = 0;
    base = (MFileDialog *)GetUserData(hwnd);
    if (base)
    {
        if (uMsg == GetFileOkMessage())
        {
            ret = base->OnFileNameOK();
        }
        else if (uMsg == GetShareViolationMessage())
        {
            ret = base->OnShareViolation((LPCTSTR)lParam);
        }
        else if (uMsg == GetLBSelChangeMessage())
        {
            base->OnLBSelChangedNotify((UINT)wParam, LOWORD(lParam), HIWORD(lParam));
        }
        else
        {
            ret = base->DialogProcDx(hwnd, uMsg, wParam, lParam);
        }
    }
    return ret;
}

inline /*virtual*/ INT_PTR CALLBACK
MFileDialog::DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_NOTIFY, OnNotify);
    }
    return DefaultProcDx();
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFILEDIALOG_HPP_
