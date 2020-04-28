#include <FD3D/Binding/Python/SceneNode_python.h>
#include <FD3D/Binding/Python/Transform_python.h>

#include <FD3D/SceneGraph/Scene.h>

#include <pybind11/stl.h>

namespace py = pybind11;

void FD3D::Python::bind_node(pybind11::module &m)
{
    bind_scenenode(m);
    bind_scenenodeproxy(m);
}

void FD3D::Python::bind_scenenode(pybind11::module &m)
{
    auto node = py::class_<FD3D::SceneNode, FD3D::Python::PySceneNode<>>(m, "SceneNode")
                .def(py::init_alias<FD3D::SceneNode::id_type>(), py::arg("parent") = 0)
                .def_property_readonly("id", &FD3D::SceneNode::getId)
                .def_property("name", &FD3D::SceneNode::getName, &FD3D::SceneNode::setName)
                .def_property("parentId", &FD3D::SceneNode::getParentId, &FD3D::SceneNode::setParentId)
                .def_property_readonly("hasParent", &FD3D::SceneNode::hasParent)
                .def_property("isEnabled", &FD3D::SceneNode::isEnabled, [](FD3D::SceneNode &node, bool value)
                {
                    if(value)
                        node.enable();
                    else
                        node.disable();
                })
                .def_property_readonly("typeCode", &FD3D::SceneNode::getTypeCode, py::return_value_policy::reference)
                .def_property_readonly("typeHash", &FD3D::SceneNode::getTypeCodeHash)
                .def("matchTypeCodeHash", &FD3D::SceneNode::matchTypeCodeHash)
                .def_property("childIds", &FD3D::SceneNode::getChildIds,
                              py::overload_cast<const std::vector<FD3D::SceneNode::id_type>&>(&FD3D::SceneNode::setChildIds))
                .def("getChildId", &FD3D::SceneNode::getChildId)
                .def("addChildId", &FD3D::SceneNode::addChildId)
                .def("removeChildId", &FD3D::SceneNode::addChildId)
                .def("removeChildIdAt", &FD3D::SceneNode::addChildId)
                .def("hasChildren", &FD3D::SceneNode::addChildId)
                .def("getChildIdCount", &FD3D::SceneNode::addChildId)
                .def("clearChildIds", &FD3D::SceneNode::addChildId);
}

void FD3D::Python::bind_scenenodeproxy(pybind11::module &m)
{
    auto node = py::class_<FD3D::SceneNodeProxy>(m, "SceneNodeProxy")
                .def(py::init<FD3D::Scene&, FD3D::SceneNode*>())
                .def_property_readonly("hasNode", [](FD3D::SceneNodeProxy &proxy) { return proxy == true; })
                .def_property_readonly("node", [](FD3D::SceneNodeProxy &proxy) { return proxy.getNodeAs<FD3D::SceneNode>(); }, py::return_value_policy::reference_internal)
                .def_property_readonly("object", [](FD3D::SceneNodeProxy &proxy) { return proxy.getNodeAs<FD3D::ObjectNode>(); }, py::return_value_policy::reference_internal)
                .def("getChildAt", &FD3D::SceneNodeProxy::getChildAt)
                .def("getParent", &FD3D::SceneNodeProxy::getParent)
                .def("findByName", &FD3D::SceneNodeProxy::findByName)
                .def("getNodeComponents", py::overload_cast<>(&FD3D::SceneNodeProxy::getNodeComponents))
                .def("getNodeComponents", py::overload_cast<std::function<bool(const Component*)>>(&FD3D::SceneNodeProxy::getNodeComponents));
}

