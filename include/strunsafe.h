/* strunsafe.h --- Unsafe version of <strsafe.h>. */
/* Copyright (C) 2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>. */
/* This file is public domain software. */
/* NO WARRANTY ABSOLUTELY. */

#ifndef _STRUNSAFE_H_INCLUDED_
#define _STRUNSAFE_H_INCLUDED_      1   /* Version 1 */

#ifdef _STRSAFE_H_INCLUDED_
    #error Please #include "strunsafe.h" before #include <strsafe.h>.
#endif

#define _STRSAFE_H_INCLUDED_    /* Block <strsafe.h> */

#ifdef __cplusplus
    #include <cstdio>
    #include <cstring>
    #include <cstdarg>
    #include <cassert>
#else
    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>
    #include <assert.h>
#endif

#if defined(_WIN32) || (!defined(WONVER) && !defined(_WONVER))
    #ifndef _INC_WINDOWS
        #include <windows.h>
    #endif
#else
    #include "wonnt.h"
#endif

#ifndef _HRESULT_DEFINED
    #define _HRESULT_DEFINED
    typedef LONG HRESULT;
#endif

#ifndef STRUNSAFEAPI
    #define STRUNSAFEAPI    static __inline HRESULT WINAPI
#endif
#ifndef STRUNSAFEAPIV
    #define STRUNSAFEAPIV   static __inline HRESULT WINAPIV
#endif

#ifndef STRSAFE_MAX_CCH
    #define STRSAFE_MAX_CCH     2147483647
#endif

#ifndef C_ASSERT
    #define C_ASSERT(e) typedef char __C_ASSERT__[(e) ? 1 : -1]
#endif

C_ASSERT(STRSAFE_MAX_CCH <= 2147483647);
C_ASSERT(STRSAFE_MAX_CCH > 1);

#define STRSAFE_MAX_LENGTH  (STRSAFE_MAX_CCH - 1)

#ifndef UNALIGNED
    #if defined(_M_MRX000) || defined(_M_ALPHA) || defined(_M_PPC) || \
        defined(_M_IA64) || defined(_M_AMD64) || defined(_M_ARM) || \
        defined(_M_ARM64)
        #define UNALIGNED __unaligned
    #else
        #define UNALIGNED
    #endif
#endif

typedef char *STRSAFE_LPSTR;
typedef const char *STRSAFE_LPCSTR;
typedef wchar_t *STRSAFE_LPWSTR;
typedef const wchar_t *STRSAFE_LPCWSTR;
typedef const wchar_t UNALIGNED *STRSAFE_LPCUWSTR;

typedef const char *STRSAFE_PCNZCH;
typedef const wchar_t *STRSAFE_PCNZWCH;
typedef const wchar_t UNALIGNED *STRSAFE_PCUNZWCH;

STRUNSAFEAPI
StringCchCopyA(
    char *pszDest,
    size_t cchDest,
    const char *pszSrc)
{
    assert(pszDest);
    assert(pszSrc);

    if (!cchDest)
        return S_OK;

#ifdef _WIN32
    if (lstrcpynA(pszDest, pszSrc, cchDest) != NULL)
        return S_OK;

    assert(0);
    return E_FAIL;
#else
    {
        size_t cchSrc = strlen(pszSrc);
        if (cchSrc + 1 > cchDest)
            cchSrc = cchDest - 1;
        if (!cchSrc)
            return S_OK;

        memcpy(pszDest, pszSrc, cchSrc * sizeof(*pszDest));
        pszDest[cchSrc] = 0;
    }
    return S_OK;
#endif
}

STRUNSAFEAPI
StringCchCopyW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszSrc)
{
    assert(pszDest);
    assert(pszSrc);

    if (!cchDest)
        return S_OK;

#ifdef _WIN32
    if (lstrcpynW(pszDest, pszSrc, cchDest) != NULL)
        return S_OK;

    assert(0);
    return E_FAIL;
#else
    {
        size_t cchSrc = wcslen(pszSrc);
        if (cchSrc + 1 > cchDest)
            cchSrc = cchDest - 1;
        if (!cchSrc)
            return S_OK;

        memcpy(pszDest, pszSrc, cchSrc * sizeof(*pszDest));
        pszDest[cchSrc] = 0;
    }
    return S_OK;
#endif
}

STRUNSAFEAPI
StringCchCatA(
    char *pszDest,
    size_t cchDest,
    const char *pszSrc)
{
    size_t cchOld, cchSrc;
    assert(pszDest);
    assert(pszSrc);

    if (!cchDest || !*pszSrc)
        return S_OK;

    cchOld = strlen(pszDest);
    cchSrc = strlen(pszSrc);
    if (cchOld + cchSrc + 1 > cchDest)
        cchSrc = cchDest - cchOld - 1;
    if (!cchSrc)
        return S_OK;

    memcpy(&pszDest[cchOld], pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchOld + cchSrc] = 0;
    return S_OK;
}

STRUNSAFEAPI
StringCchCatW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszSrc)
{
    size_t cchOld, cchSrc;
    assert(pszDest);
    assert(pszSrc);

    if (!cchDest || !*pszSrc)
        return S_OK;

    cchOld = wcslen(pszDest);
    cchSrc = wcslen(pszSrc);
    if (cchOld + cchSrc + 1 > cchDest)
        cchSrc = cchDest - cchOld - 1;
    if (!cchSrc)
        return S_OK;

    memcpy(&pszDest[cchOld], pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchOld + cchSrc] = 0;

    assert(0);
    return E_FAIL;
}

STRUNSAFEAPI
StringCchCatNA(
    char *pszDest,
    size_t cchDest,
    const char *pszSrc,
    size_t cchToAppend)
{
    size_t cchOld, cchSrc;
    assert(pszDest);
    assert(pszSrc);

    if (!cchDest || !*pszSrc)
        return S_OK;

    cchOld = strlen(pszDest);
    cchSrc = strlen(pszSrc);
    if (cchSrc > cchToAppend)
        cchSrc = cchToAppend;
    if (cchOld + cchSrc + 1 > cchDest)
        cchSrc = cchDest - cchOld - 1;
    if (!cchSrc)
        return S_OK;

    memcpy(&pszDest[cchOld], pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchOld + cchSrc] = 0;
    return S_OK;
}

STRUNSAFEAPI
StringCchCatNW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszSrc,
    size_t cchToAppend)
{
    size_t cchOld, cchSrc;
    assert(pszDest);
    assert(pszSrc);

    if (!cchDest || !*pszSrc)
        return S_OK;

    cchOld = wcslen(pszDest);
    cchSrc = wcslen(pszSrc);
    if (cchSrc > cchToAppend)
        cchSrc = cchToAppend;
    if (cchOld + cchSrc + 1 > cchDest)
        cchSrc = cchDest - cchOld - 1;
    if (!cchSrc)
        return S_OK;

    memcpy(&pszDest[cchOld], pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchOld + cchSrc] = 0;
    return S_OK;
}

STRUNSAFEAPI
StringCchCopyNA(
    char *pszDest,
    size_t cchDest,
    const char *pszSrc,
    size_t cchToCopy)
{
    size_t cchSrc;
    assert(pszDest);
    assert(pszSrc);

    if (!cchDest)
        return S_OK;

    cchSrc = strlen(pszSrc);
    if (cchSrc > cchToCopy)
        cchSrc = cchToCopy;
    if (cchSrc + 1 > cchDest)
        cchSrc = cchDest - 1;
    if (!cchSrc)
        return S_OK;

    memcpy(&pszDest, pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchSrc] = 0;
    return S_OK;
}

STRUNSAFEAPI
StringCchCopyNW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszSrc,
    size_t cchToCopy)
{
    size_t cchSrc;
    assert(pszDest);
    assert(pszSrc);

    if (!cchDest)
        return S_OK;

    cchSrc = wcslen(pszSrc);
    if (cchSrc > cchToCopy)
        cchSrc = cchToCopy;
    if (cchSrc + 1 > cchDest)
        cchSrc = cchDest - 1;
    if (!cchSrc)
        return S_OK;

    memcpy(&pszDest, pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchSrc] = 0;
    return S_OK;
}

STRUNSAFEAPI
StringCchVPrintfA(
    char *pszDest,
    size_t cchDest,
    const char *pszFormat,
    va_list argList)
{
    assert(pszDest);
    assert(pszFormat);
    assert(argList);
    if (vsnprintf(pszDest, cchDest, pszFormat, argList) != -1)
        return S_OK;
    return E_FAIL;
}

STRUNSAFEAPI
StringCchVPrintfW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszFormat,
    va_list argList)
{
    assert(pszDest);
    assert(pszFormat);
    assert(argList);
    if (vsnwprintf(pszDest, cchDest, pszFormat, argList) != -1)
        return S_OK;
    return E_FAIL;
}

STRUNSAFEAPIV
StringCchPrintfA(
    char *pszDest,
    size_t cchDest,
    const char *pszFormat, ...)
{
    int ret;
    va_list va;
    assert(pszDest);
    assert(pszFormat);

    va_start(va, pszFormat);
    ret = vsnprintf(pszDest, cchDest, pszFormat, va);
    va_end(va);
    if (ret != -1)
        return S_OK;

    assert(0);
    return E_FAIL;
}

STRUNSAFEAPIV
StringCchPrintfW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszFormat, ...)
{
    int ret;
    va_list va;
    assert(pszDest);
    assert(pszFormat);

    va_start(va, pszFormat);
    ret = vsnwprintf(pszDest, cchDest, pszFormat, va);
    va_end(va);
    if (ret != -1)
        return S_OK;

    assert(0);
    return E_FAIL;
}

STRUNSAFEAPI
StringCchGetsA(
    char *pszDest,
    size_t cchDest)
{
    assert(pszDest);
    if (fgets(pszDest, (int)cchDest, stdin) != NULL)
        return S_OK;
    assert(0);
    return E_FAIL;
}

STRUNSAFEAPI
StringCchGetsW(
    wchar_t *pszDest,
    size_t cchDest)
{
    assert(pszDest);
    if (fgetws(pszDest, (int)cchDest, stdin) != NULL)
        return S_OK;
    assert(0);
    return E_FAIL;
}

STRUNSAFEAPI
StringCchLengthA(
    const char *psz,
    size_t cchMax,
    size_t *pcchLength)
{
    assert(psz);
    assert(pcchLength);

    if (pcchLength == NULL)
        return E_FAIL;

    *pcchLength = strlen(psz);

    return S_OK;
}

STRUNSAFEAPI
StringCchLengthW(
    const wchar_t *psz,
    size_t cchMax,
    size_t *pcchLength)
{
    assert(psz);
    assert(pcchLength);

    if (pcchLength == NULL)
        return E_FAIL;

    *pcchLength = wcslen(psz);

    return S_OK;
}

STRUNSAFEAPI
StringCbCatNA(
    char *pszDest,
    size_t cbDest,
    const char *pszSrc,
    size_t cbToAppend)
{
    return StringCchCatNA(pszDest, cbDest / sizeof(*pszDest), pszSrc,
                          cbToAppend / sizeof(*pszDest));
}

STRUNSAFEAPI
StringCbCatNW(
    wchar_t *pszDest,
    size_t cbDest,
    const wchar_t *pszSrc,
    size_t cbToAppend)
{
    return StringCchCatNW(pszDest, cbDest / sizeof(*pszDest), pszSrc,
                          cbToAppend / sizeof(*pszDest));
}

STRUNSAFEAPI
StringCbCopyA(
    char *pszDest,
    size_t cbDest,
    const char *pszSrc)
{
    return StringCchCopyA(pszDest, cbDest / sizeof(*pszDest), pszSrc);
}

STRUNSAFEAPI
StringCbCopyW(
    wchar_t *pszDest,
    size_t cbDest,
    const wchar_t *pszSrc)
{
    return StringCchCopyW(pszDest, cbDest / sizeof(*pszDest), pszSrc);
}

STRUNSAFEAPI
StringCbCatA(
    char *pszDest,
    size_t cbDest,
    const char *pszSrc)
{
    return StringCchCatA(pszDest, cbDest / sizeof(*pszDest), pszSrc);
}

STRUNSAFEAPI
StringCbCatW(
    wchar_t *pszDest,
    size_t cbDest,
    const wchar_t *pszSrc)
{
    return StringCchCatW(pszDest, cbDest / sizeof(*pszDest), pszSrc);
}

STRUNSAFEAPI
StringCbCopyNA(
    char *pszDest,
    size_t cbDest,
    const char *pszSrc,
    size_t cbToCopy)
{
    return StringCchCopyNA(pszDest, cbDest / sizeof(*pszDest), pszSrc,
                           cbToCopy / sizeof(*pszDest));
}

STRUNSAFEAPI
StringCbCopyNW(
    wchar_t *pszDest,
    size_t cbDest,
    const wchar_t *pszSrc,
    size_t cbToCopy)
{
    return StringCchCopyNW(pszDest, cbDest / sizeof(*pszDest), pszSrc,
                           cbToCopy / sizeof(*pszDest));
}

STRUNSAFEAPI
StringCbVPrintfA(
    char *pszDest,
    size_t cbDest,
    const char *pszFormat,
    va_list argList)
{
    assert(pszDest);
    assert(pszFormat);
    assert(argList);

    if (vsnprintf(pszDest, cbDest / sizeof(*pszDest), pszFormat, argList) != -1)
        return S_OK;

    assert(0);
    return E_FAIL;
}

STRUNSAFEAPI
StringCbVPrintfW(
    wchar_t *pszDest,
    size_t cbDest,
    const wchar_t *pszFormat,
    va_list argList)
{
    assert(pszDest);
    assert(pszFormat);
    assert(argList);

    if (vsnwprintf(pszDest, cbDest / sizeof(*pszDest), pszFormat, argList) != -1)
        return S_OK;

    assert(0);
    return E_FAIL;
}

STRUNSAFEAPIV
StringCbPrintfA(
    char *pszDest,
    size_t cchDest,
    const char *pszFormat, ...)
{
    int ret;
    va_list va;
    assert(pszDest);
    assert(pszFormat);

    va_start(va, pszFormat);
    ret = vsnprintf(pszDest, cchDest, pszFormat, va);
    va_end(va);
    if (ret != -1)
        return S_OK;

    assert(0);
    return E_FAIL;
}

STRUNSAFEAPIV
StringCbPrintfW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszFormat, ...)
{
    int ret;
    va_list va;
    assert(pszDest);
    assert(pszFormat);

    va_start(va, pszFormat);
    ret = vsnwprintf(pszDest, cchDest, pszFormat, va);
    va_end(va);
    if (ret != -1)
        return S_OK;

    assert(0);
    return E_FAIL;
}

STRUNSAFEAPI
StringCbGetsA(
    char *pszDest,
    size_t cbDest)
{
    return StringCchGetsA(pszDest, cbDest / sizeof(*pszDest));
}

STRUNSAFEAPI
StringCbGetsW(
    wchar_t *pszDest,
    size_t cbDest)
{
    return StringCchGetsW(pszDest, cbDest / sizeof(*pszDest));
}

STRUNSAFEAPI
StringCbLengthA(
    const char *psz,
    size_t cbMax,
    size_t *pcbLength)
{
    assert(psz);
    assert(pcbLength);

    if (pcbLength == NULL)
        return E_FAIL;

    *pcbLength = strlen(psz) * sizeof(*psz);

    return S_OK;
}

STRUNSAFEAPI
StringCbLengthW(
    const wchar_t *psz,
    size_t cbMax,
    size_t *pcbLength)
{
    assert(psz);
    assert(pcbLength);

    if (pcbLength == NULL)
        return E_FAIL;

    *pcbLength = wcslen(psz) * sizeof(*psz);

    return S_OK;
}

#ifdef UNICODE
    #define StringCchCat StringCchCatW
    #define StringCchCopy StringCchCopyW
    #define StringCchCopyN StringCchCopyNW
    #define StringCchCatN StringCchCatNW
    #define StringCchVPrintf StringCchVPrintfW
    #define StringCchPrintf StringCchPrintfW
    #define StringCchGets StringCchGetsW
    #define StringCchLength StringCchLengthW
    #define StringCbCat StringCbCatW
    #define StringCbCopy StringCbCopyW
    #define StringCbCopyN StringCbCopyNW
    #define StringCbCatN StringCbCatNW
    #define StringCbVPrintf StringCbVPrintfW
    #define StringCbPrintf StringCbPrintfW
    #define StringCbGets StringCbGetsW
    #define StringCbLength StringCbLengthW
#else
    #define StringCchCat StringCchCatA
    #define StringCchCopy StringCchCopyA
    #define StringCchCopyN StringCchCopyNA
    #define StringCchCatN StringCchCatNA
    #define StringCchVPrintf StringCchVPrintfA
    #define StringCchPrintf StringCchPrintfA
    #define StringCchGets StringCchGetsA
    #define StringCchLength StringCchLengthA
    #define StringCbCat StringCbCatA
    #define StringCbCopy StringCbCopyA
    #define StringCbCopyN StringCbCopyNA
    #define StringCbCatN StringCbCatNA
    #define StringCbVPrintf StringCbVPrintfA
    #define StringCbPrintf StringCbPrintfA
    #define StringCbGets StringCbGetsA
    #define StringCbLength StringCbLengthA
#endif

#endif  /* ndef _STRUNSAFE_H_INCLUDED_ */
