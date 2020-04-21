#ifndef VERTEXPROXY_H
#define VERTEXPROXY_H

#include <FDCore/EnumFlag.h>
#include <FDCore/CRTPTrait.h>

#include <cstdint>
#include <cstddef>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <string_view>

namespace FD3D
{
    class AbstractMesh;

    class VertexProxy;

    enum class VertexComponentType : uint8_t
    {
        Invalid = 128,
        Position = 0,
        Normal = 1,
        Color = 2,
        Texture = 4,
        Tangent = 8
    };

    std::string_view vertexComponentTypeToString(VertexComponentType type);
    VertexComponentType vertexComponentTypeFromString(std::string_view str);

    typedef FDCore::EnumFlag<VertexComponentType, uint8_t> VertexComponentFlag;

    namespace internal
    {
        template<typename DerivedType>
        class ConstVertexProxyTrait : public FDCore::CRTPTrait<DerivedType>
        {
            friend class AbstractMesh;
            private:
                size_t m_index;

            protected:
                ConstVertexProxyTrait(size_t index) :
                    m_index(index)
                {}

            public:
                virtual ~ConstVertexProxyTrait();

                const AbstractMesh *getMesh() const
                {
                    return this->asDerived().m_mesh;
                }

                size_t getIndex() const
                {
                    return m_index;
                }

                void setIndex(size_t index)
                {
                    assert(index < getMesh()->getNumberOfVertices);
                    m_index = index;
                }

                DerivedType &operator+=(size_t i)
                {
                    setIndex(m_index + i);
                    return this->asDerived();
                }

                DerivedType operator+(size_t i)
                {
                    return DerivedType(getMesh(), m_index + i);
                }

                DerivedType &operator-=(size_t i)
                {
                    setIndex(m_index - i);
                    return this->asDerived();
                }

                DerivedType operator-(size_t i)
                {
                    return DerivedType(getMesh(), m_index + i);
                }

                DerivedType &operator++()
                {
                    setIndex(++m_index);
                    return this->asDerived();
                }

                DerivedType operator++(int)
                {
                    DerivedType result(getMesh(), m_index);
                    setIndex(++m_index);
                    return result;
                }

                DerivedType &operator--()
                {
                    setIndex(--m_index);
                    return this->asDerived();
                }

                DerivedType operator--(int)
                {
                    DerivedType result(getMesh(), m_index);
                    setIndex(--m_index);
                    return result;
                }

                const glm::vec3 *getPosition() const
                {
                    return getComponentPtr<const glm::vec3>(VertexComponentType::Position);
                }

                const glm::vec3 *getNormal() const
                {
                    return getComponentPtr<const glm::vec3>(VertexComponentType::Normal);
                }

                const glm::vec3 *getTangent() const
                {
                    return getComponentPtr<const glm::vec3>(VertexComponentType::Tangent);
                }

                const glm::vec3 *getBitangent() const
                {
                    auto result = getComponentPtr<const glm::vec3>(VertexComponentType::Tangent);
                    return (result ? result + 1 : result);
                }

                const glm::vec2 *getUv(size_t index) const
                {
                    auto result = getComponentPtr<const glm::vec2>(VertexComponentType::Texture);
                    return (result ? result + index : result);
                }

                const glm::vec4 *getColor(size_t index) const
                {
                    auto result = getComponentPtr<const glm::vec4>(VertexComponentType::Color);
                    return (result ? result + index : result);
                }

            private:
                int getComponentPosition(VertexComponentType comp) const;

                template<typename T>
                T *getComponentPtr(VertexComponentType comp) const
                {
                    assert(m_index < getMesh()->getNumberOfVertices());
                    int offset = getComponentPosition(comp);
                    if(offset == -1)
                        return nullptr;

                    const float *ptr = getMesh()->getVertices();
                    if(ptr == nullptr)
                        return nullptr;

                    return reinterpret_cast<T*>(ptr + offset);
                }
        };

        template<typename DerivedType>
        ConstVertexProxyTrait<DerivedType>::~ConstVertexProxyTrait() {}
    }

    class ConstVertexProxy : public internal::ConstVertexProxyTrait<ConstVertexProxy>
    {
        friend class AbstractMesh;
        friend class internal::ConstVertexProxyTrait<ConstVertexProxy>;
        protected:
            const AbstractMesh *m_mesh;

        protected:
            ConstVertexProxy(const AbstractMesh *mesh, size_t index);

        public:
            ConstVertexProxy(const VertexProxy &v);
            virtual ~ConstVertexProxy();
    };

    class VertexProxy : public internal::ConstVertexProxyTrait<VertexProxy>
    {
        friend class AbstractMesh;
        friend class internal::ConstVertexProxyTrait<VertexProxy>;
        protected:
            AbstractMesh *m_mesh;

        protected:
            VertexProxy(AbstractMesh *mesh, size_t index);

        public:
            virtual ~VertexProxy();

            const glm::vec3 *getPosition() const;

            const glm::vec3 *getNormal() const;

            const glm::vec3 *getTangent() const;

            const glm::vec3 *getBitangent() const;

            const glm::vec2 *getUv(size_t index) const;

            const glm::vec4 *getColor(size_t index) const;

            glm::vec3 *getPosition();

            glm::vec3 *getNormal();

            glm::vec3 *getTangent();

            glm::vec3 *getBitangent();

            glm::vec2 *getUv(size_t index);

            glm::vec4 *getColor(size_t index);
    };
}

#endif // VERTEXPROXY_H
