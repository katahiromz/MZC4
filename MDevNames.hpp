// MDevNames.hpp -- Win32API DEVNAMES wrapper                   -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MDEVNAMES_HPP_
#define MZC4_MDEVNAMES_HPP_     2   /* Version 2 */

struct MDevNames;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

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

#endif  // ndef MZC4_MDEVNAMES_HPP_
