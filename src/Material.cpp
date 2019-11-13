#include "include/FD3D/Material.h"


FD3D::Material::Material() :
    m_ambientColor(1.0f, 1.0f, 1.0f),
    m_diffuseColor(1.0f, 1.0f, 1.0f),
    m_specularColor(1.0f, 1.0f, 1.0f),
    m_shininess(1.0f)
{

}

const std::string &FD3D::Material::getName() const
{
    return m_name;
}

void FD3D::Material::setName(const std::string &name)
{
    m_name = name;
}

glm::vec3 &FD3D::Material::getAmbientColor()
{
    return m_ambientColor;
}

const glm::vec3 &FD3D::Material::getAmbientColor() const
{
    return m_ambientColor;
}

void FD3D::Material::setAmbientColor(const glm::vec3 &ambient)
{
    m_ambientColor = ambient;
}

glm::vec3 &FD3D::Material::getDiffuseColor()
{
    return m_diffuseColor;
}

const glm::vec3 &FD3D::Material::getDiffuseColor() const
{
    return m_diffuseColor;
}

void FD3D::Material::setDiffuseColor(const glm::vec3 &diffuse)
{
    m_diffuseColor = diffuse;
}

glm::vec3 &FD3D::Material::getSpecularColor()
{
    return m_specularColor;
}

const glm::vec3 &FD3D::Material::getSpecularColor() const
{
    return m_specularColor;
}

void FD3D::Material::setSpecularColor(const glm::vec3 &specular)
{
    m_specularColor = specular;
}

float FD3D::Material::getShininess() const
{
    return m_shininess;
}

void FD3D::Material::setShininess(float shininess)
{
    m_shininess = shininess;
}
