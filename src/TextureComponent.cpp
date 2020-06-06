#include <FD3D/Material/TextureComponent.h>

const char *FD3D::TextureComponent::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::TextureComponent>::code;
}

size_t FD3D::TextureComponent::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::TextureComponent>::hash();
}

bool FD3D::TextureComponent::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<TextureComponent>::hash()
            || AssetComponent<AbstractTexture>::matchTypeCodeHash(hash);
}
