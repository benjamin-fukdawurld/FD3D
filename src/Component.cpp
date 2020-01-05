#include <FD3D/SceneGraph/Component.h>

FD3D::Component::Component()
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
    return "";
}

size_t FD3D::Component::getTypeCodeHash() const
{
    return 0;
}
