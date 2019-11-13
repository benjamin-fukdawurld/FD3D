#ifndef FD3D_MATERIAL_H
#define FD3D_MATERIAL_H

#include <glm/vec3.hpp>
#include <unordered_map>
#include <vector>

#include <FD3D/Texture.h>

namespace FD3D
{
    class Material
    {
        protected:
            std::string m_name;
            glm::vec3 m_ambientColor;
            glm::vec3 m_diffuseColor;
            glm::vec3 m_specularColor;
            float m_shininess;

            std::unordered_map<TextureType, std::vector<uint32_t>> m_textures;

        public:
            Material();

            const std::string &getName() const;
            void setName(const std::string &name);

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

            std::unordered_map<TextureType, std::vector<uint32_t>> &getTextures()
            {
                return m_textures;
            }

            std::vector<uint32_t> &getTextures(TextureType type)
            {
                return m_textures[type];
            }
    };
}

#endif // FD3D_MATERIAL_H
