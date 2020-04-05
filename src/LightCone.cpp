#include <FD3D/Light/LightCone.h>

#include <iostream>
#include <glm/gtc/constants.hpp>

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
