#include <FD3D/Binding/Python/VertexProxy_python.h>

#include <FD3D/Mesh/AbstractMeshComponent.h>

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
    auto cls = py::class_<FD3D::VertexProxy2>(m, "VertexProxy")
               .def(py::init([](FD3D::AbstractMeshComponent *m, size_t index){ return m->getVertex(index); }))
               .def_property("index", &FD3D::internal::ConstVertexProxyTrait2<FD3D::VertexProxy2>::getIndex,
                                      &FD3D::internal::ConstVertexProxyTrait2<FD3D::VertexProxy2>::setIndex)
               .def_property_readonly("mesh", &FD3D::internal::ConstVertexProxyTrait2<FD3D::VertexProxy2>::getMesh)
               .def_property_readonly("numberOfUvChannels", [](const FD3D::VertexProxy2 &v)
               {
                   return v.getMesh()->getNumberOfUvChannel();
               })
               .def_property_readonly("numberOfColorChannels", [](const FD3D::VertexProxy2 &v)
               {
                   return v.getMesh()->getNumberOfColorChannel();
               })
               .def("hasComponent", [](const FD3D::VertexProxy2 &v, FD3D::VertexComponentType comp)
               {
                   return v.getMesh()->hasVertexComponent(comp);
               })
               .def_property_readonly("mesh", &FD3D::internal::ConstVertexProxyTrait2<FD3D::VertexProxy2>::getMesh)
               .def("getPosition", py::overload_cast<>(&FD3D::VertexProxy2::getPosition), py::return_value_policy::reference_internal)
               .def("getPosition", py::overload_cast<>(&FD3D::VertexProxy2::getPosition, py::const_), py::return_value_policy::reference_internal)
               .def("getNormal", py::overload_cast<>(&FD3D::VertexProxy2::getNormal), py::return_value_policy::reference_internal)
               .def("getNormal", py::overload_cast<>(&FD3D::VertexProxy2::getNormal, py::const_), py::return_value_policy::reference_internal)
               .def("getTangent", py::overload_cast<>(&FD3D::VertexProxy2::getTangent), py::return_value_policy::reference_internal)
               .def("getTangent", py::overload_cast<>(&FD3D::VertexProxy2::getTangent, py::const_), py::return_value_policy::reference_internal)
               .def("getBitangent", py::overload_cast<>(&FD3D::VertexProxy2::getBitangent), py::return_value_policy::reference_internal)
               .def("getBitangent", py::overload_cast<>(&FD3D::VertexProxy2::getBitangent, py::const_), py::return_value_policy::reference_internal)
               .def(py::self += size_t())
               .def(py::self -= size_t());
}

void FD3D::Python::bind_indexproxy_class(pybind11::module &m)
{
    auto cls = py::class_<FD3D::IndexProxy2>(m, "IndexProxy")
               .def(py::init([](FD3D::AbstractMeshComponent *m, size_t pos){ return m->getIndex(pos); }))
               .def_property("position", &FD3D::internal::ConstIndexProxyTrait2<FD3D::IndexProxy2>::getPosition,
                                         &FD3D::internal::ConstIndexProxyTrait2<FD3D::IndexProxy2>::setPosition)
               .def_property("value", &FD3D::internal::ConstIndexProxyTrait2<FD3D::IndexProxy2>::getValue, &FD3D::IndexProxy2::setValue)
               .def("getMesh", &FD3D::IndexProxy2::getMesh)
               .def_property_readonly("mesh", &FD3D::internal::ConstIndexProxyTrait2<FD3D::IndexProxy2>::getMesh)
               .def_property_readonly("vertex", [](FD3D::IndexProxy2 &ind) { return ind.getMesh()->getVertex(*ind); })
               .def(py::self += size_t())
               .def(py::self -= size_t());
}
