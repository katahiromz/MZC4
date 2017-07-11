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

    MCommonDialog(HWND hwndOwner) : MDialogBase(hwndOwner)
    {
    }

    static DWORD GetError()
    {
        return ::CommDlgExtendedError();
    }

    static LPCTSTR ErrorToText(DWORD dwError);
};

////////////////////////////////////////////////////////////////////////////

inline /*static*/ LPCTSTR MCommonDialog::ErrorToText(DWORD dwError)
{
    switch (dwError)
    {
        case CDERR_DIALOGFAILURE: return TEXT("CDERR_DIALOGFAILURE");
        case CDERR_GENERALCODES: return TEXT("CDERR_GENERALCODES");
        case CDERR_STRUCTSIZE: return TEXT("CDERR_STRUCTSIZE");
        case CDERR_INITIALIZATION: return TEXT("CDERR_INITIALIZATION");
        case CDERR_NOTEMPLATE: return TEXT("CDERR_NOTEMPLATE");
        case CDERR_NOHINSTANCE: return TEXT("CDERR_NOHINSTANCE");
        case CDERR_LOADSTRFAILURE: return TEXT("CDERR_LOADSTRFAILURE");
        case CDERR_FINDRESFAILURE: return TEXT("CDERR_FINDRESFAILURE");
        case CDERR_LOADRESFAILURE: return TEXT("CDERR_LOADRESFAILURE");
        case CDERR_LOCKRESFAILURE: return TEXT("CDERR_LOCKRESFAILURE");
        case CDERR_MEMALLOCFAILURE: return TEXT("CDERR_MEMALLOCFAILURE");
        case CDERR_MEMLOCKFAILURE: return TEXT("CDERR_MEMLOCKFAILURE");
        case CDERR_NOHOOK: return TEXT("CDERR_NOHOOK");
        case CDERR_REGISTERMSGFAIL: return TEXT("CDERR_REGISTERMSGFAIL");
        case PDERR_PRINTERCODES: return TEXT("PDERR_PRINTERCODES");
        case PDERR_SETUPFAILURE: return TEXT("PDERR_SETUPFAILURE");
        case PDERR_PARSEFAILURE: return TEXT("PDERR_PARSEFAILURE");
        case PDERR_RETDEFFAILURE: return TEXT("PDERR_RETDEFFAILURE");
        case PDERR_LOADDRVFAILURE: return TEXT("PDERR_LOADDRVFAILURE");
        case PDERR_GETDEVMODEFAIL: return TEXT("PDERR_GETDEVMODEFAIL");
        case PDERR_INITFAILURE: return TEXT("PDERR_INITFAILURE");
        case PDERR_NODEVICES: return TEXT("PDERR_NODEVICES");
        case PDERR_NODEFAULTPRN: return TEXT("PDERR_NODEFAULTPRN");
        case PDERR_DNDMMISMATCH: return TEXT("PDERR_DNDMMISMATCH");
        case PDERR_CREATEICFAILURE: return TEXT("PDERR_CREATEICFAILURE");
        case PDERR_PRINTERNOTFOUND: return TEXT("PDERR_PRINTERNOTFOUND");
        case PDERR_DEFAULTDIFFERENT: return TEXT("PDERR_DEFAULTDIFFERENT");
        case CFERR_CHOOSEFONTCODES: return TEXT("CFERR_CHOOSEFONTCODES");
        case CFERR_NOFONTS: return TEXT("CFERR_NOFONTS");
        case CFERR_MAXLESSTHANMIN: return TEXT("CFERR_MAXLESSTHANMIN");
        case FNERR_FILENAMECODES: return TEXT("FNERR_FILENAMECODES");
        case FNERR_SUBCLASSFAILURE: return TEXT("FNERR_SUBCLASSFAILURE");
        case FNERR_INVALIDFILENAME: return TEXT("FNERR_INVALIDFILENAME");
        case FNERR_BUFFERTOOSMALL: return TEXT("FNERR_BUFFERTOOSMALL");
        case FRERR_FINDREPLACECODES: return TEXT("FRERR_FINDREPLACECODES");
        case FRERR_BUFFERLENGTHZERO: return TEXT("FRERR_BUFFERLENGTHZERO");
        case CCERR_CHOOSECOLORCODES: return TEXT("CCERR_CHOOSECOLORCODES");
        default:
            break;
    }
    return TEXT("(Unknown)");
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MCOMMONDIALOG_HPP_
