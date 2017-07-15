/* pstdint.h -- portable standard integers                      -*- C++ -*-
/* This file is part of MZC4.  See file "ReadMe.txt" and "License.txt". */
/****************************************************************************/

#ifndef MZC4_PSTDINT_H_
#define MZC4_PSTDINT_H_     4   /* Version 4 */

#if __cplusplus >= 201103L
    #include <cstdint>
#elif defined(_WIN32)
    #ifndef _INC_WINDOWS
        #include <windows.h>
    #endif
    typedef signed char int8_t;
    typedef SHORT       int16_t;
    typedef LONG        int32_t;
    typedef LONGLONG    int64_t;
    typedef BYTE        uint8_t;
    typedef WORD        uint16_t;
    typedef DWORD       uint32_t;
    typedef DWORDLONG   uint64_t;
#else
    #ifdef __cplusplus
        #include <climits>
    #else
        #include <limits.h>
    #endif
    typedef signed char             int8_t;
    typedef short                   int16_t;
    typedef int                     int32_t;
    typedef unsigned char           uint8_t;
    typedef unsigned short          uint16_t;
    typedef unsigned int            uint32_t;
    #if defined(_I64_MAX)
        typedef __int64             int64_t;
        typedef unsigned __int64    uint64_t;
    #else
        typedef long long           int64_t;
        typedef unsigned long long  uint64_t;
    #endif
#endif

typedef char PSTDINT_TEST_00_[(sizeof(int8_t) == 1) ? 1 : -1];
typedef char PSTDINT_TEST_01_[(sizeof(int16_t) == 2) ? 1 : -1];
typedef char PSTDINT_TEST_02_[(sizeof(int32_t) == 4) ? 1 : -1];
typedef char PSTDINT_TEST_03_[(sizeof(int64_t) == 8) ? 1 : -1];
typedef char PSTDINT_TEST_04_[(sizeof(uint8_t) == 1) ? 1 : -1];
typedef char PSTDINT_TEST_05_[(sizeof(uint16_t) == 2) ? 1 : -1];
typedef char PSTDINT_TEST_06_[(sizeof(uint32_t) == 4) ? 1 : -1];
typedef char PSTDINT_TEST_07_[(sizeof(uint64_t) == 8) ? 1 : -1];

/****************************************************************************/

#endif  /* ndef MZC4_PSTDINT_H_ */
