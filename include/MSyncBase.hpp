// MSyncBase.hpp -- Win32API synchronization object wrapper   -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSYNCBASE_HPP_
#define MZC4_MSYNCBASE_HPP_       3   /* Version 3 */

class MSyncBase;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

class MSyncBase
{
protected:
    HANDLE m_hObject;
    MSyncBase();
    MSyncBase(HANDLE hObject);
    MSyncBase(const MSyncBase& base);
    MSyncBase& operator=(const MSyncBase& base);

public:
    virtual ~MSyncBase();
    bool operator!() const;
    operator HANDLE() const;
    MSyncBase& operator=(HANDLE hObject);
    bool operator==(HANDLE hObject) const;
    bool operator!=(HANDLE hObject) const;

    BOOL Attach(HANDLE hObject);
    HANDLE Detach();
    HANDLE Handle() const;

    virtual BOOL Lock(DWORD dwTimeout = INFINITE);
    virtual BOOL Unlock() = 0;

    BOOL CloseHandle();

    static HANDLE CloneHandleDx(HANDLE hObject);
};

////////////////////////////////////////////////////////////////////////////

inline /*static*/ HANDLE MSyncBase::CloneHandleDx(HANDLE hObject)
{
    if (hObject == NULL)
        return NULL;

    HANDLE hDup = NULL;
    HANDLE hProcess = ::GetCurrentProcess();
    ::DuplicateHandle(hProcess, hObject, hProcess, &hDup, 0,
                      FALSE, DUPLICATE_SAME_ACCESS);
    return hDup;
}

inline MSyncBase::MSyncBase() : m_hObject(NULL)
{
}

inline MSyncBase::MSyncBase(HANDLE hObject) : m_hObject(hObject)
{
}

inline MSyncBase::MSyncBase(const MSyncBase& base)
    : m_hObject(CloneHandleDx(base))
{
}

inline MSyncBase& MSyncBase::operator=(const MSyncBase& base)
{
    if (Handle() != base.Handle())
    {
        HANDLE hObject = CloneHandleDx(base);
        Attach(hObject);
    }
    return *this;
}

inline /*virtual*/ MSyncBase::~MSyncBase()
{
    CloseHandle();
}

inline HANDLE MSyncBase::Handle() const
{
    return (this ? m_hObject : NULL);
}

inline MSyncBase::operator HANDLE() const
{
    return Handle();
}

inline bool MSyncBase::operator!() const
{
    return Handle() == NULL;
}

inline bool MSyncBase::operator==(HANDLE hObject) const
{
    return Handle() == hObject;
}

inline bool MSyncBase::operator!=(HANDLE hObject) const
{
    return Handle() != hObject;
}

inline MSyncBase& MSyncBase::operator=(HANDLE hObject)
{
    if (m_hObject != hObject)
    {
        Attach(hObject);
    }
    return *this;
}

inline BOOL MSyncBase::Attach(HANDLE hObject)
{
    CloseHandle();
    m_hObject = hObject;
    return m_hObject != NULL;
}

inline HANDLE MSyncBase::Detach()
{
    HANDLE hObject = m_hObject;
    m_hObject = NULL;
    return hObject;
}

inline /*virtual*/ BOOL MSyncBase::Lock(DWORD dwTimeout/* = INFINITE*/)
{
    assert(Handle());
    return ::WaitForSingleObject(Handle(), dwTimeout) == WAIT_OBJECT_0;
}

inline BOOL MSyncBase::CloseHandle()
{
    if (m_hObject)
    {
        BOOL bOK = ::CloseHandle(m_hObject);
        m_hObject = NULL;
        return bOK;
    }
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSYNCBASE_HPP_
