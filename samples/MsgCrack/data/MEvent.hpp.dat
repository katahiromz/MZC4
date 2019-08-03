// MEvent.hpp -- Win32API event object wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MEVENT_HPP_
#define MZC4_MEVENT_HPP_        3   /* Version 3 */

class MEvent;

////////////////////////////////////////////////////////////////////////////

#include "MSyncBase.hpp"

class MEvent : public MSyncBase
{
public:
    MEvent();
    MEvent(HANDLE hEvent);
    MEvent(const MEvent& e);
    MEvent& operator=(HANDLE hEvent);
    MEvent& operator=(const MEvent& e);
    MEvent(BOOL bInitiallyOwn, BOOL bManualReset = FALSE,
           LPCTSTR lpszName = NULL,
           LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);

    BOOL CreateEvent(BOOL bInitiallyOwn = FALSE, BOOL bManualReset = FALSE,
           LPCTSTR lpszName = NULL,
           LPSECURITY_ATTRIBUTES lpsaAttribute = NULL);
    BOOL SetEvent();
    BOOL PulseEvent();
    BOOL ResetEvent();
    virtual BOOL Unlock();
};

////////////////////////////////////////////////////////////////////////////

inline MEvent::MEvent()
{
}

inline MEvent::MEvent(HANDLE hEvent) : MSyncBase(hEvent)
{
}

inline MEvent::MEvent(const MEvent& e)
    : MSyncBase(CloneHandleDx(e))
{
}

inline MEvent& MEvent::operator=(HANDLE hEvent)
{
    if (Handle() != hEvent)
    {
        Attach(hEvent);
    }
    return *this;
}

inline MEvent& MEvent::operator=(const MEvent& e)
{
    if (Handle() != e.Handle())
    {
        HANDLE hEvent = CloneHandleDx(e);
        Attach(hEvent);
    }
    return *this;
}

inline MEvent::MEvent(BOOL bInitiallyOwn, BOOL bManualReset,
                      LPCTSTR lpszName/* = NULL*/,
                      LPSECURITY_ATTRIBUTES lpsaAttribute/* = NULL*/)
    : MSyncBase(::CreateEvent(lpsaAttribute, bManualReset, bInitiallyOwn, lpszName))
{
    assert(Handle());
}
    
inline BOOL MEvent::CreateEvent(
    BOOL bInitiallyOwn/* = FALSE*/, BOOL bManualReset/* = FALSE*/,
    LPCTSTR lpszName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttribute/* = NULL*/)
{
    return Attach(::CreateEvent(lpsaAttribute, bManualReset, bInitiallyOwn, lpszName));
}

inline /*virtual*/ BOOL MEvent::Unlock()
{
    return TRUE;
}

inline BOOL MEvent::SetEvent()
{
    assert(Handle());
    return ::SetEvent(Handle());
}

inline BOOL MEvent::PulseEvent()
{
    assert(Handle());
    return ::PulseEvent(Handle());
}

inline BOOL MEvent::ResetEvent()
{
    assert(Handle());
    return ::ResetEvent(Handle());
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MEVENT_HPP_
