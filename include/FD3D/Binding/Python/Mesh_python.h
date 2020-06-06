#ifndef FD3D_MESH_PYTHON_H
#define FD3D_MESH_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Mesh/AbstractMeshComponent.h>
#include <FD3D/Mesh/MeshComponent.h>

#include <FD3D/Binding/Python/Component_python.h>

namespace FD3D
{
    namespace Python
    {
        template<typename MeshBase = FD3D::AbstractMeshComponent>
        class PYBIND11_EXPORT PyAbstractMesh : public PyComponent<MeshBase>
        {
            public:
                /* Inherit the constructors */
                using PyComponent<MeshBase>::PyComponent;

                float *getVertices() override
                {
                    PYBIND11_OVERLOAD_PURE(
                        float *, /* Return type */
                        MeshBase,      /* Parent class */
                        getVertices,         /* Name of function in C++ (must match Python name) */
                    );
                }

                const float *getVertices() const  override
                {
                    return const_cast<const float*>(const_cast<PyAbstractMesh<MeshBase>*>(this)->getVertices());
                }

                void setVertices(const float *data) override
                {
                    PYBIND11_OVERLOAD_PURE(
                        void, /* Return type */
                        MeshBase,      /* Parent class */
                        setVertices,         /* Name of function in C++ (must match Python name) */
                        data
                    );
                }

                uint32_t *getIndices() override
                {
                    PYBIND11_OVERLOAD_PURE(
                        uint32_t *, /* Return type */
                        MeshBase,      /* Parent class */
                        getIndices,         /* Name of function in C++ (must match Python name) */
                    );
                }

                const uint32_t *getIndices() const override
                {
                    return const_cast<const uint32_t*>(const_cast<PyAbstractMesh<MeshBase>*>(this)->getIndices());
                }

                void setIndices(const uint32_t *data) override
                {
                    PYBIND11_OVERLOAD_PURE(
                        void, /* Return type */
                        MeshBase,      /* Parent class */
                        setIndices,         /* Name of function in C++ (must match Python name) */
                        data
                    );
                }

                size_t getNumberOfVertices() const override
                {
                    PYBIND11_OVERLOAD_PURE(
                        size_t, /* Return type */
                        MeshBase,      /* Parent class */
                        getNumberOfVertices,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void setNumberOfVertices(size_t val) override
                {
                    PYBIND11_OVERLOAD_PURE(
                        void, /* Return type */
                        MeshBase,      /* Parent class */
                        setNumberOfVertices,         /* Name of function in C++ (must match Python name) */
                        val
                    );
                }

                size_t getNumberOfIndices() const override
                {
                    PYBIND11_OVERLOAD_PURE(
                        size_t, /* Return type */
                        MeshBase,      /* Parent class */
                        getNumberOfIndices,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void setNumberOfIndices(size_t val) override
                {
                    PYBIND11_OVERLOAD_PURE(
                        void, /* Return type */
                        MeshBase,      /* Parent class */
                        setNumberOfIndices,         /* Name of function in C++ (must match Python name) */
                        val
                    );
                }
        };

        template<typename MeshBase = FD3D::MeshComponent>
        class PYBIND11_EXPORT PyMesh : public PyAbstractMesh<MeshBase>
        {
            public:
                /* Inherit the constructors */
                using PyAbstractMesh<MeshBase>::PyAbstractMesh;

                float *getVertices() override
                {
                    PYBIND11_OVERLOAD(
                        float *, /* Return type */
                        MeshBase,      /* Parent class */
                        getVertices,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void setVertices(const float *data) override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        MeshBase,      /* Parent class */
                        setVertices,         /* Name of function in C++ (must match Python name) */
                        data
                    );
                }

                uint32_t *getIndices() override
                {
                    PYBIND11_OVERLOAD(
                        uint32_t *, /* Return type */
                        MeshBase,      /* Parent class */
                        getIndices,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void setIndices(const uint32_t *data) override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        MeshBase,      /* Parent class */
                        setIndices,         /* Name of function in C++ (must match Python name) */
                        data
                    );
                }

                size_t getNumberOfVertices() const override
                {
                    PYBIND11_OVERLOAD(
                        size_t, /* Return type */
                        MeshBase,      /* Parent class */
                        getNumberOfVertices,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void setNumberOfVertices(size_t val) override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        MeshBase,      /* Parent class */
                        setNumberOfVertices,         /* Name of function in C++ (must match Python name) */
                        val
                    );
                }

                size_t getNumberOfIndices() const override
                {
                    PYBIND11_OVERLOAD(
                        size_t, /* Return type */
                        MeshBase,      /* Parent class */
                        getNumberOfIndices,         /* Name of function in C++ (must match Python name) */
                    );
                }

                void setNumberOfIndices(size_t val) override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        MeshBase,      /* Parent class */
                        setNumberOfIndices,         /* Name of function in C++ (must match Python name) */
                        val
                    );
                }
        };

        PYBIND11_EXPORT void bind_mesh(pybind11::module &m);
    }
}

#endif // FD3D_MESH_PYTHON_H
