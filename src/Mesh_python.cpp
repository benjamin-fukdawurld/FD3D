#include <FD3D/Binding/Python/Mesh_python.h>

namespace py = pybind11;

void FD3D::Python::bind_mesh(pybind11::module &m)
{
    auto abm = py::class_<FD3D::AbstractMeshComponent, FD3D::Python::PyAbstractMesh<>>(m, "AbstractMesh")
            .def_property_readonly("hasMaterial", &FD3D::AbstractMeshComponent::hasMaterial)
            .def_property("materialId", &FD3D::AbstractMeshComponent::getMaterialId, &FD3D::AbstractMeshComponent::setMaterialId)
            .def_property_readonly("hasShader", &FD3D::AbstractMeshComponent::hasShader)
            .def_property_readonly("vertexSize", &FD3D::AbstractMeshComponent::getVertexSize)
            .def_property_readonly("stride", &FD3D::AbstractMeshComponent::getStride)
            .def_property_readonly("verticesDataSize", &FD3D::AbstractMeshComponent::getVerticesDataSize)
            .def_property_readonly("indicesDataSize", &FD3D::AbstractMeshComponent::getIndicesDataSize)
            .def_property("shaderId", &FD3D::AbstractMeshComponent::getShaderId, &FD3D::AbstractMeshComponent::setShaderId)
            .def_property("isInterlaced", &FD3D::AbstractMeshComponent::isInterlaced, &FD3D::AbstractMeshComponent::setInterlaced)
            .def_property("numberOfColorChannel", &FD3D::AbstractMeshComponent::getNumberOfColorChannel, &FD3D::AbstractMeshComponent::setNumberOfColorChannel)
            .def_property("numberOfUvChannel", &FD3D::AbstractMeshComponent::getNumberOfUvChannel, &FD3D::AbstractMeshComponent::setNumberOfUvChannel)
            .def_property("numberOfVertices", &FD3D::AbstractMeshComponent::getNumberOfVertices, &FD3D::AbstractMeshComponent::setNumberOfVertices)
            .def_property("numberOfIndices", &FD3D::AbstractMeshComponent::getNumberOfIndices, &FD3D::AbstractMeshComponent::setNumberOfIndices)
            .def("getVertex", [](FD3D::AbstractMeshComponent &m, size_t pos) { return m.getVertex(pos); })
            .def("getVertexFromIndex", [](FD3D::AbstractMeshComponent &m, size_t index) { return m.getVertexFromIndex(index); })
            .def("getIndex", [](FD3D::AbstractMeshComponent &m, size_t pos) { return m.getIndex(pos); })
            .def("hasVertexComponent", &FD3D::AbstractMeshComponent::hasVertexComponent)
            .def("addVertexComponent", &FD3D::AbstractMeshComponent::addVertexComponent)
            .def("removeVertexComponent", &FD3D::AbstractMeshComponent::removeVertexComponent)
            .def("getComponentOffset", &FD3D::AbstractMeshComponent::getComponentOffset);

    auto mesh = py::class_<FD3D::MeshComponent, FD3D::Python::PyMesh<>>(m, "Mesh");
}
