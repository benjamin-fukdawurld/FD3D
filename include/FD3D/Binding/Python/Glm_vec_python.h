#ifndef FD3D_GLM_VEC_PYTHON_H
#define FD3D_GLM_VEC_PYTHON_H

#include <pybind11/embed.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_vec(pybind11::module &m);
        PYBIND11_EXPORT void bind_vec2(pybind11::module &m);
        PYBIND11_EXPORT void bind_vec3(pybind11::module &m);
        PYBIND11_EXPORT void bind_vec4(pybind11::module &m);
        PYBIND11_EXPORT void bind_quat(pybind11::module &m);

        PYBIND11_EXPORT void bind_mat(pybind11::module &m);
        PYBIND11_EXPORT void bind_mat2(pybind11::module &m);
        PYBIND11_EXPORT void bind_mat3(pybind11::module &m);
        PYBIND11_EXPORT void bind_mat4(pybind11::module &m);
    }
}

#endif // FD3D_GLM_VEC_PYTHON_H
