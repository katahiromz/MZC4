// MWebBrowser.hpp -- MZC4 web browser control                  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MWEBBROWSER_HPP_
#define MZC4_MWEBBROWSER_HPP_       3       /* Version 3 */

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")

////////////////////////////////////////////////////////////////////////////

#include "MActXCtrl.hpp"

class MWebBrowser
{
public:
    MWebBrowser();
    virtual ~MWebBrowser();

    BOOL Create(HWND hwndParent, LPCTSTR pszURL = TEXT("about:blank"));
    void Destroy();

    virtual void Navigate(LPCTSTR pszURL);

    HWND GetParent() const;
    void SetParent(HWND hwndParent);
    void MoveWindow(INT x, INT y, INT cx, INT cy);
    void MoveWindow(const MRect& rc);

    MActXCtrl*      GetActXCtrl() const;
    IWebBrowser2*   GetWebBrowser2() const;
    BOOL TranslateAccelerator(LPMSG pmsg);

protected:
    IWebBrowser2*   m_pWebBrowser2;
    MActXCtrl*      m_pActXCtrl;
};

////////////////////////////////////////////////////////////////////////////

inline void MWebBrowser::Destroy()
{
    GetActXCtrl()->Destroy();
}

inline MActXCtrl* MWebBrowser::GetActXCtrl() const
{
    return m_pActXCtrl;
}

inline IWebBrowser2* MWebBrowser::GetWebBrowser2() const
{
    return m_pWebBrowser2;
}

inline void MWebBrowser::MoveWindow(INT x, INT y, INT cx, INT cy)
{
    GetActXCtrl()->SetPos(x, y, cx, cy);
}

inline void MWebBrowser::MoveWindow(const MRect& rc)
{
    GetActXCtrl()->SetPos(rc);
}

inline HWND MWebBrowser::GetParent() const
{
    return GetActXCtrl()->GetParent();
}

inline void MWebBrowser::SetParent(HWND hwndParent)
{
    GetActXCtrl()->SetParent(hwndParent);
}

inline BOOL MWebBrowser::TranslateAccelerator(LPMSG pmsg)
{
    return GetActXCtrl()->TranslateAccelerator(pmsg);
}

inline MWebBrowser::MWebBrowser() :
    m_pWebBrowser2(NULL), m_pActXCtrl(new MActXCtrl)
{
    ::OleInitialize(NULL);
}

inline /*virtual*/ MWebBrowser::~MWebBrowser()
{
    if (m_pWebBrowser2)
    {
        m_pWebBrowser2->Stop();
        m_pWebBrowser2->Release();
    }
    if (m_pActXCtrl)
    {
        m_pActXCtrl->Release();
    }
    ::OleUninitialize();
}

inline BOOL
MWebBrowser::Create(HWND hwndParent, LPCTSTR pszURL/* = TEXT("about:blank")*/)
{
    if (!GetActXCtrl()->Create(CLSID_WebBrowser))
        return FALSE;

    GetActXCtrl()->SetParent(hwndParent);
    GetActXCtrl()->Show(TRUE);

    IUnknown* pUnk = GetActXCtrl()->GetUnknown();
    if (pUnk)
    {
        HRESULT hr = pUnk->QueryInterface(
            IID_IWebBrowser2, reinterpret_cast<void**>(&m_pWebBrowser2));
        pUnk->Release();

        if (SUCCEEDED(hr))
        {
            if (pszURL)
            {
                Navigate(pszURL);
            }
            return TRUE;
        }
    }
    return FALSE;
}

inline /*virtual*/ void MWebBrowser::Navigate(LPCTSTR pszURL)
{
    VARIANT vURL;
    vURL.vt = VT_BSTR;
    vURL.bstrVal = ::SysAllocString(MTextToWide(CP_ACP, pszURL));

    VARIANT ve1, ve2, ve3, ve4;
    ve1.vt = VT_EMPTY;
    ve2.vt = VT_EMPTY;
    ve3.vt = VT_EMPTY;
    ve4.vt = VT_EMPTY;

    GetWebBrowser2()->Navigate2(&vURL, &ve1, &ve2, &ve3, &ve4);

    // Also frees memory allocated by SysAllocString
    VariantClear(&vURL);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MWEBBROWSER_HPP_
