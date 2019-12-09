#include <FD3D/Scene.h>

#include <algorithm>
#include <cassert>
#include <queue>
#include <stack>


FD3D::Scene::Scene()
{
    m_nodes.push_back(RootNode());
}

FD3D::Scene::id_type FD3D::Scene::getRootId() const
{
    return m_rootId;
}

FD3D::ConstSceneNodeProxy FD3D::Scene::getNode(FD3D::Scene::id_type id) const
{
    return ConstSceneNodeProxy(*this, &m_nodes[id]);
}

FD3D::SceneNodeProxy FD3D::Scene::getNode(FD3D::Scene::id_type id)
{
    return SceneNodeProxy(*this, &m_nodes[id]);
}

void FD3D::Scene::addNode(FD3D::SceneNode &&node)
{
    if(!node.hasParent() || !getNode(node.getParentId()))
        node.setParentId(m_rootId);

    m_nodes.push_back(std::move(node));
}

void FD3D::Scene::addNode(const FD3D::SceneNode &node)
{
    FD3D::SceneNode cp(node);
    if(!cp.hasParent() || !getNode(cp.getParentId()))
        cp.setParentId(m_rootId);

    m_nodes.push_back(std::move(node));
}

void FD3D::Scene::removeNode(FD3D::Scene::id_type id)
{
    assert(id != m_rootId && "cannot remove root node");
    removeHierarchy(id);
}

void FD3D::Scene::removeNodeAt(size_t pos)
{
    auto it = m_nodes.begin();
    std::advance(it, pos);
    if(it == m_nodes.end())
        return;

    removeNode(it->getId());
}

bool FD3D::Scene::hasNodes() const
{
    return m_nodes.size() > 1;
}

void FD3D::Scene::clearNodes()
{
    m_nodes[0].clearChildIds();
    auto it = m_nodes.begin();
    ++it;
    m_nodes.erase(it, m_nodes.end());
}

size_t FD3D::Scene::getNodeCount() const
{
    return m_nodes.size();
}

std::vector<FD3D::SceneNodeProxy> FD3D::Scene::findByName(const std::string &name,
                                                          FD3D::Scene::id_type from)
{
    if(from == 0)
        from = m_rootId;

    std::vector<FD3D::SceneNodeProxy> result;
    if(std::find_if(m_nodes.begin(), m_nodes.end(), [from](const SceneNode &node)
        {
            return node.getId() == from;
        }) == m_nodes.end())
    {
        return result;
    }

    std::queue<FD3D::Scene::id_type> todo;
    todo.push(from);
    while(!todo.empty())
    {
        SceneNodeProxy node = getNode(todo.front());
        todo.pop();
        if(!node)
            continue;

        for(FD3D::Scene::id_type id: node->getChildIds())
            todo.push(id);

        if(node->getName() == name)
            result.push_back(std::move(node));
    }

    return result;
}

std::vector<FD3D::ConstSceneNodeProxy> FD3D::Scene::findByName(const std::string &name,
                                                               FD3D::Scene::id_type from) const
{
    if(from == 0)
        from = m_rootId;

    std::vector<FD3D::ConstSceneNodeProxy> result;
    if(std::find_if(m_nodes.begin(), m_nodes.end(), [from](const SceneNode &node)
        {
            return node.getId() == from;
        }) == m_nodes.end())
    {
        return result;
    }

    std::queue<FD3D::Scene::id_type> todo;
    todo.push(from);
    while(!todo.empty())
    {
        ConstSceneNodeProxy node = getNode(todo.front());
        todo.pop();
        if(!node)
            continue;

        for(FD3D::Scene::id_type id: node->getChildIds())
            todo.push(id);

        if(node->getName() == name)
            result.push_back(std::move(node));
    }

    return result;
}

void FD3D::Scene::removeHierarchy(FD3D::Scene::id_type id)
{
    std::vector<FD3D::Scene::id_type> toErase;
    std::stack<FD3D::Scene::id_type> todo;
    todo.push(id);
    {
        auto node = getNode(id);
        if(!node)
            return;

        node = getNode(node->getParentId());
        node->removeChildId(id);
    }
    while(!todo.empty())
    {
        FD3D::Scene::id_type current = todo.top();
        todo.pop();

        toErase.push_back(current);
        auto node = getNode(current);
        for(size_t i = 0, imax = node->getChildIdCount(); i < imax; ++i)
            todo.push(node->getChildId(i));
    }

    for(auto id = toErase.begin(), end = toErase.end(); id != end; ++id)
    {
        auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
                               [id](const SceneNode &node) { return node.getId() == *id; });
        if(it == m_nodes.end())
            return;

        m_nodes.erase(it);
    }
}
