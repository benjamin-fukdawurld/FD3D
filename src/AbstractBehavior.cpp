#include <FD3D/Behavior/AbstractBehavior.h>

bool FD3D::AbstractBehavior::hasScene() const
{
    return getScene() != nullptr;
}

bool FD3D::AbstractBehavior::hasNode() const
{
    return getNodeId() != 0;
}

FD3D::SceneNodeProxy FD3D::AbstractBehavior::getNode()
{
    return getScene()->getNode(getNodeId());
}

FD3D::ConstSceneNodeProxy FD3D::AbstractBehavior::getNode() const
{
    return getScene()->getNode(getNodeId());
}

const char *FD3D::AbstractBehavior::getTypeCode() const
{
    return FDCore::TypeCodeHelper<AbstractBehavior>::code;
}

size_t FD3D::AbstractBehavior::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<AbstractBehavior>::hash();
}

bool FD3D::AbstractBehavior::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::AbstractBehavior::getTypeCodeHash()
            || FDCore::Object::matchTypeCodeHash(hash);
}
