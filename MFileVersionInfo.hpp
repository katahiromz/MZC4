// MFileVersionInfo.hpp -- EXE file version info getter         -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFILEVERSIONINFO_HPP_
#define MZC4_MFILEVERSIONINFO_HPP_

struct MLangAndCodePage;
class MFileVersionInfo;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

#pragma comment(lib, "version.lib")

////////////////////////////////////////////////////////////////////////////

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

// FootmarkDx and FootmarkThisDx
#ifndef FootmarkDx
    #define FootmarkDx()
#endif
#ifndef FootmarkThisDx
    #define FootmarkThisDx()
#endif

////////////////////////////////////////////////////////////////////////////
// MLangAndCodePage

#include <pshpack1.h>
struct MLangAndCodePage
{
    WORD wLanguage;
    WORD wCodePage;
};
#include <poppack.h>

////////////////////////////////////////////////////////////////////////////

class MFileVersionInfo
{
public:
    MFileVersionInfo();
    MFileVersionInfo(LPCTSTR pszFileName);
    virtual ~MFileVersionInfo();

    bool operator!() const;

    BOOL Open(LPCTSTR pszFileName);
    BOOL QueryTranslation();
    VOID Close();

    BOOL GetValue(LPCTSTR pszBlockName, MString& strValue) const;
    BOOL GetFixedFileInfo(VS_FIXEDFILEINFO& info) const;

    BOOL GetComments(MString& strValue) const;
    BOOL GetCompanyName(MString& strValue) const;
    BOOL GetFileDescription(MString& strValue) const;
    BOOL GetFileVersion(MString& strValue) const;
    BOOL GetInternalName(MString& strValue) const;
    BOOL GetLegalCopyright(MString& strValue) const;
    BOOL GetLegalTrademarks(MString& strValue) const;
    BOOL GetOriginalFilename(MString& strValue) const;
    BOOL GetPrivateBuild(MString& strValue) const;
    BOOL GetProductName(MString& strValue) const;
    BOOL GetProductVersion(MString& strValue) const;
    BOOL GetSpecialBuild(MString& strValue) const;

    const BYTE *GetData() const;
    INT GetTranslationIndex() const;
    INT GetNumberOfTranslations() const;
    const MLangAndCodePage *GetTranslations() const;

protected:
    BYTE *               m_pbData;
    MLangAndCodePage *   m_pTranslations;
    INT                  m_iTranslation;
    INT                  m_cTranslation;

private:
    // NOTE: MFileVersionInfo is not copyable.
    MFileVersionInfo(const MFileVersionInfo& info);
    MFileVersionInfo& operator=(const MFileVersionInfo& info);
};

////////////////////////////////////////////////////////////////////////////

inline MFileVersionInfo::MFileVersionInfo() :
    m_pbData(NULL), m_pTranslations(NULL), m_iTranslation(-1),
    m_cTranslation(0)
{
}

inline MFileVersionInfo::MFileVersionInfo(LPCTSTR pszFileName) :
    m_pbData(NULL), m_pTranslations(NULL), m_iTranslation(-1),
    m_cTranslation(0)
{
    Open(pszFileName);
}

inline /*virtual*/ MFileVersionInfo::~MFileVersionInfo()
{
    if (m_pbData)
        Close();
}

inline bool MFileVersionInfo::operator!() const
{
    return m_pbData == NULL;
}

inline BOOL MFileVersionInfo::GetComments(MString& strValue) const
{
    return GetValue(TEXT("Comments"), strValue);
}

inline BOOL MFileVersionInfo::GetCompanyName(MString& strValue) const
{
    return GetValue(TEXT("CompanyName"), strValue);
}

inline BOOL MFileVersionInfo::GetFileDescription(MString& strValue) const
{
    return GetValue(TEXT("FileDescription"), strValue);
}

inline BOOL MFileVersionInfo::GetFileVersion(MString& strValue) const
{
    return GetValue(TEXT("FileVersion"), strValue);
}

inline BOOL MFileVersionInfo::GetInternalName(MString& strValue) const
{
    return GetValue(TEXT("InternalName"), strValue);
}

inline BOOL MFileVersionInfo::GetLegalCopyright(MString& strValue) const
{
    return GetValue(TEXT("LegalCopyright"), strValue);
}

inline BOOL MFileVersionInfo::GetLegalTrademarks(MString& strValue) const
{
    return GetValue(TEXT("LegalTrademarks"), strValue);
}

inline BOOL MFileVersionInfo::GetOriginalFilename(MString& strValue) const
{
    return GetValue(TEXT("OriginalFilename"), strValue);
}

inline BOOL MFileVersionInfo::GetPrivateBuild(MString& strValue) const
{
    return GetValue(TEXT("PrivateBuild"), strValue);
}

inline BOOL MFileVersionInfo::GetProductName(MString& strValue) const
{
    return GetValue(TEXT("ProductName"), strValue);
}

inline BOOL MFileVersionInfo::GetProductVersion(MString& strValue) const
{
    return GetValue(TEXT("ProductVersion"), strValue);
}

inline BOOL MFileVersionInfo::GetSpecialBuild(MString& strValue) const
{
    return GetValue(TEXT("SpecialBuild"), strValue);
}

inline const BYTE *MFileVersionInfo::GetData() const
{
    return m_pbData;
}

inline INT MFileVersionInfo::GetTranslationIndex() const
{
    return m_iTranslation;
}

inline INT MFileVersionInfo::GetNumberOfTranslations() const
{
    return m_cTranslation;
}

inline const MLangAndCodePage *MFileVersionInfo::GetTranslations() const
{
    return m_pTranslations;
}

inline VOID MFileVersionInfo::Close()
{
    if (m_pbData)
    {
        delete[] m_pbData;
        m_pbData = NULL;
    }
}

inline BOOL MFileVersionInfo::Open(LPCTSTR pszFileName)
{
    LPTSTR pszFile = const_cast<LPTSTR>(pszFileName);
    DWORD cb = ::GetFileVersionInfoSize(pszFile, NULL);
    if (cb == 0)
    {
        FootmarkThisDx();
        return FALSE;
    }

    delete[] m_pbData;
    m_pbData = new BYTE[cb];
    assert(m_pbData);
    if (!::GetFileVersionInfo(pszFile, 0, cb, m_pbData))
    {
        FootmarkThisDx();
        delete[] m_pbData;
        m_pbData = NULL;
        return FALSE;
    }

    return TRUE;
}

inline BOOL MFileVersionInfo::QueryTranslation()
{
    if (m_pbData == NULL)
        return FALSE;

    LPVOID lpBuffer;
    UINT cbBuffer;
    if (!::VerQueryValue(m_pbData, TEXT("\\VarFileInfo\\Translation"),
                         &lpBuffer, &cbBuffer))
    {
        FootmarkThisDx();
        return FALSE;
    }

    LCID lcid = ::GetThreadLocale();
    WORD wLangID = LANGIDFROMLCID(lcid);

    MLangAndCodePage *pLangAndCodePage =
        reinterpret_cast<MLangAndCodePage *>(lpBuffer);

    INT i, c = static_cast<INT>(cbBuffer / sizeof(MLangAndCodePage));
    for (i = 0; i < c; i++)
    {
        if (pLangAndCodePage[i].wLanguage == wLangID)
            break;
    }

    if (i == c)
    {
        for (i = 0; i < c; i++)
        {
            if (PRIMARYLANGID(pLangAndCodePage[i].wLanguage) == LANG_ENGLISH)
                break;
        }
        if (i == c)
            i = -1;
    }

    m_pTranslations = pLangAndCodePage;
    m_iTranslation = i;
    m_cTranslation = c;
    return TRUE;
}

inline BOOL MFileVersionInfo::GetValue(LPCTSTR pszBlockName, MString& strValue) const
{
    LPVOID pData;
    UINT cb;
    TCHAR szPath[MAX_PATH];
    static const TCHAR szFormat[] = TEXT("\\StringFileInfo\\%04x%04x\\%s");

    if (m_pbData == NULL || m_pTranslations == NULL)
    {
        FootmarkThisDx();
        return FALSE;
    }

    if (m_iTranslation != -1 && m_cTranslation > 0)
    {
        INT i = m_iTranslation;
        ::wsprintf(szPath, szFormat,
            m_pTranslations[i].wLanguage, m_pTranslations[i].wCodePage,
            pszBlockName);
        if (::VerQueryValue(m_pbData, szPath, &pData, &cb))
        {
            strValue = reinterpret_cast<LPCTSTR>(pData);
            return TRUE;
        }
    }

    for (INT i = 0; i < m_cTranslation; i++)
    {
        ::wsprintf(szPath, szFormat,
            m_pTranslations[i].wLanguage, m_pTranslations[i].wCodePage,
            pszBlockName);

        if (::VerQueryValue(m_pbData, szPath, &pData, &cb))
        {
            strValue = reinterpret_cast<LPCTSTR>(pData);
            return TRUE;
        }
    }

    FootmarkThisDx();
    return FALSE;
}

inline BOOL MFileVersionInfo::GetFixedFileInfo(VS_FIXEDFILEINFO& info) const
{
    if (m_pbData == NULL)
    {
        FootmarkThisDx();
        return FALSE;
    }

    LPVOID lpBuffer;
    UINT cbBuffer;
    if (!::VerQueryValue(m_pbData, TEXT("\\"), &lpBuffer, &cbBuffer))
    {
        FootmarkThisDx();
        return FALSE;
    }

    assert(cbBuffer >= sizeof(VS_FIXEDFILEINFO));
    memcpy(&info, lpBuffer, sizeof(VS_FIXEDFILEINFO));
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFILEVERSIONINFO_HPP_
