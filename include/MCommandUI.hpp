// MCommandUI.hpp -- MZC4 command UI                            -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MCOMMANDUI_HPP_
#define MZC4_MCOMMANDUI_HPP_    1       /* Version 1 */

class MCommandUI;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // for Win32API
#endif
#ifndef _INC_COMMCTRL
    #include <commctrl.h>   // for common controls
#endif
#include <cassert>          // for assert
#include <vector>           // for std::vector

////////////////////////////////////////////////////////////////////////////

struct MCommandEntry
{
    INT nCommandID;
    INT nImage;
    INT nCaptionID;
    INT nDescriptionID;
};

////////////////////////////////////////////////////////////////////////////

class MCommandUI
{
public:
    struct COMMANDENTRY
    {
        INT nCommandID;
        INT nImage;
        MString strCaption;
        MString strDescription;
    };
    typedef std::vector<COMMANDENTRY> entries_type;

    MCommandUI();
    ~MCommandUI();

          HIMAGELIST& ImageList();
    const HIMAGELIST& ImageList() const;
    void DestroyImageList();
          HIMAGELIST& LargeImageList();
    const HIMAGELIST& LargeImageList() const;
    void DestroyLargeImageList();

    BOOL LoadBitmap(HINSTANCE hi, INT cEntries, const MCommandEntry *pEntries,
        LPCTSTR pszBitmap, INT cx = 16, LPCTSTR pszLargeBitmap = NULL,
        INT cxLarge = 32, COLORREF crMask = RGB(255, 0, 255));

    MString CaptionFromCommand(INT nCommandID) const;
    MString DescriptionFromCommand(INT nCommandID) const;
    INT     ImageFromCommandID(INT nCommandID) const;
    INT     IndexFromCommandID(INT nCommandID) const;
    INT     CommandIDFromIndex(INT nIndex) const;

    BOOL SetCommandImage(INT nCommandID, INT nImage);
    BOOL SetCommandCaption(INT nCommandID, const MString& strCaption);
    BOOL SetCommandDescription(INT nCommandID, const MString& strDescription);

    BOOL DrawCommand(INT nCommandID, HDC hDC, INT x, INT y,
                     UINT nILD_ = ILD_NORMAL | ILD_TRANSPARENT);
    BOOL DrawCommandEx(INT nCommandID, HDC hDC, INT x, INT y, INT cx, INT cy,
                       COLORREF crForeground = CLR_NONE,
                       UINT nILD_ = ILD_NORMAL | ILD_TRANSPARENT);

protected:
    HIMAGELIST      m_himl;
    HIMAGELIST      m_himlLarge;
    entries_type    m_entries;

    INT load_image(HIMAGELIST& himl, HINSTANCE hi, LPCTSTR pszBitmap, INT cx, COLORREF crMask);
};

////////////////////////////////////////////////////////////////////////////

inline MCommandUI::MCommandUI() : m_himl(NULL), m_himlLarge(NULL)
{
}

inline MCommandUI::~MCommandUI()
{
    DestroyImageList();
}

inline HIMAGELIST& MCommandUI::ImageList()
{
    return m_himl;
}

inline const HIMAGELIST& MCommandUI::ImageList() const
{
    return m_himl;
}

inline HIMAGELIST& MCommandUI::LargeImageList()
{
    return m_himlLarge;
}

inline const HIMAGELIST& MCommandUI::LargeImageList() const
{
    return m_himlLarge;
}

inline void MCommandUI::DestroyImageList()
{
    if (ImageList())
    {
        ImageList_Destroy(ImageList());
        ImageList() = NULL;
    }
}

inline void MCommandUI::DestroyLargeImageList()
{
    if (LargeImageList())
    {
        ImageList_Destroy(LargeImageList());
        LargeImageList() = NULL;
    }
}

inline MString MCommandUI::CaptionFromCommand(INT nCommandID) const
{
    entries_type::const_iterator it, end = m_entries.end();
    for (it = m_entries.begin(); it != end; ++it)
    {
        if (it->nCommandID == nCommandID)
            return it->strCaption;
    }
    return MString();
}

inline MString MCommandUI::DescriptionFromCommand(INT nCommandID) const
{
    entries_type::const_iterator it, end = m_entries.end();
    for (it = m_entries.begin(); it != end; ++it)
    {
        if (it->nCommandID == nCommandID)
            return it->strDescription;
    }
    return MString();
}

inline INT MCommandUI::ImageFromCommandID(INT nCommandID) const
{
    entries_type::const_iterator it, end = m_entries.end();
    for (it = m_entries.begin(); it != end; ++it)
    {
        if (it->nCommandID == nCommandID)
            return it->nImage;
    }
    return -1;
}

inline BOOL MCommandUI::SetCommandImage(INT nCommandID, INT nImage)
{
    entries_type::iterator it, end = m_entries.end();
    for (it = m_entries.begin(); it != end; ++it)
    {
        if (it->nCommandID == nCommandID)
        {
            it->nImage = nImage;
            return TRUE;
        }
    }
    return FALSE;
}

inline BOOL
MCommandUI::SetCommandCaption(INT nCommandID, const MString& strCaption)
{
    entries_type::iterator it, end = m_entries.end();
    for (it = m_entries.begin(); it != end; ++it)
    {
        if (it->nCommandID == nCommandID)
        {
            it->strCaption = strCaption;
            return TRUE;
        }
    }
    return FALSE;
}

inline BOOL
MCommandUI::SetCommandDescription(INT nCommandID, const MString& strDescription)
{
    entries_type::iterator it, end = m_entries.end();
    for (it = m_entries.begin(); it != end; ++it)
    {
        if (it->nCommandID == nCommandID)
        {
            it->strDescription = strDescription;
            return TRUE;
        }
    }
    return FALSE;
}

inline INT MCommandUI::IndexFromCommandID(INT nCommandID) const
{
    INT nIndex = 0;
    entries_type::const_iterator it, end = m_entries.end();
    for (it = m_entries.begin(); it != end; ++it, ++nIndex)
    {
        if (it->nCommandID == nCommandID)
        {
            return nIndex;
        }
    }
    return -1;
}

inline INT MCommandUI::CommandIDFromIndex(INT nIndex) const
{
    if (size_t(nIndex) < m_entries.size())
        return m_entries[nIndex].nCommandID;
    return -1;
}

inline INT
MCommandUI::load_image(HIMAGELIST& himl, HINSTANCE hi,
                       LPCTSTR pszBitmap, INT cx, COLORREF crMask)
{
    assert(pszBitmap);
    HBITMAP hbm = ::LoadBitmap(hi, pszBitmap);
    BITMAP bm;
    if (!GetObject(hbm, sizeof(bm), &bm))
        return 0;
    DeleteObject(hbm);

    if (himl)
    {
        ImageList_Destroy(himl);
        himl = NULL;
    }

    const INT cGrow = 8;
    if (bm.bmBitsPixel == 32)
    {
        himl = ImageList_LoadBitmap(hi, pszBitmap, cx, cGrow, CLR_NONE);
    }
    else
    {
        himl = ImageList_LoadBitmap(hi, pszBitmap, cx, cGrow, crMask);
    }

    if (himl == NULL)
        return 0;

    return bm.bmWidth / cx;
}

inline BOOL
MCommandUI::LoadBitmap(
    HINSTANCE hi, INT cEntries, const MCommandEntry *pEntries,
    LPCTSTR pszBitmap, INT cx/* = 16*/, LPCTSTR pszLargeBitmap/* = NULL*/,
    INT cxLarge/* = 32*/, COLORREF crMask/* = RGB(255, 0, 255)*/)
{
    if (!load_image(ImageList(), hi, pszBitmap, cx, crMask))
        return FALSE;
    if (!load_image(LargeImageList(), hi, pszLargeBitmap, cxLarge, crMask))
        return FALSE;

    for (INT i = 0; i < cEntries; ++i)
    {
        COMMANDENTRY entry;
        entry.nCommandID = pEntries[i].nCommandID;
        entry.nImage = pEntries[i].nImage;
        if (pEntries[i].nCaptionID != -1)
        {
            entry.strCaption = LoadStringDx(pEntries[i].nCaptionID);
        }
        if (pEntries[i].nDescriptionID != -1)
        {
            entry.strDescription = LoadStringDx(pEntries[i].nDescriptionID);
        }
        m_entries.push_back(entry);
    }

    return TRUE;
}

inline BOOL
MCommandUI::DrawCommand(INT nCommandID, HDC hDC, INT x, INT y,
                        UINT nILD_/* = ILD_NORMAL | ILD_TRANSPARENT*/)
{
    INT nImage = ImageFromCommandID(nCommandID);
    return ImageList_Draw(ImageList(), nImage, hDC, x, y, nILD_);
}

inline BOOL
MCommandUI::DrawCommandEx(INT nCommandID, HDC hDC, INT x, INT y,
                          INT cx, INT cy, COLORREF crForeground/* = CLR_NONE*/,
                          UINT nILD_/* = ILD_NORMAL | ILD_TRANSPARENT*/)
{
    INT nImage = ImageFromCommandID(nCommandID);
    return ImageList_DrawEx(ImageList(), nImage, hDC, x, y, cx, cy,
                            CLR_NONE, crForeground, nILD_);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCOMMANDUI_HPP_
