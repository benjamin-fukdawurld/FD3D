#ifndef FD3D_PROJECTIONTYPE_H
#define FD3D_PROJECTIONTYPE_H

#include <cstdint>

#include<string_view>

#include <FDCore/Macros.h>

namespace FD3D
{
    enum class ProjectionType : uint8_t
    {
        Invalid,
        Orthographic,
        Perspective,
        Frustum
    };

    FD_EXPORT  std::string_view projectionTypeToString(ProjectionType type);

    FD_EXPORT ProjectionType projectionTypeFromString(std::string_view str);
}

#endif // FD3D_PROJECTIONTYPE_H
