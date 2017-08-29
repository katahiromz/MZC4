// ProcessMakerTest.cpp --- A Win32 application                -*- C++ -*-
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////

struct MSubclassedEditCtrl : public MEditCtrl
{
public:
    virtual LRESULT CALLBACK
    WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_KEYUP:
            if (wParam == VK_RETURN)
            {
                return 0;
            }
            break;
        case WM_KEYDOWN:
            if (wParam == VK_RETURN)
            {
                PostMessage(GetParent(hwnd), WM_COMMAND, MAKEWPARAM(3, BN_CLICKED), (LPARAM)m_hwnd);
                return 0;
            }
            break;
        case WM_CHAR:
            if (wParam == '\n')
            {
                return 0;
            }
            break;
        }
        return DefaultProcDx();
    }
};

// the Win32 application
struct MProcessMakerTest : public MWindowBase
{
    INT         m_argc;         // number of command line parameters
    TCHAR **    m_targv;        // command line parameters

    HINSTANCE   m_hInst;        // the instance handle
    HICON       m_hIcon;        // the icon handle
    HICON       m_hIconSm;      // the small icon handle
    HACCEL      m_hAccel;       // the accelerator handle
    HFONT       m_hFont;
    HANDLE      m_hThread;
    unsigned    m_child_thread_id;
    unsigned    m_main_thread_id;
    MEditCtrl   m_hConsoleOutput;
    MSubclassedEditCtrl     m_hTextBox;
    MButton     m_hEnterButton;
    MFile       m_hInputWrite;
    MFile       m_hOutputRead;
    MProcessMaker m_pmaker;
    MStringA    m_text;

    MProcessMakerTest(int argc, TCHAR **targv, HINSTANCE hInst) :
        m_argc(argc), m_targv(targv), m_hInst(hInst),
        m_hIcon(NULL), m_hIconSm(NULL), m_hAccel(NULL),
        m_hFont(NULL), m_hThread(NULL)
    {
    }

    virtual void ModifyWndClassDx(WNDCLASSEX& wcx)
    {
        MWindowBase::ModifyWndClassDx(wcx);
        wcx.lpszMenuName = MAKEINTRESOURCE(1);
        wcx.hIcon = m_hIcon;
        wcx.hIconSm = m_hIconSm;
    }

    BOOL StartDx(INT nCmdShow)
    {
        m_hIcon = LoadIconDx(1);
        m_hIconSm = LoadSmallIconDx(1);
        m_hAccel = ::LoadAccelerators(m_hInst, MAKEINTRESOURCE(1));

        if (!CreateWindowDx(NULL, LoadStringDx(1), WS_OVERLAPPEDWINDOW, 0, 
                            CW_USEDEFAULT, CW_USEDEFAULT, 640, 400))
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
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        return INT(msg.wParam);
    }

    static unsigned __stdcall ThreadProc(void *param)
    {
        MProcessMakerTest *this_ = (MProcessMakerTest *)param;

        DWORD cbAvail, cbRead;
        CHAR szBuf[256];
        while (this_->m_hOutputRead.PeekNamedPipe(NULL, 0, NULL, &cbAvail))
        {
            if (cbAvail == 0)
            {
                if (!this_->m_pmaker.IsRunning())
                    break;

                this_->m_pmaker.WaitForSingleObject(500);
                continue;
            }

            if (cbAvail > sizeof(szBuf))
                cbAvail = sizeof(szBuf);
            else if (cbAvail == 0)
                continue;

            if (this_->m_hOutputRead.ReadFile(szBuf, cbAvail, &cbRead))
            {
                if (cbRead == 0)
                    continue;

                this_->m_text.insert(this_->m_text.end(), &szBuf[0], &szBuf[cbRead]);
                PostMessage(this_->m_hwnd, WM_COMMAND, IDM_UPDATE, 0);
            }
        }

        return 0;
    }

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        DWORD style;
        DWORD exstyle;

        style = ES_LEFT | ES_MULTILINE | ES_READONLY | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL;
        exstyle = WS_EX_CLIENTEDGE;
        if (!m_hConsoleOutput.CreateAsChildDx(hwnd, NULL, style, exstyle, 1))
            return FALSE;

        style = ES_LEFT | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP;
        exstyle = WS_EX_CLIENTEDGE;
        if (!m_hTextBox.CreateAsChildDx(hwnd, NULL, style, exstyle, 2))
            return FALSE;
        m_hTextBox.SubclassDx(m_hTextBox);

        style = BS_PUSHBUTTON | BS_CENTER | BS_VCENTER | WS_CHILD | WS_VISIBLE | WS_TABSTOP;
        exstyle = 0;
        if (!m_hEnterButton.CreateAsChildDx(hwnd, TEXT("Enter"), style, exstyle, 3))
            return FALSE;

        LOGFONT lf;
        ZeroMemory(&lf, sizeof(lf));
        lf.lfHeight = 14;
        lf.lfCharSet = DEFAULT_CHARSET;
        lf.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
        m_hFont = ::CreateFontIndirect(&lf);

        SetWindowFont(m_hConsoleOutput, m_hFont, TRUE);
        SetWindowFont(m_hTextBox, m_hFont, TRUE);
        SetWindowFont(m_hEnterButton, m_hFont, TRUE);

        m_main_thread_id = GetCurrentThreadId();

        m_pmaker.SetShowWindow(SW_HIDE);
        m_pmaker.SetCreationFlags(CREATE_NEW_CONSOLE);
        if (m_pmaker.PrepareForRedirect(&m_hInputWrite, &m_hOutputRead) &&
            m_pmaker.CreateProcess(NULL, TEXT("cmd.exe")))
        {
            m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, 0, &m_child_thread_id);
        }

        if (m_hThread == NULL)
        {
            m_hConsoleOutput.SetWindowText(TEXT("(Sorry, Failed to start up)"));
        }

        SetFocus(m_hTextBox);
        return TRUE;
    }

    void OnDestroy(HWND hwnd)
    {
        ::PostQuitMessage(0);
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        HDC hDC = GetDC(m_hConsoleOutput);
        SIZE siz;
        HGDIOBJ hFontOld = SelectObject(hDC, m_hFont);
        GetTextExtentPoint32(hDC, TEXT("Enter"), 5, &siz);
        SelectObject(hDC, hFontOld);
        ReleaseDC(m_hConsoleOutput, hDC);

        siz.cx += 8;
        siz.cy += 8;

        MoveWindow(m_hConsoleOutput, 0, 0, cx, cy - siz.cy, TRUE);
        MoveWindow(m_hTextBox, 0, cy - siz.cy, cx - siz.cx, siz.cy, TRUE);
        MoveWindow(m_hEnterButton, cx - siz.cx, cy - siz.cy, siz.cx, siz.cy, TRUE);
    }

    // IDM_EXIT
    void OnExit()
    {
        m_pmaker.TerminateProcess(-1);
        m_pmaker.CloseAll();
        ::DestroyWindow(m_hwnd);
    }

    // IDM_ABOUT
    void OnAbout();

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        if (codeNotify == BN_CLICKED && id == 3)
        {
            char buf[256];
            ::GetWindowTextA(m_hTextBox, buf, _countof(buf));
            lstrcatA(buf, "\r\n");
            int len = lstrlenA(buf);
            DWORD cbWritten;
            m_hInputWrite.WriteFile(buf, len, &cbWritten);
            ::SetWindowTextA(m_hConsoleOutput, m_text.c_str());
            ::SetWindowTextA(m_hTextBox, "");
            return;
        }
        switch (id)
        {
        case IDM_EXIT:
            OnExit();
            break;
        case IDM_ABOUT:
            OnAbout();
            break;
        case IDM_UPDATE:
            {
                LockWindowUpdate(m_hConsoleOutput);
                ::SetWindowTextA(m_hConsoleOutput, m_text.c_str());
                SendMessage(m_hConsoleOutput, WM_VSCROLL, MAKEWPARAM(SB_BOTTOM, 0), 0);
                LockWindowUpdate(NULL);
            }
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
            DO_MSG(WM_DESTROY, OnDestroy);
            DO_MSG(WM_ACTIVATE, OnActivate);
            DO_MSG(WM_CTLCOLORSTATIC, OnCtlColor);
        }
        return DefaultProcDx(hwnd, uMsg, wParam, lParam);
    }

    HBRUSH OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, int type)
    {
        if (m_hConsoleOutput == hwndChild)
        {
            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkColor(hdc, RGB(0, 0, 0));
            SetBkMode(hdc, OPAQUE);
            return GetStockBrush(BLACK_BRUSH);
        }

        return FORWARD_WM_CTLCOLORSTATIC(hwnd, hdc, hwndChild, DefWindowProc);
    }

    void OnActivate(HWND hwnd, UINT state, HWND hwndActDeact, BOOL fMinimized)
    {
        m_hTextBox.SetSel(0, -1);
        SetFocus(m_hTextBox);
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
        assert(hwnd);
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

void MProcessMakerTest::OnAbout()
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
        MProcessMakerTest app(__argc, __targv, hInstance);

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
