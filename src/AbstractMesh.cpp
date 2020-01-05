#include <FD3D/Mesh/AbstractMesh.h>

#include <FD3D/Utils/VertexProxy.h>

FD3D::AbstractMesh::AbstractMesh() :
    m_materialId(0),
    m_nbColorChannels(0),
    m_nbTexChannels(0),
    m_options(MeshOption::Interlaced)
{}

FD3D::AbstractMesh::~AbstractMesh() {}

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
    }
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

FD3D::VertexComponentFlag FD3D::internal::getVertexComponents(const aiMesh *mesh)
{
    return VertexComponentFlag(VertexComponentType::Position)
            | (mesh->HasNormals()
               ? VertexComponentType::Normal
               : VertexComponentType::Position)
            | (mesh->GetNumColorChannels() != 0
                                              ? VertexComponentType::Normal
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

bool FD3D::load(const aiMesh *in, FD3D::Scene & /*scene*/, AbstractMesh &out)
{
    VertexComponentFlag f = internal::getVertexComponents(in);
    size_t vertexSize = internal::getVertexSize(in);

    out.setComponentsFlags(f);
    out.setNumberOfVertices(vertexSize);
    out.setNumberOfIndices(in->mNumFaces * 3);
    out.setNumberOfUvChannel(static_cast<uint8_t>(in->GetNumUVChannels()));
    out.setNumberOfUvChannel(static_cast<uint8_t>(in->GetNumColorChannels()));
    out.setName(in->mName.C_Str());

    for(size_t i = 0; i < in->mNumVertices; ++i)
    {
        VertexProxy v = out[i];
        {
            glm::vec3 *pos = v.getPosition();
            *pos = internal::getVertexPosition(in, i);
        }

        if(f[VertexComponentType::Normal])
        {
            glm::vec3 *norm = v.getNormal();
            *norm = internal::getVertexNormal(in, i);
        }

        if(f[VertexComponentType::Tangent])
        {
            glm::vec3 *t = v.getTangent();
            *t = internal::getVertexTangent(in, i);
            t = v.getBitangent();
            *t = internal::getVertexBitangent(in, i);
        }

        if(f[VertexComponentType::Texture])
        {
            for(uint8_t j = 0; j < out.getNumberOfUvChannel(); ++j)
            {
                glm::vec2 *tex = v.getUv(j);
                *tex = internal::getVertexUv(in, i, j);
            }
        }

        if(f[VertexComponentType::Color])
        {
            for(uint8_t j = 0; j < out.getNumberOfColorChannel(); ++j)
            {
                glm::vec4 *col = v.getColor(j);
                *col = internal::getVertexColor(in, i, j);
            }
        }
    }

    return true;
}
