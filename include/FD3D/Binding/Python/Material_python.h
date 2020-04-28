#ifndef MATERIAL_PYTHON_H
#define MATERIAL_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Material/Material.h>
#include <FD3D/Material/Texture.h>


namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_material(pybind11::module &m);
    }
}

#endif // MATERIAL_PYTHON_H
