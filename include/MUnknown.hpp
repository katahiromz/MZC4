// MUnknown.hpp --- MZC4 IUnknown implement class               -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
//////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MUNKNOWN_HPP_
#define MZC4_MUNKNOWN_HPP_      2   /* Version 2 */

class MUnknown;

//////////////////////////////////////////////////////////////////////////////

#include <unknwn.h>

class MUnknown : public IUnknown
{
public:
    MUnknown() : m_cRef(1)
    {
    }

    virtual ~MUnknown()
    {
    }

    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObj)
    {
        if (!ppvObj)
            return E_INVALIDARG;

        *ppvObj = NULL;
        if (riid == IID_IUnknown)
        {
            *ppvObj = (void *)this;
            AddRef();
            return S_OK;
        }
        return E_NOINTERFACE;
    }

    virtual ULONG STDMETHODCALLTYPE AddRef()
    {
        InterlockedIncrement(&m_cRef);
        return m_cRef;
    }

    virtual ULONG STDMETHODCALLTYPE Release()
    {
        LONG cRef = InterlockedDecrement(&m_cRef);
        if (m_cRef == 0)
        {
            delete this;
        }
        return cRef;
    }

protected:
    LONG m_cRef;
};

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MUNKNOWN_HPP_
