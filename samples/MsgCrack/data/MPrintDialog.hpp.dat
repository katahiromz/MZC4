// MPrintDialog.hpp -- printer dialog wrapper                   -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MPRINTDIALOG_HPP_
#define MZC4_MPRINTDIALOG_HPP_      4       /* Version 4 */

class MPrintDialog;
struct MDevNames;
struct MDevMode;

////////////////////////////////////////////////////////////////////////////

#include "MCommonDialog.hpp"

HDC MZCAPI CreatePrinterDCDx(HGLOBAL hDevNames, HGLOBAL hDevMode);

////////////////////////////////////////////////////////////////////////////
// MDevNames and MDevMode

struct MDevNames : DEVNAMES
{
    LPCTSTR GetDriverName() const;
    LPCTSTR GetDeviceName() const;
    LPCTSTR GetPortName() const;
    BOOL IsDefault() const;
    static HGLOBAL CreateDevNames(LPCTSTR pszDriverName,
        LPCTSTR pszDeviceName, LPCTSTR pszPortName, WORD wDefault = 0);
    static HGLOBAL CloneHandleDx(HGLOBAL hDevNames);
};

struct MDevMode : DEVMODE
{
    LPCTSTR GetDeviceName() const;
    VOID SetDeviceName(LPCTSTR pszDevName);
    BOOL GetOrientation(SHORT& sDMORIENT_) const;
    VOID SetOrientation(SHORT sDMORIENT_);
    BOOL GetPaperSize(SHORT& sDMPAPER_) const;
    VOID SetPaperSize(SHORT sDMPAPER_);
    BOOL GetPaperLength(SHORT& sTenthsOfMillimeter) const;
    VOID SetPaperLength(SHORT sTenthsOfMillimeter);
    BOOL GetPaperWidth(SHORT& sTenthsOfMillimeter) const;
    VOID SetPaperWidth(SHORT sTenthsOfMillimeter);
    BOOL GetScale(SHORT& s) const;
    VOID SetScale(SHORT s);
    BOOL GetCopies(SHORT& sNumber) const;
    VOID SetCopies(SHORT sNumber);
    BOOL GetDefaultSource(SHORT& s) const;
    VOID SetDefaultSource(SHORT s);
    BOOL GetPrintQuality(SHORT& sDMRES_) const;
    VOID SetPrintQuality(SHORT sDMRES_);
    BOOL GetColor(SHORT& sDMCOLOR_) const;
    VOID SetColor(SHORT sDMCOLOR_);
    BOOL GetDuplex(SHORT& sDMDUP_) const;
    VOID SetDuplex(SHORT sDMDUP_);
    BOOL GetYResolution(SHORT& sDotsPerInch) const;
    VOID SetYResolution(SHORT sDotsPerInch);
    BOOL GetTTOption(SHORT& sDMTT_) const;
    VOID SetTTOption(SHORT sDMTT_);
    BOOL GetCollate(SHORT& sDMCOLLATE_) const;
    VOID SetCollate(SHORT sDMCOLLATE_);
    LPCTSTR GetFormName() const;
    VOID SetFormName(LPCTSTR pszFormName);
    BOOL GetLogPixels(WORD& wPixelsPerInch) const;
    VOID SetLogPixels(WORD wPixelsPerInch);
    BOOL GetBitsPerPel(DWORD& dwBitsPerPixel) const;
    VOID SetBitsPerPel(DWORD dwBitsPerPixel);
    BOOL GetPelsWidth(DWORD& dwPixels) const;
    VOID SetPelsWidth(DWORD dwPixels);
    BOOL GetPelsHeight(DWORD& dwPixels) const;
    VOID SetPelsHeight(DWORD dwPixels);
    BOOL GetDisplayFlags(DWORD& dwDM_GRAYSCALEorINTERLACED) const;
    VOID SetDisplayFlags(DWORD dwDM_GRAYSCALEorINTERLACED);
    BOOL GetDisplayFrequency(DWORD& dwHertz) const;
    VOID SetDisplayFrequency(DWORD dwHertz);
#if (WINVER >= 0x0400) 
    BOOL GetICMMethod(DWORD& dwDMICMMETHOD_) const;
    VOID SetICMMethod(DWORD dwDMICMMETHOD_);
    BOOL GetICMIntent(DWORD& dwDMICM_) const;
    VOID SetICMIntent(DWORD dwDMICM_);
    BOOL GetMediaType(DWORD& dwDMMEDIA_) const;
    VOID SetMediaType(DWORD dwDMMEDIA_);
    BOOL GetDitherType(DWORD& dwDMDITHER_) const;
    VOID SetDitherType(DWORD dwDMDITHER_);
#endif  // (WINVER >= 0x0400) 
#if (WINVER >= 0x0500 || _WIN32_WINNT >= 0x0400)
    BOOL GetPanningWidth(DWORD& dw) const;
    VOID SetPanningWidth(DWORD dw);
    BOOL GetPanningHeight(DWORD& dw) const;
    VOID SetPanningHeight(DWORD dw);
#endif  // (WINVER >= 0x0500 || _WIN32_WINNT >= 0x0400)
};

////////////////////////////////////////////////////////////////////////////

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

inline LPCTSTR MDevNames::GetDriverName() const
{
    const TCHAR *psz = reinterpret_cast<const TCHAR *>(this);
    return psz + wDriverOffset;
}

inline LPCTSTR MDevNames::GetDeviceName() const
{
    const TCHAR *psz = reinterpret_cast<const TCHAR *>(this);
    return psz + wDeviceOffset;
}

inline LPCTSTR MDevNames::GetPortName() const
{
    const TCHAR *psz = reinterpret_cast<const TCHAR *>(this);
    return psz + wOutputOffset;
}

inline BOOL MDevNames::IsDefault() const
{
    return (wDefault & DN_DEFAULTPRN);
}

inline /*static*/ HGLOBAL MDevNames::CloneHandleDx(HGLOBAL hDevNames)
{
    MDevNames *pDevNames = reinterpret_cast<MDevNames *>(::GlobalLock(hDevNames));
    return MDevNames::CreateDevNames(pDevNames->GetDriverName(),
        pDevNames->GetDeviceName(), pDevNames->GetPortName());
}

inline /*static*/ HGLOBAL MDevNames::CreateDevNames(
    LPCTSTR pszDriverName, LPCTSTR pszDeviceName, LPCTSTR pszPortName,
    WORD wDefault/* = 0*/)
{
    if (!pszDriverName || !pszDeviceName || !pszPortName)
        return NULL;

    const INT cchDriverName = lstrlen(pszDriverName);
    const INT cchDeviceName = lstrlen(pszDeviceName);
    const INT cchPortName = lstrlen(pszPortName);
    const DWORD cb = 4 * sizeof(WORD) + (
        cchDriverName + 1 + cchDeviceName + 1 + cchPortName + 1) * sizeof(TCHAR);
    HGLOBAL hDevNames = ::GlobalAlloc(GPTR, cb);
    if (hDevNames == NULL)
        return NULL;

    LPDEVNAMES pDevNames = (LPDEVNAMES)::GlobalLock(hDevNames);
    if (pDevNames)
    {
        LPTSTR psz = reinterpret_cast<LPTSTR>(pDevNames);

        pDevNames->wDriverOffset = sizeof(WORD) * 4;
        lstrcpy(psz + pDevNames->wDriverOffset, pszDriverName);

        pDevNames->wDeviceOffset = pDevNames->wDriverOffset + (cchDriverName + 1);
        pDevNames->wDeviceOffset += (cchDriverName + 1) * sizeof(TCHAR);
        lstrcpy(psz + pDevNames->wDeviceOffset, pszDeviceName);

        pDevNames->wOutputOffset = pDevNames->wDeviceOffset + (cchDeviceName + 1);
        pDevNames->wOutputOffset += (cchDeviceName + 1) * sizeof(TCHAR);
        lstrcpy(psz + pDevNames->wOutputOffset, pszPortName);

        pDevNames->wDefault = wDefault;
        ::GlobalUnlock(hDevNames);
    }

    return hDevNames;
}

////////////////////////////////////////////////////////////////////////////

inline LPCTSTR MDevMode::GetDeviceName() const
{
    return LPCTSTR(dmDeviceName[0] ? dmDeviceName : NULL);
}

inline VOID MDevMode::SetDeviceName(LPCTSTR pszDevName)
{
    lstrcpyn(LPTSTR(dmDeviceName), pszDevName, CCHDEVICENAME);
}

inline BOOL MDevMode::GetOrientation(SHORT& sDMORIENT_) const
{
    if (dmFields & DM_ORIENTATION)
    {
        sDMORIENT_ = dmOrientation;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetOrientation(SHORT sDMORIENT_)
{
    assert(sDMORIENT_ == DMORIENT_LANDSCAPE ||
           sDMORIENT_ == DMORIENT_PORTRAIT);
    dmFields |= DM_ORIENTATION;
    dmOrientation = sDMORIENT_;
}

inline BOOL MDevMode::GetPaperSize(SHORT& sDMPAPER_) const
{
    if (dmFields & DM_PAPERSIZE)
    {
        sDMPAPER_ = dmPaperSize;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetPaperSize(SHORT sDMPAPER_)
{
    dmFields |= DM_PAPERSIZE;
    dmPaperSize = sDMPAPER_;
}

inline BOOL MDevMode::GetPaperLength(SHORT& sTenthsOfMillimeter) const
{
    if (dmFields & DM_PAPERLENGTH)
    {
        sTenthsOfMillimeter = dmPaperLength;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetPaperLength(SHORT sTenthsOfMillimeter)
{
    dmFields |= DM_PAPERLENGTH;
    dmPaperLength = sTenthsOfMillimeter;
}

inline BOOL MDevMode::GetPaperWidth(SHORT& sTenthsOfMillimeter) const
{
    if (dmFields & DM_PAPERWIDTH)
    {
        sTenthsOfMillimeter = dmPaperWidth;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetPaperWidth(SHORT sTenthsOfMillimeter)
{
    dmFields |= DM_PAPERWIDTH;
    dmPaperWidth = sTenthsOfMillimeter;
}

inline BOOL MDevMode::GetScale(SHORT& s) const
{
    if (dmFields & DM_SCALE)
    {
        s = dmScale;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetScale(SHORT s)
{
    dmFields |= DM_SCALE;
    dmScale = s;
}

inline BOOL MDevMode::GetCopies(SHORT& sNumber) const
{
    if (dmFields & DM_COPIES)
    {
        sNumber = dmCopies;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetCopies(SHORT sNumber)
{
    dmFields |= DM_COPIES;
    dmCopies = sNumber;
}

inline BOOL MDevMode::GetDefaultSource(SHORT& s) const
{
    if (dmFields & DM_DEFAULTSOURCE)
    {
        s = dmDefaultSource;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetDefaultSource(SHORT s)
{
    dmFields |= DM_DEFAULTSOURCE;
    dmDefaultSource = s;
}

inline BOOL MDevMode::GetPrintQuality(SHORT& sDMRES_) const
{
    if (dmFields & DM_PRINTQUALITY)
    {
        sDMRES_ = dmPrintQuality;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetPrintQuality(SHORT sDMRES_)
{
    dmFields |= DM_PRINTQUALITY;
    dmPrintQuality = sDMRES_;
}

inline BOOL MDevMode::GetColor(SHORT& sDMCOLOR_) const
{
    if (dmFields & DM_COLOR)
    {
        sDMCOLOR_ = dmColor;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetColor(SHORT sDMCOLOR_)
{
    assert(sDMCOLOR_ == DMCOLOR_MONOCHROME || sDMCOLOR_ == DMCOLOR_COLOR);
    dmFields |= DM_COLOR;
    dmColor = sDMCOLOR_;
}

inline BOOL MDevMode::GetDuplex(SHORT& sDMDUP_) const
{
    if (dmFields & DM_DUPLEX)
    {
        sDMDUP_ = dmDuplex;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetDuplex(SHORT sDMDUP_)
{
    assert(sDMDUP_ == DMDUP_SIMPLEX || sDMDUP_ == DMDUP_VERTICAL ||
           sDMDUP_ == DMDUP_HORIZONTAL);
    dmFields |= DM_DUPLEX;
    dmDuplex = sDMDUP_;
}

inline BOOL MDevMode::GetYResolution(SHORT& sDotsPerInch) const
{
    if (dmFields & DM_YRESOLUTION)
    {
        sDotsPerInch = dmYResolution;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetYResolution(SHORT sDotsPerInch)
{
    dmFields |= DM_YRESOLUTION;
    dmYResolution = sDotsPerInch;
}

inline BOOL MDevMode::GetTTOption(SHORT& sDMTT_) const
{
    if (dmFields & DM_TTOPTION)
    {
        sDMTT_ = dmTTOption;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetTTOption(SHORT sDMTT_)
{
    dmFields |= DM_TTOPTION;
    dmTTOption = sDMTT_;
}

inline BOOL MDevMode::GetCollate(SHORT& sDMCOLLATE_) const
{
    if (dmFields & DM_COLLATE)
    {
        sDMCOLLATE_ = dmCollate;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetCollate(SHORT sDMCOLLATE_)
{
    dmFields |= DM_COLLATE;
    dmCollate = sDMCOLLATE_;
}

inline LPCTSTR MDevMode::GetFormName() const
{
    return LPCTSTR(dmFormName[0] ? dmFormName : NULL);
}

inline VOID MDevMode::SetFormName(LPCTSTR pszFormName)
{
    lstrcpyn(LPTSTR(dmFormName), pszFormName, CCHFORMNAME);
}

inline BOOL MDevMode::GetLogPixels(WORD& wPixelsPerInch) const
{
    if (dmFields & DM_LOGPIXELS)
    {
        wPixelsPerInch = dmLogPixels;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetLogPixels(WORD wPixelsPerInch)
{
    dmFields |= DM_LOGPIXELS;
    dmLogPixels = wPixelsPerInch;
}

inline BOOL MDevMode::GetBitsPerPel(DWORD& dwBitsPerPixel) const
{
    if (dmFields & DM_BITSPERPEL)
    {
        dwBitsPerPixel = dmBitsPerPel;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetBitsPerPel(DWORD dwBitsPerPixel)
{
    dmFields |= DM_BITSPERPEL;
    dmBitsPerPel = dwBitsPerPixel;
}

inline BOOL MDevMode::GetPelsWidth(DWORD& dwPixels) const
{
    if (dmFields & DM_PELSWIDTH)
    {
        dwPixels = dmPelsWidth;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetPelsWidth(DWORD dwPixels)
{
    dmFields |= DM_PELSWIDTH;
    dmPelsWidth = dwPixels;
}

inline BOOL MDevMode::GetPelsHeight(DWORD& dwPixels) const
{
    if (dmFields & DM_PELSHEIGHT)
    {
        dwPixels = dmPelsHeight;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetPelsHeight(DWORD dwPixels)
{
    dmFields |= DM_PELSHEIGHT;
    dmPelsHeight = dwPixels;
}

inline BOOL MDevMode::GetDisplayFlags(DWORD& dwDM_GRAYSCALEorINTERLACED) const
{
    if (dmFields & DM_DISPLAYFLAGS)
    {
        dwDM_GRAYSCALEorINTERLACED = dmDisplayFlags;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetDisplayFlags(DWORD dwDM_GRAYSCALEorINTERLACED)
{
#ifndef DM_GRAYSCALE
    #define DM_GRAYSCALE    0x00000001
#endif
#ifndef DM_INTERLACED
    #define DM_INTERLACED   0x00000002
#endif
    assert(dwDM_GRAYSCALEorINTERLACED == DM_GRAYSCALE ||
           dwDM_GRAYSCALEorINTERLACED == DM_INTERLACED);
    dmFields |= DM_DISPLAYFLAGS;
    dmDisplayFlags = dwDM_GRAYSCALEorINTERLACED;
}

inline BOOL MDevMode::GetDisplayFrequency(DWORD& dwHertz) const
{
    if (dmFields & DM_DISPLAYFREQUENCY)
    {
        dwHertz = dmDisplayFrequency;
        return TRUE;
    }
    return FALSE;
}

inline VOID MDevMode::SetDisplayFrequency(DWORD dwHertz)
{
    dmFields |= DM_DISPLAYFREQUENCY;
    dmDisplayFrequency = dwHertz;
}

#if (WINVER >= 0x0400) 
    inline BOOL MDevMode::GetICMMethod(DWORD& dwDMICMMETHOD_) const
    {
        if (dmFields & DM_ICMMETHOD)
        {
            dwDMICMMETHOD_ = dmICMMethod;
            return TRUE;
        }
        return FALSE;
    }

    inline VOID MDevMode::SetICMMethod(DWORD dwDMICMMETHOD_)
    {
        dmFields |= DM_ICMMETHOD;
        dmICMMethod = dwDMICMMETHOD_;
    }

    inline BOOL MDevMode::GetICMIntent(DWORD& dwDMICM_) const
    {
        if (dmFields & DM_ICMINTENT)
        {
            dwDMICM_ = dmICMIntent;
            return TRUE;
        }
        return FALSE;
    }

    inline VOID MDevMode::SetICMIntent(DWORD dwDMICM_)
    {
        dmFields |= DM_ICMINTENT;
        dmICMIntent = dwDMICM_;
    }

    inline BOOL MDevMode::GetMediaType(DWORD& dwDMMEDIA_) const
    {
        if (dmFields & DM_MEDIATYPE)
        {
            dwDMMEDIA_ = dmMediaType;
            return TRUE;
        }
        return FALSE;
    }

    inline VOID MDevMode::SetMediaType(DWORD dwDMMEDIA_)
    {
        dmFields |= DM_MEDIATYPE;
        dmMediaType = dwDMMEDIA_;
    }

    inline BOOL MDevMode::GetDitherType(DWORD& dwDMDITHER_) const
    {
        if (dmFields & DM_DITHERTYPE)
        {
            dwDMDITHER_ = dmDitherType;
            return TRUE;
        }
        return FALSE;
    }

    inline VOID MDevMode::SetDitherType(DWORD dwDMDITHER_)
    {
        dmFields |= DM_DITHERTYPE;
        dmDitherType = dwDMDITHER_;
    }
#endif  // (WINVER >= 0x0400) 

#if (WINVER >= 0x0500 || _WIN32_WINNT >= 0x0400)
    inline BOOL MDevMode::GetPanningWidth(DWORD& dw) const
    {
        if (dmFields & DM_PANNINGWIDTH)
        {
            dw = dmPanningWidth;
            return TRUE;
        }
        return FALSE;
    }

    inline VOID MDevMode::SetPanningWidth(DWORD dw)
    {
        dmFields |= DM_PANNINGWIDTH;
        dmPanningWidth = dw;
    }

    inline BOOL MDevMode::GetPanningHeight(DWORD& dw) const
    {
        if (dmFields & DM_PANNINGHEIGHT)
        {
            dw = dmPanningHeight;
            return TRUE;
        }
        return FALSE;
    }

    inline VOID MDevMode::SetPanningHeight(DWORD dw)
    {
        dmFields |= DM_PANNINGHEIGHT;
        dmPanningHeight = dw;
    }
#endif  // (WINVER >= 0x0500 || _WIN32_WINNT >= 0x0400)

////////////////////////////////////////////////////////////////////////////

inline MPrintDialog::MPrintDialog(
    HWND hwndOwner,
    DWORD dwPD_/* = PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | \
                    PD_HIDEPRINTTOFILE | PD_NOSELECTION*/,
    BOOL bPrintSetup/* = FALSE*/) : MCommonDialog(hwndOwner)
{
    m_bModal = TRUE;
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

#endif  // ndef MZC4_MPRINTDIALOG_HPP_
