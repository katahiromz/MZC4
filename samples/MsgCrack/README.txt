MsgCrack
========

This is an input helper application of Win32 message crackers.
This application is useful for Win32 API programming.

Supported Platforms
-------------------

Windows XP/2003/Vista/7/8/10


Explanation
-----------

The message crackers connects the Windows message identifiers and
the message procedures by preprocessor's magic.

    #include <windows.h>    // Windows API.
    #include <windowsx.h>   // for HANDLE_MSG macro

    // The message procedure of WM_CREATE
    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
    {
        return TRUE;
    }

    ...

    // Window procedure
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

In this WindowProc function, WM_CREATE message is connected to the
OnCreate function by HANDLE_MSG macro.

Such descriptions of HANDLE_MSG macros are the message crackers.
The message crackers connects WindowProc and message procedures.

For details of HANDLE_MSG macro, see <windowsx.h> header.

However, it is too tough to write many message procedures by hand.
Using this application reduces your troubles.


How To Use
----------

Please follow the dialog.

/////////////////////////////////////////////////////
// Katayama Hirofumi MZ (katahiromz) [ARMYANT]
// Homepage     http://katahiromz.web.fc2.com/
// E-Mail       katayama.hirofumi.mz@gmail.com
/////////////////////////////////////////////////////
