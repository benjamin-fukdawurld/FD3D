#ifndef LIGHT_PYTHON_H
#define LIGHT_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Light/Light.h>

namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_light(pybind11::module &m);
    }
}

#endif // LIGHT_PYTHON_H
