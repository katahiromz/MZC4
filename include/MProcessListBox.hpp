// MProcessListBox.hpp -- process list box                     -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPROCESSLISTBOX_HPP_
#define MZC4_MPROCESSLISTBOX_HPP_      10   /* Version 10 */

////////////////////////////////////////////////////////////////////////////

#include "MListBox.hpp"
#include <tlhelp32.h>   // for CreateToolhelp32Snapshot, Process32First, ...
#include <psapi.h>      // for GetModuleFileNameEx
#include <strsafe.h>    // for StringC...
#include <vector>       // for std::vector

////////////////////////////////////////////////////////////////////////////
// MProcessList

class MProcessList
{
public:
    typedef PROCESSENTRY32 entry_type;
    typedef std::vector<entry_type> entry_list_type;

    MProcessList();

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

    static HWND WindowFromProcess(DWORD pid);
    static HICON GetIconOfWindow(HWND hwnd, UINT uType = ICON_BIG);
    static BOOL IsProcessWow64(DWORD pid);
    static BOOL IsProcessWow64(HANDLE hProcess);
    static MString GetProcessFullPath(DWORD pid);
    static MString GetProcessFullPath(HANDLE hProcess);

protected:
    MProcessList m_list;

    struct PROCESS_AND_WINDOW
    {
        DWORD pid;
        HWND hwnd;
    };
    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
};

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

////////////////////////////////////////////////////////////////////////////
// MProcessListBox inlines

inline MString MProcessListBox::text_from_entry(const entry_type& entry) const
{
    HWND hwnd = WindowFromProcess(entry.th32ProcessID);
    MString strFullPath = GetProcessFullPath(entry.th32ProcessID);
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

inline BOOL CALLBACK
MProcessListBox::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    PROCESS_AND_WINDOW *paw = (PROCESS_AND_WINDOW *)lParam;
    DWORD pid = 0;
    ::GetWindowThreadProcessId(hwnd, &pid);
    if (paw->pid == pid)
    {
        if (GetWindow(hwnd, GW_OWNER) == NULL)
        {
            paw->hwnd = hwnd;
            return FALSE;
        }
    }
    return TRUE;
}

inline HWND
MProcessListBox::WindowFromProcess(DWORD pid)
{
    PROCESS_AND_WINDOW paw;
    paw.pid = pid;
    paw.hwnd = NULL;
    ::EnumWindows(MProcessListBox::EnumWindowsProc, (LPARAM)&paw);
    return paw.hwnd;
}

inline HICON MProcessListBox::GetIconOfWindow(HWND hwnd, UINT uType)
{
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

    DWORD_PTR dwResult = 0;
    UINT uTimeout = 100;
    SendMessageTimeout(hwnd, WM_GETICON, uType, 0, SMTO_ABORTIFHUNG,
                       uTimeout, &dwResult);

    hIcon = (HICON)dwResult;
    if (hIcon == NULL)
    {
        if (uType == ICON_SMALL)
        {
            INT cx = GetSystemMetrics(SM_CXSMICON);
            INT cy = GetSystemMetrics(SM_CYSMICON);
            hIcon = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, cx, cy, 0);
        }
        else
        {
            hIcon = LoadIcon(NULL, IDI_APPLICATION);
        }
    }
    return hIcon;
}

inline BOOL MProcessListBox::IsProcessWow64(DWORD pid)
{
    BOOL bIsWow64 = FALSE;
    const DWORD dwAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
    if (HANDLE hProcess = ::OpenProcess(dwAccess, FALSE, pid))
    {
        bIsWow64 = IsProcessWow64(hProcess);
        ::CloseHandle(hProcess);
    }
    return bIsWow64;
}

inline BOOL MProcessListBox::IsProcessWow64(HANDLE hProcess)
{
    typedef BOOL (WINAPI *ISWOW64PROCESS)(HANDLE, PBOOL);
    HMODULE hKernel32 = GetModuleHandle(TEXT("kernel32"));
    ISWOW64PROCESS pIsWow64Process =
        (ISWOW64PROCESS)GetProcAddress(hKernel32, "IsWow64Process");

    BOOL bIsWow64 = FALSE;
    if (pIsWow64Process)
    {
        const DWORD dwAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
        (*pIsWow64Process)(hProcess, &bIsWow64);
    }

    return bIsWow64;
}

inline MString MProcessListBox::GetProcessFullPath(DWORD pid)
{
    MString strFullPath;
    const DWORD dwAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
    if (HANDLE hProcess = ::OpenProcess(dwAccess, FALSE, pid))
    {
        strFullPath = GetProcessFullPath(hProcess);
        ::CloseHandle(hProcess);
    }
    return strFullPath;
}

inline MString MProcessListBox::GetProcessFullPath(HANDLE hProcess)
{
    TCHAR szFullPath[MAX_PATH];
#if 0
    DWORD cchMax = ARRAYSIZE(szFullPath);
    ::QueryFullProcessImageName(hProcess, 0, szFullPath, &cchMax);
#else
    ::GetModuleFileNameEx(hProcess, NULL, szFullPath, ARRAYSIZE(szFullPath));
#endif
    return szFullPath;
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

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MPROCESSLISTBOX_HPP_
