#ifndef ABSTRACTMESH_H
#define ABSTRACTMESH_H

#include <FD3D/SceneGraph/Component.h>
#include <FD3D/SceneGraph/Scene.h>
#include <FD3D/Utils/VertexProxy.h>
#include <FD3D/Utils/IndexProxy.h>

#include <FDCore/EnumFlag.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include <assimp/mesh.h>

namespace FD3D
{
    enum class MeshOption : uint8_t
    {
        None = 0,
        Interlaced = 1
    };

    typedef FDCore::EnumFlag<MeshOption, uint8_t> MeshOptionFlag;

    class AbstractMesh : public Component
    {
        protected:
            id_type m_materialId;
            uint8_t m_nbColorChannels;
            uint8_t m_nbTexChannels;
            MeshOptionFlag m_options;
            VertexComponentFlag m_componentsFlags;

        public:
            AbstractMesh();
            virtual ~AbstractMesh();

            bool hasMaterial() const { return m_materialId != 0; }
            id_type getMaterialId() const { return m_materialId; }
            void setMaterialId(id_type id) { m_materialId = id; }

            virtual float *getVertices() = 0;
            virtual const float *getVertices() const = 0;
            virtual uint32_t *getIndices() = 0;
            virtual const uint32_t *getIndices() const = 0;

            virtual size_t getNumberOfVertices() const = 0;
            virtual void setNumberOfVertices(size_t val) = 0;

            virtual size_t getNumberOfIndices() const = 0;
            virtual void setNumberOfIndices(size_t val) = 0;

            VertexProxy operator[](size_t pos);
            ConstVertexProxy operator[](size_t pos) const;

            VertexProxy operator()(size_t index);
            ConstVertexProxy operator()(size_t index) const;

            IndexProxy getIndex(size_t pos);
            ConstIndexProxy getIndex(size_t pos) const;

            VertexComponentFlag getFlags() const { return m_componentsFlags; }
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
    };

    namespace internal
    {
        template<typename DerivedType>
        int ConstVertexProxyTrait<DerivedType>::getComponentPosition(VertexComponentType comp) const
        {
            const AbstractMesh *m = getMesh();
            if(!m->hasVertexComponent(comp))
                return -1;

            return m->getComponentOffset(comp)
                    + static_cast<int>(m->isInterlaced()
                                       ? m_index * m->getVertexSize()
                                       : m_index * 3);
        }

        VertexComponentFlag getVertexComponents(const aiMesh *mesh);

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

    bool load(const aiMesh *in, Scene &scene, AbstractMesh &out);
}

#endif // ABSTRACTMESH_H
