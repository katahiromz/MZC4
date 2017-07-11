// MCriticalSection.hpp -- Win32API critical section wrapper -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MCRITICALSECTION_HPP_
#define MZC4_MCRITICALSECTION_HPP_  2   /* Version 2 */

class MCriticalSection;

////////////////////////////////////////////////////////////////////////////

// FootmarkDx and FootmarkThisDx
#ifndef FootmarkDx
    #define FootmarkDx()
#endif
#ifndef FootmarkThisDx
    #define FootmarkThisDx()
#endif

////////////////////////////////////////////////////////////////////////////

#include "MSyncBase.hpp"

class MCriticalSection : public MSyncBase
{
public:
    MCriticalSection();
    MCriticalSection(DWORD dwSpinCount);
    virtual ~MCriticalSection();
    operator LPCRITICAL_SECTION();
    virtual BOOL Lock();
    virtual BOOL Lock(DWORD dwTimeout);
    virtual BOOL Unlock();

protected:
    CRITICAL_SECTION m_cs;
};

////////////////////////////////////////////////////////////////////////////

inline MCriticalSection::MCriticalSection()
{
    ::InitializeCriticalSection(&m_cs);
}

#if (_WIN32_WINNT >= 0x0403)
inline MCriticalSection::MCriticalSection(DWORD dwSpinCount)
#else
inline MCriticalSection::MCriticalSection(DWORD)
#endif
{
#if (_WIN32_WINNT >= 0x0403)
    ::InitializeCriticalSectionAndSpinCount(&m_cs, dwSpinCount);
#else
    FootmarkThisDx();
    ::InitializeCriticalSection(&m_cs);
#endif
}

inline /*virtual*/ MCriticalSection::~MCriticalSection()
{
    ::DeleteCriticalSection(&m_cs);
}

inline /*virtual*/ BOOL MCriticalSection::Lock()
{
    ::EnterCriticalSection(&m_cs);
    return TRUE;
}

inline /*virtual*/ BOOL MCriticalSection::Lock(DWORD dwTimeout)
{
#if (_WIN32_WINNT >= 0x0400)
    if (dwTimeout != 0)
        FootmarkThisDx();
    return ::TryEnterCriticalSection(&m_cs);
#else
    FootmarkThisDx();
    return FALSE;
#endif
}

inline /*virtual*/ BOOL MCriticalSection::Unlock()
{
    ::LeaveCriticalSection(&m_cs);
    return TRUE;
}

inline MCriticalSection::operator LPCRITICAL_SECTION()
{
    return &m_cs;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCRITICALSECTION_HPP_
