#include <FD3D/Binding/Python/Component_python.h>

#include <pybind11/operators.h>

namespace py = pybind11;

void FD3D::Python::bind_component(pybind11::module &m)
{
    auto comp = py::class_<FD3D::Component, FD3D::Python::PyComponent<>>(m, "Component")
                .def(py::init_alias())
                .def(py::init_alias())
                .def_property_readonly("id", &FD3D::Component::getId)
                .def_property("name", &FD3D::Component::getName, &FD3D::Component::setName);;
}
