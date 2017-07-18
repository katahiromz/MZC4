// MUnknown.hpp --- MZC4 IUnknown implement class               -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
//////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MUNKNOWN_HPP_
#define MZC4_MUNKNOWN_HPP_      4   /* Version 4 */

class MUnknown;

//////////////////////////////////////////////////////////////////////////////

#include <unknwn.h>
#include <cassert>

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
        assert(m_cRef != -1);
#ifdef SINGLE_THREAD
        return ++m_cRef;
#else
        return ::InterlockedIncrement(&m_cRef);
#endif
    }

    virtual ULONG STDMETHODCALLTYPE Release()
    {
        assert(m_cRef);
#ifdef SINGLE_THREAD
        if (--m_cRef == 0)
#else
        if (::InterlockedDecrement(&m_cRef) == 0)
#endif
        {
            delete this;
            return 0;
        }
        return m_cRef;
    }

protected:
    LONG m_cRef;
};

//////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MUNKNOWN_HPP_
