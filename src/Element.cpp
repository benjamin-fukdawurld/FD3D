#include <FD3D/SceneGraph/Element.h>


FD3D::Element::Element() :
    FDCore::Identifiable<uintptr_t>(),
    FDCore::Object()
{}

const char *FD3D::Element::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::Element>::code;
}

size_t FD3D::Element::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::Element>::hash();
}

bool FD3D::Element::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::Element>::hash()
            || FDCore::Object::matchTypeCodeHash(hash);
}
