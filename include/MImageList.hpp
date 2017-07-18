// MAccel.hpp -- Win32API accelerator wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MIMAGELIST_HPP_
#define MZC4_MIMAGELIST_HPP_    4       /* Version 4 */

class MImageList;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#ifndef _INC_COMMCTRL
    #include <commctrl.h>   // for image list
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

#include "MLibrary.hpp"

class MImageList
{
public:
    HIMAGELIST m_hImageList;

    MImageList();
    MImageList(HIMAGELIST hImageList);
    MImageList(const MImageList& il);
    MImageList& operator=(HIMAGELIST hImageList);
    MImageList& operator=(const MImageList& ilist);
    virtual ~MImageList();

    operator HIMAGELIST() const;

    HIMAGELIST Handle() const;
    BOOL Attach(HIMAGELIST hImageList);
    HIMAGELIST Detach();

    BOOL Create(INT cx, INT cy, UINT uILC_flags, INT nInitial, INT nGrow);
    BOOL Create(LPCTSTR lpszBitmapID, INT cx, INT nGrow, COLORREF crMask,
                HINSTANCE hInstance = NULL);
    BOOL Merge(HIMAGELIST hIml1, INT nImage1, HIMAGELIST hIml2,
        INT nImage2, INT dx, INT dy);
    BOOL Destroy();

    INT GetImageCount() const;
    #if (_WIN32_IE >= 0x0300)
        BOOL SetImageCount(UINT uNewCount);
    #endif  // (_WIN32_IE >= 0x0300)

    BOOL GetImageSize(INT *cx, INT *cy) const;
    BOOL SetImageSizeAndClear(INT cx, INT cy);

    COLORREF GetBkColor() const;
    COLORREF SetBkColor(COLORREF cr);

    BOOL GetImageInfo(INT nImage, IMAGEINFO* pImageInfo) const;

    INT Add(HBITMAP hbmImage, HBITMAP hbmMask);
    INT Add(HBITMAP hbmImage, COLORREF crMask);
    BOOL Remove(INT nImage);
    BOOL Replace(INT nImage, HBITMAP hbmImage, HBITMAP hbmMask);
    INT Add(HICON hIcon);
    INT Replace(INT nImage, HICON hIcon);
    HICON ExtractIcon(INT nImage);

    BOOL Draw(INT nImage, HDC hDC, INT x, INT y, UINT nILD_flags = ILD_NORMAL);
    BOOL Draw(INT nImage, HDC hDC, POINT pt, UINT nILD_flags = ILD_NORMAL);
    BOOL DrawEx(INT nImage, HDC hDC, INT x, INT y, INT dx, INT dy,
        COLORREF rgbBk, COLORREF rgbFg = CLR_NONE, UINT nILD_flags = ILD_NORMAL);
    BOOL DrawEx(INT nImage, HDC hDC, LPCRECT prc, COLORREF rgbBk,
        COLORREF rgbFg = CLR_NONE, UINT nILD_flags = ILD_NORMAL);
    BOOL SetOverlayImage(INT nImage, INT nOverlay);

    BOOL BeginDrag(INT nImage, INT xHotSpot, INT yHotSpot);
    BOOL BeginDrag(INT nImage, POINT ptHotSpot);
    static VOID EndDrag();
    static BOOL DragMove(INT x, INT y);
    static BOOL DragMove(POINT pt);
    BOOL SetDragCursorImage(INT nDrag, INT xHotSpot, INT yHotSpot);
    BOOL SetDragCursorImage(INT nDrag, POINT ptHotSpot);
    static BOOL DragShowNolock(BOOL bShow = TRUE);
    static HIMAGELIST GetDragImage(LPPOINT ppt, LPPOINT pptHotSpot);
    static BOOL DragEnter(HWND hWnd, POINT pt);
    static BOOL DragEnter(HWND hWnd, INT x, INT y);
    static BOOL DragLeave(HWND hWnd);

#if (_WIN32_IE >= 0x0300)
    BOOL Copy(INT iDst, INT iSrc, UINT uILCF_flags = ILCF_MOVE);
    BOOL Copy(INT iDst, HIMAGELIST hImlSrc, INT iSrc,
              UINT uILCF_flags = ILCF_MOVE);
    static BOOL DrawIndirect(IMAGELISTDRAWPARAMS* pimldp);
#endif  // (_WIN32_IE >= 0x0300)

    static HIMAGELIST CloneHandleDx(HIMAGELIST hImageList);
};


////////////////////////////////////////////////////////////////////////////

inline MImageList::MImageList() : m_hImageList(NULL)
{
}

inline MImageList::MImageList(HIMAGELIST hImageList)
    : m_hImageList(hImageList)
{
}

inline /*virtual*/ MImageList::~MImageList()
{
    Destroy();
}

inline MImageList::MImageList(const MImageList& il)
    : m_hImageList(CloneHandleDx(il))
{
}

inline MImageList::operator HIMAGELIST() const
{
    return Handle();
}

inline HIMAGELIST MImageList::Handle() const
{
    return (this ? m_hImageList : NULL);
}

inline MImageList& MImageList::operator=(HIMAGELIST hImageList)
{
    if (Handle() != hImageList)
    {
        Attach(hImageList);
    }
    return *this;
}

inline MImageList& MImageList::operator=(const MImageList& ilist)
{
    if (Handle() != ilist.Handle())
    {
        HIMAGELIST himl = CloneHandleDx(ilist);
        Attach(himl);
    }
    return *this;
}

inline BOOL MImageList::Attach(HIMAGELIST hImageList)
{
    Destroy();
    m_hImageList = hImageList;
    return m_hImageList != NULL;
}

inline HIMAGELIST MImageList::Detach()
{
    HIMAGELIST hImageList = m_hImageList;
    m_hImageList = NULL;
    return hImageList;
}

inline BOOL MImageList::Create(
    INT cx, INT cy, UINT uILC_flags, INT nInitial, INT nGrow)
{
    return Attach(ImageList_Create(cx, cy, uILC_flags, nInitial, nGrow));
}

inline BOOL MImageList::Create(LPCTSTR lpszBitmapID,
    INT cx, INT nGrow, COLORREF crMask, HINSTANCE hInstance/* = NULL*/)
{
    if (hInstance == NULL)
        hInstance = ::GetModuleHandle(NULL);
    return Attach(ImageList_LoadBitmap(hInstance, lpszBitmapID, cx, nGrow, crMask));
}

inline BOOL MImageList::Merge(HIMAGELIST hIml1, INT nImage1,
    HIMAGELIST hIml2, INT nImage2, INT dx, INT dy)
{
    return Attach(ImageList_Merge(hIml1, nImage1, hIml2, nImage2, dx, dy));
}

inline INT MImageList::GetImageCount() const
{
    assert(Handle());
    return ImageList_GetImageCount(Handle());
}

inline COLORREF MImageList::SetBkColor(COLORREF cr)
{
    assert(Handle());
    return ImageList_SetBkColor(Handle(), cr);
}

inline COLORREF MImageList::GetBkColor() const
{
    assert(Handle());
    return ImageList_GetBkColor(Handle());
}

inline BOOL MImageList::GetImageInfo(
    INT nImage, IMAGEINFO* pImageInfo) const
{
    assert(Handle());
    return ImageList_GetImageInfo(Handle(), nImage, pImageInfo);
}

inline BOOL MImageList::Destroy()
{
    if (Handle())
    {
        BOOL bOK = ImageList_Destroy(Detach());
        return bOK;
    }
    return FALSE;
}

#if (_WIN32_IE >= 0x0300)
    inline BOOL MImageList::SetImageCount(UINT uNewCount)
    {
        assert(Handle());
        return ImageList_SetImageCount(Handle(), uNewCount);
    }
#endif  // (_WIN32_IE >= 0x0300)

inline BOOL MImageList::GetImageSize(INT *cx, INT *cy) const
{
    assert(Handle());
    return ImageList_GetIconSize(Handle(), cx, cy);
}

inline BOOL MImageList::SetImageSizeAndClear(INT cx, INT cy)
{
    assert(Handle());
    return ImageList_SetIconSize(Handle(), cx, cy);
}

inline INT MImageList::Add(HBITMAP hbmImage, HBITMAP hbmMask)
{
    assert(Handle());
    return ImageList_Add(Handle(), hbmImage, hbmMask);
}

inline INT MImageList::Add(HBITMAP hbmImage, COLORREF crMask)
{
    assert(Handle());
    return ImageList_AddMasked(Handle(), hbmImage, crMask);
}

inline BOOL MImageList::Remove(INT nImage)
{
    assert(Handle());
    return ImageList_Remove(Handle(), nImage);
}

inline BOOL MImageList::Replace(
    INT nImage, HBITMAP hbmImage, HBITMAP hbmMask)
{
    assert(Handle());
    return ImageList_Replace(Handle(), nImage, hbmImage, hbmMask);
}

inline INT MImageList::Add(HICON hIcon)
{
    assert(Handle());
    return ImageList_AddIcon(Handle(), hIcon);
}

inline INT MImageList::Replace(INT nImage, HICON hIcon)
{
    assert(Handle());
    return ImageList_ReplaceIcon(Handle(), nImage, hIcon);
}

inline HICON MImageList::ExtractIcon(INT nImage)
{
    assert(Handle());
    return ImageList_ExtractIcon(NULL, Handle(), nImage);
}

inline BOOL MImageList::Draw(INT nImage, HDC hDC, INT x, INT y,
    UINT nILD_flags/* = ILD_NORMAL*/)
{
    assert(Handle());
    assert(hDC);
    return ImageList_Draw(Handle(), nImage, hDC, x, y, nILD_flags);
}

inline BOOL MImageList::Draw(
    INT nImage, HDC hDC, POINT pt, UINT nILD_flags/* = ILD_NORMAL*/)
{
    return Draw(nImage, hDC, pt.x, pt.y, nILD_flags);
}

inline BOOL MImageList::DrawEx(INT nImage, HDC hDC, INT x, INT y,
    INT dx, INT dy, COLORREF rgbBk, COLORREF rgbFg/* = CLR_NONE*/,
    UINT nILD_flags/* = ILD_NORMAL*/)
{
    assert(Handle());
    assert(hDC);
    return ImageList_DrawEx(Handle(), nImage, hDC, x, y, dx, dy,
                            rgbBk, rgbFg, nILD_flags);
}

inline BOOL MImageList::DrawEx(INT nImage, HDC hDC, LPCRECT prc,
    COLORREF rgbBk, COLORREF rgbFg/* = CLR_NONE*/,
    UINT nILD_flags/* = ILD_NORMAL*/)
{
    return DrawEx(nImage, hDC, prc->left, prc->top, prc->right - prc->left,
                  prc->bottom - prc->top, rgbBk, rgbFg, nILD_flags);
}

inline BOOL MImageList::SetOverlayImage(INT nImage, INT nOverlay)
{
    assert(Handle());
    return ImageList_SetOverlayImage(Handle(), nImage, nOverlay);
}

#if (_WIN32_IE >= 0x0300)
    inline BOOL MImageList::Copy(
        INT iDst, INT iSrc, UINT uILCF_flags/* = ILCF_MOVE*/)
    {
        assert(Handle());
        return ImageList_Copy(Handle(), iDst, Handle(), iSrc, uILCF_flags);
    }
    
    inline BOOL MImageList::Copy(INT iDst, HIMAGELIST hImlSrc, INT iSrc,
        UINT uILCF_flags/* = ILCF_MOVE*/)
    {
        assert(Handle());
        assert(hImlSrc != NULL);
        return ImageList_Copy(Handle(), iDst, hImlSrc, iSrc, uILCF_flags);
    }
    
    inline /*static*/ BOOL
    MImageList::DrawIndirect(IMAGELISTDRAWPARAMS* pimldp)
    {
        return ImageList_DrawIndirect(pimldp);
    }
#endif  // (_WIN32_IE >= 0x0300)

inline BOOL MImageList::BeginDrag(INT nImage, INT xHotSpot, INT yHotSpot)
{
    assert(Handle());
    return ImageList_BeginDrag(Handle(), nImage, xHotSpot, yHotSpot);
}

inline BOOL MImageList::BeginDrag(INT nImage, POINT ptHotSpot)
{
    return BeginDrag(nImage, ptHotSpot.x, ptHotSpot.y);
}

inline /*static*/ VOID MImageList::EndDrag()
{
    ImageList_EndDrag();
}

inline /*static*/ BOOL MImageList::DragMove(INT x, INT y)
{
    return ImageList_DragMove(x, y);
}

inline /*static*/ BOOL MImageList::DragMove(POINT pt)
{
    return MImageList::DragMove(pt.x, pt.y);
}

inline BOOL MImageList::SetDragCursorImage(
    INT nDrag, INT xHotSpot, INT yHotSpot)
{
    assert(Handle());
    return ImageList_SetDragCursorImage(Handle(), nDrag, xHotSpot, yHotSpot);
}

inline BOOL MImageList::SetDragCursorImage(INT nDrag, POINT ptHotSpot)
{
    return MImageList::SetDragCursorImage(nDrag, ptHotSpot.x, ptHotSpot.y);
}

inline /*static*/ BOOL MImageList::DragShowNolock(BOOL bShow/* = TRUE*/)
{
    return ImageList_DragShowNolock(bShow);
}

inline /*static*/ HIMAGELIST MImageList::GetDragImage(
    LPPOINT ppt, LPPOINT pptHotSpot)
{
    return ImageList_GetDragImage(ppt, pptHotSpot);
}

inline /*static*/ BOOL MImageList::DragEnter(HWND hWnd, INT x, INT y)
{
    return ImageList_DragEnter(hWnd, x, y);
}

inline /*static*/ BOOL MImageList::DragEnter(HWND hWnd, POINT pt)
{
    return MImageList::DragEnter(hWnd, pt.x, pt.y);
}

inline /*static*/ BOOL MImageList::DragLeave(HWND hWnd)
{
    return ImageList_DragLeave(hWnd);
}

inline /*static*/ HIMAGELIST MImageList::CloneHandleDx(HIMAGELIST hImageList)
{
    typedef HIMAGELIST (WINAPI *IMAGELIST_DUPLICATE)(HIMAGELIST);

    if (hImageList == NULL)
        return NULL;

    static MLibrary hComCtl32(TEXT("COMCTL32"));
    static IMAGELIST_DUPLICATE fnImageList_Duplicate = NULL;

    if (fnImageList_Duplicate == NULL)
        hComCtl32.GetProcAddress("ImageList_Duplicate", fnImageList_Duplicate);
    if (fnImageList_Duplicate)
        return (*fnImageList_Duplicate)(hImageList);

#if (_WIN32_IE >= 0x0400)
    return NULL;
#else
    INT cx, cy;
    ImageList_GetIconSize(hImageList, &cx, &cy);
    
    HIMAGELIST himlNew = ImageList_Create(cx, cy, ILC_COLOR32 | ILC_MASK, 10, 10);
    if (himlNew == NULL)
        return himlNew;

    ImageList_SetBkColor(himlNew, CLR_NONE);
    INT nCount = ImageList_GetImageCount(hImageList);
    for(INT i = 0; i < nCount; i++)
    {
        HICON hIcon = ImageList_GetIcon(hImageList, i, ILD_TRANSPARENT);
        if (hIcon == NULL)
        {
            ImageList_Destroy(himlNew);
            return NULL;
        }
        INT iIcon = ImageList_AddIcon(himlNew, hIcon);
        ::DestroyIcon(hIcon);
        if (iIcon < 0)
        {
            ImageList_Destroy(himlNew);
            return NULL;
        }
    }
    return himlNew;
#endif
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MIMAGELIST_HPP_
