// MFileMapping.hpp -- Win32API file mapping wrapper            -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFILEMAPPING_HPP_
#define MZC4_MFILEMAPPING_HPP_      2       /* Version 2 */

class MFileMappingView;
class MFileMapping;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

#include "MUnknown.hpp"

class MFileMappingView
{
public:
    class MSharedView;

    MSharedView *m_pView;

    MFileMappingView();
    MFileMappingView(LPVOID pv);
    MFileMappingView(MFileMappingView& view);
    ~MFileMappingView();

    MFileMappingView& operator=(MFileMappingView& view);

    operator LPVOID() const;
    LPVOID Ptr() const;
    bool operator!() const;

    BOOL FlushViewOfFile(DWORD dwNumberOfBytes = 0);
};

////////////////////////////////////////////////////////////////////////////

class MFileMapping
{
public:
    MFileMapping();
    MFileMapping(HANDLE hMapping);
    MFileMapping(MFileMapping& mapping);
    ~MFileMapping();

    HANDLE Handle() const;
    operator HANDLE() const;
    BOOL Attach(HANDLE hMapping);
    HANDLE Detach();

    BOOL CreateFileMapping(
        HANDLE hFile = INVALID_HANDLE_VALUE,
        LPSECURITY_ATTRIBUTES lpSA = NULL,
        DWORD dwPAGE_ = PAGE_READWRITE,
        DWORD dwSizeHigh = 0, DWORD dwSizeLow = 0,
        LPCTSTR lpName = NULL);
    BOOL OpenFileMapping(DWORD dwFILE_MAP_ = FILE_MAP_ALL_ACCESS,
                         BOOL bInherit = FALSE,
                         LPCTSTR lpName = NULL);

    BOOL CloseHandle();

    MFileMappingView
    MapViewOfFile(DWORD dwFILE_MAP_, DWORD dwOffsetHigh, DWORD dwOffsetLow,
                  DWORD dwNumberOfBytes = 0);
    MFileMappingView
    MapViewOfFileEx(DWORD dwFILE_MAP_, DWORD dwOffsetHigh, DWORD dwOffsetLow,
                    DWORD dwNumberOfBytes = 0, LPVOID lpBaseAddress = NULL);

    static HANDLE CloneHandleDx(HANDLE hMapping);

    MFileMapping& operator=(MFileMapping& mapping);

protected:
    HANDLE m_hMapping;
};

////////////////////////////////////////////////////////////////////////////

class MFileMappingView::MSharedView : public MUnknown
{
public:
    LPVOID m_pv;

    MSharedView(LPVOID pv);
    ~MSharedView();
};

inline MFileMappingView::MSharedView::MSharedView(LPVOID pv) : m_pv(pv)
{
}

inline /*virtual*/ MFileMappingView::MSharedView::~MSharedView()
{
    ::UnmapViewOfFile(m_pv);
}

inline MFileMappingView::MFileMappingView() : m_pView(NULL)
{
}

inline MFileMappingView::MFileMappingView(LPVOID pv)
    : m_pView(new MSharedView(pv))
{
}

inline MFileMappingView::MFileMappingView(MFileMappingView& view)
    : m_pView(view.m_pView)
{
    if (m_pView)
        m_pView->AddRef();
}

inline MFileMappingView&
MFileMappingView::operator=(MFileMappingView& view)
{
    if (this != &view)
    {
        if (m_pView)
            m_pView->Release();
        m_pView = view.m_pView;
        if (m_pView)
            m_pView->AddRef();
    }
    return *this;
}

inline MFileMappingView::~MFileMappingView()
{
    if (m_pView)
        m_pView->Release();
}

inline LPVOID MFileMappingView::Ptr() const
{
    if (this && m_pView)
        return m_pView->m_pv;
    return NULL;
}

inline MFileMappingView::operator LPVOID() const
{
    return Ptr();
}

inline bool MFileMappingView::operator!() const
{
    return Ptr() == NULL;
}

inline BOOL
MFileMappingView::FlushViewOfFile(DWORD dwNumberOfBytes/* = 0*/)
{
    assert(m_pView);
    return ::FlushViewOfFile(Ptr(), dwNumberOfBytes);
}

////////////////////////////////////////////////////////////////////////////

inline MFileMapping::MFileMapping() : m_hMapping(NULL)
{
}

inline MFileMapping::MFileMapping(HANDLE hMapping) : m_hMapping(hMapping)
{
}

inline MFileMapping::~MFileMapping()
{
    CloseHandle();
}

inline HANDLE MFileMapping::Handle() const
{
    return (this ? m_hMapping : NULL);
}

inline MFileMapping::operator HANDLE() const
{
    return Handle();
}

inline BOOL MFileMapping::Attach(HANDLE hMapping)
{
    if (m_hMapping)
        CloseHandle();
    m_hMapping = hMapping;
    return m_hMapping != NULL;
}

inline HANDLE MFileMapping::Detach()
{
    HANDLE hMapping = m_hMapping;
    m_hMapping = NULL;
    return hMapping;
}

inline BOOL MFileMapping::CreateFileMapping(
    HANDLE hFile/* = INVALID_HANDLE_VALUE*/,
    LPSECURITY_ATTRIBUTES lpSA/* = NULL*/,
    DWORD dwPAGE_/* = PAGE_READWRITE*/,
    DWORD dwSizeHigh/* = 0*/, DWORD dwSizeLow/* = 0*/,
    LPCTSTR lpName/* = NULL*/)
{
    HANDLE hMapping = ::CreateFileMapping(hFile, lpSA, dwPAGE_,
                                          dwSizeHigh, dwSizeLow, lpName);
    return Attach(hMapping);
}

inline BOOL MFileMapping::OpenFileMapping(
    DWORD dwFILE_MAP_/* = FILE_MAP_ALL_ACCESS*/,
    BOOL bInherit/* = FALSE*/, LPCTSTR lpName/* = NULL*/)
{
    HANDLE hMapping = ::OpenFileMapping(dwFILE_MAP_, bInherit, lpName);
    return Attach(hMapping);
}

inline BOOL MFileMapping::CloseHandle()
{
    if (m_hMapping)
    {
        BOOL bOK = ::CloseHandle(m_hMapping);
        m_hMapping = NULL;
        return bOK;
    }
    return FALSE;
}

inline MFileMappingView
MFileMapping::MapViewOfFile(
    DWORD dwFILE_MAP_, DWORD dwOffsetHigh, DWORD dwOffsetLow,
    DWORD dwNumberOfBytes/* = 0*/)
{
    LPVOID pMap = ::MapViewOfFile(Handle(), dwFILE_MAP_, dwOffsetHigh,
                                  dwOffsetLow, dwNumberOfBytes);
    if (pMap)
    {
        MFileMappingView view(pMap);
        return view;
    }
    else
    {
        MFileMappingView view;
        return view;
    }
}

inline MFileMappingView
MFileMapping::MapViewOfFileEx(
    DWORD dwFILE_MAP_, DWORD dwOffsetHigh, DWORD dwOffsetLow,
    DWORD dwNumberOfBytes/* = 0*/, LPVOID lpBaseAddress/* = NULL*/)
{
    LPVOID pMap = ::MapViewOfFileEx(Handle(), dwFILE_MAP_, dwOffsetHigh,
                                    dwOffsetLow, dwNumberOfBytes,
                                    lpBaseAddress);
    if (pMap)
    {
        MFileMappingView view(pMap);
        return view;
    }
    else
    {
        MFileMappingView view;
        return view;
    }
}

inline /*static*/ HANDLE MFileMapping::CloneHandleDx(HANDLE hMapping)
{
    if (hMapping == NULL)
        return NULL;

    HANDLE hProcess = ::GetCurrentProcess();
    HANDLE hDup = NULL;
    ::DuplicateHandle(hProcess, hMapping, hProcess, &hDup, 0,
                      FALSE, DUPLICATE_SAME_ACCESS);
    return hDup;
}

inline MFileMapping::MFileMapping(MFileMapping& mapping)
    : m_hMapping(CloneHandleDx(mapping.m_hMapping))
{
}

inline MFileMapping& MFileMapping::operator=(MFileMapping& mapping)
{
    if (this != &mapping && m_hMapping != mapping.m_hMapping)
    {
        HANDLE hMapping = CloneHandleDx(mapping);
        Attach(hMapping);
    }
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFILEMAPPING_HPP_
