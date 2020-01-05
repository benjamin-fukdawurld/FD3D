#ifndef FD3D_LIGHT_H
#define FD3D_LIGHT_H

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#include <FD3D/SceneGraph/SceneNode.h>

#include <FDCore/TypeInformation.h>

namespace FD3D
{
    enum class LightType : uint8_t
    {
        Undefined,
        SpotLight,
        PointLight,
        DirectionalLight,
        AmbientLight,
        AreaLight
    };

    struct LightColor
    {
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;

        LightColor();

        LightColor(const glm::vec4 &ambient,
                   const glm::vec4 &diffuse,
                   const glm::vec4 &specular);
    };

    class LightAttenuation
    {
        protected:
            float m_constantAttenuation;
            float m_linearAttenuation;
            float m_quadraticAttenuation;

        public:
            LightAttenuation();

            LightAttenuation(float constant, float linear, float quadratic);

            float getConstantAttenuation() const;
            void setConstantAttenuation(float val);

            float getLinearAttenuation() const;
            void setLinearAttenuation(float val);

            float getQuadraticAttenuation() const;
            void setQuadraticAttenuation(float val);

            float getAttenuation(float distance) const;
    };

    class LightCone
    {
        protected:
            float m_innerAngle;
            float m_outerAngle;

        public:
            LightCone();
            LightCone(float innerAngle, float outerAngle);

            float getInnerAngle() const;
            void setInnerAngle(float val);

            float getOuterAngle() const;
            void setOuterAngle(float val);
    };

    class Light
    {
        public:
            LightColor color;
            LightCone cone;
            LightAttenuation attenuation;

        protected:
            glm::vec3 m_position;
            glm::vec3 m_direction;
            glm::vec3 m_up;
            LightType m_type;

        public:
            Light();

            glm::vec3 &getPosition();
            const glm::vec3 &getPosition() const;
            void setPosition(const glm::vec3 position);

            glm::vec3 &getDirection();
            const glm::vec3 &getDirection() const;
            void setDirection(const glm::vec3 direction);

            glm::vec3 &getUp();
            const glm::vec3 &getUp() const;
            void setUp(const glm::vec3 up);

            void translate(const glm::vec3 v);
            void rotate(const glm::vec3 angles);
            void rotate(const glm::quat quaternion);

            LightType getType() const;
            void setType(const LightType &type);
    };

    typedef EntityNode<Light> LightNode;
}

generateTypeCode(FD3D::Light);
generateTypeCode(FD3D::LightNode);

#endif // FD3D_LIGHT_H
