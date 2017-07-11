// MyNotepad.cpp --- A Win32 application                -*- C++ -*-
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////

// the Win32 application
struct MMyNotepad : public MWindowBase
{
    INT         m_argc;         // number of command line parameters
    TCHAR **    m_targv;        // command line parameters

    HINSTANCE   m_hInst;        // the instance handle
    HICON       m_hIcon;        // the icon handle
    HACCEL      m_hAccel;       // the accelerator handle
    MEditCtrl   m_edit_ctrl;
    MTextType   m_text_type;
    MString     m_file_name;
    HFONT       m_hFont;
    LOGFONT     m_lf;

    HBRUSH      m_hbrBackground;

    // constructors
    MMyNotepad(int argc, TCHAR **targv, HINSTANCE hInst) :
        m_argc(argc),
        m_targv(targv),
        m_hInst(hInst),
        m_hIcon(NULL),
        m_hAccel(NULL),
        m_hbrBackground(NULL)
    {
        ZeroMemory(&m_lf, sizeof(m_lf));
        m_lf.lfCharSet = DEFAULT_CHARSET;
        m_lf.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
        m_lf.lfQuality = ANTIALIASED_QUALITY;
        m_hFont = ::CreateFontIndirect(&m_lf);
    }

    virtual void ModifyWndClassDx(WNDCLASSEX& wcx)
    {
        MWindowBase::ModifyWndClassDx(wcx);
        wcx.lpszMenuName = MAKEINTRESOURCE(1);
    }

    virtual LRESULT CALLBACK
    WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            DO_MSG(WM_CREATE, OnCreate);
            DO_MSG(WM_COMMAND, OnCommand);
            DO_MSG(WM_SIZE, OnSize);
            DO_MSG(WM_DROPFILES, OnDropFiles);
            DO_MSG(WM_DESTROY, OnDestroy);
            DO_MSG(WM_CLOSE, OnClose);
            DO_MSG(WM_INITMENU, OnInitMenu);
        default:
            return DefaultProcDx(hwnd, uMsg, wParam, lParam);
        }
        return 0;
    }

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        ::DragAcceptFiles(hwnd, TRUE);

        DWORD style = ES_LEFT | ES_MULTILINE | WS_CHILD | WS_VISIBLE |
                      WS_TABSTOP | WS_VSCROLL;
        DWORD exstyle = WS_EX_CLIENTEDGE;

        if (!m_edit_ctrl.CreateWindowDx(hwnd, TEXT("This is a sample."), style, exstyle))
        {
            return FALSE;
        }
        SetWindowFont(m_edit_ctrl, m_hFont, TRUE);

        if (m_argc >= 2)
        {
            LoadDx(hwnd, m_targv[1]);
        }

        INT cch = m_edit_ctrl.GetWindowTextLength();
        m_edit_ctrl.SetSel(cch, cch);
        ::SetFocus(m_edit_ctrl);

        return TRUE;
    }

    void OnInitMenu(HWND hwnd, HMENU hMenu)
    {
        if (m_edit_ctrl.CanUndo())
        {
            ::EnableMenuItem(hMenu, IDM_UNDO, MF_BYCOMMAND | MF_ENABLED);
        }
        else
        {
            ::EnableMenuItem(hMenu, IDM_UNDO, MF_BYCOMMAND | MF_GRAYED);
        }

        INT start, end;
        m_edit_ctrl.GetSel(start, end);
        if (start == end)
        {
            ::EnableMenuItem(hMenu, IDM_CUT, MF_BYCOMMAND | MF_GRAYED);
            ::EnableMenuItem(hMenu, IDM_COPY, MF_BYCOMMAND | MF_GRAYED);
            ::EnableMenuItem(hMenu, IDM_DELETE, MF_BYCOMMAND | MF_GRAYED);
        }
        else
        {
            ::EnableMenuItem(hMenu, IDM_CUT, MF_BYCOMMAND | MF_ENABLED);
            ::EnableMenuItem(hMenu, IDM_COPY, MF_BYCOMMAND | MF_ENABLED);
            ::EnableMenuItem(hMenu, IDM_DELETE, MF_BYCOMMAND | MF_ENABLED);
        }

        if (::IsClipboardFormatAvailable(CF_TEXT))
        {
            ::EnableMenuItem(hMenu, IDM_PASTE, MF_BYCOMMAND | MF_ENABLED);
        }
        else
        {
            ::EnableMenuItem(hMenu, IDM_PASTE, MF_BYCOMMAND | MF_GRAYED);
        }
    }

    void OnDropFiles(HWND hwnd, HDROP hdrop)
    {
        TCHAR szPath[MAX_PATH];
        ::DragQueryFile(hdrop, 0, szPath, MAX_PATH);

        LoadDx(hwnd, szPath);

        ::DragFinish(hdrop);
    }

    BOOL LoadDx(HWND hwnd, LPCTSTR pszFileName)
    {
        DWORD dwSize;
        LPBYTE bin = GetFileContentsDx(pszFileName, &dwSize);
        if (bin == NULL)
        {
            MsgBoxDx(IDS_CANNOTOPEN, IDS_APPNAME, MB_ICONERROR);
            return FALSE;
        }

        m_text_type.nNewLine = MNEWLINE_NOCHANGE;
        MStringW wide = mstr_from_bin(bin, dwSize, &m_text_type);

        MWideToText text(wide);
        m_edit_ctrl.SetWindowText(text);
        free(bin);

        m_file_name = pszFileName;
        m_edit_ctrl.SetModify(FALSE);
        return TRUE;
    }

    BOOL SaveDx(HWND hwnd, LPCTSTR pszFileName)
    {
        MStringW wide(MTextToWide(m_edit_ctrl.GetWindowText()));
        m_text_type.nNewLine = MNEWLINE_NOCHANGE;
        std::string bin = mbin_from_str(wide, m_text_type);
        if (PutFileContentsDx(pszFileName, &bin[0], bin.size()));
        {
            m_file_name = pszFileName;
            m_edit_ctrl.SetModify(FALSE);
            return TRUE;
        }
        MsgBoxDx(IDS_CANNOTSAVE, IDS_APPNAME, MB_ICONERROR);
        return FALSE;
    }

    BOOL DoOpen(HWND hwnd)
    {
        MFileDialog dialog(hwnd, TEXT("txt"),
            m_file_name.c_str(), LoadStringDx(IDS_FILTER));
        if (dialog.GetOpenFileName())
        {
            return LoadDx(hwnd, dialog.GetPathName());
        }
        return FALSE;
    }

    BOOL DoSaveAs(HWND hwnd)
    {
        MFileDialog dialog(hwnd, TEXT("txt"),
            m_file_name.c_str(), LoadStringDx(IDS_FILTER));
        if (dialog.GetSaveFileName())
        {
            MString str = dialog.GetPathName();
            return SaveDx(hwnd, str.c_str());
        }
        return FALSE;
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

    void OnClose(HWND hwnd)
    {
        if (m_edit_ctrl.GetModify())
        {
            INT nID = MsgBoxDx(IDS_QUERYSAVE, IDS_APPNAME,
                MB_ICONINFORMATION | MB_YESNOCANCEL);
            switch (nID)
            {
            case IDYES:
                if (!DoSaveAs(hwnd))
                    return;
                break;
            case IDNO:
                break;
            case IDCANCEL:
                return;
            }
        }
        ::DestroyWindow(m_hwnd);
    }

    void OnDestroy(HWND hwnd)
    {
        ::DeleteObject(m_hbrBackground);
        m_hbrBackground = NULL;
        ::DeleteObject(m_hFont);
        m_hFont = NULL;

        ::PostQuitMessage(0);
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        RECT rc = GetClientRect();
        SIZE siz = SizeFromRectDx(&rc);
        ::MoveWindow(m_edit_ctrl, rc.left, rc.top, siz.cx, siz.cy, TRUE);
    }

    // IDM_EXIT
    void OnExit()
    {
        ::DestroyWindow(m_hwnd);
    }

    void DoSetFont(HWND hwnd)
    {
        MFontDialog dialog(hwnd, &m_lf, CF_SCREENFONTS | CF_NOVERTFONTS);
        if (dialog.ChooseFont())
        {
            dialog.GetCurrentFont(&m_lf);
            ::DeleteObject(m_hFont);
            m_hFont = ::CreateFontIndirect(&m_lf);
            SetWindowFont(m_edit_ctrl, m_hFont, TRUE);
            ::InvalidateRect(m_edit_ctrl, NULL, TRUE);
        }
    }

    void OnDateTime()
    {
        TCHAR szDate[64], szTime[64];
        ::GetDateFormat(LOCALE_USER_DEFAULT, 0,
            NULL, TEXT("yyyy/MM/dd"), szDate, _countof(szDate));
        ::GetTimeFormat(LOCALE_USER_DEFAULT, 0,
            NULL, TEXT("HH:mm:ss"), szTime, _countof(szTime));

        MString str = szDate;
        str += TEXT(" ");
        str += szTime;
        m_edit_ctrl.ReplaceSel(str.c_str(), TRUE);
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case IDM_OPEN:
            DoOpen(hwnd);
            break;
        case IDM_SAVEAS:
            DoSaveAs(hwnd);
            break;
        case IDM_SETFONT:
            DoSetFont(hwnd);
            break;
        case IDM_EXIT:
            OnExit();
            break;
        case IDM_ABOUT:
            OnAbout();
            break;
        case IDM_CUT:
            m_edit_ctrl.Cut();
            break;
        case IDM_COPY:
            m_edit_ctrl.Copy();
            break;
        case IDM_PASTE:
            m_edit_ctrl.Paste();
            break;
        case IDM_DELETE:
            m_edit_ctrl.Clear();
            break;
        case IDM_SELECTALL:
            m_edit_ctrl.SelectAll();
            break;
        case IDM_UNDO:
            m_edit_ctrl.Undo();
            break;
        case IDM_DATETIME:
            OnDateTime();
            break;
        }
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

void MMyNotepad::OnAbout()
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
        MMyNotepad app(__argc, __targv, hInstance);

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
