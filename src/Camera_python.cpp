#include <FD3D/Binding/Python/Camera_python.h>

#include <FD3D/Binding/Python/Transform_python.h>
#include <FD3D/Binding/Python/SceneNode_python.h>

namespace py = pybind11;

void FD3D::Python::bind_camera(pybind11::module &m)
{
    auto cam = py::class_<FD3D::Camera, FD3D::Python::PyTransform<FD3D::Camera>>(m, "Camera")
            .def_property_readonly("target", &FD3D::Camera::getTarget);

    auto node = py::class_<FD3D::CameraNode, FD3D::Python::PySceneNode<FD3D::CameraNode>>(m, "FD3D::CameraNode")
                .def(py::init_alias<FD3D::SceneNode::id_type>(), py::arg("parent") = 0)
                .def_property("entity", [] (FD3D::ObjectNode &node) { return node.getEntity(); },
                                        [] (FD3D::ObjectNode &node, const FD3D::Transform &t) { node.setEntity(t); })
                .def_property_readonly("typeCode", &FD3D::SceneNode::getTypeCode, py::return_value_policy::reference)
                .def_property_readonly("typeHash", &FD3D::SceneNode::getTypeCodeHash)
                .def("matchTypeCodeHash", &FD3D::SceneNode::matchTypeCodeHash);
}
