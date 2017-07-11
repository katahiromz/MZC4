// MEvent.hpp -- Win32API event object wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MEVENT_HPP_
#define MZC4_MEVENT_HPP_        2   /* Version 2 */

class MEvent;

////////////////////////////////////////////////////////////////////////////

#include "MSyncBase.hpp"

class MEvent : public MSyncBase
{
public:
    MEvent();
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

inline MEvent::MEvent(BOOL bInitiallyOwn,
    BOOL bManualReset, LPCTSTR lpszName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttribute/* = NULL*/)
{
    CreateEvent(bInitiallyOwn, bManualReset, lpszName, lpsaAttribute);
    assert(m_hObject != NULL);
}
    
inline BOOL MEvent::CreateEvent(
    BOOL bInitiallyOwn/* = FALSE*/, BOOL bManualReset/* = FALSE*/,
    LPCTSTR lpszName/* = NULL*/,
    LPSECURITY_ATTRIBUTES lpsaAttribute/* = NULL*/)
{
    assert(m_hObject == NULL);
    Attach(::CreateEvent(
        lpsaAttribute, bManualReset, bInitiallyOwn, lpszName));
    return m_hObject != NULL;
}

inline /*virtual*/ BOOL MEvent::Unlock()
{
    return TRUE;
}

inline BOOL MEvent::SetEvent()
{
    assert(m_hObject != NULL);
    return ::SetEvent(m_hObject);
}

inline BOOL MEvent::PulseEvent()
{
    assert(m_hObject != NULL);
    return ::PulseEvent(m_hObject);
}

inline BOOL MEvent::ResetEvent()
{
    assert(m_hObject != NULL);
    return ::ResetEvent(m_hObject);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MEVENT_HPP_
