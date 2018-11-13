// ProcessWindowIcon.hpp -- Processes, Windows, and Icons      -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef PROCESSWINDOWICON_HPP_
#define PROCESSWINDOWICON_HPP_      4   // Version 4

#include "MWindowBase.hpp"

MString GetPathOfProcessDx(DWORD pid);
HICON LoadIconDx(HINSTANCE hInst, LPCTSTR pszIcon, UINT uType = ICON_BIG);
HICON LoadIconDx(HINSTANCE hInst, UINT nIconID, UINT uType = ICON_BIG);
HICON GetStdIconDx(LPCTSTR pszIcon, UINT uType = ICON_BIG);
HICON GetIconOfProcessDx(DWORD pid, UINT uType = ICON_BIG);
HICON GetIconOfWindowDx(HWND hwnd, UINT uType = ICON_BIG);
HICON GetIconOfThreadDx(DWORD tid, UINT uType = ICON_BIG);
DWORD ProcessFromWindowDx(HWND hwnd);
HWND WindowFromProcessDx(DWORD pid);
BOOL IsProcessWow64Dx(DWORD pid);
BOOL IsProcessWow64Dx(HANDLE hProcess);

////////////////////////////////////////////////////////////////////////////

HICON GetIconOfThreadDx(DWORD tid, UINT uType)
{
#ifdef IDI_THREAD
    return LoadIconDx(GetModuleHandle(NULL), IDI_THREAD, uType);
#else
    return LoadIcon(NULL, IDI_INFORMATION);
#endif
}

inline HICON GetIconOfProcessDx(DWORD pid, UINT uType)
{
#ifdef IDI_PROCESS
    return LoadIconDx(GetModuleHandle(NULL), IDI_PROCESS, uType);
#else
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
#endif
}

inline HICON GetIconOfWindowDx(HWND hwnd, UINT uType)
{
#ifdef IDI_WINDOW
    return LoadIconDx(GetModuleHandle(NULL), IDI_WINDOW, uType);
#else
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
#endif
}

inline BOOL IsProcessWow64Dx(DWORD pid)
{
    BOOL bIsWow64 = FALSE;
    const DWORD dwAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
    if (HANDLE hProcess = ::OpenProcess(dwAccess, FALSE, pid))
    {
        bIsWow64 = IsProcessWow64Dx(hProcess);
        ::CloseHandle(hProcess);
    }
    return bIsWow64;
}

inline BOOL IsProcessWow64Dx(HANDLE hProcess)
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

inline DWORD ProcessFromWindowDx(HWND hwnd)
{
    DWORD pid = 0;
    ::GetWindowThreadProcessId(hwnd, &pid);
    return pid;
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

inline HICON LoadIconDx(HINSTANCE hInst, LPCTSTR pszIcon, UINT uType)
{
    HICON hIcon = NULL;
    INT cx, cy;
    switch (uType)
    {
    case ICON_SMALL:
        cx = GetSystemMetrics(SM_CXSMICON);
        cy = GetSystemMetrics(SM_CYSMICON);
        hIcon = (HICON)LoadImage(hInst, pszIcon, IMAGE_ICON, cx, cy, 0);
        if (hIcon)
            break;

    case ICON_BIG:
        hIcon = LoadIcon(hInst, pszIcon);
        break;
    }
    return hIcon;
}

inline HICON LoadIconDx(HINSTANCE hInst, UINT nIconID, UINT uType)
{
    return LoadIconDx(hInst, MAKEINTRESOURCE(nIconID), uType);
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
