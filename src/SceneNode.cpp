#include <FD3D/SceneGraph/SceneNode.h>

#include <algorithm>
#include <cassert>

FD3D::SceneNode::SceneNode(id_type parent) : m_parent(parent) {}

FD3D::SceneNode::SceneNode(FD3D::SceneNode &&node) :
    Identifiable<>(),
    m_name(std::move(node.m_name)),
    m_children(std::move(node.m_children)),
    m_parent(node.m_parent)
{

}

FD3D::SceneNode::SceneNode(const FD3D::SceneNode &node) :
    Identifiable<>(),
    m_name(node.m_name),
    m_children(node.m_children),
    m_parent(node.m_parent)
{

}

FD3D::SceneNode &FD3D::SceneNode::operator=(SceneNode &&node)
{
    m_parent = node.m_parent;
    m_name = std::move(node.m_name);
    m_children = std::move(node.m_children);

    return *this;
}

FD3D::SceneNode &FD3D::SceneNode::operator=(const SceneNode &node)
{
    m_parent = node.m_parent;
    m_name = std::move(node.m_name);
    m_children = std::move(node.m_children);

    return *this;
}

FD3D::SceneNode::~SceneNode() {}

const std::string &FD3D::SceneNode::getName() const
{
    return m_name;
}

void FD3D::SceneNode::setName(const std::string &name)
{
    m_name = name;
}

const std::vector<FD3D::SceneNode::id_type> &FD3D::SceneNode::getChildIds() const
{
    return m_children;
}

void FD3D::SceneNode::setChildIds(std::vector<FD3D::SceneNode::id_type> &&children)
{
    m_children = std::move(children);
}

void FD3D::SceneNode::setChildIds(const std::vector<FD3D::SceneNode::id_type> &children)
{
    m_children = children;
}

FD3D::SceneNode::id_type &FD3D::SceneNode::getChildId(size_t index)
{
    return m_children[index];
}

const FD3D::SceneNode::id_type &FD3D::SceneNode::getChildId(size_t index) const
{
    return m_children[index];
}

void FD3D::SceneNode::addChildId(FD3D::SceneNode::id_type id)
{
    assert(id != 0);
    m_children.push_back(id);
}

void FD3D::SceneNode::removeChildId(FD3D::SceneNode::id_type id)
{
    auto it = std::find(m_children.begin(), m_children.end(), id);
    m_children.erase(it);
}

void FD3D::SceneNode::removeChildIdAt(size_t pos)
{
    auto it = m_children.begin();
    std::advance(it, pos);
    m_children.erase(it);
}

bool FD3D::SceneNode::hasChildren() const
{
    return !m_children.empty();
}

size_t FD3D::SceneNode::getChildIdCount() const
{
    return m_children.size();
}

void FD3D::SceneNode::reserveChildIds(size_t size)
{
    m_children.reserve(size);
}

void FD3D::SceneNode::clearChildIds()
{
    m_children.clear();
}

FD3D::SceneNode::child_iterator FD3D::SceneNode::childIdsBegin()
{
    return m_children.begin();
}

FD3D::SceneNode::const_child_iterator FD3D::SceneNode::childIdsBegin() const
{
    return m_children.begin();
}

FD3D::SceneNode::const_child_iterator FD3D::SceneNode::childIdsConstBegin() const
{
    return m_children.cbegin();
}

FD3D::SceneNode::child_iterator FD3D::SceneNode::childIdsEnd()
{
    return m_children.end();
}

FD3D::SceneNode::const_child_iterator FD3D::SceneNode::childIdsEnd() const
{
    return m_children.end();
}

FD3D::SceneNode::const_child_iterator FD3D::SceneNode::childIdsConstEnd() const
{
    return m_children.cend();
}

FD3D::SceneNode::reverse_child_iterator FD3D::SceneNode::childIdsReverseBegin()
{
    return m_children.rbegin();
}

FD3D::SceneNode::const_reverse_child_iterator FD3D::SceneNode::childIdsReverseBegin() const
{
    return m_children.rbegin();
}

FD3D::SceneNode::const_reverse_child_iterator FD3D::SceneNode::childIdsConstReverseBegin() const
{
    return m_children.crbegin();
}

FD3D::SceneNode::reverse_child_iterator FD3D::SceneNode::childIdsReverseEnd()
{
    return m_children.rend();
}

FD3D::SceneNode::const_reverse_child_iterator FD3D::SceneNode::childIdsReverseEnd() const
{
    return m_children.rend();
}

FD3D::SceneNode::const_reverse_child_iterator FD3D::SceneNode::childIdsConstReverseEnd() const
{
    return m_children.rend();
}

bool FD3D::SceneNode::hasParent() const
{
    return m_parent != 0;
}

FD3D::SceneNode::id_type FD3D::SceneNode::getParentId() const
{
    return m_parent;
}

void FD3D::SceneNode::setParentId(FD3D::SceneNode::id_type parent)
{
    m_parent = parent;
}

const char *FD3D::SceneNode::getTypeCode() const
{
    return "";
}

size_t FD3D::SceneNode::getTypeCodeHash() const
{
    return 0;
}
