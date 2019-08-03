// MMutex.hpp -- Win32API mutex object wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MMUTEX_HPP_
#define MZC4_MMUTEX_HPP_        3   /* Version 3 */

class MMutex;

////////////////////////////////////////////////////////////////////////////

#include "MSyncBase.hpp"

class MMutex : public MSyncBase
{
public:
    MMutex();
    MMutex(BOOL bInitiallyOwn, LPCTSTR lpszName = NULL,
           LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
    MMutex(HANDLE hMutex);
    MMutex(const MMutex& m);
    MMutex& operator=(HANDLE hMutex);
    MMutex& operator=(const MMutex& m);

    BOOL CreateMutex(BOOL bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL,
           LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
    virtual BOOL Unlock();
};

////////////////////////////////////////////////////////////////////////////

inline MMutex::MMutex()
{
}

inline MMutex::MMutex(HANDLE hMutex) : MSyncBase(hMutex)
{
}

inline MMutex::MMutex(const MMutex& m) : MSyncBase(CloneHandleDx(m))
{
}

inline MMutex& MMutex::operator=(HANDLE hMutex)
{
    if (Handle() != hMutex)
    {
        Attach(hMutex);
    }
    return *this;
}

inline MMutex& MMutex::operator=(const MMutex& m)
{
    if (Handle() != m.Handle())
    {
        HANDLE hMutex = CloneHandleDx(m);
        Attach(hMutex);
    }
    return *this;
}

inline MMutex::MMutex(BOOL bInitiallyOwn/* = FALSE*/,
                      LPCTSTR lpszName/* = NULL*/,
                      LPSECURITY_ATTRIBUTES lpsaAttribute/* = NULL*/)
    : MSyncBase(::CreateMutex(lpsaAttribute, bInitiallyOwn, lpszName))
{
    assert(Handle());
}

inline BOOL MMutex::CreateMutex(BOOL bInitiallyOwn/* = FALSE*/,
    LPCTSTR lpszName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttribute/* = NULL*/)
{
    return Attach(::CreateMutex(lpsaAttribute, bInitiallyOwn, lpszName));
}

inline /*virtual*/ BOOL MMutex::Unlock()
{
    return ::ReleaseMutex(m_hObject);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MMUTEX_HPP_
