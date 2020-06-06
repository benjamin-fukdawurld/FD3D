#include <FD3D/Behavior/BehaviorComponent.h>

FD3D::BehaviorComponent::BehaviorComponent() :
    BehaviorComponent(nullptr, 0)
{}

FD3D::BehaviorComponent::BehaviorComponent(FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId) :
    m_scene(scene),
    m_nodeId(nodeId)
{}

FD3D::BehaviorComponent::~BehaviorComponent()
{}

FD3D::Scene *FD3D::BehaviorComponent::getScene()
{
    return m_scene;
}

const FD3D::Scene *FD3D::BehaviorComponent::getScene() const
{
    return m_scene;
}

void FD3D::BehaviorComponent::setScene(FD3D::Scene *scene)
{
    m_scene = scene;
}

FD3D::SceneNode::id_type FD3D::BehaviorComponent::getNodeId() const
{
    return m_nodeId;
}

void FD3D::BehaviorComponent::setNodeId(FD3D::SceneNode::id_type id)
{
    m_nodeId = id;
}

void FD3D::BehaviorComponent::init() {}

void FD3D::BehaviorComponent::quit() {}

void FD3D::BehaviorComponent::update() {}

void FD3D::BehaviorComponent::onDisable() {}

void FD3D::BehaviorComponent::onEnable() {}

const char *FD3D::BehaviorComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<BehaviorComponent>::code;
}

size_t FD3D::BehaviorComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<BehaviorComponent>::hash();
}

bool FD3D::BehaviorComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::BehaviorComponent::getTypeCodeHash() || FD3D::AbstractBehaviorComponent::matchTypeCodeHash(hash);
}
