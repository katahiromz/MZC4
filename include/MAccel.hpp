// MAccel.hpp -- Win32API accelerator wrapper                 -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MACCEL_HPP_
#define MZC4_MACCEL_HPP_    4       /* Version 4 */

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
    virtual ~MAccel();

    HACCEL Handle() const;
    operator HACCEL() const;
    bool operator!() const;
    MAccel& operator=(HACCEL hAccel);
    MAccel& operator=(const MAccel& accel);

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
    assert(m_hAccel);
}

inline /*virtual*/ MAccel::~MAccel()
{
    if (m_hAccel != NULL)
        DestroyAcceleratorTable();
}

inline MAccel::MAccel(HACCEL hAccel) : m_hAccel(hAccel)
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
    if (m_hAccel != hAccel)
    {
        Attach(hAccel);
    }
    return *this;
}

inline MAccel& MAccel::operator=(const MAccel& accel)
{
    if (m_hAccel != accel.m_hAccel)
    {
        HACCEL hAccel = CloneHandleDx(accel);
        Attach(hAccel);
    }
    return *this;
}

inline BOOL MAccel::Attach(HACCEL hAccel)
{
    assert(m_hAccel == NULL);
    if (m_hAccel)
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
    assert(m_hAccel);
    return ::CopyAcceleratorTable(m_hAccel, NULL, 0);
}

inline INT MAccel::CopyAcceleratorTable(LPACCEL pAccel, INT cEntries) const
{
    assert(m_hAccel);
    return ::CopyAcceleratorTable(m_hAccel, pAccel, cEntries);
}

inline BOOL MAccel::CreateAcceleratorTable(LPACCEL pAccel, INT cEntries)
{
    assert(m_hAccel == NULL);
    m_hAccel = ::CreateAcceleratorTable(pAccel, cEntries);
    assert(m_hAccel);
    return (m_hAccel != NULL);
}

inline BOOL MAccel::LoadAccelerators(LPCTSTR pszResourceName)
{
    assert(m_hAccel == NULL);
    m_hAccel = ::LoadAccelerators(::GetModuleHandle(NULL), pszResourceName);
    return (m_hAccel != NULL);
}

inline BOOL MAccel::LoadAccelerators(INT nResourceID)
{
    assert(m_hAccel == NULL);
    assert(nResourceID != 0);
    return LoadAccelerators(MAKEINTRESOURCE(nResourceID));
}

inline BOOL MAccel::DestroyAcceleratorTable()
{
    assert(m_hAccel);
    BOOL b = ::DestroyAcceleratorTable(m_hAccel);
    m_hAccel = NULL;
    return b;
}

inline BOOL MAccel::TranslateAccelerator(HWND hWnd, MSG *pMsg)
{
    return (m_hAccel != NULL &&
            ::TranslateAccelerator(hWnd, m_hAccel, pMsg));
}

inline /*static*/ HACCEL MAccel::CloneHandleDx(HACCEL hAccel)
{
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
