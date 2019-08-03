// MSecurityDescriptor.hpp -- security descriptor wrapper       -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSECURITYDESCRIPTOR_HPP_
#define MZC4_MSECURITYDESCRIPTOR_HPP_

class MSecurityDescriptor;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <accctrl.h>        // for EXPLICIT_ACCESS
#include <aclapi.h>         // for ::BuildExplicitAccessWithName
#include <cassert>          // assert

#pragma comment(lib, "advapi32.lib")

////////////////////////////////////////////////////////////////////////////

class MSecurityDescriptor : public SECURITY_DESCRIPTOR
{
public:
    MSecurityDescriptor();
    BOOL AttachEmptyDacl(); // grant all
    BOOL AttachNullDacl();  // grant none
    DWORD AttachDenyDacl(LPTSTR pszTrusteeName);
    DWORD AttachGrantDacl(LPTSTR pszTrusteeName);
};

///////////////////////////////////////////////////////////////////////////////

inline BOOL MSecurityDescriptor::AttachEmptyDacl()
{
    ACL acl;
    BOOL b = ::InitializeAcl(&acl, sizeof(acl), ACL_REVISION);
    assert(b);
    if (b)
    {
        b = ::SetSecurityDescriptorDacl(this, TRUE, &acl, TRUE);
        assert(b);
    }
    return b;
}

inline BOOL MSecurityDescriptor::AttachNullDacl()
{
    BOOL b = ::SetSecurityDescriptorDacl(this, TRUE, NULL, TRUE);
    assert(b);
    return b;
}

inline DWORD MSecurityDescriptor::AttachDenyDacl(LPTSTR pszTrusteeName)
{
    EXPLICIT_ACCESS ea;
    ZeroMemory(&ea, sizeof(ea));
    ::BuildExplicitAccessWithName(&ea, pszTrusteeName,
        GENERIC_ALL, DENY_ACCESS, NO_INHERITANCE);
    PACL pDacl;
    DWORD dwResult = ::SetEntriesInAcl(1, &ea, NULL, &pDacl);
    assert(dwResult == ERROR_SUCCESS);
    ::LocalFree(pDacl);
    return dwResult;
}

inline DWORD MSecurityDescriptor::AttachGrantDacl(LPTSTR pszTrusteeName)
{
    EXPLICIT_ACCESS ea;
    ZeroMemory(&ea, sizeof(ea));
    ::BuildExplicitAccessWithName(&ea, pszTrusteeName,
        GENERIC_ALL, GRANT_ACCESS, NO_INHERITANCE);
    PACL pDacl;
    DWORD dwResult = ::SetEntriesInAcl(1, &ea, NULL, &pDacl);
    assert(dwResult == ERROR_SUCCESS);
    ::LocalFree(pDacl);
    return dwResult;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSECURITYDESCRIPTOR_HPP_
