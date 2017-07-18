// MGdiObject.hpp -- Win32API GDI object wrapper                -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MGDIOBJECT_HPP_
#define MZC4_MGDIOBJECT_HPP_     2   /* Version 2 */

class MGdiObject;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

#pragma comment(lib, "gdi32.lib")

////////////////////////////////////////////////////////////////////////////

class MGdiObject
{
public:
    HGDIOBJ m_hGdiObj;

public:
    MGdiObject();
    MGdiObject(HGDIOBJ hGdiObj);
    virtual ~MGdiObject();

    bool operator!() const;
    MGdiObject& operator=(HGDIOBJ hGdiObj);
    bool operator==(HGDIOBJ hGdiObj);
    bool operator!=(HGDIOBJ hGdiObj);
    HANDLE Handle() const;

    BOOL Attach(HGDIOBJ hGdiObj);
    HGDIOBJ Detach();

    BOOL GetStockObject(INT nObject);
    INT GetObject(INT nSize, LPVOID pData) const;
    BOOL DeleteObject(VOID);

    BOOL UnrealizeObject(VOID);

private:
    // NOTE: MGdiObject is not copyable.
    MGdiObject(const MGdiObject& obj);              // no impl
    MGdiObject& operator=(const MGdiObject& obj);   // no impl
};

////////////////////////////////////////////////////////////////////////////

inline MGdiObject::MGdiObject() : m_hGdiObj(NULL)
{
}

inline MGdiObject::MGdiObject(HGDIOBJ hGdiObj) : m_hGdiObj(hGdiObj)
{
}

inline /*virtual*/ MGdiObject::~MGdiObject()
{
    DeleteObject();
}

inline MGdiObject& MGdiObject::operator=(HGDIOBJ hGdiObj)
{
    if (Handle() != hGdiObj)
    {
        DeleteObject();
        m_hGdiObj = hGdiObj;
    }
    return *this;
}

inline BOOL MGdiObject::Attach(HGDIOBJ hGdiObj)
{
    assert(hGdiObj);
    assert(m_hGdiObj == NULL);
    m_hGdiObj = hGdiObj;
    return m_hGdiObj != NULL;
}

inline HGDIOBJ MGdiObject::Detach()
{
    HGDIOBJ hGdiObj = m_hGdiObj;
    m_hGdiObj = NULL;
    return hGdiObj;
}

inline BOOL MGdiObject::GetStockObject(INT nObject)
{
    assert(m_hGdiObj == NULL);
    return Attach(::GetStockObject(nObject));
}

inline BOOL MGdiObject::DeleteObject(VOID)
{
    if (Handle())
    {
        BOOL bOK = ::DeleteObject(Detach());
        return bOK;
    }
    return FALSE;
}

inline HANDLE MGdiObject::Handle() const
{
    return (this ? m_hGdiObj : NULL);
}

inline BOOL MGdiObject::UnrealizeObject(VOID)
{
    return ::UnrealizeObject(m_hGdiObj);
}

inline bool MGdiObject::operator!() const
{
    return Handle() == NULL;
}

inline bool MGdiObject::operator==(HGDIOBJ hGdiObj)
{
    return Handle() == hGdiObj;
}

inline bool MGdiObject::operator!=(HGDIOBJ hGdiObj)
{
    return Handle() != hGdiObj;
}

inline INT MGdiObject::GetObject(INT nSize, LPVOID pData) const
{
    return ::GetObject(m_hGdiObj, nSize, pData);
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MGDIOBJECT_HPP_
