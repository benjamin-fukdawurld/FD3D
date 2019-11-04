#ifndef MODELLOADER_FWD_H
#define MODELLOADER_FWD_H

#include <assimp/mesh.h>

#include <FD3D/Vertex.h>
#include <FD3D/Mesh.h>

#include <functional>


namespace FD3D
{
    template<typename VertexType>
    VertexType generateVertex(const aiMesh *mesh, size_t vertexIndex);

    template<>
    Vertex generateVertex<Vertex>(const aiMesh *mesh, size_t vertexIndex);

    template<typename MeshType>
    MeshType generateMesh(const aiMesh *mesh)
    {
        return generateMesh<MeshType>(mesh, &generateVertex<typename MeshType::VertexType>);
    }

    template<typename MeshType, typename VertexGenerator>
    MeshType generateMesh(const aiMesh *mesh, VertexGenerator vertexGenerator);

    template<>
    Mesh<Vertex> generateMesh<
        Mesh<Vertex>,
        std::function<Vertex(const aiMesh*, size_t)>
    >(const aiMesh *mesh, std::function<Vertex(const aiMesh*, size_t)> vertexGenerator);
}

#endif // MODELLOADER_FWD_H
