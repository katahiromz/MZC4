// MInterProcessShare.hpp -- Win32API interprocess shared data  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MINTERPROCESSSHARE_HPP_
#define MZC4_MINTERPROCESSSHARE_HPP_    5   /* Version 5 */

// class MInterProcessShare<T_DATA>;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

template <typename T_DATA>
class MInterProcessShare
{
public:
    MInterProcessShare();
    MInterProcessShare(const TCHAR *pszName, BOOL *pfAlreadyExists = NULL,
                       SECURITY_ATTRIBUTES *psa = NULL);
    virtual ~MInterProcessShare();

    BOOL Create(const TCHAR *pszName, BOOL *pfAlreadyExists = NULL,
                SECURITY_ATTRIBUTES *psa = NULL);
    void Close();

    operator bool() const;
    bool operator!() const;

    T_DATA* Lock(DWORD dwTimeout = 1500);
    BOOL Unlock();
    BOOL IsLocked() const;

          HANDLE& Handle();
    const HANDLE& Handle() const;

          HANDLE& MutexHandle();
    const HANDLE& MutexHandle() const;

protected:
    HANDLE m_hMutex;
    HANDLE m_hFileMapping;
    T_DATA *m_pData;
};



////////////////////////////////////////////////////////////////////////////

template <typename T_DATA>
inline MInterProcessShare<T_DATA>::MInterProcessShare() :
    m_hMutex(NULL), m_hFileMapping(NULL), m_pData(NULL)
{
}

template <typename T_DATA>
inline MInterProcessShare<T_DATA>::MInterProcessShare(
    const TCHAR *pszName, BOOL *pfAlreadyExists/* = NULL*/,
    SECURITY_ATTRIBUTES *psa/* = NULL*/)
    : m_hMutex(NULL), m_hFileMapping(NULL), m_pData(NULL)
{
    Create(pszName, pfAlreadyExists, psa);
}

template <typename T_DATA>
inline /*virtual*/ MInterProcessShare<T_DATA>::~MInterProcessShare()
{
    Close();
}

template <typename T_DATA>
inline HANDLE& MInterProcessShare<T_DATA>::MutexHandle()
{
    return m_hMutex;
}

template <typename T_DATA>
inline const HANDLE& MInterProcessShare<T_DATA>::MutexHandle() const
{
    return m_hMutex;
}

template <typename T_DATA>
inline HANDLE& MInterProcessShare<T_DATA>::Handle()
{
    return m_hFileMapping;
}

template <typename T_DATA>
inline const HANDLE& MInterProcessShare<T_DATA>::Handle() const
{
    return m_hFileMapping;
}

template <typename T_DATA>
inline BOOL MInterProcessShare<T_DATA>::IsLocked() const
{
    return m_pData != NULL;
}

template <typename T_DATA>
MInterProcessShare<T_DATA>::operator bool() const
{
    return m_hMutex != NULL;
}

template <typename T_DATA>
inline bool MInterProcessShare<T_DATA>::operator!() const
{
    return !m_hMutex;
}

template <typename T_DATA>
BOOL MInterProcessShare<T_DATA>::Create(
    const TCHAR *pszName, BOOL *pfAlreadyExists/* = NULL*/,
    SECURITY_ATTRIBUTES *psa/* = NULL*/)
{
    Close();

    if (pfAlreadyExists)
    {
        *pfAlreadyExists = FALSE;
    }

    // mutex name
    TCHAR szName[MAX_PATH];
    lstrcpyn(szName, pszName, MAX_PATH);
    lstrcat(szName, TEXT(" Mutex"));

    m_hMutex = ::CreateMutex(psa, TRUE, szName);
    if (!m_hMutex)
    {
        return FALSE;
    }

    // file mapping name
    lstrcpyn(szName, pszName, MAX_PATH);
    lstrcat(szName, TEXT(" FileMapping"));

    m_hFileMapping = ::CreateFileMapping(INVALID_HANDLE_VALUE,
        psa, PAGE_READWRITE, 0, sizeof(T_DATA), szName);
    if (!m_hFileMapping)
    {
        Close();
        return FALSE;
    }
    DWORD dwError = ::GetLastError();

    ::ReleaseMutex(m_hMutex);

    if (dwError == ERROR_ALREADY_EXISTS && pfAlreadyExists)
    {
        *pfAlreadyExists = TRUE;
    }

    return TRUE;
}

template <typename T_DATA>
void MInterProcessShare<T_DATA>::Close()
{
    if (IsLocked())
    {
        Unlock();
    }

    if (m_hFileMapping)
    {
        BOOL bRet = ::CloseHandle(m_hFileMapping);
        assert(bRet);
        m_hFileMapping = NULL;
    }

    if (m_hMutex)
    {
        BOOL bRet = ::CloseHandle(m_hMutex);
        assert(bRet);
        m_hMutex = NULL;
    }
}

template <typename T_DATA>
inline T_DATA* MInterProcessShare<T_DATA>::Lock(DWORD dwTimeout/* = 1500*/)
{
    assert(!IsLocked());

    if (IsLocked())
        return m_pData;

    if (::WaitForSingleObject(m_hMutex, dwTimeout) != WAIT_OBJECT_0)
        return NULL;

    m_pData = reinterpret_cast<T_DATA *>(::MapViewOfFile(
        m_hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(T_DATA)));
    assert(m_pData);

    return m_pData;
}

template <typename T_DATA>
inline BOOL MInterProcessShare<T_DATA>::Unlock()
{
    if (!IsLocked())
        return FALSE;

    BOOL bRet = ::FlushViewOfFile(m_pData, sizeof(T_DATA));
    assert(bRet);

    bRet = ::UnmapViewOfFile(m_pData);
    assert(bRet);

    m_pData = NULL;

    bRet = ::ReleaseMutex(m_hMutex);
    assert(bRet);

    return bRet;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MINTERPROCESSSHARE_HPP_
