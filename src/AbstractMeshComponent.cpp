#include <FD3D/Mesh/AbstractMeshComponent.h>

#include <FD3D/Utils/VertexProxy.h>

#include <assimp/mesh.h>

FD3D::AbstractMeshComponent::AbstractMeshComponent() :
    m_materialId(0),
    m_shaderId(0),
    m_nbColorChannels(0),
    m_nbTexChannels(0),
    m_options(MeshOption::Interlaced)
{}

int FD3D::AbstractMeshComponent::getComponentOffset(FD3D::VertexComponentType comp) const
{
    if(!hasVertexComponent(comp))
        return -1;

    switch(comp)
    {
        case VertexComponentType::Position:
        return 0;

        case VertexComponentType::Normal:
        return 3 * (isInterlaced() ? 1 : static_cast<int>(getNumberOfVertices()));

        case VertexComponentType::Tangent:
        return (hasVertexComponent(VertexComponentType::Normal) ? 6 : 3)
                * (isInterlaced() ? 1 : static_cast<int>(getNumberOfVertices()));

        case VertexComponentType::Texture:
        return ((hasVertexComponent(VertexComponentType::Normal) ? 6 : 3)
                + (hasVertexComponent(VertexComponentType::Tangent) ? 6 : 0))
                * (isInterlaced() ? 1 : static_cast<int>(getNumberOfVertices()));

        case VertexComponentType::Color:
        return ((hasVertexComponent(VertexComponentType::Normal) ? 6 : 3)
                + (hasVertexComponent(VertexComponentType::Tangent) ? 6 : 0)
                + (hasVertexComponent(VertexComponentType::Texture)
                   ? 2 * m_nbTexChannels : 0))
                * (isInterlaced() ? 1 : static_cast<int>(getNumberOfVertices()));

        case VertexComponentType::Invalid:
        return -1;
    }

    return -1;
}

size_t FD3D::AbstractMeshComponent::getVertexSize() const
{
    return 3 + (hasVertexComponent(VertexComponentType::Normal) ? 3 : 0)
            + (hasVertexComponent(VertexComponentType::Tangent) ? 6 : 0)
            + (hasVertexComponent(VertexComponentType::Texture)
               ? 2 * m_nbTexChannels : 0)
            + (hasVertexComponent(VertexComponentType::Texture)
               ? 4 * m_nbColorChannels : 0);
}



const char *FD3D::AbstractMeshComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<AbstractMeshComponent>::code;
}

size_t FD3D::AbstractMeshComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<AbstractMeshComponent>::hash();
}

bool FD3D::AbstractMeshComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::AbstractMeshComponent::getTypeCodeHash() || Component::matchTypeCodeHash(hash);
}

FD3D::VertexComponentFlag FD3D::internal::getVertexComponents(const aiMesh *mesh)
{
    return VertexComponentFlag(VertexComponentType::Position)
            | (mesh->HasNormals()
               ? VertexComponentType::Normal
               : VertexComponentType::Position)
            | (mesh->GetNumColorChannels() != 0
                                              ? VertexComponentType::Color
                                              : VertexComponentType::Position)
            | (mesh->GetNumUVChannels() != 0
                                           ? VertexComponentType::Texture
                                           : VertexComponentType::Position)
            | (mesh->HasTangentsAndBitangents() != 0
                                                   ? VertexComponentType::Tangent
                                                   : VertexComponentType::Position);
}

float *FD3D::FunctionalMeshStrategy::getVertices(FD3D::AbstractMeshComponent &mesh)
{
    return m_getVertices(mesh);
}

const float *FD3D::FunctionalMeshStrategy::getVertices(const FD3D::AbstractMeshComponent &mesh) const
{
    return m_getConstVertices(mesh);
}

uint32_t *FD3D::FunctionalMeshStrategy::getIndices(FD3D::AbstractMeshComponent &mesh)
{
    return m_getIndices(mesh);
}

const uint32_t *FD3D::FunctionalMeshStrategy::getIndices(const FD3D::AbstractMeshComponent &mesh) const
{
    return m_getConstIndices(mesh);
}

size_t FD3D::FunctionalMeshStrategy::getNumberOfVertices(const FD3D::AbstractMeshComponent &mesh) const
{
    return m_getNumberOfVertices(mesh);
}

void FD3D::FunctionalMeshStrategy::setNumberOfVertices(FD3D::AbstractMeshComponent &mesh, size_t val)
{
    m_setNumberOfVertices(mesh, val);
}

size_t FD3D::FunctionalMeshStrategy::getNumberOfIndices(const FD3D::AbstractMeshComponent &mesh) const
{
    return m_getNumberOfIndices(mesh);
}

void FD3D::FunctionalMeshStrategy::setNumberOfIndices(FD3D::AbstractMeshComponent &mesh, size_t val)
{
    m_setNumberOfIndices(mesh, val);
}

FD3D::VertexProxy2 FD3D::AbstractMeshComponent::getVertex(size_t index)
{
    return { this, index };
}

FD3D::ConstVertexProxy2 FD3D::AbstractMeshComponent::getVertex(size_t index) const
{
    return { this, index };
}

FD3D::VertexProxy2 FD3D::AbstractMeshComponent::getVertexFromIndex(size_t index)
{
    return { this, *(getIndices() + index) };
}

FD3D::ConstVertexProxy2 FD3D::AbstractMeshComponent::getVertexFromIndex(size_t index) const
{
    return { this, *(getIndices() + index) };
}

FD3D::IndexProxy2 FD3D::AbstractMeshComponent::getIndex(size_t pos)
{
    return { this, pos };
}

FD3D::ConstIndexProxy2 FD3D::AbstractMeshComponent::getIndex(size_t pos) const
{
    return { this, pos };
}

float *FD3D::StrategyManagedMesh::getVertices()
{
    return m_strategy.getVertices(*this);
}

const float *FD3D::StrategyManagedMesh::getVertices() const
{
    return m_strategy.getVertices(*this);
}

uint32_t *FD3D::StrategyManagedMesh::getIndices()
{
    return m_strategy.getIndices(*this);
}

const uint32_t *FD3D::StrategyManagedMesh::getIndices() const
{
    return m_strategy.getIndices(*this);
}

size_t FD3D::StrategyManagedMesh::getNumberOfVertices() const
{
    return m_strategy.getNumberOfVertices(*this);
}

void FD3D::StrategyManagedMesh::setNumberOfVertices(size_t val)
{
    m_strategy.setNumberOfVertices(*this, val);
}

size_t FD3D::StrategyManagedMesh::getNumberOfIndices() const
{
    return m_strategy.getNumberOfIndices(*this);
}

void FD3D::StrategyManagedMesh::setNumberOfIndices(size_t val)
{
    m_strategy.setNumberOfIndices(*this, val);
}
