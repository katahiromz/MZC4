// MSemaphore.hpp -- Win32API semaphore object wrapper          -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSEMAPHORE_HPP_
#define MZC4_MSEMAPHORE_HPP_     3   /* Version 3 */

class MSemaphore;

////////////////////////////////////////////////////////////////////////////

#include "MSyncBase.hpp"

class MSemaphore : public MSyncBase
{
public:
    MSemaphore();
    MSemaphore(HANDLE hSem);
    MSemaphore(const MSemaphore& s);
    MSemaphore& operator=(HANDLE hSem);
    MSemaphore& operator=(const MSemaphore& s);
    MSemaphore(LONG lInitialCount, LONG lMaxCount = 1,
               LPCTSTR pstrName = NULL,
               LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
    BOOL CreateSemaphore(LONG lInitialCount = 1, LONG lMaxCount = 1,
                         LPCTSTR pstrName = NULL,
                         LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
    virtual BOOL Unlock();
    virtual BOOL Unlock(LONG lCount, LPLONG lprevCount = NULL);
};

////////////////////////////////////////////////////////////////////////////

inline MSemaphore::MSemaphore()
{
}

inline MSemaphore::MSemaphore(HANDLE hSem) : MSyncBase(hSem)
{
}

inline MSemaphore::MSemaphore(const MSemaphore& s)
    : MSyncBase(CloneHandleDx(s))
{
}

inline MSemaphore& MSemaphore::operator=(HANDLE hSem)
{
    if (Handle() != hSem)
    {
        Attach(hSem);
    }
    return *this;
}

inline MSemaphore& MSemaphore::operator=(const MSemaphore& s)
{
    if (Handle() != s.Handle())
    {
        HANDLE hSem = CloneHandleDx(s);
        Attach(hSem);
    }
    return *this;
}

inline MSemaphore::MSemaphore(LONG lInitialCount,
    LONG lMaxCount/* = 1*/, LPCTSTR pstrName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttributes/* = NULL*/)
    : MSyncBase(::CreateSemaphore(lpsaAttributes, lInitialCount, lMaxCount, pstrName))
{
    assert(lMaxCount > 0);
    assert(lInitialCount <= lMaxCount);
}

inline /*virtual*/ BOOL MSemaphore::Unlock()
{
    return Unlock(1);
}

inline BOOL MSemaphore::CreateSemaphore(
    LONG lInitialCount/* = 1*/, LONG lMaxCount/* = 1*/,
    LPCTSTR pstrName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttributes/* = NULL*/)
{
    assert(lMaxCount > 0);
    assert(lInitialCount <= lMaxCount);
    return Attach(::CreateSemaphore(lpsaAttributes, lInitialCount, lMaxCount, pstrName));
}

inline /*virtual*/ BOOL MSemaphore::Unlock(LONG lCount, LPLONG lprevCount/* = NULL*/)
{
    return ::ReleaseSemaphore(m_hObject, lCount, lprevCount);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSEMAPHORE_HPP_
