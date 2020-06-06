#include <FD3D/Binding/Python/Material_python.h>

#include <FD3D/Binding/Python/Component_python.h>

#include <FDCore/Binding/Python/Resource_python.h>

namespace py =  pybind11;

void FD3D::Python::bind_material(pybind11::module &m)
{
    auto type = py::enum_<FD3D::TextureType>(m, "TextureType")
                .value("Invalid", FD3D::TextureType::Invalid)
                .value("None", FD3D::TextureType::None)
                .value("Diffuse", FD3D::TextureType::Diffuse)
                .value("Specular", FD3D::TextureType::Specular)
                .value("Ambient", FD3D::TextureType::Ambient)
                .value("Emissive", FD3D::TextureType::Emissive)
                .value("Height", FD3D::TextureType::Height)
                .value("Normals", FD3D::TextureType::Normals)
                .value("Shininess", FD3D::TextureType::Shininess)
                .value("Opacity", FD3D::TextureType::Opacity)
                .value("Displacement", FD3D::TextureType::Displacement)
                .value("LightMap", FD3D::TextureType::LightMap)
                .value("Reflection", FD3D::TextureType::Reflection);

    auto tex = py::class_<FD3D::AbstractTexture, FDCore::Python::PyAbstractResource<FD3D::AbstractTexture>>(m, "AbstractTexture")
            .def(py::init_alias<>())
            .def(py::init_alias<std::string_view>())
            .def(py::init_alias<std::string_view, std::string_view>())
            .def_property("type", &FD3D::AbstractTexture::getType, &FD3D::AbstractTexture::setType);

    auto mat = py::class_<FD3D::Material, FDCore::Python::PyResource<FD3D::Material>>(m, "Material")
            .def(py::init_alias<>())
            .def(py::init_alias<std::string_view>())
            .def(py::init_alias<std::string_view, std::string_view>())
            .def_property("ambientColor", [](FD3D::Material &mat) { return mat.getAmbientColor(); }, &FD3D::Material::setAmbientColor)
            .def_property("diffuseColor", [](FD3D::Material &mat) { return mat.getDiffuseColor(); }, &FD3D::Material::setDiffuseColor)
            .def_property("specularColor", [](FD3D::Material &mat) { return mat.getSpecularColor(); }, &FD3D::Material::setSpecularColor)
            .def_property("shininess", &FD3D::Material::getShininess, &FD3D::Material::setShininess)
            .def_property("opacity", &FD3D::Material::getOpacity, &FD3D::Material::setOpacity)
            .def("getTextureMap", py::overload_cast<>(&FD3D::Material::getTextureMap))
            .def("getTextures", py::overload_cast<FD3D::TextureType>(&FD3D::Material::getTextures))
            .def("hasTexture", &FD3D::Material::hasTextures)
            .def("__getitem__", py::overload_cast<FD3D::TextureType>(&FD3D::Material::getTextures))
            .def("__getitem__", [](FD3D::Material &mat, FD3D::TextureType type, size_t index) { return mat.getTextures(type)[index]; });

    auto texComp = py::class_<FD3D::TextureComponent, FD3D::Python::PyComponent<FD3D::TextureComponent>>(m, "TextureComponent")
            .def(py::init_alias())
            .def(py::init_alias<FD3D::AbstractTexture*>())
            .def(py::init_alias<FD3D::AbstractTexture*, uint32_t, FD3D::TextureType>())
            .def_property("asset", py::overload_cast<>(&FD3D::TextureComponent::getAsset), &FD3D::TextureComponent::setAsset)
            .def_property("textureId", &FD3D::TextureComponent::getTextureId, &FD3D::TextureComponent::setTextureId)
            .def_property("type", &FD3D::TextureComponent::getType, &FD3D::TextureComponent::setType);

    auto matComp = py::class_<FD3D::MaterialComponent, FD3D::Python::PyComponent<FD3D::MaterialComponent>>(m, "MaterialComponent")
            .def(py::init_alias())
            .def(py::init_alias<FD3D::Material*>())
            .def_property("asset", py::overload_cast<>(&FD3D::MaterialComponent::getAsset), &FD3D::MaterialComponent::setAsset)
            .def_property("ambientColor", [](FD3D::MaterialComponent &mat) { return mat.getAmbientColor(); }, &FD3D::MaterialComponent::setAmbientColor)
            .def_property("diffuseColor", [](FD3D::MaterialComponent &mat) { return mat.getDiffuseColor(); }, &FD3D::MaterialComponent::setDiffuseColor)
            .def_property("specularColor", [](FD3D::MaterialComponent &mat) { return mat.getSpecularColor(); }, &FD3D::MaterialComponent::setSpecularColor)
            .def_property("shininess", &FD3D::MaterialComponent::getShininess, &FD3D::MaterialComponent::setShininess)
            .def_property("opacity", &FD3D::MaterialComponent::getOpacity, &FD3D::MaterialComponent::setOpacity)
            .def("getTextures", py::overload_cast<>(&FD3D::MaterialComponent::getTextures))
            .def("getTextures", py::overload_cast<FD3D::TextureType>(&FD3D::MaterialComponent::getTextures))
            .def("__getitem__", py::overload_cast<FD3D::TextureType>(&FD3D::MaterialComponent::getTextures))
            .def("__getitem__", [](FD3D::MaterialComponent &mat, FD3D::TextureType type, size_t index) { return mat.getTextures(type)[index]; });
}
