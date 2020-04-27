#ifndef LIGHTTYPE_H
#define LIGHTTYPE_H

#include <cstdint>

#include <string_view>

#include <FDCore/Macros.h>

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

    FD_EXPORT std::string_view lightTypeToString(LightType type);
    FD_EXPORT LightType lightTypeFromString(std::string_view str);
}

#endif // LIGHTTYPE_H
