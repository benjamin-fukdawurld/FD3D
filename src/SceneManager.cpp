#include <FD3D/SceneGraph/SceneManager.h>
#include <FD3D/Material/Material.h>
#include <FD3D/Camera/Camera.h>
#include <FD3D/Light/Light.h>
#include <FD3D/Mesh/Mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <iostream>
#include <cassert>

FD3D::SceneManager::SceneManager(FD3D::Scene *scene, FDCore::ResourceManager *resourceMgr) :
    m_scene(scene),
    m_resourceMgr(resourceMgr)
{}

FD3D::SceneManager::EventHandler FD3D::SceneManager::findHandler(std::string_view event_name, std::string_view type_code) const
{
    const_event_iterator it = m_eventMap.find(event_name.data());
    if(it == m_eventMap.end())
        return EventHandler();

    EventHandlerMap::const_iterator h_it = it->value.find(type_code.data());
    if(h_it == it->value.end())
        return EventHandler();

    return h_it->value;
}

void FD3D::SceneManager::prepareIdIndexMap()
{
    if(!m_scene)
        return;

    m_idIndexMap.reserve(m_scene->getNodeCount() + m_scene->getComponentCount() + 1);
    m_idIndexMap.insert(0, -1);

    for(auto &[key, value]: m_scene->getComponents())
        m_idIndexMap.insert(value->getId(), static_cast<int>(m_idIndexMap.size()));

    for(auto &[key, value]: m_scene->getNodes())
        m_idIndexMap.insert(value->getId(), static_cast<int>(m_idIndexMap.size()));
}

void FD3D::SceneManager::clearIdIndexMap()
{
    m_idIndexMap.clear();
}

int FD3D::SceneManager::getIdIndex(FD3D::Element::id_type id) const
{
    auto it = m_idIndexMap.find(id);
    if(it == m_idIndexMap.end())
        return -2;

    return it->value;
}

void FD3D::SceneManager::setIdIndex(FD3D::Element::id_type id, int index)
{
    assert(!m_idIndexMap.contains(id) && "id is already set");
    m_idIndexMap.insert(id, index);
}

FD3D::Element::id_type FD3D::SceneManager::getIndexId(int index)
{
    if(index < 0)
        return 0;

    auto it = m_idIndexMap.find_if([index](const IdIndexMap::cell_type &cell)
    {
        return cell.value == index;
    });
    if(it == m_idIndexMap.end())
        return 0;

    return it->key.hash;
}
