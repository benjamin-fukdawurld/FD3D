#include <FD3D/Mesh/Mesh.h>

FD3D::Mesh::Mesh() : AbstractMesh()
{

}

FD3D::Mesh::Mesh(std::vector<float> &&vertices, std::vector<uint32_t> &&indices) :
    AbstractMesh(),
    m_vertices(std::move(vertices)),
    m_indices(std::move(indices))
{}

FD3D::Mesh::Mesh(const std::vector<float> &vertices, const std::vector<uint32_t> &indices) :
    AbstractMesh(),
    m_vertices(vertices),
    m_indices(indices)
{}

bool FD3D::Mesh::load() { return true; }

bool FD3D::Mesh::isLoaded() const { return true; }

void FD3D::Mesh::release() {}

void FD3D::Mesh::setVertices(const float *data)
{
    memcpy(m_vertices.data(), data, getVerticesDataSize());
}

void FD3D::Mesh::setIndices(const uint32_t *data)
{
    memcpy(m_indices.data(), data, getIndicesDataSize());
}

const char *FD3D::Mesh::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::Mesh>::code;
}

size_t FD3D::Mesh::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::Mesh>::hash();
}

bool FD3D::Mesh::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::Mesh>::hash()
            || FD3D::AbstractMesh::matchTypeCodeHash(hash);
}
