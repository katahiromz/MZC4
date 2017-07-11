// MAnimateCtrl.hpp -- Win32API animate control wrapper    -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MANIMATECTRL_HPP_
#define MZC4_MANIMATECTRL_HPP_      2   /* Version 2 */

class MAnimateCtrl;

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MAnimateCtrl : public MWindowBase
{
public:
    MAnimateCtrl();
    virtual LPCTSTR GetWndClassName() const;

    BOOL Open(LPCTSTR pszFileName);
    BOOL Open(UINT nAVIResourceID);
    BOOL Play(UINT nFrom, UINT nTo, UINT nRep);
    BOOL Stop();
    BOOL Close();
    BOOL Seek(UINT nTo);
};

////////////////////////////////////////////////////////////////////////////

inline MAnimateCtrl::MAnimateCtrl()
{
}

inline /*virtual*/ LPCTSTR MAnimateCtrl::GetWndClassName() const
{
    return ANIMATE_CLASS;
}

inline BOOL MAnimateCtrl::Open(LPCTSTR pszFileName)
{
    assert(::IsWindow(m_hwnd));
    return Animate_Open(m_hwnd, pszFileName);
}

inline BOOL MAnimateCtrl::Open(UINT nAVIResourceID)
{
    assert(::IsWindow(m_hwnd));
    return Animate_Open(m_hwnd, MAKEINTRESOURCE(nAVIResourceID));
}

inline BOOL MAnimateCtrl::Play(UINT nFrom, UINT nTo, UINT nRep)
{
    assert(::IsWindow(m_hwnd));
    return Animate_Play(m_hwnd, nFrom, nTo, nRep);
}

inline BOOL MAnimateCtrl::Stop()
{
    assert(::IsWindow(m_hwnd));
    return Animate_Stop(m_hwnd);
}

inline BOOL MAnimateCtrl::Close()
{
    assert(::IsWindow(m_hwnd));
    return Animate_Close(m_hwnd);
}

inline BOOL MAnimateCtrl::Seek(UINT nTo)
{
    assert(::IsWindow(m_hwnd));
    return Animate_Seek(m_hwnd, nTo);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MANIMATECTRL_HPP_
