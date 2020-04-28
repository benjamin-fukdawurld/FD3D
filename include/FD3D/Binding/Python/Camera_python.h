#ifndef CAMERA_PYTHON_H
#define CAMERA_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Camera/Camera.h>

namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_camera(pybind11::module &m);
    }
}

#endif // CAMERA_PYTHON_H
