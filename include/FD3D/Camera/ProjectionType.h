#ifndef PROJECTIONTYPE_H
#define PROJECTIONTYPE_H

#include <cstdint>

#include<string_view>

namespace FD3D
{
    enum class ProjectionType : uint8_t
    {
        Invalid,
        Orthographic,
        Perspective,
        Frustum
    };

    std::string_view projectionTypeToString(ProjectionType type);

    ProjectionType projectionTypeFromString(std::string_view str);
}

#endif // PROJECTIONTYPE_H
