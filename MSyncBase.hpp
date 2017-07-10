// MSyncBase.hpp -- Win32API synchronization object wrapper   -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSYNCBASE_HPP_
#define MZC4_MSYNCBASE_HPP_       2   /* Version 2 */

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

public:
    virtual ~MSyncBase();
    bool operator!() const;
    operator HANDLE() const;
    MSyncBase& operator=(HANDLE hObject);
    bool operator==(HANDLE hObject) const;
    bool operator!=(HANDLE hObject) const;

    VOID Attach(HANDLE hObject);
    HANDLE Detach();
    HANDLE Handle() const;

    virtual BOOL Lock(DWORD dwTimeout = INFINITE);
    virtual BOOL Unlock() = 0;

    BOOL CloseHandle();
};

////////////////////////////////////////////////////////////////////////////

inline MSyncBase::MSyncBase() : m_hObject(NULL)
{
}

inline /*virtual*/ MSyncBase::~MSyncBase()
{
    if (m_hObject)
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
    return m_hObject == hObject;
}

inline bool MSyncBase::operator!=(HANDLE hObject) const
{
    return m_hObject != hObject;
}

inline MSyncBase& MSyncBase::operator=(HANDLE hObject)
{
    if (m_hObject != hObject)
        Attach(hObject);
    return *this;
}

inline VOID MSyncBase::Attach(HANDLE hObject)
{
    if (m_hObject)
        CloseHandle();
    assert(hObject);
    assert(m_hObject == NULL);
    m_hObject = hObject;
}

inline HANDLE MSyncBase::Detach()
{
    HANDLE hObject = m_hObject;
    m_hObject = NULL;
    return hObject;
}

inline /*virtual*/ BOOL MSyncBase::Lock(DWORD dwTimeout/* = INFINITE*/)
{
    return ::WaitForSingleObject(m_hObject, dwTimeout) == WAIT_OBJECT_0;
}

inline BOOL MSyncBase::CloseHandle()
{
    BOOL bOK = ::CloseHandle(m_hObject);
    assert(bOK);
    m_hObject = NULL;
    return bOK;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSYNCBASE_HPP_
