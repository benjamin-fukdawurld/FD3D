#ifndef FD3D_INDEXPROXY_H
#define FD3D_INDEXPROXY_H

#include <FDCore/CRTPTrait.h>

#include <cstddef>
#include <cstdint>

#include <FDCore/Macros.h>

namespace FD3D
{
    class AbstractMeshComponent;
    class AbstractMesh;

    namespace internal
    {
        template<typename DerivedType>
        class ConstIndexProxyTrait2 : public FDCore::CRTPTrait<DerivedType>
        {
            friend class FD3D::AbstractMeshComponent;
            protected:
                size_t m_position;

            protected:
                ConstIndexProxyTrait2(size_t pos) :
                    m_position(pos)
                {}

            public:
                virtual ~ConstIndexProxyTrait2();

                const FD3D::AbstractMeshComponent *getMesh() const
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
                    const uint32_t *ind = getMesh()->getIndices();
                    if(ind == nullptr)
                        return 0;

                    return *(ind + m_position);
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
                    setPosition(m_position - i);
                    return this->asDerived();
                }

                DerivedType operator-(size_t i)
                {
                    return DerivedType(getMesh(), m_position + i);
                }

                DerivedType &operator++()
                {
                    setPosition(++m_position);
                    return this->asDerived();
                }

                DerivedType operator++(int)
                {
                    DerivedType result(getMesh(), m_position);
                    setPosition(++m_position);
                    return result;
                }

                DerivedType &operator--()
                {
                    setPosition(--m_position);
                    return this->asDerived();
                }

                DerivedType operator--(int)
                {
                    DerivedType result(getMesh(), m_position);
                    setPosition(--m_position);
                    return result;
                }
        };

        template<typename Derived>
        ConstIndexProxyTrait2<Derived>::~ConstIndexProxyTrait2() {}
    }

    class FD_EXPORT ConstIndexProxy2 : public internal::ConstIndexProxyTrait2<ConstIndexProxy2>
    {
        friend class AbstractMeshComponent;
        friend class internal::ConstIndexProxyTrait2<ConstIndexProxy2>;
        protected:
            const AbstractMeshComponent *m_mesh;

        protected:
            ConstIndexProxy2(const AbstractMeshComponent *mesh, size_t position);

        public:
            virtual ~ConstIndexProxy2();
    };

    class FD_EXPORT IndexProxy2 : public internal::ConstIndexProxyTrait2<IndexProxy2>
    {
        friend class AbstractMeshComponent;
        friend class internal::ConstIndexProxyTrait2<IndexProxy2>;
        protected:
            AbstractMeshComponent *m_mesh;

        protected:
            IndexProxy2(AbstractMeshComponent *mesh, size_t position);

        public:
            virtual ~IndexProxy2();

            AbstractMeshComponent *getMesh()
            {
                return this->asDerived().m_mesh;
            }

            uint32_t getValue() const;

            uint32_t operator*() const
            {
                return getValue();
            }

            uint32_t &operator*();

            void setValue(uint32_t val);
    };


    namespace internal
    {
        template<typename DerivedType>
        class ConstIndexProxyTrait : public FDCore::CRTPTrait<DerivedType>
        {
            friend class FD3D::AbstractMesh;
            protected:
                size_t m_position;

            protected:
                ConstIndexProxyTrait(size_t pos) :
                    m_position(pos)
                {}

            public:
                virtual ~ConstIndexProxyTrait();

                const FD3D::AbstractMesh *getMesh() const
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
                    const uint32_t *ind = getMesh()->getIndices();
                    if(ind == nullptr)
                        return 0;

                    return *(ind + m_position);
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
                    setPosition(m_position - i);
                    return this->asDerived();
                }

                DerivedType operator-(size_t i)
                {
                    return DerivedType(getMesh(), m_position + i);
                }

                DerivedType &operator++()
                {
                    setPosition(++m_position);
                    return this->asDerived();
                }

                DerivedType operator++(int)
                {
                    DerivedType result(getMesh(), m_position);
                    setPosition(++m_position);
                    return result;
                }

                DerivedType &operator--()
                {
                    setPosition(--m_position);
                    return this->asDerived();
                }

                DerivedType operator--(int)
                {
                    DerivedType result(getMesh(), m_position);
                    setPosition(--m_position);
                    return result;
                }
        };

        template<typename Derived>
        ConstIndexProxyTrait<Derived>::~ConstIndexProxyTrait() {}
    }

    class FD_EXPORT ConstIndexProxy : public internal::ConstIndexProxyTrait<ConstIndexProxy>
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

    class FD_EXPORT IndexProxy : public internal::ConstIndexProxyTrait<IndexProxy>
    {
        friend class AbstractMesh;
        friend class internal::ConstIndexProxyTrait<IndexProxy>;
        protected:
            AbstractMesh *m_mesh;

        protected:
            IndexProxy(AbstractMesh *mesh, size_t position);

        public:
            virtual ~IndexProxy();

            AbstractMesh *getMesh()
            {
                return this->asDerived().m_mesh;
            }

            uint32_t getValue() const;

            uint32_t operator*() const
            {
                return getValue();
            }

            uint32_t &operator*();

            void setValue(uint32_t val);
    };

}

#endif // FD3D_INDEXPROXY_H
