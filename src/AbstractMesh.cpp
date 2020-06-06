#include <FD3D/Mesh/AbstractMesh.h>

#include <iostream>

FD3D::VertexComponentFlag FD3D::internal::vertexComponentsFromMesh(const aiMesh *mesh)
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


FD3D::AbstractMesh::AbstractMesh() :
    m_material(nullptr),
    m_shader(nullptr),
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
    return FDCore::TypeCodeHelper<FD3D::AbstractMesh>::code;
}

size_t FD3D::AbstractMesh::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::AbstractMesh>::hash();
}

bool FD3D::AbstractMesh::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::AbstractMesh>::hash()
            || FDCore::BaseResource::matchTypeCodeHash(hash);
}

bool FD3D::AbstractMesh::fromMesh(const aiMesh *mesh, const aiScene *scene, FDCore::ResourceManager &mgr)
{
    VertexComponentFlag f = internal::vertexComponentsFromMesh(mesh);

    setComponentsFlags(f);
    setNumberOfUvChannel(static_cast<uint8_t>(mesh->GetNumUVChannels()));
    setNumberOfColorChannel(static_cast<uint8_t>(mesh->GetNumColorChannels()));
    setNumberOfVertices(mesh->mNumVertices);
    setNumberOfIndices(mesh->mNumFaces * 3);
    setResourceName(mesh->mName.C_Str());


    if(mesh->mMaterialIndex < scene->mNumMaterials)
    {
        const aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        aiString str;
        if(mat->Get(AI_MATKEY_NAME, str) != AI_SUCCESS)
        {
            std::cerr << "material has no name" << std::endl;
            return false;
        }
        
        FD3D::Material *m = static_cast<FD3D::Material*>(mgr.at(str.C_Str()));
        if(!m)
        {
            std::unique_ptr<FD3D::Material> mtl(new FD3D::Material());
            mtl->setResourceName(str.C_Str());
            if(!mtl->fromMaterial(mat, mgr))
            {
                std::cerr << "unable to load material" << std::endl;
                return false;
            }

            m = mtl.release();
            mgr.insert(m);
        }

        setMaterial(m);
    }
    
    for(size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        VertexProxy v = getVertex(i);
        {
            glm::vec3 *pos = v.getPosition();
            *pos = internal::getVertexPosition(mesh, i);
        }

        if(f[VertexComponentType::Normal])
        {
            glm::vec3 *norm = v.getNormal();
            *norm = internal::getVertexNormal(mesh, i);
        }

        if(f[VertexComponentType::Tangent])
        {
            glm::vec3 *t = v.getTangent();
            *t = internal::getVertexTangent(mesh, i);
            t = v.getBitangent();
            *t = internal::getVertexBitangent(mesh, i);
        }

        if(f[VertexComponentType::Texture])
        {
            for(uint8_t j = 0; j < getNumberOfUvChannel(); ++j)
            {
                glm::vec2 *tex = v.getUv(j);
                *tex = internal::getVertexUv(mesh, i, j);
            }
        }

        if(f[VertexComponentType::Color])
        {
            for(uint8_t j = 0; j < getNumberOfColorChannel(); ++j)
            {
                glm::vec4 *col = v.getColor(j);
                *col = internal::getVertexColor(mesh, i, j);
            }
        }
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        size_t pos = i * 3;
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            getIndex(pos + j).setValue(face.mIndices[j]);
    }

    return true;
}

FD3D::VertexProxy FD3D::AbstractMesh::getVertex(size_t index)
{
    return { this, index };
}

FD3D::ConstVertexProxy FD3D::AbstractMesh::getVertex(size_t index) const
{
    return { this, index };
}

FD3D::VertexProxy FD3D::AbstractMesh::getVertexFromIndex(size_t index)
{
    return { this, *(getIndices() + index) };
}

FD3D::ConstVertexProxy FD3D::AbstractMesh::getVertexFromIndex(size_t index) const
{
    return { this, *(getIndices() + index) };
}

FD3D::IndexProxy FD3D::AbstractMesh::getIndex(size_t pos)
{
    return { this, pos };
}

FD3D::ConstIndexProxy FD3D::AbstractMesh::getIndex(size_t pos) const
{
    return { this, pos };
}
