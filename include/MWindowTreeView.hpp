// MWindowTreeView.hpp -- MZC4 window tree view             -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MWINDOWTREEVIEW_HPP_
#define MZC4_MWINDOWTREEVIEW_HPP_     11       /* Version 11 */

#include "MTreeView.hpp"
#include <shellapi.h>   // for SHGetFileInfo
#include <psapi.h>      // for GetModuleFileNameEx
#include <tlhelp32.h>   // for CreateToolhelp32Snapshot
#include <vector>       // for std::vector
#include <algorithm>    // for std::sort and std::unique

#include "ProcessWindowIcon.hpp"

// The styles of MWindowTree and MWindowTreeView
#define MWTVS_PROCESSWINDOW 0x0000
#define MWTVS_PROCESSTHREAD 0x0001
#define MWTVS_DESKTOPTREE 0x0002
#define MWTVS_TYPEMASK 0x0003
#define MWTVS_EXPANDED 0x0004

////////////////////////////////////////////////////////////////////////////
// MWindowTree

struct MWindowTreeNode
{
    enum Type
    {
        PROCESS, THREAD, WINDOW, ROOT
    };
    Type m_type;
    HWND m_hwndTarget;
    DWORD m_id;
    std::vector<MWindowTreeNode *> m_children;
    TCHAR m_szExeFile[MAX_PATH];

    MWindowTreeNode(Type type);
    MWindowTreeNode(HWND hwnd);
    ~MWindowTreeNode();

    MWindowTreeNode *find(HWND hwnd);
    MWindowTreeNode *insert_window(HWND hwnd);
    MWindowTreeNode *insert_process(const PROCESSENTRY32& pe);
    MWindowTreeNode *insert_thread(const THREADENTRY32& te);

    static bool id_less(const MWindowTreeNode *a, const MWindowTreeNode *b);

private:
    MWindowTreeNode(const MWindowTreeNode&);
    MWindowTreeNode& operator=(const MWindowTreeNode&);
};

////////////////////////////////////////////////////////////////////////////
// MWindowTree

class MWindowTree
{
public:
    MWindowTree();
    virtual ~MWindowTree();

    typedef MWindowTreeNode node_type;

    bool get_tree(DWORD dwMWTVS_ = MWTVS_PROCESSWINDOW);
    MWindowTreeNode *root() const;

    bool distribute(HANDLE hSnapshot);

    bool empty() const;
    void clear();

    static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

protected:
    MWindowTreeNode *m_root;

private:
    MWindowTree(const MWindowTree&);
    MWindowTree& operator=(const MWindowTree&);
};

////////////////////////////////////////////////////////////////////////////
// MWindowTreeView

class MWindowTreeView : public MTreeView
{
public:
    typedef MWindowTree::node_type node_type;

    MWindowTreeView();
    virtual ~MWindowTreeView();

    bool refresh();

    virtual MString text_from_node(const node_type *node) const;
    virtual HTREEITEM InsertNodeTree(const node_type *node, HTREEITEM hParent = TVI_ROOT);
    virtual HTREEITEM InsertNodeItem(const node_type *node, HTREEITEM hParent = TVI_ROOT);

    bool empty() const;
    void clear();

    DWORD get_style() const;
    void set_style(DWORD style);

    bool get_selected_hwnd(HWND& hwnd) const;
    bool select_hwnd(HWND hwnd);

    bool find_text(HTREEITEM& hItem, const MString& text, HTREEITEM hParent = TVI_ROOT) const;

    HTREEITEM ItemFromWindow(HWND hwnd) const;
    HTREEITEM ItemFromNode(const node_type *node,
                           HTREEITEM hItem = TVI_ROOT) const;

    HWND WindowFromItem(HTREEITEM hItem) const;

    node_type *NodeFromItem(HTREEITEM hItem) const
    {
        return (node_type *)GetItemData(hItem);
    }
    node_type *root() const
    {
        return m_tree.root();
    }
    node_type *find_node(HWND hwnd) const
    {
        if (node_type *node = root())
        {
            return node->find(hwnd);
        }
        return NULL;
    }

protected:
    MWindowTree m_tree;
    HIMAGELIST m_himl;
    DWORD m_MWTVS_;

    void ReCreateTreeImageList();
};

////////////////////////////////////////////////////////////////////////////
// MWindowTreeNode inlines

inline bool
MWindowTreeNode::id_less(const MWindowTreeNode *a, const MWindowTreeNode *b)
{
    return (a->m_id < b->m_id);
}

inline
MWindowTreeNode::MWindowTreeNode(Type type)
    : m_type(type), m_hwndTarget(NULL), m_id(0)
{
    m_szExeFile[0] = 0;
}

inline MWindowTreeNode::MWindowTreeNode(HWND hwnd)
    : m_type(WINDOW), m_hwndTarget(hwnd), m_id(0)
{
    m_szExeFile[0] = 0;
}

inline MWindowTreeNode::~MWindowTreeNode()
{
    for (size_t i = 0; i < m_children.size(); ++i)
    {
        delete m_children[i];
    }
}

inline MWindowTreeNode *MWindowTreeNode::find(HWND hwnd)
{
    if (m_hwndTarget == hwnd)
        return this;

    for (size_t i = 0; i < m_children.size(); ++i)
    {
        if (MWindowTreeNode *node = m_children[i]->find(hwnd))
            return node;
    }
    return NULL;
}

inline MWindowTreeNode *MWindowTreeNode::insert_window(HWND hwnd)
{
    MWindowTreeNode *node = new MWindowTreeNode(WINDOW);
    node->m_hwndTarget = hwnd;
    m_children.push_back(node);
    return node;
}

inline MWindowTreeNode *
MWindowTreeNode::insert_process(const PROCESSENTRY32& pe)
{
    MWindowTreeNode *node = new MWindowTreeNode(PROCESS);
    node->m_id = pe.th32ProcessID;
    m_children.push_back(node);
    lstrcpyn(node->m_szExeFile, pe.szExeFile, MAX_PATH);
    return node;
}

inline MWindowTreeNode *
MWindowTreeNode::insert_thread(const THREADENTRY32& te)
{
    MWindowTreeNode *node = new MWindowTreeNode(THREAD);
    node->m_id = te.th32ThreadID;
    m_children.push_back(node);
    return node;
}

////////////////////////////////////////////////////////////////////////////
// MWindowTree inlines

inline MWindowTree::MWindowTree() : m_root(NULL)
{
}

inline MWindowTree::~MWindowTree()
{
    clear();
}

inline void MWindowTree::clear()
{
    if (m_root)
    {
        delete m_root;
        m_root = NULL;
    }
}

inline MWindowTreeNode *MWindowTree::root() const
{
    return m_root;
}

inline BOOL CALLBACK MWindowTree::EnumChildProc(HWND hwnd, LPARAM lParam)
{
    MWindowTreeNode *parent = (MWindowTreeNode *)lParam;
    HWND hwndOwnerOrParent = ::GetWindow(hwnd, GW_OWNER);
    if (!hwndOwnerOrParent)
        hwndOwnerOrParent = ::GetParent(hwnd);
    if (parent->m_hwndTarget == hwndOwnerOrParent)
    {
        MWindowTreeNode *node = parent->insert_window(hwnd);
        lParam = (LPARAM)node;
        ::EnumChildWindows(hwnd, MWindowTree::EnumChildProc, lParam);
    }
    return TRUE;
}

inline BOOL CALLBACK MWindowTree::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    MWindowTreeNode *node = (MWindowTreeNode *)lParam;
    MWindowTreeNode *new_node = node->insert_window(hwnd);
    lParam = (LPARAM)new_node;
    ::EnumChildWindows(hwnd, MWindowTree::EnumChildProc, lParam);
    return TRUE;
}

bool MWindowTree::empty() const
{
    return m_root == NULL || m_root->m_children.empty();
}

inline bool MWindowTree::get_tree(DWORD dwMWTVS_)
{
    clear();

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD | TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;

    if ((dwMWTVS_ & MWTVS_TYPEMASK) == MWTVS_PROCESSTHREAD)
    {
        m_root = new MWindowTreeNode(MWindowTreeNode::ROOT);

        PROCESSENTRY32 process = { sizeof(process) };
        if (Process32First(hSnapshot, &process))
        {
            do
            {
                m_root->insert_process(process);
            } while (Process32Next(hSnapshot, &process));
        }

        std::sort(m_root->m_children.begin(), m_root->m_children.end(), MWindowTreeNode::id_less);

        THREADENTRY32 thread = { sizeof(thread) };
        if (Thread32First(hSnapshot, &thread))
        {
            do
            {
                size_t k;
                for (k = 0; k < m_root->m_children.size(); ++k)
                {
                    MWindowTreeNode *child = m_root->m_children[k];
                    if (child->m_id == thread.th32OwnerProcessID)
                    {
                        child->insert_thread(thread);
                        break;
                    }
                }
            } while (Thread32Next(hSnapshot, &thread));
        }

        for (size_t k = 0; k < m_root->m_children.size(); ++k)
        {
            MWindowTreeNode *child = m_root->m_children[k];
            std::sort(child->m_children.begin(), child->m_children.end(), MWindowTreeNode::id_less);
        }
    }
    else
    {
        m_root = new MWindowTreeNode(::GetDesktopWindow());

        if (!::EnumWindows(MWindowTree::EnumWindowsProc, (LPARAM)m_root))
            return false;

        if ((dwMWTVS_ & MWTVS_TYPEMASK) == MWTVS_PROCESSWINDOW)
        {
            distribute(hSnapshot);
        }
    }

    CloseHandle(hSnapshot);

    return !empty();
}

inline bool MWindowTree::distribute(HANDLE hSnapshot)
{
    if (!m_root)
        return false;

    MWindowTreeNode *new_root = new MWindowTreeNode(GetDesktopWindow());
    MWindowTreeNode *old_root = m_root;

    PROCESSENTRY32 process = { sizeof(process) };
    if (Process32First(hSnapshot, &process))
    {
        do
        {
            new_root->insert_process(process);
        } while (Process32Next(hSnapshot, &process));
    }

    std::sort(new_root->m_children.begin(), new_root->m_children.end(), MWindowTreeNode::id_less);

    for (size_t i = 0; i < old_root->m_children.size(); ++i)
    {
        MWindowTreeNode *child = old_root->m_children[i];
        DWORD pid = ProcessFromWindowDx(child->m_hwndTarget);

        size_t k;
        for (k = 0; k < new_root->m_children.size(); ++k)
        {
            if (new_root->m_children[k]->m_id == pid)
            {
                new_root->m_children[k]->m_children.push_back(child);
                break;
            }
        }
        if (k == new_root->m_children.size())
        {
            MWindowTreeNode *new_child = new MWindowTreeNode(MWindowTreeNode::PROCESS);
            new_child->m_id = pid;
            new_child->m_children.push_back(child);
            new_root->m_children.push_back(new_child);
        }
    }

    m_root = new_root;
    old_root->m_children.clear();
    delete old_root;

    return true;
}

////////////////////////////////////////////////////////////////////////////
// MWindowTreeView inlines

inline MWindowTreeView::MWindowTreeView() : m_himl(NULL)
{
}

inline void MWindowTreeView::ReCreateTreeImageList()
{
    if (m_himl)
    {
        ImageList_Destroy(m_himl);
        m_himl = NULL;
    }
    INT cx = GetSystemMetrics(SM_CXSMICON);
    INT cy = GetSystemMetrics(SM_CYSMICON);
    m_himl = ImageList_Create(cx, cy, ILC_COLOR32 | ILC_MASK, 128, 16);
    SetImageList(m_himl, TVSIL_NORMAL);
}

inline MWindowTreeView::~MWindowTreeView()
{
    ImageList_Destroy(m_himl);
}

inline bool MWindowTreeView::refresh()
{
    SendMessageDx(WM_SETREDRAW, FALSE);
    clear();
    if (m_tree.get_tree(get_style()))
    {
        MWindowTreeNode *node;
        switch (get_style() & MWTVS_TYPEMASK)
        {
        case MWTVS_PROCESSWINDOW:
        case MWTVS_PROCESSTHREAD:
            node = root();
            for (size_t i = 0; i < node->m_children.size(); ++i)
            {
                InsertNodeTree(node->m_children[i]);
            }
            break;
        case MWTVS_DESKTOPTREE:
            InsertNodeTree(root());
            break;
        }
    }
    SendMessageDx(WM_SETREDRAW, TRUE);
    return false;
}

inline MString MWindowTreeView::text_from_node(const node_type *node) const
{
    if (node->m_type == MWindowTreeNode::THREAD)
    {
        TCHAR szText[64];
        StringCbPrintf(szText, sizeof(szText), TEXT("TID %lu "), node->m_id);
        MString strText = szText;
        return strText;
    }
    else if (node->m_type == MWindowTreeNode::PROCESS)
    {
        DWORD pid = node->m_id;

        TCHAR szText[64];
        StringCbPrintf(szText, sizeof(szText), TEXT("PID %lu "), pid);
        MString strText = szText;
        MString strPath = GetPathOfProcessDx(pid);

        if (strPath.size())
        {
            szText[0] = 0;
            GetFileTitle(strPath.c_str(), szText, ARRAYSIZE(szText));
            strText += TEXT("[");
            strText += szText;
            strText += TEXT("] ");
            strText += strPath;
        }
        else
        {
            strText += TEXT("[");
            strText += node->m_szExeFile;
            strText += TEXT("]");
        }

        return strText;
    }
    else
    {
        HWND hwndTarget = node->m_hwndTarget;

        TCHAR szText[64];
        StringCbPrintf(szText, sizeof(szText), TEXT("%08lX "),
                       (LONG)(LONG_PTR)hwndTarget);
        MString strText = szText;

        strText += TEXT(" [");
        GetClassName(hwndTarget, szText, ARRAYSIZE(szText));
        strText += szText;
        strText += TEXT("] ");

        strText += MWindowBase::GetWindowText(hwndTarget);
        return strText;
    }
}

inline bool MWindowTreeView::empty() const
{
    return m_tree.empty();
}

inline void MWindowTreeView::clear()
{
    DeleteAllItems();
    m_tree.clear();
    ReCreateTreeImageList();
}

inline bool MWindowTreeView::get_selected_hwnd(HWND& hwnd) const
{
    hwnd = NULL;
    if (HTREEITEM hItem = GetSelectedItem())
    {
        hwnd = WindowFromItem(hItem);
    }
    return hwnd != NULL;
}

inline HTREEITEM
MWindowTreeView::InsertNodeTree(const node_type *node, HTREEITEM hParent)
{
    if (HTREEITEM hInserted = InsertNodeItem(node, hParent))
    {
        for (size_t i = 0; i < node->m_children.size(); ++i)
        {
            InsertNodeTree(node->m_children[i], hInserted);
        }
        return hInserted;
    }
    return NULL;
}

inline HTREEITEM
MWindowTreeView::InsertNodeItem(const node_type *node, HTREEITEM hParent)
{
    HTREEITEM hItem;
    MString text = text_from_node(node);
    if (node->m_type == MWindowTreeNode::THREAD)
    {
        HICON hIcon = GetIconOfThreadDx(node->m_id, ICON_SMALL);
        if (!hIcon)
            hIcon = GetStdIconDx(IDI_APPLICATION, ICON_SMALL);
        assert(hIcon);
        INT iImage = ImageList_AddIcon(m_himl, hIcon);
        UINT mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT |
                    TVIF_STATE | TVIF_PARAM;
        UINT state = 0;
        if (get_style() & MWTVS_EXPANDED)
        {
            state = TVIS_EXPANDED;
        }
        LPARAM lParam = (LPARAM)node;
        hItem = InsertItem(mask, text.c_str(), iImage, iImage,
                           state, state, lParam, hParent);
        DestroyIcon(hIcon);
    }
    else if (node->m_type == MWindowTreeNode::PROCESS)
    {
        HICON hIcon = GetIconOfProcessDx(node->m_id, ICON_SMALL);
        if (!hIcon)
            hIcon = GetStdIconDx(IDI_APPLICATION, ICON_SMALL);
        assert(hIcon);
        INT iImage = ImageList_AddIcon(m_himl, hIcon);
        UINT mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT |
                    TVIF_STATE | TVIF_PARAM;
        UINT state = 0;
        if (get_style() & MWTVS_EXPANDED)
        {
            state = TVIS_EXPANDED;
        }
        LPARAM lParam = (LPARAM)node;
        hItem = InsertItem(mask, text.c_str(), iImage, iImage,
                           state, state, lParam, hParent);
        DestroyIcon(hIcon);
    }
    else
    {
        HWND hwndTarget = node->m_hwndTarget;
        HICON hIcon = GetIconOfWindowDx(hwndTarget);
        if (!hIcon)
        {
            if (!GetWindow(hwndTarget, GW_OWNER) && !GetParent(hwndTarget))
                hIcon = GetStdIconDx(IDI_APPLICATION, ICON_SMALL);
            else
                hIcon = GetStdIconDx(IDI_INFORMATION, ICON_SMALL);
        }
        assert(hIcon);
        INT iImage = ImageList_AddIcon(m_himl, hIcon);
        UINT mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT |
                    TVIF_STATE | TVIF_PARAM;
        UINT state = 0;
        if ((get_style() & MWTVS_EXPANDED) || node == root())
        {
            state = TVIS_EXPANDED;
        }
        LPARAM lParam = (LPARAM)node;
        hItem = InsertItem(mask, text.c_str(), iImage, iImage,
                           state, state, lParam, hParent);
        DestroyIcon(hIcon);
    }
    return hItem;
}

inline bool
MWindowTreeView::find_text(HTREEITEM& hItem, const MString& text, HTREEITEM hParent) const
{
    node_type *node = NodeFromItem(hParent);
    MString node_text = text_from_node(node);
    if (node_text.find(text) != MString::npos)
    {
        hItem = hParent;
        return true;
    }

    if (HTREEITEM hChild = GetChildItem(hParent))
    {
        do
        {
            if (find_text(hItem, text, hChild))
            {
                return true;
            }
            hChild = GetNextSiblingItem(hChild);
        } while (hChild);
    }

    return false;
}

inline HTREEITEM
MWindowTreeView::ItemFromNode(const node_type *node, HTREEITEM hItem) const
{
    if (!node)
        return NULL;

    const node_type *parent = (const node_type *)GetItemData(hItem);
    if (parent == node)
        return hItem;

    if (HTREEITEM hChild = GetChildItem(hItem))
    {
        do
        {
            if (HTREEITEM hFound = ItemFromNode(node, hChild))
            {
                return hFound;
            }
            hChild = GetNextSiblingItem(hChild);
        } while (hChild);
    }

    return NULL;
}

inline HTREEITEM MWindowTreeView::ItemFromWindow(HWND hwnd) const
{
    if (node_type *node = find_node(hwnd))
        return ItemFromNode(node);
    return NULL;
}

inline HWND MWindowTreeView::WindowFromItem(HTREEITEM hItem) const
{
    if (node_type *node = NodeFromItem(hItem))
    {
        return node->m_hwndTarget;
    }
    return NULL;
}

inline bool MWindowTreeView::select_hwnd(HWND hwnd)
{
    if (node_type *node = find_node(hwnd))
    {
        if (HTREEITEM hItem = ItemFromNode(node))
            return !!SelectItem(hItem);
    }
    return false;
}

inline DWORD MWindowTreeView::get_style() const
{
    return m_MWTVS_;
}

inline void MWindowTreeView::set_style(DWORD style)
{
    m_MWTVS_ = style;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MWINDOWTREEVIEW_HPP_
