// MWindowTreeView.hpp -- MZC4 window tree view             -*- C++ -*-
// This file is part of MZC4.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef MZC4_MWINDOWTREEVIEW_HPP_
#define MZC4_MWINDOWTREEVIEW_HPP_     6       /* Version 6 */

#include "MTreeView.hpp"
#include <shellapi.h>   // for SHGetFileInfo
#include <psapi.h>      // for GetModuleFileNameEx
#include <vector>       // for std::vector
#include <algorithm>    // for std::sort and std::unique

#include "ProcessWindowIcon.hpp"

////////////////////////////////////////////////////////////////////////////
// MWindowTree

struct MWindowTreeNode
{
    HWND m_hwnd;
    DWORD m_pid;
    std::vector<MWindowTreeNode *> m_children;

    MWindowTreeNode(HWND hwnd = NULL);
    ~MWindowTreeNode();

    MWindowTreeNode *find(HWND hwnd);
    void insert(HWND hwnd);

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

    struct RELATION
    {
        HWND m_hwndParent;
        HWND m_hwnd;

        RELATION();
        RELATION(HWND hwnd1, HWND hwnd2);
        bool operator<(const RELATION& other) const;
        bool operator==(const RELATION& other) const;
    };
    typedef std::vector<RELATION> relations_type;

    typedef MWindowTreeNode node_type;

    bool get_tree(bool do_distribute = true);
    MWindowTreeNode *root() const;

    bool distribute();

    bool empty() const;
    void clear();

    static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

protected:
    MWindowTreeNode *m_root;

    bool insert_by_relation(const RELATION& relation);
    bool get_relations(relations_type& relations);

private:
    MWindowTree(const MWindowTree&);
    MWindowTree& operator=(const MWindowTree&);
};

////////////////////////////////////////////////////////////////////////////
// MWindowTreeView

enum MWindowTreeViewStyle
{
    MWTVS_PROCESSVIEW = 0x0001,
    MWTVS_DESKTOPVIEW = 0x0002,
    MWTVS_EXPANDED = 0x0004,
};

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
    DWORD m_style;  // See MWindowTreeViewStyle.

    void ReCreateTreeImageList();
};

////////////////////////////////////////////////////////////////////////////
// MWindowTreeNode inlines

inline MWindowTreeNode::MWindowTreeNode(HWND hwnd) : m_hwnd(hwnd), m_pid(0)
{
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
    if (m_hwnd == hwnd)
        return this;

    for (size_t i = 0; i < m_children.size(); ++i)
    {
        if (MWindowTreeNode *node = m_children[i]->find(hwnd))
            return node;
    }
    return NULL;
}

inline void MWindowTreeNode::insert(HWND hwnd)
{
    MWindowTreeNode *node = new MWindowTreeNode(hwnd);
    m_children.push_back(node);
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

inline MWindowTree::RELATION::RELATION()
{
}

inline MWindowTree::RELATION::RELATION(HWND hwnd1, HWND hwnd2)
    : m_hwndParent(hwnd1), m_hwnd(hwnd2)
{
}

inline bool MWindowTree::RELATION::operator<(const RELATION& other) const
{
    if (m_hwndParent < other.m_hwndParent)
        return true;
    if (m_hwndParent > other.m_hwndParent)
        return false;
    return (m_hwnd < other.m_hwnd);
}

inline bool MWindowTree::RELATION::operator==(const RELATION& other) const
{
    return (m_hwndParent == other.m_hwndParent && m_hwnd == other.m_hwnd);
}

inline BOOL CALLBACK MWindowTree::EnumChildProc(HWND hwnd, LPARAM lParam)
{
    relations_type *relations = (relations_type *)lParam;
    HWND hwndOwnerOrParent = ::GetWindow(hwnd, GW_OWNER);
    if (!hwndOwnerOrParent)
        hwndOwnerOrParent = ::GetParent(hwnd);
    RELATION relation(hwndOwnerOrParent, hwnd);
    relations->push_back(relation);
    ::EnumChildWindows(hwnd, MWindowTree::EnumChildProc, lParam);
    return TRUE;
}

inline BOOL CALLBACK MWindowTree::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    relations_type *relations = (relations_type *)lParam;
    HWND hwndOwner = ::GetWindow(hwnd, GW_OWNER);
    RELATION relation(hwndOwner, hwnd);
    relations->push_back(relation);
    ::EnumChildWindows(hwnd, MWindowTree::EnumChildProc, lParam);
    return TRUE;
}

inline bool MWindowTree::insert_by_relation(const RELATION& relation)
{
    HWND hwndTarget = relation.m_hwnd;
    if (hwndTarget == GetDesktopWindow() || !::IsWindow(hwndTarget))
        return false;

    if (relation.m_hwndParent)
    {
        if (MWindowTreeNode *parent = m_root->find(relation.m_hwndParent))
        {
            parent->insert(hwndTarget);
            return true;
        }
    }
    else
    {
        m_root->insert(hwndTarget);
        return true;
    }

    return false;
}

inline bool MWindowTree::get_relations(relations_type& relations)
{
    if (!::EnumWindows(MWindowTree::EnumWindowsProc, (LPARAM)&relations))
        return false;

    return !relations.empty();
}

bool MWindowTree::empty() const
{
    return m_root == NULL || m_root->m_children.empty();
}

inline bool MWindowTree::get_tree(bool do_distribute)
{
    clear();

    relations_type relations;
    if (!get_relations(relations))
        return false;

    std::sort(relations.begin(), relations.end());
    relations.erase(std::unique(relations.begin(), relations.end()), relations.end());

    m_root = new MWindowTreeNode(::GetDesktopWindow());

    for (size_t i = 0; i < relations.size(); ++i)
    {
        insert_by_relation(relations[i]);
    }

    if (do_distribute)
        distribute();

    return !empty();
}

inline bool MWindowTree::distribute()
{
    if (!m_root)
        return false;

    MWindowTreeNode *new_root = new MWindowTreeNode();
    MWindowTreeNode *old_root = m_root;

    for (size_t i = 0; i < old_root->m_children.size(); ++i)
    {
        MWindowTreeNode *child = old_root->m_children[i];
        DWORD pid = ProcessFromWindowDx(child->m_hwnd);

        size_t k;
        for (k = 0; k < new_root->m_children.size(); ++k)
        {
            if (new_root->m_children[k]->m_pid == pid)
            {
                new_root->m_children[k]->m_children.push_back(child);
                break;
            }
        }
        if (k == new_root->m_children.size())
        {
            MWindowTreeNode *new_child = new MWindowTreeNode();
            new_child->m_pid = pid;
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
    bool do_distribute = !!(get_style() & MWTVS_PROCESSVIEW);
    if (m_tree.get_tree(do_distribute))
    {
        if (do_distribute)
        {
            MWindowTreeNode *the_root = root();
            for (size_t i = 0; i < the_root->m_children.size(); ++i)
            {
                InsertNodeTree(the_root->m_children[i]);
            }
        }
        else
        {
            InsertNodeTree(root());
        }
    }
    SendMessageDx(WM_SETREDRAW, TRUE);
    return false;
}

inline MString MWindowTreeView::text_from_node(const node_type *node) const
{
    if (node->m_pid)
    {
        DWORD pid = node->m_pid;

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
        }

        strText += strPath;
        return strText;
    }
    else
    {
        HWND hwndTarget = node->m_hwnd;

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
    if (node->m_pid)
    {
        HICON hIcon = GetIconOfProcessDx(node->m_pid, ICON_SMALL);
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
        HWND hwndTarget = node->m_hwnd;
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
        if (get_style() & MWTVS_EXPANDED)
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
        return node->m_hwnd;
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
    return m_style;
}

inline void MWindowTreeView::set_style(DWORD style)
{
    m_style = style;
}

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MZC4_MWINDOWTREEVIEW_HPP_
