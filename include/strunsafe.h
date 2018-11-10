/* strunsafe.h --- Unsafe version of <strsafe.h>. */
/* Copyright (C) 2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>. */
/* This file is public domain software. */
/* NO WARRANTY ABSOLUTELY. */

#ifndef _STRUNSAFE_H_INCLUDED_
#define _STRUNSAFE_H_INCLUDED_      9   /* Version 9 */

#ifdef _STRSAFE_H_INCLUDED_
    #error Please #include "strunsafe.h" before #include <strsafe.h>.
#endif

#define _STRSAFE_H_INCLUDED_    /* Block <strsafe.h> */

#ifdef __cplusplus
    #include <cstdio>
    #include <cstring>
    #include <cstdarg>
    #ifndef STRUNSAFE_NO_ASSERT
        #include <cassert>
    #endif
#else
    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>
    #ifndef STRUNSAFE_NO_ASSERT
        #include <assert.h>
    #endif
#endif

#if defined(_WIN32) && !defined(WONVER) && !defined(_WONVER)
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
#define STRUNSAFE_MAX_BUFFER  1024

#define STRSAFE_E_INSUFFICIENT_BUFFER ((HRESULT)0x8007007A)
#define STRSAFE_E_INVALID_PARAMETER ((HRESULT)0x80070057)
#define STRSAFE_E_END_OF_FILE ((HRESULT)0x80070026)

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
typedef const char *STRSAFE_PCNZCH;

#ifdef _WIN32
    typedef wchar_t *STRSAFE_LPWSTR;
    typedef const wchar_t *STRSAFE_LPCWSTR;
    typedef const wchar_t UNALIGNED *STRSAFE_LPCUWSTR;
    typedef const wchar_t *STRSAFE_PCNZWCH;
    typedef const wchar_t UNALIGNED *STRSAFE_PCUNZWCH;
#endif

STRUNSAFEAPI
StringCchCopyA(
    char *pszDest,
    size_t cchDest,
    const char *pszSrc)
{
    HRESULT hr = S_OK;
    size_t cchSrc;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszSrc);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !cchDest || !pszSrc || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    cchSrc = strlen(pszSrc);
    if (cchSrc + 1 > cchDest)
    {
        cchSrc = cchDest - 1;
        hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    if (!cchSrc)
    {
        if (cchDest)
            pszDest[0] = 0;
        return hr;
    }

    memcpy(pszDest, pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchSrc] = 0;

    return hr;
}

STRUNSAFEAPI
StringCchCatA(
    char *pszDest,
    size_t cchDest,
    const char *pszSrc)
{
    HRESULT hr = S_OK;
    size_t cchOld, cchSrc;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszSrc);
    assert(pszDest != pszSrc);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!cchDest || !pszSrc || pszDest == pszSrc || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    cchOld = strlen(pszDest);
    cchSrc = strlen(pszSrc);
    if (cchOld >= cchDest)
        return STRSAFE_E_INVALID_PARAMETER;
    if (!cchSrc)
        return S_OK;

    if (cchOld + cchSrc + 1 > cchDest)
    {
        cchSrc = cchDest - cchOld - 1;
        hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    memcpy(&pszDest[cchOld], pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchOld + cchSrc] = 0;

    return hr;
}

STRUNSAFEAPI
StringCchCatNA(
    char *pszDest,
    size_t cchDest,
    const char *pszSrc,
    size_t cchToAppend)
{
    HRESULT hr = S_OK;
    size_t cchOld, cchSrc;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszSrc);
    assert(pszDest != pszSrc);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !cchDest || !pszSrc || pszDest == pszSrc || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    cchOld = strlen(pszDest);
    cchSrc = strlen(pszSrc);
    if (cchOld >= cchDest)
        return STRSAFE_E_INVALID_PARAMETER;
    if (cchSrc > cchToAppend)
        cchSrc = cchToAppend;
    if (!cchSrc)
        return S_OK;

    if (cchOld + cchSrc + 1 > cchDest)
    {
        cchSrc = cchDest - cchOld - 1;
        hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    memcpy(&pszDest[cchOld], pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchOld + cchSrc] = 0;

    return hr;
}

STRUNSAFEAPI
StringCchCopyNA(
    char *pszDest,
    size_t cchDest,
    const char *pszSrc,
    size_t cchToCopy)
{
    HRESULT hr = S_OK;
    size_t cchSrc;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszSrc);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !cchDest || !pszSrc || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    cchSrc = strlen(pszSrc);
    if (cchSrc > cchToCopy)
        cchSrc = cchToCopy;
    if (cchSrc + 1 > cchDest)
    {
        cchSrc = cchDest - 1;
        hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    if (!cchSrc)
    {
        if (cchDest)
            pszDest[0] = 0;
        return hr;
    }

    memcpy(pszDest, pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchSrc] = 0;

    return hr;
}

STRUNSAFEAPI
StringCchVPrintfA(
    char *pszDest,
    size_t cchDest,
    const char *pszFormat,
    va_list argList)
{
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszFormat);
    assert(argList);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !pszFormat || !cchDest || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

#ifdef HAVE__VSNPRINTF_S
    if (_vsnprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, argList) != -1)
        return S_OK;
#elif defined(HAVE_VSNPRINTF_S)
    if (vsnprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, argList) != -1)
        return S_OK;
#elif defined(HAVE__VSNPRINTF)
    if (_vsnprintf(pszDest, cchDest, pszFormat, argList) != -1)
        return S_OK;
#else
    if (vsnprintf(pszDest, cchDest, pszFormat, argList) != -1)
        return S_OK;
#endif

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
    char buf[STRUNSAFE_MAX_BUFFER];
    size_t bufsize = sizeof(buf) / sizeof(buf[0]);
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszFormat);
    assert(pszDest != pszFormat);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    va_start(va, pszFormat);

    if (!pszDest || !cchDest || !pszFormat || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

#ifdef HAVE__VSNPRINTF_S
    ret = _vsnprintf_s(buf, bufsize, _TRUNCATE, pszFormat, va);
#elif defined(HAVE_VSNPRINTF_S)
    ret = vsnprintf_s(buf, bufsize, _TRUNCATE, pszFormat, va);
#elif defined(HAVE__VSNPRINTF)
    ret = _vsnprintf(buf, bufsize, pszFormat, va);
#else
    ret = vsnprintf(buf, bufsize, pszFormat, va);
#endif
    va_end(va);

    if (ret >= 0)
    {
        return StringCchCopyNA(pszDest, cchDest, buf, bufsize);
    }

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
    return E_FAIL;
}

STRUNSAFEAPI
StringCchGetsA(
    char *pszDest,
    size_t cchDest)
{
    size_t cchLength;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !cchDest || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    if (fgets(pszDest, (int)cchDest, stdin) != NULL)
    {
        // chomp
        cchLength = strlen(pszDest);
        if (cchLength && pszDest[cchLength - 1] == '\n')
        {
            --cchLength;
            pszDest[cchLength] = 0;
            if (cchLength && pszDest[cchLength - 1] == '\r')
            {
                --cchLength;
                pszDest[cchLength] = 0;
            }
        }
        return S_OK;
    }

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
    return E_FAIL;
}

STRUNSAFEAPI
StringCchLengthA(
    const char *psz,
    size_t cchMax,
    size_t *pcchLength)
{
    size_t cchLength;
#ifndef STRUNSAFE_NO_ASSERT
    assert(psz);
    assert(pcchLength);
    assert(cchMax <= STRSAFE_MAX_CCH);
#endif

    if (!psz || !cchMax || !pcchLength || cchMax > STRSAFE_MAX_CCH)
    {
        if (pcchLength)
            *pcchLength = 0;
        return STRSAFE_E_INVALID_PARAMETER;
    }

    for (cchLength = 0; *psz; ++psz, ++cchLength)
    {
        if (cchMax <= cchLength + 1)
        {
            *pcchLength = 0;
            return STRSAFE_E_INVALID_PARAMETER;
        }
    }

    *pcchLength = cchLength;

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
StringCbCopyA(
    char *pszDest,
    size_t cbDest,
    const char *pszSrc)
{
    return StringCchCopyA(pszDest, cbDest / sizeof(*pszDest), pszSrc);
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
StringCbVPrintfA(
    char *pszDest,
    size_t cbDest,
    const char *pszFormat,
    va_list argList)
{
    size_t cchDest = cbDest / sizeof(*pszDest);
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszFormat);
    assert(argList);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !pszFormat || !cbDest || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

#ifdef HAVE__VSNPRINTF_S
    if (_vsnprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, argList) != -1)
        return S_OK;
#elif defined(HAVE_VSNPRINTF_S)
    if (vsnprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, argList) != -1)
        return S_OK;
#elif defined(HAVE__VSNPRINTF)
    if (_vsnprintf(pszDest, cchDest, pszFormat, argList) != -1)
        return S_OK;
#else
    if (vsnprintf(pszDest, cchDest, pszFormat, argList) != -1)
        return S_OK;
#endif

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
    return E_FAIL;
}

STRUNSAFEAPIV
StringCbPrintfA(
    char *pszDest,
    size_t cbDest,
    const char *pszFormat, ...)
{
    int ret;
    va_list va;
    size_t cchDest = cbDest / sizeof(*pszDest);
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszFormat);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !pszFormat || !cchDest || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    va_start(va, pszFormat);
#ifdef HAVE__VSNPRINTF_S
    ret = _vsnprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, va);
#elif defined(HAVE_VSNPRINTF_S)
    ret = vsnprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, va);
#elif defined(HAVE__VSNPRINTF)
    ret = _vsnprintf(pszDest, cchDest, pszFormat, va);
#else
    ret = vsnprintf(pszDest, cchDest, pszFormat, va);
#endif
    va_end(va);
    if (ret != -1)
        return S_OK;

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
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
StringCbLengthA(
    const char *psz,
    size_t cbMax,
    size_t *pcbLength)
{
    size_t cchLength;
    size_t cchMax = cbMax / sizeof(*psz);
#ifndef STRUNSAFE_NO_ASSERT
    assert(psz);
    assert(pcbLength);
    assert(cchMax <= STRSAFE_MAX_CCH);
#endif

    if (!psz || !cchMax || !pcbLength || cchMax > STRSAFE_MAX_CCH)
    {
        if (pcbLength)
            *pcbLength = 0;
        return STRSAFE_E_INVALID_PARAMETER;
    }

    for (cchLength = 0; *psz; ++psz, ++cchLength)
    {
        if (cchMax <= cchLength + 1)
        {
            *pcbLength = 0;
            return STRSAFE_E_INVALID_PARAMETER;
        }
    }

    *pcbLength = cchLength * sizeof(*psz);

    return S_OK;
}

#ifdef _WIN32   // Unicode support for Win32 only
STRUNSAFEAPI
StringCchCopyW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszSrc)
{
    HRESULT hr = S_OK;
    size_t cchSrc;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszSrc);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !cchDest || !pszSrc || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    cchSrc = wcslen(pszSrc);
    if (cchSrc + 1 > cchDest)
    {
        cchSrc = cchDest - 1;
        hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    if (!cchSrc)
    {
        if (cchDest)
            pszDest[0] = 0;
        return hr;
    }

    memcpy(pszDest, pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchSrc] = 0;

    return hr;
}

STRUNSAFEAPI
StringCchCatW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszSrc)
{
    HRESULT hr = S_OK;
    size_t cchOld, cchSrc;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszSrc);
    assert(pszDest != pszSrc);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!cchDest || !pszSrc || pszDest == pszSrc || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    cchOld = wcslen(pszDest);
    cchSrc = wcslen(pszSrc);
    if (cchOld >= cchDest)
        return STRSAFE_E_INVALID_PARAMETER;
    if (!cchSrc)
        return S_OK;

    if (cchOld + cchSrc + 1 > cchDest)
    {
        cchSrc = cchDest - cchOld - 1;
        hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    memcpy(&pszDest[cchOld], pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchOld + cchSrc] = 0;

    return hr;
}

STRUNSAFEAPI
StringCchCatNW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszSrc,
    size_t cchToAppend)
{
    HRESULT hr = S_OK;
    size_t cchOld, cchSrc;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszSrc);
    assert(pszDest != pszSrc);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!cchDest || !pszSrc || pszDest == pszSrc || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    cchOld = wcslen(pszDest);
    cchSrc = wcslen(pszSrc);
    if (cchOld >= cchDest)
        return STRSAFE_E_INVALID_PARAMETER;
    if (cchSrc > cchToAppend)
        cchSrc = cchToAppend;
    if (!cchSrc)
        return S_OK;

    if (cchOld + cchSrc + 1 > cchDest)
    {
        cchSrc = cchDest - cchOld - 1;
        hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    memcpy(&pszDest[cchOld], pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchOld + cchSrc] = 0;

    return hr;
}

STRUNSAFEAPI
StringCchCopyNW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszSrc,
    size_t cchToCopy)
{
    HRESULT hr = S_OK;
    size_t cchSrc;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszSrc);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !cchDest || !pszSrc || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    cchSrc = wcslen(pszSrc);
    if (cchSrc > cchToCopy)
        cchSrc = cchToCopy;
    if (cchSrc + 1 > cchDest)
    {
        cchSrc = cchDest - 1;
        hr = STRSAFE_E_INSUFFICIENT_BUFFER;
    }

    if (!cchSrc)
    {
        if (cchDest)
            pszDest[0] = 0;
        return hr;
    }

    memcpy(pszDest, pszSrc, cchSrc * sizeof(*pszDest));
    pszDest[cchSrc] = 0;

    return hr;
}

STRUNSAFEAPI
StringCchVPrintfW(
    wchar_t *pszDest,
    size_t cchDest,
    const wchar_t *pszFormat,
    va_list argList)
{
    int ret;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszFormat);
    assert(argList);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !pszFormat || !cchDest || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

#ifdef HAVE__VSNWPRINTF_S
    ret = _vsnwprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, argList);
#elif defined(HAVE_VSNWPRINTF_S)
    ret = vsnwprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, argList);
#elif defined(HAVE_VSNWPRINTF)
    ret = vsnwprintf(pszDest, cchDest, pszFormat, argList);
#else
    ret = _vsnwprintf(pszDest, cchDest, pszFormat, argList);
#endif
    if (ret != -1)
        return S_OK;

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
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
    wchar_t buf[STRUNSAFE_MAX_BUFFER];
    size_t bufsize = sizeof(buf) / sizeof(buf[0]);
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszFormat);
    assert(pszDest != pszFormat);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    va_start(va, pszFormat);

    if (!pszDest || !cchDest || !pszFormat || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

#ifdef HAVE__VSNWPRINTF_S
    ret = _vsnwprintf_s(buf, bufsize, _TRUNCATE, pszFormat, va);
#elif defined(HAVE_VSNWPRINTF_S)
    ret = vsnwprintf_s(buf, bufsize, _TRUNCATE, pszFormat, va);
#elif defined(HAVE_VSNWPRINTF)
    ret = vsnwprintf(buf, bufsize, pszFormat, va);
#else
    ret = _vsnwprintf(buf, bufsize, pszFormat, va);
#endif
    va_end(va);

    if (ret >= 0)
    {
        return StringCchCopyNW(pszDest, cchDest, buf, bufsize);
    }

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
    return E_FAIL;
}

STRUNSAFEAPI
StringCchGetsW(
    wchar_t *pszDest,
    size_t cchDest)
{
    size_t cchLength;
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !cchDest || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    if (fgetws(pszDest, (int)cchDest, stdin) != NULL)
    {
        // chomp
        cchLength = wcslen(pszDest);
        if (cchLength && pszDest[cchLength - 1] == L'\n')
        {
            --cchLength;
            pszDest[cchLength] = 0;
            if (cchLength && pszDest[cchLength - 1] == L'\r')
            {
                --cchLength;
                pszDest[cchLength] = 0;
            }
        }
        return S_OK;
    }

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
    return E_FAIL;
}

STRUNSAFEAPI
StringCchLengthW(
    const wchar_t *psz,
    size_t cchMax,
    size_t *pcchLength)
{
    size_t cchLength;
#ifndef STRUNSAFE_NO_ASSERT
    assert(psz);
    assert(pcchLength);
    assert(cchMax <= STRSAFE_MAX_CCH);
#endif

    if (!psz || !cchMax || !pcchLength || cchMax > STRSAFE_MAX_CCH)
    {
        if (pcchLength)
            *pcchLength = 0;
        return STRSAFE_E_INVALID_PARAMETER;
    }

    for (cchLength = 0; *psz; ++psz, ++cchLength)
    {
        if (cchMax <= cchLength + 1)
        {
            *pcchLength = 0;
            return STRSAFE_E_INVALID_PARAMETER;
        }
    }

    *pcchLength = cchLength;

    return S_OK;
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
StringCbCopyW(
    wchar_t *pszDest,
    size_t cbDest,
    const wchar_t *pszSrc)
{
    return StringCchCopyW(pszDest, cbDest / sizeof(*pszDest), pszSrc);
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
StringCbVPrintfW(
    wchar_t *pszDest,
    size_t cbDest,
    const wchar_t *pszFormat,
    va_list argList)
{
    size_t cchDest = cbDest / sizeof(*pszDest);
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszFormat);
    assert(argList);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif

    if (!pszDest || !pszFormat || !cchDest || cchDest > STRSAFE_MAX_CCH);
        return STRSAFE_E_INVALID_PARAMETER;

#ifdef HAVE__VSNWPRINTF_S
    if (_vsnwprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, argList) != -1)
        return S_OK;
#elif defined(HAVE_VSNWPRINTF_S)
    if (vsnwprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, argList) != -1)
        return S_OK;
#elif defined(HAVE_VSNWPRINTF)
    if (vsnwprintf(pszDest, cchDest, pszFormat, argList) != -1)
        return S_OK;
#else
    if (_vsnwprintf(pszDest, cchDest, pszFormat, argList) != -1)
        return S_OK;
#endif

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
    return E_FAIL;
}

STRUNSAFEAPIV
StringCbPrintfW(
    wchar_t *pszDest,
    size_t cbDest,
    const wchar_t *pszFormat, ...)
{
    int ret;
    va_list va;
    size_t cchDest = cbDest / sizeof(*pszDest);
#ifndef STRUNSAFE_NO_ASSERT
    assert(pszDest);
    assert(pszFormat);
    assert(cchDest <= STRSAFE_MAX_CCH);
#endif
    if (!pszDest || !pszFormat || !cchDest || cchDest > STRSAFE_MAX_CCH)
        return STRSAFE_E_INVALID_PARAMETER;

    va_start(va, pszFormat);
#ifdef HAVE__VSNWPRINTF_S
    ret = _vsnwprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, va);
#elif defined(HAVE_VSNWPRINTF_S)
    ret = vsnwprintf_s(pszDest, cchDest, _TRUNCATE, pszFormat, va);
#elif defined(HAVE_VSNWPRINTF)
    ret = vsnwprintf(pszDest, cchDest, pszFormat, va);
#else
    ret = _vsnwprintf(pszDest, cchDest, pszFormat, va);
#endif
    va_end(va);
    if (ret != -1)
        return S_OK;

#ifndef STRUNSAFE_NO_ASSERT
    assert(0);
#endif
    return E_FAIL;
}

STRUNSAFEAPI
StringCbGetsW(
    wchar_t *pszDest,
    size_t cbDest)
{
    return StringCchGetsW(pszDest, cbDest / sizeof(*pszDest));
}

STRUNSAFEAPI
StringCbLengthW(
    const wchar_t *psz,
    size_t cbMax,
    size_t *pcbLength)
{
    size_t cchLength;
    size_t cchMax = cbMax / sizeof(*psz);
#ifndef STRUNSAFE_NO_ASSERT
    assert(psz);
    assert(pcbLength);
    assert(cchMax <= STRSAFE_MAX_CCH);
#endif

    if (!psz || !cchMax || !pcbLength || cchMax > STRSAFE_MAX_CCH)
    {
        if (pcbLength)
            *pcbLength = 0;
        return STRSAFE_E_INVALID_PARAMETER;
    }

    for (cchLength = 0; *psz; ++psz, ++cchLength)
    {
        if (cchMax <= cchLength + 1)
        {
            *pcbLength = 0;
            return STRSAFE_E_INVALID_PARAMETER;
        }
    }

    *pcbLength = cchLength * sizeof(*psz);

    return S_OK;
}
#endif  /* def _WIN32 */

#ifdef UNICODE
    #define StringCbCat StringCbCatW
    #define StringCbCatN StringCbCatNW
    #define StringCbCopy StringCbCopyW
    #define StringCbCopyN StringCbCopyNW
    #define StringCbGets StringCbGetsW
    #define StringCbLength StringCbLengthW
    #define StringCbPrintf StringCbPrintfW
    #define StringCbVPrintf StringCbVPrintfW
    #define StringCchCat StringCchCatW
    #define StringCchCatN StringCchCatNW
    #define StringCchCopy StringCchCopyW
    #define StringCchCopyN StringCchCopyNW
    #define StringCchGets StringCchGetsW
    #define StringCchLength StringCchLengthW
    #define StringCchPrintf StringCchPrintfW
    #define StringCchVPrintf StringCchVPrintfW
#else
    #define StringCbCat StringCbCatA
    #define StringCbCatN StringCbCatNA
    #define StringCbCopy StringCbCopyA
    #define StringCbCopyN StringCbCopyNA
    #define StringCbGets StringCbGetsA
    #define StringCbLength StringCbLengthA
    #define StringCbPrintf StringCbPrintfA
    #define StringCbVPrintf StringCbVPrintfA
    #define StringCchCat StringCchCatA
    #define StringCchCatN StringCchCatNA
    #define StringCchCopy StringCchCopyA
    #define StringCchCopyN StringCchCopyNA
    #define StringCchGets StringCchGetsA
    #define StringCchLength StringCchLengthA
    #define StringCchPrintf StringCchPrintfA
    #define StringCchVPrintf StringCchVPrintfA
#endif

#endif  /* ndef _STRUNSAFE_H_INCLUDED_ */
