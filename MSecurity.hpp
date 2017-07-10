// MSecurity.hpp -- security                                    -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSECURITY_HPP_
#define MZC4_MSECURITY_HPP_     2   /* Version 2 */

////////////////////////////////////////////////////////////////////////////

#include "MSecurityAttributes.hpp"
#include "MSecurityDescriptor.hpp"

inline BOOL EnableProcessPriviledgeDx(LPCTSTR pszSE_)
{
    BOOL f;
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tp;
    
    f = FALSE;
    if (::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES,
                           &hToken))
    {
        if (::LookupPrivilegeValue(NULL, pszSE_, &luid))
        {
            tp.PrivilegeCount = 1;
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            tp.Privileges[0].Luid = luid;
            f = ::AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL);
        }
        ::CloseHandle(hToken);
    }

    return f;
}

inline BOOL EnableThreadPriviledgeDx(LPCTSTR pszSE_)
{
    BOOL f;
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tp;
    
    f = FALSE;
    if (::OpenThreadToken(::GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES,
                          FALSE, &hToken))
    {
        if (::LookupPrivilegeValue(NULL, pszSE_, &luid))
        {
            tp.PrivilegeCount = 1;
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            tp.Privileges[0].Luid = luid;
            f = ::AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL);
        }
        ::CloseHandle(hToken);
    }

    return f;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSECURITY_HPP_
