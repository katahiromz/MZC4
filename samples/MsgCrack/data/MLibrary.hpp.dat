// MLibrary.hpp -- Win32API DLL loader class                    -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MLIBRARY_HPP_
#define MZC4_MLIBRARY_HPP_      3   /* Version 3 */

class MLibrary;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <shlwapi.h>        // DLLVERSIONINFO, DLLVERSIONINFO2
#include <cassert>          // assert
#include <mbstring.h>       // _mbsrchr

////////////////////////////////////////////////////////////////////////////

class MLibrary
{
public:
    MLibrary();
    MLibrary(HINSTANCE hInstance);
    MLibrary(LPCTSTR pszFileName);
    MLibrary(LPCTSTR pszFileName, DWORD dwFlags);
    virtual ~MLibrary();

    BOOL Attach(HINSTANCE hInstance);
    HINSTANCE Detach();
    HINSTANCE Handle() const;

    bool operator!() const;
    operator HINSTANCE() const;
    MLibrary& operator=(HINSTANCE hInstance);

    BOOL LoadLibrary(LPCTSTR pszFileName);
    BOOL LoadLibraryEx(LPCTSTR pszFileName, DWORD dwFlags);
    BOOL LoadLocalLibrary(LPCTSTR pszFileName);
    BOOL LoadLocalLibraryEx(LPCTSTR pszFileName, DWORD dwFlags);
    BOOL LoadSystemLibrary(LPCTSTR pszFileName);
    BOOL LoadSystemLibraryEx(LPCTSTR pszFileName, DWORD dwFlags);
    BOOL FreeLibrary();

    FARPROC GetProcAddress(LPCSTR pszProcName);
    template <typename T_PROC>
    BOOL GetProcAddress(LPCSTR pszProcName, T_PROC& proc);
    BOOL GetModuleHandle(LPCTSTR pszFileName);
    BOOL GetModuleFileName(LPTSTR pszFileName, DWORD cch = MAX_PATH);

    HRESULT GetDllVersion(DLLVERSIONINFO *info);
#if (_WIN32_IE >= 0x0501)
    HRESULT GetDllVersion(DLLVERSIONINFO2 *info);
#endif

    HICON   LoadIcon(LPCTSTR pszName);
    HICON   LoadIcon(UINT nID);
    HICON   LoadSmallIcon(LPCTSTR pszName);
    HICON   LoadSmallIcon(UINT nID);
    HCURSOR LoadCursor(LPCTSTR pszName);
    HCURSOR LoadCursor(UINT nID);
    HBITMAP LoadBitmap(LPCTSTR pszName);
    HBITMAP LoadBitmap(UINT nID);
    HANDLE  LoadImage(LPCTSTR pszName, UINT uType,
        INT cxDesired = 0, INT cyDesired = 0, UINT fuLoad = 0);
    HANDLE  LoadImage(UINT nID, UINT uType,
        INT cxDesired = 0, INT cyDesired = 0, UINT fuLoad = 0);
    HMENU   LoadMenu(LPCTSTR pszName);
    HMENU   LoadMenu(UINT nID);
    INT     LoadString(UINT nID, LPTSTR pszBuffer, INT cchBuffer);
    HACCEL  LoadAccelerators(LPCTSTR pszName);
    HACCEL  LoadAccelerators(UINT nID);

    HRSRC   FindResource(LPCTSTR pszName, LPCTSTR pszType);
    HRSRC   FindResource(LPCTSTR pszName, UINT nType);
    HRSRC   FindResource(UINT nID, LPCTSTR pszType);
    HRSRC   FindResource(UINT nID, UINT nType);
    HRSRC   FindResourceEx(LPCTSTR pszName, LPCTSTR pszType, WORD wLanguage);
    HRSRC   FindResourceEx(LPCTSTR pszName, UINT nType, WORD wLanguage);
    HRSRC   FindResourceEx(UINT nID, LPCTSTR pszType, WORD wLanguage);
    HRSRC   FindResourceEx(UINT nID, UINT nType, WORD wLanguage);
    HGLOBAL LoadResource(HRSRC hRsrc);
    DWORD   SizeofResource(HRSRC hRsrc);

protected:
    HINSTANCE m_hInstance;

private:
    // NOTE: MLibrary is not copyable.
    MLibrary(const MLibrary& lib);
    MLibrary& operator=(const MLibrary& lib);
};

////////////////////////////////////////////////////////////////////////////

#define MakeDllVerULLDx(major,minor,build,qfe) \
    MAKEDLLVERULL((major),(minor),(build),(qfe))

HINSTANCE LoadLocalLibraryDx(LPCTSTR pszFileName);
HINSTANCE LoadSystemLibraryDx(LPCTSTR pszFileName);
HINSTANCE LoadLocalLibraryDx(LPCTSTR pszFileName, DWORD dwFlags);
HINSTANCE LoadSystemLibraryDx(LPCTSTR pszFileName, DWORD dwFlags);
HRESULT GetDllVersionDx(LPCTSTR pszDLL, DLLVERSIONINFO* info);
#if (_WIN32_IE >= 0x0501)
    HRESULT GetDllVersion2Dx(LPCTSTR pszDLL, DLLVERSIONINFO2* info);
#endif

////////////////////////////////////////////////////////////////////////////

inline MLibrary::MLibrary() : m_hInstance(NULL)
{
}

inline MLibrary::MLibrary(HINSTANCE hInstance) : m_hInstance(hInstance)
{
}

inline MLibrary::MLibrary(LPCTSTR pszFileName)
    : m_hInstance(::LoadLibrary(pszFileName))
{
    assert(Handle());
}

inline MLibrary::MLibrary(LPCTSTR pszFileName, DWORD dwFlags)
    : m_hInstance(::LoadLibraryEx(pszFileName, NULL, dwFlags))
{
    assert(Handle());
}

inline /*virtual*/ MLibrary::~MLibrary()
{
    FreeLibrary();
}

inline MLibrary& MLibrary::operator=(HINSTANCE hInstance)
{
#ifndef NDEBUG
    TCHAR szFileName[MAX_PATH];
    assert(hInstance == NULL || ::GetModuleFileName(hInstance, szFileName, MAX_PATH));
#endif
    if (Handle() != hInstance)
    {
        Attach(hInstance);
    }
    return *this;
}

inline BOOL MLibrary::Attach(HINSTANCE hInstance)
{
    FreeLibrary();
    m_hInstance = hInstance;
#ifndef NDEBUG
    TCHAR szFileName[MAX_PATH];
    assert(::GetModuleFileName(m_hInstance, szFileName, MAX_PATH));
#endif
    return m_hInstance != NULL;
}

inline HINSTANCE MLibrary::Detach()
{
    HINSTANCE hInstance = m_hInstance;
    m_hInstance = NULL;
    return hInstance;
}

inline HINSTANCE MLibrary::Handle() const
{
    return (this ? m_hInstance : NULL);
}

inline BOOL MLibrary::LoadLibrary(LPCTSTR pszFileName)
{
    return Attach(::LoadLibrary(pszFileName));
}

inline BOOL MLibrary::LoadLibraryEx(LPCTSTR pszFileName, DWORD dwFlags)
{
    return Attach(::LoadLibraryEx(pszFileName, NULL, dwFlags));
}

inline BOOL MLibrary::LoadLocalLibrary(LPCTSTR pszFileName)
{
    return Attach(LoadLocalLibraryDx(pszFileName));
}

inline BOOL MLibrary::LoadLocalLibraryEx(LPCTSTR pszFileName, DWORD dwFlags)
{
    return Attach(LoadLocalLibraryDx(pszFileName, dwFlags));
}

inline BOOL MLibrary::LoadSystemLibrary(LPCTSTR pszFileName)
{
    return Attach(LoadSystemLibraryDx(pszFileName));
}

inline BOOL MLibrary::LoadSystemLibraryEx(LPCTSTR pszFileName, DWORD dwFlags)
{
    return Attach(LoadSystemLibraryDx(pszFileName, dwFlags));
}

inline BOOL MLibrary::FreeLibrary()
{
    if (m_hInstance)
    {
        BOOL bOK = ::FreeLibrary(m_hInstance);
        m_hInstance = NULL;
        return bOK;
    }
    return FALSE;
}

inline FARPROC MLibrary::GetProcAddress(LPCSTR pszProcName)
{
    assert(Handle());
    return ::GetProcAddress(Handle(), pszProcName);
}

inline BOOL MLibrary::GetModuleHandle(LPCTSTR pszFileName)
{
    return Attach(::GetModuleHandle(pszFileName));
}

inline BOOL MLibrary::GetModuleFileName(LPTSTR pszFileName, DWORD cch/* = MAX_PATH*/)
{
    return ::GetModuleFileName(Handle(), pszFileName, cch);
}

inline bool MLibrary::operator!() const
{
    return Handle() == NULL;
}

inline MLibrary::operator HINSTANCE() const
{
    return Handle();
}

#if (_WIN32_IE >= 0x0501)
    inline HRESULT MLibrary::GetDllVersion(DLLVERSIONINFO2 *info)
    {
        return MLibrary::GetDllVersion(reinterpret_cast<DLLVERSIONINFO *>(info));
    }
#endif

inline HRESULT GetDllVersionDx(LPCTSTR pszDLL, DLLVERSIONINFO* info)
{
    assert(info);
    MLibrary lib(pszDLL);
    return lib.GetDllVersion(info);
}

#if (_WIN32_IE >= 0x0501)
    inline HRESULT GetDllVersion2Dx(LPCTSTR pszDLL, DLLVERSIONINFO2* info)
    {
        assert(info);
        MLibrary lib(pszDLL);
        return lib.GetDllVersion(info);
    }
#endif

inline HICON MLibrary::LoadIcon(LPCTSTR pszName)
{
    return ::LoadIcon(Handle(), pszName);
}

inline HICON MLibrary::LoadIcon(UINT nID)
{
    return LoadIcon(MAKEINTRESOURCE(nID));
}

inline HCURSOR MLibrary::LoadCursor(LPCTSTR pszName)
{
    return ::LoadCursor(Handle(), pszName);
}

inline HCURSOR MLibrary::LoadCursor(UINT nID)
{
    return LoadCursor(MAKEINTRESOURCE(nID));
}

inline HBITMAP MLibrary::LoadBitmap(LPCTSTR pszName)
{
    return ::LoadBitmap(Handle(), pszName);
}

inline HBITMAP MLibrary::LoadBitmap(UINT nID)
{
    return LoadBitmap(MAKEINTRESOURCE(nID));
}

inline HANDLE MLibrary::LoadImage(LPCTSTR pszName, UINT uType,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, UINT fuLoad/* = 0*/)
{
    return ::LoadImage(Handle(), pszName, uType, cxDesired, cyDesired, fuLoad);
}

inline HANDLE MLibrary::LoadImage(UINT nID, UINT uType,
    INT cxDesired/* = 0*/, INT cyDesired/* = 0*/, UINT fuLoad/* = 0*/)
{
    return LoadImage(MAKEINTRESOURCE(nID), uType, cxDesired, cyDesired, fuLoad);
}

inline HMENU MLibrary::LoadMenu(LPCTSTR pszName)
{
    assert(Handle());
    return ::LoadMenu(Handle(), pszName);
}

inline HMENU MLibrary::LoadMenu(UINT nID)
{
    return LoadMenu(MAKEINTRESOURCE(nID));
}

inline INT MLibrary::LoadString(UINT nID, LPTSTR pszBuffer, INT cchBuffer)
{
    assert(Handle());
    return ::LoadString(Handle(), nID, pszBuffer, cchBuffer);
}

inline HACCEL MLibrary::LoadAccelerators(LPCTSTR pszName)
{
    assert(Handle());
    return ::LoadAccelerators(Handle(), pszName);
}

inline HACCEL MLibrary::LoadAccelerators(UINT nID)
{
    assert(Handle());
    return LoadAccelerators(MAKEINTRESOURCE(nID));
}

inline HRSRC MLibrary::FindResource(LPCTSTR pszName, LPCTSTR pszType)
{
    return ::FindResource(Handle(), pszName, pszType);
}

inline HRSRC MLibrary::FindResource(LPCTSTR pszName, UINT nType)
{
    return FindResource(pszName, MAKEINTRESOURCE(nType));
}

inline HRSRC MLibrary::FindResource(UINT nID, LPCTSTR pszType)
{
    return FindResource(MAKEINTRESOURCE(nID), pszType);
}

inline HRSRC MLibrary::FindResource(UINT nID, UINT nType)
{
    return FindResource(MAKEINTRESOURCE(nID), MAKEINTRESOURCE(nType));
}

inline HRSRC MLibrary::FindResourceEx(LPCTSTR pszName, LPCTSTR pszType, WORD wLanguage)
{
    return ::FindResourceEx(Handle(), pszName, pszType, wLanguage);
}

inline HRSRC MLibrary::FindResourceEx(LPCTSTR pszName, UINT nType, WORD wLanguage)
{
    return FindResourceEx(pszName, MAKEINTRESOURCE(nType), wLanguage);
}

inline HRSRC MLibrary::FindResourceEx(UINT nID, LPCTSTR pszType, WORD wLanguage)
{
    return FindResourceEx(MAKEINTRESOURCE(nID), pszType, wLanguage);
}

inline HRSRC MLibrary::FindResourceEx(UINT nID, UINT nType, WORD wLanguage)
{
    return FindResourceEx(MAKEINTRESOURCE(nID), MAKEINTRESOURCE(nType), wLanguage);
}

inline HGLOBAL MLibrary::LoadResource(HRSRC hRsrc)
{
    return ::LoadResource(Handle(), hRsrc);
}

inline DWORD MLibrary::SizeofResource(HRSRC hRsrc)
{
    assert(Handle());
    return ::SizeofResource(Handle(), hRsrc);
}

inline HICON MLibrary::LoadSmallIcon(LPCTSTR pszName)
{
    return (HICON)LoadImage(pszName, IMAGE_ICON,
        ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON),
        0);
}

inline HICON MLibrary::LoadSmallIcon(UINT nID)
{
    return (HICON)LoadImage(MAKEINTRESOURCE(nID), IMAGE_ICON,
        ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON),
        0);
}

template <typename T_PROC>
inline BOOL MLibrary::GetProcAddress(LPCSTR pszProcName, T_PROC& proc)
{
    proc = (T_PROC)GetProcAddress(pszProcName);
    return proc != NULL;
}

inline HINSTANCE LoadLocalLibraryDx(LPCTSTR pszFileName)
{
    TCHAR szPath[MAX_PATH];
    ::GetModuleFileName(NULL, szPath, MAX_PATH);
    #ifdef UNICODE
        LPWSTR pch = wcsrchr(szPath, L'\\');
    #else
        LPSTR pch = reinterpret_cast<LPSTR>(
            _mbsrchr(reinterpret_cast<LPBYTE>(szPath), '\\'));
    #endif
    assert(pch != NULL);
    pch++;
    lstrcpy(pch, pszFileName);
    HINSTANCE hInstance = ::LoadLibrary(szPath);
    return hInstance;
}

inline HINSTANCE LoadSystemLibraryDx(LPCTSTR pszFileName)
{
    TCHAR szPath[MAX_PATH];
    ::GetSystemDirectory(szPath, MAX_PATH);
    lstrcat(szPath, TEXT("\\"));
    lstrcat(szPath, pszFileName);
    HINSTANCE hInstance = ::LoadLibrary(szPath);
    return hInstance;
}

inline HINSTANCE LoadLocalLibraryDx(LPCTSTR pszFileName, DWORD dwFlags)
{
    TCHAR szPath[MAX_PATH];
    ::GetModuleFileName(NULL, szPath, MAX_PATH);
    #ifdef UNICODE
        LPWSTR pch = wcsrchr(szPath, L'\\');
    #else
        LPSTR pch = reinterpret_cast<LPSTR>(
            _mbsrchr(reinterpret_cast<LPBYTE>(szPath), '\\'));
    #endif
    assert(pch != NULL);
    pch++;
    lstrcpy(pch, pszFileName);
    HINSTANCE hInstance = ::LoadLibraryEx(szPath, NULL, dwFlags);
    return hInstance;
}

inline HINSTANCE LoadSystemLibraryDx(LPCTSTR pszFileName, DWORD dwFlags)
{
    TCHAR szPath[MAX_PATH];
    ::GetSystemDirectory(szPath, MAX_PATH);
    lstrcat(szPath, TEXT("\\"));
    lstrcat(szPath, pszFileName);
    HINSTANCE hInstance = ::LoadLibraryEx(szPath, NULL, dwFlags);
    return hInstance;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MLIBRARY_HPP_
