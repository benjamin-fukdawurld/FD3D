#ifndef FD3D_LIGHT_H
#define FD3D_LIGHT_H

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#include <FD3D/SceneNode.h>

#include <FDCore/TypeInformation.h>

namespace FD3D
{
    enum class LightType : uint8_t
    {
        SpotLight,
        PointLight,
        DirectionalLight
    };

    class Light
    {
        protected:
            glm::vec4 m_ambient;
            glm::vec4 m_diffuse;
            glm::vec4 m_specular;
            glm::vec3 m_position;
            glm::vec3 m_direction;
            LightType m_type;

        public:
            Light();

            glm::vec4 &getAmbientColor();
            const glm::vec4 &getAmbientColor() const;

            glm::vec4 &getDiffuse();
            const glm::vec4 &getDiffuse() const;

            glm::vec4 &getSpecular();
            const glm::vec4 &getSpecular() const;

            glm::vec3 &getPosition();
            const glm::vec3 &getPosition() const;

            glm::vec3 &getDirection();
            const glm::vec3 &getDirection() const;

            void setAmbientColor(const glm::vec4 color);
            void setDiffuse(const glm::vec4 &diffuse);
            void setSpecular(const glm::vec4 &specular);

            void setPosition(const glm::vec3 position);
            void translate(const glm::vec3 v);

            void setDirection(const glm::vec3 direction);
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
