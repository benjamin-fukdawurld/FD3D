#ifndef LIGHTCOLOR_H
#define LIGHTCOLOR_H

#include <glm/vec4.hpp>

namespace FD3D
{
    struct LightColor
    {
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;

        LightColor();

        LightColor(const glm::vec4 &ambient,
                   const glm::vec4 &diffuse,
                   const glm::vec4 &specular);
    };
}

#endif // LIGHTCOLOR_H
