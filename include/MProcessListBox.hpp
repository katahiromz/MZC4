// MProcessListBox.hpp -- process list box                     -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPROCESSLISTBOX_HPP_
#define MZC4_MPROCESSLISTBOX_HPP_      12   /* Version 12 */

////////////////////////////////////////////////////////////////////////////

#include "MListBox.hpp"
#include <tlhelp32.h>   // for CreateToolhelp32Snapshot, Process32First, ...
#include <psapi.h>      // for GetModuleFileNameEx
#include <strsafe.h>    // for StringC...
#include <vector>       // for std::vector

#include "ProcessWindowIcon.hpp"

////////////////////////////////////////////////////////////////////////////
// MProcessEntry

struct MProcessEntry : PROCESSENTRY32
{
    INT iImage;
};

////////////////////////////////////////////////////////////////////////////
// MProcessList

class MProcessList
{
public:
    typedef MProcessEntry entry_type;
    typedef std::vector<entry_type> entry_list_type;

    MProcessList(UINT nIconType = ICON_BIG);

    bool get_list();

    bool empty() const;
    size_t size() const;
    void clear();

    entry_list_type& entries()
    {
        return m_entries;
    }
    const entry_list_type& entries() const
    {
        return m_entries;
    }

    entry_type& operator[](size_t index)
    {
        assert(index < size());
        return entries()[index];
    }
    const entry_type& operator[](size_t index) const
    {
        assert(index < size());
        return entries()[index];
    }

    HIMAGELIST ImageList();
    BOOL ReCreateImageList(UINT nIconType = ICON_BIG);

protected:
    UINT m_nIconType;
    HIMAGELIST m_himl;
    entry_list_type m_entries;
};

////////////////////////////////////////////////////////////////////////////
// MProcessListBox

class MProcessListBox : public MListBox
{
public:
    typedef MProcessList::entry_type entry_type;
    typedef MProcessList::entry_list_type entry_list_type;

    MProcessListBox();

    bool refresh();

    virtual MString text_from_entry(const entry_type& entry) const;
    virtual INT AddProcessItem(const entry_type& entry);

    bool empty() const;
    size_t size() const;
    void clear();

    bool get_selected_pid(DWORD& pid) const;

    entry_list_type& entries()
    {
        return m_list.entries();
    }
    const entry_list_type& entries() const
    {
        return m_list.entries();
    }

    entry_type& operator[](size_t index)
    {
        assert(index < size());
        return entries()[index];
    }
    const entry_type& operator[](size_t index) const
    {
        assert(index < size());
        return entries()[index];
    }

    bool find_text(size_t& index, const MString& text) const;

    HIMAGELIST ImageList();

protected:
    MProcessList m_list;
};

////////////////////////////////////////////////////////////////////////////
// MProcessList inlines

inline MProcessList::MProcessList(UINT nIconType)
    : m_nIconType(nIconType), m_himl(NULL)
{
    ReCreateImageList(nIconType);
}

inline HIMAGELIST MProcessList::ImageList()
{
    return m_himl;
}

inline BOOL MProcessList::ReCreateImageList(UINT nIconType)
{
    if (m_himl)
    {
        ImageList_Destroy(m_himl);
        m_himl = NULL;
    }
    INT cx, cy;
    if (nIconType == ICON_BIG)
    {
        cx = GetSystemMetrics(SM_CXICON);
        cy = GetSystemMetrics(SM_CYICON);
    }
    else
    {
        cx = GetSystemMetrics(SM_CXSMICON);
        cy = GetSystemMetrics(SM_CYSMICON);
    }
    m_himl = ImageList_Create(cx, cy, ILC_COLOR32 | ILC_MASK, 128, 16);
    m_nIconType = nIconType;
    return m_himl != NULL;
}

inline bool MProcessList::empty() const
{
    return m_entries.empty();
}

inline size_t MProcessList::size() const
{
    return m_entries.size();
}

inline void MProcessList::clear()
{
    m_entries.clear();
}

inline bool MProcessList::get_list()
{
    clear();

    const DWORD dwFlags = TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE32;
    HANDLE hSnapshot = ::CreateToolhelp32Snapshot(dwFlags, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;

    entry_type entry;
    entry.dwSize = sizeof(entry);
    if (::Process32First(hSnapshot, &entry))
    {
        do
        {
            HICON hIcon = GetIconOfProcessDx(entry.th32ProcessID);
            if (!hIcon)
            {
                hIcon = GetStdIconDx(IDI_APPLICATION, m_nIconType);
            }
            assert(hIcon);
            entry.iImage = ImageList_AddIcon(m_himl, hIcon);
            DestroyIcon(hIcon);

            m_entries.push_back(entry);
        } while (::Process32Next(hSnapshot, &entry));
    }

    CloseHandle(hSnapshot);
    return !empty();
}

////////////////////////////////////////////////////////////////////////////
// MProcessListBox inlines

inline MString MProcessListBox::text_from_entry(const entry_type& entry) const
{
    HWND hwnd = WindowFromProcessDx(entry.th32ProcessID);
    MString strFullPath = GetPathOfProcessDx(entry.th32ProcessID);
    MString strWindowText = MWindowBase::GetWindowText(m_hwnd);

    const size_t MAX_WINDOW_TEXT = 20;
    if (strWindowText.size() >= MAX_WINDOW_TEXT)
    {
        strWindowText.resize(MAX_WINDOW_TEXT);
        strWindowText += TEXT("...");
    }

    TCHAR szText[MAX_PATH * 2];
    StringCbPrintf(szText, sizeof(szText), TEXT("PID %08X hwnd %p %s %s %s"),
        entry.th32ProcessID, hwnd, entry.szExeFile, strWindowText.c_str(),
        strFullPath.c_str());

    return szText;
}

inline MProcessListBox::MProcessListBox()
{
}

inline bool MProcessListBox::empty() const
{
    return m_list.empty();
}

inline size_t MProcessListBox::size() const
{
    return m_list.size();
}

inline void MProcessListBox::clear()
{
    ResetContent();
    m_list.clear();
}

inline bool MProcessListBox::refresh()
{
    clear();

    if (!m_list.get_list())
        return false;

    if (size())
    {
        SendMessageDx(WM_SETREDRAW, FALSE);
        {
            for (size_t i = 0; i < size(); ++i)
            {
                AddProcessItem(entries()[i]);
            }
        }
        SendMessageDx(WM_SETREDRAW, TRUE);
        return true;
    }
    return false;
}

inline bool MProcessListBox::get_selected_pid(DWORD& pid) const
{
    INT i = GetCurSel();
    if (i < 0 || size_t(i) >= size())
    {
        pid = 0;
        return false;
    }

    pid = entries()[i].th32ProcessID;
    return TRUE;
}

inline bool MProcessListBox::find_text(size_t& index, const MString& text) const
{
    for (size_t i = 0; i < size(); ++i)
    {
        MString info_text = text_from_entry(entries()[i]);
        if (info_text.find(text) != MString::npos)
        {
            index = i;
            return true;
        }
    }
    return false;
}

inline INT MProcessListBox::AddProcessItem(const entry_type& entry)
{
    INT iItem;
    if (GetStyleDx() & LBS_HASSTRINGS)
    {
        MString text = text_from_entry(entry);
        iItem = AddString(text.c_str());
        if (iItem >= 0)
        {
            SetItemDataPtr(iItem, (LPVOID)&entry);
        }
    }
    else
    {
        iItem = AddString((LPTSTR)&entry);
    }
    return iItem;
}

inline HIMAGELIST MProcessListBox::ImageList()
{
    return m_list.ImageList();
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MPROCESSLISTBOX_HPP_
