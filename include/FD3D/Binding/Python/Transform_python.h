#ifndef FD3D_TRANSFORM_PYTHON_H
#define FD3D_TRANSFORM_PYTHON_H

#include <pybind11/embed.h>
#include <FD3D/Utils/Transform.h>

namespace FD3D
{
    namespace Python
    {
        template<typename TransformBase = FD3D::Transform>
        class PYBIND11_EXPORT PyTransform : public TransformBase
        {
            public:
                /* Inherit the constructors */
                using TransformBase::TransformBase;

                /*  Trampoline (need one for each virtual function) */
                void update() const override
                {
                    PYBIND11_OVERLOAD(
                        void, /* Return type */
                        TransformBase,      /* Parent class */
                        update,         /* Name of function in C++ (must match Python name) */
                    );
                }
        };

        PYBIND11_EXPORT void bind_transform(pybind11::module &m);
    }
}

#endif // FD3D_TRANSFORM_PYTHON_H
