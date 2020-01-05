#include <FD3D/SceneGraph/Scene.h>

#include <algorithm>
#include <cassert>
#include <queue>
#include <stack>


FD3D::Scene::Scene()
{
    auto p = new RootNode();
    m_nodes.insert(p->getId(), std::unique_ptr<SceneNode>(p));
}

FD3D::Scene::id_type FD3D::Scene::getRootId() const
{
    return m_rootId;
}

FD3D::ConstSceneNodeProxy FD3D::Scene::getNode(FD3D::Scene::id_type id) const
{
    return ConstSceneNodeProxy(*this, m_nodes[id]->value.get());
}

FD3D::SceneNodeProxy FD3D::Scene::getNode(FD3D::Scene::id_type id)
{
    auto n = m_nodes[id];
    if(n == nullptr)
        return SceneNodeProxy(*this, nullptr);

    return SceneNodeProxy(*this, m_nodes[id]->value.get());
}

void FD3D::Scene::addNode(SceneNode *node)
{
    if(!node->hasParent() || !getNode(node->getParentId()))
        node->setParentId(m_rootId);

    m_nodes.insert(node->getId(), std::unique_ptr<SceneNode>(node));
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

    removeNode(it->value->getId());
}

bool FD3D::Scene::hasNodes() const
{
    return m_nodes.size() > 1;
}

void FD3D::Scene::clearNodes()
{
    m_nodes[0]->value->clearChildIds();
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
    typedef FDCore::AssociativeContainer<
                SceneNode::id_type,
                std::unique_ptr<SceneNode>
            >::cell_type cell_type;

    if(from == 0)
        from = m_rootId;

    std::vector<FD3D::SceneNodeProxy> result;
    if(std::find_if(m_nodes.begin(), m_nodes.end(), [from](const cell_type &node)
        {
            return node.value->getId() == from;
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
    typedef FDCore::AssociativeContainer<
                SceneNode::id_type,
                std::unique_ptr<SceneNode>
            >::cell_type cell_type;

    if(from == 0)
        from = m_rootId;

    std::vector<FD3D::ConstSceneNodeProxy> result;
    if(std::find_if(m_nodes.begin(), m_nodes.end(), [from](const cell_type &node)
        {
            return node.value->getId() == from;
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

FD3D::Component *FD3D::Scene::getComponent(Component::id_type id)
{
    typedef FDCore::AssociativeContainer<
                Component::id_type,
                std::unique_ptr<Component>
            >::cell_type cell_type;
    auto it = std::find_if(m_components.begin(), m_components.end(),
                 [id](const cell_type &c){ return c.value->getId() == id; });

    if(it == m_components.end())
        return nullptr;

    return it->value.get();
}

const FD3D::Component *FD3D::Scene::getComponent(Component::id_type id) const
{
    typedef FDCore::AssociativeContainer<
                Component::id_type,
                std::unique_ptr<Component>
            >::cell_type cell_type;
    auto it = std::find_if(m_components.begin(), m_components.end(),
                 [id](const cell_type &c){ return c.value->getId() == id; });

    if(it == m_components.end())
        return nullptr;

    return it->value.get();
}

void FD3D::Scene::addComponent(Component *comp)
{
    m_components.insert(comp->getId(), std::unique_ptr<Component>(comp));
}

void FD3D::Scene::removeComponent(Component::id_type id)
{
    typedef FDCore::AssociativeContainer<
                Component::id_type,
                std::unique_ptr<Component>
            >::cell_type cell_type;
    auto it = std::find_if(m_components.begin(), m_components.end(),
                 [id](const cell_type &c){ return c.value->getId() == id; });

    if(it == m_components.end())
        return;

    m_components.erase(it);
}

void FD3D::Scene::removeComponentAt(size_t pos)
{
    auto it = m_components.begin();
    std::advance(it, pos);

    if(it == m_components.end())
        return;

    m_components.erase(it);
}

bool FD3D::Scene::hasComponents() const
{
    return !m_components.empty();
}

void FD3D::Scene::clearComponents()
{
    m_components.clear();
}

size_t FD3D::Scene::getComponentCount() const
{
    return m_components.size();
}

std::vector<const FD3D::Component*> FD3D::Scene::findComponentsByName(const std::string &name) const
{
    std::vector<const FD3D::Component*> result;
    for(auto &c : m_components)
    {
        if(c.value->getName() == name)
            result.push_back(c.value.get());
    }

    return result;
}

void FD3D::Scene::bindComponent(Scene::id_type node, Component::id_type comp)
{
    typedef FDCore::AssociativeContainer<
                SceneNode::id_type,
                std::unique_ptr<SceneNode>
            >::cell_type node_cell_type;

    typedef FDCore::AssociativeContainer<
                Component::id_type,
                std::unique_ptr<Component>
            >::cell_type comp_cell_type;

    if(std::find_if(m_nodes.begin(), m_nodes.end(),
        [node](const node_cell_type &n)
        {
            return n.value->getId() == node;
        }) == m_nodes.end())
        return;

    if(std::find_if(m_components.begin(), m_components.end(),
        [comp](const comp_cell_type &c)
        {
            return c.value->getId() == comp;
        }) == m_components.end())
        return;

    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        if(it->value == comp)
            return;
    }

    m_componentBindings.insert(node, comp);
}

void FD3D::Scene::unbindComponent(FD3D::Scene::id_type node, FD3D::Component::id_type comp)
{
    typedef FDCore::AssociativeContainer<id_type, Component::id_type>::cell_type cell_type;
    size_t h = m_componentBindings.hashKey(node);
    m_componentBindings.erase_if([h, comp](const cell_type &cell){
        return cell.key.hash == h && cell.value == comp;
    });
}

std::vector<FD3D::Component::id_type> FD3D::Scene::getNodeComponentIds(FD3D::Scene::id_type node) const
{
    std::vector<FD3D::Component::id_type> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        result.push_back(it->value);
    }

    return result;
}

std::vector<FD3D::Component::id_type>
    FD3D::Scene::getNodeComponentIds(FD3D::Scene::id_type node,
                                     std::function<bool (const FD3D::Component *)> pred) const
{
    std::vector<FD3D::Component::id_type> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        if(pred(getComponent(it->value)))
            result.push_back(it->value);
    }

    return result;
}

std::vector<FD3D::Component*> FD3D::Scene::getNodeComponents(FD3D::Scene::id_type node)
{
    std::vector<FD3D::Component*> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        result.push_back(getComponent(it->value));
    }

    return result;
}

std::vector<const FD3D::Component*> FD3D::Scene::getNodeComponents(FD3D::Scene::id_type node) const
{
    std::vector<const FD3D::Component*> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        result.push_back(getComponent(it->value));
    }

    return result;
}

std::vector<FD3D::Component*>
    FD3D::Scene::getNodeComponents(FD3D::Scene::id_type node,
                                   std::function<bool (const FD3D::Component *)> pred)
{
    std::vector<FD3D::Component*> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        Component *c = getComponent(it->value);
        if(pred(c))
            result.push_back(c);
    }

    return result;
}

std::vector<const FD3D::Component*>
    FD3D::Scene::getNodeComponents(FD3D::Scene::id_type node,
                                   std::function<bool (const FD3D::Component *)> pred) const
{
    std::vector<const FD3D::Component*> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        const Component *c = getComponent(it->value);
        if(pred(c))
            result.push_back(c);
    }

    return result;
}

std::vector<FD3D::Component*> FD3D::Scene::findComponentsByName(const std::string &name)
{
    std::vector<FD3D::Component*> result;
    for(auto &c : m_components)
    {
        if(c.value->getName() == name)
            result.push_back(c.value.get());
    }

    return result;
}

void FD3D::Scene::removeHierarchy(FD3D::Scene::id_type id)
{
    typedef FDCore::AssociativeContainer<
                SceneNode::id_type,
                std::unique_ptr<SceneNode>
            >::cell_type cell_type;

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
                               [id](cell_type &node) { return node.value->getId() == *id; });
        if(it == m_nodes.end())
            return;

        m_nodes.erase(it);
    }
}
