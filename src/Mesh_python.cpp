#include <FD3D/Binding/Python/Mesh_python.h>

namespace py = pybind11;

void FD3D::Python::bind_mesh(pybind11::module &m)
{
    auto abm = py::class_<FD3D::AbstractMesh, FD3D::Python::PyAbstractMesh<>>(m, "AbstractMesh")
            .def_property_readonly("hasMaterial", &FD3D::AbstractMesh::hasMaterial)
            .def_property("materialId", &FD3D::AbstractMesh::getMaterialId, &FD3D::AbstractMesh::setMaterialId)
            .def_property_readonly("hasShader", &FD3D::AbstractMesh::hasShader)
            .def_property_readonly("vertexSize", &FD3D::AbstractMesh::getVertexSize)
            .def_property_readonly("stride", &FD3D::AbstractMesh::getStride)
            .def_property_readonly("verticesDataSize", &FD3D::AbstractMesh::getVerticesDataSize)
            .def_property_readonly("indicesDataSize", &FD3D::AbstractMesh::getIndicesDataSize)
            .def_property("shaderId", &FD3D::AbstractMesh::getShaderId, &FD3D::AbstractMesh::setShaderId)
            .def_property("isInterlaced", &FD3D::AbstractMesh::isInterlaced, &FD3D::AbstractMesh::setInterlaced)
            .def_property("numberOfColorChannel", &FD3D::AbstractMesh::getNumberOfColorChannel, &FD3D::AbstractMesh::setNumberOfColorChannel)
            .def_property("numberOfUvChannel", &FD3D::AbstractMesh::getNumberOfUvChannel, &FD3D::AbstractMesh::setNumberOfUvChannel)
            .def_property("numberOfVertices", &FD3D::AbstractMesh::getNumberOfVertices, &FD3D::AbstractMesh::setNumberOfVertices)
            .def_property("numberOfIndices", &FD3D::AbstractMesh::getNumberOfIndices, &FD3D::AbstractMesh::setNumberOfIndices)
            .def("getVertex", [](FD3D::AbstractMesh &m, size_t pos) { return m.getVertex(pos); })
            .def("getVertexFromIndex", [](FD3D::AbstractMesh &m, size_t index) { return m.getVertexFromIndex(index); })
            .def("getIndex", [](FD3D::AbstractMesh &m, size_t pos) { return m.getIndex(pos); })
            .def("hasVertexComponent", &FD3D::AbstractMesh::hasVertexComponent)
            .def("addVertexComponent", &FD3D::AbstractMesh::addVertexComponent)
            .def("removeVertexComponent", &FD3D::AbstractMesh::removeVertexComponent)
            .def("getComponentOffset", &FD3D::AbstractMesh::getComponentOffset);

    auto mesh = py::class_<FD3D::Mesh, FD3D::Python::PyMesh<>>(m, "Mesh");
}
