(Japanese, UTF-8)

MsgCrack
========

これはWin32メッセージクラッカーの入力支援アプリです。
このアプリは、Win32 APIプログラミングに便利です。


動作環境
--------

Windows XP/2003/Vista/7/8/10


説明
----

メッセージクラッカーは、プリプロセッサの魔術により、WM_で始まる
Windowsメッセージ識別子とメッセージプロシージャを結びつけます。

    #include <windows.h>    // Windows API。
    #include <windowsx.h>   // for HANDLE_MSG macro

    // WM_CREATEのメッセージプロシージャ。
    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        return TRUE;
    }

    ...

    // ウィンドウプロシージャ。
    LRESULT CALLBACK
    WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam)
    {
        switch (uMsg)
        {
            HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
            HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
            ...
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

このWindowProc関数においては、HANDLE_MSGマクロによって、
WM_CREATEメッセージはOnCreate関数と結びついています。

このようなHANDLE_MSGマクロの記述がメッセージクラッカーです。
メッセージクラッカーは、WindowProcとメッセージプロシージャを
結びつけます。

HANDLE_MSGマクロの定義については <windowsx.h> ヘッダーを
ご覧下さい。

ただ、手作業でたくさんのメッセージプロシージャの宣言と定義を
記述するのは大変です。
そこで、このアプリを使えば、入力の手間が省けます。


使い方
------

ダイアログに従って下さい。

/////////////////////////////////////////////////////
// 片山博文MZ (katahiromz) [蟻]
// ホームページ http://katahiromz.web.fc2.com/
// 掲示板       http://katahiromz.bbs.fc2.com/
// メール       katayama.hirofumi.mz@gmail.com
/////////////////////////////////////////////////////
