// MCommonDialog.hpp -- MZC4 common dialog base                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MCOMMONDIALOG_HPP_
#define MZC4_MCOMMONDIALOG_HPP_     2       /* Version 2 */

class MCommonDialog;

////////////////////////////////////////////////////////////////////////////

#include "MDialogBase.hpp"

#ifndef _INC_COMMDLG
    #include <commdlg.h>
#endif

#pragma comment(lib, "comdlg32.lib")

////////////////////////////////////////////////////////////////////////////

class MCommonDialog : public MDialogBase
{
public:
    MCommonDialog()
    {
    }

    MCommonDialog(HWND hwndParent) : MDialogBase(hwndParent)
    {
    }

    static DWORD GetExtendedError()
    {
        return ::CommDlgExtendedError();
    }
};

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCOMMONDIALOG_HPP_
