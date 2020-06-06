#ifndef ABSTRACTMESH_H
#define ABSTRACTMESH_H

#include <FDCore/EnumFlag.h>
#include <FDCore/BaseResource.h>

#include <FD3D/Material/Material.h>

#include <FD3D/Utils/VertexProxy.h>
#include <FD3D/Utils/IndexProxy.h>

#include <assimp/scene.h>
#include <assimp/mesh.h>

namespace FD3D
{
    enum class MeshOption : uint8_t
    {
        Invalid = 255,
        None = 0,
        Interlaced = 1
    };

    typedef FDCore::EnumFlag<MeshOption, uint8_t> MeshOptionFlag;

    class FD_EXPORT AbstractMesh : public FDCore::BaseResource
    {
        protected:
            Material *m_material;
            FDCore::AbstractResource *m_shader;
            uint8_t m_nbColorChannels;
            uint8_t m_nbTexChannels;
            VertexComponentFlag m_componentsFlags;
            MeshOptionFlag m_options;

        public:
            AbstractMesh();
            ~AbstractMesh() override = default;

            bool hasMaterial() const { return m_material != nullptr; }
            Material *getMaterial() const { return m_material; }
            void setMaterial(Material *mat) { m_material = mat; }

            bool hasShader() const { return m_shader != nullptr; }
            FDCore::AbstractResource *getShader() const { return m_shader; }
            void setShader(FDCore::AbstractResource *shad) { m_shader = shad; }

            virtual float *getVertices() = 0;
            virtual const float *getVertices() const = 0;
            virtual void setVertices(const float *data) = 0;

            virtual uint32_t *getIndices() = 0;
            virtual const uint32_t *getIndices() const = 0;
            virtual void setIndices(const uint32_t *data) = 0;

            virtual size_t getNumberOfVertices() const = 0;
            virtual void setNumberOfVertices(size_t val) = 0;

            virtual size_t getNumberOfIndices() const = 0;
            virtual void setNumberOfIndices(size_t val) = 0;

            virtual VertexProxy getVertex(size_t pos);
            virtual ConstVertexProxy getVertex(size_t pos) const;

            virtual VertexProxy getVertexFromIndex(size_t index);
            virtual ConstVertexProxy getVertexFromIndex(size_t index) const;

            virtual IndexProxy getIndex(size_t pos);
            virtual ConstIndexProxy getIndex(size_t pos) const;

            VertexProxy operator[](size_t pos) { return getVertex(pos); }
            ConstVertexProxy operator[](size_t pos) const { return getVertex(pos); }

            VertexProxy operator()(size_t index) { return getVertexFromIndex(index); }
            ConstVertexProxy operator()(size_t index) const { return getVertexFromIndex(index); }

            VertexComponentFlag getComponentFlags() const { return m_componentsFlags; }
            void setComponentsFlags(VertexComponentFlag flags) { m_componentsFlags = flags; }

            bool hasVertexComponent(VertexComponentType val) const
            {
                return m_componentsFlags[val];
            }

            void addVertexComponent(VertexComponentType val)
            {
                m_componentsFlags[val] = true;
            }

            void removeVertexComponent(VertexComponentType val)
            {
                m_componentsFlags[val] = false;
            }

            bool isInterlaced() const { return m_options[MeshOption::Interlaced]; }
            void setInterlaced(bool toggle) { m_options[MeshOption::Interlaced] = toggle; }

            uint8_t getNumberOfColorChannel() const { return m_nbColorChannels; }
            void setNumberOfColorChannel(uint8_t value) { m_nbColorChannels = value; }

            uint8_t getNumberOfUvChannel() const { return m_nbTexChannels; }
            void setNumberOfUvChannel(uint8_t value) { m_nbTexChannels = value; }

            int getComponentOffset(VertexComponentType comp) const;

            size_t getVertexSize() const;

            size_t getStride() const
            {
                return (isInterlaced() ? getVertexSize() : 0);
            }

            size_t getVerticesDataSize() const
            {
                return sizeof(float) * getNumberOfVertices() * getVertexSize();
            }

            size_t getIndicesDataSize() const
            {
                return sizeof(uint32_t) * getNumberOfIndices();
            }

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;

            bool fromMesh(const aiMesh *mesh, const aiScene *scene, FDCore::ResourceManager &mgr);
    };

    namespace internal
    {
        template<typename DerivedType>
        int ConstVertexProxyTrait<DerivedType>::getComponentPosition(VertexComponentType comp) const
        {
            const FD3D::AbstractMesh *m = getMesh();
            if(!m->hasVertexComponent(comp))
                return -1;

            return m->getComponentOffset(comp)
                    + static_cast<int>(m->isInterlaced()
                                       ? m_index * m->getVertexSize()
                                       : m_index * 3);
        }

        VertexComponentFlag vertexComponentsFromMesh(const aiMesh *mesh);

        size_t getVertexSize(const aiMesh *mesh);

        size_t getMeshSize(const aiMesh *mesh, size_t vertexSize);

        glm::vec3 getVertexPosition(const aiMesh *mesh, size_t vertexIndex);

        glm::vec3 getVertexNormal(const aiMesh *mesh, size_t vertexIndex);

        glm::vec3 getVertexTangent(const aiMesh *mesh, size_t vertexIndex);

        glm::vec3 getVertexBitangent(const aiMesh *mesh, size_t vertexIndex);

        glm::vec2 getVertexUv(const aiMesh *mesh,
                              size_t vertexIndex,
                              size_t textureIndex);

        glm::vec4 getVertexColor(const aiMesh *mesh,
                                  size_t vertexIndex,
                                  size_t colorIndex);

        std::vector<uint32_t> getIndices(const aiMesh *mesh);
    }
}

generateTypeCode(FD3D::AbstractMesh);

#endif // ABSTRACTMESH_H
