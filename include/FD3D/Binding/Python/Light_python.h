#ifndef FD3D_LIGHT_PYTHON_H
#define FD3D_LIGHT_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Light/Light.h>

namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_light(pybind11::module &m);
    }
}

#endif // FD3D_LIGHT_PYTHON_H
