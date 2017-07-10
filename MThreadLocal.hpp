// MThreadLocal.hpp -- Win32API thread local                    -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MTHREADLOCAL_HPP_
#define MZC4_MTHREADLOCAL_HPP_      2   /* Version 2 */

template <class T_DATA>
class MThreadLocal;

////////////////////////////////////////////////////////////////////////////

#ifndef _INC_WINDOWS
    #include <windows.h>    // Win32API
#endif
#include <cassert>          // assert

////////////////////////////////////////////////////////////////////////////

template <class T_DATA>
class MThreadLocal
{
public:
    MThreadLocal();
    virtual ~MThreadLocal();

    T_DATA* GetData();
    T_DATA* GetDataNA();    // no allocation
    T_DATA& operator*();
    T_DATA* operator->();

    struct MThreadLocalNode
    {
        T_DATA *value;
        MThreadLocalNode *next;
    };

protected:
    DWORD m_dwIndex;
    MThreadLocalNode *m_nodes;
};

////////////////////////////////////////////////////////////////////////////

template <class T_DATA>
inline MThreadLocal<T_DATA>::MThreadLocal() :
    m_dwIndex(::TlsAlloc()),
    m_nodes(NULL)
{
    assert(m_dwIndex != 0xFFFFFFFF);
}

template <class T_DATA>
/*virtual*/ MThreadLocal<T_DATA>::~MThreadLocal()
{
    ::TlsFree(m_dwIndex);

    MThreadLocalNode *node = m_nodes;
    while (node)
    {
        MThreadLocalNode *next = node->next;
        delete node->value;
        delete node;
        node = next;
    }
}

template <class T_DATA>
inline T_DATA* MThreadLocal<T_DATA>::GetDataNA()
{
    return reinterpret_cast<T_DATA *>(::TlsGetValue(m_dwIndex));
}

template <class T_DATA>
inline T_DATA* MThreadLocal<T_DATA>::GetData()
{
    T_DATA *pData = GetDataNA();
    if (pData)
        return pData;

    pData = new T_DATA;
    MThreadLocalNode *node = new MThreadLocalNode;
    node->value = pData;
    node->next = m_nodes;
    m_nodes = node;

    return pData;
}

template <class T_DATA>
inline T_DATA& MThreadLocal<T_DATA>::operator*()
{
    return *GetData();
}

template <class T_DATA>
inline T_DATA* MThreadLocal<T_DATA>::operator->()
{
    return GetData();
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MTHREADLOCAL_HPP_
