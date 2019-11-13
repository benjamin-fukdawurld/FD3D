#ifndef FD3D_TEXTURE_H
#define FD3D_TEXTURE_H

#include <cstdint>
#include <string>

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

    class Texture
    {
        protected:
            uint32_t m_id;
            TextureType m_type;

        public:
            Texture() : m_id(0), m_type() {}
            Texture(uint32_t id, TextureType type) : m_id(id), m_type(type) {}

            uint32_t getId() const
            {
                return m_id;
            }

            void setId(uint32_t id)
            {
                m_id = id;
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
