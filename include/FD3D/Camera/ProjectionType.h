#ifndef PROJECTIONTYPE_H
#define PROJECTIONTYPE_H

#include <cstdint>

namespace FD3D
{
    enum class ProjectionType : uint8_t
    {
        Orthographic,
        Perspective,
        Frustum
    };
}

#endif // PROJECTIONTYPE_H
