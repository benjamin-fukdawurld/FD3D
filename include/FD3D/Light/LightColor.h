#ifndef FD3D_LIGHTCOLOR_H
#define FD3D_LIGHTCOLOR_H

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

#endif // FD3D_LIGHTCOLOR_H
