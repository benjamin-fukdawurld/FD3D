#ifndef FD3D_MESHCOMPONENT_H
#define FD3D_MESHCOMPONENT_H

#include <vector>

#include <FD3D/Mesh/AbstractMeshComponent.h>
#include <assimp/mesh.h>

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT MeshComponent : public AbstractMeshComponent
    {
        protected:
            std::vector<float> m_vertices;
            std::vector<uint32_t> m_indices;

        public:
            MeshComponent();

            MeshComponent(std::vector<float> &&vertices,
                 std::vector<uint32_t> &&indices);

            MeshComponent(const std::vector<float> &vertices,
                 const std::vector<uint32_t> &indices);

            ~MeshComponent() override;

            float *getVertices() override { return m_vertices.data(); }
            const float *getVertices() const override { return m_vertices.data(); }
            void setVertices(const float *data) override;

            uint32_t *getIndices() override { return m_indices.data(); }
            const uint32_t *getIndices() const override { return m_indices.data(); }
            void setIndices(const uint32_t *data) override;


            size_t getNumberOfVertices() const override { return m_vertices.size()/getVertexSize(); }
            void setNumberOfVertices(size_t val) override
            {
                m_vertices.resize(val * getVertexSize(), 0.0f);
            }

            size_t getNumberOfIndices() const override { return m_indices.size(); }
            void setNumberOfIndices(size_t val) override { m_indices.resize(val, 0); }

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::MeshComponent);

#endif // FD3D_MESHCOMPONENT_H
