#include <FD3D/Binding/Python/Behavior_python.h>

namespace py = pybind11;

FD3D::PythonBehaviorWrapper::PythonBehaviorWrapper(pybind11::object self):
    FD3D::AbstractBehaviorComponent(),
    m_self(self)
{}

void FD3D::PythonBehaviorWrapper::setSelf(pybind11::object self)
{
    m_self = self;
}

pybind11::object FD3D::PythonBehaviorWrapper::getSelf() { return m_self; }

FD3D::Scene *FD3D::PythonBehaviorWrapper::getScene()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "scene"))
        return m_self.attr("scene").cast<FD3D::Scene*>();

    return nullptr;
}

const FD3D::Scene *FD3D::PythonBehaviorWrapper::getScene() const
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "scene"))
        return m_self.attr("scene").cast<FD3D::Scene*>();

    return nullptr;
}

void FD3D::PythonBehaviorWrapper::setScene(FD3D::Scene *scene)
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "scene"))
        m_self.attr("scene") = scene;
}

FD3D::SceneNode::id_type FD3D::PythonBehaviorWrapper::getNodeId() const
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "nodeId"))
        return m_self.attr("nodeId").cast<FD3D::Scene::node_id_type>();

    return 0;
}

void FD3D::PythonBehaviorWrapper::setNodeId(FD3D::SceneNode::id_type id)
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "nodeId"))
        m_self.attr("nodeId") = id;
}

void FD3D::PythonBehaviorWrapper::init()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "init"))
        m_self.attr("init")();
}

void FD3D::PythonBehaviorWrapper::quit()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "quit"))
        m_self.attr("quit")();
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
        m_self.attr("onDisable")();
}

void FD3D::PythonBehaviorWrapper::onEnable()
{
    pybind11::gil_scoped_acquire acquire;
    if(py::hasattr(m_self, "onEnable"))
        m_self.attr("onEnable")();
}

const char *FD3D::PythonBehaviorWrapper::getTypeCode() const
{
    return FDCore::TypeCodeHelper<FD3D::PythonBehaviorWrapper>::code;
}

size_t FD3D::PythonBehaviorWrapper::getTypeCodeHash() const
{
    return FDCore::TypeCodeHelper<FD3D::PythonBehaviorWrapper>::hash();
}

bool FD3D::PythonBehaviorWrapper::matchTypeCodeHash(size_t hash) const
{
    return hash == FD3D::PythonBehaviorWrapper::getTypeCodeHash() || FD3D::AbstractBehaviorComponent::matchTypeCodeHash(hash);
}


void FD3D::Python::bind_behavior(pybind11::module &m)
{
    auto bvr = py::class_<FD3D::BehaviorComponent, FD3D::Python::PyBehavior<>>(m, "Behavior")
            .def(py::init_alias())
            .def(py::init_alias<FD3D::Scene *, FD3D::SceneNode::id_type>())
            .def_property("nodeId", &FD3D::BehaviorComponent::getNodeId, &FD3D::BehaviorComponent::setNodeId)
            .def_property_readonly("node", [](FD3D::BehaviorComponent &bvr) { return bvr.getNode(); })
            .def_property_readonly("hasScene", &FD3D::BehaviorComponent::hasScene)
            .def_property_readonly("hasNode", &FD3D::BehaviorComponent::hasNode)
            .def_property("scene", [](FD3D::BehaviorComponent &bvr) { return bvr.getScene(); },
                                   &FD3D::BehaviorComponent::setScene, py::return_value_policy::reference_internal);
}
