#ifndef FD3D_VERTEX_H
#define FD3D_VERTEX_H

#include <cstdlib>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace FD3D
{
    struct VertexPositionUtils
    {
        typedef glm::vec3 type;
        static const size_t size = 3;
    };

    struct VertexNormalUtils
    {
        typedef glm::vec3 type;
        static const size_t size = 3;
    };

    struct VertexTextureUtils
    {
        typedef glm::vec2 type;
        static const size_t size = 2;
    };

    struct VertexColorUtils
    {
        typedef glm::vec4 type;
        static const size_t size = 4;
    };

    template<typename Derived, size_t nb_components = 8>
    class VertexTrait
    {
        public:
            static const size_t numberOfComponents = nb_components;

            float &operator[](size_t pos)
            {
                return static_cast<Derived*>(this)->data()[pos];
            }

            float operator[](size_t pos) const
            {
                return static_cast<Derived*>(this)->data()[pos];
            }

            size_t size() const
            {
                return numberOfComponents;
            }

            void assign(float value)
            {
                Derived &that = asDerived();
                for(size_t i = 0; i < nb_components; ++i)
                    that[i] = value;
            }

            void assign(float values[], size_t size = nb_components)
            {
                Derived &that = asDerived();
                for(size_t i = 0, imax = (size > nb_components ? nb_components : size);
                    i < imax; ++i)
                    that[i] = values[i];
            }

        private:
            Derived &asDerived()
            {
                return *static_cast<Derived*>(this);
            }
    };

    template<size_t nb_components = 8>
    class BaseVertexWrapper : public VertexTrait<BaseVertexWrapper<nb_components>, nb_components>
    {
        private:
            typedef VertexTrait<BaseVertexWrapper<nb_components>, nb_components> parent_type;

        public:
            static const size_t numberOfComponents = nb_components;

        protected:
            float *m_components;

        public:
            BaseVertexWrapper() {}

            BaseVertexWrapper(float value)
            {
                for (size_t i = 0; i < numberOfComponents; ++i)
                    m_components[i] = value;
            }

            BaseVertexWrapper(float values[], size_t size = nb_components)
            {
                for(size_t i = 0, imax = (size > nb_components ? nb_components : size);
                    i < imax; ++i)
                    m_components[i] = values[i];
            }

            float *data()
            {
                return m_components;
            }

            const float *data() const
            {
                return m_components;
            }
    };

    template<size_t nb_components = 8>
    class BaseVertex : public VertexTrait<BaseVertexWrapper<nb_components>, nb_components>
    {
        private:
            typedef VertexTrait<BaseVertexWrapper<nb_components>, nb_components> parent_type;

        public:
            static const size_t numberOfComponents = nb_components;

        protected:
            float m_components[nb_components];

        public:
            BaseVertex(float value = 0.0f)
            {
                for (size_t i = 0; i < numberOfComponents; ++i)
                    m_components[i] = value;
            }

            BaseVertex(float values[], size_t size = nb_components)
            {
                for(size_t i = 0, imax = (size > nb_components ? nb_components : size);
                    i < imax; ++i)
                    m_components[i] = values[i];
            }

            float *data()
            {
                return m_components;
            }

            const float *data() const
            {
                return m_components;
            }
    };

    template<typename ParentClass, size_t offset = 0>
    class VertexPositionHelper : public ParentClass
    {
        public:
            using ParentClass::ParentClass;

            typedef VertexPositionUtils::type PositionType;

            glm::vec3 &getPosition()
            {
                return *reinterpret_cast<glm::vec3*>(
                            static_cast<ParentClass*>(this)->data() + offset);
            }

            const glm::vec3 &getPosition() const
            {
                return *reinterpret_cast<glm::vec3*>(
                            static_cast<ParentClass*>(this)->data() + offset);
            }

            void setPosition(const glm::vec3 &pos)
            {
                float *components = static_cast<ParentClass*>(this)->data() + offset;
                *(components) = pos.x;
                *(components + 1) = pos.y;
                *(components + 2) = pos.z;
            }
    };

    template<typename ParentClass, size_t offset = 3>
    class VertexNormalHelper : public ParentClass
    {
        public:
            using ParentClass::ParentClass;

            typedef VertexNormalUtils::type NormalType;

            glm::vec3 &getNormal()
            {
                return *reinterpret_cast<glm::vec3*>(
                            static_cast<ParentClass*>(this)->data() + offset);
            }

            const glm::vec3 &getNormal() const
            {
                return *reinterpret_cast<glm::vec3*>(
                            static_cast<ParentClass*>(this)->data() + offset);
            }

            void setNormal(const glm::vec3 &n)
            {
                float *components = static_cast<ParentClass*>(this)->data() + offset;
                *(components) = n.x;
                *(components + 1) = n.y;
                *(components + 2) = n.z;
            }
    };

    template<typename ParentClass, size_t offset = 6, size_t nb_texture = 1>
    class VertexTextureHelper : public ParentClass
    {
        public:
            using ParentClass::ParentClass;

            typedef VertexTextureUtils::type TexCoordType;

            glm::vec2 &getTextureCoordinates(size_t pos = 0)
            {
                assert(pos < nb_texture);
                return *reinterpret_cast<glm::vec2*>(
                            static_cast<ParentClass*>(this)->data()
                                + offset
                                + (pos * sizeof(TexCoordType)));
            }

            const glm::vec2 &getTextureCoordinates(size_t pos = 0) const
            {
                assert(pos < nb_texture);
                return *reinterpret_cast<glm::vec2*>(
                            static_cast<ParentClass*>(this)->data()
                                + offset
                                + (pos * sizeof(TexCoordType)));
            }

            void setTexture(const glm::vec2 &t, size_t pos = 0)
            {
                assert(pos < nb_texture);
                float *components = static_cast<ParentClass*>(this)->data()
                                        + offset
                                        + (pos * sizeof(TexCoordType));
                *(components) = t.x;
                *(components + 1) = t.y;
            }
    };

    template<typename ParentClass, size_t offset = 6>
    class VertexColorHelper : public ParentClass
    {
        public:
            using ParentClass::ParentClass;

            typedef VertexColorUtils::type ColorType;

            glm::vec4 &getColor()
            {
                return *reinterpret_cast<glm::vec4*>(
                            static_cast<ParentClass*>(this)->data() + offset);
            }

            const glm::vec4 &getColor() const
            {
                return *reinterpret_cast<glm::vec4*>(
                            static_cast<ParentClass*>(this)->data() + offset);
            }

            void setColor(const glm::vec4 &t)
            {
                float *components = static_cast<ParentClass*>(this)->data() + offset;
                *(components) = t.x;
                *(components + 1) = t.y;
                *(components + 2) = t.z;
                *(components + 3) = t.w;
            }
    };

    typedef VertexPositionHelper<
                VertexNormalHelper<
                    VertexTextureHelper<
                        BaseVertex<8>,
                    6>,
                3>,
            0> Vertex;

    typedef VertexPositionHelper<
                VertexNormalHelper<
                    VertexTextureHelper<
                        BaseVertexWrapper<8>,
                    6>,
                3>,
            0> VertexWrapper;
}

#endif // FD3D_VERTEX_H
