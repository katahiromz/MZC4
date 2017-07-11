// MMutex.hpp -- Win32API mutex object wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MMUTEX_HPP_
#define MZC4_MMUTEX_HPP_        2   /* Version 2 */

class MMutex;

////////////////////////////////////////////////////////////////////////////

#include "MSyncBase.hpp"

class MMutex : public MSyncBase
{
public:
    MMutex();
    MMutex(BOOL bInitiallyOwn, LPCTSTR lpszName = NULL,
           LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
    BOOL CreateMutex(BOOL bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL,
           LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
    virtual BOOL Unlock();
};

////////////////////////////////////////////////////////////////////////////

inline MMutex::MMutex()
{
}

inline MMutex::MMutex(BOOL bInitiallyOwn/* = FALSE*/,
    LPCTSTR lpszName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttribute/* = NULL*/)
{
    CreateMutex(bInitiallyOwn, lpszName, lpsaAttribute);
}

inline BOOL MMutex::CreateMutex(BOOL bInitiallyOwn/* = FALSE*/,
    LPCTSTR lpszName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttribute/* = NULL*/)
{
    Attach(::CreateMutex(lpsaAttribute, bInitiallyOwn, lpszName));
    return m_hObject != NULL;
}

inline /*virtual*/ BOOL MMutex::Unlock()
{
    return ::ReleaseMutex(m_hObject);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MMUTEX_HPP_
