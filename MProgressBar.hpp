// MProgressBar.hpp -- Win32API progress bar wrapper            -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPROGRESSBAR_HPP_
#define MZC4_MPROGRESSBAR_HPP_      2       /* Version 2 */

class MProgressBar;

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MProgressBar : public MWindowBase
{
public:
    MProgressBar();
    virtual LPCTSTR GetWndClassName() const;

    VOID SetRange(SHORT nLower, SHORT nUpper);
#if (_WIN32_IE >= 0x0300)
    VOID GetRange(INT& nLower, INT& nUpper);
    VOID SetRange32(INT nLower, INT nUpper);

    INT GetPos();
#endif  // (_WIN32_IE >= 0x0300)
    INT SetPos(INT nPos);
    INT OffsetPos(INT nPos);
    INT SetStep(INT nStep);
    INT StepIt();
};

////////////////////////////////////////////////////////////////////////////

inline MProgressBar::MProgressBar()
{
}

inline /*virtual*/ LPCTSTR MProgressBar::GetWndClassName() const
{
    return PROGRESS_CLASS;
}

inline VOID MProgressBar::SetRange(SHORT nLower, SHORT nUpper)
{
    SendMessageDx(PBM_SETRANGE, 0, MAKELPARAM(nLower, nUpper));
}

#if (_WIN32_IE >= 0x0300)
    inline VOID MProgressBar::SetRange32(INT nLower, INT nUpper)
    {
        SendMessageDx(PBM_SETRANGE32, (WPARAM)nLower, (LPARAM)nUpper);
    }

    inline VOID MProgressBar::GetRange(INT& nLower, INT& nUpper)
    {
        PBRANGE range;
        ZeroMemory(&range, sizeof(range));
        SendMessageDx(PBM_GETRANGE, TRUE, (LPARAM)&range);
        nLower = range.iLow;
        nUpper = range.iHigh;
    }

    inline INT MProgressBar::GetPos()
    {
        return (INT)SendMessageDx(PBM_GETPOS);
    }
#endif  // (_WIN32_IE >= 0x0300)

inline INT MProgressBar::SetPos(INT nPos)
{
    return (INT)SendMessageDx(PBM_SETPOS, (WPARAM)nPos);
}

inline INT MProgressBar::OffsetPos(INT nPos)
{
    return (INT)SendMessageDx(PBM_DELTAPOS, (WPARAM)nPos);
}

inline INT MProgressBar::SetStep(INT nStep)
{
    return (INT)SendMessageDx(PBM_SETSTEP, (WPARAM)nStep);
}

inline INT MProgressBar::StepIt()
{
    return (INT)SendMessageDx(PBM_STEPIT);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MPROGRESSBAR_HPP_
