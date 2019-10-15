#include <FD3D/Light.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>

FD3D::Light::Light() :
    m_ambient(1.0f, 1.0f, 1.0f, 1.0f),
    m_position(0.0f, 1.0f, 0.0f),
    m_direction(0.0f, -1.0f, 0.0f)
{

}

glm::vec4 &FD3D::Light::getAmbientColor()
{
    return m_ambient;
}

const glm::vec4 &FD3D::Light::getAmbientColor() const
{
    return m_ambient;
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

void FD3D::Light::setAmbientColor(const glm::vec4 color)
{
    m_ambient = color;
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
