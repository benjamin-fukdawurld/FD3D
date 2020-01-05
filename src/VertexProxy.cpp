#include <FD3D/Utils/VertexProxy.h>
#include <FD3D/Mesh/AbstractMesh.h>

FD3D::ConstVertexProxy::ConstVertexProxy(const FD3D::AbstractMesh *mesh, size_t index) :
    ConstVertexProxyTrait<ConstVertexProxy>(index),
    m_mesh(mesh)
{}

FD3D::ConstVertexProxy::~ConstVertexProxy() {}

FD3D::VertexProxy::VertexProxy(FD3D::AbstractMesh *mesh, size_t index) :
    internal::ConstVertexProxyTrait<VertexProxy>(index),
    m_mesh(mesh)
{}

FD3D::VertexProxy::~VertexProxy() {}

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

FD3D::VertexProxy FD3D::AbstractMesh::operator[](size_t index)
{
    return { this, index };
}

FD3D::ConstVertexProxy FD3D::AbstractMesh::operator[](size_t index) const
{
    return { this, index };
}

FD3D::VertexProxy FD3D::AbstractMesh::operator()(size_t index)
{
    return { this, *(getIndices() + index) };
}

FD3D::ConstVertexProxy FD3D::AbstractMesh::operator()(size_t index) const
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
