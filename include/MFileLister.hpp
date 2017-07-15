// MFileLister.hpp -- Win32API file lister                  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFILELISTER_HPP_
#define MZC4_MFILELISTER_HPP_   2       /* Version 2 */

class MFileLister;

///////////////////////////////////////////////////////////////////////////////

#include "MFile.hpp"

///////////////////////////////////////////////////////////////////////////////

class MFileLister
{
public:
    HANDLE m_hFind;
    WIN32_FIND_DATA m_find;
    TCHAR m_szRootDir[MAX_PATH];

public:
    MFileLister();
    MFileLister(LPCTSTR pszWildCard, BOOL bUseFullPath = FALSE);
    virtual ~MFileLister();

    bool operator!() const;
    operator HANDLE() const;
    MFileLister& operator=(HANDLE hFind);
    PHANDLE operator&();

    BOOL Attach(HANDLE hFind);
    HANDLE Detach();
    HANDLE Handle() const;

    BOOL FindFirstFile(LPCTSTR pszWildCard = TEXT("*"), BOOL bUseFullPath = FALSE);
    BOOL FindNextFile();
    BOOL FindClose();

    ULONGLONG GetFileSize() const;

    LPCTSTR GetRootDir() const;
    LPCTSTR GetFileName() const;
    LPCTSTR GetAlternateFileName() const;
    BOOL GetFilePath(LPTSTR pszPath, DWORD cchPath) const;
    template <typename T_STRING>
    BOOL GetFilePath(T_STRING& strPath);

    BOOL GetLastWriteTime(FILETIME* pTimeStamp) const;
    BOOL GetLastAccessTime(FILETIME* pTimeStamp) const;
    BOOL GetCreationTime(FILETIME* pTimeStamp) const;
    DWORD GetFileAttributes() const;
    BOOL MatchesMask(DWORD dwMask) const;

    BOOL IsDots() const;    // "." or ".."
    BOOL IsReadOnly() const;
    BOOL IsDirectory() const;
    BOOL IsCompressed() const;
    BOOL IsSystem() const;
    BOOL IsHidden() const;
    BOOL IsTemporary() const;
    BOOL IsNormal() const;
    BOOL IsArchived() const;

private:
    // NOTE: MFileLister is not copyable.
    MFileLister(const MFileLister& find);
    MFileLister& operator=(const MFileLister& find);
};

////////////////////////////////////////////////////////////////////////////

inline MFileLister::MFileLister()
{
    m_hFind = INVALID_HANDLE_VALUE;
    m_szRootDir[0] = TEXT('\0');
}

inline /*virtual*/ MFileLister::~MFileLister()
{
}

inline bool MFileLister::operator!() const
{
    return Handle() == INVALID_HANDLE_VALUE;
}

inline MFileLister& MFileLister::operator=(HANDLE hFind)
{
    if (m_hFind != hFind)
        Attach(hFind);
    return *this;
}

inline BOOL MFileLister::Attach(HANDLE hFind)
{
    if (m_hFind != INVALID_HANDLE_VALUE)
        FindClose();
    assert(hFind != INVALID_HANDLE_VALUE);
    assert(m_hFind == INVALID_HANDLE_VALUE);
    m_hFind = hFind;
    return m_hFind != INVALID_HANDLE_VALUE;
}

inline HANDLE MFileLister::Detach()
{
    HANDLE hFind = m_hFind;
    m_hFind = INVALID_HANDLE_VALUE;
    return hFind;
}

inline HANDLE MFileLister::Handle() const
{
    return (this ? m_hFind : NULL);
}

inline MFileLister::operator HANDLE() const
{
    return Handle();
}

inline PHANDLE MFileLister::operator&()
{
    return &m_hFind;
}

inline ULONGLONG MFileLister::GetFileSize() const
{
    return MAKELONGLONG(m_find.nFileSizeLow, m_find.nFileSizeHigh);
}

inline BOOL MFileLister::GetLastWriteTime(FILETIME* pTimeStamp) const
{
    assert(pTimeStamp);
    *pTimeStamp = m_find.ftLastWriteTime;
    return TRUE;
}

inline BOOL MFileLister::GetLastAccessTime(FILETIME* pTimeStamp) const
{
    assert(pTimeStamp);
    *pTimeStamp = m_find.ftLastAccessTime;
    return TRUE;
}

inline BOOL MFileLister::GetCreationTime(FILETIME* pTimeStamp) const
{
    assert(pTimeStamp);
    *pTimeStamp = m_find.ftCreationTime;
    return TRUE;
}

inline DWORD MFileLister::GetFileAttributes() const
{
    return m_find.dwFileAttributes;
}

inline BOOL MFileLister::MatchesMask(DWORD dwMask) const
{
    return MFileLister::GetFileAttributes() & dwMask;
}

inline BOOL MFileLister::IsReadOnly() const
{
    return m_find.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
}

inline BOOL MFileLister::IsDirectory() const
{
    return m_find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

inline BOOL MFileLister::IsCompressed() const
{
    return m_find.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED;
}

inline BOOL MFileLister::IsSystem() const
{
    return m_find.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM;
}

inline BOOL MFileLister::IsHidden() const
{
    return m_find.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
}

inline BOOL MFileLister::IsTemporary() const
{
    return m_find.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY;
}

inline BOOL MFileLister::IsNormal() const
{
    return m_find.dwFileAttributes & FILE_ATTRIBUTE_NORMAL;
}

inline BOOL MFileLister::IsArchived() const
{
    return m_find.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE;
}

inline LPCTSTR MFileLister::GetRootDir() const
{
    return m_szRootDir;
}

inline LPCTSTR MFileLister::GetFileName() const
{
    return m_find.cFileName;
}

inline LPCTSTR MFileLister::GetAlternateFileName() const
{
    return m_find.cAlternateFileName;
}

inline BOOL MFileLister::FindNextFile()
{
    assert(m_hFind != INVALID_HANDLE_VALUE);
    BOOL bFound = ::FindNextFile(m_hFind, &m_find);
    return bFound;
}

inline BOOL MFileLister::FindClose()
{
    assert(m_hFind != INVALID_HANDLE_VALUE);
    return ::FindClose(m_hFind);
}

template <typename T_STRING>
inline BOOL MFileLister::GetFilePath(T_STRING& strPath)
{
    TCHAR szPath[MAX_PATH] = TEXT("");
    if (m_szRootDir[0])
    {
        lstrcpy(szPath, m_szRootDir);
        Path_AddSep(szPath);
    }
    lstrcat(szPath, MFileLister::GetFileName());
    strPath = szPath;
    return TRUE;
}

inline BOOL MFileLister::IsDots() const
{
    if (m_find.cFileName[0] == TEXT('.'))
    {
        if (!m_find.cFileName[1])
            return TRUE;

        if (m_find.cFileName[1] == TEXT('.') && !m_find.cFileName[2])
            return TRUE;
    }
    return FALSE;
}

inline MFileLister::MFileLister(
    LPCTSTR pszWildCard, BOOL bUseFullPath/* = FALSE*/)
{
    m_hFind = INVALID_HANDLE_VALUE;
    m_szRootDir[0] = TEXT('\0');

    MFileLister::FindFirstFile(pszWildCard, bUseFullPath);
}

inline BOOL MFileLister::GetFilePath(LPTSTR pszPath, DWORD cchPath) const
{
    assert(pszPath);

    TCHAR szPath[MAX_PATH];
    if (m_szRootDir[0])
    {
        lstrcpy(szPath, m_szRootDir);
        Path_AddSep(szPath);
    }
    else
        szPath[0] = 0;
    lstrcat(szPath, MFileLister::GetFileName());

    if (pszPath)
    {
        lstrcpyn(pszPath, szPath, cchPath);
        return TRUE;
    }
    return FALSE;
}

inline BOOL MFileLister::FindFirstFile(
    LPCTSTR pszWildCard/* = TEXT("*")*/, BOOL bUseFullPath/* = FALSE*/)
{
    assert(pszWildCard);

    TCHAR szPath[MAX_PATH];
    lstrcpyn(szPath, pszWildCard, MAX_PATH);
    LPTSTR pch = Path_FindTitle(szPath);

    if (pch != szPath)
    {
        pch--;
        *pch = '\0';
        if (bUseFullPath)
            ::GetFullPathName(szPath, MAX_PATH, m_szRootDir, NULL);
        else
            lstrcpyn(m_szRootDir, szPath, MAX_PATH);
    }
    else 
    {
        if (bUseFullPath)
            ::GetCurrentDirectory(MAX_PATH, m_szRootDir);
        else
            m_szRootDir[0] = 0;
    }

    m_hFind = ::FindFirstFile(pszWildCard, &m_find);
    return (m_hFind != INVALID_HANDLE_VALUE);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFILELISTER_HPP_
