#include <FD3D/Behavior/AbstractBehaviorComponent.h>


bool FD3D::AbstractBehaviorComponent::hasScene() const
{
    return getScene() != nullptr;
}

bool FD3D::AbstractBehaviorComponent::hasNode() const
{
    return getNodeId() != 0;
}

FD3D::SceneNodeProxy FD3D::AbstractBehaviorComponent::getNode()
{
    return getScene()->getNode(getNodeId());
}

FD3D::ConstSceneNodeProxy FD3D::AbstractBehaviorComponent::getNode() const
{
    return getScene()->getNode(getNodeId());
}

const char *FD3D::AbstractBehaviorComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<AbstractBehaviorComponent>::code;
}

size_t FD3D::AbstractBehaviorComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<AbstractBehaviorComponent>::hash();
}

bool FD3D::AbstractBehaviorComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::AbstractBehaviorComponent::getTypeCodeHash() || Component::matchTypeCodeHash(hash);
}
