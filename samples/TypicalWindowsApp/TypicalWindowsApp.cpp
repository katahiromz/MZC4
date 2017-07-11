// TypicalWindowsApp.cpp --- A Win32 application                -*- C++ -*-
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////

// the Win32 application
struct MTypicalWindowsApp : public MWindowBase
{
    INT         m_argc;         // number of command line parameters
    TCHAR **    m_targv;        // command line parameters

    HINSTANCE   m_hInst;        // the instance handle
    HICON       m_hIcon;        // the icon handle
    HACCEL      m_hAccel;       // the accelerator handle

    // constructors
    MTypicalWindowsApp(int argc, TCHAR **targv, HINSTANCE hInst) :
        m_argc(argc),
        m_targv(targv),
        m_hInst(hInst),
        m_hIcon(NULL),
        m_hAccel(NULL)
    {
    }

    virtual void ModifyWndClassDx(WNDCLASSEX& wcx)
    {
        MWindowBase::ModifyWndClassDx(wcx);
        wcx.lpszMenuName = MAKEINTRESOURCE(1);
    }

    BOOL StartDx(INT nCmdShow)
    {
        m_hIcon = ::LoadIcon(m_hInst, MAKEINTRESOURCE(1));
        m_hAccel = ::LoadAccelerators(m_hInst, MAKEINTRESOURCE(1));

        if (!CreateWindowDx(NULL, LoadStringDx(1)))
        {
            MsgBoxDx(TEXT("failure of CreateWindow"), NULL, MB_ICONERROR);
            return FALSE;
        }

        ::ShowWindow(*this, nCmdShow);
        ::UpdateWindow(*this);

        return TRUE;
    }

    // message loop
    INT RunDx()
    {
        MSG msg;
        while (::GetMessage(&msg, NULL, 0, 0))
        {
            if (!::TranslateAccelerator(m_hwnd, m_hAccel, &msg))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
        return INT(msg.wParam);
    }

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        ::DragAcceptFiles(hwnd, TRUE);
        return TRUE;
    }

    void OnDropFiles(HWND hwnd, HDROP hdrop)
    {
        TCHAR szPath[MAX_PATH];
        UINT cFiles = ::DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
        for (UINT i = 0; i < cFiles; ++i)
        {
            ::DragQueryFile(hdrop, i, szPath, MAX_PATH);
            ::MessageBox(m_hwnd, szPath, TEXT("File"), MB_ICONINFORMATION);
        }
        ::DragFinish(hdrop);
    }

    void OnDestroy(HWND hwnd)
    {
        ::PostQuitMessage(0);
    }

    void OnPaint(HWND hwnd)
    {
        RECT rc;
        ::GetClientRect(m_hwnd, &rc);

        PAINTSTRUCT ps;
        HDC hDC = ::BeginPaint(m_hwnd, &ps);
        if (hDC)
        {
            // draw something...
            SelectObject(hDC, GetStockPen(BLACK_PEN));
            ::MoveToEx(hDC, rc.left, rc.top, NULL);
            ::LineTo(hDC, rc.right, rc.bottom);
            ::MoveToEx(hDC, rc.right, rc.top, NULL);
            ::LineTo(hDC, rc.left, rc.bottom);

            MString str = LoadStringDx(IDS_APPNAME);
            ::SetBkMode(hDC, TRANSPARENT);
            ::TextOut(hDC, 0, 0, str.c_str(), int(str.size()));

            ::EndPaint(m_hwnd, &ps);
        }
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        ::InvalidateRect(m_hwnd, NULL, TRUE);
    }

    // IDM_EXIT
    void OnExit()
    {
        ::DestroyWindow(m_hwnd);
    }

    // IDM_ABOUT
    void OnAbout();

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case IDM_EXIT:
            MsgBoxDx(TEXT("I will exit!"), MB_ICONINFORMATION);
            OnExit();
            break;
        case IDM_ABOUT:
            OnAbout();
            break;
        }
    }

    virtual LRESULT CALLBACK
    WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            DO_MSG(WM_CREATE, OnCreate);
            DO_MSG(WM_COMMAND, OnCommand);
            DO_MSG(WM_SIZE, OnSize);
            DO_MSG(WM_PAINT, OnPaint);
            DO_MSG(WM_DROPFILES, OnDropFiles);
            DO_MSG(WM_DESTROY, OnDestroy);
        default:
            return DefaultProcDx(hwnd, uMsg, wParam, lParam);
        }
        return 0;
    }
};

//////////////////////////////////////////////////////////////////////////////

struct MAboutDialog : public MDialogBase
{
    virtual INT_PTR CALLBACK
    DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            DO_MSG(WM_INITDIALOG, OnInitDialog);
            DO_MSG(WM_COMMAND, OnCommand);
        }
        return DefaultProcDx(hwnd, uMsg, wParam, lParam);
    }

    BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
    {
        CenterWindowDx();
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
        default:
            break;
        }
    }
};

void MTypicalWindowsApp::OnAbout()
{
    MAboutDialog about;
    about.DialogBoxDx(m_hwnd, IDD_ABOUTBOX);
}

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
        MTypicalWindowsApp app(__argc, __targv, hInstance);

        ::InitCommonControls();

        HRESULT hres = ::CoInitialize(NULL);

        if (app.StartDx(nCmdShow))
        {
            ret = app.RunDx();
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
