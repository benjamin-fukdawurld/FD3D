#ifndef LIGHTTYPE_H
#define LIGHTTYPE_H

#include <cstdint>

#include <string_view>

namespace FD3D
{
    enum class LightType : uint8_t
    {
        Invalid,
        SpotLight,
        PointLight,
        DirectionalLight,
        AmbientLight,
        AreaLight
    };

    std::string_view lightTypeToString(LightType type);
    LightType lightTypeFromString(std::string_view str);
}

#endif // LIGHTTYPE_H
