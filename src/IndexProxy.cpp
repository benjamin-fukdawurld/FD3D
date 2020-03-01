#include "include/FD3D/Utils/IndexProxy.h"

#include <FD3D/Mesh/AbstractMesh.h>

FD3D::ConstIndexProxy::ConstIndexProxy(const FD3D::AbstractMesh *mesh, size_t position) :
    internal::ConstIndexProxyTrait<ConstIndexProxy>(position),
    m_mesh(mesh)
{

}

FD3D::ConstIndexProxy::~ConstIndexProxy()
{

}

FD3D::IndexProxy::IndexProxy(AbstractMesh *mesh, size_t position) :
    internal::ConstIndexProxyTrait<IndexProxy>(position),
    m_mesh(mesh)
{

}

FD3D::IndexProxy::~IndexProxy()
{

}

uint32_t &FD3D::IndexProxy::operator*()
{
    assert(m_position < getMesh()->getNumberOfIndices());
    return *(m_mesh->getIndices() + m_position);
}

uint32_t FD3D::IndexProxy::getValue() const
{
    assert(m_position < getMesh()->getNumberOfIndices());
    return *(m_mesh->getIndices() + m_position);
}

void FD3D::IndexProxy::setValue(uint32_t val)
{
    *(m_mesh->getIndices() + m_position) = val;
}
