#include <FD3D/Mesh/MeshComponent.h>


FD3D::MeshComponent::MeshComponent() : AbstractMeshComponent()
{

}

FD3D::MeshComponent::MeshComponent(std::vector<float> &&vertices, std::vector<uint32_t> &&indices) :
    AbstractMeshComponent(),
    m_vertices(std::move(vertices)),
    m_indices(std::move(indices))
{}

FD3D::MeshComponent::MeshComponent(const std::vector<float> &vertices, const std::vector<uint32_t> &indices) :
    AbstractMeshComponent(),
    m_vertices(vertices),
    m_indices(indices)
{}

FD3D::MeshComponent::~MeshComponent()
{

}

void FD3D::MeshComponent::setVertices(const float *data)
{
    memcpy(m_vertices.data(), data, getVerticesDataSize());
}

void FD3D::MeshComponent::setIndices(const uint32_t *data)
{
    memcpy(m_indices.data(), data, getIndicesDataSize());
}

const char *FD3D::MeshComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<MeshComponent>::code;
}

size_t FD3D::MeshComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<MeshComponent>::hash();
}

bool FD3D::MeshComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::MeshComponent::getTypeCodeHash() || AbstractMeshComponent::matchTypeCodeHash(hash);
}
