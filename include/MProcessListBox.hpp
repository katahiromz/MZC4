// MProcessListBox.hpp -- process list box                     -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPROCESSLISTBOX_HPP_
#define MZC4_MPROCESSLISTBOX_HPP_      6   /* Version 6 */

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
    MProcessInfo();
    virtual void from_entry(const PROCESSENTRY32& entry);
    virtual MString get_text() const;
    MString get_full_path() const;
    HWND get_window() const;
    MString get_window_text(INT cchMax = 32) const;
    bool is_wow64() const;
    HICON get_icon(UINT uType = ICON_BIG) const;
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

namespace details
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
}

inline HWND MProcessInfo::get_window() const
{
    return details::WindowFromProcessID(th32ProcessID);
}

inline MString MProcessInfo::get_window_text(INT cchMax) const
{
    MString str;
    if (cchMax < 3 + 1)
        return str;     // too short

    str.resize(cchMax - (3 + 1));
    if (INT cch = GetWindowText(get_window(), &str[0], cchMax - 3))
    {
        str.resize(cch);
        if (cch == cchMax - (3 + 1))
        {
            // ellipsis
            str += TEXT("...");
        }
    }
    else
    {
        str.clear();
    }
    return str;
}

inline HICON MProcessInfo::get_icon(UINT uType) const
{
    HWND hwnd = get_window();
    HICON hIcon;

    if (uType == ICON_SMALL)
    {
        hIcon = (HICON)GetClassLongPtr(hwnd, GCL_HICONSM);
    }
    else
    {
        hIcon = (HICON)GetClassLongPtr(hwnd, GCL_HICON);
    }
    if (hIcon)
        return hIcon;

    DWORD_PTR dwResult;
    SendMessageTimeout(hwnd, WM_GETICON, uType, 0, SMTO_ABORTIFHUNG, 100, &dwResult);

    hIcon = (HICON)dwResult;
    return hIcon;
}

inline bool MProcessInfo::is_wow64() const
{
    typedef BOOL (WINAPI *ISWOW64PROCESS)(HANDLE, PBOOL);
    HMODULE hKernel32 = GetModuleHandle(TEXT("kernel32"));
    ISWOW64PROCESS pIsWow64Process =
        (ISWOW64PROCESS)GetProcAddress(hKernel32, "IsWow64Process");

    BOOL bIsWow64 = FALSE;
    if (pIsWow64Process)
    {
        const DWORD dwAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
        if (HANDLE hProcess = ::OpenProcess(dwAccess, FALSE, th32ProcessID))
        {
            (*pIsWow64Process)(hProcess, &bIsWow64);
            ::CloseHandle(hProcess);
        }
    }

    return bIsWow64;
}

inline MString MProcessInfo::get_full_path() const
{
    // get full path
    TCHAR szFullPath[MAX_PATH] = { };
    const DWORD dwAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
    if (HANDLE hProcess = ::OpenProcess(dwAccess, FALSE, th32ProcessID))
    {
#if 0
        DWORD cchMax = ARRAYSIZE(szFullPath);
        ::QueryFullProcessImageName(hProcess, 0, szFullPath, &cchMax);
#else
        ::GetModuleFileNameEx(hProcess, NULL, szFullPath, ARRAYSIZE(szFullPath));
#endif
        ::CloseHandle(hProcess);
    }
    return szFullPath;
}

inline void MProcessInfo::from_entry(const PROCESSENTRY32& entry)
{
    *(PROCESSENTRY32 *)this = entry;
}

inline MString MProcessInfo::get_text() const
{
    // get text
    TCHAR szText[MAX_PATH * 2];
    StringCbPrintf(szText, sizeof(szText),
                   TEXT("ProcessID:%08lX%s, Text:\"%s\", HWND:%p, FullPath:%s"),
                   th32ProcessID,
                   (is_wow64() ? " (WOW64)" : ""),
                   get_window_text().c_str(),
                   (void *)get_window(), get_full_path().c_str());
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
                t_info_type info;
                info.from_entry(entries()[i]);
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
