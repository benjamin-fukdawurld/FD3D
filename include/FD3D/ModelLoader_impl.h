#ifndef MODELLOADER_IMPL_H
#define MODELLOADER_IMPL_H

#include <FD3D/ModelLoader_fwd.h>
#include <FD3D/ModelLoader.h>

namespace FD3D
{
    template<>
    inline Vertex generateVertex<Vertex>(const aiMesh *mesh, size_t vertexIndex)
    {
        Vertex v;
        v.setPosition(internal::getVertexPosition(mesh, vertexIndex));
        v.setNormal(internal::getVertexNormal(mesh, vertexIndex));
        v.setTexture(internal::getVertexTextureCoordinates(mesh, vertexIndex, 0));
        return v;
    }

    template<>
    inline Mesh<Vertex> generateMesh<Mesh<Vertex>>(const aiMesh *mesh)
    {
        std::vector<Vertex> v;
        std::vector<Texture> t;
        v.reserve(mesh->mNumVertices);
        for(size_t i = 0; i < mesh->mNumVertices; ++i)
        {
            v.push_back(generateVertex<Vertex>(mesh, i));
        }

        return Mesh{v, internal::getMeshIndices(mesh), t};
    }

    template<>
    inline Mesh<Vertex> generateMesh<
        Mesh<Vertex>,
        std::function<Vertex(const aiMesh*, size_t)>
    >(const aiMesh *mesh, std::function<Vertex(const aiMesh*, size_t)> vertexGenerator)
    {
        std::vector<Vertex> v;
        std::vector<Texture> t;
        v.reserve(mesh->mNumVertices);
        for(size_t i = 0; i < mesh->mNumVertices; ++i)
        {
            v.push_back(vertexGenerator(mesh, i));
        }

        return Mesh{v, internal::getMeshIndices(mesh), t};
    }
}

#endif // MODELLOADER_IMPL_H
