// MProcessListBox.hpp -- process list box                     -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPROCESSLISTBOX_HPP_
#define MZC4_MPROCESSLISTBOX_HPP_      2   /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#include "MListBox.hpp"
#include <tlhelp32.h>   // for CreateToolhelp32Snapshot, Process32First, ...
#include <psapi.h>      // for GetModuleFileNameEx
#include <strsafe.h>    // for StringC...
#include <vector>       // for std::vector

////////////////////////////////////////////////////////////////////////////
// MProcessInfo

struct MProcessInfo : PROCESSENTRY32
{
    TCHAR fullpath[MAX_PATH];
    HWND hwnd;

    MProcessInfo();
    MProcessInfo(const PROCESSENTRY32& entry);
    MProcessInfo& operator=(const PROCESSENTRY32& entry);

    virtual void from_entry(const PROCESSENTRY32& entry);
    virtual MString get_text() const;
};

////////////////////////////////////////////////////////////////////////////
// MProcessList

class MProcessList
{
public:
    typedef PROCESSENTRY32 entry_type;
    typedef std::vector<entry_type> entry_list_type;

    MProcessList();

    template <typename t_info_type = MProcessInfo>
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

    template <typename t_info_type = MProcessInfo>
    bool find_text(size_t& index, const MString& text) const;

protected:
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

    template <typename t_info_type = MProcessInfo>
    bool refresh();

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

    template <typename t_info_type = MProcessInfo>
    bool find_text(size_t& index, const MString& text) const;

protected:
    MProcessList m_list;
};

////////////////////////////////////////////////////////////////////////////
// details

namespace process_list_box_details
{
    struct PROCESS_AND_WINDOW
    {
        DWORD pid;
        HWND hwnd;
    };

    BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
    {
        PROCESS_AND_WINDOW *paw = (PROCESS_AND_WINDOW *)lParam;
        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        if (paw->pid == pid)
        {
            paw->hwnd = hwnd;
            return FALSE;
        }
        return TRUE;
    }

    HWND WindowFromProcessID(DWORD pid)
    {
        PROCESS_AND_WINDOW paw;
        paw.pid = pid;
        paw.hwnd = NULL;
        ::EnumWindows(EnumWindowsProc, (LPARAM)&paw);
        return paw.hwnd;
    }
}

////////////////////////////////////////////////////////////////////////////
// MProcessInfo inlines

inline MProcessInfo::MProcessInfo()
{
    fullpath[0] = 0;
    hwnd = NULL;
}

inline MProcessInfo::MProcessInfo(const PROCESSENTRY32& entry)
{
    fullpath[0] = 0;
    hwnd = NULL;
    from_entry(entry);
}

inline MProcessInfo& MProcessInfo::operator=(const PROCESSENTRY32& entry)
{
    fullpath[0] = 0;
    hwnd = NULL;
    from_entry(entry);
    return *this;
}

inline void MProcessInfo::from_entry(const PROCESSENTRY32& entry)
{
    *(PROCESSENTRY32 *)this = entry;

    // get full path
    fullpath[0] = 0;
    const DWORD dwAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
    if (HANDLE hProcess = ::OpenProcess(dwAccess, FALSE, th32ProcessID))
    {
        ::GetModuleFileNameEx(hProcess, NULL, fullpath, ARRAYSIZE(fullpath));
        ::CloseHandle(hProcess);
    }

    // get window handle
    hwnd = process_list_box_details::WindowFromProcessID(th32ProcessID);
}

inline MString MProcessInfo::get_text() const
{
    // get window text
    TCHAR szWindowText[32];
    GetWindowText(hwnd, szWindowText, ARRAYSIZE(szWindowText) - 3);
    if (lstrlen(szWindowText) == ARRAYSIZE(szWindowText) - 4)
        StringCbCat(szWindowText, sizeof(szWindowText), TEXT("..."));

    // get text
    TCHAR szText[MAX_PATH * 2];
    StringCbPrintf(szText, sizeof(szText), TEXT("ProcessID:%08lX, Text:\"%s\", FullPath:%s"),
                   th32ProcessID, szWindowText, fullpath);
    return MString(szText);
}

////////////////////////////////////////////////////////////////////////////
// MProcessList inlines

inline MProcessList::MProcessList()
{
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

template <typename t_info_type>
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
            m_entries.push_back(entry);
        } while (::Process32Next(hSnapshot, &entry));
    }

    CloseHandle(hSnapshot);
    return !empty();
}

template <typename t_info_type>
inline bool MProcessList::find_text(size_t& index, const MString& text) const
{
    index = size_t(-1);

    for (size_t i = 0; i < size(); ++i)
    {
        t_info_type info;
        info.from_entry(m_entries[i]);
        if (info.get_text().find(text) != MString::npos)
        {
            index = i;
            return true;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////
// MProcessListBox inlines

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

template <typename t_info_type>
inline bool MProcessListBox::refresh()
{
    clear();

    if (!m_list.get_list<t_info_type>())
        return false;

    if (size())
    {
        SendMessageDx(WM_SETREDRAW, FALSE);
        {
            for (size_t i = 0; i < size(); ++i)
            {
                t_info_type info(entries()[i]);
                MString text = info.get_text();
                //printf("%s\n", text.c_str());
                AddString(text.c_str());
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

template <typename t_info_type>
inline bool MProcessListBox::find_text(size_t& index, const MString& text) const
{
    return m_list.find_text(index, text);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MPROCESSLISTBOX_HPP_
