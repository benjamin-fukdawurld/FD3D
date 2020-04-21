#include <FD3D/Light/Light.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>

#include <iostream>

FD3D::Light::Light() :
    m_position(0.0f, 1.0f, 0.0f),
    m_direction(0.0f, -1.0f, 0.0f),
    m_type(LightType::Invalid)
{

}

glm::vec3 &FD3D::Light::getPosition()
{
    return m_position;
}

const glm::vec3 &FD3D::Light::getPosition() const
{
    return m_position;
}

glm::vec3 &FD3D::Light::getDirection()
{
    return m_position;
}

const glm::vec3 &FD3D::Light::getDirection() const
{
    return m_position;
}

void FD3D::Light::setPosition(const glm::vec3 position)
{
    m_position = position;
}

void FD3D::Light::translate(const glm::vec3 v)
{
    m_position += v;
}

void FD3D::Light::setDirection(const glm::vec3 direction)
{
    m_direction = direction;
}

glm::vec3 &FD3D::Light::getUp()
{
    return m_up;
}

const glm::vec3 &FD3D::Light::getUp() const
{
    return m_up;
}

void FD3D::Light::setUp(const glm::vec3 up)
{
    m_up = up;
}

void FD3D::Light::rotate(const glm::vec3 angles)
{
    m_direction = glm::orientate3(angles) * m_direction;
}

void FD3D::Light::rotate(const glm::quat quaternion)
{
    m_direction = quaternion * m_direction;
}

FD3D::LightType FD3D::Light::getType() const
{
    return m_type;
}

void FD3D::Light::setType(const LightType &type)
{
    m_type = type;
}

std::string_view FD3D::lightTypeToString(FD3D::LightType type)
{
    switch(type)
    {
        case LightType::Invalid:
        return "Invalid";

        case LightType::SpotLight:
        return "SpotLight";

        case LightType::PointLight:
        return "PointLight";

        case LightType::DirectionalLight:
        return "DirectionalLight";

        case LightType::AmbientLight:
        return "AmbientLight";

        case LightType::AreaLight:
        return "AreaLight";
    }
}

FD3D::LightType FD3D::lightTypeFromString(std::string_view str)
{
    if(str == "SpotLight")
        return LightType::SpotLight;

    if(str == "PointLight")
        return LightType::PointLight;

    if(str == "DirectionalLight")
        return LightType::DirectionalLight;

    if(str == "AmbientLight")
        return LightType::AmbientLight;

    if(str == "AreaLight")
        return LightType::AreaLight;

    return LightType::Invalid;
}
