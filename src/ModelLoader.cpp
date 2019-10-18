#include <FD3D/ModelLoader.h>

#include <iostream>


const aiScene *FD3D::internal::importScene(Assimp::Importer &importer, const std::string &path, unsigned int flags)
{
    const aiScene *scene = importer.ReadFile(path, flags);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    return scene;
}

std::vector<uint32_t> FD3D::internal::getMeshIndices(const aiMesh *mesh)
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

glm::vec2 FD3D::internal::getVertexTextureCoordinates(const aiMesh *mesh, size_t vertexIndex, size_t textureIndex)
{
    auto &t = mesh->mTextureCoords[textureIndex][vertexIndex];
    return glm::vec2(t.x, t.y);
}

FD3D::Vertex FD3D::internal::defaultVertexGenerator(const aiMesh *mesh, size_t vertexIndex)
{
    Vertex v;
    v.setPosition(getVertexPosition(mesh, vertexIndex));
    v.setNormal(getVertexNormal(mesh, vertexIndex));
    v.setTexture(getVertexTextureCoordinates(mesh, vertexIndex, 0));
    return v;
}
