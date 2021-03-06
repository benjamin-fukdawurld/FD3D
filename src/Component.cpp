#include <FD3D/SceneGraph/Component.h>

FD3D::Component::Component() :
    Element()
{

}

FD3D::Component::~Component()
{

}

const std::string &FD3D::Component::getName() const
{
    return m_name;
}

void FD3D::Component::setName(const std::string &name)
{
    m_name = name;
}

const char *FD3D::Component::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::Component>::code;
}

size_t FD3D::Component::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::Component>::hash();
}

bool FD3D::Component::matchTypeCodeHash(size_t hash) const
{
    return hash == FDCore::TypeCodeHelper<FD3D::Component>::hash()
            || FD3D::Element::matchTypeCodeHash(hash);
}
