#ifndef FD3D_ABSTRACTTEXTURE_H
#define FD3D_ABSTRACTTEXTURE_H

#include <FDCore/BaseResource.h>

#include <memory>

#include <assimp/material.h>
#include <assimp/texture.h>

#include <cassert>

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

    namespace internal
    {
        aiTextureType textureTypeToAssimpType(FD3D::TextureType type);
        FD3D::TextureType textureTypeFromAssimpType(aiTextureType type);
    }

    class TextureChannelInformation
    {
        private:
            char m_hint[4];

        public:
            TextureChannelInformation(): m_hint{0}
            {}

            constexpr size_t getHintSize() const { return 4; }
            const char *getHint() const { return m_hint; }
            void setHint(const char hint[4]) { memcpy(m_hint, hint, 4); }

            size_t getNumberOfChannels() const { return (hasRed() ? 1 : 0) + (hasGreen() ? 1 : 0) + (hasBlue() ? 1 : 0) + (hasAlpha() ? 1 : 0); }
            size_t getPixelSize() const { return getRedSize() + getGreenSize() + getBlueSize() + getAlphaSize(); }

            bool hasRed() const { return m_hint[0] != 0; }
            bool isRedFloat() const { return m_hint[0] == 'f'; }
            void setRedFloat() { m_hint[0] = 'f'; }
            size_t getRedSize() const { return isRedFloat() ? 32 : static_cast<size_t>(-m_hint[0]); }
            void setRedSize(size_t s) { assert(s <= 128); m_hint[0] = static_cast<char>(-static_cast<int>(s)); }

            bool hasGreen() const { return m_hint[1] != 0; }
            bool isGreenFloat() const { return m_hint[1] == 'f'; }
            void setGreenFloat() { m_hint[1] = 'f'; }
            size_t getGreenSize() const { return isGreenFloat() ? 32 : static_cast<size_t>(-m_hint[1]); }
            void setGreenSize(size_t s) { assert(s <= 128); m_hint[1] = static_cast<char>(-static_cast<int>(s)); }

            bool hasBlue() const { return m_hint[2] != 0; }
            bool isBlueFloat() const { return m_hint[2] == 'f'; }
            void setBlueFloat() { m_hint[2] = 'f'; }
            size_t getBlueSize() const { return isBlueFloat() ? 32 : static_cast<size_t>(-m_hint[2]); }
            void setBlueSize(size_t s) { assert(s <= 128); m_hint[2] = static_cast<char>(-static_cast<int>(s)); }

            bool hasAlpha() const { return m_hint[3] != 0; }
            bool isAlphaFloat() const { return m_hint[3] == 'f'; }
            void setAlphaFloat() { m_hint[3] = 'f'; }
            size_t getAlphaSize() const { return isAlphaFloat() ? 32 : static_cast<size_t>(-m_hint[3]); }
            void setAlphaSize(size_t s) { assert(s <= 128); m_hint[3] = static_cast<char>(-static_cast<int>(s)); }
    };

    struct TextureData
    {
        size_t width;
        size_t height;
        TextureChannelInformation channelsInformation;
        std::unique_ptr<uint8_t[]> data;

        TextureData():
            width(0),
            height(0)
        {}
    };


    class AbstractTexture: public FDCore::BaseResource
    {
        protected:
            TextureType m_type;

        public:
            AbstractTexture() : AbstractTexture("") {}
            AbstractTexture(std::string_view textureName) :
                AbstractTexture(textureName, "")
            {}

            AbstractTexture(std::string_view textureName, std::string_view path) :
                FDCore::BaseResource (textureName, path),
                m_type(TextureType::Invalid)
            {}

            ~AbstractTexture() override = default;

            TextureType getType() const;

            void setType(TextureType type);

            static TextureData loadFile(std::string_view path);
            static TextureData loadEmbeddedTexture(const aiTexture *tex);

            const char *getTypeCode() const override;

            size_t getTypeCodeHash() const override;

            bool matchTypeCodeHash(size_t hash) const override;
    };


    //typedef AssetComponent<FD3D::AbstractTexture> TextureComponent;
}

generateTypeCode(FD3D::AbstractTexture);

#endif // FD3D_ABSTRACTTEXTURE_H
