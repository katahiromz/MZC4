// MPagerCtrl.hpp -- Win32API pager control wrapper         -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPAGERCTRL_HPP_
#define MZC4_MPAGERCTRL_HPP_        2   /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

#if (_WIN32_IE >= 0x0400)
    class MPagerCtrl : public MWindowBase
    {
    public:
        MPagerCtrl();
        virtual LPCTSTR GetWndClassNameDx() const;

        INT GetButtonSize() const;
        INT SetButtonSize(INT nButtonSize);

        DWORD GetButtonState(INT nButton) const;

        COLORREF GetBkColor() const;
        COLORREF SetBkColor(COLORREF clrBk);

        INT GetBorder() const;
        INT SetBorder(INT nBorderSize);

        INT GetPos() const;
        INT SetPos(INT nPos);

        VOID SetChild(HWND hWndChild);
        VOID ForwardMouse(BOOL bForward = TRUE);
        VOID RecalcSize();
        VOID GetDropTarget(IDropTarget** ppDropTarget);
    };
#endif  // (_WIN32_IE >= 0x0400)

////////////////////////////////////////////////////////////////////////////

#if (_WIN32_IE >= 0x0400)
    inline MPagerCtrl::MPagerCtrl()
    {
    }

    inline /*virtual*/ LPCTSTR MPagerCtrl::GetWndClassNameDx() const
    {
        return WC_PAGESCROLLER;
    }

    inline INT MPagerCtrl::GetButtonSize() const
    {
        return (INT)SendMessageDx(PGM_GETBUTTONSIZE);
    }

    inline INT MPagerCtrl::SetButtonSize(INT nButtonSize)
    {
        return (INT)SendMessageDx(PGM_SETBUTTONSIZE, 0, nButtonSize);
    }

    inline DWORD MPagerCtrl::GetButtonState(INT nButton) const
    {
        assert(nButton == PGB_TOPORLEFT || nButton == PGB_BOTTOMORRIGHT);
        return (DWORD)SendMessageDx(PGM_GETBUTTONSTATE, 0, nButton);
    }

    inline COLORREF MPagerCtrl::GetBkColor() const
    {
        return (COLORREF)SendMessageDx(PGM_GETBKCOLOR);
    }

    inline COLORREF MPagerCtrl::SetBkColor(COLORREF clrBk)
    {
        return (COLORREF)SendMessageDx(PGM_SETBKCOLOR, 0, (LPARAM)clrBk);
    }

    inline INT MPagerCtrl::GetBorder() const
    {
        return (INT)SendMessageDx(PGM_GETBORDER);
    }

    inline INT MPagerCtrl::SetBorder(INT nBorderSize)
    {
        return (INT)SendMessageDx(PGM_SETBORDER, 0, nBorderSize);
    }

    inline INT MPagerCtrl::GetPos() const
    {
        return (INT)SendMessageDx(PGM_GETPOS);
    }

    inline INT MPagerCtrl::SetPos(INT nPos)
    {
        return (INT)SendMessageDx(PGM_SETPOS, 0, nPos);
    }

    inline VOID MPagerCtrl::SetChild(HWND hWndChild)
    {
        SendMessageDx(PGM_SETCHILD, 0, (LPARAM)hWndChild);
    }

    inline VOID MPagerCtrl::ForwardMouse(BOOL bForward/* = TRUE*/)
    {
        SendMessageDx(PGM_FORWARDMOUSE, (WPARAM)bForward);
    }

    inline VOID MPagerCtrl::RecalcSize()
    {
        SendMessageDx(PGM_RECALCSIZE);
    }

    inline VOID MPagerCtrl::GetDropTarget(IDropTarget** ppDropTarget)
    {
        assert(ppDropTarget);
        SendMessageDx(PGM_GETDROPTARGET, 0, (LPARAM)ppDropTarget);
    }
#endif  // (_WIN32_IE >= 0x0400)

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MPAGERCTRL_HPP_
