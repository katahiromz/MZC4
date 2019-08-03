// MAccel.hpp -- Win32API accelerator wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MACCEL_HPP_
#define MZC4_MACCEL_HPP_    5       /* Version 5 */

class MAccel;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

class MAccel
{
public:
    MAccel();
    MAccel(UINT nResourceID);
    MAccel(HACCEL hAccel);
    MAccel(const MAccel& accel);
    MAccel& operator=(HACCEL hAccel);
    MAccel& operator=(const MAccel& accel);
    virtual ~MAccel();

    HACCEL Handle() const;
    operator HACCEL() const;
    bool operator!() const;

    BOOL Attach(HACCEL hAccel);
    HACCEL Detach();

    INT GetAcceleratorCount() const;
    INT CopyAcceleratorTable(LPACCEL pAccel, INT cEntries) const;

    BOOL CreateAcceleratorTable(LPACCEL pAccel, INT cEntries);
    BOOL LoadAccelerators(LPCTSTR pszResourceName);
    BOOL LoadAccelerators(INT nResourceID);
    BOOL DestroyAcceleratorTable();

    BOOL TranslateAccelerator(HWND hWnd, MSG *pMsg);

    static HACCEL CloneHandleDx(HACCEL hAccel);

public:
    HACCEL m_hAccel;
};

////////////////////////////////////////////////////////////////////////////

inline MAccel::MAccel() : m_hAccel(NULL)
{
}

inline MAccel::MAccel(UINT nResourceID) : m_hAccel(NULL)
{
    LoadAccelerators(nResourceID);
}

inline /*virtual*/ MAccel::~MAccel()
{
    DestroyAcceleratorTable();
}

inline MAccel::MAccel(HACCEL hAccel) : m_hAccel(hAccel)
{
}

inline MAccel::MAccel(const MAccel& accel)
    : m_hAccel(CloneHandleDx(accel))
{
}

inline HACCEL MAccel::Handle() const
{
    return (this ? m_hAccel : NULL);
}

inline MAccel::operator HACCEL() const
{
    return Handle();
}

inline bool MAccel::operator!() const
{
    return Handle() == NULL;
}

inline MAccel& MAccel::operator=(HACCEL hAccel)
{
    if (Handle() != hAccel)
    {
        Attach(hAccel);
    }
    return *this;
}

inline MAccel& MAccel::operator=(const MAccel& accel)
{
    if (Handle() != accel.Handle())
    {
        HACCEL hAccel = CloneHandleDx(accel);
        Attach(hAccel);
    }
    return *this;
}

inline BOOL MAccel::Attach(HACCEL hAccel)
{
    DestroyAcceleratorTable();
    m_hAccel = hAccel;
    return m_hAccel != NULL;
}

inline HACCEL MAccel::Detach()
{
    HACCEL hAccel = m_hAccel;
    m_hAccel = NULL;
    return hAccel;
}

inline INT MAccel::GetAcceleratorCount() const
{
    assert(Handle());
    return ::CopyAcceleratorTable(Handle(), NULL, 0);
}

inline INT MAccel::CopyAcceleratorTable(LPACCEL pAccel, INT cEntries) const
{
    assert(Handle());
    return ::CopyAcceleratorTable(Handle(), pAccel, cEntries);
}

inline BOOL MAccel::CreateAcceleratorTable(LPACCEL pAccel, INT cEntries)
{
    return Attach(::CreateAcceleratorTable(pAccel, cEntries));
}

inline BOOL MAccel::LoadAccelerators(LPCTSTR pszResourceName)
{
    return Attach(::LoadAccelerators(::GetModuleHandle(NULL), pszResourceName));
}

inline BOOL MAccel::LoadAccelerators(INT nResourceID)
{
    assert(nResourceID != 0);
    return LoadAccelerators(MAKEINTRESOURCE(nResourceID));
}

inline BOOL MAccel::DestroyAcceleratorTable()
{
    if (Handle())
    {
        BOOL bOK = ::DestroyAcceleratorTable(Detach());
        return bOK;
    }
    return FALSE;
}

inline BOOL MAccel::TranslateAccelerator(HWND hWnd, MSG *pMsg)
{
    return (Handle() != NULL &&
            ::TranslateAccelerator(hWnd, Handle(), pMsg));
}

inline /*static*/ HACCEL MAccel::CloneHandleDx(HACCEL hAccel)
{
    if (hAccel == NULL)
        return NULL;
    INT nCount = ::CopyAcceleratorTable(hAccel, NULL, 0);
    if (nCount == 0)
        return NULL;
    LPACCEL pAccel = new ACCEL[nCount];
    ::CopyAcceleratorTable(hAccel, pAccel, nCount);
    hAccel = ::CreateAcceleratorTable(pAccel, nCount);
    delete[] pAccel;
    return hAccel;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MACCEL_HPP_
