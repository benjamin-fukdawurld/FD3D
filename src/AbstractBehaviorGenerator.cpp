#include <FD3D/Behavior/AbstractBehaviorGenerator.h>


std::unique_ptr<FD3D::AbstractBehavior> FD3D::AbstractBehaviorGenerator::generateBehavior(FD3D::Scene &scene,
                                                                                          FD3D::Scene::node_id_type nodeId,
                                                                                          void *data)
{
    std::unique_ptr<FD3D::AbstractBehavior> result = generateBehavior(data);
    result->setScene(&scene);
    result->setNodeId(nodeId);

    return result;
}

const char *FD3D::AbstractBehaviorGenerator::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::AbstractBehaviorGenerator>::code;
}

size_t FD3D::AbstractBehaviorGenerator::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::AbstractBehaviorGenerator>::hash();
}

bool FD3D::AbstractBehaviorGenerator::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::AbstractBehaviorGenerator>::hash()
            || FDCore::BaseResource::matchTypeCodeHash(hash);
}
