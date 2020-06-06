#include <FD3D/Material/AbstractTexture.h>

#include <assimp/scene.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

aiTextureType FD3D::internal::textureTypeToAssimpType(FD3D::TextureType type)
{
    switch (type)
    {
        case FD3D::TextureType::None:
        return aiTextureType_NONE;

        case FD3D::TextureType::Height:
        return aiTextureType_HEIGHT;

        case FD3D::TextureType::Ambient:
        return aiTextureType_AMBIENT;

        case FD3D::TextureType::Diffuse:
        return aiTextureType_DIFFUSE;

        case FD3D::TextureType::Normals:
        return aiTextureType_NORMALS;

        case FD3D::TextureType::Opacity:
        return aiTextureType_OPACITY;

        case FD3D::TextureType::Emissive:
        return aiTextureType_EMISSIVE;

        case FD3D::TextureType::LightMap:
        return aiTextureType_LIGHTMAP;

        case FD3D::TextureType::Specular:
        return aiTextureType_SPECULAR;

        case FD3D::TextureType::Shininess:
        return aiTextureType_SHININESS;

        case FD3D::TextureType::Reflection:
        return aiTextureType_REFLECTION;

        case FD3D::TextureType::Displacement:
        return aiTextureType_DISPLACEMENT;

        case FD3D::TextureType::Invalid:
        return aiTextureType_UNKNOWN;
    }

    return aiTextureType_UNKNOWN;
}

FD3D::TextureType FD3D::internal::textureTypeFromAssimpType(aiTextureType type)
{
    switch (type)
    {
        case aiTextureType_NONE:
        return FD3D::TextureType::None;

        case aiTextureType_HEIGHT:
        return FD3D::TextureType::Height;

        case aiTextureType_AMBIENT:
        return FD3D::TextureType::Ambient;

        case aiTextureType_DIFFUSE:
        return FD3D::TextureType::Diffuse;

        case aiTextureType_NORMALS:
        return FD3D::TextureType::Normals;

        case aiTextureType_OPACITY:
        return FD3D::TextureType::Opacity;

        case aiTextureType_EMISSIVE:
        return FD3D::TextureType::Emissive;

        case aiTextureType_LIGHTMAP:
        return FD3D::TextureType::LightMap;

        case aiTextureType_SPECULAR:
        return FD3D::TextureType::Specular;

        case aiTextureType_SHININESS:
        return FD3D::TextureType::Shininess;

        case aiTextureType_REFLECTION:
        return FD3D::TextureType::Reflection;

        case aiTextureType_DISPLACEMENT:
        return FD3D::TextureType::Displacement;

        case aiTextureType_UNKNOWN:
        default:
        return FD3D::TextureType::Invalid;
    }
}

FD3D::TextureType FD3D::AbstractTexture::getType() const
{
    aiTexture tex;
    return m_type;
}

void FD3D::AbstractTexture::setType(FD3D::TextureType type)
{
    m_type = type;
}

FD3D::TextureData FD3D::AbstractTexture::loadFile(std::string_view path)
{
    TextureData result;

    int width, height, nbChannels;
    stbi_set_flip_vertically_on_load(true);
    result.data.reset(stbi_load(path.data(), &width, &height, &nbChannels, 0));

    if (!result.data)
    {
        std::cout << "Failed to load texture '" << path << "'" << std::endl;
        return result;
    }

    switch(nbChannels)
    {
        case 1:
            result.channelsInformation.setRedSize(8);
            [[fallthrough]];
        case 2:
            result.channelsInformation.setGreenSize(8);
            [[fallthrough]];
        case 3:
            result.channelsInformation.setBlueSize(8);
            [[fallthrough]];
        case 4:
            result.channelsInformation.setAlphaSize(8);
        break;

        case 0:
        default:
            result.data.reset();
            std::cout << "Failed to load texture '" << path << "': invalid number of channels" << std::endl;
        return result;

    }

    result.width = static_cast<size_t>(width);
    result.height = static_cast<size_t>(height);

    return result;
}

FD3D::TextureData FD3D::AbstractTexture::loadEmbeddedTexture(const aiTexture *tex)
{
    TextureData result;
    if(tex->mHeight == 0)
    {
        int width, height, nbChannels;
        result.data.reset(stbi_load_from_memory(reinterpret_cast<uint8_t*>(tex->pcData), static_cast<int>(tex->mWidth), &width, &height, &nbChannels, 0));

        if (!result.data)
        {
            std::cerr << "Failed to load texture '" << tex->mFilename.C_Str() << "'" << std::endl;
            return result;
        }

        switch(nbChannels)
        {
            case 1:
                result.channelsInformation.setRedSize(8);
                [[fallthrough]];
            case 2:
                result.channelsInformation.setGreenSize(8);
                [[fallthrough]];
            case 3:
                result.channelsInformation.setBlueSize(8);
                [[fallthrough]];
            case 4:
                result.channelsInformation.setAlphaSize(8);
            break;

            case 0:
            default:
                result.data.reset();
                std::cout << "Failed to load texture '" << tex->mFilename.C_Str() << "': invalid number of channels" << std::endl;
            return result;

        }

        result.width = static_cast<size_t>(width);
        result.height = static_cast<size_t>(height);

        return result;
    }


    result.channelsInformation.setRedSize(static_cast<size_t>(tex->achFormatHint[4]) - '0');
    result.channelsInformation.setGreenSize(static_cast<size_t>(tex->achFormatHint[5]) - '0');
    result.channelsInformation.setBlueSize(static_cast<size_t>(tex->achFormatHint[6]) - '0');
    result.channelsInformation.setAlphaSize(static_cast<size_t>(tex->achFormatHint[7]) - '0');

    size_t dataSize = static_cast<size_t>(tex->mWidth) * static_cast<size_t>(tex->mHeight) * (result.channelsInformation.getPixelSize() / 8);

    if(dataSize == 0)
    {
        std::cerr << "Failed to load texture, invalid texture size: w = " << tex->mWidth
                  << " h = " << tex->mHeight
                  << " nb channels = " << result.channelsInformation.getNumberOfChannels()
                  << "hint = '" << tex->achFormatHint << "'"
                  << std::endl;

        const char noChannel[4] ={0, 0, 0, 0};
        result.channelsInformation.setHint(noChannel);
        return result;
    }

    result.width = static_cast<size_t>(tex->mWidth);
    result.height = static_cast<size_t>(tex->mHeight);
    result.data.reset(new uint8_t[dataSize]);
    memcpy(result.data.get(), tex->pcData, dataSize);

    return result;
}

const char *FD3D::AbstractTexture::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::AbstractTexture>::code;
}

size_t FD3D::AbstractTexture::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::AbstractTexture>::hash();
}

bool FD3D::AbstractTexture::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::AbstractTexture>::hash()
            || FDCore::BaseResource::matchTypeCodeHash(hash);
}
