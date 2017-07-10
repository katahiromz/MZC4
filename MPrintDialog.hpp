// MPrintDialog.hpp -- printer dialog wrapper                   -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPRINTDIALOG_HPP_
#define MZC4_MPRINTDIALOG_HPP_      4       /* Version 4 */

class MPrintDialog;

////////////////////////////////////////////////////////////////////////////

#include "MCommonDialog.hpp"
#include "MDevNames.hpp"
#include "MDevMode.hpp"

HDC MZCAPI CreatePrinterDCDx(HGLOBAL hDevNames, HGLOBAL hDevMode);

class MPrintDialog : public MCommonDialog
{
public:
    PRINTDLG m_pd;

    /* before main */
    MPrintDialog(HWND hwndOwner,
                 DWORD dwPD_ = PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS |
                               PD_HIDEPRINTTOFILE | PD_NOSELECTION,
                 BOOL bPrintSetup = FALSE);
    virtual ~MPrintDialog();

    /* main */
    BOOL PrintDlg();
    BOOL GetDefaults();

    /* after main */
    HDC CreatePrinterDC();
    HDC GetPrinterDC() const;
    HGLOBAL DetachDevNames();
    HGLOBAL DetachDevMode();

    MString GetDriverName() const;
    MString GetDeviceName() const;
    MString GetPortName() const;

    INT GetCopies() const;
    INT GetFromPage() const;
    INT GetToPage() const;
    BOOL PrintAll() const;
    BOOL PrintCollate() const;
    BOOL PrintRange() const;
    BOOL PrintSelection() const;
};

////////////////////////////////////////////////////////////////////////////

inline MPrintDialog::MPrintDialog(
    HWND hwndOwner,
    DWORD dwPD_/* = PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | \
                    PD_HIDEPRINTTOFILE | PD_NOSELECTION*/,
    BOOL bPrintSetup/* = FALSE*/)
{
    ZeroMemory(&m_pd, sizeof(m_pd));
    m_pd.lStructSize = sizeof(m_pd);
    m_pd.hwndOwner = hwndOwner;
    m_pd.Flags = dwPD_ | PD_RETURNDC;
    if (bPrintSetup)
        m_pd.Flags |= PD_PRINTSETUP;
}

inline /*virtual*/ MPrintDialog::~MPrintDialog()
{
    GlobalFree(m_pd.hDevMode);
    GlobalFree(m_pd.hDevNames);
    DeleteDC(m_pd.hDC);
}

inline BOOL MPrintDialog::PrintDlg()
{
    return ::PrintDlg(&m_pd);
}

inline INT MPrintDialog::GetFromPage() const
{
    return m_pd.nFromPage;
}

inline INT MPrintDialog::GetToPage() const
{
    return m_pd.nToPage;
}

inline HDC MPrintDialog::CreatePrinterDC()
{
    ::DeleteDC(m_pd.hDC);
    m_pd.hDC = CreatePrinterDCDx(m_pd.hDevNames, m_pd.hDevMode);
    return m_pd.hDC;
}

inline HDC MPrintDialog::GetPrinterDC() const
{
    assert(m_pd.Flags & PD_RETURNDC);
    return m_pd.hDC;
}

inline HGLOBAL MPrintDialog::DetachDevNames()
{
    HGLOBAL hDevNames = m_pd.hDevNames;
    m_pd.hDevNames = NULL;
    return hDevNames;
}

inline HGLOBAL MPrintDialog::DetachDevMode()
{
    HGLOBAL hDevMode = m_pd.hDevMode;
    m_pd.hDevMode = NULL;
    return hDevMode;
}

inline BOOL MPrintDialog::GetDefaults()
{
    m_pd.Flags |= PD_RETURNDEFAULT;
    return ::PrintDlg(&m_pd);
}

inline MString MPrintDialog::GetDriverName() const
{
    MString str;
    if (m_pd.hDevNames)
    {
        MDevNames *pDevNames = (MDevNames *)GlobalLock(m_pd.hDevNames);
        str = pDevNames->GetDriverName();
        GlobalUnlock(m_pd.hDevNames);
    }
    return str;
}

inline MString MPrintDialog::GetDeviceName() const
{
    MString str;
    if (m_pd.hDevNames)
    {
        MDevNames *pDevNames = (MDevNames *)GlobalLock(m_pd.hDevNames);
        str = pDevNames->GetDeviceName();
        GlobalUnlock(m_pd.hDevNames);
    }
    return str;
}

inline MString MPrintDialog::GetPortName() const
{
    MString str;
    if (m_pd.hDevNames)
    {
        MDevNames *pDevNames = (MDevNames *)GlobalLock(m_pd.hDevNames);
        str = pDevNames->GetPortName();
        GlobalUnlock(m_pd.hDevNames);
    }
    return str;
}

inline INT MPrintDialog::GetCopies() const
{
    return m_pd.nCopies;
}

inline BOOL MPrintDialog::PrintAll() const
{
    return (m_pd.Flags & PD_ALLPAGES) != 0;
}

inline BOOL MPrintDialog::PrintCollate() const
{
    return (m_pd.Flags & PD_COLLATE) != 0;
}

inline BOOL MPrintDialog::PrintRange() const
{
    return (m_pd.Flags & PD_PAGENUMS) != 0;
}

inline BOOL MPrintDialog::PrintSelection() const
{
    return (m_pd.Flags & PD_SELECTION) != 0;
}

////////////////////////////////////////////////////////////////////////////

inline HDC MZCAPI CreatePrinterDCDx(HGLOBAL hDevNames, HGLOBAL hDevMode)
{
    HDC hPrinterDC = NULL;
    MDevNames *pDevNames = (MDevNames *)GlobalLock(hDevNames);
    if (pDevNames)
    {
        MDevMode *pDevMode = (MDevMode *)GlobalLock(hDevMode);
        hPrinterDC = ::CreateDC(pDevNames->GetDriverName(),
                                pDevNames->GetDeviceName(),
                                pDevNames->GetPortName(),
                                pDevMode);
        GlobalUnlock(hDevMode);
    }
    GlobalUnlock(hDevNames);
    return hPrinterDC;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MPRINTDIALOG_HPP_
