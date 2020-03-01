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
            VertexComponentFlag m_componentsFlags;
            MeshOptionFlag m_options;

        public:
            AbstractMesh();
            virtual ~AbstractMesh() = default;

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

            VertexProxy getVertex(size_t pos);
            ConstVertexProxy getVertex(size_t pos) const;

            VertexProxy getVertexFromIndex(size_t index);
            ConstVertexProxy getVertexFromIndex(size_t index) const;

            VertexProxy operator[](size_t pos) { return getVertex(pos); }
            ConstVertexProxy operator[](size_t pos) const { return getVertex(pos); }

            VertexProxy operator()(size_t index) { return getVertexFromIndex(index); }
            ConstVertexProxy operator()(size_t index) const { return getVertexFromIndex(index); }

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

    class AbstractMeshStrategy : public Component
    {
        public:
            AbstractMeshStrategy();
            virtual ~AbstractMeshStrategy() = default;

            virtual float *getVertices(AbstractMesh &mesh) = 0;
            virtual const float *getVertices(const AbstractMesh &mesh) const = 0;
            virtual uint32_t *getIndices(AbstractMesh &mesh) = 0;
            virtual const uint32_t *getIndices(const AbstractMesh &mesh) const = 0;

            virtual size_t getNumberOfVertices(const AbstractMesh &mesh) const = 0;
            virtual void setNumberOfVertices(AbstractMesh &mesh, size_t val) = 0;

            virtual size_t getNumberOfIndices(const AbstractMesh &mesh) const = 0;
            virtual void setNumberOfIndices(AbstractMesh &mesh, size_t val) = 0;
    };

    class FunctionalMeshStrategy : public AbstractMeshStrategy
    {
        protected:
            std::function<float *(AbstractMesh &)> m_getVertices;
            std::function<const float *(const AbstractMesh &)> m_getConstVertices;

            std::function<uint32_t *(AbstractMesh &)> m_getIndices;
            std::function<const uint32_t *(const AbstractMesh &)> m_getConstIndices;

            std::function<size_t (const AbstractMesh &)> m_getNumberOfVertices;
            std::function<void(AbstractMesh &, size_t)> m_setNumberOfVertices;

            std::function<size_t (const AbstractMesh &)> m_getNumberOfIndices;
            std::function<void(AbstractMesh &, size_t)> m_setNumberOfIndices;

        public:
            template<typename VerticesGetter, typename ConstVerticesGetter,
                     typename IndicesGetter, typename ConstIndicesGetter,
                     typename VerticesNumberGetter, typename VerticesNumberSetter,
                     typename IndicesNumberGetter, typename IndicesNumberSetter>
            FunctionalMeshStrategy(VerticesGetter getVertices,
                                   ConstVerticesGetter getConstVertices,
                                   IndicesGetter getIndices,
                                   ConstIndicesGetter getConstIndices,
                                   VerticesNumberGetter getNumberOfVertices,
                                   VerticesNumberSetter setNumberOfVertices,
                                   IndicesNumberGetter getNumberOfIndices,
                                   IndicesNumberSetter setNumberOfIndices) :
                m_getVertices(getVertices),
                m_getConstVertices(getConstVertices),
                m_getIndices(getIndices),
                m_getConstIndices(getConstIndices),
                m_getNumberOfVertices(getNumberOfVertices),
                m_setNumberOfVertices(setNumberOfVertices),
                m_getNumberOfIndices(getNumberOfIndices),
                m_setNumberOfIndices(setNumberOfIndices)
            {}

            ~FunctionalMeshStrategy () override = default;

            float *getVertices(AbstractMesh &mesh) override;
            const float *getVertices(const AbstractMesh &mesh) const override;
            uint32_t *getIndices(AbstractMesh &mesh) override;
            const uint32_t *getIndices(const AbstractMesh &mesh) const override;

            size_t getNumberOfVertices(const AbstractMesh &mesh) const override;
            void setNumberOfVertices(AbstractMesh &mesh, size_t val) override;

            size_t getNumberOfIndices(const AbstractMesh &mesh) const override;
            void setNumberOfIndices(AbstractMesh &mesh, size_t val) override;
    };

    class StrategyManagedMesh : public AbstractMesh
    {
        protected:
            AbstractMeshStrategy &m_strategy;

        public:
            StrategyManagedMesh(AbstractMeshStrategy &strategy) :
                m_strategy(strategy)
            {}
            ~StrategyManagedMesh() override = default;

            float *getVertices() override;
            const float *getVertices() const override;
            uint32_t *getIndices() override;
            const uint32_t *getIndices() const override;

            size_t getNumberOfVertices() const override;
            void setNumberOfVertices(size_t val) override;

            size_t getNumberOfIndices() const override;
            void setNumberOfIndices(size_t val) override;
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
