#include <FD3D/Binding/Python/Scene_python.h>

namespace py = pybind11;

void FD3D::Python::bind_scene(pybind11::module &m)
{
    auto s = py::class_<FD3D::Scene>(m, "Scene")
            .def(py::init())
            .def_property_readonly("rootId", &FD3D::Scene::getRootId)
            .def_property_readonly("rootNode", [](FD3D::Scene &scene) { return scene.getNode(scene.getRootId()); })
            .def("clear", &FD3D::Scene::clear)
            .def("getNode", [](FD3D::Scene &scene, FD3D::Scene::node_id_type id) { return scene.getNode(id); })
            .def("addNode", &FD3D::Scene::addNode)
            .def("removeNode", &FD3D::Scene::removeNode)
            .def("removeNodeAt", &FD3D::Scene::removeNodeAt)
            .def("hasNodes", &FD3D::Scene::hasNodes)
            .def("clearNodes", &FD3D::Scene::clearNodes)
            .def("getNodeCount", &FD3D::Scene::getNodeCount)
            .def("findByName", [](FD3D::Scene &scene, std::string &name) { return scene.findByName(name); })
            .def("getComponent", [](FD3D::Scene &scene, FD3D::Scene::node_id_type id) { return scene.getComponent(id); })
            .def("addComponent", &FD3D::Scene::addComponent)
            .def("removeComponent", &FD3D::Scene::removeComponent)
            .def("removeComponentAt", &FD3D::Scene::removeComponentAt)
            .def("hasComponents", &FD3D::Scene::hasComponents)
            .def("clearComponents", &FD3D::Scene::clearNodes)
            .def("getComponentCount", &FD3D::Scene::getNodeCount)
            .def("findComponentsByName", [](FD3D::Scene &scene, std::string &name) { return scene.findComponentsByName(name); })
            .def("bindComponent", &FD3D::Scene::bindComponent)
            .def("unbindComponent", &FD3D::Scene::unbindComponent)
            .def("getNodeComponentIds", [](FD3D::Scene &scene, FD3D::Scene::node_id_type id) { return scene.getNodeComponentIds(id); })
            .def("getNodeComponentIds", [](FD3D::Scene &scene, FD3D::Scene::node_id_type id, std::function<bool(const Component*)> pred)
            {
                return scene.getNodeComponentIds(id, pred);
            })
            .def("getNodeComponents", [](FD3D::Scene &scene, FD3D::Scene::node_id_type id) { return scene.getNodeComponents(id); })
            .def("getNodeComponents", [](FD3D::Scene &scene, FD3D::Scene::node_id_type id, std::function<bool(const Component*)> pred)
            {
                return scene.getNodeComponents(id, pred);
            })
            .def("getBoundNodes", [](FD3D::Scene &scene, FD3D::Scene::component_id_type id) { return scene.getBoundNodes(id); });
}
