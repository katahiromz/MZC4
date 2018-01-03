// TriStateTV.cpp --- A Win32 Dialog application          -*- C++ -*-
//////////////////////////////////////////////////////////////////////////////

#include "MTriStateTreeView.hpp"

//////////////////////////////////////////////////////////////////////////////

// the Win32 dialog application
struct MTriStateTVSample : public MDialogBase
{
    INT         m_argc;         // number of command line parameters
    TCHAR **    m_targv;        // command line parameters

    HINSTANCE   m_hInst;        // the instance handle
    HICON       m_hIcon;        // the icon handle
    HICON       m_hIconSm;      // the small icon handle
    HACCEL      m_hAccel;       // the accelerator handle
    HIMAGELIST  m_himl;

    MTriStateTreeView m_hTV;

    MTriStateTVSample(int argc, TCHAR **targv, HINSTANCE hInst) :
        m_argc(argc), m_targv(targv), m_hInst(hInst),
        m_hIcon(NULL), m_hIconSm(NULL), m_hAccel(NULL), m_himl(NULL)
    {
    }

    ~MTriStateTVSample()
    {
        if (m_himl)
        {
            ImageList_Destroy(m_himl);
            m_himl = NULL;
        }
    }

    // start up
    BOOL StartDx(INT nCmdShow)
    {
        // load accessories
        m_hIcon = LoadIconDx(1);
        m_hIconSm = LoadSmallIconDx(1);
        m_hAccel = ::LoadAccelerators(m_hInst, MAKEINTRESOURCE(1));

        return TRUE;
    }

    // message loop
    INT RunDx()
    {
        return INT(DialogBoxDx(NULL, 1));
    }

    HTREEITEM InsertTreeItem(HTREEITEM hitemParent, LPCTSTR lpszName, INT iImage)
    {
        TV_INSERTSTRUCT is = {0};

        is.hParent      = hitemParent;
        is.item.mask    = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        is.item.pszText = const_cast<LPTSTR>(lpszName);
        is.item.iImage = iImage;
        is.item.iSelectedImage = iImage;

        return m_hTV.InsertItem(&is);
    }

    BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
    {
        CenterWindowDx();
        ::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)m_hIcon);
        ::SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)m_hIconSm);

        m_hTV.SubclassDx(GetDlgItem(hwnd, ctl1));
        m_hTV.InitStateImageList(1);
        m_hTV.SetItemHeight(16);

        m_himl = ImageList_LoadBitmap(m_hInst, MAKEINTRESOURCE(2), 16, 0, RGB(255, 0, 255));
        assert(m_himl);
        m_hTV.SetImageList(m_himl, TVSIL_NORMAL);

        HTREEITEM hRoot = InsertTreeItem(TVI_ROOT, TEXT("A"), 0);
        HTREEITEM hParent1 = InsertTreeItem(hRoot, TEXT("B"), 1);
        HTREEITEM hChild1 = InsertTreeItem(hParent1, TEXT("C"), 2);
        HTREEITEM hChild2 = InsertTreeItem(hParent1, TEXT("D"), 3);
        HTREEITEM hParent2 = InsertTreeItem(hRoot, TEXT("E"), 4);
        HTREEITEM hChild3 = InsertTreeItem(hParent2, TEXT("F"), 5);
        HTREEITEM hChild4 = InsertTreeItem(hParent2, TEXT("G"), 6);
        m_hTV.Expand(hRoot);
        m_hTV.Expand(hParent1);
        m_hTV.Expand(hParent2);

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
            DO_MSG(WM_NOTIFY, OnNotify);
        }
        return DefaultProcDx();
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        MoveWindow(m_hTV, 0, 0, cx, cy, TRUE);
    }

    LRESULT OnNotify(HWND hwnd, int idFrom, LPNMHDR pnmhdr)
    {
        return m_hTV.OnNotifyFromParent(m_hTV, idFrom, pnmhdr);
    }
}; // MTriStateTVSample

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
        MTriStateTVSample app(__argc, __targv, hInstance);

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
