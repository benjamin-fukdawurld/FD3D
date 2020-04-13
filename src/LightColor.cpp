#include <FD3D/Light/LightColor.h>

FD3D::LightColor::LightColor() :
    ambient(1.0f, 1.0f, 1.0f, 1.0f),
    diffuse(1.0f, 1.0f, 1.0f, 1.0f),
    specular(1.0f, 1.0f, 1.0f, 1.0f)
{}

FD3D::LightColor::LightColor(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular) :
    ambient(ambient),
    diffuse(diffuse),
    specular(specular)
{}
