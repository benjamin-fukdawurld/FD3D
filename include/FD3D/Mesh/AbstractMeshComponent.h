#ifndef FD3D_ABSTRACTMESHCOMPONENT_H
#define FD3D_ABSTRACTMESHCOMPONENT_H

#include <FD3D/SceneGraph/Component.h>
#include <FD3D/SceneGraph/Scene.h>

#include <FD3D/Mesh/AbstractMesh.h>

#include <FD3D/Utils/VertexProxy.h>
#include <FD3D/Utils/IndexProxy.h>

#include <FDCore/EnumFlag.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include <FDCore/Macros.h>

class aiMesh;

namespace FD3D
{
    class FD_EXPORT AbstractMeshComponent : public Component
    {
        protected:
            id_type m_materialId;
            id_type m_shaderId;
            uint8_t m_nbColorChannels;
            uint8_t m_nbTexChannels;
            VertexComponentFlag m_componentsFlags;
            MeshOptionFlag m_options;

        public:
            AbstractMeshComponent();
            ~AbstractMeshComponent() override = default;

            bool hasMaterial() const { return m_materialId != 0; }
            id_type getMaterialId() const { return m_materialId; }
            void setMaterialId(id_type id) { m_materialId = id; }

            bool hasShader() const { return m_shaderId != 0; }
            id_type getShaderId() const { return m_shaderId; }
            void setShaderId(id_type id) { m_shaderId = id; }

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

            virtual VertexProxy2 getVertex(size_t pos);
            virtual ConstVertexProxy2 getVertex(size_t pos) const;

            virtual VertexProxy2 getVertexFromIndex(size_t index);
            virtual ConstVertexProxy2 getVertexFromIndex(size_t index) const;

            virtual IndexProxy2 getIndex(size_t pos);
            virtual ConstIndexProxy2 getIndex(size_t pos) const;

            VertexProxy2 operator[](size_t pos) { return getVertex(pos); }
            ConstVertexProxy2 operator[](size_t pos) const { return getVertex(pos); }

            VertexProxy2 operator()(size_t index) { return getVertexFromIndex(index); }
            ConstVertexProxy2 operator()(size_t index) const { return getVertexFromIndex(index); }

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
    };

    class FD_EXPORT AbstractMeshStrategy : public Component
    {
        public:
            AbstractMeshStrategy();
            virtual ~AbstractMeshStrategy() = default;

            virtual float *getVertices(AbstractMeshComponent &mesh) = 0;
            virtual const float *getVertices(const AbstractMeshComponent &mesh) const = 0;
            virtual uint32_t *getIndices(AbstractMeshComponent &mesh) = 0;
            virtual const uint32_t *getIndices(const AbstractMeshComponent &mesh) const = 0;

            virtual size_t getNumberOfVertices(const AbstractMeshComponent &mesh) const = 0;
            virtual void setNumberOfVertices(AbstractMeshComponent &mesh, size_t val) = 0;

            virtual size_t getNumberOfIndices(const AbstractMeshComponent &mesh) const = 0;
            virtual void setNumberOfIndices(AbstractMeshComponent &mesh, size_t val) = 0;
    };

    class FD_EXPORT FunctionalMeshStrategy : public AbstractMeshStrategy
    {
        protected:
            std::function<float *(AbstractMeshComponent &)> m_getVertices;
            std::function<const float *(const AbstractMeshComponent &)> m_getConstVertices;

            std::function<uint32_t *(AbstractMeshComponent &)> m_getIndices;
            std::function<const uint32_t *(const AbstractMeshComponent &)> m_getConstIndices;

            std::function<size_t (const AbstractMeshComponent &)> m_getNumberOfVertices;
            std::function<void(AbstractMeshComponent &, size_t)> m_setNumberOfVertices;

            std::function<size_t (const AbstractMeshComponent &)> m_getNumberOfIndices;
            std::function<void(AbstractMeshComponent &, size_t)> m_setNumberOfIndices;

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

            float *getVertices(AbstractMeshComponent &mesh) override;
            const float *getVertices(const AbstractMeshComponent &mesh) const override;
            uint32_t *getIndices(AbstractMeshComponent &mesh) override;
            const uint32_t *getIndices(const AbstractMeshComponent &mesh) const override;

            size_t getNumberOfVertices(const AbstractMeshComponent &mesh) const override;
            void setNumberOfVertices(AbstractMeshComponent &mesh, size_t val) override;

            size_t getNumberOfIndices(const AbstractMeshComponent &mesh) const override;
            void setNumberOfIndices(AbstractMeshComponent &mesh, size_t val) override;
    };

    class FD_EXPORT StrategyManagedMesh : public AbstractMeshComponent
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
        int ConstVertexProxyTrait2<DerivedType>::getComponentPosition(VertexComponentType comp) const
        {
            const FD3D::AbstractMeshComponent *m = getMesh();
            if(!m->hasVertexComponent(comp))
                return -1;

            return m->getComponentOffset(comp)
                    + static_cast<int>(m->isInterlaced()
                                       ? m_index * m->getVertexSize()
                                       : m_index * 3);
        }

        VertexComponentFlag getVertexComponents(const aiMesh *mesh);
    }

    bool load(const aiMesh *in, Scene &scene, AbstractMeshComponent &out);
}

generateTypeCode(FD3D::AssetComponent<FD3D::AbstractMesh>);
generateTypeCode(FD3D::AbstractMeshComponent);

#endif // FD3D_ABSTRACTMESHCOMPONENT_H
