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
        typedef glm::vec3 type;
        static const size_t size = 2;
    };

    struct VertexColorUtils
    {
        typedef glm::vec4 type;
        static const size_t size = 4;
    };

    template<size_t nb_components = 8>
    class BaseVertex
    {
        public:
            static const size_t numberOfComponents = nb_components;

        protected:
            float m_components[nb_components];

        public:
            BaseVertex(float value = 0.0f)
            {
                for(size_t i = 0; i < nb_components; ++i)
                    m_components[i] = value;
            }

            BaseVertex(float values[], size_t size = nb_components)
            {
                for(size_t i = 0, imax = (size > nb_components ? nb_components : size);
                    i < imax; ++i)
                    m_components[i] = values[i];
            }

            float &operator[](size_t pos)
            {
                return m_components[pos];
            }

            float operator[](size_t pos) const
            {
                return m_components[pos];
            }

            size_t size() const
            {
                return numberOfComponents;
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
                            static_cast<ParentClass>(this)->data() + offset);
            }

            const glm::vec3 &getPosition() const
            {
                return *reinterpret_cast<glm::vec3*>(
                            static_cast<ParentClass>(this)->data() + offset);
            }

            void setPosition(const glm::vec3 &pos)
            {
                float *components = static_cast<ParentClass>(this)->data() + offset;
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
                            static_cast<ParentClass>(this)->data() + offset);
            }

            const glm::vec3 &getNormal() const
            {
                return *reinterpret_cast<glm::vec3*>(
                            static_cast<ParentClass>(this)->data() + offset);
            }

            void setNormal(const glm::vec3 &n)
            {
                float *components = static_cast<ParentClass>(this)->data() + offset;
                *(components) = n.x;
                *(components + 1) = n.y;
                *(components + 2) = n.z;
            }
    };

    template<typename ParentClass, size_t offset = 6>
    class VertexTextureHelper : public ParentClass
    {
        public:
            using ParentClass::ParentClass;

            typedef VertexNormalUtils::type NormalType;

            glm::vec2 &getTextureCoordinates()
            {
                return *reinterpret_cast<glm::vec2*>(
                            static_cast<ParentClass>(this)->data() + offset);
            }

            const glm::vec2 &getTextureCoordinates() const
            {
                return *reinterpret_cast<glm::vec2*>(
                            static_cast<ParentClass>(this)->data() + offset);
            }

            void setNormal(const glm::vec2 &t)
            {
                float *components = static_cast<ParentClass>(this)->data() + offset;
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
                            static_cast<ParentClass>(this)->data() + offset);
            }

            const glm::vec4 &getColor() const
            {
                return *reinterpret_cast<glm::vec4*>(
                            static_cast<ParentClass>(this)->data() + offset);
            }

            void setColor(const glm::vec4 &t)
            {
                float *components = static_cast<ParentClass>(this)->data() + offset;
                *(components) = t.x;
                *(components + 1) = t.y;
                *(components + 2) = t.z;
                *(components + 3) = t.w;
            }
    };

    typedef VertexNormalHelper<
                VertexNormalHelper<
                    VertexTextureHelper<
                        BaseVertex<8>,
                    6>,
                3>,
            0> Vertex;
}

#endif // FD3D_VERTEX_H