// TypicalDialogApp.cpp --- A Win32 Dialog application          -*- C++ -*-
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////

// the Win32 dialog application
struct MTypicalDialogApp : public MDialogBase
{
    INT         m_argc;         // number of command line parameters
    TCHAR **    m_targv;        // command line parameters

    HINSTANCE   m_hInst;        // the instance handle
    HICON       m_hIcon;        // the icon handle
    HACCEL      m_hAccel;       // the accelerator handle

    MResizable  m_resizable;    // realize a resizable dialog

    MTypicalDialogApp(int argc, TCHAR **targv, HINSTANCE hInst) :
        m_argc(argc),
        m_targv(targv),
        m_hInst(hInst),
        m_hIcon(NULL),
        m_hAccel(NULL)
    {
    }

    // start up
    BOOL StartDx(INT nCmdShow)
    {
        // load accessories
        m_hIcon = ::LoadIcon(m_hInst, MAKEINTRESOURCE(1));
        m_hAccel = ::LoadAccelerators(m_hInst, MAKEINTRESOURCE(1));

        return TRUE;
    }

    // message loop
    INT RunDx()
    {
        return INT(DialogBoxDx(NULL, 1));
    }

    BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
    {
        CenterWindowDx();
        ::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)m_hIcon);

        m_resizable.OnParentCreate(hwnd);
        m_resizable.SetLayoutAnchor(stc1, mzcLA_TOP_LEFT);
        m_resizable.SetLayoutAnchor(edt1, mzcLA_TOP_LEFT, mzcLA_BOTTOM_RIGHT);
        m_resizable.SetLayoutAnchor(IDOK, mzcLA_BOTTOM_CENTER);

        ::SetDlgItemText(hwnd, edt1, TEXT("This is an EDIT control."));

        return TRUE;
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case IDOK:
            ::EndDialog(hwnd, IDOK);
            break;
        case IDCANCEL:
            ::EndDialog(hwnd, IDCANCEL);
            break;
        }
    }

    virtual INT_PTR CALLBACK
    DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            DO_MSG(WM_INITDIALOG, OnInitDialog);
            DO_MSG(WM_COMMAND, OnCommand);
            DO_MSG(WM_SIZE, OnSize);
        }
        return DefaultProcDx();
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        m_resizable.OnSize();
    }
}; // MTypicalDialogApp

//////////////////////////////////////////////////////////////////////////////
// Win32 App main function

extern "C"
INT APIENTRY _tWinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPTSTR      lpCmdLine,
    INT         nCmdShow)
{
    int ret;

    {
        MTypicalDialogApp app(__argc, __targv, hInstance);

        ::InitCommonControls();
        HRESULT hres = ::CoInitialize(NULL);

        if (app.StartDx(nCmdShow))
        {
            ret = INT(app.RunDx());
        }
        else
        {
            ret = 2;
        }

        if (hres == S_OK)
        {
            ::CoUninitialize();
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
