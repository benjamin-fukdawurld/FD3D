#include <FD3D/Binding/Python/Projection_python.h>

namespace py = pybind11;

void FD3D::Python::bind_projection(pybind11::module &m)
{
    bind_projection_type(m);
    bind_projection_class(m);
}

void FD3D::Python::bind_projection_type(pybind11::module &m)
{
    py::enum_<FD3D::ProjectionType>(m, "ProjectionType")
            .value("Invalid", FD3D::ProjectionType::Invalid)
            .value("Orthographic", FD3D::ProjectionType::Orthographic)
            .value("Perspective", FD3D::ProjectionType::Perspective)
            .value("Frustum", FD3D::ProjectionType::Frustum);
}

void FD3D::Python::bind_projection_class(pybind11::module &m)
{
    py::class_<FD3D::Projection>(m, "Projection")
            .def(py::init<>())
            .def_property("left", &FD3D::Projection::getLeft, &FD3D::Projection::setLeft)
            .def_property("right", &FD3D::Projection::getRight, &FD3D::Projection::setRight)
            .def_property("top", &FD3D::Projection::getTop, &FD3D::Projection::setTop)
            .def_property("bottom", &FD3D::Projection::getBottom, &FD3D::Projection::setBottom)
            .def_property("fov", &FD3D::Projection::getFov, &FD3D::Projection::setFov)
            .def_property("near", &FD3D::Projection::getNear, &FD3D::Projection::setNear)
            .def_property("far", &FD3D::Projection::getFar, &FD3D::Projection::setFar)
            .def_property("type", &FD3D::Projection::getType, &FD3D::Projection::setType)
            .def_property("width", &FD3D::Projection::getWidth, &FD3D::Projection::setWidth)
            .def_property("height", &FD3D::Projection::getHeight, &FD3D::Projection::setHeight)
            .def_property_readonly("aspectRatio", &FD3D::Projection::getAspectRatio)
            .def_property_readonly("isUpToDate", &FD3D::Projection::isUptoDate)
            .def_property_readonly("mat", &FD3D::Projection::getMatrix)
            .def("getMatrix", &FD3D::Projection::getMatrix)
            .def("invalidate", &FD3D::Projection::invalidate)
            .def("update", &FD3D::Projection::update);
}
