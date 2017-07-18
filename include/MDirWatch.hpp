// MDirWatch.hpp -- Win32API directory watcher                  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MDIRWATCH_HPP_
#define MZC4_MDIRWATCH_HPP_     3   /* Version 3 */

class MDirWatch;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

///////////////////////////////////////////////////////////////////////////////

class MDirWatch
{
public:
    enum
    {
        check_file_name = FILE_NOTIFY_CHANGE_FILE_NAME,
        check_dir_name = FILE_NOTIFY_CHANGE_DIR_NAME,
        check_attributes = FILE_NOTIFY_CHANGE_ATTRIBUTES,
        check_size = FILE_NOTIFY_CHANGE_SIZE,
        check_last_write = FILE_NOTIFY_CHANGE_LAST_WRITE,
        check_last_access = FILE_NOTIFY_CHANGE_LAST_ACCESS,
        check_creation = FILE_NOTIFY_CHANGE_CREATION,
        check_security =  FILE_NOTIFY_CHANGE_SECURITY,
        check_all = 0x17F
    }; // for dwNotifyChangeFlags

public:
    MDirWatch();
    MDirWatch(HANDLE hFindChange);
    MDirWatch(LPCTSTR pszPath, BOOL bWatchSubTree = TRUE,
              DWORD dwNotifyChangeFlags = MDirWatch::check_all);
    virtual ~MDirWatch();

    bool operator!() const;
    operator HANDLE() const;
    MDirWatch& operator=(HANDLE hFindChange);
    PHANDLE operator&();

    BOOL Attach(HANDLE hFindChange);
    HANDLE Detach();
    HANDLE Handle() const;

    BOOL FindFirstChangeNotification(
        LPCTSTR pszPath, BOOL bWatchSubTree = TRUE,
        DWORD dwNotifyChangeFlags = MDirWatch::check_all);
    BOOL FindNextChangeNotification();  
    BOOL FindCloseChangeNotification();

    DWORD WaitForSingleObject(DWORD dwMilliseconds = INFINITE);
    DWORD WaitForSingleObjectEx(DWORD dwMilliseconds = INFINITE,
                                BOOL bAlertable = TRUE);

public:
    HANDLE m_hFindChange;

private:
    // NOTE: MDirWatch is not copyable.
    MDirWatch(const MDirWatch& dw);
    MDirWatch& operator=(const MDirWatch& dw);
};

////////////////////////////////////////////////////////////////////////////

inline MDirWatch::MDirWatch() : m_hFindChange(INVALID_HANDLE_VALUE)
{
}

inline MDirWatch::MDirWatch(HANDLE hFindChange) :
    m_hFindChange(hFindChange)
{
}

inline MDirWatch::MDirWatch(
    LPCTSTR pszPath, BOOL bWatchSubTree/* = TRUE*/,
    DWORD dwNotifyChangeFlags/* = MDirWatch::check_all*/
) : m_hFindChange(INVALID_HANDLE_VALUE)
{
    FindFirstChangeNotification(pszPath, bWatchSubTree, dwNotifyChangeFlags);
}

inline /*virtual*/ MDirWatch::~MDirWatch()
{
    FindCloseChangeNotification();
}

inline bool MDirWatch::operator!() const
{
    return Handle() == INVALID_HANDLE_VALUE;
}

inline MDirWatch& MDirWatch::operator=(HANDLE hFindChange)
{
    assert(hFindChange != NULL && hFindChange != INVALID_HANDLE_VALUE);
    if (m_hFindChange != hFindChange)
    {
        Attach(hFindChange);
    }
    return *this;
}

inline BOOL MDirWatch::Attach(HANDLE hFindChange)
{
    FindCloseChangeNotification();
    m_hFindChange = hFindChange;
    return m_hFindChange != NULL;
}

inline HANDLE MDirWatch::Detach()
{
    HANDLE hFindChange = m_hFindChange;
    m_hFindChange = INVALID_HANDLE_VALUE;
    return hFindChange;
}

inline HANDLE MDirWatch::Handle() const
{
    return (this ? m_hFindChange : NULL);
}

inline MDirWatch::operator HANDLE() const
{
    return Handle();
}

inline PHANDLE MDirWatch::operator&()
{
    return &m_hFindChange;
}

inline BOOL MDirWatch::FindNextChangeNotification() 
{
    assert(m_hFindChange != INVALID_HANDLE_VALUE);
    BOOL bFound = ::FindNextChangeNotification(m_hFindChange);
    return bFound;
}

inline BOOL MDirWatch::FindCloseChangeNotification()
{
    if (m_hFindChange != INVALID_HANDLE_VALUE)
    {
        BOOL bOK = ::FindCloseChangeNotification(m_hFindChange);
        m_hFindChange = INVALID_HANDLE_VALUE;
        return bOK;
    }
    return FALSE;
}

inline DWORD
MDirWatch::WaitForSingleObject(DWORD dwMilliseconds/* = INFINITE*/)
{
    return ::WaitForSingleObject(m_hFindChange, dwMilliseconds);
}

inline DWORD MDirWatch::WaitForSingleObjectEx(
    DWORD dwMilliseconds/* = INFINITE*/, BOOL bAlertable/* = TRUE*/)
{
    return ::WaitForSingleObjectEx(m_hFindChange,
                                   dwMilliseconds, bAlertable);
}

inline BOOL MDirWatch::FindFirstChangeNotification(
    LPCTSTR pszPath, BOOL bWatchSubTree/* = TRUE*/,
    DWORD dwNotifyChangeFlags/* = MDirWatch::check_all*/)
{
    assert(pszPath);
    assert(m_hFindChange == INVALID_HANDLE_VALUE);
    m_hFindChange = ::FindFirstChangeNotification(
        pszPath, bWatchSubTree, dwNotifyChangeFlags);
    return m_hFindChange != INVALID_HANDLE_VALUE;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MDIRWATCH_HPP_
