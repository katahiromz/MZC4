// MFindReplaceDialog.hpp -- Win32API find/replace dialog       -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFINDREPLACEDIALOG_HPP_
#define MZC4_MFINDREPLACEDIALOG_HPP_    3       /* Version 3 */

class MFindReplaceDialog;

////////////////////////////////////////////////////////////////////////////

#include "MCommonDialog.hpp"

struct FINDREPLACEDX : FINDREPLACE
{
    DWORD dwMagic;
    MFindReplaceDialog *pDialog;
};

class MFindReplaceDialog : public MCommonDialog
{
public:
    FINDREPLACEDX m_fr;

    MFindReplaceDialog();
    BOOL FindText(HWND hwndOwner, LPCTSTR pszFindWhat = NULL, DWORD dwFR_ = FR_DOWN);
    BOOL ReplaceText(HWND hwndOwner, LPCTSTR pszFindWhat = NULL,
                     LPCTSTR pszReplaceWith = NULL, DWORD dwFR_ = FR_DOWN);
    BOOL FindNext() const;
    MString GetFindString() const;
    MString GetReplaceString() const;
    BOOL IsTerminating() const;
    BOOL MatchCase() const;
    BOOL MatchWholeWord() const;
    BOOL ReplaceAll() const;
    BOOL ReplaceCurrent() const;
    BOOL SearchDown() const;

    static MFindReplaceDialog *GetNotifier(LPARAM lParam);
    static UINT GetFindReplaceMessageDx();

protected:
    TCHAR m_szFindWhat[128];
    TCHAR m_szReplaceWith[128];

    VOID SetFindWhat(LPCTSTR pszFindWhat);
    VOID SetReplaceWidth(LPCTSTR pszReplaceWith);
};

////////////////////////////////////////////////////////////////////////////

inline
MFindReplaceDialog::MFindReplaceDialog()
{
    ZeroMemory(&m_fr, sizeof(m_fr));
    m_fr.lStructSize = sizeof(m_fr);
    m_fr.hwndOwner = NULL;
    m_fr.hInstance = ::GetModuleHandle(NULL);

    m_szFindWhat[0] = 0;
    m_fr.lpstrFindWhat = m_szFindWhat;
    m_fr.wFindWhatLen = _countof(m_szFindWhat);

    m_szReplaceWith[0] = 0;
    m_fr.lpstrReplaceWith = m_szReplaceWith;
    m_fr.wReplaceWithLen = _countof(m_szReplaceWith);

    m_fr.dwMagic = 0xDEADFACE;
    m_fr.pDialog = this;
}

inline VOID MFindReplaceDialog::SetFindWhat(LPCTSTR pszFindWhat)
{
    if (pszFindWhat)
    {
        ::lstrcpyn(m_szFindWhat, pszFindWhat, _countof(m_szFindWhat));
    }
    else
    {
        m_szFindWhat[0] = 0;
    }
    m_fr.lpstrFindWhat = m_szFindWhat;
}

inline VOID MFindReplaceDialog::SetReplaceWidth(LPCTSTR pszReplaceWith)
{
    if (pszReplaceWith)
    {
        ::lstrcpyn(m_szReplaceWith, pszReplaceWith, _countof(m_szReplaceWith));
    }
    else
    {
        m_szReplaceWith[0] = 0;
    }
    m_fr.lpstrReplaceWith = m_szReplaceWith;
}

inline BOOL
MFindReplaceDialog::FindText(HWND hwndOwner, LPCTSTR pszFindWhat/* = NULL*/,
                             DWORD dwFR_/* = FR_DOWN*/)
{
    m_fr.Flags = dwFR_;
    m_fr.Flags &= ~(FR_REPLACE | FR_REPLACEALL);

    SetFindWhat(pszFindWhat);
    m_fr.hwndOwner = hwndOwner;

    return Attach(::FindText(&m_fr));
}

inline BOOL
MFindReplaceDialog::ReplaceText(HWND hwndOwner,
                                LPCTSTR pszFindWhat/* = NULL*/,
                                LPCTSTR pszReplaceWith/* = NULL*/,
                                DWORD dwFR_/* = FR_DOWN*/)
{
    m_fr.Flags = dwFR_;
    m_fr.Flags |= FR_REPLACE;

    SetFindWhat(pszFindWhat);
    SetReplaceWidth(pszReplaceWith);
    m_fr.hwndOwner = hwndOwner;

    return Attach(::ReplaceText(&m_fr));
}

inline BOOL MFindReplaceDialog::FindNext() const
{
    return (m_fr.Flags & FR_FINDNEXT) != 0;
}

inline MString
MFindReplaceDialog::GetFindString() const
{
    MString ret;
    if (m_fr.lpstrFindWhat)
        ret = m_fr.lpstrFindWhat;
    return ret;
}

inline MString
MFindReplaceDialog::GetReplaceString() const
{
    MString ret;
    if (m_fr.lpstrReplaceWith)
        ret = m_fr.lpstrReplaceWith;
    return ret;
}

inline BOOL
MFindReplaceDialog::IsTerminating() const
{
    return (m_fr.Flags & FR_DIALOGTERM) != 0;
}

inline BOOL
MFindReplaceDialog::MatchCase() const
{
    return (m_fr.Flags & FR_MATCHCASE) != 0;
}

inline BOOL
MFindReplaceDialog::MatchWholeWord() const
{
    return (m_fr.Flags & FR_WHOLEWORD) != 0;
}

inline BOOL
MFindReplaceDialog::ReplaceAll() const
{
    return (m_fr.Flags & FR_REPLACEALL) != 0;
}

inline BOOL
MFindReplaceDialog::ReplaceCurrent() const
{
    return (m_fr.Flags & FR_REPLACE) != 0;
}

inline BOOL
MFindReplaceDialog::SearchDown() const
{
    return (m_fr.Flags & FR_DOWN) != 0;
}

inline /*static*/ UINT
MFindReplaceDialog::GetFindReplaceMessageDx()
{
    static UINT s_uMsg = ::RegisterWindowMessage(FINDMSGSTRING);
    return s_uMsg;
}

inline /*static*/ MFindReplaceDialog *
MFindReplaceDialog::GetNotifier(LPARAM lParam)
{
    FINDREPLACEDX *fr = reinterpret_cast<FINDREPLACEDX *>(lParam);
    if (fr->dwMagic == 0xDEADFACE)
        return fr->pDialog;
    return NULL;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFINDREPLACEDIALOG_HPP_
