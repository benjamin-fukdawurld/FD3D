#include <FD3D/SceneGraph/Scene.h>

#include <algorithm>
#include <cassert>
#include <queue>
#include <stack>


FD3D::Scene::Scene() :
    m_rootId(0)
{
    init();
}

FD3D::Scene::node_id_type FD3D::Scene::getRootId() const
{
    return m_rootId;
}

void FD3D::Scene::clear()
{
    m_components.clear();
    m_componentBindings.clear();
    m_nodes.clear();

    m_rootId = 0;
    init();
}

FD3D::ConstSceneNodeProxy FD3D::Scene::getNode(FD3D::Scene::node_id_type id) const
{
    return ConstSceneNodeProxy(*this, m_nodes[id]->get());
}

FD3D::SceneNodeProxy FD3D::Scene::getNode(FD3D::Scene::node_id_type id)
{
    auto n = m_nodes[id];
    if(n == nullptr)
        return SceneNodeProxy(*this, nullptr);

    return SceneNodeProxy(*this, m_nodes[id]->get());
}

void FD3D::Scene::addNode(SceneNode *node)
{
    if(!node->hasParent() || !getNode(node->getParentId()))
    {
        node->setParentId(m_rootId);
        getNode(m_rootId)->addChildId(node->getId());
    }

    m_nodes.insert(node->getId(), std::unique_ptr<SceneNode>(node));
}

void FD3D::Scene::removeNode(FD3D::Scene::node_id_type id)
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
    m_nodes[0]->get()->clearChildIds();
    auto it = m_nodes.begin();
    ++it;
    m_nodes.erase(it, m_nodes.end());
}

size_t FD3D::Scene::getNodeCount() const
{
    return m_nodes.size();
}

std::vector<FD3D::SceneNodeProxy> FD3D::Scene::findByName(const std::string &name,
                                                          FD3D::Scene::node_id_type from)
{
    typedef NodeMap::cell_type cell_type;

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

    std::queue<FD3D::Scene::node_id_type> todo;
    todo.push(from);
    while(!todo.empty())
    {
        SceneNodeProxy node = getNode(todo.front());
        todo.pop();
        if(!node)
            continue;

        for(FD3D::Scene::node_id_type id: node->getChildIds())
            todo.push(id);

        if(node->getName() == name)
            result.push_back(std::move(node));
    }

    return result;
}

std::vector<FD3D::ConstSceneNodeProxy> FD3D::Scene::findByName(const std::string &name,
                                                               FD3D::Scene::node_id_type from) const
{
    typedef NodeMap::cell_type cell_type;

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

    std::queue<FD3D::Scene::node_id_type> todo;
    todo.push(from);
    while(!todo.empty())
    {
        ConstSceneNodeProxy node = getNode(todo.front());
        todo.pop();
        if(!node)
            continue;

        for(FD3D::Scene::node_id_type id: node->getChildIds())
            todo.push(id);

        if(node->getName() == name)
            result.push_back(std::move(node));
    }

    return result;
}

FD3D::Component *FD3D::Scene::getComponent(Component::id_type id)
{
    typedef ComponentMap::cell_type cell_type;

    auto it = std::find_if(m_components.begin(), m_components.end(),
                 [id](const cell_type &c){ return c.value->getId() == id; });

    if(it == m_components.end())
        return nullptr;

    return it->value.get();
}

const FD3D::Component *FD3D::Scene::getComponent(Component::id_type id) const
{
    typedef ComponentMap::cell_type cell_type;

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
    typedef ComponentMap::cell_type cell_type;

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

void FD3D::Scene::bindComponent(Scene::node_id_type node, Component::id_type comp)
{
    typedef NodeMap::cell_type node_cell_type;

    typedef ComponentMap::cell_type comp_cell_type;

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

void FD3D::Scene::unbindComponent(FD3D::Scene::node_id_type node, FD3D::Component::id_type comp)
{
    typedef BindingMap::cell_type cell_type;
    size_t h = m_componentBindings.hashKey(node);
    m_componentBindings.erase_if([h, comp](const cell_type &cell){
        return cell.key.hash == h && cell.value == comp;
    });
}

std::vector<FD3D::Component::id_type> FD3D::Scene::getNodeComponentIds(FD3D::Scene::node_id_type node) const
{
    std::vector<FD3D::Component::id_type> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        result.push_back(it->value);
    }

    return result;
}

std::vector<FD3D::Component::id_type>
    FD3D::Scene::getNodeComponentIds(FD3D::Scene::node_id_type node,
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

std::vector<FD3D::Component*> FD3D::Scene::getNodeComponents(FD3D::Scene::node_id_type node)
{
    std::vector<FD3D::Component*> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        result.push_back(getComponent(it->value));
    }

    return result;
}

std::vector<const FD3D::Component*> FD3D::Scene::getNodeComponents(FD3D::Scene::node_id_type node) const
{
    std::vector<const FD3D::Component*> result;
    for(auto it = m_componentBindings.find(node), end = m_componentBindings.end(); it != end; ++it)
    {
        result.push_back(getComponent(it->value));
    }

    return result;
}

std::vector<FD3D::Component*>
    FD3D::Scene::getNodeComponents(FD3D::Scene::node_id_type node,
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
    FD3D::Scene::getNodeComponents(FD3D::Scene::node_id_type node,
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

std::vector<FD3D::SceneNodeProxy> FD3D::Scene::getBoundNodes(component_id_type comp)
{
    std::vector<BindingMap::iterator> v = m_componentBindings.find_all_if([comp](const BindingMap::cell_type &cell){
        return cell.value == comp;
    });

    std::vector<FD3D::SceneNodeProxy> result;
    result.reserve(v.size());
    for(auto &b : v)
        result.push_back(getNode(b->key.hash));

    return result;
}

std::vector<FD3D::ConstSceneNodeProxy> FD3D::Scene::getBoundNodes(component_id_type comp) const
{
    std::vector<BindingMap::const_iterator> v = const_cast<const BindingMap&>(m_componentBindings).find_all_if([comp](const BindingMap::cell_type &cell){
        return cell.value == comp;
    });

    std::vector<FD3D::ConstSceneNodeProxy> result;
    result.reserve(v.size());
    for(auto &b : v)
        result.push_back(getNode(b->key.hash));

    return result;
}

void FD3D::Scene::init()
{
    if(m_rootId != 0)
        return;

    auto p = new RootNode();
    m_nodes.insert(p->getId(), std::unique_ptr<SceneNode>(p));
    m_rootId = p->getId();
}

void FD3D::Scene::removeNodeComponents(FD3D::SceneNode::id_type id)
{
    auto begin = m_componentBindings.find(id);
    if(begin == m_componentBindings.end())
        return;

    auto v = getNodeComponentIds(id);
    for(auto c: v)
    {
        size_t s = m_componentBindings.count_if([c](const FDCore::AssociativeContainer<node_id_type, Component::id_type>::cell_type &cell)
        {
            return cell.value == c;
        });

        if(s < 2)
            m_components.erase(c);
    }

    auto end = m_componentBindings.find_last(id);
    if(begin == end)
        m_componentBindings.erase(begin);
    else
        m_componentBindings.erase(begin, end);
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

void FD3D::Scene::removeHierarchy(FD3D::Scene::node_id_type id)
{
    typedef NodeMap::cell_type cell_type;

    std::vector<FD3D::Scene::node_id_type> toErase;
    std::stack<FD3D::Scene::node_id_type> todo;
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
        FD3D::Scene::node_id_type current = todo.top();
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
