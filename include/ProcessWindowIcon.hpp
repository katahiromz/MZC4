// ProcessWindowIcon.hpp -- Processes, Windows, and Icons      -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef PROCESSWINDOWICON_HPP_
#define PROCESSWINDOWICON_HPP_      1   // Version 1

#include "MWindowBase.hpp"

MString GetPathOfProcessDx(DWORD pid);
HICON GetStdIconDx(LPCTSTR pszIcon, UINT uType = ICON_BIG);
HICON GetIconOfProcessDx(DWORD pid, UINT uType = ICON_BIG);
HICON GetIconOfWindowDx(HWND hwnd, UINT uType = ICON_BIG);
DWORD ProcessFromWindowDx(HWND hwnd);
HWND WindowFromProcessDx(DWORD pid);

////////////////////////////////////////////////////////////////////////////

inline DWORD ProcessFromWindowDx(HWND hwnd)
{
    DWORD pid = 0;
    ::GetWindowThreadProcessId(hwnd, &pid);
    return pid;
}

inline HICON GetIconOfWindowDx(HWND hwnd, UINT uType)
{
    HICON hIcon = NULL;

    if (hwnd == GetDesktopWindow() || hwnd == NULL)
    {
        static const LPCTSTR pszShell32 = TEXT("shell32.dll");
        const INT nDesktopIndex = 34;
        switch (uType)
        {
        case ICON_SMALL:
            ::ExtractIconEx(pszShell32, nDesktopIndex, NULL, &hIcon, 1);
            break;
        case ICON_BIG:
            ::ExtractIconEx(pszShell32, nDesktopIndex, &hIcon, NULL, 1);
            break;
        }
        if (hIcon)
            hIcon = CopyIcon(hIcon);
    }

    if (!hIcon)
    {
        DWORD_PTR dwResult = 0;
        UINT uTimeout = 100;
        SendMessageTimeout(hwnd, WM_GETICON, uType, 0, SMTO_ABORTIFHUNG,
                           uTimeout, &dwResult);
        hIcon = (HICON)dwResult;
        if (hIcon)
            hIcon = CopyIcon(hIcon);
    }

    if (!hIcon)
    {
        switch (uType)
        {
        case ICON_SMALL:
            hIcon = (HICON)GetClassLongPtr(hwnd, GCL_HICONSM);
            if (hIcon)
                break;
            // FALL THROUGH
        case ICON_BIG:
            hIcon = (HICON)GetClassLongPtr(hwnd, GCL_HICON);
            break;
        }
        if (hIcon)
            hIcon = CopyIcon(hIcon);
    }

    if (!hIcon)
    {
        if (!GetWindow(hwnd, GW_OWNER) && !GetParent(hwnd))
        {
            DWORD pid = 0;
            GetWindowThreadProcessId(hwnd, &pid);

            hIcon = GetIconOfProcessDx(pid, uType);
        }
    }

    return hIcon;
}

inline MString GetPathOfProcessDx(DWORD pid)
{
    MString ret;
    const DWORD dwAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
    if (HANDLE hProcess = ::OpenProcess(dwAccess, FALSE, pid))
    {
        TCHAR szPath[MAX_PATH];
        DWORD cchPath = ARRAYSIZE(szPath);
#if _WIN32_WINNT >= 0x600 && 0
        if (::QueryFullProcessImageName(hProcess, 0, szPath, &cchPath))
        {
            ret = szPath;
        }
#else
        if (::GetModuleFileNameEx(hProcess, NULL, szPath, cchPath))
        {
            ret = szPath;
        }
#endif
        ::CloseHandle(hProcess);
    }

    return ret;
}

inline HICON GetIconOfProcessDx(DWORD pid, UINT uType)
{
    HICON hIcon = NULL;
    MString strPath = GetPathOfProcessDx(pid);
    if (strPath.size())
    {
        SHFILEINFO shfi;
        ZeroMemory(&shfi, sizeof(shfi));
        UINT uFlags = 0;
        switch (uType)
        {
        case ICON_SMALL:
            uFlags = SHGFI_ICON | SHGFI_SMALLICON;
            break;

        case ICON_BIG:
            uFlags = SHGFI_ICON | SHGFI_LARGEICON;
            break;

        default:
            return NULL;
        }
        SHGetFileInfo(strPath.c_str(), 0, &shfi, sizeof(shfi), uFlags);
        hIcon = shfi.hIcon;
    }
    return hIcon;
}

inline HICON GetStdIconDx(LPCTSTR pszIcon, UINT uType)
{
    HICON hIcon = NULL;
    INT cx, cy;
    switch (uType)
    {
    case ICON_SMALL:
        cx = GetSystemMetrics(SM_CXSMICON);
        cy = GetSystemMetrics(SM_CYSMICON);
        hIcon = (HICON)LoadImage(NULL, pszIcon, IMAGE_ICON, cx, cy, 0);
        if (hIcon)
            break;

    case ICON_BIG:
        hIcon = LoadIcon(NULL, pszIcon);
        break;
    }
    return hIcon;
}

namespace details
{
    struct PROCESS_AND_WINDOW
    {
        DWORD pid;
        HWND hwnd;
    };

    inline BOOL CALLBACK WindowFromProcessProc(HWND hwnd, LPARAM lParam)
    {
        PROCESS_AND_WINDOW *paw = (PROCESS_AND_WINDOW *)lParam;
        DWORD pid = ProcessFromWindowDx(hwnd);
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
} // namespace details

inline HWND WindowFromProcessDx(DWORD pid)
{
    details::PROCESS_AND_WINDOW paw;
    paw.pid = pid;
    paw.hwnd = NULL;
    ::EnumWindows(details::WindowFromProcessProc, (LPARAM)&paw);
    return paw.hwnd;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef PROCESSWINDOWICON_HPP_
