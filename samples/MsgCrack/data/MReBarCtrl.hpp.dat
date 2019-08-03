// MReBarCtrl.hpp -- Win32API rebar control wrapper             -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MREBARCTRL_HPP_
#define MZC4_MREBARCTRL_HPP_        2       /* Version 2 */

#if (_WIN32_IE >= 0x0300)
    class MReBarCtrl;
#endif

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

#if (_WIN32_IE >= 0x0300)
    class MReBarCtrl : public MWindowBase
    {
    public:
        MReBarCtrl();
        virtual LPCTSTR GetWndClassNameDx() const;

        virtual HWND SetParent(HWND hWndNewParent);

        UINT GetBandCount() const;

        BOOL GetBandInfo(UINT uBand, REBARBANDINFO* prbbi) const;
        BOOL SetBandInfo(UINT uBand, REBARBANDINFO* prbbi);

        BOOL GetBarInfo(REBARINFO* prbi) const;
        BOOL SetBarInfo(REBARINFO* prbi);

        HIMAGELIST GetImageList() const;
        BOOL SetImageList(HIMAGELIST hImageList);

        INT GetRowCount() const;
        INT GetRowHeight(UINT uRow) const;

        BOOL InsertBand(INT nIndex, REBARBANDINFO* prbbi);
        BOOL AddBand(LPREBARBANDINFO lprbbi);
        BOOL DeleteBand(INT nIndex);

        HWND SetNotifyWnd(HWND hWnd);

        VOID AutoSize();

    #if (_WIN32_IE >= 0x0400)
        COLORREF GetTextColor() const;
        COLORREF SetTextColor(COLORREF clr);

        BOOL GetColorScheme(COLORSCHEME* lpcs);
        VOID SetColorScheme(const COLORSCHEME* lpcs);

        COLORREF GetBkColor() const;
        COLORREF SetBkColor(COLORREF clr);

        UINT GetBarHeight() const;
        BOOL GetRect(UINT uBand, LPRECT prc) const;

        HWND GetToolTips() const;
        VOID SetToolTips(HWND hwndToolTips);

        VOID GetBandBorders(UINT uBand, LPRECT prc) const;

        HPALETTE GetPalette() const;
        HPALETTE SetPalette(HPALETTE hPal);

        VOID BeginDrag(INT nIndex, DWORD dwPos = (DWORD)-1);
        VOID BeginDrag(INT nIndex, INT xPos, INT yPos);
        VOID EndDrag();
        VOID DragMove(DWORD dwPos = (DWORD)-1);
        VOID DragMove(INT xPos, INT yPos);

        VOID MaximizeBand(UINT uBand, BOOL bIdeal = FALSE);
        VOID MinimizeBand(UINT uBand);

        BOOL SizeToRect(LPRECT prc);
        INT IDToIndex(UINT uBandID) const;

        BOOL ShowBand(INT nBand, BOOL fShow = TRUE);
        BOOL MoveBand(INT nFrom, INT nTo);
    #endif  // (_WIN32_IE >= 0x0400)
    #if (_WIN32_IE >= 0x0500)
        INT HitTest(RBHITTESTINFO *prbht);
    #endif  // (_WIN32_IE >= 0x0500)
    };
#endif  // (_WIN32_IE >= 0x0300)

////////////////////////////////////////////////////////////////////////////

#if (_WIN32_IE >= 0x0300)
    inline MReBarCtrl::MReBarCtrl()
    {
    }

    inline /*virtual*/ LPCTSTR MReBarCtrl::GetWndClassNameDx() const
    {
        return REBARCLASSNAME;
    }

    inline UINT MReBarCtrl::GetBandCount() const
    {
        return (UINT)SendMessageDx(RB_GETBANDCOUNT);
    }

    inline BOOL MReBarCtrl::GetBandInfo(UINT uBand, REBARBANDINFO* prbbi) const
    {
        return (BOOL)SendMessageDx(RB_GETBANDINFO, uBand, (LPARAM)prbbi);
    }

    inline BOOL MReBarCtrl::SetBandInfo(UINT uBand, REBARBANDINFO* prbbi)
    {
        return (BOOL)SendMessageDx(RB_SETBANDINFO, uBand, (LPARAM)prbbi);
    }

    inline BOOL MReBarCtrl::GetBarInfo(REBARINFO* prbi) const
    {
        return (BOOL)SendMessageDx(RB_GETBARINFO, 0, (LPARAM)prbi);
    }

    inline BOOL MReBarCtrl::SetBarInfo(REBARINFO* prbi)
    {
        return (BOOL)SendMessageDx(RB_SETBARINFO, 0, (LPARAM)prbi);
    }

    inline HIMAGELIST MReBarCtrl::GetImageList() const
    {
        REBARINFO rbi;
        ZeroMemory(&rbi, sizeof(REBARINFO));
        rbi.cbSize = sizeof(REBARINFO);
        rbi.fMask = RBIM_IMAGELIST;
        if (!(BOOL)SendMessageDx(RB_GETBARINFO, 0, (LPARAM)&rbi))
            return NULL;
        return rbi.himl;
    }

    inline BOOL MReBarCtrl::SetImageList(HIMAGELIST hImageList)
    {
        REBARINFO rbi;
        ZeroMemory(&rbi, sizeof(REBARINFO));
        rbi.cbSize = sizeof(REBARINFO);
        rbi.fMask = RBIM_IMAGELIST;
        rbi.himl = hImageList;
        return (BOOL)SendMessageDx(RB_SETBARINFO, 0, (LPARAM)&rbi);
    }

    inline INT MReBarCtrl::GetRowCount() const
    {
        return (INT)SendMessageDx(RB_GETROWCOUNT);
    }

    inline INT MReBarCtrl::GetRowHeight(UINT uRow) const
    {
        return (INT)SendMessageDx(RB_GETROWHEIGHT, uRow);
    }

    inline VOID MReBarCtrl::AutoSize()
    {
        SendMessageDx(WM_SIZE);
    }

    #if (_WIN32_IE >= 0x0400)
        inline COLORREF MReBarCtrl::GetTextColor() const
        {
            return (COLORREF)SendMessageDx(RB_GETTEXTCOLOR);
        }

        inline COLORREF MReBarCtrl::SetTextColor(COLORREF clr)
        {
            return (COLORREF)SendMessageDx(RB_SETTEXTCOLOR, 0, (LPARAM)clr);
        }

        inline BOOL MReBarCtrl::GetColorScheme(COLORSCHEME* lpcs)
        {
            assert(lpcs);
            return (BOOL)SendMessageDx(RB_GETCOLORSCHEME, 0, (LPARAM)lpcs);
        }

        inline VOID MReBarCtrl::SetColorScheme(const COLORSCHEME* lpcs)
        {
            assert(lpcs);
            SendMessageDx(RB_SETCOLORSCHEME, 0, (LPARAM)lpcs);
        }

        inline COLORREF MReBarCtrl::GetBkColor() const
        {
            return (COLORREF)SendMessageDx(RB_GETBKCOLOR);
        }

        inline COLORREF MReBarCtrl::SetBkColor(COLORREF clr)
        {
            return (COLORREF)SendMessageDx(RB_SETBKCOLOR, 0, (LPARAM)clr);
        }

        inline UINT MReBarCtrl::GetBarHeight() const
        {
            return (UINT)SendMessageDx(RB_GETBARHEIGHT);
        }

        inline BOOL MReBarCtrl::GetRect(UINT uBand, LPRECT prc) const
        {
            assert(prc);
            return (BOOL)SendMessageDx(RB_GETRECT, uBand, (LPARAM)prc);
        }

        inline HWND MReBarCtrl::GetToolTips() const
        {
            return (HWND)SendMessageDx(RB_GETTOOLTIPS);
        }

        inline VOID MReBarCtrl::SetToolTips(HWND hwndToolTips)
        {
            SendMessageDx(RB_SETTOOLTIPS, (WPARAM)hwndToolTips);
        }

        inline VOID MReBarCtrl::GetBandBorders(UINT uBand, LPRECT prc) const
        {
            assert(prc);
            SendMessageDx(RB_GETBANDBORDERS, uBand, (LPARAM)prc);
        }

        inline HPALETTE MReBarCtrl::GetPalette() const
        {
            return (HPALETTE)SendMessageDx(RB_GETPALETTE);
        }

        inline HPALETTE MReBarCtrl::SetPalette(HPALETTE hPal)
        {
            return (HPALETTE)SendMessageDx(RB_SETPALETTE, 0, (LPARAM)hPal);
        }

        inline VOID MReBarCtrl::BeginDrag(INT nIndex, DWORD dwPos/* = (DWORD)-1*/)
        {
            SendMessageDx(RB_BEGINDRAG, (WPARAM)nIndex, (LPARAM)dwPos);
        }

        inline VOID MReBarCtrl::BeginDrag(INT nIndex, INT xPos, INT yPos)
        {
            return BeginDrag(nIndex, MAKELONG(xPos, yPos));
        }

        inline VOID MReBarCtrl::EndDrag()
        {
            SendMessageDx(RB_ENDDRAG);
        }

        inline VOID MReBarCtrl::DragMove(DWORD dwPos/* = (DWORD)-1*/)
        {
            SendMessageDx(RB_DRAGMOVE, 0, (LPARAM)dwPos);
        }

        inline VOID MReBarCtrl::DragMove(INT xPos, INT yPos)
        {
            DragMove(MAKELONG(xPos, yPos));
        }

        inline VOID MReBarCtrl::MaximizeBand(UINT uBand, BOOL bIdeal/* = FALSE*/)
        {
            SendMessageDx(RB_MAXIMIZEBAND, uBand, bIdeal);
        }

        inline VOID MReBarCtrl::MinimizeBand(UINT uBand)
        {
            SendMessageDx(RB_MINIMIZEBAND, uBand);
        }

        inline BOOL MReBarCtrl::SizeToRect(LPRECT prc)
        {
            return (BOOL)SendMessageDx(RB_SIZETORECT, 0, (LPARAM)prc);
        }

        inline INT MReBarCtrl::IDToIndex(UINT uBandID) const
        {
            return (INT)SendMessageDx(RB_IDTOINDEX, uBandID);
        }

        inline BOOL MReBarCtrl::ShowBand(INT nBand, BOOL fShow/* = TRUE*/)
        {
            return (BOOL)SendMessageDx(RB_SHOWBAND, (WPARAM)nBand, (LPARAM)fShow);
        }

        inline BOOL MReBarCtrl::MoveBand(INT nFrom, INT nTo)
        {
            assert(0 <= nTo && nTo < (INT) GetBandCount());
            return (BOOL)SendMessageDx(RB_MOVEBAND, (WPARAM)nFrom, (LPARAM)nTo);
        }
    #endif  // (_WIN32_IE >= 0x0400)

    inline BOOL MReBarCtrl::InsertBand(INT nIndex, REBARBANDINFO* prbbi)
    {
        return (BOOL)SendMessageDx(RB_INSERTBAND, (WPARAM)nIndex, (LPARAM)prbbi);
    }

    inline BOOL MReBarCtrl::AddBand(REBARBANDINFO* prbbi)
    {
        return InsertBand(-1, prbbi);
    }

    inline BOOL MReBarCtrl::DeleteBand(INT nIndex)
    {
        return (BOOL)SendMessageDx(RB_DELETEBAND, (WPARAM)nIndex);
    }

    inline HWND MReBarCtrl::SetNotifyWnd(HWND hWnd)
    {
        assert(::IsWindow(hWnd));
        return (HWND)SendMessageDx(RB_SETPARENT, (WPARAM)hWnd);
    }

    #if (_WIN32_IE >= 0x0500)
        inline INT MReBarCtrl::HitTest(RBHITTESTINFO *prbht)
        {
            return (INT)SendMessageDx(RB_HITTEST, 0, (LPARAM)prbht);
        }
    #endif  // (_WIN32_IE >= 0x0500)

    inline /*virtual*/ HWND MReBarCtrl::SetParent(HWND hWndNewParent)
    {
        HWND hWnd2 = ::SetParent(m_hwnd, hWndNewParent);
        HWND hWnd = (HWND)SendMessageDx(RB_SETPARENT, (WPARAM)hWndNewParent);
        if (hWnd2)
            hWnd = hWnd2;
        return hWnd;
    }
#endif  // (_WIN32_IE >= 0x0300)

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MREBARCTRL_HPP_
