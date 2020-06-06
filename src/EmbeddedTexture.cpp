#include <FD3D/Material/EmbeddedTexture.h>

FD3D::EmbeddedTexture::~EmbeddedTexture()
{
    release();
}

size_t FD3D::EmbeddedTexture::getWidth() const
{
    return m_data.width;
}

size_t FD3D::EmbeddedTexture::getHeight() const
{
    return m_data.height;
}

size_t FD3D::EmbeddedTexture::getNumberOfChannels() const
{
    return m_data.channelsInformation.getNumberOfChannels();
}

uint8_t *FD3D::EmbeddedTexture::getData()
{
    return m_data.data.get();
}

const uint8_t *FD3D::EmbeddedTexture::getData() const
{
    return m_data.data.get();
}

const aiTexture *FD3D::EmbeddedTexture::getTexture() const
{
    return m_tex;
}

void FD3D::EmbeddedTexture::setTexture(const aiTexture *texture)
{
    m_tex = texture;
}

const FD3D::TextureData &FD3D::EmbeddedTexture::getTextureInformation() const
{
    return m_data;
}

bool FD3D::EmbeddedTexture::load()
{
    if(m_tex == nullptr)
        return false;

    m_data = AbstractTexture::loadEmbeddedTexture(m_tex);
    if(!m_data.data)
        return false;

    m_tex = nullptr;
    return true;
}

bool FD3D::EmbeddedTexture::isLoaded() const
{
    return m_data.data.get() != nullptr;
}

void FD3D::EmbeddedTexture::release()
{
    m_data = TextureData();
}

const char *FD3D::EmbeddedTexture::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::EmbeddedTexture>::code;
}

size_t FD3D::EmbeddedTexture::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::EmbeddedTexture>::hash();
}

bool FD3D::EmbeddedTexture::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::EmbeddedTexture>::hash()
            || FD3D::AbstractTexture::matchTypeCodeHash(hash);
}

