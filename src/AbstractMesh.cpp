#include <FD3D/Mesh/AbstractMesh.h>

#include <FD3D/Utils/VertexProxy.h>

#include <assimp/mesh.h>

FD3D::AbstractMesh::AbstractMesh() :
    m_materialId(0),
    m_nbColorChannels(0),
    m_nbTexChannels(0),
    m_options(MeshOption::Interlaced)
{}

int FD3D::AbstractMesh::getComponentOffset(FD3D::VertexComponentType comp) const
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

size_t FD3D::AbstractMesh::getVertexSize() const
{
    return 3 + (hasVertexComponent(VertexComponentType::Normal) ? 3 : 0)
            + (hasVertexComponent(VertexComponentType::Tangent) ? 6 : 0)
            + (hasVertexComponent(VertexComponentType::Texture)
               ? 2 * m_nbTexChannels : 0)
            + (hasVertexComponent(VertexComponentType::Texture)
               ? 4 * m_nbColorChannels : 0);
}



const char *FD3D::AbstractMesh::getTypeCode() const
{
    return FDCore::TypeCodeHelper<AbstractMesh>::code;
}

size_t FD3D::AbstractMesh::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<AbstractMesh>::hash();
}

bool FD3D::AbstractMesh::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::AbstractMesh::getTypeCodeHash() || Component::matchTypeCodeHash(hash);
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

size_t FD3D::internal::getVertexSize(const aiMesh *mesh)
{
    unsigned int nb_color = mesh->GetNumColorChannels();
    unsigned int nb_tex = mesh->GetNumUVChannels();
    return 3
            + (mesh->HasNormals() ? 3 : 0)
            + (nb_color != 0 ? 4 * nb_color : 0)
            + (nb_tex != 0 ? 2 * nb_tex : 0)
            + (mesh->HasTangentsAndBitangents() ? 6 :0);
}

size_t FD3D::internal::getMeshSize(const aiMesh *mesh, size_t vertexSize)
{
    return vertexSize * mesh->mNumVertices;
}

glm::vec3 FD3D::internal::getVertexPosition(const aiMesh *mesh, size_t vertexIndex)
{
    auto &v = mesh->mVertices[vertexIndex];
    return glm::vec3(v.x, v.y, v.z);
}

glm::vec3 FD3D::internal::getVertexNormal(const aiMesh *mesh, size_t vertexIndex)
{
    auto &n = mesh->mNormals[vertexIndex];
    return glm::vec3(n.x, n.y, n.z);
}

glm::vec3 FD3D::internal::getVertexTangent(const aiMesh *mesh, size_t vertexIndex)
{
    auto &t = mesh->mTangents[vertexIndex];
    return glm::vec3(t.x, t.y, t.z);
}

glm::vec3 FD3D::internal::getVertexBitangent(const aiMesh *mesh, size_t vertexIndex)
{
    auto &t = mesh->mBitangents[vertexIndex];
    return glm::vec3(t.x, t.y, t.z);
}

glm::vec2 FD3D::internal::getVertexUv(const aiMesh *mesh, size_t vertexIndex, size_t textureIndex)
{
    auto &t = mesh->mTextureCoords[textureIndex][vertexIndex];
    return glm::vec2(t.x, t.y);
}

glm::vec4 FD3D::internal::getVertexColor(const aiMesh *mesh, size_t vertexIndex, size_t colorIndex)
{
    auto &t = mesh->mColors [colorIndex][vertexIndex];
    return glm::vec4(t.r, t.g, t.b, t.a);
}

std::vector<uint32_t> FD3D::internal::getIndices(const aiMesh *mesh)
{
    std::vector<uint32_t> indices;
    indices.reserve(mesh->mNumFaces * 3);

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return indices;
}

float *FD3D::FunctionalMeshStrategy::getVertices(FD3D::AbstractMesh &mesh)
{
    return m_getVertices(mesh);
}

const float *FD3D::FunctionalMeshStrategy::getVertices(const FD3D::AbstractMesh &mesh) const
{
    return m_getConstVertices(mesh);
}

uint32_t *FD3D::FunctionalMeshStrategy::getIndices(FD3D::AbstractMesh &mesh)
{
    return m_getIndices(mesh);
}

const uint32_t *FD3D::FunctionalMeshStrategy::getIndices(const FD3D::AbstractMesh &mesh) const
{
    return m_getConstIndices(mesh);
}

size_t FD3D::FunctionalMeshStrategy::getNumberOfVertices(const FD3D::AbstractMesh &mesh) const
{
    return m_getNumberOfVertices(mesh);
}

void FD3D::FunctionalMeshStrategy::setNumberOfVertices(FD3D::AbstractMesh &mesh, size_t val)
{
    m_setNumberOfVertices(mesh, val);
}

size_t FD3D::FunctionalMeshStrategy::getNumberOfIndices(const FD3D::AbstractMesh &mesh) const
{
    return m_getNumberOfIndices(mesh);
}

void FD3D::FunctionalMeshStrategy::setNumberOfIndices(FD3D::AbstractMesh &mesh, size_t val)
{
    m_setNumberOfIndices(mesh, val);
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
