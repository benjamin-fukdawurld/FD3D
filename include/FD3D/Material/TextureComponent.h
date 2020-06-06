#ifndef FD3D_TEXTURECOMPONENT_H
#define FD3D_TEXTURECOMPONENT_H

#include <cstdint>
#include <string>


#include <FD3D/SceneGraph/Component.h>

#include <FD3D/Material/AbstractTexture.h>

#include <assimp/material.h>

#include <FDCore/Macros.h>

namespace FD3D
{
    class FD_EXPORT TextureComponent : public AssetComponent<FD3D::AbstractTexture>
    {
        protected:
            uint32_t m_textureId;
            TextureType m_type;

        public:
            TextureComponent() : TextureComponent(nullptr) {}
            TextureComponent(AbstractTexture *texture) : TextureComponent(texture, 0, FD3D::TextureType::Invalid) {}
            TextureComponent(AbstractTexture *texture, uint32_t id, TextureType type) :
                AssetComponent<FD3D::AbstractTexture>(texture), m_textureId(id), m_type(type)
            {}

            ~TextureComponent() override = default;


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

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::AssetComponent<FD3D::AbstractTexture>);
generateTypeCode(FD3D::TextureComponent);

#endif // FD3D_TEXTURECOMPONENT_H
