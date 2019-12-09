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
        Invalid = aiTextureType_UNKNOWN,
        None = aiTextureType_NONE,
        Diffuse = aiTextureType_DIFFUSE,
        Specular = aiTextureType_SPECULAR,
        Ambient = aiTextureType_AMBIENT,
        Emissive = aiTextureType_EMISSIVE,
        Height = aiTextureType_HEIGHT,
        Normals = aiTextureType_NORMALS,
        Shininess = aiTextureType_SHININESS,
        Opacity = aiTextureType_OPACITY,
        Displacement = aiTextureType_DISPLACEMENT,
        LightMap = aiTextureType_LIGHTMAP,
        Reflection = aiTextureType_REFLECTION
    };

    class Texture : public Component
    {
        protected:
            uint32_t m_textureId;
            TextureType m_type;

        public:
            Texture() : m_textureId(0), m_type() {}
            Texture(uint32_t id, TextureType type) : m_textureId(id), m_type(type) {}
            virtual ~Texture();

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
    };
}

#endif // FD3D_TEXTURE_H
