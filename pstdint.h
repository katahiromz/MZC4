// pstdint.h -- dummy file                                      -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
//////////////////////////////////////////////////////////////////////////////

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
    #error This is poor man version. You lose.
#endif
