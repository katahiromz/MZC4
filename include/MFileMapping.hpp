// MFileMapping.hpp -- Win32API file mapping wrapper            -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFILEMAPPING_HPP_
#define MZC4_MFILEMAPPING_HPP_      16      /* Version 16 */

class MMapView;
    template <typename T>
    class MTypedMapView;

class MFileMapping;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

#ifndef LOLONG
    #define LOLONG(dwl) static_cast<DWORD>(dwl)
#endif
#ifndef HILONG
    #define HILONG(dwl) static_cast<DWORD>(((dwl) >> 32) & 0xFFFFFFFF)
#endif
#ifndef MAKELONGLONG
    #define MAKELONGLONG(lo,hi) \
        (static_cast<DWORD>(lo) | \
            (static_cast<DWORDLONG>(static_cast<DWORD>(hi)) << 32))
#endif

////////////////////////////////////////////////////////////////////////////

#include "MUnknown.hpp"

class MMapView
{
public:
    class MSharedView;
    MSharedView *m_pView;
    DWORDLONG    m_index;
    DWORD        m_mod;
    DWORD        m_size;

    MMapView();
    MMapView(LPVOID pv, DWORDLONG index, DWORD mod, DWORD size);
    MMapView(const MMapView& view);
    ~MMapView();

    MMapView& operator=(const MMapView& view);

    LPVOID Ptr() const;
    operator LPVOID() const;
    bool operator!() const;

    BOOL FlushViewOfFile(DWORD dwNumberOfBytes = 0);
};

////////////////////////////////////////////////////////////////////////////

template <typename T>
class MTypedMapView
{
public:
    MMapView m_map_view;

    MTypedMapView();
    MTypedMapView(LPVOID pv, DWORDLONG index, DWORD mod, DWORD size);
    MTypedMapView(const MMapView& map_view);
    MTypedMapView(const MTypedMapView<T>& map_view);
    MTypedMapView<T>& operator=(const MMapView& map_view);
    MTypedMapView<T>& operator=(const MTypedMapView<T>& map_view);

    T *Ptr() const;
    operator T*() const;
    bool operator!() const;
    T& operator*() const;
    T *operator->() const;
    T& operator[](size_t index)
    {
        return Ptr()[index];
    }
    const T& operator[](size_t index) const
    {
        return Ptr()[index];
    }

    BOOL FlushViewOfFile(DWORD dwNumberOfBytes = 0);
};

////////////////////////////////////////////////////////////////////////////

class MFileMapping
{
public:
    MFileMapping();
    MFileMapping(HANDLE hMapping);
    MFileMapping(const MFileMapping& mapping);
    MFileMapping& operator=(const MFileMapping& mapping);
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
    BOOL CreateFileMapping64(
        HANDLE hFile = INVALID_HANDLE_VALUE,
        LPSECURITY_ATTRIBUTES lpSA = NULL,
        DWORD dwPAGE_ = PAGE_READWRITE,
        DWORDLONG dwlSize = 0, LPCTSTR lpName = NULL);
    BOOL OpenFileMapping(DWORD dwFILE_MAP_ = FILE_MAP_ALL_ACCESS,
                         BOOL bInherit = FALSE,
                         LPCTSTR lpName = NULL);
    BOOL CloseHandle();

    LPVOID
    MapViewOfFile(DWORD dwFILE_MAP_, DWORD dwOffsetHigh = 0,
                  DWORD dwOffsetLow = 0, DWORD dwNumberOfBytes = 0);
    LPVOID
    MapViewOfFile64(DWORD dwFILE_MAP_, DWORDLONG dwlOffset = 0,
                    DWORD dwNumberOfBytes = 0);
    LPVOID
    MapViewOfFileEx(DWORD dwFILE_MAP_, DWORD dwOffsetHigh = 0,
                    DWORD dwOffsetLow = 0, DWORD dwNumberOfBytes = 0,
                    LPVOID lpBaseAddress = NULL);
    LPVOID
    MapViewOfFileEx64(DWORD dwFILE_MAP_, DWORDLONG dwlOffset = 0,
                      DWORD dwNumberOfBytes = 0, LPVOID lpBaseAddress = NULL);
    BOOL UnmapViewOfFile(LPVOID lpBaseAddress);

    DWORD     Seek(DWORD dwOffsetHigh, DWORD dwOffsetLow, BOOL bAbsolute = FALSE);
    DWORDLONG Seek64(LONGLONG offset, BOOL bAbsolute = FALSE);

    BOOL ReadData(LPVOID pvData, DWORD dwDataSize);
    BOOL WriteData(LPCVOID pvData, DWORD dwDataSize);

    DWORD GetPos(LPDWORD pdwHigh = NULL) const;
    DWORDLONG GetPos64() const;

    MMapView MapViewDx(DWORD dwOffsetHigh = 0, DWORD dwOffsetLow = 0,
                       DWORD dwFILE_MAP_ = FILE_MAP_ALL_ACCESS,
                       DWORD dwNumberOfBytes = 0);
    MMapView MapViewDx64(DWORDLONG dwlOffset = 0,
                         DWORD dwFILE_MAP_ = FILE_MAP_ALL_ACCESS,
                         DWORD dwNumberOfBytes = 0);

    MMapView GetData(DWORD dwDataSize,
                     DWORD dwFILE_MAP_ = FILE_MAP_ALL_ACCESS);
    template <typename T>
    MTypedMapView<T> GetTypedData(DWORD dwDataSize = sizeof(T) * 1,
                                  DWORD dwFILE_MAP_ = FILE_MAP_ALL_ACCESS)
    {
        MTypedMapView<T> view(MapViewDx64(m_index, dwFILE_MAP_, dwDataSize));
        return view;
    }

    static HANDLE CloneHandleDx(HANDLE hMapping);

protected:
    HANDLE m_hMapping;
    DWORDLONG m_index;
    DWORD m_granularity;

    VOID GetGranularity(DWORD& granularity);
};

////////////////////////////////////////////////////////////////////////////

class MMapView::MSharedView : public MUnknown
{
public:
    LPVOID m_pv;

    MSharedView(LPVOID pv) : m_pv(pv)
    {
    }

    virtual ~MSharedView()
    {
        ::UnmapViewOfFile(m_pv);
    }
};

inline MMapView::MMapView() : m_pView(NULL), m_mod(0), m_size(0)
{
}

inline MMapView::MMapView(LPVOID pv, DWORDLONG index, DWORD mod, DWORD size)
    : m_pView(new MSharedView(pv)), m_index(index), m_mod(mod), m_size(size)
{
}

inline MMapView::MMapView(const MMapView& view)
    : m_pView(view.m_pView), m_index(view.m_index),
      m_mod(view.m_mod), m_size(view.m_size)
{
    if (m_pView)
        m_pView->AddRef();
}

inline MMapView&
MMapView::operator=(const MMapView& view)
{
    if (this != &view && m_pView != view.m_pView)
    {
        if (m_pView)
            m_pView->Release();
        m_pView = view.m_pView;
        if (m_pView)
            m_pView->AddRef();
        m_index = view.m_index;
        m_mod = view.m_mod;
        m_size = view.m_size;
    }
    return *this;
}

inline MMapView::~MMapView()
{
    if (m_pView)
        m_pView->Release();
}

inline LPVOID MMapView::Ptr() const
{
    if (this && m_pView)
    {
        return ((LPBYTE)m_pView->m_pv) + m_mod;
    }
    return NULL;
}

inline MMapView::operator LPVOID() const
{
    return Ptr();
}

inline bool MMapView::operator!() const
{
    return Ptr() == NULL;
}

inline BOOL
MMapView::FlushViewOfFile(DWORD dwNumberOfBytes/* = 0*/)
{
    assert(m_pView);
    return ::FlushViewOfFile(Ptr(), dwNumberOfBytes);
}

////////////////////////////////////////////////////////////////////////////

inline VOID MFileMapping::GetGranularity(DWORD& granularity)
{
    SYSTEM_INFO info;
    ::GetSystemInfo(&info);
    granularity = info.dwAllocationGranularity;
}

inline MFileMapping::MFileMapping() : m_hMapping(NULL), m_index(0)
{
    GetGranularity(m_granularity);
}

inline MFileMapping::MFileMapping(HANDLE hMapping)
    : m_hMapping(hMapping), m_index(0)
{
    GetGranularity(m_granularity);
}

inline MFileMapping::MFileMapping(const MFileMapping& mapping)
    : m_hMapping(CloneHandleDx(mapping.m_hMapping)), m_index(mapping.m_index),
      m_granularity(mapping.m_granularity)
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

inline BOOL
MFileMapping::CreateFileMapping64(
    HANDLE hFile/* = INVALID_HANDLE_VALUE*/,
    LPSECURITY_ATTRIBUTES lpSA/* = NULL*/,
    DWORD dwPAGE_/* = PAGE_READWRITE*/,
    DWORDLONG dwlSize/* = 0*/, LPCTSTR lpName/* = NULL*/)
{
    return CreateFileMapping(hFile, lpSA, dwPAGE_,
                             HILONG(dwlSize), LOLONG(dwlSize), lpName);
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

inline LPVOID
MFileMapping::MapViewOfFile(
    DWORD dwFILE_MAP_, DWORD dwOffsetHigh/* = 0*/, DWORD dwOffsetLow/* = 0*/,
    DWORD dwNumberOfBytes/* = 0*/)
{
    LPVOID pMap = ::MapViewOfFile(Handle(), dwFILE_MAP_, dwOffsetHigh,
                                  dwOffsetLow, dwNumberOfBytes);
    return pMap;
}

inline LPVOID 
MFileMapping::MapViewOfFileEx(
    DWORD dwFILE_MAP_, DWORD dwOffsetHigh/* = 0*/, DWORD dwOffsetLow/* = 0*/,
    DWORD dwNumberOfBytes/* = 0*/, LPVOID lpBaseAddress/* = NULL*/)
{
    LPVOID pMap = ::MapViewOfFileEx(Handle(), dwFILE_MAP_, dwOffsetHigh,
                                    dwOffsetHigh, dwNumberOfBytes,
                                    lpBaseAddress);
    return pMap;
}

inline LPVOID
MFileMapping::MapViewOfFileEx64(DWORD dwFILE_MAP_, DWORDLONG dwlOffset/* = 0*/,
    DWORD dwNumberOfBytes/* = 0*/, LPVOID lpBaseAddress/* = NULL*/)
{
    return MapViewOfFileEx(dwFILE_MAP_, HILONG(dwlOffset),
        LOLONG(dwlOffset), dwNumberOfBytes, lpBaseAddress);
}

inline BOOL MFileMapping::UnmapViewOfFile(LPVOID lpBaseAddress)
{
    return ::UnmapViewOfFile(lpBaseAddress);
}

inline MMapView
MFileMapping::MapViewDx(
    DWORD dwOffsetHigh/* = 0*/, DWORD dwOffsetLow/* = 0*/,
    DWORD dwFILE_MAP_/* = FILE_MAP_ALL_ACCESS*/, DWORD dwNumberOfBytes/* = 0*/)
{
    DWORDLONG dwlOffset = MAKELONGLONG(dwOffsetLow, dwOffsetHigh);
    return MapViewDx64(dwlOffset, dwFILE_MAP_, dwNumberOfBytes);
}

inline MMapView
MFileMapping::MapViewDx64(DWORDLONG dwlOffset/* = 0*/,
                          DWORD dwFILE_MAP_/* = FILE_MAP_ALL_ACCESS*/,
                          DWORD dwNumberOfBytes/* = 0*/)
{
    DWORD mod = DWORD(dwlOffset % m_granularity);
    DWORDLONG dwlFixedOffset = dwlOffset;
    dwlFixedOffset -= mod;

    LPVOID pv = MapViewOfFile64(dwFILE_MAP_, dwlFixedOffset, dwNumberOfBytes + mod);
    MMapView view(pv, dwlOffset, mod, dwNumberOfBytes);
    return view;
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

inline MFileMapping& MFileMapping::operator=(const MFileMapping& mapping)
{
    if (this != &mapping && m_hMapping != mapping.m_hMapping)
    {
        HANDLE hMapping = CloneHandleDx(mapping);
        Attach(hMapping);
    }
    m_index = mapping.m_index;
}

inline LPVOID
MFileMapping::MapViewOfFile64(DWORD dwFILE_MAP_, DWORDLONG dwlOffset/* = 0*/,
                              DWORD dwNumberOfBytes/* = 0*/)
{
    return MapViewOfFile(dwFILE_MAP_, HILONG(dwlOffset), LOLONG(dwlOffset),
                         dwNumberOfBytes);
}

inline DWORD
MFileMapping::Seek(DWORD dwOffsetHigh, DWORD dwOffsetLow,
                   BOOL bAbsolute/* = FALSE*/)
{
    return (DWORD)Seek64(MAKELONGLONG(dwOffsetLow, dwOffsetHigh), bAbsolute);
}

inline DWORDLONG
MFileMapping::Seek64(LONGLONG offset, BOOL bAbsolute/* = FALSE*/)
{
    if (bAbsolute)
    {
        m_index = offset;
    }
    else
    {
        m_index += offset;
    }
    return m_index;
}

inline MMapView
MFileMapping::GetData(DWORD dwDataSize,
                      DWORD dwFILE_MAP_/* = FILE_MAP_ALL_ACCESS*/)
{
    return MapViewDx64(m_index, dwFILE_MAP_, dwDataSize);
}

inline BOOL MFileMapping::ReadData(LPVOID pvData, DWORD dwDataSize)
{
    MMapView view = GetData(dwDataSize, FILE_MAP_READ);
    if (!view)
        return FALSE;
    CopyMemory(pvData, view, dwDataSize);
    m_index += dwDataSize;
    return TRUE;
}

inline BOOL MFileMapping::WriteData(LPCVOID pvData, DWORD dwDataSize)
{
    MMapView view = GetData(dwDataSize, FILE_MAP_WRITE);
    if (!view)
        return FALSE;
    CopyMemory(view, pvData, dwDataSize);
    m_index += dwDataSize;
    return TRUE;
}

inline DWORD MFileMapping::GetPos(LPDWORD pdwHigh) const
{
    DWORDLONG index = m_index;
    if (pdwHigh)
    {
        *pdwHigh = HILONG(index);
        return LOLONG(index);
    }
    else if (index > 0xFFFFFFFF)
    {
        return 0xFFFFFFFF;
    }
    else
    {
        return (DWORD)index;
    }
}

inline DWORDLONG MFileMapping::GetPos64() const
{
    return m_index;
}

////////////////////////////////////////////////////////////////////////////

template <typename T>
inline MTypedMapView<T>::MTypedMapView()
{
}

template <typename T>
inline MTypedMapView<T>::MTypedMapView(LPVOID pv, DWORDLONG index, DWORD mod, DWORD size)
    : m_map_view(pv, index, mod, size)
{
}

template <typename T>
inline MTypedMapView<T>::MTypedMapView(const MMapView& map_view)
    : m_map_view(map_view)
{
}

template <typename T>
inline MTypedMapView<T>::MTypedMapView(const MTypedMapView<T>& map_view)
    : m_map_view(map_view.m_map_view)
{
}

template <typename T>
inline MTypedMapView<T>& MTypedMapView<T>::operator=(const MMapView& map_view)
{
    m_map_view = map_view;
    return *this;
}

template <typename T>
inline MTypedMapView<T>&
MTypedMapView<T>::operator=(const MTypedMapView<T>& map_view)
{
    m_map_view = map_view.m_map_view;
    return *this;
}

template <typename T>
inline MTypedMapView<T>::operator T*() const
{
    return Ptr();
}

template <typename T>
inline T *MTypedMapView<T>::Ptr() const
{
    return reinterpret_cast<T *>(m_map_view.Ptr());
}

template <typename T>
inline bool MTypedMapView<T>::operator!() const
{
    return !m_map_view;
}

template <typename T>
inline BOOL MTypedMapView<T>::FlushViewOfFile(DWORD dwNumberOfBytes/* = 0*/)
{
    return m_map_view.FlushViewOfFile(dwNumberOfBytes);
}

template <typename T>
inline T *MTypedMapView<T>::operator->() const
{
    return Ptr();
}

template <typename T>
inline T& MTypedMapView<T>::operator*() const
{
    return *Ptr();
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFILEMAPPING_HPP_
