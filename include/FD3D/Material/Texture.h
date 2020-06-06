#ifndef TEXTURE_H
#define TEXTURE_H

#include <FD3D/Material/AbstractTexture.h>

namespace FD3D
{
    class Texture : public AbstractTexture
    {
        protected:
            size_t m_width;
            size_t m_height;
            size_t m_numberOfChannels;
            std::unique_ptr<uint8_t[]> m_data;

        public:
            Texture() : Texture("") {}
            Texture(std::string_view textureName) :
                Texture(textureName, "")
            {}

            Texture(std::string_view textureName, std::string_view path) :
                AbstractTexture(textureName, path),
                m_width(0),
                m_height(0),
                m_numberOfChannels(0),
                m_data(nullptr)
            {}

            ~Texture() override;

            size_t getWidth() const;
            void setWidth(size_t value);

            size_t getHeight() const;
            void setHeight(size_t value);

            size_t getNumberOfChannels() const;
            void setNumberOfChannels(size_t value);

            uint8_t *getData();
            const uint8_t *getData() const;

            bool load() override;
            bool isLoaded() const override;
            void release() override;

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };
}

generateTypeCode(FD3D::Texture);

#endif // TEXTURE_H
