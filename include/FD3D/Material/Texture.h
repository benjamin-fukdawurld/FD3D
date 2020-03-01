#ifndef FD3D_TEXTURE_H
#define FD3D_TEXTURE_H

#include <cstdint>
#include <string>


#include <FD3D/SceneGraph/Component.h>

#include <assimp/material.h>

namespace FD3D
{
    enum class TextureType : uint8_t
    {
        Invalid,
        None,
        Diffuse,
        Specular,
        Ambient,
        Emissive,
        Height,
        Normals,
        Shininess,
        Opacity,
        Displacement,
        LightMap,
        Reflection
    };

    class Texture : public Component
    {
        protected:
            uint32_t m_textureId;
            TextureType m_type;

        public:
            Texture() : m_textureId(0), m_type() {}
            Texture(uint32_t id, TextureType type) : m_textureId(id), m_type(type) {}
            ~Texture() override;

            uint32_t getTextureId() const
            {
                return m_textureId;
            }

            void setTextureId(uint32_t id)
            {
                m_textureId = id;
            }

            TextureType getType() const
            {
                return m_type;
            }

            void setType(TextureType type)
            {
                m_type = type;
            }

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;
    };
}

generateTypeCode(FD3D::Texture);

#endif // FD3D_TEXTURE_H
