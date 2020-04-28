#include <FD3D/Binding/Python/Behavior_python.h>

namespace py = pybind11;

FD3D::PythonBehaviorWrapper::PythonBehaviorWrapper(pybind11::object self):
    FD3D::Behavior(self.cast<FD3D::Behavior>()),
    m_self(self)
{}

FD3D::PythonBehaviorWrapper::PythonBehaviorWrapper(pybind11::object self, FD3D::Scene *scene, FD3D::SceneNode::id_type nodeId):
    FD3D::Behavior(scene, nodeId),
    m_self(std::move(self))
{}

pybind11::object FD3D::PythonBehaviorWrapper::getSelf() { return m_self; }

void FD3D::PythonBehaviorWrapper::init()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "init"))
        m_self.attr("init").cast<py::function>();
}

void FD3D::PythonBehaviorWrapper::quit()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "quit"))
        m_self.attr("quit").cast<py::function>();
}

void FD3D::PythonBehaviorWrapper::update()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "update"))
        m_self.attr("update")();
}

void FD3D::PythonBehaviorWrapper::onDisable()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "onDisable"))
        m_self.attr("onDisable").cast<py::function>();
}

void FD3D::PythonBehaviorWrapper::onEnable()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "onEnable"))
        m_self.attr("onEnable").cast<py::function>();
}


void FD3D::Python::bind_behavior(pybind11::module &m)
{
    auto bvr = py::class_<FD3D::Behavior, FD3D::Python::PyBehavior<>>(m, "Behavior")
            .def(py::init_alias())
            .def(py::init_alias<FD3D::Scene *, FD3D::SceneNode::id_type>())
            .def_property("nodeId", &FD3D::Behavior::getNodeId, &FD3D::Behavior::setNodeId)
            .def_property_readonly("node", [](FD3D::Behavior &bvr) { return bvr.getNode(); })
            .def_property_readonly("hasScene", &FD3D::Behavior::hasScene)
            .def_property_readonly("hasNode", &FD3D::Behavior::hasNode)
            .def_property("scene", [](FD3D::Behavior &bvr) { return bvr.getScene(); },
                                   &FD3D::Behavior::setScene, py::return_value_policy::reference_internal);
}
