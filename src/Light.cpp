#include <FD3D/Light/Light.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/euler_angles.hpp>

#include <iostream>

FD3D::Light::Light() :
    m_position(0.0f, 1.0f, 0.0f),
    m_direction(0.0f, -1.0f, 0.0f)
{

}

const std::string &FD3D::Light::getName() const
{
    return m_name;
}

void FD3D::Light::setName(const std::string &name)
{
    m_name = name;
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

FD3D::LightColor::LightColor() :
    ambient(0.0f, 0.0f, 0.0f, 1.0f),
    diffuse(0.0f, 0.0f, 0.0f, 1.0f),
    specular(0.0f, 0.0f, 0.0f, 1.0f)
{}

FD3D::LightColor::LightColor(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular) :
    ambient(ambient),
    diffuse(diffuse),
    specular(specular)
{}

FD3D::LightAttenuation::LightAttenuation() :
    m_constantAttenuation(1.0f),
    m_linearAttenuation(0.0f),
    m_quadraticAttenuation(0.0f)
{}

FD3D::LightAttenuation::LightAttenuation(float constant, float linear, float quadratic) :
    LightAttenuation()
{
    setConstantAttenuation(constant);
    setLinearAttenuation(linear);
    setQuadraticAttenuation(quadratic);
}

float FD3D::LightAttenuation::getConstantAttenuation() const
{
    return m_constantAttenuation;
}

void FD3D::LightAttenuation::setConstantAttenuation(float val)
{
    if(val < 1.0f)
    {
        std::cerr << "constant light attenuation cannot be less than 1.0, received '"
                  << val << "'" << std::endl;

        return;
    }

    m_constantAttenuation = val;
}

float FD3D::LightAttenuation::getLinearAttenuation() const
{
    return m_linearAttenuation;
}

void FD3D::LightAttenuation::setLinearAttenuation(float val)
{
    if(val < 0.0f)
    {
        std::cerr << "linear light attenuation cannot be less than 0.0, received '"
                  << val << "'" << std::endl;

        return;
    }

    m_linearAttenuation = val;
}

float FD3D::LightAttenuation::getQuadraticAttenuation() const
{
    return m_quadraticAttenuation;
}

void FD3D::LightAttenuation::setQuadraticAttenuation(float val)
{
    if(val < 0.0f)
    {
        std::cerr << "quadratic light attenuation cannot be less than 0.0, received '"
                  << val << "'" << std::endl;

        return;
    }

    m_quadraticAttenuation = val;
}

float FD3D::LightAttenuation::getAttenuation(float distance) const
{
    return 1/(m_constantAttenuation + m_linearAttenuation * distance
              + m_quadraticAttenuation * distance * distance);
}

FD3D::LightCone::LightCone() :
    m_innerAngle(glm::pi<float>() * 2),
    m_outerAngle(glm::pi<float>() * 2)
{}

FD3D::LightCone::LightCone(float innerAngle, float outerAngle) :
    LightCone()
{
    setInnerAngle(innerAngle);
    setOuterAngle(outerAngle);
}

float FD3D::LightCone::getInnerAngle() const
{
    return m_innerAngle;
}

void FD3D::LightCone::setInnerAngle(float val)
{
    if(val < 0.0f)
    {
        std::cerr << "inner cone angle cannot be less than 0.0, received '"
                  << val << "'" << std::endl;

        return;
    }

    m_innerAngle = val;
}

float FD3D::LightCone::getOuterAngle() const
{
    return m_outerAngle;
}

void FD3D::LightCone::setOuterAngle(float val)
{
    if(val < 0.0f)
    {
        std::cerr << "outer cone angle cannot be less than 0.0, received '"
                  << val << "'" << std::endl;

        return;
    }

    m_outerAngle = val;
}
