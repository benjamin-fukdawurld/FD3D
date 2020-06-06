#include <FD3D/Behavior/BaseBehavior.h>

FD3D::BaseBehavior::BaseBehavior() :
    BaseBehavior(nullptr, 0)
{}

FD3D::BaseBehavior::BaseBehavior(FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId) :
    m_scene(scene),
    m_nodeId(nodeId)
{}

FD3D::BaseBehavior::~BaseBehavior()
{}

FD3D::Scene *FD3D::BaseBehavior::getScene()
{
    return m_scene;
}

const FD3D::Scene *FD3D::BaseBehavior::getScene() const
{
    return m_scene;
}

void FD3D::BaseBehavior::setScene(FD3D::Scene *scene)
{
    m_scene = scene;
}

FD3D::SceneNode::id_type FD3D::BaseBehavior::getNodeId() const
{
    return m_nodeId;
}

void FD3D::BaseBehavior::setNodeId(FD3D::SceneNode::id_type id)
{
    m_nodeId = id;
}

void FD3D::BaseBehavior::init() {}

void FD3D::BaseBehavior::quit() {}

void FD3D::BaseBehavior::update() {}

void FD3D::BaseBehavior::onDisable() {}

void FD3D::BaseBehavior::onEnable() {}

const char *FD3D::BaseBehavior::getTypeCode() const
{
    return FDCore::TypeCodeHelper<BaseBehavior>::code;
}

size_t FD3D::BaseBehavior::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<BaseBehavior>::hash();
}

bool FD3D::BaseBehavior::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::BaseBehavior::getTypeCodeHash() || FD3D::AbstractBehavior::matchTypeCodeHash(hash);
}
