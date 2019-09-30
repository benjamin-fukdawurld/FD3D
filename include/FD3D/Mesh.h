#ifndef MESH_H
#define MESH_H

#include <FD3D/Vertex.h>
#include <FD3D/Texture.h>
#include <vector>

namespace FD3D
{
    class Mesh
    {
        protected:
            std::vector<Vertex> m_vertices;
            std::vector<uint32_t> m_indices;
            std::vector<Texture> m_textures;

        public:
            Mesh();

            Mesh(const std::vector<Vertex> &vertices,
                 const std::vector<uint32_t> &indices,
                 const std::vector<Texture> textures) :
                m_vertices(vertices),
                m_indices(indices),
                m_textures(textures)
            {}

            std::vector<Vertex> &getVertices() { return m_vertices; }
            std::vector<uint32_t> &getIndices() { return m_indices; }
            std::vector<Texture> &getTextures() { return m_textures; }

            const std::vector<Vertex> &getVertices() const { return m_vertices; }
            const std::vector<uint32_t> &getIndices() const { return m_indices; }
            const std::vector<Texture> &getTextures() const { return m_textures; }

            void setVertices(const std::vector<Vertex> &vert)
            {
                m_vertices = vert;
            }

            void setIndices(const std::vector<uint32_t> &ind)
            {
                m_indices = ind;
            }

            void setTexture(const std::vector<Texture> &tex)
            {
                m_textures = tex;
            }
    };
}

#endif // MESH_H
