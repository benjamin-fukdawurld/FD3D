#include <FD3D/Behavior/Behavior.h>

FD3D::Behavior::Behavior() :
    Behavior(nullptr, 0)
{}

FD3D::Behavior::Behavior(FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId) :
    m_scene(scene),
    m_nodeId(nodeId)
{}

bool FD3D::Behavior::hasScene() const
{
    return m_scene != nullptr;
}

FD3D::Scene *FD3D::Behavior::getScene()
{
    return m_scene;
}

const FD3D::Scene *FD3D::Behavior::getScene() const
{
    return m_scene;
}

void FD3D::Behavior::setScene(FD3D::Scene *scene)
{
    m_scene = scene;
}

bool FD3D::Behavior::hasNode() const
{
    return m_nodeId != 0;
}

FD3D::SceneNode::id_type FD3D::Behavior::getNodeId() const
{
    return m_nodeId;
}

void FD3D::Behavior::setNodeId(FD3D::SceneNode::id_type id)
{
    m_nodeId = id;
}

FD3D::SceneNodeProxy FD3D::Behavior::getNode()
{
    return m_scene->getNode(m_nodeId);
}

FD3D::ConstSceneNodeProxy FD3D::Behavior::getNode() const
{
    return const_cast<const FD3D::Scene*>(m_scene)->getNode(m_nodeId);
}

void FD3D::Behavior::init() {}

void FD3D::Behavior::quit() {}

void FD3D::Behavior::update() {}

void FD3D::Behavior::onDisable() {}

void FD3D::Behavior::onEnable() {}

const char *FD3D::Behavior::getTypeCode() const
{
    return FDCore::TypeCodeHelper<Behavior>::code;
}

size_t FD3D::Behavior::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<Behavior>::hash();
}

bool FD3D::Behavior::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::Behavior::getTypeCodeHash() || Component::matchTypeCodeHash(hash);
}
