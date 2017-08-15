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
#include <cassert>          // for assert
#include <vector>           // for std::vector

////////////////////////////////////////////////////////////////////////////

class MCommandUI
{
public:
    struct UIENTRY
    {
        INT nCommandID;
        INT nImage;
    };
    typedef std::vector<UIENTRY> entries_type;

    MCommandUI() : m_himl(NULL)
    {
    }

    ~MCommandUI()
    {
        DestroyImageList();
    }

    HIMAGELIST& ImageList()
    {
        return m_himl;
    }
    const HIMAGELIST& ImageList() const
    {
        return m_himl;
    }

    void DestroyImageList()
    {
        if (ImageList())
        {
            ImageList_Destroy(ImageList());
            ImageList() = NULL;
        }
    }

    INT ImageFromCommand(INT nCommandID) const
    {
        entries_type::const_iterator it, end = m_entries.end();
        for (it = m_entries.begin(); it != end; ++it)
        {
            if (it->nCommandID == nCommandID)
                return it->nImage;
        }
        return -1;
    }

    BOOL LoadBitmap(HINSTANCE hi, LPCTSTR pszBmpName,
                    UINT nCommandID, INT cx = 16,
                    COLORREF crMask = RGB(255, 0, 255))
    {
        HBITMAP hbm = ::LoadBitmap(hi, pszBmpName);
        BITMAP bm;
        if (!GetObject(hbm, sizeof(bm), &bm))
            return FALSE;
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
            return FALSE;

        const INT nCount = bm.bmWidth / cx;
        for (INT i = 0; i < nCount; ++i)
        {
            UIENTRY entry;
            entry.nCommandID = nCommandID++;
            entry.nImage = i;
            m_entries.push_back(entry);
        }
        return TRUE;
    }

protected:
    HIMAGELIST      m_himl;
    entries_type    m_entries;
};

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCOMMANDUI_HPP_
