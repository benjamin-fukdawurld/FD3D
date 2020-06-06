#ifndef FD3D_VERTEXPROXY_PYTHON_H
#define FD3D_VERTEXPROXY_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Utils/VertexProxy.h>
#include <FD3D/Utils/IndexProxy.h>

namespace FD3D
{
    namespace Python
    {
        PYBIND11_EXPORT void bind_vertexproxy(pybind11::module &m);
        PYBIND11_EXPORT void bind_vertex_component_type(pybind11::module &m);
        PYBIND11_EXPORT void bind_vertexproxy_class(pybind11::module &m);
        PYBIND11_EXPORT void bind_indexproxy_class(pybind11::module &m);
    }
}

#endif // FD3D_VERTEXPROXY_PYTHON_H
