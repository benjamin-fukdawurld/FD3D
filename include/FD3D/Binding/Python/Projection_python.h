#ifndef FD3D_PROJECTION_PYTHON_H
#define FD3D_PROJECTION_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Camera/Projection.h>

namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_projection(pybind11::module &m);
        PYBIND11_EXPORT void bind_projection_type(pybind11::module &m);
        PYBIND11_EXPORT void bind_projection_class(pybind11::module &m);
    }
}

#endif // FD3D_PROJECTION_PYTHON_H
