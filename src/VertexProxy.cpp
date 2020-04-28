#include <FD3D/Utils/VertexProxy.h>
#include <FD3D/Mesh/AbstractMesh.h>

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

FD3D::VertexProxy FD3D::AbstractMesh::getVertex(size_t index)
{
    return { this, index };
}

FD3D::ConstVertexProxy FD3D::AbstractMesh::getVertex(size_t index) const
{
    return { this, index };
}

FD3D::VertexProxy FD3D::AbstractMesh::getVertexFromIndex(size_t index)
{
    return { this, *(getIndices() + index) };
}

FD3D::ConstVertexProxy FD3D::AbstractMesh::getVertexFromIndex(size_t index) const
{
    return { this, *(getIndices() + index) };
}

FD3D::IndexProxy FD3D::AbstractMesh::getIndex(size_t pos)
{
    return { this, pos };
}

FD3D::ConstIndexProxy FD3D::AbstractMesh::getIndex(size_t pos) const
{
    return { this, pos };
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
