#ifndef LIGHT_H
#define LIGHT_H

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

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
            glm::vec3 m_ambient;
            glm::vec3 m_diffuse;
            glm::vec3 m_specular;
            glm::vec3 m_position;
            glm::vec3 m_direction;
            LightType m_type;

        public:
            Light();

            glm::vec4 &getAmbientColor();
            const glm::vec4 &getAmbientColor() const;

            glm::vec3 &getDiffuse();
            const glm::vec3 &getDiffuse() const;

            glm::vec3 &getSpecular();
            const glm::vec3 &getSpecular() const;

            glm::vec3 &getPosition();
            const glm::vec3 &getPosition() const;

            glm::vec3 &getDirection();
            const glm::vec3 &getDirection() const;

            void setAmbientColor(const glm::vec4 color);
            void setDiffuse(const glm::vec3 &diffuse);
            void setSpecular(const glm::vec3 &specular);

            void setPosition(const glm::vec3 position);
            void translate(const glm::vec3 v);

            void setDirection(const glm::vec3 direction);
            void rotate(const glm::vec3 angles);
            void rotate(const glm::quat quaternion);

            LightType getType() const;
            void setType(const LightType &type);
    };
}

#endif // LIGHT_H
