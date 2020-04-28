#include <FD3D/Binding/Python/Transform_python.h>

#include <FD3D/SceneGraph/SceneNode.h>
#include <FD3D/Binding/Python/SceneNode_python.h>

#include <pybind11/operators.h>

namespace py = pybind11;

void FD3D::Python::bind_transform(pybind11::module &m)
{
    py::class_<FD3D::Transform, PyTransform<>> tran(m, "Transform");
    tran.def(py::init_alias())
            .def(py::init_alias<const glm::vec3 &, const glm::vec3 &, const glm::quat &>())
            .def_property_readonly("matrix", &FD3D::Transform::getMatrix)
            .def_property_readonly("forward", &FD3D::Transform::getForward)
            .def_property_readonly("backward", &FD3D::Transform::getBackward)
            .def_property_readonly("left", &FD3D::Transform::getLeft)
            .def_property_readonly("right", &FD3D::Transform::getRight)
            .def_property_readonly("up", &FD3D::Transform::getUp)
            .def_property_readonly("down", &FD3D::Transform::getDown)
            .def_property_readonly("isUpToDate", &FD3D::Transform::isUpToDate)
            .def_property("position", [](const FD3D::Transform &t) { return &t.getPosition(); }, &FD3D::Transform::setPosition)
            .def_property("scale_value", [](const FD3D::Transform &t) { return &t.getScale(); }, &FD3D::Transform::setScale)
            .def_property("rotation", [](const FD3D::Transform &t) { return &t.getRotation(); },
                                      [](FD3D::Transform &t, const glm::quat &q) { t.setRotation(q); } )
            .def_property("eulerAngles", &FD3D::Transform::getEulerAngles, [](FD3D::Transform &t, const glm::vec3 &v) { return t.setRotation(v); })
            .def("translate", &FD3D::Transform::translate)
            .def("rotate", py::overload_cast<const glm::quat&>(&FD3D::Transform::rotate))
            .def("rotate", py::overload_cast<const glm::vec3&>(&FD3D::Transform::rotate))
            .def("scale", py::overload_cast<const glm::vec3&>(&FD3D::Transform::scale))
            .def("scale", py::overload_cast<float>(&FD3D::Transform::scale))
            .def("setScaleFactor", &FD3D::Transform::setScaleFactor)
            .def("invalidate", &FD3D::Transform::invalidate)
            .def("update", &FD3D::Transform::update);

    auto node = py::class_<FD3D::ObjectNode, FD3D::Python::PySceneNode<FD3D::ObjectNode>>(m, "ObjectNode")
                .def(py::init_alias<FD3D::SceneNode::id_type>(), py::arg("parent") = 0)
                .def_property("entity", [] (FD3D::ObjectNode &node) { return &node.getEntity(); },
                                        [] (FD3D::ObjectNode &node, const FD3D::Transform &t) { node.setEntity(t); }, py::return_value_policy::reference_internal)
                .def_property_readonly("typeCode", &FD3D::SceneNode::getTypeCode, py::return_value_policy::reference)
                .def_property_readonly("typeHash", &FD3D::SceneNode::getTypeCodeHash)
                .def("matchTypeCodeHash", &FD3D::SceneNode::matchTypeCodeHash);
}
