// MyBrowser.cpp --- A Win32 application                -*- C++ -*-
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////

// the Win32 application
struct MMyBrowser : public MWindowBase
{
    INT         m_argc;         // number of command line parameters
    TCHAR **    m_targv;        // command line parameters

    HINSTANCE   m_hInst;        // the instance handle
    HICON       m_hIcon;        // the icon handle
    HICON       m_hIconSm;      // the small icon handle
    HACCEL      m_hAccel;       // the accelerator handle
    HFONT       m_hFont;        // the UI font
    MOleCtrl    m_browser;      // the web browser
    MStaticCtrl m_static;       // the label
    MEditCtrl   m_address_box;  // the address box
    MButton     m_go_button;    // the "Go!" button
    MStatusBar  m_status_bar;   // the status bar
    MString     m_url;          // the URL
    MToolBarCtrl    m_toolbar;

    // constructors
    MMyBrowser(int argc, TCHAR **targv, HINSTANCE hInst) :
        m_argc(argc), m_targv(targv),
        m_hInst(hInst), m_hIcon(NULL), m_hIconSm(NULL),
        m_hAccel(NULL), m_hFont(NULL)
    {
    }

    ~MMyBrowser()
    {
        ::DestroyIcon(m_hIcon);
        ::DestroyIcon(m_hIconSm);
    }

    virtual void ModifyWndClassDx(WNDCLASSEX& wcx)
    {
        MWindowBase::ModifyWndClassDx(wcx);
        wcx.lpszMenuName = MAKEINTRESOURCE(1);
        wcx.hIcon = m_hIcon;
        wcx.hIconSm = m_hIconSm;
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
        default:
            return DefaultProcDx(hwnd, uMsg, wParam, lParam);
        }
        return 0;
    }

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        m_hFont = GetStockFont(DEFAULT_GUI_FONT);

        m_url = TEXT("https://google.co.jp");

        DWORD style, exstyle;

        style = SS_CENTER | SS_NOTIFY | SS_CENTERIMAGE | WS_VISIBLE;
        exstyle = 0;
        if (!m_static.CreateAsChildDx(hwnd, TEXT("Address:"), style, exstyle, stc1))
            return FALSE;

        style = ES_AUTOHSCROLL | ES_LEFT | ES_NOHIDESEL | WS_BORDER | WS_TABSTOP | WS_VISIBLE;
        exstyle = WS_EX_CLIENTEDGE;
        if (!m_address_box.CreateAsChildDx(hwnd, m_url.c_str(), style, exstyle, edt1))
            return FALSE;

        style = BS_DEFPUSHBUTTON | BS_CENTER | WS_TABSTOP | WS_VISIBLE;
        exstyle = WS_EX_CLIENTEDGE;
        if (!m_go_button.CreateAsChildDx(hwnd, TEXT("Go!"), style, exstyle, psh1))
            return FALSE;

        style = CCS_BOTTOM | SBARS_SIZEGRIP | WS_VISIBLE;
        exstyle = 0;
#ifndef ctl1
#define ctl1 0x04A0
#endif
        if (!m_status_bar.CreateAsChildDx(hwnd, NULL, style, exstyle, ctl1))
            return FALSE;

        if (!m_browser.CreateAsChildDx(hwnd, m_url.c_str()))
            return FALSE;

        SetWindowFont(m_static, m_hFont, TRUE);
        SetWindowFont(m_address_box, m_hFont, TRUE);
        SetWindowFont(m_go_button, m_hFont, TRUE);

        style = WS_CHILD | WS_VISIBLE | CCS_TOP | TBSTYLE_TOOLTIPS;
        if (!m_toolbar.CreateAsChildDx(hwnd, NULL, style))
            return FALSE;
        
        m_toolbar.SetButtonStructSize(sizeof(TBBUTTON));
        SIZE siz = { 0, 0 };
        m_toolbar.SetBitmapSize(siz);

        INT iBack = m_toolbar.AddString(IDS_BACK);
        INT iForward = m_toolbar.AddString(IDS_FORWARD);

        TBBUTTON buttons[] =
        {
            { -1, IDM_BACK, TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE, {0}, 0, iBack },
            { -1, IDM_FORWARD, TBSTATE_ENABLED, TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE, {0}, 0, iForward },
        };
        BOOL b = m_toolbar.AddButtons(_countof(buttons), buttons);
        assert(b);

        PostMessageDx(WM_COMMAND);

        return TRUE;
    }

    BOOL StartDx(INT nCmdShow)
    {
        m_hIcon = LoadIconDx(1);
        m_hIconSm = LoadSmallIconDx(1);
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
            if (::TranslateAccelerator(m_hwnd, m_hAccel, &msg))
                continue;

            if (m_browser.TranslateAccelerator(&msg))
                continue;

            if (msg.hwnd == m_address_box.m_hwnd)
            {
                if (msg.message == WM_KEYDOWN &&
                    msg.wParam == VK_RETURN)
                {
                    PostMessageDx(WM_COMMAND, IDM_GO, 0);
                }
            }

            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        return INT(msg.wParam);
    }

    void OnDestroy(HWND hwnd)
    {
        ::PostQuitMessage(0);
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        RECT rc;
        ::GetClientRect(hwnd, &rc);
        SIZE siz = SizeFromRectDx(&rc);

        SIZE sizTB;
        if (IsWindowVisible(m_toolbar))
        {
            m_toolbar.AutoSize();
            RECT rcTB;
            GetWindowRect(m_toolbar, &rcTB);
            sizTB = SizeFromRectDx(&rcTB);
        }
        else
        {
            sizTB.cy = 0;
        }
        rc.top += sizTB.cy;

        SIZE sizGo, sizAddress;
        HDC hDC = ::GetDC(m_go_button);
        ::GetTextExtentPoint32(hDC, TEXT("Go!"), 3, &sizGo);
        ::GetTextExtentPoint32(hDC, TEXT("Address:"), 8, &sizAddress);
        ::ReleaseDC(m_go_button, hDC);
        sizGo.cx += 8;
        sizGo.cy += 4;
        sizAddress.cx += 8;

        m_status_bar.SendMessageDx(WM_SIZE);
        RECT rcStatus;
        ::GetWindowRect(m_status_bar, &rcStatus);
        SIZE sizStatus = SizeFromRectDx(&rcStatus);

        ::MoveWindow(m_static,
            rc.left, rc.top, sizAddress.cx, sizGo.cy, TRUE);
        ::MoveWindow(m_address_box, rc.left + sizAddress.cx, rc.top,
                     siz.cx - sizGo.cx - sizAddress.cx, rc.top, TRUE);
        ::MoveWindow(m_go_button, rc.left + siz.cx - sizGo.cx,
                     rc.top, sizGo.cx, sizGo.cy, TRUE);

        ::MoveWindow(m_browser, rc.left, rc.top + sizGo.cy,
            siz.cx, siz.cy - sizGo.cy - sizStatus.cy - sizTB.cy, TRUE);
    }

    void Navigate(LPCWSTR pszURL)
    {
        HWND hwnd = NULL;
        m_browser.GetWindow(&hwnd);
        if (hwnd)
        {
            ::SetFocus(hwnd);
        }
        m_url = pszURL;
        m_address_box.SetWindowText(pszURL);
        m_browser.NavigateDx(pszURL);
    }

    // IDM_EXIT
    void OnExit()
    {
        ::DestroyWindow(m_hwnd);
    }

    void OnGoogle()
    {
        Navigate(L"https://google.com");
    }

    void OnYahoo()
    {
        Navigate(L"https://yahoo.com");
    }

    void OnBlank()
    {
        Navigate(L"about:blank");
    }

    void OnRefresh()
    {
        Navigate(m_url.c_str());
    }

    void OnAddress()
    {
        INT cch = m_address_box.GetWindowTextLength();
        m_address_box.SetSel(0, cch);
        ::SetFocus(m_address_box);
    }

    void OnGo()
    {
        MString url = m_address_box.GetWindowText();
        Navigate(MTextToWide(CP_ACP, url).c_str());
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        MWaitCursor wcur;
        m_status_bar.SetText(TEXT("Executing command..."));
        switch (id)
        {
        case IDM_BLANK:
            OnBlank();
            break;
        case IDM_GOOGLE:
            OnGoogle();
            break;
        case IDM_YAHOO:
            OnYahoo();
            break;
        case IDM_EXIT:
            OnExit();
            break;
        case IDM_ABOUT:
            OnAbout();
            break;
        case IDM_ADDRESS:
        case stc1:
            OnAddress();
            break;
        case IDM_GO:
        case psh1:
            OnGo();
            break;
        case IDM_REFRESH:
            OnRefresh();
            break;
        case IDM_BACK:
            m_browser.GoBack();
            break;
        case IDM_FORWARD:
            m_browser.GoForward();
            break;
        }
        m_status_bar.SetText(TEXT("Ready"));
    }

    // IDM_ABOUT
    void OnAbout();
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

void MMyBrowser::OnAbout()
{
    MAboutDialog about;
    about.DialogBoxDx(m_hwnd, IDD_ABOUTBOX);
}

//////////////////////////////////////////////////////////////////////////////
// Win32 App main function

extern "C"
INT APIENTRY WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    INT         nCmdShow)
{
    int ret;

    {
#ifdef UNICODE
        MMyBrowser app(__argc, __wargv, hInstance);
#else
        MMyBrowser app(__argc, __argv, hInstance);
#endif
        ::InitCommonControls();
        HRESULT hres = ::OleInitialize(NULL);

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
            ::OleUninitialize();
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
