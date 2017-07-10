// MAccel.hpp -- Win32API ActX control wrapper                  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MACTXCTRL_HPP_
#define MZC4_MACTXCTRL_HPP_     2       /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#ifndef _INC_COMMCTRL
    #include <commctrl.h>   // for SB_SETTEXT
#endif

#include <cassert>          // assert

#include <exdisp.h>
#include <ocidl.h>

////////////////////////////////////////////////////////////////////////////

#include "MPointSizeRect.hpp"
#include "MTextToText.hpp"

class MActXCtrl :
    public IOleClientSite, public IOleInPlaceSite, public IOleInPlaceFrame,
    public IOleControlSite, public IDispatch
{
public:
    MActXCtrl();
    virtual ~MActXCtrl();

    BOOL Create(BSTR bstrClsid);
    BOOL Create(CLSID clsid);

    void UIActivate();
    void InPlaceActivate();
    void Show(BOOL fVisible = TRUE);
    void Destroy();

    HWND GetParent() const;
    void SetParent(HWND hwndParent);

    HWND GetStatusWindow() const;
    void SetStatusWindow(HWND hwndStatus);

    BOOL TranslateAccelerator(LPMSG pMsg);
    void SetPos(const MRect& rc);
    void SetPos(INT x, INT y, INT width, INT height);

    IDispatch*   GetDispatch();
    IUnknown*    GetUnknown();

    void DoVerb(LONG iVerb);

    // IUnknown Methods
    STDMETHODIMP QueryInterface(REFIID riid, void** ppvObject);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IOleClientSite Methods
    STDMETHODIMP SaveObject();
    STDMETHODIMP GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER* ppMk);
    STDMETHODIMP GetContainer(LPOLECONTAINER* ppContainer);
    STDMETHODIMP ShowObject();
    STDMETHODIMP OnShowWindow(BOOL fShow);
    STDMETHODIMP RequestNewObjectLayout();

    // IOleWindow Methods
    STDMETHODIMP GetWindow(HWND* phwnd);
    STDMETHODIMP ContextSensitiveHelp(BOOL fEnterMode);

    // IOleInPlaceSite Methods
    STDMETHODIMP CanInPlaceActivate();
    STDMETHODIMP OnInPlaceActivate();
    STDMETHODIMP OnUIActivate();
    STDMETHODIMP GetWindowContext(
        IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppDoc,
        LPRECT prcPosRect, LPRECT prcClipRect,
        LPOLEINPLACEFRAMEINFO lpFrameInfo);
    STDMETHODIMP Scroll(SIZE scrollExtent);
    STDMETHODIMP OnUIDeactivate(BOOL fUndoable);
    STDMETHODIMP OnInPlaceDeactivate();
    STDMETHODIMP DiscardUndoState();
    STDMETHODIMP DeactivateAndUndo();
    STDMETHODIMP OnPosRectChange(LPCRECT prcPosRect);

    // IOleInPlaceUIWindow Methods
    STDMETHODIMP GetBorder(LPRECT prcBorder);
    STDMETHODIMP RequestBorderSpace(LPCBORDERWIDTHS lpborderwidths);
    STDMETHODIMP SetBorderSpace(LPCBORDERWIDTHS lpborderwidths);
    STDMETHODIMP SetActiveObject(
        IOleInPlaceActiveObject* pActiveObject, LPCOLESTR lpszObjName);

    // IOleInPlaceFrame Methods
    STDMETHODIMP InsertMenus(
        HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths);
    STDMETHODIMP SetMenu(
        HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject);
    STDMETHODIMP RemoveMenus(HMENU hmenuShared);
    STDMETHODIMP SetStatusText(LPCOLESTR pszStatusText);
    STDMETHODIMP EnableModeless(BOOL fEnable);
    STDMETHODIMP TranslateAccelerator(LPMSG lpmsg, WORD wID);

    // IOleControlSite Methods
    STDMETHODIMP OnControlInfoChanged();
    STDMETHODIMP LockInPlaceActive(BOOL fLock);
    STDMETHODIMP GetExtendedControl(IDispatch** ppDisp);
    STDMETHODIMP TransformCoords(
        POINTL* pptlHimetric, POINTF* pptfContainer, DWORD dwFlags);
    STDMETHODIMP TranslateAccelerator(LPMSG pMsg, DWORD grfModifiers);
    STDMETHODIMP OnFocus(BOOL fGotFocus);
    STDMETHODIMP ShowPropertyFrame();

    // IDispatch Methods
    STDMETHODIMP GetIDsOfNames(REFIID riid, OLECHAR** rgszNames,
        UINT cNames, LCID lcid, DISPID* rgdispid);
    STDMETHODIMP GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo);
    STDMETHODIMP GetTypeInfoCount(UINT* pctinfo);
    STDMETHODIMP Invoke(
        DISPID dispid, REFIID riid, LCID lcid, WORD wFlags,
        DISPPARAMS* pdispparams, VARIANT* pvarResult,
        EXCEPINFO* pexecinfo, UINT* puArgErr);

protected:
     ULONG       m_nRefs;
     HWND        m_hwndParent;
     HWND        m_hwndStatus;
     IUnknown*   m_pUnknown;
     MRect       m_rcCtrl;
};

////////////////////////////////////////////////////////////////////////////

inline MActXCtrl::MActXCtrl() :
    m_nRefs(1), m_hwndParent(NULL), m_pUnknown(NULL)
{
}

inline BOOL MActXCtrl::Create(BSTR bstrClsid)
{
    CLSID clsid;
    ::CLSIDFromString(bstrClsid, &clsid);
    return Create(clsid);
}

inline HWND MActXCtrl::GetParent() const
{
    return m_hwndParent;
}

inline void MActXCtrl::SetParent(HWND hwndParent)
{
    m_hwndParent = hwndParent;
}

inline IUnknown* MActXCtrl::GetUnknown()
{
    if (m_pUnknown == NULL)
        return NULL;
    m_pUnknown->AddRef();
    return m_pUnknown;
}

inline HWND MActXCtrl::GetStatusWindow() const
{
    return m_hwndStatus;
}

inline void MActXCtrl::SetStatusWindow(HWND hwndStatus)
{
    m_hwndStatus = hwndStatus;
}

inline void MActXCtrl::InPlaceActivate()
{
    DoVerb(OLEIVERB_INPLACEACTIVATE);
}

inline void MActXCtrl::UIActivate()
{
    DoVerb(OLEIVERB_UIACTIVATE);
}

inline void MActXCtrl::Show(BOOL fVisible/* = TRUE*/)
{
    DoVerb(fVisible ? OLEIVERB_SHOW : OLEIVERB_HIDE);
}

inline void MActXCtrl::SetPos(INT x, INT y, INT width, INT height)
{
    SetPos(MRect(x, y, x + width, y + height));
}

inline /*virtual*/ MActXCtrl::~MActXCtrl()
{
}

inline void MActXCtrl::DoVerb(LONG iVerb)
{
    if (m_pUnknown == NULL)
        return;

    IOleObject* pioo;
    HRESULT hr = m_pUnknown->QueryInterface(
        IID_IOleObject, reinterpret_cast<void**>(&pioo));
    if (FAILED(hr))
        return;

    pioo->DoVerb(iVerb, NULL, this, 0, m_hwndParent, &m_rcCtrl);
    pioo->Release();
}

inline BOOL MActXCtrl::Create(CLSID clsid)
{
    ::CoCreateInstance(clsid, NULL,
        CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER,
        IID_IUnknown, reinterpret_cast<void**>(&m_pUnknown));

    if (m_pUnknown == NULL)
        return FALSE;

    IOleObject* pioo;
    HRESULT hr = m_pUnknown->QueryInterface(
        IID_IOleObject, reinterpret_cast<void**>(&pioo));
    if (FAILED(hr))
        return FALSE;

    pioo->SetClientSite(this);
    pioo->Release();

    IPersistStreamInit* ppsi;
    hr = m_pUnknown->QueryInterface(
        IID_IPersistStreamInit, reinterpret_cast<void**>(&ppsi));
    if (SUCCEEDED(hr))
    {
        ppsi->InitNew();
        ppsi->Release();
        return TRUE;
    }
    return FALSE;
}

inline void MActXCtrl::Destroy()
{
    if (m_pUnknown == NULL)
        return;

    IOleObject* pioo;
    HRESULT hr = m_pUnknown->QueryInterface(
        IID_IOleObject, reinterpret_cast<void**>(&pioo));
    if (SUCCEEDED(hr))
    {
        pioo->Close(OLECLOSE_NOSAVE);
        pioo->SetClientSite(NULL);
        pioo->Release();
    }

    IOleInPlaceObject* pipo;
    hr = m_pUnknown->QueryInterface(
        IID_IOleInPlaceObject, reinterpret_cast<void**>(&pipo));
    if (SUCCEEDED(hr))
    {
        pipo->UIDeactivate();
        pipo->InPlaceDeactivate();
        pipo->Release();
    }

    m_pUnknown->Release();
    m_pUnknown = NULL;
}

inline void MActXCtrl::SetPos(const MRect& rc)
{
    m_rcCtrl = rc;

    if (m_pUnknown == NULL)
        return;

    IOleInPlaceObject* pipo;
    HRESULT hr = m_pUnknown->QueryInterface(
        IID_IOleInPlaceObject, reinterpret_cast<void**>(&pipo));
    if (FAILED(hr))
        return;

    pipo->SetObjectRects(&m_rcCtrl, &m_rcCtrl);
    pipo->Release();
}

inline BOOL MActXCtrl::TranslateAccelerator(LPMSG pMsg)
{
    if (m_pUnknown == NULL)
        return FALSE;

    IOleInPlaceActiveObject* pao;
    HRESULT hr = m_pUnknown->QueryInterface(
        IID_IOleInPlaceActiveObject, reinterpret_cast<void**>(&pao));
    if (FAILED(hr))
        return FALSE;

    HRESULT result = pao->TranslateAccelerator(pMsg);
    pao->Release();
    return FAILED(result);
}

inline STDMETHODIMP MActXCtrl::QueryInterface(REFIID riid, void** ppvObject)
{
    if (ppvObject == NULL)
        return E_POINTER;

    if (IsEqualIID(riid, IID_IOleClientSite))
        *ppvObject = dynamic_cast<IOleClientSite*>(this);
    else if (IsEqualIID(riid, IID_IOleInPlaceSite))
        *ppvObject = dynamic_cast<IOleInPlaceSite*>(this);
    else if (IsEqualIID(riid, IID_IOleInPlaceFrame))
        *ppvObject = dynamic_cast<IOleInPlaceFrame*>(this);
    else if (IsEqualIID(riid, IID_IOleInPlaceUIWindow))
        *ppvObject = dynamic_cast<IOleInPlaceUIWindow*>(this);
    else if (IsEqualIID(riid, IID_IOleControlSite))
        *ppvObject = dynamic_cast<IOleControlSite*>(this);
    else if (IsEqualIID(riid, IID_IOleWindow))
        *ppvObject = this;
    else if (IsEqualIID(riid, IID_IDispatch))
        *ppvObject = dynamic_cast<IDispatch*>(this);
    else if (IsEqualIID(riid, IID_IUnknown))
        *ppvObject = this;
    else
    {
        *ppvObject = NULL;
        return E_NOINTERFACE;
    }

    AddRef();
    return S_OK;
}

inline STDMETHODIMP_(ULONG) MActXCtrl::AddRef()
{
    return ++m_nRefs;
}

inline STDMETHODIMP_(ULONG) MActXCtrl::Release()
{
    if (--m_nRefs == 0)
    {
        delete this;
        return 0;
    }
    return m_nRefs;
}

inline STDMETHODIMP MActXCtrl::SaveObject()
{
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::GetMoniker(
    DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER* ppMk)
{
    UNREFERENCED_PARAMETER(dwAssign);
    UNREFERENCED_PARAMETER(dwWhichMoniker);
    UNREFERENCED_PARAMETER(ppMk);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::GetContainer(LPOLECONTAINER* ppContainer)
{
    UNREFERENCED_PARAMETER(ppContainer);
    return E_NOINTERFACE;
}

inline STDMETHODIMP MActXCtrl::ShowObject()
{
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::OnShowWindow(BOOL fShow)
{
    UNREFERENCED_PARAMETER(fShow);
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::RequestNewObjectLayout()
{
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::GetWindow(HWND* phwnd)
{
    if (!::IsWindow(m_hwndParent))
        return S_FALSE;

    *phwnd = m_hwndParent;
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::ContextSensitiveHelp(BOOL fEnterMode)
{
    UNREFERENCED_PARAMETER(fEnterMode);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::CanInPlaceActivate()
{
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::OnInPlaceActivate()
{
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::OnUIActivate()
{
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::GetWindowContext(
    IOleInPlaceFrame** ppFrame, IOleInPlaceUIWindow** ppIIPUIWin,
    LPRECT prcPosRect, LPRECT prcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
    *ppFrame = dynamic_cast<IOleInPlaceFrame*>(this);
    *ppIIPUIWin = NULL;

    RECT rc;
    ::GetClientRect(m_hwndParent, &rc);
    prcPosRect->left = 0;
    prcPosRect->top = 0;
    prcPosRect->right  = rc.right;
    prcPosRect->bottom = rc.bottom;
    *prcClipRect = *prcPosRect;

    lpFrameInfo->cb             = sizeof(OLEINPLACEFRAMEINFO);
    lpFrameInfo->fMDIApp        = FALSE;
    lpFrameInfo->hwndFrame      = m_hwndParent;
    lpFrameInfo->haccel         = NULL;
    lpFrameInfo->cAccelEntries  = 0;

    (*ppFrame)->AddRef();
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::Scroll(SIZE scrollExtent)
{
    UNREFERENCED_PARAMETER(scrollExtent);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::OnUIDeactivate(BOOL fUndoable)
{
    UNREFERENCED_PARAMETER(fUndoable);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::OnInPlaceDeactivate()
{
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::DiscardUndoState()
{
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::DeactivateAndUndo()
{
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::OnPosRectChange(LPCRECT prcPosRect)
{
    UNREFERENCED_PARAMETER(prcPosRect);
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::GetBorder(LPRECT prcBorder)
{
    UNREFERENCED_PARAMETER(prcBorder);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::RequestBorderSpace(LPCBORDERWIDTHS lpborderwidths)
{
    UNREFERENCED_PARAMETER(lpborderwidths);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::SetBorderSpace(LPCBORDERWIDTHS lpborderwidths)
{
    UNREFERENCED_PARAMETER(lpborderwidths);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::SetActiveObject(
    IOleInPlaceActiveObject* pActiveObject, LPCOLESTR lpszObjName)
{
    UNREFERENCED_PARAMETER(pActiveObject);
    UNREFERENCED_PARAMETER(lpszObjName);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::InsertMenus(
    HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
    UNREFERENCED_PARAMETER(hmenuShared);
    UNREFERENCED_PARAMETER(lpMenuWidths);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::SetMenu(
    HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject)
{
    UNREFERENCED_PARAMETER(hmenuShared);
    UNREFERENCED_PARAMETER(holemenu);
    UNREFERENCED_PARAMETER(hwndActiveObject);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::RemoveMenus(HMENU hmenuShared)
{
    UNREFERENCED_PARAMETER(hmenuShared);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::SetStatusText(LPCOLESTR pszStatusText)
{
    if (m_hwndStatus && ::IsWindow(m_hwndStatus))
    {
        MWideToText strText(pszStatusText);
        if (::IsWindow(m_hwndStatus))
        {
            ::SendMessage(m_hwndStatus, SB_SETTEXT, 0,
                reinterpret_cast<LPARAM>(strText.c_str()));
        }
        else
        {
            ::SetWindowText(m_hwndStatus, strText.c_str());
        }
    }
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::EnableModeless(BOOL fEnable)
{
    UNREFERENCED_PARAMETER(fEnable);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::TranslateAccelerator(LPMSG pMsg, WORD wID)
{
    UNREFERENCED_PARAMETER(pMsg);
    UNREFERENCED_PARAMETER(wID);
    return S_OK;
}

inline STDMETHODIMP MActXCtrl::OnControlInfoChanged()
{
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::LockInPlaceActive(BOOL fLock)
{
    UNREFERENCED_PARAMETER(fLock);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::GetExtendedControl(IDispatch** ppDisp)
{
    if (ppDisp == NULL)
        return E_INVALIDARG;

    *ppDisp = dynamic_cast<IDispatch*>(this);
    (*ppDisp)->AddRef();

    return S_OK;
}

inline STDMETHODIMP
MActXCtrl::TransformCoords(POINTL* pptlHimetric, POINTF* pptfContainer, DWORD dwFlags)
{
    UNREFERENCED_PARAMETER(pptlHimetric);
    UNREFERENCED_PARAMETER(pptfContainer);
    UNREFERENCED_PARAMETER(dwFlags);
    return E_NOTIMPL;
}

inline STDMETHODIMP
MActXCtrl::TranslateAccelerator(LPMSG pMsg, DWORD grfModifiers)
{
    UNREFERENCED_PARAMETER(pMsg);
    UNREFERENCED_PARAMETER(grfModifiers);
    return S_FALSE;
}

inline STDMETHODIMP MActXCtrl::OnFocus(BOOL fGotFocus)
{
    UNREFERENCED_PARAMETER(fGotFocus);
    return E_NOTIMPL;
}

inline STDMETHODIMP MActXCtrl::ShowPropertyFrame()
{
    return E_NOTIMPL;
}

inline STDMETHODIMP
MActXCtrl::GetIDsOfNames(
    REFIID riid, OLECHAR** rgszNames, UINT cNames,
    LCID lcid, DISPID* rgdispid)
{
    UNREFERENCED_PARAMETER(static_cast<IID>(riid)); // IID cast required for MinGW
    UNREFERENCED_PARAMETER(rgszNames);
    UNREFERENCED_PARAMETER(cNames);
    UNREFERENCED_PARAMETER(lcid);

    *rgdispid = DISPID_UNKNOWN;
    return DISP_E_UNKNOWNNAME;
}

inline STDMETHODIMP
MActXCtrl::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
{
    UNREFERENCED_PARAMETER(itinfo);
    UNREFERENCED_PARAMETER(lcid);
    UNREFERENCED_PARAMETER(pptinfo);
    return E_NOTIMPL;
}

inline STDMETHODIMP
MActXCtrl::GetTypeInfoCount(UINT* pctinfo)
{
    UNREFERENCED_PARAMETER(pctinfo);
    return E_NOTIMPL;
}

inline STDMETHODIMP
MActXCtrl::Invoke(
    DISPID dispid, REFIID riid, LCID lcid, WORD wFlags,
    DISPPARAMS* pdispparams, VARIANT* pvarResult,
    EXCEPINFO* pexecinfo, UINT* puArgErr)
{
    UNREFERENCED_PARAMETER(dispid);
    UNREFERENCED_PARAMETER(static_cast<IID>(riid)); // IID cast required for MinGW
    UNREFERENCED_PARAMETER(lcid);
    UNREFERENCED_PARAMETER(wFlags);
    UNREFERENCED_PARAMETER(pdispparams);
    UNREFERENCED_PARAMETER(pvarResult);
    UNREFERENCED_PARAMETER(pexecinfo);
    UNREFERENCED_PARAMETER(puArgErr);
    return DISP_E_MEMBERNOTFOUND;
}

inline IDispatch* MActXCtrl::GetDispatch()
{
    if (m_pUnknown == NULL)
        return NULL;

    IDispatch* pDispatch;
    HRESULT hr = m_pUnknown->QueryInterface(
        IID_IDispatch, reinterpret_cast<void**>(&pDispatch));
    if (SUCCEEDED(hr))
        return pDispatch;
    return NULL;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MACTXCTRL_HPP_
