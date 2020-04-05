#include <FD3D/Light/LightAttenuation.h>

#include <iostream>

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
