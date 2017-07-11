// MFile.hpp -- Win32API file or pipe wrapper                  -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MFILE_HPP_
#define MZC4_MFILE_HPP_     4   /* Version 4 */

class MFile;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert
#include <cstring>          // strlen, wcslen
#include <mbstring.h>       // _mbsrchr

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

// FootmarkDx and FootmarkThisDx
#ifndef FootmarkDx
    #define FootmarkDx()
#endif
#ifndef FootmarkThisDx
    #define FootmarkThisDx()
#endif

////////////////////////////////////////////////////////////////////////////

class MFile
{
public:
    HANDLE m_hFile;

public:
    MFile();
    MFile(HANDLE hFile);
    MFile(LPCTSTR pszFileName, BOOL bOutput = FALSE,
          DWORD dwFILE_SHARE_ = FILE_SHARE_READ);
    virtual ~MFile();

    operator HANDLE() const;
    PHANDLE operator&();

    bool operator!() const;
    bool operator==(HANDLE hFile) const;
    bool operator!=(HANDLE hFile) const;
    bool operator==(const MFile& file) const;
    bool operator!=(const MFile& file) const;

    MFile& operator=(HANDLE hFile);
    BOOL Attach(HANDLE hFile);
    HANDLE Detach();
    HANDLE Handle() const;
    BOOL CloseHandle();

    BOOL DuplicateHandle(PHANDLE phFile, BOOL bInherit);
    BOOL DuplicateHandle(PHANDLE phFile, BOOL bInherit,
                         DWORD dwDesiredAccess);
    DWORD WaitForSingleObject(DWORD dwTimeout = INFINITE);

    BOOL PeekNamedPipe(LPVOID pBuffer = NULL, DWORD cbBuffer = 0,
                       LPDWORD pcbRead = NULL, LPDWORD pcbAvail = NULL,
                       LPDWORD pBytesLeft = NULL);
    BOOL ReadFile(LPVOID pBuffer, DWORD cbToRead, LPDWORD pcbRead,
                  LPOVERLAPPED pOverlapped = NULL);
    BOOL WriteFile(LPCVOID pBuffer, DWORD cbToWrite, LPDWORD pcbWritten,
                   LPOVERLAPPED pOverlapped = NULL);
    BOOL WriteSzA(LPCSTR psz, LPDWORD pcbWritten,
                  LPOVERLAPPED pOverlapped = NULL);
    BOOL WriteSzW(LPCWSTR psz, LPDWORD pcbWritten,
                  LPOVERLAPPED pOverlapped = NULL);
    BOOL WriteSz(LPCTSTR psz, LPDWORD pcbWritten,
                 LPOVERLAPPED pOverlapped = NULL);

    BOOL         WriteBinary(LPCVOID pv, DWORD cb);
    BOOL         WriteSzA(LPCSTR psz);
    BOOL         WriteSzW(LPCWSTR psz);
    BOOL         WriteSz(LPCTSTR psz);
    BOOL __cdecl WriteFormatA(LPCSTR pszFormat, ...);
    BOOL __cdecl WriteFormatW(LPCWSTR pszFormat, ...);
    BOOL __cdecl WriteFormat(LPCTSTR pszFormat, ...);

    BOOL GetStdHandle(DWORD dwSTD_);
    BOOL GetStdIn();
    BOOL GetStdOut();
    BOOL GetStdErr();
    BOOL SetStdHandle(DWORD dwSTD_) const;
    BOOL SetStdIn() const;
    BOOL SetStdOut() const;
    BOOL SetStdErr() const;

    BOOL OpenFileForInput(LPCTSTR pszFileName,
                          DWORD dwFILE_SHARE_ = FILE_SHARE_READ);
    BOOL OpenFileForOutput(LPCTSTR pszFileName,
                           DWORD dwFILE_SHARE_ = FILE_SHARE_READ);
    BOOL OpenFileForRandom(LPCTSTR pszFileName,
                           DWORD dwFILE_SHARE_ = FILE_SHARE_READ);
    BOOL OpenFileForAppend(LPCTSTR pszFileName,
                           DWORD dwFILE_SHARE_ = FILE_SHARE_READ);

    BOOL CreateFile(LPCTSTR pszFileName, DWORD dwDesiredAccess,
                    DWORD dwShareMode, LPSECURITY_ATTRIBUTES pSA,
                    DWORD dwCreationDistribution,
                    DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
                    HANDLE hTemplateFile = NULL);
    DWORD GetFileSize(LPDWORD pdwHighPart = NULL) const;
    DWORDLONG GetFileSize64() const;
    BOOL SetEndOfFile();
    DWORD SetFilePointer(LONG nDeltaLow, PLONG pnDeltaHigh = NULL,
                         DWORD dwOrigin = FILE_BEGIN);
    VOID SeekToBegin();
    DWORD SeekToEnd();
    BOOL FlushFileBuffers();
    BOOL GetFileTime(LPFILETIME pftCreate = NULL,
                     LPFILETIME pftLastAccess = NULL,
                     LPFILETIME pftLastWrite = NULL) const;

    BOOL GetFileInformationByHandle(LPBY_HANDLE_FILE_INFORMATION info);
    DWORD GetFileType() const;

    BOOL LockFile(DWORD dwFileOffsetLow, DWORD dwFileOffsetHigh,
                  DWORD dwNumberOfBytesToLockLow,
                  DWORD dwNumberOfBytesToLockHigh);
    BOOL LockFile(DWORDLONG dwlFileOffset, DWORDLONG dwlNumberOfBytesToLock);

    BOOL LockFileEx(DWORD dwFlags, DWORD dwReserved,
                    DWORD dwNumberOfBytesToLockLow,
                    DWORD dwNumberOfBytesToLockHigh,
                    LPOVERLAPPED lpOverlapped);
    BOOL LockFileEx(DWORD dwFlags, DWORD dwReserved,
                    DWORDLONG dwlNumberOfBytesToLock,
                    LPOVERLAPPED lpOverlapped);

    BOOL UnlockFile(DWORD dwFileOffsetLow, DWORD dwFileOffsetHigh,
                    DWORD dwNumberOfBytesToUnlockLow,
                    DWORD dwNumberOfBytesToUnlockHigh);
    BOOL UnlockFile(DWORDLONG dwFileOffset, DWORDLONG dwNumberOfBytesToUnlock);

    BOOL UnlockFileEx(DWORD dwReserved, DWORD dwNumberOfBytesToUnlockLow,
                      DWORD dwNumberOfBytesToUnlockHigh,
                      LPOVERLAPPED lpOverlapped);
    BOOL UnlockFileEx(DWORD dwReserved, DWORDLONG dwlNumberOfBytesToUnlock,
                      LPOVERLAPPED lpOverlapped);

    BOOL ReadFileEx(LPVOID pBuffer, DWORD cbToRead, LPOVERLAPPED pOverlapped,
                    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
    BOOL WriteFileEx(LPCVOID pBuffer, DWORD cbToWrite, LPOVERLAPPED pOverlapped,
                     LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

    static HANDLE CloneHandleDx(HANDLE hFile);

private:
    // NOTE: MFile is not copyable
    MFile(const MFile& file);
    MFile& operator=(const MFile& file);
};

////////////////////////////////////////////////////////////////////////////
// path

BOOL PathExistsDx(LPCTSTR psz);
DWORD GetFullPathNameDx(
    LPCTSTR pszPath, DWORD cchBuff, LPTSTR pszFull, LPTSTR *pFilePart = NULL);

////////////////////////////////////////////////////////////////////////////
// directory

BOOL DirExistsDx(LPCTSTR psz);
BOOL CreateDirectoryRecursiveDx(LPCTSTR pszPath, BOOL fForce = FALSE);
BOOL DeleteDirectoryDx(LPCTSTR pszDir);

////////////////////////////////////////////////////////////////////////////
// file

BOOL FileExistsDx(LPCTSTR psz);
LPBYTE GetFileContentsDx(LPCTSTR pszFile, LPDWORD pdwSize = NULL);
BOOL PutFileContentsDx(LPCTSTR pszFile, LPCVOID pvContents, DWORD dwSize);
BOOL PutFileContentsDx(LPCTSTR pszFile, LPCTSTR psz);
BOOL MoveFileDx(LPCTSTR pszExistingFile, LPCTSTR pszNewFile);
BOOL MoveFileExDx(LPCTSTR pszExistingFile, LPCTSTR pszNewFile, DWORD dwFlags);
BOOL CopyFileDx(LPCTSTR pszExistingFile, LPCTSTR pszNewFile,
                 BOOL bFailIfExists = FALSE);

////////////////////////////////////////////////////////////////////////////
// file name extension

LPSTR FindDotExtDxA(LPSTR pszPath);
LPWSTR FindDotExtDxW(LPWSTR pszPath);
LPSTR SetDotExtDxA(LPSTR pszPath, LPCSTR pszDotExt);
LPWSTR SetDotExtDxW(LPWSTR pszPath, LPCWSTR pszDotExt);

////////////////////////////////////////////////////////////////////////////
// drive

#ifdef MZC_WRAP_SHLWAPI
    #define AddBackslashDxA PathAddBackslashA
    #define AddBackslashDxW PathAddBackslashW
    #define RemoveBackslashDxA PathRemoveBackslashA
    #define RemoveBackslashDxW PathRemoveBackslashW
    #define FindFileNameDxA PathFindFileNameA
    #define FindFileNameDxW PathFindFileNameW
#else
    VOID AddBackslashDxA(LPSTR pszPath);
    VOID AddBackslashDxW(LPWSTR pszPath);
    VOID RemoveBackslashDxA(LPSTR pszPath);
    VOID RemoveBackslashDxW(LPWSTR pszPath);
    LPSTR FindFileNameDxA(LPSTR pszPath);
    LPWSTR FindFileNameDxW(LPWSTR pszPath);
#endif

#ifdef UNICODE
    #define AddBackslashDx AddBackslashDxW
    #define RemoveBackslashDx RemoveBackslashDxW
    #define FindFileNameDx FindFileNameDxW
    #define FindDotExtDx FindDotExtDxW
#else
    #define AddBackslashDx AddBackslashDxA
    #define RemoveBackslashDx RemoveBackslashDxA
    #define FindFileNameDx FindFileNameDxA
    #define FindDotExtDx FindDotExtDxA
#endif

////////////////////////////////////////////////////////////////////////////

inline MFile::MFile() : m_hFile(INVALID_HANDLE_VALUE)
{
}

inline MFile::MFile(HANDLE hFile) : m_hFile(hFile)
{
}

inline MFile::MFile(LPCTSTR pszFileName, BOOL bOutput/* = FALSE*/,
                        DWORD dwFILE_SHARE_/* = FILE_SHARE_READ*/)
    : m_hFile(INVALID_HANDLE_VALUE)
{
    if (bOutput)
        OpenFileForOutput(pszFileName, dwFILE_SHARE_);
    else
        OpenFileForInput(pszFileName, dwFILE_SHARE_);
}

inline /*virtual*/ MFile::~MFile()
{
    if (m_hFile != INVALID_HANDLE_VALUE && m_hFile != NULL)
        CloseHandle();
}

inline HANDLE MFile::Handle() const
{
    if (this == NULL)
        return INVALID_HANDLE_VALUE;
    if (m_hFile == NULL)
        return INVALID_HANDLE_VALUE;
    return m_hFile;
}

inline MFile::operator HANDLE() const
{
    return Handle();
}

inline PHANDLE MFile::operator&()
{
    return &m_hFile;
}

inline bool MFile::operator!() const
{
    HANDLE hFile = Handle();
    return hFile == INVALID_HANDLE_VALUE || hFile == NULL;
}

inline bool MFile::operator==(HANDLE hFile) const
{
    return Handle() == hFile;
}

inline bool MFile::operator!=(HANDLE hFile) const
{
    return Handle() != hFile;
}

inline bool MFile::operator==(const MFile& file) const
{
    return Handle() == file.Handle();
}

inline bool MFile::operator!=(const MFile& file) const
{
    return Handle() != file.Handle();
}

inline BOOL MFile::OpenFileForInput(
    LPCTSTR pszFileName, DWORD dwFILE_SHARE_/* = FILE_SHARE_READ*/)
{
    return MFile::CreateFile(pszFileName, GENERIC_READ,
        dwFILE_SHARE_, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

inline BOOL MFile::OpenFileForOutput(
    LPCTSTR pszFileName, DWORD dwFILE_SHARE_/* = FILE_SHARE_READ*/)
{
    return MFile::CreateFile(pszFileName, GENERIC_WRITE,
        dwFILE_SHARE_, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

inline BOOL MFile::OpenFileForRandom(
    LPCTSTR pszFileName, DWORD dwFILE_SHARE_/* = FILE_SHARE_READ*/)
{
    return MFile::CreateFile(pszFileName,
        GENERIC_READ | GENERIC_WRITE, dwFILE_SHARE_, NULL, OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);
}

inline DWORD MFile::WaitForSingleObject(
    DWORD dwTimeout/* = INFINITE*/)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::WaitForSingleObject(m_hFile, dwTimeout);
}

inline MFile& MFile::operator=(HANDLE hFile)
{
#ifndef NDEBUG
    BY_HANDLE_FILE_INFORMATION info;
    assert(hFile == INVALID_HANDLE_VALUE ||
        ::GetFileInformationByHandle(hFile, &info));
#endif
    if (m_hFile != hFile)
        Attach(hFile);
    return *this;
}

inline BOOL MFile::Attach(HANDLE hFile)
{
    if (m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE)
        CloseHandle();
    assert(hFile != NULL && hFile != INVALID_HANDLE_VALUE);
    assert(m_hFile == NULL || m_hFile == INVALID_HANDLE_VALUE);
#ifndef NDEBUG
    BY_HANDLE_FILE_INFORMATION info;
    assert(::GetFileInformationByHandle(hFile, &info));
#endif
    m_hFile = hFile;
    return m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE;
}

inline HANDLE MFile::Detach()
{
    HANDLE hFile = m_hFile;
    m_hFile = NULL;
    return hFile;
}

inline BOOL MFile::CloseHandle()
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    BOOL b = ::CloseHandle(m_hFile);
    m_hFile = INVALID_HANDLE_VALUE;
    return b;
}

inline BOOL MFile::PeekNamedPipe(
    LPVOID pBuffer/* = NULL*/,
    DWORD cbBuffer/* = 0*/,
    LPDWORD pcbRead/* = NULL*/,
    LPDWORD pcbAvail/* = NULL*/,
    LPDWORD pBytesLeft/* = NULL*/)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::PeekNamedPipe(m_hFile, pBuffer, cbBuffer,
        pcbRead, pcbAvail, pBytesLeft);
}

inline BOOL MFile::ReadFile(LPVOID pBuffer, DWORD cbToRead,
    LPDWORD pcbRead, LPOVERLAPPED pOverlapped/* = NULL*/)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::ReadFile(m_hFile, pBuffer, cbToRead, pcbRead, pOverlapped);
}

inline BOOL MFile::WriteFile(LPCVOID pBuffer, DWORD cbToWrite,
    LPDWORD pcbWritten, LPOVERLAPPED pOverlapped/* = NULL*/)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::WriteFile(
        m_hFile, pBuffer, cbToWrite, pcbWritten, pOverlapped);
}

inline BOOL MFile::WriteSzA(LPCSTR psz,
    LPDWORD pcbWritten, LPOVERLAPPED pOverlapped/* = NULL*/)
{
    using namespace std;
    SIZE_T size = strlen(psz) * sizeof(CHAR);
#ifdef _WIN64
    if (size > 0x7FFFFFFF)
        FootmarkThisDx();
#endif
    return WriteFile(psz, (DWORD)size, pcbWritten, pOverlapped);
}

inline BOOL MFile::WriteSzW(LPCWSTR psz,
    LPDWORD pcbWritten, LPOVERLAPPED pOverlapped/* = NULL*/)
{
    using namespace std;
    SIZE_T size = wcslen(psz) * sizeof(WCHAR);
#ifdef _WIN64
    if (size > 0x7FFFFFFF)
        FootmarkThisDx();
#endif
    return WriteFile(psz, (DWORD)size, pcbWritten, pOverlapped);
}

inline BOOL MFile::WriteSz(LPCTSTR psz,
    LPDWORD pcbWritten, LPOVERLAPPED pOverlapped/* = NULL*/)
{
    return WriteFile(psz, (DWORD)(lstrlen(psz) * sizeof(TCHAR)), pcbWritten, pOverlapped);
}

inline BOOL MFile::CreateFile(LPCTSTR pszFileName,
    DWORD dwDesiredAccess, DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES pSA, DWORD dwCreationDistribution,
    DWORD dwFlagsAndAttributes/* = FILE_ATTRIBUTE_NORMAL*/,
    HANDLE hTemplateFile/* = NULL*/)
{
    assert(m_hFile == NULL || m_hFile == INVALID_HANDLE_VALUE);
    return Attach(::CreateFile(pszFileName, dwDesiredAccess, dwShareMode,
                  pSA, dwCreationDistribution, dwFlagsAndAttributes, hTemplateFile));
}

inline DWORD MFile::SetFilePointer(
    LONG nDeltaLow,
    PLONG pnDeltaHigh/* = NULL*/,
    DWORD dwOrigin/* = FILE_BEGIN*/)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::SetFilePointer(m_hFile, nDeltaLow, pnDeltaHigh, dwOrigin);
}

inline DWORD MFile::SeekToEnd()
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return SetFilePointer(0, NULL, FILE_END);
}

inline VOID MFile::SeekToBegin()
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    SetFilePointer(0, NULL, FILE_BEGIN);
}

inline DWORD MFile::GetFileSize(LPDWORD pdwHighPart/* = NULL*/) const
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::GetFileSize(m_hFile, pdwHighPart);
}

inline DWORDLONG MFile::GetFileSize64() const
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    DWORD dwLow, dwHigh;
    dwLow = ::GetFileSize(m_hFile, &dwHigh);
    if (dwLow == 0xFFFFFFFF && ::GetLastError() != NO_ERROR)
        return 0;
    else
        return MAKELONGLONG(dwLow, dwHigh);
}

inline BOOL MFile::SetEndOfFile()
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::SetEndOfFile(m_hFile);
}

inline BOOL MFile::FlushFileBuffers()
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::FlushFileBuffers(m_hFile);
}

inline BOOL MFile::WriteSzA(LPCSTR psz)
{
    assert(psz);
    INT cb = lstrlenA(psz);
    return WriteBinary(psz, (DWORD) cb);
}

inline BOOL MFile::WriteSzW(LPCWSTR psz)
{
    assert(psz);
    INT cb = lstrlenW(psz) * sizeof(WCHAR);
    return WriteBinary(psz, (DWORD) cb);
}

inline BOOL MFile::WriteSz(LPCTSTR psz)
{
    assert(psz);
    INT cb = lstrlen(psz) * sizeof(TCHAR);
    return WriteBinary(psz, (DWORD) cb);
}

inline BOOL MFile::GetFileTime(
    LPFILETIME pftCreate/* = NULL*/,
    LPFILETIME pftLastAccess/* = NULL*/,
    LPFILETIME pftLastWrite/* = NULL*/) const
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::GetFileTime(m_hFile, pftCreate, pftLastAccess, pftLastWrite);
}

inline DWORD MFile::GetFileType() const
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::GetFileType(m_hFile);
}

inline BOOL MFile::GetFileInformationByHandle(LPBY_HANDLE_FILE_INFORMATION info)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::GetFileInformationByHandle(m_hFile, info);
}

inline BOOL MFile::LockFile(DWORD dwFileOffsetLow, DWORD dwFileOffsetHigh,
    DWORD dwNumberOfBytesToLockLow, DWORD dwNumberOfBytesToLockHigh)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::LockFile(m_hFile, dwFileOffsetLow, dwFileOffsetHigh,
        dwNumberOfBytesToLockLow, dwNumberOfBytesToLockHigh);
}

inline BOOL MFile::LockFile(DWORDLONG dwlFileOffset, DWORDLONG dwlNumberOfBytesToLock)
{
    return MFile::LockFile(LOLONG(dwlFileOffset), HILONG(dwlFileOffset),
        LOLONG(dwlNumberOfBytesToLock), HILONG(dwlNumberOfBytesToLock));
}

inline BOOL MFile::LockFileEx(DWORD dwFlags, DWORD dwReserved,
    DWORD dwNumberOfBytesToLockLow, DWORD dwNumberOfBytesToLockHigh,
    LPOVERLAPPED lpOverlapped)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::LockFileEx(m_hFile, dwFlags, dwReserved,
        dwNumberOfBytesToLockLow, dwNumberOfBytesToLockHigh, lpOverlapped);
}

inline BOOL MFile::LockFileEx(DWORD dwFlags, DWORD dwReserved,
    DWORDLONG dwlNumberOfBytesToLock, LPOVERLAPPED lpOverlapped)
{
    return MFile::LockFileEx(dwFlags, dwReserved,
        LOLONG(dwlNumberOfBytesToLock), HILONG(dwlNumberOfBytesToLock),
        lpOverlapped);
}

inline BOOL MFile::UnlockFile(DWORD dwFileOffsetLow, DWORD dwFileOffsetHigh,
    DWORD dwNumberOfBytesToUnlockLow, DWORD dwNumberOfBytesToUnlockHigh)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::UnlockFile(m_hFile, dwFileOffsetLow, dwFileOffsetHigh,
        dwNumberOfBytesToUnlockLow, dwNumberOfBytesToUnlockHigh);
}

inline BOOL MFile::UnlockFile(DWORDLONG dwFileOffset, DWORDLONG dwNumberOfBytesToUnlock)
{
    return MFile::UnlockFile(LOLONG(dwFileOffset), HILONG(dwFileOffset),
        LOLONG(dwNumberOfBytesToUnlock), HILONG(dwNumberOfBytesToUnlock));
}

inline BOOL MFile::UnlockFileEx(DWORD dwReserved, DWORD dwNumberOfBytesToUnlockLow,
    DWORD dwNumberOfBytesToUnlockHigh, LPOVERLAPPED lpOverlapped)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::UnlockFileEx(m_hFile, dwReserved, dwNumberOfBytesToUnlockLow,
        dwNumberOfBytesToUnlockHigh, lpOverlapped);
}

inline BOOL MFile::UnlockFileEx(DWORD dwReserved, DWORDLONG dwlNumberOfBytesToUnlock,
    LPOVERLAPPED lpOverlapped)
{
    return MFile::UnlockFileEx(dwReserved, LOLONG(dwlNumberOfBytesToUnlock),
        HILONG(dwlNumberOfBytesToUnlock), lpOverlapped);
}

inline BOOL MFile::ReadFileEx(LPVOID pBuffer, DWORD cbToRead, 
    LPOVERLAPPED pOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::ReadFileEx(m_hFile, pBuffer, cbToRead, pOverlapped, lpCompletionRoutine);
}

inline BOOL MFile::WriteFileEx(LPCVOID pBuffer, DWORD cbToWrite, 
    LPOVERLAPPED pOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    return ::WriteFileEx(m_hFile, pBuffer, cbToWrite, pOverlapped, lpCompletionRoutine);
}


inline BOOL MFile::GetStdHandle(DWORD dwSTD_)
{
    return Attach(::GetStdHandle(dwSTD_));
}

inline BOOL MFile::GetStdIn()
{
    return Attach(::GetStdHandle(STD_INPUT_HANDLE));
}

inline BOOL MFile::GetStdOut()
{
    return Attach(::GetStdHandle(STD_OUTPUT_HANDLE));
}

inline BOOL MFile::GetStdErr()
{
    return Attach(::GetStdHandle(STD_ERROR_HANDLE));
}

inline BOOL MFile::SetStdHandle(DWORD dwSTD_) const
{
    return ::SetStdHandle(dwSTD_, m_hFile);
}

inline BOOL MFile::SetStdIn() const
{
    return ::SetStdHandle(STD_INPUT_HANDLE, m_hFile);
}

inline BOOL MFile::SetStdOut() const
{
    return ::SetStdHandle(STD_OUTPUT_HANDLE, m_hFile);
}

inline BOOL MFile::SetStdErr() const
{
    return ::SetStdHandle(STD_ERROR_HANDLE, m_hFile);
}

////////////////////////////////////////////////////////////////////////////

inline BOOL PathExistsDx(LPCTSTR psz)
{
    assert(psz);
    DWORD attrs = ::GetFileAttributes(psz);
    return attrs != 0xFFFFFFFF;
}

inline BOOL FileExistsDx(LPCTSTR psz)
{
    assert(psz);
    DWORD attrs = ::GetFileAttributes(psz);
    return attrs != 0xFFFFFFFF && !(attrs & FILE_ATTRIBUTE_DIRECTORY);
}

inline BOOL DirExistsDx(LPCTSTR psz)
{
    assert(psz);
    DWORD attrs = ::GetFileAttributes(psz);
    return attrs != 0xFFFFFFFF && (attrs & FILE_ATTRIBUTE_DIRECTORY);
}

inline LPSTR SetDotExtDxA(LPSTR pszPath, LPCSTR pszDotExt)
{
    assert(pszPath);
    assert(pszDotExt);
    lstrcpyA(FindDotExtDxA(pszPath), pszDotExt);
    return pszPath;
}

inline LPWSTR SetDotExtDxW(LPWSTR pszPath, LPCWSTR pszDotExt)
{
    assert(pszPath);
    assert(pszDotExt);
    lstrcpyW(FindDotExtDxW(pszPath), pszDotExt);
    return pszPath;
}

inline BOOL CopyFileDx(LPCTSTR pszExistingFile, LPCTSTR pszNewFile,
                       BOOL bFailIfExists/* = FALSE*/)
{
    assert(pszExistingFile);
    assert(pszNewFile);
    return ::CopyFile(pszExistingFile, pszNewFile, bFailIfExists);
}

inline DWORD GetFullPathNameDx(
    LPCTSTR pszPath, DWORD cchBuff, LPTSTR pszFull, LPTSTR *pFilePart/* = NULL*/)
{
    assert(pszPath);
    assert(pszFull);
    return ::GetFullPathName(pszPath, cchBuff, pszFull, pFilePart);
}

inline BOOL MoveFileDx(LPCTSTR pszExistingFile, LPCTSTR pszNewFile)
{
    assert(pszExistingFile);
    assert(pszNewFile);
    return ::MoveFile(pszExistingFile, pszNewFile);
}

inline BOOL MoveFileExDx(LPCTSTR pszExistingFile, LPCTSTR pszNewFile, DWORD dwFlags)
{
    assert(pszExistingFile);
    assert(pszNewFile);
    return ::MoveFileEx(pszExistingFile, pszNewFile, dwFlags);
}

inline BOOL PutFileContentsDx(LPCTSTR pszFile, LPCTSTR psz)
{
    return PutFileContentsDx(pszFile, psz, lstrlen(psz) * sizeof(TCHAR));
}

#ifndef MZC_WRAP_SHLWAPI
    inline VOID AddBackslashDxA(LPSTR pszPath)
    {
        assert(pszPath);
        std::size_t cchPath = strlen(pszPath);
        if (cchPath == 0)
            return;
        LPSTR pchPrev = CharPrevA(pszPath, pszPath + cchPath);
        if (*pchPrev != '\\' && *pchPrev != '/')
        {
            pszPath[cchPath++] = '\\';
            pszPath[cchPath] = '\0';
        }
    }

    inline VOID AddBackslashDxW(LPWSTR pszPath)
    {
        assert(pszPath);
        std::size_t cchPath = wcslen(pszPath);
        if (cchPath == 0)
            return;
        LPWSTR pchPrev = pszPath + cchPath - 1;
        if (*pchPrev != L'\\' && *pchPrev != L'/')
        {
            pszPath[cchPath++] = L'\\';
            pszPath[cchPath] = L'\0';
        }
    }

    inline VOID RemoveBackslashDxA(LPSTR pszPath)
    {
        assert(pszPath);
        std::size_t cchPath = strlen(pszPath);
        if (cchPath == 0)
            return;
        LPSTR pchPrev = CharPrevA(pszPath, pszPath + cchPath);
        if (*pchPrev == '\\' || *pchPrev == '/')
            *pchPrev = '\0';
    }

    inline VOID RemoveBackslashDxW(LPWSTR pszPath)
    {
        assert(pszPath);
        std::size_t cchPath = wcslen(pszPath);
        if (cchPath == 0)
            return;
        LPWSTR pchPrev = pszPath + cchPath - 1;
        if (*pchPrev == L'\\' || *pchPrev == L'/')
            *pchPrev = L'\0';
    }

    inline LPSTR FindFileNameDxA(LPSTR pszPath)
    {
        assert(pszPath);
        #ifdef ANSI
            LPSTR pch1 = strrchr(pszPath, '\\');
            LPSTR pch2 = strrchr(pszPath, '/');
        #else
            LPSTR pch1 = reinterpret_cast<LPSTR>(
                _mbsrchr(reinterpret_cast<LPBYTE>(pszPath), '\\'));
            LPSTR pch2 = reinterpret_cast<LPSTR>(
                _mbsrchr(reinterpret_cast<LPBYTE>(pszPath), '/'));
        #endif
        if (pch1 == NULL && pch2 == NULL)
            return pszPath;
        if (pch1 == NULL)
            return pch2 + 1;
        if (pch2 == NULL)
            return pch1 + 1;
        if (pch1 < pch2)
            return pch2 + 1;
        else
            return pch1 + 1;
    }

    inline LPWSTR FindFileNameDxW(LPWSTR pszPath)
    {
        assert(pszPath);
        LPWSTR pch1 = wcsrchr(pszPath, L'\\');
        LPWSTR pch2 = wcsrchr(pszPath, L'/');
        if (pch1 == NULL && pch2 == NULL)
            return pszPath;
        if (pch1 == NULL)
            return pch2 + 1;
        if (pch2 == NULL)
            return pch1 + 1;
        if (pch1 < pch2)
            return pch2 + 1;
        else
            return pch1 + 1;
    }
#endif  // ndef MZC_WRAP_SHLWAPI

inline LPSTR FindDotExtDxA(LPSTR pszPath)
{
    assert(pszPath);
    pszPath = FindFileNameDxA(pszPath);
    #ifdef ANSI
        LPSTR pch = strrchr(pszPath, '.');
    #else
        LPSTR pch = reinterpret_cast<LPSTR>(
            _mbsrchr(reinterpret_cast<LPBYTE>(pszPath), '.'));
    #endif
    if (pch)
        return pch;
    else
        return pszPath + strlen(pszPath);
}

inline LPWSTR FindDotExtDxW(LPWSTR pszPath)
{
    assert(pszPath);
    pszPath = FindFileNameDxW(pszPath);
    LPWSTR pch = wcsrchr(pszPath, L'.');
    if (pch)
        return pch;
    else
        return pszPath + lstrlenW(pszPath);
}

////////////////////////////////////////////////////////////////////////////

inline LPBYTE
GetFileContentsDx(LPCTSTR pszFile, LPDWORD pdwSize/* = NULL*/)
{
    assert(pszFile);

    HANDLE hFile;
    DWORD cbFile, cbRead, dwLastError;
    LPBYTE pb = NULL;

    if (pdwSize)
        *pdwSize = 0;

    hFile = ::CreateFile(pszFile, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        cbFile = ::GetFileSize(hFile, NULL);
        if (cbFile != 0xFFFFFFFF)
        {
            LPVOID pv = malloc((cbFile + 1) * sizeof(char));
            pb = reinterpret_cast<LPBYTE>(pv);
            if (pb)
            {
                if (::ReadFile(hFile, pb, cbFile, &cbRead, NULL) &&
                    cbFile == cbRead)
                {
                    pb[cbFile] = 0;
                    if (pdwSize)
                        *pdwSize = cbFile;
                }
                else
                {
                    dwLastError = ::GetLastError();
                    free(pb);
                    pb = NULL;
                }
            }
            else
                dwLastError = ERROR_OUTOFMEMORY;
        }
        else
            dwLastError = ::GetLastError();

        ::CloseHandle(hFile);
    }
    else
        dwLastError = ::GetLastError();

    if (pb == NULL)
    {
        FootmarkDx();
        ::SetLastError(dwLastError);
    }

    return pb;
}

inline BOOL
PutFileContentsDx(LPCTSTR pszFile, LPCVOID pvContents, DWORD dwSize)
{
    assert(pszFile);
    assert(pvContents || dwSize == 0);

    HANDLE hFile;
    DWORD cbWritten, dwLastError;
    BOOL bOK = FALSE;

    hFile = ::CreateFile(pszFile, GENERIC_WRITE, FILE_SHARE_READ, NULL,
        CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        if (::WriteFile(hFile, pvContents, dwSize, &cbWritten, NULL) &&
            dwSize == cbWritten)
        {
            if (::CloseHandle(hFile))
                bOK = TRUE;
            else
                dwLastError = ::GetLastError();
        }
        else
        {
            dwLastError = ::GetLastError();
            ::CloseHandle(hFile);
        }

        if (!bOK)
            ::DeleteFile(pszFile);
    }
    else
        dwLastError = ::GetLastError();

    if (!bOK)
    {
        FootmarkDx();
        ::SetLastError(dwLastError);
    }

    return bOK;
}

////////////////////////////////////////////////////////////////////////////

inline BOOL
CreateDirectoryRecursiveDx(LPCTSTR pszPath, BOOL fForce/* = FALSE*/)
{
    assert(pszPath);

    // check length
    if (lstrlen(pszPath) >= MAX_PATH)
    {
        ::SetLastError(ERROR_BUFFER_OVERFLOW);
        return FALSE;   // failure
    }

    // save it local to recurse
    TCHAR szPath[MAX_PATH];
    lstrcpyn(szPath, pszPath, MAX_PATH);
    RemoveBackslashDx(szPath);

    // does it exists?
    DWORD attrs = ::GetFileAttributes(szPath);
    if (attrs == 0xFFFFFFFF)
    {
retry:;
        // no, it doesn't. find the last separator
        LPTSTR pchLastSep = NULL;
        for(LPTSTR pch = szPath; *pch; pch = CharNext(pch))
        {
            if (*pch == TEXT('\\') || *pch == TEXT('/'))
                pchLastSep = pch;
        }

        if (pchLastSep != NULL)
        {
            // found sep; recurse the parent directory
            *pchLastSep = 0;
            if (CreateDirectoryRecursiveDx(szPath))
                return ::CreateDirectory(pszPath, NULL);

            return FALSE;   // failure
        }
        else
        {
            // no sep; a create
            return ::CreateDirectory(szPath, NULL);
        }
    }

    if (!(attrs & FILE_ATTRIBUTE_DIRECTORY))
    {
        // shit, same name non-directory file exists
        if (!fForce)
        {
            ::SetLastError(ERROR_ALREADY_EXISTS);
            return FALSE;
        }

        // don't disturb us or delete you by force of arms!
        if (!::DeleteFile(szPath))
            return FALSE;   // OMG, failure!

        goto retry;
    }

    return TRUE;    // the directory exists. success.
}

inline BOOL IsDotsDx_(LPCTSTR psz)
{
    assert(psz);
    return (psz[0] == TEXT('.') &&
        (psz[1] == TEXT('\0') || (psz[1] == TEXT('.') && psz[2] == TEXT('\0')))
    );
}

inline BOOL DeleteDirectoryDx(LPCTSTR pszDir)
{
    assert(pszDir);

    DWORD attrs;
    TCHAR szDirOld[MAX_PATH];
    HANDLE hFind;
    WIN32_FIND_DATA find;

    attrs = ::GetFileAttributes(pszDir);
    if (attrs == 0xFFFFFFFF || !(attrs & FILE_ATTRIBUTE_DIRECTORY))
        return FALSE;

    ::GetCurrentDirectory(MAX_PATH, szDirOld);
    if (!::SetCurrentDirectory(pszDir))
        return FALSE;

    hFind = ::FindFirstFile(TEXT("*"), &find);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!IsDotsDx_(find.cFileName))
            {
                if (find.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
                {
                    // ignore
                }
                else
                {
                    if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                        DeleteDirectoryDx(find.cFileName);
                    else
                        ::DeleteFile(find.cFileName);
                }
            }
        } while(::FindNextFile(hFind, &find));
        ::FindClose(hFind);
    }
    ::SetCurrentDirectory(szDirOld);

    return ::RemoveDirectory(pszDir);
}

////////////////////////////////////////////////////////////////////////////

inline BOOL MFile::DuplicateHandle(PHANDLE phFile, BOOL bInherit)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    HANDLE hProcess = ::GetCurrentProcess();
    return ::DuplicateHandle(hProcess, m_hFile, hProcess, phFile, 0,
        bInherit, DUPLICATE_SAME_ACCESS);
}

inline BOOL MFile::DuplicateHandle(
    PHANDLE phFile, BOOL bInherit, DWORD dwDesiredAccess)
{
    assert(m_hFile != NULL && m_hFile != INVALID_HANDLE_VALUE);
    HANDLE hProcess = ::GetCurrentProcess();
    return ::DuplicateHandle(hProcess, m_hFile, hProcess, phFile,
        dwDesiredAccess, bInherit, 0);
}

inline BOOL __cdecl MFile::WriteFormatA(LPCSTR pszFormat, ...)
{
    assert(pszFormat);
    assert(strlen(pszFormat) < 1024);
    va_list argList;
    CHAR sz[1024];
    va_start(argList, pszFormat);
    wvsprintfA(sz, pszFormat, argList);
    BOOL b = WriteSzA(sz);
    va_end(argList);
    return b;
}

inline BOOL __cdecl MFile::WriteFormatW(LPCWSTR pszFormat, ...)
{
    assert(pszFormat);
    assert(wcslen(pszFormat) < 1024);
    va_list argList;
    WCHAR sz[1024];
    va_start(argList, pszFormat);
    wvsprintfW(sz, pszFormat, argList);
    BOOL b = WriteSzW(sz);
    va_end(argList);
    return b;
}

inline BOOL __cdecl MFile::WriteFormat(LPCTSTR pszFormat, ...)
{
    assert(pszFormat);
    assert(lstrlen(pszFormat) < 1024);
    va_list argList;
    TCHAR sz[1024];
    va_start(argList, pszFormat);
    wvsprintf(sz, pszFormat, argList);
    BOOL b = WriteSz(sz);
    va_end(argList);
    return b;
}

inline BOOL MFile::OpenFileForAppend(
    LPCTSTR pszFileName, DWORD dwFILE_SHARE_/* = FILE_SHARE_READ*/)
{
    assert(pszFileName);
    BOOL bExisted = (::GetFileAttributes(pszFileName) != 0xFFFFFFFF);
    if (!MFile::CreateFile(pszFileName, GENERIC_READ | GENERIC_WRITE,
        dwFILE_SHARE_, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL))
        return FALSE;
    if (SetFilePointer(0, NULL, FILE_END) == 0xFFFFFFFF)
    {
        assert(false);
        CloseHandle();
        if (!bExisted)
            ::DeleteFile(pszFileName);
        return FALSE;
    }
    return TRUE;
}

inline BOOL MFile::WriteBinary(LPCVOID pv, DWORD cb)
{
    assert(pv || cb == 0);
    const BYTE *pb = reinterpret_cast<const BYTE *>(pv);
    DWORD cbWritten;
    while (cb != 0)
    {
        if (WriteFile(pb, cb, &cbWritten))
        {
            cb -= cbWritten;
            pb += cbWritten;
        }
        else
            break;
    }
    return (cb == 0) && FlushFileBuffers();
}

inline /*static*/ HANDLE MFile::CloneHandleDx(HANDLE hFile)
{
    if (hFile == INVALID_HANDLE_VALUE || hFile == NULL)
        return INVALID_HANDLE_VALUE;

    HANDLE hProcess = ::GetCurrentProcess();
    HANDLE hDup = INVALID_HANDLE_VALUE;
    ::DuplicateHandle(hProcess, hFile, hProcess, &hDup, 0,
                      FALSE, DUPLICATE_SAME_ACCESS);
    return hDup;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MFILE_HPP_
