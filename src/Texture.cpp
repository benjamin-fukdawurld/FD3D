#include <FD3D/Material/Texture.h>

#include <iostream>

FD3D::Texture::~Texture()
{
    release();
}

size_t FD3D::Texture::getWidth() const
{
    return m_width;
}

void FD3D::Texture::setWidth(size_t value)
{
    m_width = value;
}

size_t FD3D::Texture::getHeight() const
{
    return m_height;
}

void FD3D::Texture::setHeight(size_t value)
{
    m_height = value;
}

size_t FD3D::Texture::getNumberOfChannels() const
{
    return m_numberOfChannels;
}

void FD3D::Texture::setNumberOfChannels(size_t value)
{
    m_numberOfChannels = value;
}

uint8_t *FD3D::Texture::getData()
{
    return m_data.get();
}

const uint8_t *FD3D::Texture::getData() const
{
    return m_data.get();
}

bool FD3D::Texture::load()
{
    TextureData data = AbstractTexture::loadFile(getResourcePath());
    if(!data.data)
        return false;

    m_data = std::move(data.data);
    m_width = data.width;
    m_height = data.height;
    m_numberOfChannels = data.channelsInformation.getNumberOfChannels();

    return true;
}

bool FD3D::Texture::isLoaded() const
{
    return m_data.get() != nullptr;
}

void FD3D::Texture::release()
{
    m_data.reset();
    m_width = 0;
    m_height = 0;
    m_numberOfChannels = 0;
}

const char *FD3D::Texture::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::Texture>::code;
}

size_t FD3D::Texture::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::Texture>::hash();
}

bool FD3D::Texture::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::Texture>::hash()
            || FD3D::AbstractTexture::matchTypeCodeHash(hash);
}
