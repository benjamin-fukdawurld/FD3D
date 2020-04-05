#ifndef LIGHTTYPE_H
#define LIGHTTYPE_H

#include <cstdint>

namespace FD3D
{
    enum class LightType : uint8_t
    {
        Undefined,
        SpotLight,
        PointLight,
        DirectionalLight,
        AmbientLight,
        AreaLight
    };
}

#endif // LIGHTTYPE_H
