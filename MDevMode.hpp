// MDevMode.hpp -- Win32API DEVMODE wrapper                     -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MDEVMODE_HPP_
#define MZC4_MDEVMODE_HPP_      2   /* Version 2 */

struct MDevMode;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

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

#endif  // ndef MZC4_MDEVMODE_HPP_
