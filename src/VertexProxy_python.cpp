#include <FD3D/Binding/Python/VertexProxy_python.h>

#include <FD3D/Mesh/AbstractMesh.h>

#include <pybind11/operators.h>

namespace py = pybind11;

void FD3D::Python::bind_vertexproxy(pybind11::module &m)
{
    bind_vertex_component_type(m);
    bind_vertexproxy_class(m);
    bind_indexproxy_class(m);
}

void FD3D::Python::bind_vertex_component_type(pybind11::module &m)
{
    auto enm = py::enum_<FD3D::VertexComponentType>(m, "VertexComponentType")
               .value("Invalid", FD3D::VertexComponentType::Invalid)
               .value("Position", FD3D::VertexComponentType::Position)
               .value("Normal", FD3D::VertexComponentType::Normal)
               .value("Color", FD3D::VertexComponentType::Color)
               .value("Texture", FD3D::VertexComponentType::Texture)
               .value("Tangent", FD3D::VertexComponentType::Tangent);
}

void FD3D::Python::bind_vertexproxy_class(pybind11::module &m)
{
    auto cls = py::class_<FD3D::VertexProxy>(m, "VertexProxy")
               .def(py::init([](FD3D::AbstractMesh *m, size_t index){ return m->getVertex(index); }))
               .def_property("index", &FD3D::internal::ConstVertexProxyTrait<FD3D::VertexProxy>::getIndex,
                                      &FD3D::internal::ConstVertexProxyTrait<FD3D::VertexProxy>::setIndex)
               .def_property_readonly("mesh", &FD3D::internal::ConstVertexProxyTrait<FD3D::VertexProxy>::getMesh)
               .def_property_readonly("numberOfUvChannels", [](const FD3D::VertexProxy &v)
               {
                   return v.getMesh()->getNumberOfUvChannel();
               })
               .def_property_readonly("numberOfColorChannels", [](const FD3D::VertexProxy &v)
               {
                   return v.getMesh()->getNumberOfColorChannel();
               })
               .def("hasComponent", [](const FD3D::VertexProxy &v, FD3D::VertexComponentType comp)
               {
                   return v.getMesh()->hasVertexComponent(comp);
               })
               .def_property_readonly("mesh", &FD3D::internal::ConstVertexProxyTrait<FD3D::VertexProxy>::getMesh)
               .def("getPosition", py::overload_cast<>(&FD3D::VertexProxy::getPosition), py::return_value_policy::reference_internal)
               .def("getPosition", py::overload_cast<>(&FD3D::VertexProxy::getPosition, py::const_), py::return_value_policy::reference_internal)
               .def("getNormal", py::overload_cast<>(&FD3D::VertexProxy::getNormal), py::return_value_policy::reference_internal)
               .def("getNormal", py::overload_cast<>(&FD3D::VertexProxy::getNormal, py::const_), py::return_value_policy::reference_internal)
               .def("getTangent", py::overload_cast<>(&FD3D::VertexProxy::getTangent), py::return_value_policy::reference_internal)
               .def("getTangent", py::overload_cast<>(&FD3D::VertexProxy::getTangent, py::const_), py::return_value_policy::reference_internal)
               .def("getBitangent", py::overload_cast<>(&FD3D::VertexProxy::getBitangent), py::return_value_policy::reference_internal)
               .def("getBitangent", py::overload_cast<>(&FD3D::VertexProxy::getBitangent, py::const_), py::return_value_policy::reference_internal)
               .def(py::self += size_t())
               .def(py::self -= size_t());
}

void FD3D::Python::bind_indexproxy_class(pybind11::module &m)
{
    auto cls = py::class_<FD3D::IndexProxy>(m, "IndexProxy")
               .def(py::init([](FD3D::AbstractMesh *m, size_t pos){ return m->getIndex(pos); }))
               .def_property("position", &FD3D::internal::ConstIndexProxyTrait<FD3D::IndexProxy>::getPosition,
                                         &FD3D::internal::ConstIndexProxyTrait<FD3D::IndexProxy>::setPosition)
               .def_property("value", &FD3D::internal::ConstIndexProxyTrait<FD3D::IndexProxy>::getValue, &FD3D::IndexProxy::setValue)
               .def("getMesh", &FD3D::IndexProxy::getMesh)
               .def_property_readonly("mesh", &FD3D::internal::ConstIndexProxyTrait<FD3D::IndexProxy>::getMesh)
               .def_property_readonly("vertex", [](FD3D::IndexProxy &ind) { return ind.getMesh()->getVertex(*ind); })
               .def(py::self += size_t())
               .def(py::self -= size_t());
}
