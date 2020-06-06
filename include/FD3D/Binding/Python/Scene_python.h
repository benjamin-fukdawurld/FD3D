#ifndef FD3D_SCENE_PYTHON_H
#define FD3D_SCENE_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/SceneGraph/Scene.h>

namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_scene(pybind11::module &m);
    }
}

#endif // FD3D_SCENE_PYTHON_H
