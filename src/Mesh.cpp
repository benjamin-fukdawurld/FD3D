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

FD3D::Mesh::~Mesh()
{

}

const char *FD3D::Mesh::getTypeCode() const
{
    return FDCore::TypeCodeHelper<Mesh>::code;
}

size_t FD3D::Mesh::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<Mesh>::hash();
}
