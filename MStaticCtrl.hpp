// MStaticCtrl.hpp -- Win32API static control wrapper           -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSTATICCTRL_HPP_
#define MZC4_MSTATICCTRL_HPP_   2   /* Version 2 */

class MStaticCtrl;

////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"

class MStaticCtrl : public MWindowBase
{
public:
    MStaticCtrl();

    virtual LPCTSTR GetWndClassName() const;

    HICON GetIcon() const;
    HICON SetIcon(HICON hIcon);

    HENHMETAFILE GetEnhMetaFile() const;
    HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile);

    HBITMAP GetBitmap() const;
    HBITMAP SetBitmap(HBITMAP hBitmap);

    HCURSOR GetCursor();
    HCURSOR SetCursor(HCURSOR hCursor);
};

////////////////////////////////////////////////////////////////////////////

inline MStaticCtrl::MStaticCtrl()
{
}

inline /*virtual*/ LPCTSTR MStaticCtrl::GetWndClassName() const
{
    return TEXT("STATIC");
}

inline HICON MStaticCtrl::SetIcon(HICON hIcon)
{
    return (HICON)SendMessageDx(STM_SETICON, (WPARAM)hIcon);
}

inline HICON MStaticCtrl::GetIcon() const
{
    return (HICON)SendMessageDx(STM_GETICON);
}

inline HENHMETAFILE MStaticCtrl::SetEnhMetaFile(HENHMETAFILE hMetaFile)
{
    return (HENHMETAFILE)SendMessageDx(STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);
}

inline HENHMETAFILE MStaticCtrl::GetEnhMetaFile() const
{
    return (HENHMETAFILE)SendMessageDx(STM_GETIMAGE, IMAGE_ENHMETAFILE);
}

inline HBITMAP MStaticCtrl::SetBitmap(HBITMAP hBitmap)
{
    return (HBITMAP)SendMessageDx(STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
}

inline HBITMAP MStaticCtrl::GetBitmap() const
{
    return (HBITMAP)SendMessageDx(STM_GETIMAGE, IMAGE_BITMAP);
}

inline HCURSOR MStaticCtrl::SetCursor(HCURSOR hCursor)
{
    return (HCURSOR)SendMessageDx(STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);
}

inline HCURSOR MStaticCtrl::GetCursor()
{
    return (HCURSOR)SendMessageDx(STM_GETIMAGE, IMAGE_CURSOR);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSTATICCTRL_HPP_
