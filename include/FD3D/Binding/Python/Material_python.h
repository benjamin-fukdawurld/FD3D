#ifndef FD3D_MATERIAL_PYTHON_H
#define FD3D_MATERIAL_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Material/MaterialComponent.h>
#include <FD3D/Material/TextureComponent.h>


namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_material(pybind11::module &m);
    }
}

#endif // FD3D_MATERIAL_PYTHON_H
