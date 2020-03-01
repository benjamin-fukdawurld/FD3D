#ifndef INDEXPROXY_H
#define INDEXPROXY_H

#include <FDCore/CRTPTrait.h>

#include <cstddef>
#include <cstdint>

namespace FD3D
{
    class AbstractMesh;

    namespace internal
    {
        template<typename DerivedType>
        class ConstIndexProxyTrait : public FDCore::CRTPTrait<DerivedType>
        {
            friend class AbstractMesh;
            protected:
                size_t m_position;

            protected:
                ConstIndexProxyTrait(size_t pos) :
                    m_position(pos)
                {}

            public:
                virtual ~ConstIndexProxyTrait();

                const AbstractMesh *getMesh() const
                {
                    return this->asDerived().m_mesh;
                }

                size_t getPosition() { return m_position; }

                void setPosition(size_t position)
                {
                    assert(position < getMesh()->getNumberOfIndices());
                    m_position = position;
                }

                uint32_t getValue() const
                {
                    assert(m_position < getMesh()->getNumberOfIndices());
                    return *(getMesh()->getIndices() + m_position);
                }

                uint32_t operator*() const
                {
                    return getValue();
                }

                DerivedType &operator+=(size_t i)
                {
                    setPosition(m_position + i);
                    return this->asDerived();
                }

                DerivedType operator+(size_t i)
                {
                    return DerivedType(getMesh(), m_position + i);
                }

                DerivedType &operator-=(size_t i)
                {
                    setIndex(m_position - i);
                    return this->asDerived();
                }

                DerivedType operator-(size_t i)
                {
                    return DerivedType(getMesh(), m_position + i);
                }

                DerivedType &operator++()
                {
                    setIndex(++m_position);
                    return this->asDerived();
                }

                DerivedType operator++(int)
                {
                    DerivedType result(getMesh(), m_position);
                    setIndex(++m_position);
                    return result;
                }

                DerivedType &operator--()
                {
                    setIndex(--m_position);
                    return this->asDerived();
                }

                DerivedType operator--(int)
                {
                    DerivedType result(getMesh(), m_position);
                    setIndex(--m_position);
                    return result;
                }
        };

        template<typename Derived>
        ConstIndexProxyTrait<Derived>::~ConstIndexProxyTrait() {}
    }

    class ConstIndexProxy : internal::ConstIndexProxyTrait<ConstIndexProxy>
    {
        friend class AbstractMesh;
        friend class internal::ConstIndexProxyTrait<ConstIndexProxy>;
        protected:
            const AbstractMesh *m_mesh;

        protected:
            ConstIndexProxy(const AbstractMesh *mesh, size_t position);

        public:
            virtual ~ConstIndexProxy();
    };

    class IndexProxy : internal::ConstIndexProxyTrait<IndexProxy>
    {
        friend class AbstractMesh;
        friend class internal::ConstIndexProxyTrait<IndexProxy>;
        protected:
            AbstractMesh *m_mesh;

        protected:
            IndexProxy(AbstractMesh *mesh, size_t position);

        public:
            virtual ~IndexProxy();

            uint32_t getValue() const;

            uint32_t operator*() const
            {
                return getValue();
            }

            uint32_t &operator*();

            void setValue(uint32_t val);
    };
}
#endif // INDEXPROXY_H
