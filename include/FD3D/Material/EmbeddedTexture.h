#ifndef FD3D_EMBEDDEDTEXTURE_H
#define FD3D_EMBEDDEDTEXTURE_H

#include <FD3D/Material/AbstractTexture.h>

namespace FD3D
{
    class EmbeddedTexture : public AbstractTexture
    {
        protected:
            TextureData m_data;
            const aiTexture *m_tex;

        public:
            EmbeddedTexture() : EmbeddedTexture("") {}
            EmbeddedTexture(std::string_view textureName) :
                EmbeddedTexture(textureName, "")
            {}

            EmbeddedTexture(std::string_view textureName, std::string_view path) :
                EmbeddedTexture(textureName, path, nullptr)
            {}

            EmbeddedTexture(std::string_view textureName, std::string_view path, const aiTexture *tex) :
                AbstractTexture(textureName, path),
                m_tex(tex)
            {}

            ~EmbeddedTexture() override;

            size_t getWidth() const;
            size_t getHeight() const;
            size_t getNumberOfChannels() const;

            uint8_t *getData();
            const uint8_t *getData() const;

            const aiTexture *getTexture() const;
            void setTexture(const aiTexture *texture);

            const TextureData &getTextureInformation() const;

            bool load() override;
            bool isLoaded() const override;
            void release() override;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::EmbeddedTexture);

#endif // FD3D_EMBEDDEDTEXTURE_H
