#include <FD3D/Binding/Python/Material_python.h>

#include <FD3D/Binding/Python/Component_python.h>

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

    auto tex = py::class_<FD3D::Texture, FD3D::Python::PyComponent<FD3D::Texture>>(m, "Texture")
            .def(py::init())
            .def(py::init<uint32_t, FD3D::TextureType>())
            .def_property("textureId", &FD3D::Texture::getTextureId, &FD3D::Texture::setTextureId)
            .def_property("type", &FD3D::Texture::getType, &FD3D::Texture::setType);

    auto mat = py::class_<FD3D::Material, FD3D::Python::PyComponent<FD3D::Material>>(m, "Material")
            .def(py::init())
            .def_property("ambientColor", [](FD3D::Material &mat) { return mat.getAmbientColor(); }, &FD3D::Material::setAmbientColor)
            .def_property("diffuseColor", [](FD3D::Material &mat) { return mat.getDiffuseColor(); }, &FD3D::Material::setDiffuseColor)
            .def_property("specularColor", [](FD3D::Material &mat) { return mat.getSpecularColor(); }, &FD3D::Material::setSpecularColor)
            .def_property("shininess", &FD3D::Material::getShininess, &FD3D::Material::setShininess)
            .def_property("opacity", &FD3D::Material::getOpacity, &FD3D::Material::setOpacity)
            .def("getTextures", py::overload_cast<>(&FD3D::Material::getTextures))
            .def("getTextures", py::overload_cast<FD3D::TextureType>(&FD3D::Material::getTextures))
            .def("__getitem__", py::overload_cast<FD3D::TextureType>(&FD3D::Material::getTextures))
            .def("__getitem__", [](FD3D::Material &mat, FD3D::TextureType type, size_t index) { return mat.getTextures(type)[index]; });
}
