#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>

namespace FD3D
{
    class Material
    {
        protected:
            glm::vec3 m_ambientColor;
            glm::vec3 m_diffuseColor;
            glm::vec3 m_specularColor;
            float m_shininess;
            uint32_t m_diffuseMap;
            uint32_t m_specularMap;

        public:
            Material();

            glm::vec3 &getAmbientColor();
            const glm::vec3 &getAmbientColor() const;
            void setAmbientColor(const glm::vec3 &ambient);

            glm::vec3 &getDiffuseColor();
            const glm::vec3 &getDiffuseColor() const;
            void setDiffuseColor(const glm::vec3 &diffuse);

            glm::vec3 &getSpecularColor();
            const glm::vec3 &getSpecularColor() const;
            void setSpecularColor(const glm::vec3 &specular);

            float getShininess() const;
            void setShininess(float shininess);

            uint32_t getDiffuseMap() const;
            void setDiffuseMap(const uint32_t &diffuseMap);

            uint32_t getSpecularMap() const;
            void setSpecularMap(const uint32_t &specularMap);
    };
}

#endif // MATERIAL_H
