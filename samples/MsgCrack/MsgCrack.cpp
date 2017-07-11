// MsgCrack.cpp --- A Message Cracker Input Helper              -*- C++ -*-
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////

// subclassed EDIT control to handle keys
class MSubclassedEdit : public MEditCtrl
{
    virtual LRESULT CALLBACK
    WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        HWND hwndParent = ::GetParent(hwnd);
        switch (uMsg)
        {
        case WM_KEYDOWN:
            switch (wParam)
            {
            case VK_UP:
                ::SendMessage(hwndParent, WM_COMMAND, ID_UP, 0);
                break;
            case VK_DOWN:
                ::SendMessage(hwndParent, WM_COMMAND, ID_DOWN, 0);
                break;
            case VK_PRIOR:
                ::SendMessage(hwndParent, WM_COMMAND, ID_PAGEUP, 0);
                break;
            case VK_NEXT:
                ::SendMessage(hwndParent, WM_COMMAND, ID_PAGEDOWN, 0);
                break;
            default:
                return DefaultProcDx();
            }
            break;
        default:
            return DefaultProcDx();
        }
        return 0;
    }
};

//////////////////////////////////////////////////////////////////////////////

// timer IDs
#define TIMERID_FOR_COPYED_MESSAGE  777
#define TIMERID_FOR_BUTTON_DOWN     999

// the Win32 dialog application
class MMsgCrackApp : public MDialogBase
{
public:
    INT             m_argc;     // number of command line parameters
    TCHAR **        m_targv;    // command line parameters

    HINSTANCE       m_hInst;    // the instance handle
    HICON           m_hIcon;    // the icon handle
    HICON           m_hIconSm;  // the small icon handle
    HFONT           m_hFont;    // font for edt2

    // controls
    MListBox        m_hLst1;    // for lst1
    MSubclassedEdit m_hEdt1;    // for edt1
    MEditCtrl       m_hEdt2;    // for edt2
    MButton         m_hOK;      // for IDOK

    typedef std::map<MString, MString> map_type;
    map_type  m_map1;
    map_type  m_map2;

    MMsgCrackApp(int argc, TCHAR **targv, HINSTANCE hInst) :
        m_argc(argc), m_targv(targv),
        m_hInst(hInst), m_hIcon(NULL), m_hIconSm(NULL), m_hFont(NULL)
    {
    }

    ~MMsgCrackApp()
    {
        DestroyIcon(m_hIcon);
        DestroyIcon(m_hIconSm);
        DeleteObject(m_hFont);
    }

    // start up
    BOOL StartDx(INT nCmdShow)
    {
        // load accessories
        m_hIcon = LoadIconDx(1);
        m_hIconSm = LoadSmallIconDx(1);

        HFONT hFont = GetStockFont(DEFAULT_GUI_FONT);

        LOGFONT lf;
        GetObject(hFont, sizeof(lf), &lf);
        lf.lfHeight = 14;
        lf.lfFaceName[0] = 0;
        lf.lfPitchAndFamily = FIXED_PITCH | FF_DONTCARE;
        m_hFont = CreateFontIndirect(&lf);

        if (!LoadDataFile())
        {
            MsgBoxDx(LoadStringDx(2), NULL, MB_ICONERROR);
            return FALSE;
        }
        return TRUE;
    }

    BOOL ParseLine(char *line)
    {
        char *pch1 = strchr(line, ':');
        if (pch1 == NULL)
            return FALSE;

        char *pch2 = strchr(pch1 + 1, ':');
        if (pch2 == NULL)
            return FALSE;

        *pch1 = *pch2 = 0;

        MStringA str1 = line;
        MStringA str2 = pch1 + 1;
        MStringA str3 = pch2 + 1;

        mstr_trim(str1);
        mstr_trim(str2);
        mstr_trim(str3);

        mstr_replace_all(str3, "\\r\\n", "\r\n");
        mstr_replace_all(str3, "\\n", "\r\n");

        m_map1[str1] = str3;
        m_map2[str2] = str3;

        return TRUE;
    }

    BOOL LoadDataFile()
    {
        TCHAR Path[MAX_PATH];
        GetModuleFileName(NULL, Path, MAX_PATH);

#ifndef INVALID_FILE_ATTRIBUTES
    #define INVALID_FILE_ATTRIBUTES     ((DWORD)-1)
#endif

        // find "DATA.DAT" file
        TCHAR *pch = _tcsrchr(Path, TEXT('\\'));
        lstrcpy(pch, TEXT("\\DATA.DAT"));
        if (GetFileAttributes(Path) == INVALID_FILE_ATTRIBUTES)
        {
            lstrcpy(pch, TEXT("\\..\\DATA.DAT"));
            if (GetFileAttributes(Path) == INVALID_FILE_ATTRIBUTES)
            {
                lstrcpy(pch, TEXT("\\..\\..\\DATA.DAT"));
                if (GetFileAttributes(Path) == INVALID_FILE_ATTRIBUTES)
                {
                    lstrcpy(pch, TEXT("\\..\\samples\\MsgCrack\\DATA.DAT"));
                    if (GetFileAttributes(Path) == INVALID_FILE_ATTRIBUTES)
                    {
                        lstrcpy(pch, TEXT("\\..\\..\\samples\\MsgCrack\\DATA.DAT"));
                        if (GetFileAttributes(Path) == INVALID_FILE_ATTRIBUTES)
                        {
                            lstrcpy(pch, TEXT("\\..\\..\\..\\samples\\MsgCrack\\DATA.DAT"));
                        }
                    }
                }
            }
        }

        using namespace std;
        FILE *fp = _tfopen(Path, "r");
        if (fp == NULL)
            return FALSE;

        char buf[256];
        while (fgets(buf, 256, fp) != NULL)
        {
            ParseLine(buf);
        }
        fclose(fp);

        return TRUE;
    }

    INT RunDx()
    {
        DialogBoxDx(NULL, 1);
        return 0;
    }

    BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
    {
        SendMessageDx(WM_SETICON, ICON_SMALL, (LPARAM)m_hIconSm);
        SendMessageDx(WM_SETICON, ICON_BIG, (LPARAM)m_hIcon);

        SubclassChildDx(m_hLst1, lst1);
        SubclassChildDx(m_hEdt1, edt1);
        SubclassChildDx(m_hEdt2, edt2);
        SubclassChildDx(m_hOK, IDOK);

        InitListBox(hwnd);

        static const TCHAR szInitial[] = TEXT("WM_");
        m_hEdt1.SetWindowText(szInitial);
        OnEdt1Change(hwnd);

        SetWindowFont(m_hEdt2, m_hFont, TRUE);

        return TRUE;
    }

    void InitListBox(HWND hwnd)
    {
        map_type::const_iterator it, end;
        end = m_map1.end();
        for (it = m_map1.begin(); it != end; ++it)
        {
            m_hLst1.AddString(it->first.c_str());
        }
        end = m_map2.end();
        for (it = m_map2.begin(); it != end; ++it)
        {
            m_hLst1.AddString(it->first.c_str());
        }
    }

    void OnLst1SelChange(HWND hwnd)
    {
        TCHAR Buffer[256];
        INT nIndex = m_hLst1.GetCurSel();
        if (nIndex == LB_ERR)
            return;

        m_hLst1.GetText(nIndex, Buffer);

        MString str = Buffer;
        mstr_trim(str);

        map_type::iterator it;

        it = m_map1.find(str);
        if (it != m_map1.end())
        {
            m_hEdt2.SetWindowText(it->second.c_str());
            return;
        }

        it = m_map2.find(str);
        if (it != m_map2.end())
        {
            m_hEdt2.SetWindowText(it->second.c_str());
            return;
        }
    }

    void OnEdt1Change(HWND hwnd)
    {
        MString str = m_hEdt1.GetWindowText();
        mstr_trim(str);
        if (str.empty())
        {
            m_hLst1.SetCurSel(-1);
            return;
        }

        INT nIndex = m_hLst1.FindString(-1, str.c_str());
        if (nIndex == LB_ERR)
        {
            m_hLst1.SetCurSel(-1);
            return;
        }

        m_hLst1.SetCurSel(nIndex);
        OnLst1SelChange(hwnd);
    }

    void OnOK(HWND hwnd)
    {
        m_hOK.SetState(TRUE);

        MString str = m_hEdt2.GetWindowText();
        mstr_trim(str);

        str += TEXT("\r\n");
        CopyText(hwnd, str);

        ::SetTimer(hwnd, TIMERID_FOR_BUTTON_DOWN, 100, NULL);
    }

    void CopyText(HWND hwnd, MString& str)
    {
        HANDLE h = NULL;
        if (OpenClipboard(hwnd))
        {
            EmptyClipboard();

            DWORD Size = (str.size() + 1) * sizeof(TCHAR);
            LPVOID pText = GlobalAllocPtr(GHND | GMEM_SHARE, Size);
            if (pText)
            {
                CopyMemory(pText, str.c_str(), Size);
                GlobalUnlockPtr(pText);

                #ifdef UNICODE
                    h = SetClipboardData(CF_UNICODETEXT, GlobalHandle(pText));
                #else
                    h = SetClipboardData(CF_TEXT, GlobalHandle(pText));
                #endif
            }
            CloseClipboard();
        }
        if (h)
        {
            ::SetDlgItemText(hwnd, stc1, LoadStringDx(3));
            ::SetTimer(hwnd, TIMERID_FOR_COPYED_MESSAGE, 3000, NULL);
        }
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case IDOK:
            OnOK(hwnd);
            break;
        case IDCANCEL:
            ::EndDialog(hwnd, IDCANCEL);
            break;
        case lst1:
            if (codeNotify == LBN_SELCHANGE)
            {
                OnLst1SelChange(hwnd);
            }
            break;
        case edt1:
            if (codeNotify == EN_CHANGE)
            {
                OnEdt1Change(hwnd);
            }
            break;
        case ID_UP:
            OnUp(hwnd);
            break;
        case ID_DOWN:
            OnDown(hwnd);
            break;
        case ID_PAGEUP:
            OnPageUp(hwnd);
            break;
        case ID_PAGEDOWN:
            OnPageDown(hwnd);
            break;
        }
    }

    void OnUp(HWND hwnd)
    {
        INT nIndex, nNewIndex;
        nIndex = m_hLst1.GetCurSel();
        nNewIndex = nIndex - 1;
        if (nNewIndex < 0)
            nNewIndex = 0;

        m_hLst1.SetCurSel(nNewIndex);
        OnLst1SelChange(hwnd);
    }

    void OnDown(HWND hwnd)
    {
        INT nIndex, nNewIndex, nCount;
        nIndex = m_hLst1.GetCurSel();
        nCount = m_hLst1.GetCount();
        nNewIndex = nIndex + 1;
        if (nNewIndex >= nCount)
            nNewIndex = nCount - 1;

        m_hLst1.SetCurSel(nNewIndex);
        OnLst1SelChange(hwnd);
    }

    void OnPageUp(HWND hwnd)
    {
        INT nIndex, nNewIndex;
        nIndex = m_hLst1.GetCurSel();
        nNewIndex = nIndex - 10;
        if (nNewIndex < 0)
            nNewIndex = 0;

        m_hLst1.SetCurSel(nNewIndex);
        OnLst1SelChange(hwnd);
    }

    void OnPageDown(HWND hwnd)
    {
        INT nIndex, nNewIndex, nCount;
        nIndex = m_hLst1.GetCurSel();
        nCount = m_hLst1.GetCount();
        nNewIndex = nIndex + 10;
        if (nNewIndex >= nCount)
            nNewIndex = nCount - 1;

        m_hLst1.SetCurSel(nNewIndex);
        OnLst1SelChange(hwnd);
    }

    void OnTimer(HWND hwnd, UINT id)
    {
        if (id == TIMERID_FOR_BUTTON_DOWN)
        {
            m_hOK.SetState(FALSE);
            ::KillTimer(hwnd, TIMERID_FOR_BUTTON_DOWN);
        }
        if (id == TIMERID_FOR_COPYED_MESSAGE)
        {
            ::SetDlgItemText(hwnd, stc1, NULL);
            ::KillTimer(hwnd, TIMERID_FOR_COPYED_MESSAGE);
        }
    }

    virtual INT_PTR CALLBACK
    DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            DO_MSG(WM_INITDIALOG, OnInitDialog);
            DO_MSG(WM_COMMAND, OnCommand);
            DO_MSG(WM_TIMER, OnTimer);
        }
        return DefaultProcDx();
    }
}; // MMsgCrackApp

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
        MMsgCrackApp app(__argc, __targv, hInstance);

        InitCommonControls();
        MEditCtrl::SetCtrlAHookDx(TRUE);

        if (app.StartDx(nCmdShow))
        {
            ret = app.RunDx();
        }
        else
        {
            ret = 2;
        }

        MEditCtrl::SetCtrlAHookDx(FALSE);
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
