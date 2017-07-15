/* MTester.h --- MZC4 tester                                    -*- C++ -*- */
/* This file is part of MZC4.  See file "ReadMe.txt" and "License.txt". */
/****************************************************************************/

#ifndef MZC4_MTESTER_H_
#define MZC4_MTESTER_H_     5   /* Version 5 */

/****************************************************************************/

#ifdef __cplusplus
    #include <cstdio>
    #include <cstring>
#else
    #include <stdio.h>
    #include <string.h>
#endif

/****************************************************************************/

#ifndef USING_NAMESPACE_STD
    #ifdef __cplusplus
        #define USING_NAMESPACE_STD     using namespace std
    #else
        #define USING_NAMESPACE_STD     /* empty */
    #endif
#endif

/* C99 and C++11 */
#if __STDC_VERSION__ >= 199901L && !defined(C99)
    #define C99             1
#endif
#if __cplusplus >= 201103L && !defined(CXX11)
    #define CXX11           1
#endif

#ifndef _countof
    #define _countof(array)     (sizeof(array) / sizeof(array[0]))
#endif

#ifndef MTESTER_MAX_BUFFER_COUNT
    #define MTESTER_MAX_BUFFER_COUNT    16
#endif

#ifndef MTESTER_MAX_BUFFER_SIZE
    #define MTESTER_MAX_BUFFER_SIZE     512
#endif

/****************************************************************************/
/* types */

typedef void (*MTEST_FUNC)(void);

typedef struct MTESTCASE
{
    const char *    name;
    MTEST_FUNC      func;
} MTESTCASE;

typedef struct MTEST_BUFFER
{
    int index;
    char buffer[MTESTER_MAX_BUFFER_COUNT][MTESTER_MAX_BUFFER_SIZE];
} MTEST_BUFFER;

/****************************************************************************/
/* global variables */

extern int              g_executed;
extern int              g_failures;
extern int              g_skipped;
extern MTEST_BUFFER     g_test_buffer;
extern const int        g_testcase_count;
extern MTESTCASE        g_testcases[];

/****************************************************************************/
/* mtester functions */

inline int MTester_finish(const char *name)
{
    USING_NAMESPACE_STD;
    printf("\n%s: %d tests executed (%d failures), %d skipped.\n",
           name, g_executed, g_failures, g_skipped);
    return g_failures > 0;
}

inline int MTester_execute(MTESTCASE *testcase)
{
    USING_NAMESPACE_STD;
    g_executed = g_failures = g_skipped = 0;
    memset(&g_test_buffer, 0, sizeof(g_test_buffer));
    (*testcase->func)();
    return MTester_finish(testcase->name);
}

inline int MTester_list(void)
{
    USING_NAMESPACE_STD;
    int i;
    for (i = 0; i < g_testcase_count; ++i)
    {
        if (g_testcases[i].name == NULL)
            break;

        printf("\t%s\n", g_testcases[i].name);
    }
    return 1;
}

inline MTESTCASE *MTester_find(const char *name)
{
    USING_NAMESPACE_STD;
    int i;
    for (i = 0; i < g_testcase_count; ++i)
    {
        if (g_testcases[i].name == NULL)
            break;
        if (strcmp(g_testcases[i].name, name) == 0)
            return &g_testcases[i];
    }
    return NULL;
}

inline int MTester_main(int argc, char **argv)
{
    int i, ret = 0;
    MTESTCASE *testcase;

    if (argc <= 1)
    {
        if (g_testcase_count == 1)
        {
            return MTester_execute(&g_testcases[0]);
        }
        return MTester_list();
    }
    else if (strcmp(argv[1], "all") == 0)
    {
        for (i = 0; i < g_testcase_count; ++i)
        {
            ret += MTester_execute(&g_testcases[i]);
        }
        return ret;
    }
    else
    {
        for (i = 1; i < argc; ++i)
        {
            testcase = MTester_find(argv[i]);
            if (testcase == NULL)
            {
                return MTester_list();
            }
        }
        for (i = 1; i < argc; ++i)
        {
            testcase = MTester_find(argv[i]);
            if (testcase)
            {
                ret += MTester_execute(testcase);
            }
        }
        return ret;
    }
}

inline void MTester_do_skip(const char *file, int line, const char *fmt, ...)
{
    USING_NAMESPACE_STD;
    va_list va;
    va_start(va, fmt);
    printf("%s:%d: Tests skipped: ", file, line);
    vprintf(fmt, va);
    va_end(va);
    g_skipped++;
}

inline void
MTester_head(const char *file, int line)
{
    USING_NAMESPACE_STD;
    printf("%s:%d: Test failed: ", file, line);
}

inline int
MTester_body_v(int cond, const char *fmt, va_list va)
{
    USING_NAMESPACE_STD;
    if (!cond)
    {
        vprintf(fmt, va);
        g_failures++;
    }
    return cond;
}

inline int
MTester_body(int cond, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    MTester_body_v(cond, fmt, va);
    va_end(va);
    return cond;
}

inline void
MTester_do_test(const char *file, int line, int cond, const char *fmt, ...)
{
    USING_NAMESPACE_STD;
    if (!cond)
    {
        va_list va;
        va_start(va, fmt);
        MTester_head(file, line);
        MTester_body_v(cond, fmt, va);
        va_end(va);
    }
    g_executed++;
}

inline char *MTester_sprintf(const char *fmt, ...)
{
    USING_NAMESPACE_STD;
    char *buffer = g_test_buffer.buffer[g_test_buffer.index];
    va_list va;
    va_start(va, fmt);
    vsnprintf(buffer, MTESTER_MAX_BUFFER_SIZE, fmt, va);
    g_test_buffer.index = (g_test_buffer.index + 1) % MTESTER_MAX_BUFFER_COUNT;
    va_end(va);
    return buffer;
}

/****************************************************************************/
/* macros */

#define START_TEST(name) void func_#name(void)
#define DECLARE_TEST(name)  void func_#name(void);

#define BEGIN_TESTS() \
    int g_executed, g_failures, g_skipped; \
    MTEST_BUFFER g_test_buffer; \
    MTESTCASE g_testcases[] = \
    {
#define DEFINE_TEST(name) \
        { #name, func_#name },
#define END_TESTS() \
    }; \
    const int g_testcase_count = (int)_countof(g_testcases); \
    int main(int argc, char **argv) { \
        return MTester_main(argc, argv); \
    }

#if C99 || CXX11
    #define mtest(cond, ...) \
        MTester_do_test(__FILE__, __LINE__, (cond), __VA_ARGS__)
#else
    #define mtest \
        MTester_head(__FILE__, __LINE__), MTester_body
#endif

#define mtest_int_eq(expr, value) \
    MTester_do_test(__FILE__, __LINE__, (expr) == (value), \
                    "%s expected %d (0x%X), got %d (0x%X).\n", \
                    #expr, (value), (value), (expr), (expr))
#define mtest_int_ne(expr, value) \
    MTester_do_test(__FILE__, __LINE__, (expr) != (value), \
                    "%s expected not %d (0x%X).\n", #expr, (value), (value))

#define mtest_ptr_eq(expr, value) \
    MTester_do_test(__FILE__, __LINE__, (expr) == (value), \
                    "%s expected %p, got %p.\n", #expr, \
                    (const void *)(value), (const void *)(expr))
#define mtest_ptr_ne(expr, value) \
    MTester_do_test(__FILE__, __LINE__, (expr) != (value), \
                    "%s expected not %p.\n", #expr, (const void *)(value))

#define mtest_psz_eq(expr, value) \
    MTester_do_test(__FILE__, __LINE__, strcmp((expr), (value)) == 0, \
                    "%s expected %s, got %s.\n", #expr, (value), (expr))
#define mtest_psz_ne(expr, value) \
    MTester_do_test(__FILE__, __LINE__, strcmp((expr), (value)) != 0, \
                    "%s expected not %s.\n", #expr, (value))

#ifdef __cplusplus
    #define mtest_str_eq(expr, value) \
        MTester_do_test(__FILE__, __LINE__, std::string(expr) == std::string(value), \
                        "%s expected %s, got %s.\n", #expr, \
                        std::string(value).c_str(), std::string(expr).c_str())
    #define mtest_str_ne(expr, value) \
        MTester_do_test(__FILE__, __LINE__, std::string(expr) != std::string(value), \
                        "%s expected not %s.\n", #expr, std::string(value).c_str())
#endif

/****************************************************************************/
/* Win32API */

#ifdef _WIN32
    inline const char *MTester_point(const POINT *ppt)
    {
        if (ppt == NULL)
            return "(null)";
        return MTester_sprintf("(%d, %d)", ppt->x, ppt->y);
    }
    inline const char *MTester_size(const SIZE *psiz)
    {
        if (psiz == NULL)
            return "(null)";
        return MTester_sprintf("(%d, %d)", psiz->cx, psiz->cy);
    }
    inline const char *MTester_rect(const RECT *prc)
    {
        if (prc == NULL)
            return "(null)";
        return MTester_sprintf("(%d, %d) - (%d, %d)",
                               prc->left, prc->top, prc->right, prc->bottom);
    }
    inline const char *MTester_longlong(LONGLONG ll)
    {
        return MTester_sprintf("0x%08%08X", (LONG)(ll >> 32), (LONG)ll);
    }
    inline const char *MTester_guid(const GUID *id)
    {
        if (id == NULL)
            return "(null)";
        if (IS_INTRESOURCE(id))
            return MTester_sprintf("<guid-0x%04lx>", (LONG)((ULONG_PTR)id & 0xFFFF));
        return MTester_sprintf("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
                             id->Data1, id->Data2, id->Data3,
                             id->Data4[0], id->Data4[1], id->Data4[2], id->Data4[3],
                             id->Data4[4], id->Data4[5], id->Data4[6], id->Data4[7]);
    }
#endif  /* _WIN32 */

/****************************************************************************/

#endif  /* ndef MZC4_MTESTER_H_ */
