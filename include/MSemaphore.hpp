// MSemaphore.hpp -- Win32API semaphore object wrapper          -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSEMAPHORE_HPP_
#define MZC4_MSEMAPHORE_HPP_     2   /* Version 2 */

class MSemaphore;

////////////////////////////////////////////////////////////////////////////

#include "MSyncBase.hpp"

class MSemaphore : public MSyncBase
{
public:
    MSemaphore();
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

inline MSemaphore::MSemaphore(LONG lInitialCount,
    LONG lMaxCount/* = 1*/, LPCTSTR pstrName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttributes/* = NULL*/)
{
    assert(lMaxCount > 0);
    assert(lInitialCount <= lMaxCount);

    CreateSemaphore(lInitialCount, lMaxCount, pstrName, lpsaAttributes);
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

    Attach(::CreateSemaphore(
        lpsaAttributes, lInitialCount, lMaxCount, pstrName));
    return m_hObject != NULL;
}

inline /*virtual*/ BOOL MSemaphore::Unlock(LONG lCount, LPLONG lprevCount/* = NULL*/)
{
    return ::ReleaseSemaphore(m_hObject, lCount, lprevCount);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSEMAPHORE_HPP_
