// WindowTreeViewer.cpp
// Copyright (C) 2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>.
// This file is public domain software.

#include "targetver.h"
#include "MWindowTreeView.hpp"
#include "MResizable.hpp"
#include "resource.h"

BOOL EnableProcessPriviledge(LPCTSTR pszSE_)
{
    BOOL f;
    HANDLE hProcess;
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tp;
    
    f = FALSE;
    hProcess = GetCurrentProcess();
    if (OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        if (LookupPrivilegeValue(NULL, pszSE_, &luid))
        {
            tp.PrivilegeCount = 1;
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            tp.Privileges[0].Luid = luid;
            f = AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL);
        }
        CloseHandle(hToken);
    }
    return f;
}

class WindowTreeViewer : public MDialogBase
{
public:
    HINSTANCE   m_hInst;        // the instance handle
    HICON       m_hIcon;        // the main icon
    HICON       m_hIconSm;      // the small icon
    HWND                m_hwndSelected;
    MWindowTreeView     m_ctl1;
    MResizable          m_resizable;

    WindowTreeViewer(HINSTANCE hInst)
        : MDialogBase(IDD_MAIN), m_hInst(hInst),
          m_hIcon(NULL), m_hIconSm(NULL), m_hwndSelected(NULL)
    {
        m_hIcon = LoadIconDx(IDI_MAIN);
        m_hIconSm = LoadSmallIconDx(IDI_MAIN);
    }

    virtual ~WindowTreeViewer()
    {
        DestroyIcon(m_hIcon);
        DestroyIcon(m_hIconSm);
    }

    BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
    {
        EnableProcessPriviledge(SE_DEBUG_NAME);

        SubclassChildDx(m_ctl1, ctl1);

        m_ctl1.set_style(MWTVS_PROCESSWINDOW);
        //m_ctl1.set_style(MWTVS_PROCESSTHREAD);
        //m_ctl1.set_style(MWTVS_DESKTOPTREE);

        if (HINSTANCE hinstUXTheme = LoadLibrary(TEXT("UXTHEME")))
        {
            typedef HRESULT (WINAPI *SETWINDOWTHEME)(HWND, LPCWSTR, LPCWSTR);
            SETWINDOWTHEME pSetWindowTheme =
                (SETWINDOWTHEME)GetProcAddress(hinstUXTheme, "SetWindowTheme");

            if (pSetWindowTheme)
            {
                // apply Explorer's visual style
                (*pSetWindowTheme)(m_ctl1, L"Explorer", NULL);
            }

            FreeLibrary(hinstUXTheme);
        }

        m_ctl1.refresh();

        SendMessageDx(WM_SETICON, ICON_BIG, LPARAM(m_hIcon));
        SendMessageDx(WM_SETICON, ICON_SMALL, LPARAM(m_hIconSm));

        m_resizable.OnParentCreate(hwnd);

        m_resizable.SetLayoutAnchor(ctl1, mzcLA_TOP_LEFT, mzcLA_BOTTOM_RIGHT);
        m_resizable.SetLayoutAnchor(psh1, mzcLA_BOTTOM_LEFT);
        m_resizable.SetLayoutAnchor(IDOK, mzcLA_BOTTOM_RIGHT);
        m_resizable.SetLayoutAnchor(IDCANCEL, mzcLA_BOTTOM_RIGHT);

        return TRUE;
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        m_resizable.OnSize();
    }

    void OnOK(HWND hwnd)
    {
        m_hwndSelected = NULL;
        m_ctl1.get_selected_hwnd(m_hwndSelected);
        EndDialog(IDOK);
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case IDOK:
            OnOK(hwnd);
            break;
        case IDCANCEL:
            EndDialog(IDCANCEL);
            break;
        case psh1:
            m_ctl1.refresh();
            break;
        }
    }

    virtual INT_PTR CALLBACK
    DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hwnd, WM_SIZE, OnSize);
        default:
            return DefaultProcDx();
        }
    }

    BOOL StartDx(INT nCmdShow)
    {
        return TRUE;
    }

    INT RunDx()
    {
        if (IDOK == DialogBoxDx(NULL))
        {
            TCHAR szText[64];
            StringCbPrintf(szText, sizeof(szText), TEXT("HWND: 0x%08lX"),
                           (LONG)(LONG_PTR)m_hwndSelected);
            MsgBoxDx(szText, TEXT("Selected Window"), MB_ICONINFORMATION);
        }
    }
};

//////////////////////////////////////////////////////////////////////////////
// Win32 main function

extern "C"
INT APIENTRY _tWinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPTSTR      lpCmdLine,
    INT         nCmdShow)
{
    int ret = -1;

    {
        WindowTreeViewer app(hInstance);

        ::InitCommonControls();

        if (app.StartDx(nCmdShow))
        {
            ret = app.RunDx();
        }
    }

#if (WINVER >= 0x0500)
    HANDLE hProcess = GetCurrentProcess();
    DebugPrintDx(TEXT("Count of GDI objects: %ld\n"),
                 GetGuiResources(hProcess, GR_GDIOBJECTS));
    DebugPrintDx(TEXT("Count of USER objects: %ld\n"),
                 GetGuiResources(hProcess, GR_USEROBJECTS));
#endif

#if defined(_MSC_VER) && !defined(NDEBUG)
    // for detecting memory leak (MSVC only)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    return ret;
}

//////////////////////////////////////////////////////////////////////////////
