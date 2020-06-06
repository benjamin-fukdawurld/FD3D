#ifndef FD3D_FD3DPYTHON_H
#define FD3DPYTHON_H

#include <FD3D/Binding/Python/Glm_vec_python.h>
#include <FD3D/Binding/Python/Projection_python.h>
#include <FD3D/Binding/Python/VertexProxy_python.h>
#include <FD3D/Binding/Python/Component_python.h>
#include <FD3D/Binding/Python/SceneNode_python.h>
#include <FD3D/Binding/Python/Transform_python.h>
#include <FD3D/Binding/Python/Behavior_python.h>
#include <FD3D/Binding/Python/Scene_python.h>
#include <FD3D/Binding/Python/Camera_python.h>
#include <FD3D/Binding/Python/Light_python.h>
#include <FD3D/Binding/Python/Material_python.h>
#include <FD3D/Binding/Python/Mesh_python.h>

extern pybind11::detail::embedded_module PyFD3D;
PYBIND11_EMBEDDED_MODULE(PyFD3D, m)
{
    FD3D::Python::bind_vec(m);
    FD3D::Python::bind_mat(m);
    FD3D::Python::bind_projection(m);
    FD3D::Python::bind_vertexproxy(m);
    FD3D::Python::bind_component(m);
    FD3D::Python::bind_node(m);
    FD3D::Python::bind_transform(m);
    FD3D::Python::bind_behavior(m);
    FD3D::Python::bind_scene(m);
    FD3D::Python::bind_camera(m);
    FD3D::Python::bind_light(m);
    FD3D::Python::bind_material(m);
    FD3D::Python::bind_mesh(m);
}

#endif // FD3D_FD3DPYTHON_H
