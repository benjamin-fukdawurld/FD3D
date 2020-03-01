#include <FD3D/Material/Texture.h>

FD3D::Texture::~Texture() {}

const char *FD3D::Texture::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::Texture>::code;
}
