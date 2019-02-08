// MPrintHelper.hpp
// Copyright (C) 2019 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
// This file is public domain software.

#ifndef MPRINT_HELPER_HPP_
#define MPRINT_HELPER_HPP_      3   // Version 3

#include <windows.h>
#include <commdlg.h>

#ifndef PRINT_HELPER_MIN_MARGIN
    #define PRINT_HELPER_MIN_MARGIN 800     // default margin: 8mm
#endif

//////////////////////////////////////////////////////////////////////////////

class MPrintHelper
{
public:
    MPrintHelper();
    virtual ~MPrintHelper();

    BOOL InitPageSetup(HWND hwnd);

          RECT& Margins();
    const RECT& Margins() const;

          RECT& MinMargins();
    const RECT& MinMargins() const;

    BOOL DoPrint(HWND hwnd, LPCWSTR pszDocName);
    BOOL DoPageSetupDlg(HWND hwnd);
    HDC CreatePrinterDC();

          DWORD& Flags();
    const DWORD& Flags() const;

          DWORD& PageFlags();
    const DWORD& PageFlags() const;

    HGLOBAL& DevMode();
    HGLOBAL& DevNames();

    LONG Inch1000FromMM100(LONG mm100) const;
    LONG MM100FromInch1000(LONG inch1000) const;

    BOOL AllPages() const;
    BOOL PageNums() const;
    WORD FromPage() const;
    WORD ToPage() const;
    BOOL Selection() const;

    UINT GetLastPageCount() const;

protected:
    PRINTDLGW m_pd;
    PAGESETUPDLGW m_psd;
    UINT m_nLastPageCount;

    virtual BOOL DoPrintDocument(HWND hwnd, HDC hDC, LPCWSTR pszDocName);
    virtual BOOL DoPrintPages(HWND hwnd, HDC hDC, LPCWSTR pszDocName);
};

//////////////////////////////////////////////////////////////////////////////

inline MPrintHelper::MPrintHelper()
{
    ZeroMemory(&m_pd, sizeof(m_pd));
    ZeroMemory(&m_psd, sizeof(m_psd));
    m_nLastPageCount = 0;
}

inline UINT MPrintHelper::GetLastPageCount() const
{
    return m_nLastPageCount;
}

inline HGLOBAL& MPrintHelper::DevMode()
{
    return m_psd.hDevMode;
}

inline HGLOBAL& MPrintHelper::DevNames()
{
    return m_psd.hDevNames;
}

inline MPrintHelper::~MPrintHelper()
{
    ::GlobalFree(DevMode());
    ::GlobalFree(DevNames());
    DevMode() = NULL;
    DevNames() = NULL;
}

inline BOOL MPrintHelper::InitPageSetup(HWND hwnd)
{
    ZeroMemory(&m_psd, sizeof(m_psd));
    m_psd.lStructSize = sizeof(m_psd);
    m_psd.hwndOwner = hwnd;
    m_psd.Flags = PSD_MARGINS | PSD_MINMARGINS |
                  PSD_NOWARNING | PSD_RETURNDEFAULT;
    PageSetupDlgW(&m_psd);

    RECT& mrg = m_psd.rtMargin;
    RECT& minm = m_psd.rtMinMargin;

    if (mrg.left < PRINT_HELPER_MIN_MARGIN || minm.left < PRINT_HELPER_MIN_MARGIN)
        minm.left = mrg.left = PRINT_HELPER_MIN_MARGIN;
    if (mrg.top < PRINT_HELPER_MIN_MARGIN || minm.top < PRINT_HELPER_MIN_MARGIN)
        minm.top = mrg.top = PRINT_HELPER_MIN_MARGIN;
    if (mrg.right < PRINT_HELPER_MIN_MARGIN || minm.right < PRINT_HELPER_MIN_MARGIN)
        minm.right = mrg.right = PRINT_HELPER_MIN_MARGIN;
    if (mrg.bottom < PRINT_HELPER_MIN_MARGIN || minm.bottom < PRINT_HELPER_MIN_MARGIN)
        minm.bottom = mrg.bottom = PRINT_HELPER_MIN_MARGIN;

    if (PageFlags() & PSD_INTHOUSANDTHSOFINCHES)
    {
        mrg.left = Inch1000FromMM100(mrg.left);
        mrg.top = Inch1000FromMM100(mrg.top);
        mrg.right = Inch1000FromMM100(mrg.right);
        mrg.bottom = Inch1000FromMM100(mrg.bottom);

        minm.left = Inch1000FromMM100(minm.left);
        minm.top = Inch1000FromMM100(minm.top);
        minm.right = Inch1000FromMM100(minm.right);
        minm.bottom = Inch1000FromMM100(minm.bottom);
    }
}

inline RECT& MPrintHelper::Margins()
{
    return m_psd.rtMargin;
}

inline const RECT& MPrintHelper::Margins() const
{
    return m_psd.rtMargin;
}

inline RECT& MPrintHelper::MinMargins()
{
    return m_psd.rtMinMargin;
}

inline const RECT& MPrintHelper::MinMargins() const
{
    return m_psd.rtMinMargin;
}

inline BOOL MPrintHelper::DoPrintDocument(HWND hwnd, HDC hDC, LPCWSTR pszDocName)
{
    m_nLastPageCount = 0;

    DOCINFOW di;
    if (pszDocName)
    {
        ZeroMemory(&di, sizeof(di));
        di.cbSize = sizeof(di);
        di.lpszDocName = pszDocName;
    }

    for (int i = 0; i < m_pd.nCopies; i++)
    {
        if (pszDocName)
        {
            if (::StartDocW(hDC, &di) <= 0)
                return FALSE;
        }

        if (!DoPrintPages(hwnd, hDC, pszDocName))
        {
            if (pszDocName)
                ::AbortDoc(hDC);
            return FALSE;
        }

        if (pszDocName)
        {
            ::EndDoc(hDC);
        }
    }

    return TRUE;
}

inline BOOL MPrintHelper::DoPageSetupDlg(HWND hwnd)
{
    m_psd.lStructSize = sizeof(m_psd);
    m_psd.hwndOwner = hwnd;
    m_psd.Flags = PSD_MARGINS | PSD_MINMARGINS;
    return PageSetupDlgW(&m_psd);
}

inline HDC MPrintHelper::CreatePrinterDC()
{
    HDC hPrinterDC = NULL;
    if (DEVNAMES *pDevNames = (DEVNAMES *)::GlobalLock(m_psd.hDevNames))
    {
        if (DEVMODE *pDevMode = (DEVMODE *)::GlobalLock(m_psd.hDevMode))
        {
            hPrinterDC = ::CreateDC(
                (LPCTSTR)pDevNames + pDevNames->wDriverOffset,
                (LPCTSTR)pDevNames + pDevNames->wDeviceOffset,
                (LPCTSTR)pDevNames + pDevNames->wOutputOffset,
                pDevMode);
            ::GlobalUnlock(m_psd.hDevMode);
        }
        ::GlobalUnlock(m_psd.hDevNames);
    }
    return hPrinterDC;
}

inline BOOL MPrintHelper::DoPrint(HWND hwnd, LPCWSTR pszDocName)
{
    m_nLastPageCount = 0;

    BOOL bPrinted = FALSE;
    if (pszDocName)
    {
        ZeroMemory(&m_pd, sizeof(m_pd));
        m_pd.lStructSize = sizeof(m_pd);
        m_pd.hwndOwner = hwnd;
        m_pd.Flags = PD_ALLPAGES | PD_HIDEPRINTTOFILE | PD_COLLATE |
                     PD_NOPAGENUMS | PD_NOSELECTION | PD_RETURNDC;
        m_pd.nCopies = 1;
        m_pd.hDevMode = DevMode();
        m_pd.hDevNames = DevNames();

        if (!::PrintDlgW(&m_pd))
            return FALSE;

        bPrinted = DoPrintDocument(hwnd, m_pd.hDC, pszDocName);
        DeleteDC(m_pd.hDC);

        DevMode() = m_pd.hDevMode;
        DevNames() = m_pd.hDevNames;
        m_pd.hDevMode = NULL;
        m_pd.hDevNames = NULL;
    }
    else
    {
        if (HDC hDC = CreatePrinterDC())
        {
            bPrinted = DoPrintPages(hwnd, hDC, NULL);
            ::DeleteDC(hDC);
        }
    }

    return bPrinted;
}

inline DWORD& MPrintHelper::Flags()
{
    return m_pd.Flags;
}

inline const DWORD& MPrintHelper::Flags() const
{
    return m_pd.Flags;
}

inline DWORD& MPrintHelper::PageFlags()
{
    return m_psd.Flags;
}

inline const DWORD& MPrintHelper::PageFlags() const
{
    return m_psd.Flags;
}

inline LONG MPrintHelper::Inch1000FromMM100(LONG mm100) const
{
    return (LONG)(mm100 * (10 / 25.4));
}

inline LONG MPrintHelper::MM100FromInch1000(LONG inch1000) const
{
    return (LONG)(inch1000 * (25.4 / 10));
}

inline BOOL MPrintHelper::AllPages() const
{
    return !!(Flags() & PD_ALLPAGES);
}

inline BOOL MPrintHelper::PageNums() const
{
    return !!(Flags() & PD_PAGENUMS);
}

inline WORD MPrintHelper::FromPage() const
{
    return m_pd.nFromPage;
}

inline WORD MPrintHelper::ToPage() const
{
    return m_pd.nToPage;
}

inline BOOL MPrintHelper::Selection() const
{
    return !!(Flags() & PD_SELECTION);
}

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef MPRINT_HELPER_HPP_
