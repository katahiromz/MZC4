// ProcessLister.cpp
// Copyright (C) 2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>.
// This file is public domain software.

#include "targetver.h"
#include "MProcessListBox.hpp"
#include "MResizable.hpp"
#include "resource.h"

static const INT s_nItemHeight = 48;
static const INT s_nIconSize = 32;

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

class ProcessLister : public MDialogBase
{
public:
    HINSTANCE       m_hInst;        // the instance handle
    HICON           m_hIcon;        // the main icon
    HICON           m_hIconSm;      // the small icon
    MProcessListBox m_lst1;         // the list box
    DWORD           m_pid;          // the process id
    MResizable      m_resizable;    // make the window resizable layout

    ProcessLister(INT argc, TCHAR **targv, HINSTANCE hInst)
        : MDialogBase(IDD_MAIN), m_hInst(hInst),
          m_hIcon(NULL), m_hIconSm(NULL)
    {
        EnableProcessPriviledge(SE_DEBUG_NAME);
        m_hIcon = LoadIconDx(IDI_MAIN);
        m_hIconSm = LoadSmallIconDx(IDI_MAIN);
        m_pid = 0;
    }

    virtual ~ProcessLister()
    {
        DestroyIcon(m_hIcon);
        DestroyIcon(m_hIconSm);
    }

    void Refresh()
    {
        m_lst1.refresh();
    }

    BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
    {
        SendMessageDx(WM_SETICON, ICON_BIG, LPARAM(m_hIcon));
        SendMessageDx(WM_SETICON, ICON_SMALL, LPARAM(m_hIconSm));

        SubclassChildDx(m_lst1, lst1);
        Refresh();

        m_resizable.OnParentCreate(hwnd);

        m_resizable.SetLayoutAnchor(lst1, mzcLA_TOP_LEFT, mzcLA_BOTTOM_RIGHT);
        m_resizable.SetLayoutAnchor(psh1, mzcLA_BOTTOM_LEFT);
        m_resizable.SetLayoutAnchor(IDOK, mzcLA_BOTTOM_RIGHT);
        m_resizable.SetLayoutAnchor(IDCANCEL, mzcLA_BOTTOM_RIGHT);

        return TRUE;
    }

    void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case IDOK:
            m_lst1.get_selected_pid(m_pid);
            EndDialog(IDOK);
            break;
        case IDCANCEL:
            EndDialog(IDCANCEL);
            break;
        case psh1:
            Refresh();
            break;
        }
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        m_resizable.OnSize();
    }

    void OnMeasureItem(HWND hwnd, MEASUREITEMSTRUCT * lpMeasureItem)
    {
        if (lpMeasureItem->CtlType != ODT_LISTBOX || lpMeasureItem->CtlID != lst1)
            return;

        lpMeasureItem->itemHeight = s_nItemHeight;
    }

    void OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT * lpDrawItem)
    {
        if (lpDrawItem->CtlType != ODT_LISTBOX || lpDrawItem->CtlID != lst1)
            return;

        if (lpDrawItem->itemID == -1)
            return;

        RECT rcItem = lpDrawItem->rcItem;
        HDC hDC = lpDrawItem->hDC;
        if (lpDrawItem->itemState & ODS_SELECTED)
        {
            FillRect(hDC, &rcItem, (HBRUSH)(COLOR_HIGHLIGHT + 1));
        }
        else
        {
            FillRect(hDC, &rcItem, (HBRUSH)(COLOR_WINDOW + 1));
        }

        if (lpDrawItem->itemState & ODS_FOCUS)
        {
            DrawFocusRect(hDC, &rcItem);
        }

        LPVOID pData = (LPVOID)lpDrawItem->itemData;
        MProcessListBox::entry_type *entry = (MProcessListBox::entry_type *)pData;

        DWORD pid = entry->th32ProcessID;
        HWND window = WindowFromProcessDx(pid);
        INT iImage = entry->iImage;
        MString strFullPath = GetPathOfProcessDx(pid);
        MString strWindowText = MWindowBase::GetWindowText(window);

        INT xyIcon = (s_nItemHeight - s_nIconSize) / 2;

        ImageList_DrawEx(m_lst1.ImageList(), iImage, hDC,
            rcItem.left + xyIcon, rcItem.top + xyIcon,
            s_nIconSize, s_nIconSize,
            CLR_NONE, CLR_NONE, ILD_NORMAL | ILD_TRANSPARENT);

        SetBkMode(hDC, TRANSPARENT);

        TCHAR szText[MAX_PATH];
        UINT uFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS;
        if (lpDrawItem->itemState & ODS_SELECTED)
        {
            SetBkColor(hDC, GetSysColor(COLOR_HIGHLIGHT));
            SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
        }
        else
        {
            SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
            SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
        }

        RECT rc;
        rc = rcItem;
        rc.left = s_nItemHeight;
        rc.top += s_nItemHeight / 6;
        rc.bottom = (rc.top + rc.bottom) / 2;
        if (window)
            StringCbPrintf(szText, sizeof(szText), TEXT("PID:%08lX, HWND:%p"),
                           pid, (HWND)window);
        else
            StringCbPrintf(szText, sizeof(szText), TEXT("PID:%08lX"), pid);
        DrawText(hDC, szText, -1, &rc, uFormat);

        rc = rcItem;
        rc.left = s_nItemHeight;
        rc.top = (rc.top + rc.bottom) / 2;
        rc.bottom -= s_nItemHeight / 6;
        if (strFullPath.size() && strWindowText.size())
        {
            StringCbPrintf(szText, sizeof(szText), TEXT("%s %s"),
                           strWindowText.c_str(), strFullPath.c_str());
        }
        else if (!strFullPath.size() && strWindowText.size())
        {
            StringCbPrintf(szText, sizeof(szText), TEXT("%s %s"),
                           strWindowText.c_str(), entry->szExeFile);
        }
        else if (strFullPath.size() && !strWindowText.size())
        {
            StringCbPrintf(szText, sizeof(szText), TEXT("%s"),
                           strFullPath.c_str());
        }
        else if (!strFullPath.size() && !strWindowText.size())
        {
            StringCbPrintf(szText, sizeof(szText), TEXT("%s"),
                           entry->szExeFile);
        }
        DrawText(hDC, szText, -1, &rc, uFormat);
    }

    virtual INT_PTR CALLBACK
    DialogProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hwnd, WM_SIZE, OnSize);
        HANDLE_MSG(hwnd, WM_MEASUREITEM, OnMeasureItem);
        HANDLE_MSG(hwnd, WM_DRAWITEM, OnDrawItem);
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
            StringCbPrintf(szText, sizeof(szText), TEXT("pid: 0x%08lX"), m_pid);
            MsgBoxDx(szText, TEXT("Selected Process"), MB_ICONINFORMATION);
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
        ProcessLister app(__argc, __targv, hInstance);

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
