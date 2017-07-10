// MString.hpp -- MZC4 string class                             -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MSTRING_HPP_
#define MZC4_MSTRING_HPP_       2   /* Version 2 */

// class MString;
// class MStringA;
// class MStringW;
// mstr_... functions

////////////////////////////////////////////////////////////////////////////

// MString
#ifndef MString
    #include <string>       // std::string and std::wstring
    typedef std::string     MStringA;
    typedef std::wstring    MStringW;
    #ifdef UNICODE
        #define MString     MStringW
    #else
        #define MString     MStringA
    #endif
#endif

////////////////////////////////////////////////////////////////////////////

#include "MTextToText.hpp"

////////////////////////////////////////////////////////////////////////////

inline void mstr_trim(std::string& str, const char *spaces = " \t\r\n")
{
    size_t i = str.find_first_not_of(spaces);
    size_t j = str.find_last_not_of(spaces);
    if ((i == std::string::npos) || (j == std::string::npos))
    {
        str.clear();
    }
    else
    {
        str = str.substr(i, j - i + 1);
    }
}

inline void mstr_trim(std::wstring& str, const wchar_t *spaces = L" \t\r\n")
{
    size_t i = str.find_first_not_of(spaces);
    size_t j = str.find_last_not_of(spaces);
    if ((i == std::wstring::npos) || (j == std::wstring::npos))
    {
        str.clear();
    }
    else
    {
        str = str.substr(i, j - i + 1);
    }
}

inline void mstr_trim(char *str, const char *spaces = " \t\r\n")
{
    std::string s = str;
    mstr_trim(s, spaces);
    std::strcpy(str, s.c_str());
}

inline void mstr_trim(wchar_t *str, const wchar_t *spaces = L" \t\r\n")
{
    std::wstring s = str;
    mstr_trim(s, spaces);
    std::wcscpy(str, s.c_str());
}

inline std::string mstr_repeat(const std::string& str, int count)
{
    std::string ret;
    for (int i = 0; i < count; ++i)
    {
        ret += str;
    }
    return ret;
}

inline std::wstring mstr_repeat(const std::wstring& str, int count)
{
    std::wstring ret;
    for (int i = 0; i < count; ++i)
    {
        ret += str;
    }
    return ret;
}

inline std::string mstr_escape(const std::string& str)
{
    std::string ret;

    for (size_t i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        switch (ch)
        {
        case '\"': ret += "\"\""; break;
        case '\\': ret += "\\\\"; break;
        case '\0': ret += "\\0"; break;
        case '\a': ret += "\\a"; break;
        case '\b': ret += "\\b"; break;
        case '\f': ret += "\\f"; break;
        case '\n': ret += "\\n"; break;
        case '\r': ret += "\\r"; break;
        case '\t': ret += "\\t"; break;
        case '\v': ret += "\\v"; break;
        default:
            if (ch < 0x20)
            {
                using namespace std;
                char sz[32];
                sprintf(sz, "\\x%02X", ch);
                ret += sz;
            }
            else
            {
                ret += ch;
            }
        }
    }

    return ret;
}

inline std::wstring mstr_escape(const std::wstring& str)
{
    std::wstring ret;

    for (size_t i = 0; i < str.size(); ++i)
    {
        wchar_t ch = str[i];
        switch (ch)
        {
        case L'\"': ret += L"\"\""; break;
        case L'\\': ret += L"\\\\"; break;
        case L'\0': ret += L"\\0"; break;
        case L'\a': ret += L"\\a"; break;
        case L'\b': ret += L"\\b"; break;
        case L'\f': ret += L"\\f"; break;
        case L'\n': ret += L"\\n"; break;
        case L'\r': ret += L"\\r"; break;
        case L'\t': ret += L"\\t"; break;
        case L'\v': ret += L"\\v"; break;
        default:
            if (ch < 0x20)
            {
                using namespace std;
                wchar_t sz[32];
                wsprintfW(sz, L"\\x%02X", (BYTE)ch);
                ret += sz;
            }
            else
            {
                ret += ch;
            }
        }
    }

    return ret;
}

template <typename T_STR>
inline void
mstr_replace_all(T_STR& str, const T_STR& from, const T_STR& to)
{
    size_t i = 0;
    for (;;) {
        i = str.find(from, i);
        if (i == T_STR::npos)
            break;
        str.replace(i, from.size(), to);
        i += to.size();
    }
}
template <typename T_STR>
inline void
mstr_replace_all(T_STR& str,
                 const typename T_STR::value_type *from,
                 const typename T_STR::value_type *to)
{
    mstr_replace_all(str, T_STR(from), T_STR(to));
}

inline void
mem_swap_endian(void *ptr, long len)
{
    char *pb = (char *)ptr;
    len /= 2;
    while (--len)
    {
        char b = pb[0];
        pb[0] = pb[1];
        pb[1] = b;
        ++pb;
        ++pb;
    }
}

inline std::wstring
mstr_from_binary(const std::vector<BYTE>& data)
{
    std::wstring ret;
    if (data.size() >= 2 && memcmp(&data[0], "\xFF\xFE", 2) == 0)
    {
        // UTF-16 LE
        ret.assign((const WCHAR *)&data[0], data.size() / sizeof(WCHAR));
    }
    else if (data.size() >= 2 && memcmp(&data[0], "\xFE\xFF", 2) == 0)
    {
        // UTF-16 BE
        ret.assign((const WCHAR *)&data[0], data.size() / sizeof(WCHAR));
        mem_swap_endian(&ret[0], ret.size() * sizeof(WCHAR));
    }
    else if (data.size() >= 3 && memcmp(&data[0], "\xEF\xBB\xBF", 3) == 0)
    {
        // UTF-8
        std::string str((const char *)&data[3], data.size() - 3);
        ret = MUtf8ToWide(str);
    }
    else
    {
        // ANSI
        std::string str((const char *)&data[0], data.size());
        ret = MAnsiToWide(str);
    }

    mstr_replace_all(ret, L"\r\n", L"\n");
    mstr_replace_all(ret, L"\r", L"\n");
    mstr_replace_all(ret, L"\n", L"\r\n");
    return ret;
}

inline std::string mstr_quote(const std::string& str)
{
    std::string ret = "\"";
    ret += mstr_escape(str);
    ret += "\"";
    return ret;
}

inline std::wstring mstr_quote(const std::wstring& str)
{
    std::wstring ret = L"\"";
    ret += mstr_escape(str);
    ret += L"\"";
    return ret;
}

template <typename T_STR_CONTAINER, typename Pred>
inline void
mstr_split(T_STR_CONTAINER& container,
           const typename T_STR_CONTAINER::value_type& str,
           const typename T_STR_CONTAINER::value_type& chars)
{
    container.clear();
    size_t i = 0, k = str.find_first_of(chars);
    while (k != T_STR_CONTAINER::value_type::npos)
    {
        container.push_back(str.substr(i, k - i));
        i = k + 1;
        k = str.find_first_of(chars, i);
    }
    container.push_back(str.substr(i));
}

template <typename T_STR_CONTAINER>
inline typename T_STR_CONTAINER::value_type
mstr_join(const T_STR_CONTAINER& container,
          const typename T_STR_CONTAINER::value_type& sep)
{
    typename T_STR_CONTAINER::value_type result;
    typename T_STR_CONTAINER::const_iterator it, end;
    it = container.begin();
    end = container.end();
    if (it != end)
    {
        result = *it;
        for (++it; it != end; ++it)
        {
            result += sep;
            result += *it;
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MSTRING_HPP_
