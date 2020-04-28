#ifndef LIGHTCOLOR_H
#define LIGHTCOLOR_H

#include <glm/vec4.hpp>

#include <FDCore/Macros.h>

namespace FD3D
{
    struct FD_EXPORT LightColor
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
