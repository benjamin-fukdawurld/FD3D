#ifndef FD3D_MESH_H
#define FD3D_MESH_H

#include <vector>

#include <FD3D/Mesh/AbstractMesh.h>
#include <assimp/mesh.h>

namespace FD3D
{
    class Mesh : public AbstractMesh
    {
        protected:
            std::vector<float> m_vertices;
            std::vector<uint32_t> m_indices;

        public:
            Mesh();

            Mesh(std::vector<float> &&vertices,
                 std::vector<uint32_t> &&indices);

            Mesh(const std::vector<float> &vertices,
                 const std::vector<uint32_t> &indices);

            ~Mesh() override;

            float *getVertices() override { return m_vertices.data(); }
            const float *getVertices() const override { return m_vertices.data(); }
            uint32_t *getIndices() override { return m_indices.data(); }
            const uint32_t *getIndices() const override { return m_indices.data(); }

            size_t getNumberOfVertices() const override { return m_vertices.size()/getVertexSize(); }
            void setNumberOfVertices(size_t val) override
            {
                m_vertices.resize(val * getVertexSize(), 0.0f);
            }

            size_t getNumberOfIndices() const override { return m_indices.size(); }
            void setNumberOfIndices(size_t val) override { m_indices.resize(val, 0); }

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;
    };
}

generateTypeCode(FD3D::Mesh);

#endif // FD3D_MESH_H
