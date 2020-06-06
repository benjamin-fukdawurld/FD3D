#include <FD3D/Utils/VertexProxy.h>
#include <FD3D/Mesh/AbstractMeshComponent.h>
#include <FD3D/Mesh/AbstractMesh.h>

FD3D::ConstVertexProxy2::ConstVertexProxy2(const FD3D::AbstractMeshComponent *mesh, size_t index) :
    ConstVertexProxyTrait2<ConstVertexProxy2>(index),
    m_mesh(mesh)
{}

FD3D::ConstVertexProxy2::ConstVertexProxy2(const VertexProxy2 &v) :
    ConstVertexProxyTrait2<ConstVertexProxy2>(v.getIndex()),
    m_mesh(v.getMesh())
{}

FD3D::ConstVertexProxy2::~ConstVertexProxy2() {}

FD3D::VertexProxy2::VertexProxy2(FD3D::AbstractMeshComponent *mesh, size_t index) :
    internal::ConstVertexProxyTrait2<VertexProxy2>(index),
    m_mesh(mesh)
{}

FD3D::VertexProxy2::~VertexProxy2() {}

const glm::vec3 *FD3D::VertexProxy2::getPosition() const
{
    return internal::ConstVertexProxyTrait2<VertexProxy2>::getPosition();
}

const glm::vec3 *FD3D::VertexProxy2::getNormal() const
{
    return internal::ConstVertexProxyTrait2<VertexProxy2>::getNormal();
}

const glm::vec3 *FD3D::VertexProxy2::getTangent() const
{
    return internal::ConstVertexProxyTrait2<VertexProxy2>::getTangent();
}

const glm::vec3 *FD3D::VertexProxy2::getBitangent() const
{
    return internal::ConstVertexProxyTrait2<VertexProxy2>::getBitangent();
}

const glm::vec2 *FD3D::VertexProxy2::getUv(size_t index) const
{
    return internal::ConstVertexProxyTrait2<VertexProxy2>::getUv(index);
}

const glm::vec4 *FD3D::VertexProxy2::getColor(size_t index) const
{
    return internal::ConstVertexProxyTrait2<VertexProxy2>::getColor(index);
}

glm::vec3 *FD3D::VertexProxy2::getPosition()
{
    return const_cast<glm::vec3 *>(internal::ConstVertexProxyTrait2<VertexProxy2>::getPosition());
}

glm::vec3 *FD3D::VertexProxy2::getNormal()
{
    return const_cast<glm::vec3 *>(internal::ConstVertexProxyTrait2<VertexProxy2>::getNormal());
}

glm::vec3 *FD3D::VertexProxy2::getTangent()
{
    return const_cast<glm::vec3 *>(internal::ConstVertexProxyTrait2<VertexProxy2>::getTangent());
}

glm::vec3 *FD3D::VertexProxy2::getBitangent()
{
    return const_cast<glm::vec3 *>(internal::ConstVertexProxyTrait2<VertexProxy2>::getBitangent());
}

glm::vec2 *FD3D::VertexProxy2::getUv(size_t index)
{
    return const_cast<glm::vec2 *>(internal::ConstVertexProxyTrait2<VertexProxy2>::getUv(index));
}

glm::vec4 *FD3D::VertexProxy2::getColor(size_t index)
{
    return const_cast<glm::vec4 *>(internal::ConstVertexProxyTrait2<VertexProxy2>::getColor(index));
}

std::string_view FD3D::vertexComponentTypeToString(FD3D::VertexComponentType type)
{
    switch(type)
    {
        case VertexComponentType::Position:
        return "Position";

        case VertexComponentType::Normal:
        return "Normal";

        case VertexComponentType::Color:
        return "Color";

        case VertexComponentType::Texture:
        return "Texture";

        case VertexComponentType::Tangent:
        return "Tangent";

        case VertexComponentType::Invalid:
        return "Invalid";
    }

    return "Invalid";
}

FD3D::VertexComponentType FD3D::vertexComponentTypeFromString(std::string_view str)
{
    if(str == "Position")
        return VertexComponentType::Position;

    if(str == "Normal")
        return VertexComponentType::Normal;

    if(str == "Color")
        return VertexComponentType::Color;

    if(str == "Texture")
        return VertexComponentType::Texture;

    if(str == "Tangent")
        return VertexComponentType::Tangent;

    return VertexComponentType::Invalid;
}




FD3D::ConstVertexProxy::ConstVertexProxy(const FD3D::AbstractMesh *mesh, size_t index) :
    ConstVertexProxyTrait<ConstVertexProxy>(index),
    m_mesh(mesh)
{}

FD3D::ConstVertexProxy::ConstVertexProxy(const VertexProxy &v) :
    ConstVertexProxyTrait<ConstVertexProxy>(v.getIndex()),
    m_mesh(v.getMesh())
{}

FD3D::ConstVertexProxy::~ConstVertexProxy() {}

FD3D::VertexProxy::VertexProxy(FD3D::AbstractMesh *mesh, size_t index) :
    internal::ConstVertexProxyTrait<VertexProxy>(index),
    m_mesh(mesh)
{}

FD3D::VertexProxy::~VertexProxy() {}

const glm::vec3 *FD3D::VertexProxy::getPosition() const
{
    return internal::ConstVertexProxyTrait<VertexProxy>::getPosition();
}

const glm::vec3 *FD3D::VertexProxy::getNormal() const
{
    return internal::ConstVertexProxyTrait<VertexProxy>::getNormal();
}

const glm::vec3 *FD3D::VertexProxy::getTangent() const
{
    return internal::ConstVertexProxyTrait<VertexProxy>::getTangent();
}

const glm::vec3 *FD3D::VertexProxy::getBitangent() const
{
    return internal::ConstVertexProxyTrait<VertexProxy>::getBitangent();
}

const glm::vec2 *FD3D::VertexProxy::getUv(size_t index) const
{
    return internal::ConstVertexProxyTrait<VertexProxy>::getUv(index);
}

const glm::vec4 *FD3D::VertexProxy::getColor(size_t index) const
{
    return internal::ConstVertexProxyTrait<VertexProxy>::getColor(index);
}

glm::vec3 *FD3D::VertexProxy::getPosition()
{
    return const_cast<glm::vec3 *>(internal::ConstVertexProxyTrait<VertexProxy>::getPosition());
}

glm::vec3 *FD3D::VertexProxy::getNormal()
{
    return const_cast<glm::vec3 *>(internal::ConstVertexProxyTrait<VertexProxy>::getNormal());
}

glm::vec3 *FD3D::VertexProxy::getTangent()
{
    return const_cast<glm::vec3 *>(internal::ConstVertexProxyTrait<VertexProxy>::getTangent());
}

glm::vec3 *FD3D::VertexProxy::getBitangent()
{
    return const_cast<glm::vec3 *>(internal::ConstVertexProxyTrait<VertexProxy>::getBitangent());
}

glm::vec2 *FD3D::VertexProxy::getUv(size_t index)
{
    return const_cast<glm::vec2 *>(internal::ConstVertexProxyTrait<VertexProxy>::getUv(index));
}

glm::vec4 *FD3D::VertexProxy::getColor(size_t index)
{
    return const_cast<glm::vec4 *>(internal::ConstVertexProxyTrait<VertexProxy>::getColor(index));
}
