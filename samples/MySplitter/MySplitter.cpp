// MySplitter.cpp --- A Win32 application                       -*- C++ -*-
//////////////////////////////////////////////////////////////////////////////

#include "MWindowBase.hpp"
#include "MSplitterWnd.hpp"
#include "MEditCtrl.hpp"

//////////////////////////////////////////////////////////////////////////////

class MMySplitter : public MWindowBase
{
public:
    MSplitterWnd m_splitter;
    MEditCtrl m_edit[3];

    MMySplitter()
    {
    }

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        MSplitterWnd::CursorNS() = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(1));
        MSplitterWnd::CursorWE() = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(2));

        DWORD style = WS_CHILD | WS_VISIBLE | SWS_HORZ | SWS_RIGHTALIGN;
        DWORD exstyle = 0;
        if (!m_splitter.CreateDx(hwnd, 3, style, exstyle))
            return FALSE;

        for (INT i = 0; i < 3; ++i)
        {
            TCHAR szText[64];
#ifdef NO_STRSAFE
            wsprintf(szText, TEXT("m_edit[%d]"), i);
#else
            StringCchPrintf(szText, _countof(szText), TEXT("m_edit[%d]"), i);
#endif
            style = WS_CHILD | WS_VISIBLE | ES_CENTER;
            exstyle = WS_EX_CLIENTEDGE;
            if (!m_edit[i].CreateAsChildDx(m_splitter, szText, style, exstyle))
                return FALSE;

            m_splitter.SetPane(i, m_edit[i]);
        }

        m_splitter.SetPaneExtent(0, 50);
        m_splitter.SetPaneMinExtent(1, 100);

        return TRUE;
    }

    INT StartDx(INT nCmdShow)
    {
        if (!CreateWindowDx(NULL, TEXT("MySplitter"), WS_OVERLAPPEDWINDOW, 0,
                            CW_USEDEFAULT, CW_USEDEFAULT, 500, 300))
        {
            return 1;
        }

        ShowWindow(m_hwnd, nCmdShow);
        UpdateWindow(m_hwnd);
        return 0;
    }

    INT RunDx()
    {
        MSG msg;
        while (::GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return INT(msg.wParam);
    }

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);
        MoveWindow(m_splitter, 0, 0, rc.right, rc.bottom, TRUE);
    }

    void OnDestroy(HWND hwnd)
    {
        PostQuitMessage(0);
    }

    virtual LRESULT CALLBACK
    WindowProcDx(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hwnd, WM_SIZE, OnSize);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        default:
            return DefaultProcDx();
        }
    }
};

//////////////////////////////////////////////////////////////////////////////

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    MMySplitter app;
    INT ret = app.StartDx(nCmdShow);
    if (ret == 0)
    {
        return app.RunDx();
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////
