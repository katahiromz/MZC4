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

    BOOL LoadBitmap(HINSTANCE hi, LPCTSTR pszBmpName,
                    INT nFirstCommandID, INT nFirstCaptionID = -1,
                    INT nFirstDescriptionID = -1, 
                    INT cx = 16, COLORREF crMask = RGB(255, 0, 255));
    BOOL LoadBitmap(HINSTANCE hi, LPCTSTR pszBmpName,
                    INT cEntries, const MCommandEntry *pEntries,
                    INT cx = 16, COLORREF crMask = RGB(255, 0, 255));

    MString CaptionFromCommand(INT nCommandID) const;
    MString DescriptionFromCommand(INT nCommandID) const;
    INT     ImageFromCommandID(INT nCommandID) const;
    INT     IndexFromCommandID(INT nCommandID) const;
    INT     CommandIDFromIndex(INT nIndex) const;

    BOOL SetCommandImage(INT nCommandID, INT nImage);
    BOOL SetCommandCaption(INT nCommandID, const MString& strCaption);
    BOOL SetCommandDescription(INT nCommandID, const MString& strDescription);

protected:
    HIMAGELIST      m_himl;
    entries_type    m_entries;

    INT load_image(HINSTANCE hi, LPCTSTR pszBmpName, INT cx, COLORREF crMask);
};

////////////////////////////////////////////////////////////////////////////

inline MCommandUI::MCommandUI() : m_himl(NULL)
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

inline void MCommandUI::DestroyImageList()
{
    if (ImageList())
    {
        ImageList_Destroy(ImageList());
        ImageList() = NULL;
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
MCommandUI::load_image(HINSTANCE hi, LPCTSTR pszBmpName, INT cx, COLORREF crMask)
{
    HBITMAP hbm = ::LoadBitmap(hi, pszBmpName);
    BITMAP bm;
    if (!GetObject(hbm, sizeof(bm), &bm))
        return 0;
    DeleteObject(hbm);

    DestroyImageList();

    const INT cGrow = 8;
    if (bm.bmBitsPixel == 32)
    {
        ImageList() = ImageList_LoadBitmap(hi, pszBmpName, cx, cGrow, CLR_NONE);
    }
    else
    {
        ImageList() = ImageList_LoadBitmap(hi, pszBmpName, cx, cGrow, crMask);
    }

    if (ImageList() == NULL)
        return 0;

    return bm.bmWidth / cx;
}

inline BOOL
MCommandUI::LoadBitmap(HINSTANCE hi, LPCTSTR pszBmpName,
    INT nFirstCommandID, INT nFirstCaptionID/* = -1*/,
    INT nFirstDescriptionID/* = -1*/, 
    INT cx/* = 16*/, COLORREF crMask/* = RGB(255, 0, 255)*/)
{
    const INT nCount = load_image(hi, pszBmpName, cx, crMask);
    if (nCount == 0)
        return FALSE;

    for (INT i = 0; i < nCount; ++i)
    {
        COMMANDENTRY entry;
        entry.nCommandID = nFirstCommandID++;
        entry.nImage = i;
        if (nFirstCaptionID != -1)
        {
            entry.strCaption = LoadStringDx(nFirstCaptionID++);
        }
        if (nFirstDescriptionID != -1)
        {
            entry.strDescription = LoadStringDx(nFirstDescriptionID++);
        }

        m_entries.push_back(entry);
    }

    return TRUE;
}

inline BOOL MCommandUI::LoadBitmap(
    HINSTANCE hi, LPCTSTR pszBmpName,
    INT cEntries, const MCommandEntry *pEntries,
    INT cx/* = 16*/, COLORREF crMask/* = RGB(255, 0, 255)*/)
{
    const INT nCount = load_image(hi, pszBmpName, cx, crMask);
    if (nCount == 0)
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

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCOMMANDUI_HPP_
