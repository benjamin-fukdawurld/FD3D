#ifndef FD3D_MATERIAL_H
#define FD3D_MATERIAL_H

#include <glm/vec3.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

#include <FD3D/Material/Texture.h>
#include <FD3D/SceneGraph/Component.h>

#include <FDCore/TypeInformation.h>

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT Material : public Component
    {
        protected:
            glm::vec3 m_ambientColor;
            glm::vec3 m_diffuseColor;
            glm::vec3 m_specularColor;
            float m_shininess;
            float m_opacity;

            std::unordered_map<TextureType, std::vector<uint32_t>> m_textures;

        public:
            Material();
            ~Material() override;

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

            float getOpacity() const;
            void setOpacity(float opacity);

            std::unordered_map<TextureType, std::vector<uint32_t>> &getTextures()
            {
                return m_textures;
            }

            std::vector<uint32_t> &getTextures(TextureType type)
            {
                return m_textures[type];
            }

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;
    };

    bool load(const aiMaterial *in, Material &out, const std::string &directory,
              std::function<uint32_t(std::string)> textureLoader);
}

generateTypeCode(FD3D::Material);

#endif // FD3D_MATERIAL_H
