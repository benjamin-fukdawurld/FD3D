#ifndef VERTEXPROXY_H
#define VERTEXPROXY_H

#include <FDCore/EnumFlag.h>
#include <FDCore/CRTPTrait.h>

#include <cstdint>
#include <cstddef>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace FD3D
{
    class AbstractMesh;

    enum class VertexComponentType : uint8_t
    {
        Position = 0,
        Normal = 1,
        Color = 2,
        Texture = 4,
        Tangent = 8
    };

    typedef FDCore::EnumFlag<VertexComponentType, uint8_t> VertexComponentFlag;

    namespace internal
    {
        template<typename DerivedType>
        class ConstVertexProxyTrait : public FDCore::CRTPTrait<DerivedType>
        {
            friend class AbstractMesh;
            private:
                size_t m_index;

            public:
                ConstVertexProxyTrait(size_t index) :
                    m_index(index)
                {}

                virtual ~ConstVertexProxyTrait();

                const AbstractMesh *getMesh() const
                {
                    return this->asDerived().m_mesh;
                }

                size_t getIndex();

                void setIndex(size_t index)
                {
                    if(index < getMesh().getNumberOfVertices)
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
                    return getComponentPtr<const glm::vec3>(VertexComponentType::Position);
                }

                const glm::vec3 *getBitangent() const
                {
                    auto result = getComponentPtr<const glm::vec3>(VertexComponentType::Position);
                    return (result ? result + 1 : result);
                }

                const glm::vec2 *getUv(size_t index) const
                {
                    auto result = getComponentPtr<const glm::vec2>(VertexComponentType::Position);
                    return (result ? result + index : result);
                }

                const glm::vec4 *getColor(size_t index) const
                {
                    auto result = getComponentPtr<const glm::vec4>(VertexComponentType::Position);
                    return (result ? result + index : result);
                }

            private:
                int getComponentPosition(VertexComponentType comp) const;

                template<typename T>
                T *getComponentPtr(VertexComponentType comp) const
                {
                    int offset = getComponentPosition(comp);
                    if(offset == -1)
                        return nullptr;

                    return reinterpret_cast<T*>(getMesh()->vertices() + offset);
                }
        };
    }

    class ConstVertexProxy : internal::ConstVertexProxyTrait<ConstVertexProxy>
    {
        friend class internal::ConstVertexProxyTrait<ConstVertexProxy>;
        protected:
            const AbstractMesh *m_mesh;

        public:
            ConstVertexProxy(const AbstractMesh *mesh, size_t index);
            virtual ~ConstVertexProxy();
    };

    class VertexProxy : public internal::ConstVertexProxyTrait<VertexProxy>
    {
        friend class internal::ConstVertexProxyTrait<VertexProxy>;
        protected:
            AbstractMesh *m_mesh;

        public:
            VertexProxy(AbstractMesh *mesh, size_t index);
            virtual ~VertexProxy();

            glm::vec3 *getPosition();

            glm::vec3 *getNormal();

            glm::vec3 *getTangent();

            glm::vec3 *getBitangent();

            glm::vec2 *getUv(size_t index);

            glm::vec4 *getColor(size_t index);
    };
}

#endif // VERTEXPROXY_H
