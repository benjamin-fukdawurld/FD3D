#include <FD3D/Binding/Python/Light_python.h>

#include <FD3D/Binding/Python/SceneNode_python.h>

namespace py = pybind11;

void FD3D::Python::bind_light(pybind11::module &m)
{
    auto type = py::enum_<FD3D::LightType>(m, "LightType")
                .value("Invalid", FD3D::LightType::Invalid)
                .value("SpotLight", FD3D::LightType::SpotLight)
                .value("PointLight", FD3D::LightType::PointLight)
                .value("DirectionalLight", FD3D::LightType::DirectionalLight)
                .value("AmbientLight", FD3D::LightType::AmbientLight)
                .value("AreaLight", FD3D::LightType::AreaLight);

    auto col = py::class_<FD3D::LightColor>(m, "LightColor")
               .def(py::init<>())
               .def(py::init<const glm::vec4&, const glm::vec4&, const glm::vec4&>())
               .def_readwrite("ambient", &FD3D::LightColor::ambient)
               .def_readwrite("diffuse", &FD3D::LightColor::diffuse)
               .def_readwrite("specular", &FD3D::LightColor::specular);

    auto cone = py::class_<FD3D::LightCone>(m, "LightCone")
                .def(py::init<>())
                .def(py::init<float, float>())
                .def_property("innerAngle", &FD3D::LightCone::getInnerAngle, &FD3D::LightCone::setInnerAngle)
                .def_property("outerAngle", &FD3D::LightCone::getOuterAngle, &FD3D::LightCone::setOuterAngle);

    auto att = py::class_<FD3D::LightAttenuation>(m, "LightAttenuation")
               .def(py::init())
               .def(py::init<float, float, float>())
               .def_property("constant", &FD3D::LightAttenuation::getConstantAttenuation, &FD3D::LightAttenuation::setConstantAttenuation)
               .def_property("linear", &FD3D::LightAttenuation::getLinearAttenuation, &FD3D::LightAttenuation::setLinearAttenuation)
               .def_property("quadratic", &FD3D::LightAttenuation::getQuadraticAttenuation, &FD3D::LightAttenuation::setQuadraticAttenuation)
               .def("getAttenuation", &FD3D::LightAttenuation::getAttenuation);

    auto light = py::class_<FD3D::Light>(m, "Light")
                 .def(py::init())
                 .def_property("position", [](FD3D::Light &l) { return l.getPosition(); }, &FD3D::Light::setPosition)
                 .def_property("direction", [](FD3D::Light &l) { return l.getDirection(); }, &FD3D::Light::setDirection)
                 .def_property("up", [](FD3D::Light &l) { return l.getUp(); }, &FD3D::Light::setUp)
                 .def_property("type", &FD3D::Light::getType, &FD3D::Light::setType)
                 .def("translate", &FD3D::Light::translate)
                 .def("rotate", py::overload_cast<const glm::vec3&>(&FD3D::Light::rotate))
                 .def("rotate", py::overload_cast<const glm::quat&>(&FD3D::Light::rotate));

    auto node = py::class_<FD3D::LightNode, FD3D::Python::PySceneNode<FD3D::LightNode>>(m, "LightNode")
                .def(py::init_alias<FD3D::SceneNode::id_type>(), py::arg("parent") = 0)
                .def_property("entity", [] (FD3D::LightNode &node) { return node.getEntity(); }, &FD3D::LightNode::setEntity,
                              py::return_value_policy::reference)
                .def_property_readonly("typeCode", &FD3D::SceneNode::getTypeCode, py::return_value_policy::reference)
                .def_property_readonly("typeHash", &FD3D::SceneNode::getTypeCodeHash)
                .def("matchTypeCodeHash", &FD3D::SceneNode::matchTypeCodeHash);
}
