/* MFileAPI.h -- filesystem manipulator                       -*- C++ -*-
 * This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
 */

#ifndef MZC4_MFILEAPI_H_
#define MZC4_MFILEAPI_H_        25  /* Version 25 */

/*
 * mpath_... functions
 * mdir_... functions
 * mfile_... functions
 */

/* TODO: support MSDOS, link, shortcut */
/**************************************************************************/

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#endif
#if !defined(UNICODE) && defined(_UNICODE)
    #define UNICODE
#endif

/* C99 and C++11 */
#if __STDC_VERSION__ >= 199901L && !defined(C99)
    #define C99             1
#endif
#if __cplusplus >= 201103L && !defined(CXX11)
    #define CXX11           1
#endif

/* Some C compilers don't support inline keyword. Use __inline instread if so. */
#ifndef MZC_INLINE
    #ifdef __cplusplus
        #define MZC_INLINE inline
    #elif (__STDC_VERSION__ >= 199901L)
        #define MZC_INLINE inline
    #else
        #define MZC_INLINE __inline
    #endif
#endif

/* <stdbool.h> and <stdint.h> */
#ifdef __cplusplus
    #ifdef CXX11
        #include <cstdint>
    #else
        #include "pstdint.h"
    #endif
#else
    #if C99
        #include <stdbool.h>
        #include <stdint.h>
    #else
        #include "pstdbool.h"
        #include "pstdint.h"
    #endif
#endif

#ifndef USING_NAMESPACE_STD
    #ifdef __cplusplus
        #define USING_NAMESPACE_STD     using namespace std
    #else
        #define USING_NAMESPACE_STD     /*empty*/
    #endif
#endif

#ifdef _WIN32
    #ifndef _INC_WINDOWS
        #include <windows.h>    /* Win32API */
    #endif
    #include <mbstring.h>       /* _mbsrchr */
    #include <tchar.h>          /* generic text mapping */

    #ifndef MChar
        typedef TCHAR MChar;
        #define MChar MChar
    #endif
#else
    #ifdef __cplusplus
        #include <cstdlib>
        #include <cstdio>
    #else
        #include <stdlib.h>
        #include <stdio.h>
    #endif

    #include <sys/stat.h>
    #include <sys/types.h>

    #ifdef MSDOS
        #include <direct.h>
    #else
        #include <unistd.h>
        #include <dirent.h>     /* opendir, ... */
    #endif

    #ifndef MChar
        typedef char MChar;
        #define MChar MChar
    #endif

    #ifndef MAX_PATH
        #ifdef PATH_MAX
            #define MAX_PATH    PATH_MAX
        #else
            #define MAX_PATH    260
        #endif
    #endif

    #ifndef TEXT
        #define TEXT(x)     x
    #endif
#endif

#ifdef __cplusplus
    #include <cassert>          /* assert */
    #include <cstring>          /* strlen, wcslen */
    #include <string>           /* for std::string */
    #include <vector>           /* for std::vector */
    #include <algorithm>        /* for std::sort */
#else
    #include <assert.h>
    #include <string.h>
#endif

#ifndef optional_
    #ifdef __cplusplus
        #define optional_(def) = def
    #else
        #define optional_(def)      /*empty*/
    #endif
#endif

/**************************************************************************/
/* pathname */

bool mpath_Exists(const MChar *pathname);
MChar *mpath_GetFullPath(MChar *full, const MChar *relative);
MChar *mpath_AddSep(MChar *pathname);
MChar *mpath_RemoveSep(MChar *pathname);
MChar *mpath_FindTitle(MChar *pathname);
MChar *mpath_SetTitle(MChar *pathname, const MChar *title);
MChar *mpath_FindDotExt(MChar *pathname);
MChar *mpath_SetDotExt(MChar *pathname, const MChar *dot_ext);
bool mpath_IsDots(const MChar *name);
void mpath_BackslashToSlash(MChar *pathname);
void mpath_SlashToBackslash(MChar *pathname);

/**************************************************************************/
/* directory */

bool mdir_Exists(const MChar *pathname);
bool mdir_Create(const MChar *pathname);
bool mdir_Remove(const MChar *pathname);
bool mdir_Get(MChar *pathname, size_t maxbuf optional_(MAX_PATH));
bool mdir_Set(const MChar *pathname);
bool mdir_CreateRecurse(const MChar *pathname, bool fForce optional_(false));

#ifndef MSDOS
    #ifdef _WIN32
        typedef WIN32_FIND_DATA     MZC_DIR_INFO;
        typedef HANDLE              MZC_DIR_P;
    #else
        typedef struct MZC_DIR_INFO
        {
            MChar   cFileName[MAX_PATH];
        } MZC_DIR_INFO;
        typedef DIR *MZC_DIR_P;
    #endif

    MZC_DIR_P mdir_FindFirstItem(const MChar *pathname, MZC_DIR_INFO *info);
    bool      mdir_FindNextItem(MZC_DIR_P dirp, MZC_DIR_INFO *info);
    bool      mdir_FindClose(MZC_DIR_P dirp);

    bool mdir_Delete(const MChar *dir);

    #ifdef __cplusplus
        #ifndef MString
            typedef std::basic_string<MChar> MString;
        #endif
        bool mdir_GetItemList(const MChar *dirname, std::vector<MString>& items,
                              bool sort = true);
        bool mdir_GetFullPathList(const MChar *dirname, std::vector<MString>& paths,
                                  bool recursive = true, bool sort = true);
    #endif
#endif  /* ndef MSDOS */

/**************************************************************************/
/* file */

bool mfile_Exists(const MChar *filename);

uint8_t *
mfile_GetContents(const MChar *filename, size_t *psize optional_(NULL));
bool
mfile_PutContents(const MChar *filename, const void *pvContents, size_t size);

bool mfile_PutText(const MChar *filename, const MChar *psz);

bool mfile_Move(const MChar *existing_file, const MChar *new_file);
bool mfile_Copy(const MChar *existing_file, const MChar *new_file,
                bool bFailIfExists optional_(false));
bool mfile_Delete(const MChar *filename);

unsigned long mfile_GetSize(const MChar *filename, unsigned long *high);
uint64_t      mfile_GetSize64(const MChar *filename);

/**************************************************************************/

MZC_INLINE bool mpath_Exists(const MChar *pathname)
{
    USING_NAMESPACE_STD;
    assert(pathname);
#ifdef _WIN32
    DWORD attrs;
#else
    struct stat sbuf;
#endif

    assert(pathname);
#ifdef _WIN32
    attrs = GetFileAttributes(pathname);
    return (attrs != 0xFFFFFFFF);
#else
    return (stat(pathname, &sbuf) == 0);
#endif
}

MZC_INLINE bool mfile_Exists(const MChar *filename)
{
    USING_NAMESPACE_STD;
    assert(filename);
#ifdef _WIN32
    DWORD attrs;
#else
    struct stat sbuf;
#endif

    assert(filename);
#ifdef _WIN32
    attrs = GetFileAttributes(filename);
    return (attrs != 0xFFFFFFFF) && !(attrs & FILE_ATTRIBUTE_DIRECTORY);
#else
    if (stat(filename, &sbuf) == 0)
    {
        if ((sbuf.st_mode & S_IFMT) == S_IFREG)
            return true;
    }
    return false;
#endif
}

MZC_INLINE bool mdir_Exists(const MChar *pathname)
{
    USING_NAMESPACE_STD;
    assert(pathname);
#ifdef _WIN32
    DWORD attrs;
#else
    struct stat sbuf;
#endif

    assert(pathname);
#ifdef _WIN32
    attrs = GetFileAttributes(pathname);
    return (attrs != 0xFFFFFFFF) && (attrs & FILE_ATTRIBUTE_DIRECTORY);
#else
    if (stat(pathname, &sbuf) == 0)
    {
        if ((sbuf.st_mode & S_IFMT) == S_IFDIR)
            return true;
    }
    return false;
#endif
}

MZC_INLINE MChar *mpath_GetFullPath(MChar *full, const MChar *relative)
{
    USING_NAMESPACE_STD;
    assert(full);
    assert(relative);
#ifdef _WIN32
    GetFullPathName(relative, MAX_PATH, full, NULL);
    return full;
#else
    return realpath(relative, full);
#endif
}

MZC_INLINE bool mfile_Delete(const MChar *filename)
{
    USING_NAMESPACE_STD;
    assert(filename);
#ifdef _WIN32
    return !!DeleteFile(filename);
#elif defined(MSDOS)
    return remove(filename) == 0;
#else
    return unlink(filename) == 0;
#endif
}

MZC_INLINE uint64_t
mfile_GetSize64(const MChar *filename)
{
    USING_NAMESPACE_STD;
    assert(filename);
#ifdef _WIN32
    HANDLE hFile = CreateFile(filename, GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL,
        OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return (uint64_t)-1;

    DWORD low, high;
    low = GetFileSize(hFile, &high);
    CloseHandle(hFile);
    return low | ((uint64_t)high << 32);
#else
    struct stat st;
    if (stat(filename, &st))
        return (uint64_t)-1;
    return st.st_size;
#endif
}

MZC_INLINE unsigned long
mfile_GetSize(const MChar *filename, unsigned long *high)
{
    USING_NAMESPACE_STD;
    assert(filename);

    if (high)
        *high = 0;

#ifdef _WIN32
    HANDLE hFile = CreateFile(filename, GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL,
        OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return 0xFFFFFFFF;

    DWORD low = GetFileSize(hFile, high);
    CloseHandle(hFile);
    return low;
#else
    struct stat st;
    if (stat(filename, &st))
        return 0xFFFFFFFF;

    if (sizeof(st.st_size) >= 8 && st.st_size > 0xFFFFFFFF)
    {
        if (high)
        {
            *high = st.st_size >> 32;
            return (unsigned long)st.st_size;
        }
        return 0xFFFFFFFF;
    }

    return (unsigned long)st.st_size;
#endif
}

MZC_INLINE uint8_t *
mfile_GetContents(const MChar *filename, size_t *psize)
{
    USING_NAMESPACE_STD;
    uint8_t *pb = NULL;

#ifdef _WIN32
    HANDLE hFile;
    DWORD cbFile, cbRead;

    assert(filename);

    if (psize)
        *psize = 0;

    hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        cbFile = GetFileSize(hFile, NULL);
        if (cbFile != 0xFFFFFFFF)
        {
            LPVOID pv = malloc((cbFile + 3) * sizeof(char));
            pb = (uint8_t *)(pv);
            if (pb)
            {
                if (ReadFile(hFile, pb, cbFile, &cbRead, NULL) &&
                    cbFile == cbRead)
                {
                    pb[cbFile + 0] = 0;
                    pb[cbFile + 1] = 0;
                    pb[cbFile + 2] = 0;
                    if (psize)
                        *psize = cbFile;
                }
                else
                {
                    free(pb);
                    pb = NULL;
                }
            }
        }
        CloseHandle(hFile);
    }
#else
    FILE *fp;
    struct stat sbuf;

    assert(filename);

    if (psize)
        *psize = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL)
        return NULL;

    if (stat(filename, &sbuf) == 0)
    {
        pb = (uint8_t *)malloc(sbuf.st_size + 3);
        if (pb)
        {
            if (fread(pb, sbuf.st_size, 1, fp))
            {
                pb[sbuf.st_size + 0] = 0;
                pb[sbuf.st_size + 1] = 0;
                pb[sbuf.st_size + 2] = 0;
                if (psize)
                    *psize = sbuf.st_size;
            }
            else
            {
                free(pb);
                pb = NULL;
            }
        }
    }
    fclose(fp);
#endif

    return pb;
}

MZC_INLINE bool mfile_PutText(const MChar *filename, const MChar *str)
{
    USING_NAMESPACE_STD;
#ifdef _WIN32
    return mfile_PutContents(filename, str, _tcslen(str) * sizeof(MChar));
#else
    return mfile_PutContents(filename, str, strlen(str));
#endif
}

MZC_INLINE bool
mfile_PutContents(const MChar *filename, const void *pvContents, size_t size)
{
    USING_NAMESPACE_STD;
    bool bOK = false;

#ifdef _WIN32
    HANDLE hFile;
    DWORD cbWritten, dwSize = (DWORD)size;

    assert(filename);
    assert(pvContents || size == 0);

    hFile = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL,
        CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        if (WriteFile(hFile, pvContents, dwSize, &cbWritten, NULL) &&
            dwSize == cbWritten)
        {
            if (CloseHandle(hFile))
                bOK = true;
        }
        else
        {
            CloseHandle(hFile);
        }

        if (!bOK)
            DeleteFile(filename);
    }
#else
    FILE *fp;

    assert(filename);
    assert(pvContents || size == 0);

    fp = fopen(filename, "wb");
    if (fp)
    {
        if (fwrite(pvContents, size, 1, fp))
        {
            fclose(fp);
            bOK = true;
        }
        else
        {
            fclose(fp);
            mfile_Delete(filename);
        }
    }
#endif

    return bOK;
}

MZC_INLINE bool mdir_Create(const MChar *pathname)
{
    USING_NAMESPACE_STD;
#ifdef _WIN32
    return !!CreateDirectory(pathname, NULL);
#elif defined(MSDOS)
    return mkdir(pathname) == 0;
#else
    return mkdir(pathname, 0755) == 0;
#endif
}

MZC_INLINE bool
mfile_Move(const MChar *existing_file, const MChar *new_file)
{
    USING_NAMESPACE_STD;
    assert(existing_file);
    assert(new_file);
#ifdef _WIN32
    return MoveFile(existing_file, new_file) != FALSE;
#else
    return rename(existing_file, new_file) == 0;
#endif
}

MZC_INLINE bool
mfile_Copy(const MChar *existing_file, const MChar *new_file,
          bool bFailIfExists)
{
    USING_NAMESPACE_STD;
#ifdef _WIN32
    return CopyFile(existing_file, new_file, bFailIfExists) != FALSE;
#else
    size_t size;
    void *ptr = mfile_GetContents(existing_file, &size);
    return mfile_PutContents(new_file, ptr, size);
#endif
}

MZC_INLINE MChar *mpath_SetDotExt(MChar *pathname, const MChar *dot_ext)
{
    USING_NAMESPACE_STD;
    assert(pathname);
    assert(dot_ext);
#ifdef _WIN32
    lstrcpy(mpath_FindDotExt(pathname), dot_ext);
#else
    strcpy(mpath_FindDotExt(pathname), dot_ext);
#endif
    return pathname;
}

MZC_INLINE MChar *mpath_AddSep(MChar *pathname)
{
    USING_NAMESPACE_STD;
    size_t path_len;

#ifdef _WIN32
    MChar *prev;

    assert(pathname);
    path_len = _tcslen(pathname);
    if (path_len == 0)
        return pathname;

    prev = CharPrev(pathname, pathname + path_len);
    if (*prev != TEXT('\\') && *prev != TEXT('/'))
    {
        pathname[path_len++] = TEXT('\\');
        pathname[path_len] = 0;
    }
#else
    char *prev;

    assert(pathname);
    path_len = strlen(pathname);
    if (path_len == 0)
        return pathname;

    prev = &pathname[path_len - 1];
    if (*prev != '/')
    {
        pathname[path_len++] = '/';
        pathname[path_len] = 0;
    }
#endif

    return pathname;
}

MZC_INLINE MChar *mpath_FindDotExt(MChar *pathname)
{
    USING_NAMESPACE_STD;
    MChar *title, *dot_ext;
    assert(pathname);
    title = mpath_FindTitle(pathname);
#ifdef _WIN32
    dot_ext = _tcsrchr(title, TEXT('.'));
    if (dot_ext)
        return dot_ext;
    return pathname + _tcslen(pathname);
#else
    dot_ext = strrchr(title, '.');
    if (dot_ext)
        return dot_ext;
    return pathname + strlen(pathname);
#endif
}

MZC_INLINE MChar *mpath_RemoveSep(MChar *pathname)
{
    USING_NAMESPACE_STD;
    size_t path_len;
    MChar *prev;

    assert(pathname);
#ifdef _WIN32
    path_len = _tcslen(pathname);
#else
    path_len = strlen(pathname);
#endif
    if (path_len == 0)
        return pathname;

#ifdef _WIN32
    #ifdef UNICODE
        prev = pathname + path_len - 1;
        if (*prev == L'\\' || *prev == L'/')
            *prev = 0;
    #else
        prev = CharPrev(pathname, pathname + path_len);
        if (*prev == '\\' || *prev == '/')
            *prev = 0;
    #endif
#else
    prev = pathname + path_len - 1;
    if (*prev == '/')
        *prev = 0;
#endif

    return pathname;
}

MZC_INLINE MChar *mpath_FindTitle(MChar *pathname)
{
    USING_NAMESPACE_STD;
#ifdef _WIN32
    MChar *pch1 = _tcsrchr(pathname, _T('\\'));
    MChar *pch2 = _tcsrchr(pathname, _T('/'));
    if (pch1 == NULL && pch2 == NULL)
        return pathname;
    if (pch1 == NULL)
        return pch2 + 1;
    if (pch2 == NULL)
        return pch1 + 1;
    if (pch1 < pch2)
        return pch2 + 1;
    else
        return pch1 + 1;
#else
    MChar *pch = strrchr(pathname, '/');
    if (pch == NULL)
        return pathname;
    return pch + 1;
#endif
}

MZC_INLINE MChar *mpath_SetTitle(MChar *pathname, const MChar *title)
{
    USING_NAMESPACE_STD;
#ifdef _WIN32
    lstrcpy(mpath_FindTitle(pathname), title);
#else
    strcpy(mpath_FindTitle(pathname), title);
#endif
    return pathname;
}

MZC_INLINE bool mdir_Remove(const MChar *pathname)
{
    USING_NAMESPACE_STD;
#ifdef _WIN32
    return !!RemoveDirectory(pathname);
#else
    return rmdir(pathname) == 0;
#endif
}

#ifndef MSDOS
    MZC_INLINE MZC_DIR_P mdir_FindFirstItem(const MChar *pathname, MZC_DIR_INFO *info)
    {
        USING_NAMESPACE_STD;
    #ifdef _WIN32
        MChar spec[MAX_PATH];
        MZC_DIR_P dirp;

        assert(pathname);
        assert(info);

        lstrcpy(spec, pathname);
        mpath_AddSep(spec);
        lstrcat(spec, TEXT("*"));

        dirp = FindFirstFile(spec, info);
        if (dirp == INVALID_HANDLE_VALUE)
            dirp = NULL;
        return dirp;
    #else
        DIR *dirp;
        struct dirent *ent;

        assert(pathname);
        assert(info);

        dirp = opendir(pathname);
        if (dirp == NULL)
            return NULL;

        ent = readdir(dirp);
        if (!ent)
        {
            closedir(dirp);
            return NULL;
        }

        strcpy(info->cFileName, ent->d_name);
        return dirp;
    #endif
    }

    MZC_INLINE bool mdir_FindNextItem(MZC_DIR_P dirp, MZC_DIR_INFO *info)
    {
        USING_NAMESPACE_STD;
    #ifdef _WIN32
        assert(dirp);
        assert(info);

        if (dirp == NULL)
            return false;

        return FindNextFile(dirp, info) != FALSE;
    #else
        struct dirent *ent;

        assert(dirp);
        assert(info);

        if (dirp == NULL)
            return false;

        ent = readdir(dirp);
        if (ent == NULL)
            return false;

        strcpy(info->cFileName, ent->d_name);
        return true;
    #endif
    }

    MZC_INLINE bool mdir_FindClose(MZC_DIR_P dirp)
    {
        USING_NAMESPACE_STD;
        assert(dirp);

    #ifdef _WIN32
        return !!FindClose(dirp);
    #else
        return closedir(dirp) == 0;
    #endif
    }

    MZC_INLINE bool mdir_Delete(const MChar *dir)
    {
    #ifdef _WIN32
        TCHAR dir_old[MAX_PATH];
    #else
        char dir_old[MAX_PATH];
    #endif
        MZC_DIR_INFO info;
        MZC_DIR_P dirp;

        assert(dir);

        if (!mdir_Exists(dir))
            return false;

        mdir_Get(dir_old, MAX_PATH);
        if (!mdir_Set(dir))
            return false;

        dirp = mdir_FindFirstItem(TEXT("."), &info);
        if (dirp)
        {
            do
            {
                if (!mpath_IsDots(info.cFileName))
                {
                    if (mdir_Exists(info.cFileName))
                        mdir_Delete(info.cFileName);
                    else
                        mfile_Delete(info.cFileName);
                }
            } while(mdir_FindNextItem(dirp, &info));
            mdir_FindClose(dirp);
        }
        mdir_Set(dir_old);

        return mdir_Remove(dir);
    }

    #ifdef __cplusplus
        inline bool mdir_GetItemList(const MChar *dirname, std::vector<MString>& items,
                                     bool sort)
        {
            if (!mdir_Exists(dirname))
                return false;

            MZC_DIR_INFO info;
            MZC_DIR_P dir_p = mdir_FindFirstItem(dirname, &info);
            if (dir_p)
            {
                do
                {
                    if (!mpath_IsDots(info.cFileName))
                    {
                        items.push_back(info.cFileName);
                    }
                } while (mdir_FindNextItem(dir_p, &info));
                mdir_FindClose(dir_p);

                if (sort)
                {
                    std::sort(items.begin(), items.end());
                }
                return true;
            }
            return false;
        }

        inline bool
        mdir_GetFullPathList(const MChar *dirname, std::vector<MString>& paths,
                             bool recursive, bool sort)
        {
            MChar cur_dir[MAX_PATH], full_path[MAX_PATH];

            mdir_Get(cur_dir);
            if (!mdir_Set(dirname))
                return false;

            std::vector<MString> items;
            mdir_GetItemList(TEXT("."), items, false);

            bool ret = true;
            std::vector<MString>::iterator it, end = items.end();
            for (it = items.begin(); it != end; ++it)
            {
                if (recursive)
                {
                    if (mdir_Exists(it->c_str()))
                    {
                        if (!mdir_GetFullPathList(it->c_str(), paths, true, false))
                            ret = false;
                    }
                }
                mpath_GetFullPath(full_path, it->c_str());
                paths.push_back(full_path);
            }

            mdir_Set(cur_dir);

            if (sort)
            {
                std::sort(paths.begin(), paths.end());
            }
            return ret;
        }
    #endif  /* __cplusplus */
#endif  /* ndef MSDOS */

MZC_INLINE bool mdir_Get(MChar *pathname, size_t maxbuf)
{
    USING_NAMESPACE_STD;
#ifdef _WIN32
    return !!GetCurrentDirectory((DWORD)maxbuf, pathname);
#else
    MChar *pch = getcwd(NULL, maxbuf);
    if (pch)
    {
        if (maxbuf)
        {
            strncpy(pathname, pch, maxbuf);
            pathname[maxbuf - 1] = 0;
            free(pch);
            return true;
        }
        free(pch);
    }
    return false;
#endif
}

MZC_INLINE bool mdir_Set(const MChar *pathname)
{
    USING_NAMESPACE_STD;
#ifdef _WIN32
    return !!SetCurrentDirectory(pathname);
#else
    return chdir(pathname) == 0;
#endif
}

MZC_INLINE bool mpath_IsDots(const MChar *name)
{
    return name[0] == TEXT('.') && (
        name[1] == 0 || (name[1] == TEXT('.') && name[2] == 0)
    );
}

MZC_INLINE bool
mdir_CreateRecurse(const MChar *path, bool fForce)
{
    MChar *new_path, *pch, *last_sep;

    assert(path);
#ifdef _WIN32
    new_path = _tcsdup(path);
#else
    new_path = strdup(path);
#endif
    if (!new_path)
        return false;

    mpath_RemoveSep(new_path);

    for (;;)
    {
        if (!mpath_Exists(new_path))
        {
            last_sep = NULL;
#ifdef _WIN32
            for (pch = new_path; *pch; pch = CharNext(pch))
            {
                if (*pch == TEXT('\\') || *pch == TEXT('/'))
                    last_sep = pch;
            }
#else
            for (pch = new_path; *pch; ++pch)
            {
                if (*pch == '/')
                    last_sep = pch;
            }
#endif
            if (last_sep)
            {
                *last_sep = 0;
                if (mdir_CreateRecurse(new_path, fForce))
                {
                    free(new_path);
                    return mdir_Create(path);
                }
            }
            else
            {
                if (mdir_Create(new_path))
                {
                    return true;
                }
            }

            free(new_path);
            return false;
        }

        if (!mdir_Exists(new_path))
        {
            if (!fForce)
                return false;

            if (!mfile_Delete(new_path))
                return false;

            continue;
        }

        break;
    }

    free(new_path);
    return true;
}

MZC_INLINE void mpath_BackslashToSlash(MChar *pathname)
{
    MChar *pch = pathname;
#ifdef _WIN32
    while (*pch)
    {
        if (*pch == TEXT('\\'))
        {
            *pch = TEXT('/');
        }
        pch = CharNext(pch);
    }
#else
    while (*pch)
    {
        if (*pch == '\\')
        {
            *pch = '/';
        }
        ++pch;
    }
#endif
}

MZC_INLINE void mpath_SlashToBackslash(MChar *pathname)
{
    MChar *pch = pathname;
#ifdef _WIN32
    while (*pch)
    {
        if (*pch == TEXT('/'))
        {
            *pch = TEXT('\\');
        }
        pch = CharNext(pch);
    }
#else
    while (*pch)
    {
        if (*pch == '/')
        {
            *pch = '\\';
        }
        ++pch;
    }
#endif
}

/**************************************************************************/

#endif  /* ndef MZC4_MFILEAPI_H_ */
